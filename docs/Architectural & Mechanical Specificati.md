# Architectural & Mechanical Specification: Unified Multi-Region Pokémon Decompilation Engine

```markdown
# ==============================================================================
# UNIFIED MULTI-REGION ENGINE ARCHITECTURAL SPECIFICATION
# Integrated Subsystems: Red, Blue, Yellow, Gold, Silver, Crystal, Ruby,
# Sapphire, Emerald, FireRed, LeafGreen, Expansion, pokemultiregion & pokeconfluence
# ==============================================================================
```

---

## 1. Core Architecture (The "How")
`#low_level_asm` `#memory_offsets` `#ram_mapping` `#vram_management` `#interrupt_handlers` `#stack_frames` `#pointer_tables` `#binary_patching` `#opcode_optimization` `#registers`

```c
/* =============================================================================
 * MEMORY LAYOUT & BUS SPECIFICATION (ARM7TDMI 32-bit Architecture)
 * =============================================================================
 * Cartridge ROM (32 MB)  : 0x08000000 - 0x09FFFFFF (Waitstates: N=4/3/2, S=2/1)
 * EWRAM (Board RAM, 256K): 0x02000000 - 0x0203FFFF (16-bit bus, 3 waitstates)
 * IWRAM (Fast On-Chip, 32K): 0x03000000 - 0x03007FFF (32-bit bus, 0 waitstates)
 * VRAM (Video Memory, 96K): 0x06000000 - 0x06017FFF (16-bit text, 32-bit bitmap)
 * OAM (Sprite Attributes): 0x07000000 - 0x070003FF (128 objects, 4 words each)
 * Palette RAM (1 KB)     : 0x05000000 - 0x050003FF (BG: 0x05000000, OBJ: 0x05000200)
 */

// Linker Section Pinning (ld_script.ld)
MEMORY
{
    ewram (rwx) : ORIGIN = 0x02000000, LENGTH = 256K
    iwram (rwx) : ORIGIN = 0x03000000, LENGTH = 32K
    rom    (rx) : ORIGIN = 0x08000000, LENGTH = 32M
}

// -----------------------------------------------------------------------------
// LOW-LEVEL INTERRUPT & VBLANK PIPELINE (IWRAM Pinned)
// -----------------------------------------------------------------------------
#define INTR_VBLANK   (1 << 0)
#define INTR_HBLANK   (1 << 1)
#define INTR_VCOUNTER (1 << 2)
#define INTR_TIMER0   (1 << 3)
#define INTR_SERIAL   (1 << 7)

typedef void (*IntrFunc)(void);

// Fast Interrupt Vector Table (Mapped to 0x03007FFC in IWRAM)
extern IntrFunc gIntrTable;

void __attribute__((section(".iwram"), target("arm"))) IntrMain(void)
{
    u16 flags = REG_IF & REG_IE;
    
    // Acknowledge interrupt flags in hardware register
    REG_IF = flags;
    
    if (flags & INTR_VBLANK)
    {
        // 1. Initiate DMA3 transfer for Object Attribute Memory (128 OAM entries)
        REG_DMA3SAD = (u32)&gOamBuffer;
        REG_DMA3DAD = (u32)0x07000000;
        REG_DMA3CNT = 0x84400080; // Enable, 32-bit, HBlank-off, Count=128 words
        
        // 2. Flush Palette Buffers if dirty
        if (gPaletteFade.active)
            TransferPlttBuffer();
            
        // 3. Increment hardware tick counters
        gVBlankCounter++;
    }
    
    // Pass execution to mapped C handler via pointer table
    if (gIntrTable && (flags & INTR_VBLANK))
        gIntrTable();
}

// -----------------------------------------------------------------------------
// VRAM BG/OBJ LAYER ORCHESTRATION (Mode 0 Tile Engine)
// -----------------------------------------------------------------------------
/*
 * BG0: Text, Menus, Windows (Priority 0, CharBase 0, ScreenBase 31)
 * BG1: Overhead & Third Layer (Priority 1, CharBase 0, ScreenBase 30)
 * BG2: Middle Layer / Buildings (Priority 2, CharBase 0/1, ScreenBase 29)
 * BG3: Bottom Layer / Ground (Priority 3, CharBase 0/1, ScreenBase 28)
 */
#define REG_DISPCNT_MODE0_CONFIG  0x1F40 // Mode 0, BG0-3 enabled, OBJ enabled, 1D mapping
``` [cite: 44, 72, 87].

---

## 2. Game Logic & Systems (The "What")
`#battle_engine` `#turn_calculator` `#damage_formula` `#exp_logic` `#type_chart` `#status_effects` `#move_pool` `#ability_triggers` `#stat_scaling` `#catch_mechanics` `#evolution_logic`

```c
// -----------------------------------------------------------------------------
// BATTLE ENGINE TURN CALCULATOR & PRIORITY RESOLVER (src/battle_util.c)
// -----------------------------------------------------------------------------
s32 GetTurnPriority(u8 bank, u16 move)
{
    s32 priority = gBattleMoves[move].priority;
    u16 ability = GetBattlerAbility(bank);
    u16 holdEffect = ItemId_GetHoldEffect(gBattleMons[bank].item);

    // Gen 7+ Prankster: Non-damage moves gain +1 priority (fails vs Dark-types)
    if (ability == ABILITY_PRANKSTER && IS_MOVE_STATUS(move))
        priority += 1;
        
    // Gale Wings: Flying moves gain +1 priority at full HP
    if (ability == ABILITY_GALE_WINGS && gBattleMoves[move].type == TYPE_FLYING)
    {
        #if B_GALE_WINGS == GEN_7
        if (gBattleMons[bank].hp == gBattleMons[bank].maxHP)
            priority += 1;
        #else
            priority += 1;
        #endif
    }

    // Triage: Healing moves gain +3 priority
    if (ability == ABILITY_TRIAGE && (gBattleMoves[move].flags & FLAG_TRIAGE_AFFECTED))
        priority += 3;

    // Item Bracket Multipliers (Quick Claw, Custap Berry, Lagging Tail)
    if (holdEffect == HOLD_EFFECT_LAGGING_TAIL)
        priority -= 7;

    return priority;
}

// -----------------------------------------------------------------------------
// UNIFIED DAMAGE FORMULA (Gen 4–9 Engine Integration)
// -----------------------------------------------------------------------------
s32 CalculateMoveDamage(struct BattlePokemon *attacker, struct BattlePokemon *defender, u16 move)
{
    u32 attackVal, defenseVal;
    u32 basePower = gBattleMoves[move].power;
    u8 split = gBattleMoves[move].split; // SPLIT_PHYSICAL, SPLIT_SPECIAL, SPLIT_STATUS

    // 1. Resolve Physical / Special Category Split
    if (split == SPLIT_PHYSICAL)
    {
        attackVal = attacker->attack;
        defenseVal = (move == MOVE_BODY_PRESS) ? attacker->defense : defender->defense;
        
        // Critical hits ignore negative attack stages and positive defense stages
        ApplyStageModifiers(&attackVal, attacker->statStages[STAT_ATK]);
        ApplyStageModifiers(&defenseVal, defender->statStages[STAT_DEF]);
    }
    else // SPLIT_SPECIAL
    {
        attackVal = attacker->spAttack;
        defenseVal = (move == MOVE_PSYSHOCK) ? defender->defense : defender->spDefense;
        ApplyStageModifiers(&attackVal, attacker->statStages[STAT_SPATK]);
        ApplyStageModifiers(&defenseVal, defender->statStages[STAT_SPDEF]);
    }

    // 2. Base Damage Calculation
    // BaseDamage = ((((2 * Level / 5) + 2) * Power * A / D) / 50) + 2
    s32 damage = (2 * attacker->level) / 5 + 2;
    damage = (damage * basePower * attackVal) / defenseVal;
    damage = (damage / 50) + 2;

    // 3. Targets (Multi-Target Penalty 0.75x)
    if (IsDoubleBattle() && (gBattleMoves[move].target & MOVE_TARGET_BOTH))
        damage = (damage * 75) / 100;

    // 4. Weather Modifiers (Sun/Rain/Sandstorm/Snow)
    damage = ApplyWeatherDamageModifier(damage, move);

    // 5. Critical Hit Multiplier (Gen 6+: 1.5x, Sniper: 2.25x)
    if (gBattleStruct->isCriticalHit)
        damage = (attacker->ability == ABILITY_SNIPER) ? (damage * 225) / 100 : (damage * 150) / 100;

    // 6. STAB (Same Type Attack Bonus: 1.5x, Adaptability: 2.0x, Terastallized: 2.0x)
    if (IS_BATTLER_OF_TYPE(attacker, gBattleMoves[move].type))
        damage = (attacker->ability == ABILITY_ADAPTABILITY) ? (damage * 2) : (damage * 150) / 100;

    // 7. Type Effectiveness (Type Chart Matrix Multiplication: 0x, 0.25x, 0.5x, 1x, 2x, 4x)
    damage = ApplyTypeEffectiveness(damage, move, defender);

    // 8. Burn Reduction (0.5x on physical moves unless Guts is active)
    if ((attacker->status1 & STATUS1_BURN) && split == SPLIT_PHYSICAL && attacker->ability != ABILITY_GUTS)
        damage /= 2;

    return damage;
}

// -----------------------------------------------------------------------------
// DYNAMIC 24-GYM ENCOUNTER & TRAINER SCALING ENGINE (pokeconfluence)
// -----------------------------------------------------------------------------
u8 GetDynamicScalingTier(void)
{
    u8 badgeCount = 0;
    // Tally all acquired badges across Kanto (0-7), Johto (8-15), and Hoenn (16-23)
    badgeCount += CountBits(gSaveBlock2Ptr->kantoBadges);
    badgeCount += CountBits(gSaveBlock2Ptr->johtoBadges);
    badgeCount += CountBits(gSaveBlock2Ptr->hoennBadges);

    if (badgeCount <= 2)  return SCALING_TIER_NOVICE;       // Levels 10-16 (Basic learnsets)
    if (badgeCount <= 6)  return SCALING_TIER_INTERMEDIATE; // Levels 20-30 (Tier 2 evolutions)
    if (badgeCount <= 12) return SCALING_TIER_ADVANCED;     // Levels 35-48 (Competitive items)
    if (badgeCount <= 18) return SCALING_TIER_EXPERT;       // Levels 50-65 (Full EV spreads)
    return SCALING_TIER_CHAMPION;                           // Levels 70-85 (Mega/Z/Tera integration)
}
``` [cite: 20, 21, 30, 31, 35, 59, 85].

---

## 3. World & Environment (The "Where")
`#tile_maps` `#collision_masks` `#event_triggers` `#warp_coordinates` `#npc_ai_scripts` `#flag_system` `#global_variables` `#field_effects` `#coordinate_system`

```pory
// =============================================================================
// TRI-CONTINENTAL MERIDIAN TRANSIT GATEWAY (Poryscript Source)
// =============================================================================
script Common_EventScript_GreatMeridianTransit {
    lock
    faceplayer
    msgbox(format("Welcome to the Great Meridian Terminal. Please present your Transit Pass."), MSGBOX_DEFAULT)
    
    if (!checkitem(ITEM_MERIDIAN_PASS)) {
        msgbox(format("Access denied. The tectonic transit line requires a valid Meridian Pass."), MSGBOX_NPC)
        release
        end
    }

    message(format("Where would you like to travel?"))
    waitmessage
    multichoice(0, 0, MULTI_MERIDIAN_DESTINATIONS, FALSE)
    
    switch (var(VAR_RESULT)) {
        case 0: // Saffron Central (Kanto)
            setrespawn(HEAL_LOCATION_SAFFRON_CITY)
            warp(MAP_SAFFRON_MAGNET_TRAIN_STATION_JOHTO, 10, 14)
        case 1: // Goldenrod Terminal (Johto)
            setrespawn(HEAL_LOCATION_GOLDENROD_CITY)
            warp(MAP_GOLDENROD_CITY_MAGNET_TRAIN_STATION, 8, 12)
        case 2: // Mauville Transit Hub (Hoenn)
            setrespawn(HEAL_LOCATION_MAUVILLE_CITY)
            warp(MAP_MAUVILLE_CITY_TERMINAL, 12, 10)
        default:
            release
            end
    }
    waitstate
    release
    end
}
``` [cite: 40, 48, 71, 73, 95].

```c
// -----------------------------------------------------------------------------
// METATILE ATTRIBUTE & COLLISION MASKS (GBA 2-Byte vs 4-Byte Layout)
// -----------------------------------------------------------------------------
/*
 * In pokeemerald-expansion, metatile attributes utilize a 16-bit packed bitfield:
 * [15:12] Layer Type (0=Normal, 1=Covered/Top, 2=Split)
 * [11:8]  Encounter Type (0=None, 1=Grass, 2=Water)
 * [7:0]   Metatile Behavior (Collision, Ledges, Warps, Doors, Waterfalls)
 */
#define MB_NORMAL          0x00 // Walkable ground
#define MB_IMPASSABLE      0x01 // Solid obstacle
#define MB_TALL_GRASS      0x02 // Wild encounter field effect
#define MB_SURFABLE_WATER  0x10 // Surf field move required
#define MB_WATERFALL       0x13 // Waterfall field move required
#define MB_DOOR            0x69 // Warp transition on walk-up
#define MB_ICE_SLIDE       0x20 // Uncontrolled directional inertia
``` [cite: 45, 73].

---

## 4. Data & Assets (The "Stuff")
`#sprite_sheets` `#palette_swaps` `#midi_sequencing` `#text_compression` `#item_databases` `#pokemon_stats_table` `#move_data` `#cry_assets` `#font_rendering`

```text
================================================================================
ASSET PIPELINE TAXONOMY & INGESTION ARCHITECTURE
================================================================================

1. Pokémon Battlers (graphics/pokemon/<species>/)
   ├── front.png          : 64x64 px, 4bpp indexed (15 colors + #FF00FF transparent)
   ├── back.png           : 64x64 px, 4bpp indexed (Synchronized index palette)
   ├── anim_front.png     : 128x64 px horizontal strip (2-frame entry animation)
   ├── normal.pal         : 16-color JASC-PAL formatted master color ramp
   ├── shiny.pal          : 16-color JASC-PAL (HSV-rotated, preserving dark outlines)
   ├── icon.png           : 64x32 px (2-frame 32x32 party box jump sprite)
   └── footprint.png      : 16x16 px, 1bpp monochrome Pokédex footprint

2. Overworld Scenery & Tilesets (source_tilesets/ -> Porytiles -> data/tilesets/)
   ├── bottom.png         : 32-bit RGBA ground terrain (grass, paths, water beds)
   ├── middle.png         : 32-bit RGBA impassable blocks (walls, fences, trunks)
   ├── top.png            : 32-bit RGBA overhead canopy (treetops, roofs, archways)
   └── attributes.csv     : Metatile behavior mappings (MB_NORMAL, MB_IMPASSABLE)
   

   
3. Audio Soundfont Compilation (sound/songs/*.mid -> mid2agb -> sound/songs/*.s)
   ├── Voicegroups        : Isolated tables (voicegroup_frlg, voicegroup_gsc)
   ├── DirectSound (PCM)  : 8-bit mono WAV samples pinned in Cartridge ROM (.rodata)
   └── PSG Synthesizer    : Hardware Square Wave 1/2, Programmable Wave, Noise
```

```c
// -----------------------------------------------------------------------------
// UNIFIED POKÉMON DATA STRUCTURE (species_info.h)
// -----------------------------------------------------------------------------
struct SpeciesInfo
{
    u8 baseHP;
    u8 baseAttack;
    u8 baseDefense;
    u8 baseSpeed;
    u8 baseSpAttack;
    u8 baseSpDefense;
    u8 types;
    u8 catchRate;
    u16 expYield;
    u16 evYield_HP:2;
    u16 evYield_Attack:2;
    u16 evYield_Defense:2;
    u16 evYield_Speed:2;
    u16 evYield_SpAttack:2;
    u16 evYield_SpDefense:2;
    u16 itemCommon;
    u16 itemRare;
    u8 genderRatio;
    u8 eggCycles;
    u8 friendship;
    u8 growthRate;
    u8 eggGroups;
    u16 abilities; // =Primary,=Secondary,=Hidden Ability
    u8 bodyColor:7;
    u8 noFlip:1;
    const u32 *frontPic;
    const u32 *backPic;
    const u16 *palette;
    const u16 *shinyPalette;
    const u32 *iconSprite;
    const u8 *footprint;
};
``` [cite: 23, 24, 72].

---

## 5. Interface & UX (The "View")
`#menu_navigation` `#ui_overlays` `#cursor_logic` `#dialogue_boxes` `#battle_hud` `#inventory_screens` `#animation_states` `#screen_transitions`

```c
// -----------------------------------------------------------------------------
// DUAL-REGION / TRI-REGION POKÉNAV TOWN MAP SWITCHER (src/region_map.c)
// -----------------------------------------------------------------------------
bool8 HandleRegionMapInput(struct RegionMap *regionMap)
{
    // L-Trigger: Cycle to Previous Region
    if (JOY_NEW(L_BUTTON))
    {
        regionMap->activeRegion = (regionMap->activeRegion == 0) 
            ? REGION_COUNT - 1 
            : regionMap->activeRegion - 1;
        ReloadRegionMapTilemap(regionMap);
        return TRUE;
    }
    
    // R-Trigger: Cycle to Next Region
    if (JOY_NEW(R_BUTTON))
    {
        regionMap->activeRegion = (regionMap->activeRegion + 1) % REGION_COUNT;
        ReloadRegionMapTilemap(regionMap);
        return TRUE;
    }

    // Directional Pad Cursor Movement
    if (JOY_HELD(DPAD_UP) && regionMap->cursorY > REGION_MAP_MIN_Y)
        regionMap->cursorY--;
    if (JOY_HELD(DPAD_DOWN) && regionMap->cursorY < REGION_MAP_MAX_Y)
        regionMap->cursorY++;
    if (JOY_HELD(DPAD_LEFT) && regionMap->cursorX > REGION_MAP_MIN_X)
        regionMap->cursorX--;
    if (JOY_HELD(DPAD_RIGHT) && regionMap->cursorX < REGION_MAP_MAX_X)
        regionMap->cursorX++;

    UpdateCursorPosition(regionMap);
    return FALSE;
}

// -----------------------------------------------------------------------------
// BATTLE HUD EFFECTIVENESS HIGHLIGHTING OVERLAY (src/battle_controllers.c)
// -----------------------------------------------------------------------------
void DrawMoveEffectivenessIndicator(u8 moveIndex, u8 targetBank)
{
    u16 move = gBattleMons[gBattlerAttacker].moves[moveIndex];
    u32 multiplier = GetTypeModifier(move, targetBank);

    if (multiplier == 0)
        SetMoveNameTextColor(COLOR_RED);       // No effect
    else if (multiplier < UQ_4_12(1.0))
        SetMoveNameTextColor(COLOR_YELLOW);    // Not very effective
    else if (multiplier > UQ_4_12(1.0))
        SetMoveNameTextColor(COLOR_GREEN);     // Super effective
    else
        SetMoveNameTextColor(COLOR_WHITE);     // Neutral
}
``` [cite: 19, 54, 61, 79].

---

## 6. Configuration & Metadata (The "Rules")
`#save_block_structure` `#checksum_validation` `#game_version_flags` `#difficulty_settings` `#global_config` `#build_pipeline`

```c
// -----------------------------------------------------------------------------
// DYNAMIC FLASH 1M SAVE SECTOR EXPANSION (include/config/save.h)
// -----------------------------------------------------------------------------
/*
 * Reclaims dead space and redistributes chunks across Flash 1M (128 KB)
 * Sectors 0-13: Slot 1 (Primary Save State)
 * Sectors 14-27: Slot 2 (Backup Save State)
 * Sectors 28-31: Dynamic Extended Sector Blocks (Flags, Quest Variables, PC)
 */
#define B_SAVE_EXPANSION                 TRUE
#define FREE_MYSTERY_GIFT                TRUE  // Reclaims 876 Bytes
#define FREE_TRAINER_HILL                TRUE  // Reclaims 28 Bytes
#define FREE_LINK_BATTLE_RECORDS         TRUE  // Reclaims 88 Bytes
#define FREE_EXTRA_SEEN_FLAGS_SAVEBLOCK1 TRUE  // Reclaims 52 Bytes
#define SKIP_SAVE_CONFIRMATION           TRUE

// -----------------------------------------------------------------------------
// EXTENDED SAVEBLOCK BITFIELDS (include/global.h)
// -----------------------------------------------------------------------------
struct SaveBlock2
{
    u8 playerName[PLAYER_NAME_LENGTH + 1];
    u8 playerGender;
    u8 specialSaveWarpFlags;
    u8 playTimeHours;
    u8 playTimeMinutes;
    u8 playTimeSeconds;
    u8 playTimeVBlanks;
    
    // Decoupled 24-Gym Badge Allocations
    u8 kantoBadges; // Boulder, Cascade, Thunder, Rainbow, Soul, Marsh, Volcano, Earth
    u8 johtoBadges; // Zephyr, Hive, Plain, Fog, Storm, Mineral, Glacier, Rising
    u8 hoennBadges; // Stone, Knuckle, Dynamo, Heat, Balance, Feather, Mind, Rain
    
    // Visited Map Bitfields (Supports 128 sections across 3 continents)
    u8 regionMapSectionsVisited;
};

// Compile-Time Boundary Assertions (src/load_save.c)
STATIC_ASSERT(sizeof(struct SaveBlock1) <= 0x3E80, SaveBlock1_Overflow_Error);
STATIC_ASSERT(sizeof(struct SaveBlock2) <= 0x0F24, SaveBlock2_Overflow_Error);
``` [cite: 43, 54, 55, 63, 72, 87].

```bash
# ==============================================================================
# AUTOMATED CONTINUOUS COMPILATION & AUDIT PIPELINE (Makefile)
# ==============================================================================
# Compile targets using parallel execution and automated static analysis:
make -j$(nproc)

# Execute spatial and RAM boundary oracles:
python3 tools/poke_audit_warps.py pokeconfluence.elf
tools/ram_check/ram_check pokeconfluence.elf
``` [cite: 60, 61, 62, 72].

---

This unified framework forms the architectural core linking the classic mechanics of Generation I–III with modern combat engines, multi-region open traversal, and automated decompilation workflows [cite: 46, 50, 70, 72].
