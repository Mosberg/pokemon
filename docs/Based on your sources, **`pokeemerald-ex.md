Based on your sources, **`pokeemerald-expansion`**, **`pokemultiregion`**, and **`pokeconfluence`** integrate an extensive suite of core mechanics, locations, items, and event systems originating in the Generation 1 (_Red_, _Blue_, _Yellow_, _FireRed_, _LeafGreen_) and Generation 2 (_Gold_, _Silver_, _Crystal_, _Heart & Soul_) games [cite: 46, 48, 62, 65, 70, 91, 94, 96, 134]:

---

### 1. Generation I In-Game Mechanics & Features Included

- **Full Kanto Geography & Map Hierarchy**:
  - Complete Kanto overworld routes and cities (Pallet Town, Viridian, Pewter, Cerulean, Vermilion, Lavender, Celadon, Fuchsia, Saffron, Cinnabar, and Indigo Plateau) [cite: 149, 150, 164, 170, 171, 172].
  - Interior dungeons and landmarks: Viridian Forest, Mt. Moon, Diglett's Cave, Rock Tunnel, Pokémon Tower, Rocket Hideout, Silph Co. headquarters, Pokémon Mansion, and Victory Road [cite: 62, 161, 164, 165, 169, 171, 172].
- **Sevii Islands Expansion (Islands 1–7)**:
  - Full inclusion of the Sevii Islands archipelago from _FireRed/LeafGreen_ accessible via the Seagallop Ferries with the Rainbow Pass [cite: 51, 96, 135, 161].
  - Island-specific landmarks like Mt. Ember and Tanoby Ruins (with chamber-dependent wild Unown spawns) [cite: 22, 169].
- **Authentic _Yellow_ & _FRLG_ Storyline Mechanics**:
  - **Partner Pikachu Mechanics**: Starter Pikachu that refuses to enter a Poké Ball, refuses Thunder Stone evolution triggers, and tracks mood and happiness [cite: 111, 128].
  - **Branching Rival Eevee Evolutions**: Rival Eevee evolution into Vaporeon, Jolteon, or Flareon determined by the outcomes of early-game battles in Oak's Lab and Route 22 [cite: 111].
  - **Gift Starters**: The original Kanto trio obtainable as in-game gifts (Bulbasaur in Cerulean with happiness check, Charmander on Route 24, and Squirtle from Officer Jenny in Vermilion) [cite: 32, 111].
  - **Jessie & James Encounters**: Scripted multi-battle encounters with Team Rocket's Jessie and James at Mt. Moon B2F, Rocket Hideout B4F, Pokémon Tower 7F, and Silph Co. 11F [cite: 111].
- **Classic Facilities & Minigames**:
  - **Kanto Safari Zone**: Original bait, rock, and Safari Ball capture mechanics [cite: 64, 90, 147].
  - **Celadon Game Corner**: Coin Case system and slot machine minigames with prize redemption counters [cite: 64, 108, 161].
  - **Cinnabar Island Fossil Lab**: Resurrection of prehistoric Pokémon from the Old Amber, Dome Fossil, and Helix Fossil [cite: 40, 164, 174, 177].
- **Kanto Badge Circuit & Decoupled Traversal**:
  - The 8 original Kanto Badges (Boulder, Cascade, Thunder, Rainbow, Soul, Marsh, Volcano, Earth) [cite: 112, 139].
  - Badge obedience thresholds and HM field moves (Cut, Flash, Surf, Strength) are decoupled from Hoenn milestones, enabling native Kanto badges to unlock field abilities and command obedience while in Kanto [cite: 96, 102, 103, 106, 112].

---

### 2. Generation II In-Game Mechanics & Features Included

- **Full Johto World & Landmark Infrastructure**:
  - Complete Johto topography from _Gold, Silver, and Crystal_ (New Bark Town, Cherrygrove, Violet City, Azalea Town, Goldenrod City, Ecruteak City, Olivine City, Cianwood City, Mahogany Town, Blackthorn City, and Mt. Silver) [cite: 68, 72, 91, 134, 149, 150, 163, 164, 166, 168].
  - Iconic Johto dungeons and sacred sites: Sprout Tower, Ruins of Alph, Slowpoke Well, Ilex Forest shrine, National Park, Burned Tower, Bell/Tin Tower, Whirl Islands, Lake of Rage, Dark Cave, Mt. Mortar, Ice Path, and Dragon's Den [cite: 46, 91, 131, 135, 165, 166, 169].
- **Day/Night System (DNS) & Real-Time Clock (RTC)**:
  - Hardware RTC time-tracking powering dynamic 24-hour overworld palette-tinting shaders (Dawn/Morning, Day, Dusk/Sunset, and Night) [cite: 20, 21, 46, 58, 90].
  - Time-dependent wild encounter tables (e.g. nocturnal species like Hoothoot and Spinarak appearing after dark) and time-gated evolutions (Espeon in day/AM hours, Umbreon at night/PM hours) [cite: 40, 46, 90, 138].
- **PokéGear & Radio Subsystems**:
  - Full PokéGear functionality featuring registered trainer phone contacts, rematch calls, and gift notifications [cite: 90, 91].
  - Radio Broadcast receiver with classic _Crystal_ radio channels (such as Professor Oak's Pokémon Talk, Pokémon March, Pokémon Lullaby, and the Hoenn Sound) [cite: 91, 92, 131].
  - Day of the Week progression scripts and Day-of-Week Siblings events [cite: 131, 165].
- **National Park Bug-Catching Contest**:
  - Dedicated contest scripting evaluating entered species, remaining HP, and IVs to compute custom prize scoring, complete with original Park Balls [cite: 46, 91, 131, 174, 177].
- **Kurt's Custom Apricorn Poké Balls**:
  - Gathering Apricorns (Red, Blue, Yellow, Green, White, Black, Pink) crafted by Kurt in Azalea Town into specialty Poké Balls: Level Ball, Lure Ball, Moon Ball, Friend Ball, Fast Ball, Heavy Ball, and Love Ball [cite: 91, 158, 159, 174, 175, 176, 177].
- **Johto Hold Items & Key Items**:
  - Classic Gen 2 evolution items and held battle items: Metal Coat, King's Rock, Dragon Scale, Up-Grade, Berserk Gene, Berry Juice, Thick Club, Stick/Leek, Light Ball, Cleanse Tag, Rainbow Wing, Silver Wing, and the GS Ball [cite: 131, 135, 158, 174, 175, 176, 177].
  - Modern trade evolution replacement items like the Link Cable (`ITEM_LINK_CABLE` / `linking_cord`) [cite: 31, 63, 135, 158, 159, 174].
- **Ruins of Alph Puzzle Chambers**:
  - Interactive Kabuto, Omanyte, Aerodactyl, and Ho-Oh slide tile puzzles that update room metatiles and expand wild Unown forms in the lower chambers [cite: 22, 46, 92, 131].
- **Breeding & Day Care Center**:
  - Route 34 Day Care infrastructure handling dual-parent Pokémon breeding, egg generation, species egg cycles, and hatching [cite: 77, 150, 165].
- **Independent Roaming Legendary Pokémon**:
  - Route-tracking roaming algorithms for Raikou, Entei, and Suicune that flee on turn 1, maintain current HP damage, and dynamically reposition across regional routes [cite: 70, 91, 131, 154].
- **Mom's Savings Account & Room Decoration**:
  - Post-battle prize money banking with Mom in New Bark Town, triggering random phone calls and delivery of rare items [cite: 91].
  - Player bedroom customization with Pokémon Dolls (Pikachu, Clefairy, Jigglypuff, big Lapras/Snorlax dolls) and elemental cushions [cite: 91, 173, 175, 177].
- **Inter-Regional Transit Networks**:
  - **S.S. Aqua / S.S. Anne**: Fast-ship ferry corridors linking Vermilion City Port, Olivine City Port, and Slateport/Lilycove [cite: 131, 135, 150, 167, 172].
  - **Magnet Train**: High-speed rail travel connecting Goldenrod Station and Saffron Station once the Kanto Power Plant crisis is resolved [cite: 131, 135, 168, 171, 172].
  - **Tohjo Falls & Route 27**: Overland/surf/waterfall border route connecting Johto and western Kanto [cite: 44, 131, 135].
  - **The Great Meridian Transit Line**: `pokeconfluence`'s deep-sea tectonic transit network providing direct, non-linear high-speed rail access between Kanto, Johto, and Hoenn [cite: 68, 70, 71, 126, 168].
- **Unified 24-Badge Circuit & Mt. Silver Summit**:
  - Complete 8-badge Johto league (Zephyr, Hive, Plain, Fog, Storm, Mineral, Glacier, Rising) integrated into an expanded 24-badge save architecture [cite: 72, 112, 126, 139].
  - Badges dynamically scale wild encounters and Gym Leader rosters across all three regions, leading to the endgame Apex Summit atop Mt. Silver [cite: 71, 72, 126, 134, 150].


---


An analysis of your sources, decompilations (*pokered*, *pokeyellow*, *pokegold*, *pokecrystal*, *pokefirered*, *pokeruby*, *pokeemerald*), and expanded bases (*pokeemerald-expansion*, *pokemultiregion*, *pokeconfluence*, *Heart & Soul*) reveals several authentic Generation 1 and Generation 2 features, rulesets, options, and configs that are **absent**, **overridden by Gen 3+ defaults**, or **omitted**:

---

### 1. Missing Generation 1 Core Mechanics & Quirks

#### A. Classic Gen 1 Combat Rulesets & Calculation Toggles
* **The "1-in-256" Accuracy Miss**: In Generation 1, 100% accurate moves still possessed a \\(\frac{1}{256}\\) (~0.39%) chance to miss due to a boundary check against an 8-bit random number generator [cite: 66, 67]. Modern decomp engines default to guaranteed hits [cite: 67].
* **Speed-Based Critical Hit Formula**: Gen 1 critical hit rates were directly proportional to a Pokémon’s base Speed stat rather than using tiered critical stages [cite: 66, 67]:
  \\[\text{Probability} = \frac{\text{BaseSpeed} \times 100}{512}\\]
  High-speed Pokémon (like Electrode, Jolteon, and Slash/Razor Leaf users) had near-guaranteed critical strikes [cite: 66].
* **Hyper Beam KO Exemption**: In Gen 1, if Hyper Beam successfully knocked out the opposing Pokémon, the required 1-turn recharge was skipped entirely [cite: 66, 67].
* **Trapping Moves Immobilization (Wrap, Bind, Fire Spin, Clamp)**: Gen 1 trapping attacks locked the target into complete immobility for 2–5 turns, preventing the opponent from executing any moves until the sequence concluded.
* **Stat Modification Stat Re-application Glitch**: In Gen 1, whenever a stat stage was modified in battle, any badge boosts or status debuffs (like Paralysis dropping Speed to \\(\frac{1}{4}\\) or Burn dropping Attack to \\(\frac{1}{2}\\)) were re-applied cumulatively to the current stats [cite: 21, 23].
* **Invulnerability to Residual Status**: In Gen 1, Pokémon could not be afflicted with Burn, Freeze, or Poison if they used a move of that corresponding type or were damaged by that move type.
* **100% Freeze Immobility**: Freezing in Gen 1 had no organic percentage chance to thaw out naturally over time; the Pokémon remained frozen indefinitely until hit by an enemy Fire attack or healed with an item.
* **Focus Energy Bug**: Focus Energy in Gen 1 mistakenly quartered the critical hit rate (\\(\times 0.25\\)) rather than quadrupling it (\\(\times 4\\)) [cite: 66, 67].

#### B. Generation 1 Game Systems & Menus
* **Stat System (Stat Experience vs. Modern EVs)**: Gen 1 (and 2) did not limit effort points to 510 total EVs capped at 252 per stat. Instead, Pokémon could max out Stat Experience across every individual stat simultaneously (\\(65.535\\) points per stat).
* **Combined "Special" Stat**: Gen 1 featured a unified Special stat governing both Special Attack and Special Defense simultaneously.
* **Enemy Infinite PP**: AI trainers in Gen 1 did not deplete PP when selecting moves, meaning opposing Pokémon never executed Struggle [cite: 66, 67].

---

### 2. Missing Generation 2 Core Mechanics & Features

#### A. Dedicated Subsystems & UI
* **PokéGear Card Interface**:
  * While the *pokeconfluence* map system integrates regional views, it uses Emerald's PokéNav [cite: 73, 75, 84]. The native Gen 2 PokéGear hardware interface—featuring the 4-card navigation bar (Clock, Town Map, Phone Book, and Tunable Radio frequency dial)—is replaced by Emerald's Start Menu and Pokénav layouts [cite: 71, 75].
  * **Manual Radio Frequency Tuning**: Dialing custom decimal frequencies (\\(0.0\\) to \\(20.0\\)) to pick up local regional broadcasts (e.g., Unown radio signals in Ruins of Alph, Route 205 broadcasts, or Poké Flute Channel on \\(20.0\\)).
* **Unown Dex & Research Report**:
  * In *Crystal*, capturing distinct Unown forms unlocked the interactive *Unown Report* key item, which logged forms, alphabetical letter chambers, and lore inscriptions in the Research Center [cite: 9, 43]. In vanilla Gen 3 engines, Unown forms exist strictly as visual PID calculations without the dedicated report booklet [cite: 9, 15].
* **Pokéathlon Dome & Minigames**:
  * *HeartGold/SoulSilver*'s athletic stadium with Touch/D-Pad minigames (Hurdle Dash, Relay Run, Block Smash, Ring Drop, Snow Throw) and Aprijuice stat-blending are omitted in decomp bases due to GBA hardware interface differences [cite: 72].

#### B. Battle Mechanics & Items
* **Gen 2 Critical Hit Damage (\\(2\times\\))**:
  * Gen 2 critical hits inflicted exactly \\(2.0\times\\) damage and calculated using Gen 2–5 stage tables, whereas modern expansion defaults use Gen 6+ (\\(1.5\times\\) damage) [cite: 23].
* **Thief / Covet Permanent Wild Stealing**:
  * In Gen 2, wild Pokémon using Thief on the player's Pokémon could permanently steal the player's held item unless recovered before ending the encounter.
* **Mystery Gift via Game Boy Color IR Sensor**:
  * Gen 2's optical infrared communication port used with Mary in Goldenrod City or other Game Boy Color consoles to deliver daily room decorations, dolls, and rare items.

---

### 3. Missing Options, Settings, and Flags

Decompilation frameworks like `Complete FireRed Upgrade` (CFRU) and `pokeemerald-expansion` include configurable header flags in `include/config/battle.h` and `include/config/overworld.h` that can restore these classic mechanics [cite: 4, 14, 21, 22, 23, 73, 83]:

| Configuration / Define Flag       | Default in Expansion Base                                  | Behavior if Restored to Gen 1/Gen 2 Classic                                                                                                     |
| :-------------------------------- | :--------------------------------------------------------- | :---------------------------------------------------------------------------------------------------------------------------------------------- |
| **`OLD_MOVE_SPLIT`**              | `FALSE` (Physical/Special Split active) [cite: 22, 47, 70] | Binds Physical/Special category strictly to elemental typing (Fire/Water/Grass = Special; Normal/Fighting/Rock = Physical) [cite: 22].          |
| **`BADGE_BOOSTS`**                | `FALSE` (No passive stat boosts) [cite: 23]                | Grants subtle passive \\(+12.5\%\\) boosts to specific stats in combat upon earning Gym Badges (e.g. Boulder Badge boosting Attack) [cite: 23]. |
| **`CRIT_CHANCE_GEN_2_TO_5`**      | `FALSE` (Uses Gen 6+ \\(4.17\%\\) base) [cite: 23]         | Restores Gen 2–5 critical hit calculation odds (\\(\frac{1}{16}\\) or \\(6.25\%\\) base rate) [cite: 23].                                       |
| **`OLD_CRIT_DAMAGE`**             | `FALSE` (\\(1.5\times\\) multiplier) [cite: 23]            | Sets critical hit damage multiplier back to \\(2.0\times\\) (and \\(3.0\times\\) with Sniper) [cite: 23].                                       |
| **`OLD_PARALYSIS_SPD_DROP`**      | `FALSE` (Halves Speed, Gen 7+) [cite: 21]                  | Reduces afflicted Pokémon's Speed to \\(\frac{1}{4}\\) (\\(75\%\\) drop) like Gen 1–6 [cite: 21].                                               |
| **`OLD_BURN_DAMAGE`**             | `FALSE` (\\(\frac{1}{16}\\) max HP drop) [cite: 21]        | Deals \\(\frac{1}{8}\\) max HP damage each turn as in Gen 1–6 [cite: 21].                                                                       |
| **`OLD_CONFUSION_CHANCE`**        | `FALSE` (\\(33\%\\) self-hit chance) [cite: 21]            | Restores the \\(50\%\\) chance to hit oneself in confusion [cite: 21].                                                                          |
| **`NO_POISON_IN_OW`**             | `TRUE` / Faints at 1 HP [cite: 18, 20]                     | Forces Pokémon to take 1 damage every 4 steps in the overworld until fainting (as in Gen 1–3) [cite: 18, 20].                                   |
| **`OBEDIENCE_CHECK_PLAYER_MONS`** | `FALSE` (Only traded Pokémon disobey) [cite: 27]           | Allows high-level Pokémon with your original Trainer ID (OT) to disobey if you lack the required badges [cite: 27].                             |
| **`GB_PLAYER_AUDIO_TOGGLE`**      | `FALSE` (Uses GBA MP2K sound engine) [cite: 71]            | Provides an in-game Key Item or option setting to toggle 8-bit chiptune soundfonts for music and sound effects [cite: 71].                      |

---
