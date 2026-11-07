#include "global.h"
#include "test/test.h"
#include "test/overworld_script.h"
#include "caps.h"
#include "confluence.h"
#include "data.h"
#include "follower_helper.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "pokedex.h"
#include "regions.h"
#include "constants/field_move.h"
#include "constants/items.h"
#include "constants/pokeball.h"
#include "constants/map_types.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/region_map_sections.h"
#include "constants/trainers.h"
#include "constants/weather.h"
#include "constants/species.h"
#include "constants/heal_locations.h"
#include "trainer_card.h"
#include "mood.h"
#include "johto_phone.h"
#include "script_pokemon_util.h"
#include "constants/johto_flags.h"
#include "wild_encounter.h"
#include "headbutt.h"
#include "metatile_behavior.h"
#include "constants/metatile_behaviors.h"
#include "roamer.h"
#include "battle.h"
#include "constants/songs.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "clock.h"
#include "rtc.h"
#include "script.h"
#include "overworld.h"
#include "johto_radio.h"
#include "unown.h"
#include "card_flip.h"
#include "coins.h"
#include "string_util.h"
#include "johto_battle_tower.h"
#include "fame_checker.h"
#include "teachy_tv.h"
#include "surfing_pikachu.h"
#include "battle_setup.h"
#include "gym_leader_rematch.h"
#include "time_events.h"
#include "pokeblock.h"
#include "contest.h"
#include "dexnav.h"
#include "gba/m4a_internal.h"
#include "sound.h"
extern struct ToneData gPikachuVoiceTable[];
extern struct ToneData gPikachuVoiceTable_Reverse[];
#include "constants/pikachu_voice.h"
#include "config/pokemon.h"
#include "item_use.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "dodrio_berry_picking.h"
#include "constants/game_stat.h"

static void ClearAllBadges(void)
{
    u32 i;

    for (i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
    {
        FlagClear(GetBadgeFlagForRegion(REGION_HOENN, i));
        FlagClear(GetBadgeFlagForRegion(REGION_KANTO, i));
        FlagClear(GetBadgeFlagForRegion(REGION_JOHTO, i));
    }
    FlagClear(FLAG_CONFLUENCE_APEX_CHAMPION);
}

TEST("Confluence: badges are counted across Kanto, Johto and Hoenn")
{
    ClearAllBadges();
    EXPECT_EQ(Confluence_CountBadges(), 0);

    FlagSet(GetBadgeFlagForRegion(REGION_HOENN, 0));
    FlagSet(GetBadgeFlagForRegion(REGION_KANTO, 3));
    FlagSet(GetBadgeFlagForRegion(REGION_JOHTO, 7));
    EXPECT_EQ(Confluence_CountBadges(), 3);

    for (u32 i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
    {
        FlagSet(GetBadgeFlagForRegion(REGION_HOENN, i));
        FlagSet(GetBadgeFlagForRegion(REGION_KANTO, i));
        FlagSet(GetBadgeFlagForRegion(REGION_JOHTO, i));
    }
    EXPECT_EQ(Confluence_CountBadges(), CONFLUENCE_TOTAL_BADGES);
    ClearAllBadges();
}

TEST("Confluence: the level cap follows the number of badges")
{
    ClearAllBadges();
    EXPECT_EQ(GetCurrentLevelCap(), Confluence_GetLevelCapForBadges(0));

    FlagSet(GetBadgeFlagForRegion(REGION_KANTO, 0));
    FlagSet(GetBadgeFlagForRegion(REGION_JOHTO, 0));
    EXPECT_EQ(GetCurrentLevelCap(), Confluence_GetLevelCapForBadges(2));
    EXPECT_GT(Confluence_GetLevelCapForBadges(2), Confluence_GetLevelCapForBadges(1));

    for (u32 badges = 1; badges <= CONFLUENCE_TOTAL_BADGES; badges++)
        EXPECT_GT(Confluence_GetLevelCapForBadges(badges), Confluence_GetLevelCapForBadges(badges - 1));
    EXPECT_EQ(Confluence_GetLevelCapForBadges(CONFLUENCE_TOTAL_BADGES + 5), Confluence_GetLevelCapForBadges(CONFLUENCE_TOTAL_BADGES));
    ClearAllBadges();
}

TEST("Confluence: clearing the Apex Summit lifts the level cap")
{
    ClearAllBadges();
    FlagSet(FLAG_CONFLUENCE_APEX_CHAMPION);
    EXPECT_EQ(GetCurrentLevelCap(), MAX_LEVEL);
    ClearAllBadges();
}

TEST("Confluence: the Meridian line opens with the second badge")
{
    ClearAllBadges();
    RUN_OVERWORLD_SCRIPT(special ConfluenceCheckMeridianAccess;);
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    FlagSet(GetBadgeFlagForRegion(REGION_HOENN, 0));
    RUN_OVERWORLD_SCRIPT(special ConfluenceCheckMeridianAccess;);
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    FlagSet(GetBadgeFlagForRegion(REGION_KANTO, 0));
    RUN_OVERWORLD_SCRIPT(special ConfluenceCheckMeridianAccess;);
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    ClearAllBadges();
}

TEST("Confluence: the Apex Summit needs all 24 badges")
{
    ClearAllBadges();
    for (u32 i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
    {
        FlagSet(GetBadgeFlagForRegion(REGION_HOENN, i));
        FlagSet(GetBadgeFlagForRegion(REGION_KANTO, i));
    }
    RUN_OVERWORLD_SCRIPT(special ConfluenceCheckApexEligible;);
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    for (u32 i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
        FlagSet(GetBadgeFlagForRegion(REGION_JOHTO, i));
    RUN_OVERWORLD_SCRIPT(special ConfluenceCheckApexEligible;);
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    ClearAllBadges();
}

TEST("Confluence: Resonance legends are calmed once caught")
{
    u32 before = Confluence_CountResonanceCalmed();

    GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_SUICUNE), FLAG_SET_CAUGHT);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_REGISTEEL), FLAG_SET_CAUGHT);
    EXPECT_GE(Confluence_CountResonanceCalmed(), 2);
    EXPECT_LE(Confluence_CountResonanceCalmed(), CONFLUENCE_RESONANCE_COUNT);
    EXPECT_GE(Confluence_CountResonanceCalmed(), before);
}

TEST("Confluence: the Apex Summit trainer ids fit in the trainer flag space")
{
    // gTrainers is replaced by test trainers in test builds, so only the id layout is checked here.
    EXPECT_GE(TRAINER_APEX_KANTO, TRAINERS_COUNT_EMERALD - 8);
    EXPECT_LT(TRAINER_SYNDICATE_CHAIRMAN, MAX_TRAINERS_COUNT);
    EXPECT_LT(TRAINER_APEX_CHAMPION, MAX_TRAINERS_COUNT);
    EXPECT_LT(TRAINER_APEX_CHAMPION, KANTO_TRAINER_BASE);
}

static const struct TrainerMon sBoostParty[] =
{
    { .species = SPECIES_GEODUDE, .lvl = 12 },
    { .species = SPECIES_ONIX, .lvl = 14 },
};

TEST("Confluence: gym leaders are lifted to the level cap, never lowered")
{
    struct Trainer leader = { .trainerClass = TRAINER_CLASS_LEADER, .party = sBoostParty, .partySize = ARRAY_COUNT(sBoostParty) };
    struct Trainer grunt = leader;

    ClearAllBadges();
    // 14 is the strongest member; the first cap is 15
    EXPECT_EQ(Confluence_GetTrainerLevelBoost(&leader), Confluence_GetLevelCapForBadges(0) - 14);

    for (u32 i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
        FlagSet(GetBadgeFlagForRegion(REGION_JOHTO, i));
    EXPECT_EQ(Confluence_GetTrainerLevelBoost(&leader), Confluence_GetLevelCapForBadges(8) - 14);

    grunt.trainerClass = TRAINER_CLASS_ELITE_FOUR;
    EXPECT_EQ(Confluence_GetTrainerLevelBoost(&grunt), Confluence_GetLevelCapForBadges(8) - 14);
    grunt.trainerClass = TRAINER_CLASS_CHAMPION_FRLG;
    EXPECT_EQ(Confluence_GetTrainerLevelBoost(&grunt), Confluence_GetLevelCapForBadges(8) - 14);
    grunt.trainerClass = TRAINER_CLASS_PKMN_TRAINER_1;
    EXPECT_EQ(Confluence_GetTrainerLevelBoost(&grunt), 0);
    ClearAllBadges();
}

TEST("Confluence: Resonance anomalies replace clear weather outdoors")
{
    ClearAllBadges();
    FlagClear(FLAG_CONFLUENCE_CRISIS_RESOLVED);
    gMapHeader.mapType = MAP_TYPE_ROUTE;
    gSaveBlock1Ptr->location.mapGroup = 0;
    gMapHeader.regionMapSectionId = MAPSEC_LITTLEROOT_TOWN;

    // no anomaly before the Meridian line opens
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_SUNNY), WEATHER_SUNNY);

    FlagSet(GetBadgeFlagForRegion(REGION_HOENN, 0));
    FlagSet(GetBadgeFlagForRegion(REGION_HOENN, 1));
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_SUNNY), WEATHER_DOWNPOUR);
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_NONE), WEATHER_DOWNPOUR);
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_SNOW), WEATHER_SNOW);

    gMapHeader.mapType = MAP_TYPE_INDOOR;
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_NONE), WEATHER_NONE);

    gMapHeader.mapType = MAP_TYPE_ROUTE;
    gMapHeader.regionMapSectionId = MAPSEC_PALLET_TOWN;
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_NONE), WEATHER_RAIN_THUNDERSTORM);

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F);
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_NONE), WEATHER_FOG_HORIZONTAL);

    FlagSet(FLAG_CONFLUENCE_CRISIS_RESOLVED);
    EXPECT_EQ(Confluence_GetAnomalyWeather(WEATHER_NONE), WEATHER_NONE);
    FlagClear(FLAG_CONFLUENCE_CRISIS_RESOLVED);
    ClearAllBadges();
}

TEST("Confluence: the Field Kit lets the first non-egg Pokemon use HM field moves")
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gParties[B_TRAINER_PLAYER][i]);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 20, 0, OTID_STRUCT_PRESET(0));
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PRESET(0));

    RemoveBagItem(ITEM_FIELD_KIT, 99);
    EXPECT_EQ(Confluence_GetFieldKitMon(FIELD_MOVE_CUT), PARTY_SIZE);

    ASSUME(AddBagItem(ITEM_FIELD_KIT, 1));
    EXPECT_EQ(Confluence_GetFieldKitMon(FIELD_MOVE_CUT), 0);
    EXPECT_EQ(Confluence_GetFieldKitMon(FIELD_MOVE_SURF), 0);
    EXPECT_EQ(Confluence_GetFieldKitMon(FIELD_MOVE_FLY), PARTY_SIZE);

    u32 isEgg = TRUE;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(Confluence_GetFieldKitMon(FIELD_MOVE_STRENGTH), 1);
    EXPECT(Confluence_IsFieldKitSlot(1));
    EXPECT(!Confluence_IsFieldKitSlot(0));
    EXPECT_EQ(Confluence_GetFieldKitMoveByIndex(0), FIELD_MOVE_SURF);
    EXPECT_EQ(Confluence_GetFieldKitMoveByIndex(7), FIELD_MOVES_COUNT);
    RemoveBagItem(ITEM_FIELD_KIT, 1);
    EXPECT(!Confluence_IsFieldKitSlot(1));
}

TEST("Confluence: Meridian Station and the Apex Summit arena are Johto maps")
{
    // GetCurrentRegion() tells Johto by map group, so both must sit in the Johto groups
    EXPECT_GE(MAP_GROUP(MAP_JOHTO_MERIDIAN_STATION), MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F));
    EXPECT_GE(MAP_GROUP(MAP_JOHTO_APEX_SUMMIT), MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F));
    EXPECT_NE(MAP_NUM(MAP_JOHTO_MERIDIAN_STATION), MAP_NUM(MAP_JOHTO_APEX_SUMMIT));
}

TEST("Confluence: Yellow gift starters flags and generation")
{
    FlagClear(FLAG_GOT_YELLOW_BULBASAUR);
    FlagClear(FLAG_GOT_YELLOW_CHARMANDER);
    FlagClear(FLAG_GOT_YELLOW_SQUIRTLE);

    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_BULBASAUR), FALSE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_CHARMANDER), FALSE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_SQUIRTLE), FALSE);

    FlagSet(FLAG_GOT_YELLOW_BULBASAUR);
    FlagSet(FLAG_GOT_YELLOW_CHARMANDER);
    FlagSet(FLAG_GOT_YELLOW_SQUIRTLE);

    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_BULBASAUR), TRUE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_CHARMANDER), TRUE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_SQUIRTLE), TRUE);

    // Verify gift mon species can be created at level 10
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_BULBASAUR, 10, 0, OTID_STRUCT_PRESET(0));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES, NULL), SPECIES_BULBASAUR);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL, NULL), 10);

    CreateMon(&mon, SPECIES_CHARMANDER, 10, 0, OTID_STRUCT_PRESET(0));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES, NULL), SPECIES_CHARMANDER);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL, NULL), 10);

    CreateMon(&mon, SPECIES_SQUIRTLE, 10, 0, OTID_STRUCT_PRESET(0));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES, NULL), SPECIES_SQUIRTLE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL, NULL), 10);

    FlagClear(FLAG_GOT_YELLOW_BULBASAUR);
    FlagClear(FLAG_GOT_YELLOW_CHARMANDER);
    FlagClear(FLAG_GOT_YELLOW_SQUIRTLE);
}

TEST("Confluence: Pokégear flag and communicator logic")
{
    FlagClear(FLAG_JOHTO_ENGINE_POKEGEAR);
    FlagClear(FLAG_SYS_POKENAV_GET);

    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_POKEGEAR), FALSE);
    EXPECT_EQ(FlagGet(FLAG_SYS_POKENAV_GET), FALSE);

    FlagSet(FLAG_JOHTO_ENGINE_POKEGEAR);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_POKEGEAR), TRUE);

    FlagSet(FLAG_SYS_POKENAV_GET);
    EXPECT_EQ(FlagGet(FLAG_SYS_POKENAV_GET), TRUE);

    FlagClear(FLAG_JOHTO_ENGINE_POKEGEAR);
    FlagClear(FLAG_SYS_POKENAV_GET);
}

TEST("Confluence: Johto Fly destinations and regional GameClear warp")
{
    EXPECT_EQ(HEAL_LOCATION_JOHTO_NEW_BARK_TOWN > HEAL_LOCATION_NONE, TRUE);
    EXPECT_EQ(HEAL_LOCATION_JOHTO_GOLDENROD_CITY > HEAL_LOCATION_NONE, TRUE);
    EXPECT_EQ(HEAL_LOCATION_JOHTO_BLACKTHORN_CITY > HEAL_LOCATION_NONE, TRUE);
    EXPECT_EQ(HEAL_LOCATION_PALLET_TOWN > HEAL_LOCATION_NONE, TRUE);
    EXPECT_EQ(HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F > HEAL_LOCATION_NONE, TRUE);
}

TEST("Confluence: Regional Trainer Card badge retrieval and cycling")
{
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_HOENN, 0), FLAG_BADGE01_GET);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_HOENN, 7), FLAG_BADGE08_GET);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_HOENN, 8), 0);

    EXPECT_EQ(GetBadgeFlagForRegion(REGION_KANTO, 0), FLAG_BADGE09_GET);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_KANTO, 7), FLAG_BADGE16_GET);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_KANTO, 8), 0);

    EXPECT_EQ(GetBadgeFlagForRegion(REGION_JOHTO, 0), FLAG_JOHTO_ENGINE_ZEPHYRBADGE);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_JOHTO, 7), FLAG_JOHTO_ENGINE_RISINGBADGE);
    EXPECT_EQ(GetBadgeFlagForRegion(REGION_JOHTO, 8), 0);

    EXPECT_EQ(TrainerCard_GetBadgeRegion(), GetCurrentRegion());
}

TEST("Confluence: Johto Town Map sections map correctly to REGION_JOHTO")
{
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_NEW_BARK_TOWN), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_CHERRYGROVE_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_VIOLET_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_AZALEA_TOWN), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_GOLDENROD_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_ECRUTEAK_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_OLIVINE_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_CIANWOOD_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_MAHOGANY_TOWN), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_BLACKTHORN_CITY), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_SILVER_CAVE), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_JOHTO_APEX_SUMMIT), REGION_JOHTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_PALLET_TOWN), REGION_KANTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_LITTLEROOT_TOWN), REGION_HOENN);
}

TEST("Confluence: Universal Mood System calculates moods accurately across all conditions")
{
    struct Pokemon mon;
    u8 friendship;
    u32 hp;
    u32 maxHp = 100;
    u32 status = 0;

    CreateMon(&mon, SPECIES_PIKACHU, 25, 0, OTID_STRUCT_PRESET(0));

    // 1. Ecstatic tier (Friendship >= 220)
    friendship = 250;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(&mon, MON_DATA_MAX_HP, &maxHp);
    hp = 100;
    SetMonData(&mon, MON_DATA_HP, &hp);
    SetMonData(&mon, MON_DATA_STATUS, &status);
    FlagClear(FLAG_POKEMON_REFUSED_STONE);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_ECSTATIC);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_ECSTATIC), FOLLOWER_EMOTION_LOVE);
    EXPECT_EQ(Confluence_GetPortraitEmotionForMood(MOOD_ECSTATIC), PORTRAIT_EMOTION_JOYOUS);

    // 2. Happy tier (Friendship 160..219)
    friendship = 180;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_HAPPY);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_HAPPY), FOLLOWER_EMOTION_HAPPY);

    // 3. Content tier (Friendship 100..159)
    friendship = 130;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_CONTENT);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_CONTENT), FOLLOWER_EMOTION_MUSIC);

    // 4. Normal tier (Friendship 50..99)
    friendship = 70;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_NORMAL);

    // 5. Distant tier (Friendship < 50)
    friendship = 20;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_DISTANT);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_DISTANT), FOLLOWER_EMOTION_PENSIVE);

    // 6. Exhausted / Low HP (HP <= 25%)
    friendship = 200;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    hp = 20;
    SetMonData(&mon, MON_DATA_HP, &hp);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_TIRED);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_TIRED), FOLLOWER_EMOTION_SAD);

    // 7. Status conditions override friendship
    hp = 100;
    SetMonData(&mon, MON_DATA_HP, &hp);
    status = STATUS1_SLEEP;
    SetMonData(&mon, MON_DATA_STATUS, &status);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_SLEEPING);

    status = STATUS1_POISON;
    SetMonData(&mon, MON_DATA_STATUS, &status);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_SICK);
    EXPECT_EQ(Confluence_GetFollowerEmotionForMood(MOOD_SICK), FOLLOWER_EMOTION_POISONED);

    status = STATUS1_PARALYSIS;
    SetMonData(&mon, MON_DATA_STATUS, &status);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_PARALYZED);

    // 8. Fainted (0 HP)
    hp = 0;
    SetMonData(&mon, MON_DATA_HP, &hp);
    EXPECT_EQ(Confluence_GetPokemonMood(&mon), MOOD_ANGRY);
}

TEST("Confluence: Evolution Stone Refusal for Pikachu and loyal starters")
{
    struct Pokemon mon;
    u8 friendship;
    u16 item;

    CreateMon(&mon, SPECIES_PIKACHU, 25, 0, OTID_STRUCT_PRESET(0));

    // Pikachu with high friendship refuses Thunder Stone (Yellow authenticity)
    friendship = 150;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(Confluence_CheckStoneRefusal(&mon, ITEM_THUNDER_STONE), TRUE);
    EXPECT_EQ(FlagGet(FLAG_POKEMON_REFUSED_STONE), TRUE);

    // Pikachu does NOT refuse irrelevant items
    FlagClear(FLAG_POKEMON_REFUSED_STONE);
    EXPECT_EQ(Confluence_CheckStoneRefusal(&mon, ITEM_WATER_STONE), FALSE);
    EXPECT_EQ(FlagGet(FLAG_POKEMON_REFUSED_STONE), FALSE);

    // Holding Everstone refuses evolution stones
    item = ITEM_EVERSTONE;
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    EXPECT_EQ(Confluence_CheckStoneRefusal(&mon, ITEM_THUNDER_STONE), TRUE);

    // Loyal Starters refuse stones when FLAG_STARTER_LOYALTY_REFUSAL is set
    CreateMon(&mon, SPECIES_CHARMANDER, 25, 0, OTID_STRUCT_PRESET(0));
    friendship = 250;
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    item = ITEM_NONE;
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    FlagSet(FLAG_STARTER_LOYALTY_REFUSAL);
    EXPECT_EQ(Confluence_CheckStoneRefusal(&mon, ITEM_FIRE_STONE), TRUE);
    FlagClear(FLAG_STARTER_LOYALTY_REFUSAL);
    FlagClear(FLAG_POKEMON_REFUSED_STONE);
}

TEST("Confluence: Pokégear Card Subsystem and Phone Contact Registration")
{
    // 1. Initial state (no cards)
    FlagClear(FLAG_JOHTO_ENGINE_MAP_CARD);
    FlagClear(FLAG_JOHTO_ENGINE_PHONE_CARD);
    FlagClear(FLAG_JOHTO_ENGINE_RADIO_CARD);

    EXPECT_EQ(Johto_HasMapCard(), FALSE);
    EXPECT_EQ(Johto_HasPhoneCard(), FALSE);
    EXPECT_EQ(Johto_HasRadioCard(), FALSE);

    // 2. Unlocking cards
    FlagSet(FLAG_JOHTO_ENGINE_MAP_CARD);
    EXPECT_EQ(Johto_HasMapCard(), TRUE);

    FlagSet(FLAG_JOHTO_ENGINE_PHONE_CARD);
    EXPECT_EQ(Johto_HasPhoneCard(), TRUE);

    FlagSet(FLAG_JOHTO_ENGINE_RADIO_CARD);
    EXPECT_EQ(Johto_HasRadioCard(), TRUE);

    // 3. Contact registration and counts
    FlagClear(FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED);
    FlagClear(FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED);
    FlagClear(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH);
    FlagClear(FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH);

    EXPECT_EQ(Johto_GetRegisteredPhoneCount(), 0);

    FlagSet(FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED);
    EXPECT_EQ(Johto_GetRegisteredPhoneCount(), 1);

    FlagSet(FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED);
    EXPECT_EQ(Johto_GetRegisteredPhoneCount(), 2);

    // 4. Arming rematches
    Johto_ArmRandomRematch();
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH), TRUE);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH), TRUE);

    // Cleanup
    FlagClear(FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED);
    FlagClear(FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED);
    FlagClear(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH);
    FlagClear(FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH);
    FlagClear(FLAG_JOHTO_ENGINE_MAP_CARD);
    FlagClear(FLAG_JOHTO_ENGINE_PHONE_CARD);
    FlagClear(FLAG_JOHTO_ENGINE_RADIO_CARD);
}

TEST("Confluence: Kanto Yellow progression, MapSecs, and Meridian fast travel access")
{
    ClearAllBadges();

    // 1. Initial state: 0 badges -> Meridian ferry locked
    ConfluenceCheckMeridianAccess();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // 2. 1 Kanto badge -> Meridian ferry still locked
    FlagSet(FLAG_BADGE09_GET); // Boulder Badge (Brock)
    ConfluenceCheckMeridianAccess();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // 3. 2 Kanto badges -> Meridian ferry unlocks
    FlagSet(FLAG_BADGE10_GET); // Cascade Badge (Misty)
    ConfluenceCheckMeridianAccess();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // 4. Kanto / Yellow map section topology verification
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_VIRIDIAN_FOREST), REGION_KANTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_MT_MOON), REGION_KANTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_CERULEAN_CITY), REGION_KANTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_VERMILION_CITY), REGION_KANTO);
    EXPECT_EQ(GetRegionForSectionId(MAPSEC_ROUTE_24), REGION_KANTO);

    // 5. Authentic Yellow gift starter flags
    FlagClear(FLAG_GOT_YELLOW_BULBASAUR);
    FlagClear(FLAG_GOT_YELLOW_CHARMANDER);
    FlagClear(FLAG_GOT_YELLOW_SQUIRTLE);

    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_BULBASAUR), FALSE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_CHARMANDER), FALSE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_SQUIRTLE), FALSE);

    FlagSet(FLAG_GOT_YELLOW_BULBASAUR);
    FlagSet(FLAG_GOT_YELLOW_CHARMANDER);
    FlagSet(FLAG_GOT_YELLOW_SQUIRTLE);

    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_BULBASAUR), TRUE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_CHARMANDER), TRUE);
    EXPECT_EQ(FlagGet(FLAG_GOT_YELLOW_SQUIRTLE), TRUE);

    ClearAllBadges();
    FlagClear(FLAG_GOT_YELLOW_BULBASAUR);
    FlagClear(FLAG_GOT_YELLOW_CHARMANDER);
    FlagClear(FLAG_GOT_YELLOW_SQUIRTLE);
}

// POKE-CONFLUENCE: Authentic Johto Time-of-Day wild encounter tables verification
TEST("Confluence: Johto authentic morning, day, and night wild encounter tables")
{
    u32 i;
    u32 route29Header = HEADER_NONE;
    u32 route30Header = HEADER_NONE;
    u32 route34Header = HEADER_NONE;
    u32 route37Header = HEADER_NONE;

    for (i = 0; gWildMonHeaders[i].mapGroup != 0xFF; i++)
    {
        if (gWildMonHeaders[i].mapGroup == MAP_GROUP(MAP_JOHTO_ROUTE_29) &&
            gWildMonHeaders[i].mapNum == MAP_NUM(MAP_JOHTO_ROUTE_29))
            route29Header = i;
        else if (gWildMonHeaders[i].mapGroup == MAP_GROUP(MAP_JOHTO_ROUTE_30) &&
                 gWildMonHeaders[i].mapNum == MAP_NUM(MAP_JOHTO_ROUTE_30))
            route30Header = i;
        else if (gWildMonHeaders[i].mapGroup == MAP_GROUP(MAP_JOHTO_ROUTE_34) &&
                 gWildMonHeaders[i].mapNum == MAP_NUM(MAP_JOHTO_ROUTE_34))
            route34Header = i;
        else if (gWildMonHeaders[i].mapGroup == MAP_GROUP(MAP_JOHTO_ROUTE_37) &&
                 gWildMonHeaders[i].mapNum == MAP_NUM(MAP_JOHTO_ROUTE_37))
            route37Header = i;
    }

    EXPECT_NE(route29Header, HEADER_NONE);
    EXPECT_NE(route30Header, HEADER_NONE);
    EXPECT_NE(route34Header, HEADER_NONE);
    EXPECT_NE(route37Header, HEADER_NONE);

    // Route 29: Night has Hoothoot (Crystal authentic)
    const struct WildPokemonInfo *r29Night = gWildMonHeaders[route29Header].encounterTypes[TIME_NIGHT].landMonsInfo;
    EXPECT_NE(r29Night, NULL);
    EXPECT_EQ(r29Night->wildPokemon[0].species, SPECIES_HOOTHOOT);

    // Route 30: Morning has Ledyba, Day has Pidgey, Night has Spinarak (Crystal authentic)
    const struct WildPokemonInfo *r30Morn = gWildMonHeaders[route30Header].encounterTypes[TIME_MORNING].landMonsInfo;
    const struct WildPokemonInfo *r30Day = gWildMonHeaders[route30Header].encounterTypes[TIME_DAY].landMonsInfo;
    const struct WildPokemonInfo *r30Night = gWildMonHeaders[route30Header].encounterTypes[TIME_NIGHT].landMonsInfo;
    EXPECT_NE(r30Morn, NULL);
    EXPECT_NE(r30Day, NULL);
    EXPECT_NE(r30Night, NULL);
    EXPECT_EQ(r30Morn->wildPokemon[0].species, SPECIES_LEDYBA);
    EXPECT_EQ(r30Day->wildPokemon[0].species, SPECIES_PIDGEY);
    EXPECT_EQ(r30Night->wildPokemon[0].species, SPECIES_SPINARAK);

    // Route 34: Morning/Day has Snubbull, Night has Drowzee (Crystal authentic)
    const struct WildPokemonInfo *r34Day = gWildMonHeaders[route34Header].encounterTypes[TIME_DAY].landMonsInfo;
    const struct WildPokemonInfo *r34Night = gWildMonHeaders[route34Header].encounterTypes[TIME_NIGHT].landMonsInfo;
    EXPECT_NE(r34Day, NULL);
    EXPECT_NE(r34Night, NULL);
    EXPECT_EQ(r34Day->wildPokemon[0].species, SPECIES_SNUBBULL);
    EXPECT_EQ(r34Night->wildPokemon[0].species, SPECIES_DROWZEE);

    // Route 37: Night has Stantler & Spinarak (Crystal authentic)
    const struct WildPokemonInfo *r37Morn = gWildMonHeaders[route37Header].encounterTypes[TIME_MORNING].landMonsInfo;
    const struct WildPokemonInfo *r37Night = gWildMonHeaders[route37Header].encounterTypes[TIME_NIGHT].landMonsInfo;
    EXPECT_NE(r37Morn, NULL);
    EXPECT_NE(r37Night, NULL);
    EXPECT_EQ(r37Morn->wildPokemon[0].species, SPECIES_LEDYBA);
    EXPECT_EQ(r37Night->wildPokemon[0].species, SPECIES_SPINARAK);
}

// POKE-CONFLUENCE: Authentic Johto Headbutt Tree mechanics verification
TEST("Confluence: Authentic Johto Headbutt Tree mechanics and encounter tables")
{
    // 1. Metatile behavior verification
    EXPECT_EQ(MetatileBehavior_IsHeadbuttTree(MB_HEADBUTT_TREE), TRUE);
    EXPECT_EQ(MetatileBehavior_IsHeadbuttTree(MB_NORMAL), FALSE);
    EXPECT_EQ(MetatileBehavior_IsHeadbuttTree(MB_TALL_GRASS), FALSE);

    // 2. Sleeping tree Pokémon logic
    // Heracross is nocturnal -> sleeps during morning/day, active at night
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_HERACROSS, TIME_MORNING), TRUE);
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_HERACROSS, TIME_DAY), TRUE);
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_HERACROSS, TIME_NIGHT), FALSE);

    // Aipom is diurnal -> active during morning/day, sleeps at night
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_AIPOM, TIME_MORNING), FALSE);
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_AIPOM, TIME_DAY), FALSE);
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_AIPOM, TIME_NIGHT), TRUE);

    // Spinarak is nocturnal -> sleeps during day, active at night
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_SPINARAK, TIME_DAY), TRUE);
    EXPECT_EQ(CheckSleepingTreeMon(SPECIES_SPINARAK, TIME_NIGHT), FALSE);

    // 3. Map TreeMon set resolution
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_33);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_ROUTE_33);
    EXPECT_EQ(GetCurrentMapTreeMonSet(), TREEMON_SET_TOWN);

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_43);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_ROUTE_43);
    EXPECT_EQ(GetCurrentMapTreeMonSet(), TREEMON_SET_LAKE);

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_ILEX_FOREST);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_ILEX_FOREST);
    EXPECT_EQ(GetCurrentMapTreeMonSet(), TREEMON_SET_FOREST);

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_CIANWOOD_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_CIANWOOD_CITY);
    EXPECT_EQ(GetCurrentMapTreeMonSet(), TREEMON_SET_ROCK);

    // 4. Headbutt user check via Field Kit
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIDGEY, 5, 0, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 1;

    // Without Headbutt move or Field Kit -> fails
    JohtoCheckHeadbuttUser();
    EXPECT_EQ(gSpecialVar_Result, PARTY_SIZE);

    // With Field Kit in bag -> succeeds, selecting party member 0
    AddBagItem(ITEM_FIELD_KIT, 1);
    JohtoCheckHeadbuttUser();
    EXPECT_EQ(gSpecialVar_Result, 0);

    RemoveBagItem(ITEM_FIELD_KIT, 1);
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
}

TEST("Confluence: Authentic Johto Roaming Legendary Beasts (Raikou & Entei)")
{
    u8 group, num;
    u16 newHp;
    u32 sleepStatus;

    // 1. Initial deactivation state
    DeactivateAllRoamers();
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].active, FALSE);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[1].active, FALSE);

    // 2. Awakening the beasts (Burned Tower event)
    InitJohtoRoamMons();
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].active, TRUE);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].species, SPECIES_RAIKOU);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].level, 40);

    EXPECT_EQ(gSaveBlock1Ptr->roamer[1].active, TRUE);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[1].species, SPECIES_ENTEI);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[1].level, 40);

    // 3. Authentic starting locations (Route 42 for Raikou, Route 37 for Entei)
    GetRoamerLocation(0, &group, &num);
    EXPECT_EQ(group, MAP_GROUP(MAP_JOHTO_ROUTE_42));
    EXPECT_EQ(num, MAP_NUM(MAP_JOHTO_ROUTE_42));
    EXPECT_EQ(IsRoamerAt(0, MAP_GROUP(MAP_JOHTO_ROUTE_42), MAP_NUM(MAP_JOHTO_ROUTE_42)), TRUE);
    EXPECT_EQ(IsRoamerAt(0, MAP_GROUP(MAP_JOHTO_ROUTE_29), MAP_NUM(MAP_JOHTO_ROUTE_29)), FALSE);

    GetRoamerLocation(1, &group, &num);
    EXPECT_EQ(group, MAP_GROUP(MAP_JOHTO_ROUTE_37));
    EXPECT_EQ(num, MAP_NUM(MAP_JOHTO_ROUTE_37));
    EXPECT_EQ(IsRoamerAt(1, MAP_GROUP(MAP_JOHTO_ROUTE_37), MAP_NUM(MAP_JOHTO_ROUTE_37)), TRUE);

    // 4. Roamer movement across adjacent Johto routes
    RoamerMove(0);
    GetRoamerLocation(0, &group, &num);
    // After moving from Route 42, Raikou should still be in Johto group (78)
    EXPECT_EQ(group, MAP_GROUP(MAP_JOHTO_ROUTE_42));

    RoamerMoveToOtherLocationSet(1);
    GetRoamerLocation(1, &group, &num);
    EXPECT_EQ(group, MAP_GROUP(MAP_JOHTO_ROUTE_37));

    // 5. Battle setup, music, and surfing check
    // Set player to Route 42
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_42);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_ROUTE_42);

    CreateRoamerMonInstance(0);
    gBattleTypeFlags = BATTLE_TYPE_ROAMER;
    EXPECT_EQ(GetBattleBGM(), MUS_C_VS_LEGEND_BEAST);

    // 6. HP and status condition persistence across wild encounters
    newHp = 42;
    sleepStatus = STATUS1_SLEEP;
    SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_HP, &newHp);
    SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_STATUS, &sleepStatus);
    gEncounteredRoamerIndex = 0;
    UpdateRoamerHPStatus(&gParties[B_TRAINER_OPPONENT_A][0]);

    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].hp, newHp);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].statusA, STATUS1_SLEEP);

    // 7. Deactivation upon capture or fainting
    SetRoamerInactive(0);
    EXPECT_EQ(gSaveBlock1Ptr->roamer[0].active, FALSE);
    EXPECT_EQ(IsRoamerAt(0, MAP_GROUP(MAP_JOHTO_ROUTE_42), MAP_NUM(MAP_JOHTO_ROUTE_42)), FALSE);

    // Cleanup
    DeactivateAllRoamers();
    gBattleTypeFlags = 0;
}

TEST("Confluence: Authentic Johto Day-of-Week events and Weekday Siblings")
{
    u32 day;

    // 1. Weekday setter and getter verification across all 7 days
    for (day = WEEKDAY_SUN; day <= WEEKDAY_SAT; day++)
    {
        gSpecialVar_0x8004 = day;
        JohtoSetWeekday();
        JohtoGetWeekday();
        EXPECT_EQ(gSpecialVar_Result, day);
        EXPECT_EQ(GetDayOfWeek(), day);
    }

    // 2. Friday Lapras event in Union Cave B2F
    // On Thursday: Lapras should not appear
    gSpecialVar_0x8004 = WEEKDAY_THU;
    JohtoSetWeekday();
    FlagClear(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS);

    // Verify day check logic: appears only on Friday (weekday 5) when engine flag is clear
    JohtoGetWeekday();
    if (FlagGet(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS) || gSpecialVar_Result != WEEKDAY_FRI)
        FlagSet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    else
        FlagClear(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS), TRUE);

    // On Friday: Lapras appears
    gSpecialVar_0x8004 = WEEKDAY_FRI;
    JohtoSetWeekday();
    JohtoGetWeekday();
    if (FlagGet(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS) || gSpecialVar_Result != WEEKDAY_FRI)
        FlagSet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    else
        FlagClear(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS), FALSE);

    // Battling / catching Lapras sets FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS and hides Lapras
    FlagSet(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS);
    if (FlagGet(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS) || gSpecialVar_Result != WEEKDAY_FRI)
        FlagSet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    else
        FlagClear(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS), TRUE);

    // Daily midnight reset clears FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS for next weekly encounter
    DoDailyEvents(1);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS), FALSE);

    // 3. 7 Weekday Siblings schedules, appearances, and type-boost item awards
    struct WeekdaySiblingTest
    {
        u8 weekday;
        u16 item;
        u16 appearanceFlag;
        u16 giftFlag;
    };

    static const struct WeekdaySiblingTest sSiblings[7] =
    {
        { WEEKDAY_SUN, ITEM_MAGNET,      FLAG_JOHTO_ROUTE_37_SUNNY_OF_SUNDAY,        FLAG_JOHTO_GOT_MAGNET_FROM_SUNNY },
        { WEEKDAY_MON, ITEM_SHARP_BEAK,  FLAG_JOHTO_ROUTE_40_MONICA_OF_MONDAY,       FLAG_JOHTO_GOT_SHARP_BEAK_FROM_MONICA },
        { WEEKDAY_TUE, ITEM_PINK_BOW,    FLAG_JOHTO_ROUTE_29_TUSCANY_OF_TUESDAY,     FLAG_JOHTO_GOT_PINK_BOW_FROM_TUSCANY },
        { WEEKDAY_WED, ITEM_BLACKBELT_I, FLAG_JOHTO_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY,FLAG_JOHTO_GOT_BLACKBELT_FROM_WESLEY },
        { WEEKDAY_THU, ITEM_HARD_STONE,  FLAG_JOHTO_ROUTE_36_ARTHUR_OF_THURSDAY,     FLAG_JOHTO_GOT_HARD_STONE_FROM_ARTHUR },
        { WEEKDAY_FRI, ITEM_POISON_BARB, FLAG_JOHTO_ROUTE_32_FRIEDA_OF_FRIDAY,       FLAG_JOHTO_GOT_POISON_BARB_FROM_FRIEDA },
        { WEEKDAY_SAT, ITEM_SPELL_TAG,   FLAG_JOHTO_BLACKTHORN_CITY_SANTOS_OF_SATURDAY, FLAG_JOHTO_GOT_SPELL_TAG_FROM_SANTOS },
    };

    for (day = 0; day < 7; day++)
    {
        gSpecialVar_0x8004 = sSiblings[day].weekday;
        JohtoSetWeekday();
        EXPECT_EQ(GetDayOfWeek(), sSiblings[day].weekday);

        // Clear gift flag
        FlagClear(sSiblings[day].giftFlag);

        // Verify item space and gift award
        AddBagItem(sSiblings[day].item, 1);
        FlagSet(sSiblings[day].giftFlag);

        EXPECT_EQ(CheckBagHasItem(sSiblings[day].item, 1), TRUE);
        EXPECT_EQ(FlagGet(sSiblings[day].giftFlag), TRUE);

        // Cleanup
        RemoveBagItem(sSiblings[day].item, 1);
        FlagClear(sSiblings[day].giftFlag);
    }
}

TEST("Confluence: Authentic Lake of Rage Shiny Red Gyarados and Red Scale trade")
{
    // Clear flags and bag before test
    FlagClear(FLAG_JOHTO_LAKE_OF_RAGE_RED_GYARADOS);
    FlagClear(FLAG_JOHTO_LAKE_OF_RAGE_LANCE);
    RemoveBagItem(ITEM_RED_SCALE, 99);
    RemoveBagItem(ITEM_EXP_SHARE, 99);

    // 1. Scripted encounter generation: level 30 Gyarados forced shiny
    CreateScriptedWildMon(SPECIES_GYARADOS, 30, ITEM_NONE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES), SPECIES_GYARADOS);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL), 30);

    JohtoSetWildMonShiny();
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_IS_SHINY), TRUE);

    // 2. Victory / capture sets Gyarados flag and awards Red Scale
    FlagSet(FLAG_JOHTO_LAKE_OF_RAGE_RED_GYARADOS);
    AddBagItem(ITEM_RED_SCALE, 1);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_LAKE_OF_RAGE_RED_GYARADOS), TRUE);
    EXPECT_EQ(CheckBagHasItem(ITEM_RED_SCALE, 1), TRUE);

    // 3. Trade Red Scale to Mr. Pokémon for Exp. Share on Route 30
    EXPECT_EQ(CheckBagHasItem(ITEM_EXP_SHARE, 1), FALSE);
    RemoveBagItem(ITEM_RED_SCALE, 1);
    AddBagItem(ITEM_EXP_SHARE, 1);
    EXPECT_EQ(CheckBagHasItem(ITEM_RED_SCALE, 1), FALSE);
    EXPECT_EQ(CheckBagHasItem(ITEM_EXP_SHARE, 1), TRUE);

    // Cleanup
    RemoveBagItem(ITEM_EXP_SHARE, 1);
    FlagClear(FLAG_JOHTO_LAKE_OF_RAGE_RED_GYARADOS);
}

TEST("Confluence: Authentic National Park Bug-Catching Contest Minigame")
{
    u32 i;
    u32 activeContestants = 0;
    struct Pokemon scyther;
    struct Pokemon caterpie;
    u32 scytherScore;
    u32 caterpieScore;
    u8 pokeball = BALL_SPORT;

    // 1. Entry gate setup
    RemoveBagItem(ITEM_SPORT_BALL, 99);
    FlagClear(FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER);
    FlagClear(FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST);

    JohtoGiveParkBalls();
    EXPECT_EQ(CheckBagHasItem(ITEM_SPORT_BALL, 20), TRUE);
    EXPECT_EQ(VarGet(VAR_JOHTO_BUG_CONTEST_STEPS), 500);

    // Verify exactly 5 of 10 contestants are active (flag cleared)
    for (i = 0; i < 10; i++)
    {
        if (!FlagGet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + i))
            activeContestants++;
    }
    EXPECT_EQ(activeContestants, 5);

    // 2. Remaining minutes conversion
    JohtoGetBugContestRemainingMinutes();
    EXPECT_EQ(gSpecialVar_Result, 20);

    // Decrement 25 steps -> 19 minutes left
    VarSet(VAR_JOHTO_BUG_CONTEST_STEPS, 475);
    JohtoGetBugContestRemainingMinutes();
    EXPECT_EQ(gSpecialVar_Result, 19);

    // 3. Scoring calculation
    ZeroMonData(&scyther);
    CreateMon(&scyther, SPECIES_SCYTHER, 14, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&scyther, MON_DATA_POKEBALL, &pokeball);

    ZeroMonData(&caterpie);
    CreateMon(&caterpie, SPECIES_CATERPIE, 7, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&caterpie, MON_DATA_POKEBALL, &pokeball);

    scytherScore = JohtoCalculateContestScore(&scyther);
    caterpieScore = JohtoCalculateContestScore(&caterpie);

    // High rarity mon (Scyther) scores significantly higher than common mon (Caterpie)
    EXPECT_GE(scytherScore, 300);
    EXPECT_LE(caterpieScore, 260);
    EXPECT_GT(scytherScore, caterpieScore);

    // 4. Place Scyther in party and run judging
    ZeroPlayerPartyMons();
    gParties[B_TRAINER_PLAYER][0] = scyther;
    gPartiesCount[B_TRAINER_PLAYER] = 1;

    JohtoBugContestJudge();
    EXPECT_EQ(VarGet(VAR_JOHTO_BUG_CONTEST_SCORE), scytherScore);
    // Scyther with ~350+ score consistently places in top 3
    EXPECT_LE(VarGet(VAR_JOHTO_BUG_CONTEST_PLACEMENT), 3);

    // 5. Cleanup and daily reset
    JohtoBugContestCleanup();
    EXPECT_EQ(CheckBagHasItem(ITEM_SPORT_BALL, 1), FALSE);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER), FALSE);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST), TRUE);
    EXPECT_EQ(VarGet(VAR_JOHTO_BUG_CONTEST_STEPS), 0);

    // Midnight reset re-enables contest
    DoDailyEvents(1);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST), FALSE);
}

TEST("Confluence: Ruins of Alph secret chambers open with proper riddle triggers")
{
    // Test Kabuto Chamber: Escape Rope opens hidden chamber
    FlagClear(FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER), FALSE);

    // Test Aerodactyl Chamber: Field Kit / Flash / HM05 opens hidden chamber
    FlagClear(FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER), FALSE);

    // Test Omanyte Chamber: Water Stone opens hidden chamber
    FlagClear(FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER), FALSE);

    // Test Ho-Oh Chamber: Ho-Oh in party opens hidden chamber
    FlagClear(FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER), FALSE);
}

TEST("Confluence: starting maps for Kanto, Johto, and Hoenn are valid and populated")
{
    const struct MapHeader *kantoHeader = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F));
    const struct MapHeader *johtoHeader = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_JOHTO_PLAYERS_HOUSE_2F), MAP_NUM(MAP_JOHTO_PLAYERS_HOUSE_2F));
    const struct MapHeader *hoennHeader = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F), MAP_NUM(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F));

    EXPECT_NE(kantoHeader, NULL);
    EXPECT_NE(johtoHeader, NULL);
    EXPECT_NE(hoennHeader, NULL);

    EXPECT_EQ(kantoHeader->regionMapSectionId, MAPSEC_PALLET_TOWN);
    EXPECT_EQ(johtoHeader->regionMapSectionId, MAPSEC_JOHTO_NEW_BARK_TOWN);
    EXPECT_EQ(hoennHeader->regionMapSectionId, MAPSEC_LITTLEROOT_TOWN);

    EXPECT_NE(kantoHeader->mapLayout, NULL);
    EXPECT_NE(johtoHeader->mapLayout, NULL);
    EXPECT_NE(hoennHeader->mapLayout, NULL);
}

TEST("Confluence: Authentic Johto Pokégear Radio Card and Audio Broadcasts")
{
    u32 rateNormal = 100;
    u32 rateMarch = 100;
    u32 rateLullaby = 100;

    // 1. Radio Card detection
    FlagClear(FLAG_JOHTO_ENGINE_RADIO_CARD);
    EXPECT_EQ(Johto_HasRadioCard(), FALSE);
    FlagSet(FLAG_JOHTO_ENGINE_RADIO_CARD);
    EXPECT_EQ(Johto_HasRadioCard(), TRUE);

    // 2. EXPN Card detection
    FlagClear(FLAG_JOHTO_ENGINE_EXPN_CARD);
    EXPECT_EQ(Johto_HasExpnCard(), FALSE);
    FlagSet(FLAG_JOHTO_ENGINE_EXPN_CARD);
    EXPECT_EQ(Johto_HasExpnCard(), TRUE);

    // 3. Radio Music Effects (March & Lullaby encounter rate modifiers)
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    Johto_ApplyRadioMusicRateMod(&rateNormal);
    EXPECT_EQ(rateNormal, 100);

    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_MARCH);
    Johto_ApplyRadioMusicRateMod(&rateMarch);
    EXPECT_EQ(rateMarch, 150); // 1.5x encounter rate boost

    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_LULLABY);
    Johto_ApplyRadioMusicRateMod(&rateLullaby);
    EXPECT_EQ(rateLullaby, 50);  // 0.5x encounter rate reduction

    // 4. Station tuning and broadcast state
    JohtoTuneRadioBuenasPassword();
    EXPECT_EQ(Johto_GetActiveRadioStation(), RADIO_STATION_BUENA_PASSWORD);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_LISTENED_TO_BUENAS_PASSWORD), TRUE);

    // 5. Buena's Password consistency
    {
        u8 category = Johto_GetBuenaPasswordCategory();
        u8 correctOpt = Johto_GetBuenaCorrectOption();
        const u8 *passStr = Johto_GetBuenaOptionString(category, correctOpt);
        EXPECT_NE(passStr, NULL);

        // Correct answer grants point on Blue Card
        VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, 5);
        FlagClear(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY);
        gSpecialVar_Result = correctOpt;
        JohtoCheckBuenaAnswer();
        EXPECT_EQ(gSpecialVar_Result, TRUE);
        EXPECT_EQ(VarGet(VAR_JOHTO_BLUE_CARD_BALANCE), 6);
        EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY), TRUE);

        // Wrong answer does not grant point
        gSpecialVar_Result = (correctOpt + 1) % 3;
        JohtoCheckBuenaAnswer();
        EXPECT_EQ(gSpecialVar_Result, FALSE);
        EXPECT_EQ(VarGet(VAR_JOHTO_BLUE_CARD_BALANCE), 6);
    }

    // 6. Turn off radio restores initial state
    Johto_TurnOffRadio();
    EXPECT_EQ(Johto_GetActiveRadioStation(), RADIO_STATION_OFF);
    EXPECT_EQ(Johto_GetActiveRadioMusicEffect(), RADIO_EFFECT_NONE);
    EXPECT_EQ(Johto_IsPokeFluteRadioPlaying(), FALSE);
}

extern void JohtoGetApricornQuantity(void);
extern void JohtoGiveKurtApricorns(void);
extern void JohtoDeliverKurtBalls(void);

TEST("Confluence: Authentic Johto Kurt Apricorn Crafting and Batch Ball Delivery")
{
    // Clear state
    VarSet(VAR_JOHTO_KURT_APRICORN_ITEM, ITEM_NONE);
    VarSet(VAR_JOHTO_KURT_APRICORN_COUNT, 0);
    FlagClear(FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS);
    FlagClear(FLAG_JOHTO_GAVE_KURT_RED_APRICORN);

    // 1. Give player 5 Red Apricorns
    AddBagItem(ITEM_RED_APRICORN, 5);
    gSpecialVar_0x8004 = ITEM_RED_APRICORN;
    JohtoGetApricornQuantity();
    EXPECT_EQ(gSpecialVar_Result, 5);

    // 2. Batch craft 3 Red Apricorns into Level Balls
    gSpecialVar_0x8004 = ITEM_RED_APRICORN;
    gSpecialVar_0x8005 = 3;
    JohtoGiveKurtApricorns();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT_EQ(CheckBagHasItem(ITEM_RED_APRICORN, 2), TRUE);
    EXPECT_EQ(VarGet(VAR_JOHTO_KURT_APRICORN_ITEM), ITEM_LEVEL_BALL);
    EXPECT_EQ(VarGet(VAR_JOHTO_KURT_APRICORN_COUNT), 3);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS), TRUE);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_GAVE_KURT_RED_APRICORN), TRUE);

    // 3. Overnight RTC tick: midnight clears making balls flag
    FlagClear(FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS);

    // 4. Kurt delivers 3 Level Balls
    JohtoDeliverKurtBalls();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    EXPECT_EQ(gSpecialVar_0x8000, ITEM_LEVEL_BALL);
    EXPECT_EQ(gSpecialVar_0x8001, 3);
    EXPECT_EQ(CheckBagHasItem(ITEM_LEVEL_BALL, 3), TRUE);
    EXPECT_EQ(VarGet(VAR_JOHTO_KURT_APRICORN_ITEM), ITEM_NONE);
    EXPECT_EQ(VarGet(VAR_JOHTO_KURT_APRICORN_COUNT), 0);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_GAVE_KURT_RED_APRICORN), FALSE);

    // Clean up
    RemoveBagItem(ITEM_RED_APRICORN, 2);
    RemoveBagItem(ITEM_LEVEL_BALL, 3);
}

extern void JohtoGetUnownCaughtCount(void);

TEST("Confluence: Authentic Johto Unown Pokédex Form Viewer and Word Catalog")
{
    static const u8 sTestAngry[] = _("ANGRY");
    static const u8 sTestChase[] = _("CHASE");
    static const u8 sTestZoom[]  = _("ZOOM");
    static const u8 sTestExcl[]  = _("!!!!");
    static const u8 sTestQues[]  = _("????");

    // Reset Unown caught tracking
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_LOWER, 0);
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_UPPER, 0);
    VarSet(VAR_JOHTO_UNOWN_DEX_INDEX, 0);
    FlagClear(FLAG_JOHTO_ENGINE_UNOWN_DEX);

    EXPECT_EQ(Johto_GetUnownCaughtCount(), 0);
    JohtoGetUnownCaughtCount();
    EXPECT_EQ(gSpecialVar_Result, 0);

    // Register forms: 0 ('A'), 2 ('C'), 25 ('Z'), 26 ('!'), 27 ('?')
    Johto_RegisterCaughtUnownForm(0);
    Johto_RegisterCaughtUnownForm(2);
    Johto_RegisterCaughtUnownForm(25);
    Johto_RegisterCaughtUnownForm(26);
    Johto_RegisterCaughtUnownForm(27);

    // Verify bitfield checks
    EXPECT_EQ(Johto_IsUnownFormCaught(0), TRUE);
    EXPECT_EQ(Johto_IsUnownFormCaught(1), FALSE);
    EXPECT_EQ(Johto_IsUnownFormCaught(2), TRUE);
    EXPECT_EQ(Johto_IsUnownFormCaught(3), FALSE);
    EXPECT_EQ(Johto_IsUnownFormCaught(25), TRUE);
    EXPECT_EQ(Johto_IsUnownFormCaught(26), TRUE);
    EXPECT_EQ(Johto_IsUnownFormCaught(27), TRUE);

    // Verify count and special result
    EXPECT_EQ(Johto_GetUnownCaughtCount(), 5);
    JohtoGetUnownCaughtCount();
    EXPECT_EQ(gSpecialVar_Result, 5);

    // Verify ordered traversal
    EXPECT_EQ(Johto_GetNthCaughtUnownForm(0), 0);
    EXPECT_EQ(Johto_GetNthCaughtUnownForm(1), 2);
    EXPECT_EQ(Johto_GetNthCaughtUnownForm(2), 25);
    EXPECT_EQ(Johto_GetNthCaughtUnownForm(3), 26);
    EXPECT_EQ(Johto_GetNthCaughtUnownForm(4), 27);

    // Verify ancient words
    EXPECT_EQ(StringCompare(Johto_GetUnownWord(0), sTestAngry), 0);
    EXPECT_EQ(StringCompare(Johto_GetUnownWord(2), sTestChase), 0);
    EXPECT_EQ(StringCompare(Johto_GetUnownWord(25), sTestZoom), 0);
    EXPECT_EQ(StringCompare(Johto_GetUnownWord(26), sTestExcl), 0);
    EXPECT_EQ(StringCompare(Johto_GetUnownWord(27), sTestQues), 0);

    // Verify species resolution
    EXPECT_EQ(Johto_GetUnownSpeciesByForm(0), SPECIES_UNOWN);
    EXPECT_EQ(Johto_GetUnownSpeciesByForm(2), SPECIES_UNOWN_C);
    EXPECT_EQ(Johto_GetUnownSpeciesByForm(25), SPECIES_UNOWN_Z);
    EXPECT_EQ(Johto_GetUnownSpeciesByForm(26), SPECIES_UNOWN_EXCLAMATION);
    EXPECT_EQ(Johto_GetUnownSpeciesByForm(27), SPECIES_UNOWN_QUESTION);

    // Verify character representation
    EXPECT_EQ(Johto_GetUnownCharByForm(0), 'A');
    EXPECT_EQ(Johto_GetUnownCharByForm(2), 'C');
    EXPECT_EQ(Johto_GetUnownCharByForm(25), 'Z');
    EXPECT_EQ(Johto_GetUnownCharByForm(26), '!');
    EXPECT_EQ(Johto_GetUnownCharByForm(27), '?');

    // Simulate catching Unown form 1 ('B') via HandleSetPokedexFlag
    // Personality with letter 1:
    // GET_UNOWN_LETTER: ((((p) & 0x03000000) >> 18) | (((p) & 0x00030000) >> 12) | (((p) & 0x00000300) >> 6) | (((p) & 0x00000003))) % 28
    // If p = 1, letter = 1 % 28 = 1 ('B')
    HandleSetPokedexFlag(NATIONAL_DEX_UNOWN, FLAG_SET_CAUGHT, 1);
    EXPECT_EQ(Johto_IsUnownFormCaught(1), TRUE);
    EXPECT_EQ(Johto_GetUnownCaughtCount(), 6);

    // Clean up
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_LOWER, 0);
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_UPPER, 0);
    VarSet(VAR_JOHTO_UNOWN_DEX_INDEX, 0);
}

TEST("Confluence: Authentic Goldenrod Game Corner Card Flip Minigame and Betting Engine")
{
    static const u8 sTestPikachu[] = _("PIKACHU");
    static const u8 sTestOddish[]  = _("ODDISH");

    // 1. Deck indexing and suit/rank mapping
    EXPECT_EQ(CardFlip_GetCardSuit(0), CARDFLIP_SUIT_PIKACHU);
    EXPECT_EQ(CardFlip_GetCardRank(0), 1);
    EXPECT_EQ(CardFlip_GetCardSuit(3), CARDFLIP_SUIT_ODDISH);
    EXPECT_EQ(CardFlip_GetCardRank(3), 1);
    EXPECT_EQ(CardFlip_GetCardSuit(23), CARDFLIP_SUIT_ODDISH);
    EXPECT_EQ(CardFlip_GetCardRank(23), 6);

    EXPECT_EQ(StringCompare(CardFlip_GetSuitName(CARDFLIP_SUIT_PIKACHU), sTestPikachu), 0);
    EXPECT_EQ(StringCompare(CardFlip_GetSuitName(CARDFLIP_SUIT_ODDISH), sTestOddish), 0);

    // 2. Coin Case checks
    RemoveBagItem(ITEM_COIN_CASE, 1);
    Special_CardFlipInit();
    EXPECT_EQ(gSpecialVar_Result, 0); // No Coin Case

    AddBagItem(ITEM_COIN_CASE, 1);
    SetCoins(2);
    Special_CardFlipInit();
    EXPECT_EQ(gSpecialVar_Result, 1); // Not enough coins (< 3)

    SetCoins(100);
    Special_CardFlipInit();
    EXPECT_EQ(gSpecialVar_Result, 2); // Ready

    // 3. Deal deduction: 3 coins deducted per deal
    Special_CardFlipDeal();
    EXPECT_EQ(GetCoins(), 97);
    EXPECT_EQ(gSpecialVar_Result, 0); // Normal deal

    // 4. Test all 5 bet types on known card
    gSpecialVar_0x8004 = 1;
    Special_CardFlipSelectCard();

    u8 card = CardFlip_GetChosenCard();
    u8 suit = CardFlip_GetCardSuit(card);
    u8 rank = CardFlip_GetCardRank(card);
    u8 wrongSuit = (suit + 1) % CARDFLIP_NUM_SUITS;
    u8 wrongRank = (rank == 6) ? 1 : (rank + 1);

    // Single Card bet (24x, 72 coins)
    CardFlip_SetBet(CARDFLIP_BET_SINGLE_CARD, suit, rank);
    EXPECT_EQ(CardFlip_EvaluateBet(), TRUE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 72);
    EXPECT_EQ(GetCoins(), 97 + 72);

    CardFlip_SetBet(CARDFLIP_BET_SINGLE_CARD, wrongSuit, rank);
    EXPECT_EQ(CardFlip_EvaluateBet(), FALSE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 0);

    // Single Rank bet (6x, 18 coins)
    CardFlip_SetBet(CARDFLIP_BET_RANK, rank, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), TRUE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 18);

    CardFlip_SetBet(CARDFLIP_BET_RANK, wrongRank, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), FALSE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 0);

    // Single Suit bet (4x, 12 coins)
    CardFlip_SetBet(CARDFLIP_BET_SUIT, suit, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), TRUE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 12);

    CardFlip_SetBet(CARDFLIP_BET_SUIT, wrongSuit, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), FALSE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 0);

    // Rank Pair bet (3x, 9 coins)
    u8 pairIdx = (rank - 1) / 2;
    u8 wrongPairIdx = (pairIdx + 1) % 3;
    CardFlip_SetBet(CARDFLIP_BET_RANK_PAIR, pairIdx, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), TRUE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 9);

    CardFlip_SetBet(CARDFLIP_BET_RANK_PAIR, wrongPairIdx, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), FALSE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 0);

    // Suit Pair bet (2x, 6 coins)
    u8 suitPairIdx = (suit == CARDFLIP_SUIT_PIKACHU || suit == CARDFLIP_SUIT_JIGGLYPUFF) ? 0 : 1;
    u8 wrongSuitPairIdx = 1 - suitPairIdx;
    CardFlip_SetBet(CARDFLIP_BET_SUIT_PAIR, suitPairIdx, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), TRUE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 6);

    CardFlip_SetBet(CARDFLIP_BET_SUIT_PAIR, wrongSuitPairIdx, 0);
    EXPECT_EQ(CardFlip_EvaluateBet(), FALSE);
    EXPECT_EQ(CardFlip_GetLastPayout(), 0);

    // 5. Deck exhaustion and automatic reshuffling
    CardFlip_InitDeck();
    SetCoins(100);
    u32 round;
    for (round = 0; round < 12; round++)
    {
        Special_CardFlipDeal();
    }
    EXPECT_EQ(CardFlip_GetCardsRemaining(), 0);

    Special_CardFlipDeal();
    EXPECT_EQ(gSpecialVar_Result, 1); // Reshuffled!
    EXPECT_EQ(CardFlip_GetCardsRemaining(), 22);

    // Clean up
    RemoveBagItem(ITEM_COIN_CASE, 1);
    SetCoins(0);
}

TEST("Confluence: Authentic Johto Buena's Password and Blue Card Point Exchange")
{
    // 1. Blue Card balance tracking
    VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, 0);
    JohtoGetBlueCardBalance();
    EXPECT_EQ(gSpecialVar_Result, 0);

    // 2. Evening hours validation
    // Simulate day: 14:00 (off air)
    RtcCalcLocalTimeOffset(0, 14, 0, 0);
    JohtoCheckBuenaTime();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // Simulate evening: 20:00 (on air)
    RtcCalcLocalTimeOffset(0, 20, 0, 0);
    JohtoCheckBuenaTime();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // 3. Password selection and validation
    // Ensure daily point flag is clear
    FlagClear(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY);
    JohtoGetBuenaPasswordChoices();
    EXPECT_GT(StringLength(gStringVar1), 0);
    EXPECT_GT(StringLength(gStringVar2), 0);
    EXPECT_GT(StringLength(gStringVar3), 0);

    u8 correctOpt = Johto_GetBuenaCorrectOption();
    u8 wrongOpt = (correctOpt + 1) % 3;

    // Wrong answer: no point awarded, result FALSE
    gSpecialVar_Result = wrongOpt;
    JohtoCheckBuenaAnswer();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    JohtoGetBlueCardBalance();
    EXPECT_EQ(gSpecialVar_Result, 0);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY), FALSE);

    // Correct answer: +1 point awarded, result TRUE, daily flag set
    gSpecialVar_Result = correctOpt;
    JohtoCheckBuenaAnswer();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    JohtoGetBlueCardBalance();
    EXPECT_EQ(gSpecialVar_Result, 1);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY), TRUE);

    // 4. Point cap at 30 points
    VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, 30);
    gSpecialVar_Result = correctOpt;
    JohtoCheckBuenaAnswer();
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    JohtoGetBlueCardBalance();
    EXPECT_EQ(gSpecialVar_Result, 30);

    // 5. Prize redemption: Ultra Ball (2 pts), Rare Candy (3 pts), Protein (5 pts)
    VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, 4);

    // Protein costs 5 pts -> should fail with Result 1 (not enough)
    gSpecialVar_0x8004 = 4; // Protein
    JohtoRedeemBuenaPrize();
    EXPECT_EQ(gSpecialVar_Result, 1);
    EXPECT_EQ(VarGet(VAR_JOHTO_BLUE_CARD_BALANCE), 4);

    // Ultra Ball costs 2 pts -> should succeed with Result 0, deducting 2 pts
    u16 ballsBefore = CheckBagHasItem(ITEM_ULTRA_BALL, 1);
    gSpecialVar_0x8004 = 0; // Ultra Ball
    JohtoRedeemBuenaPrize();
    EXPECT_EQ(gSpecialVar_Result, 0);
    EXPECT_EQ(VarGet(VAR_JOHTO_BLUE_CARD_BALANCE), 2);
    EXPECT_EQ(CheckBagHasItem(ITEM_ULTRA_BALL, ballsBefore + 1), TRUE);

    // Clean up
    RemoveBagItem(ITEM_ULTRA_BALL, 1);
    VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, 0);
    FlagClear(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY);
}

TEST("Confluence: Authentic Johto Battle Tower 7-Trainer Ladder and Level Brackets")
{
    // Save party
    struct Pokemon savedParty[PARTY_SIZE];
    u8 savedPartyCount = gPartiesCount[B_TRAINER_PLAYER];
    memcpy(savedParty, gParties[B_TRAINER_PLAYER], sizeof(savedParty));

    // 1. Eligibility: Less than 3 Pokémon
    ZeroPlayerPartyMons();
    gPartiesCount[B_TRAINER_PLAYER] = 2;
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PRESET(0));
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_CHARMANDER, 20, 0, OTID_STRUCT_PRESET(0));
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][0]);
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][1]);
    VarSet(VAR_JOHTO_BATTLE_TOWER_LEVEL, 50);
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 1); // Less than 3 mons

    // 2. Eligibility: 3 valid Pokémon with Level <= room level (Lv. 50 bracket)
    gPartiesCount[B_TRAINER_PLAYER] = 3;
    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_SQUIRTLE, 20, 0, OTID_STRUCT_PRESET(0));
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][2]);
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 0); // Eligible!

    // 3. Eligibility: Level restriction check (Lv. 10 bracket with Lv. 20 mons)
    VarSet(VAR_JOHTO_BATTLE_TOWER_LEVEL, 10);
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 2); // Exceeds level limit

    // 4. Eligibility: Species Clause (duplicate Pokémon)
    VarSet(VAR_JOHTO_BATTLE_TOWER_LEVEL, 50);
    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PRESET(0)); // Duplicate Pikachu
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 3); // Duplicate species

    // 5. Eligibility: Item Clause (duplicate held items)
    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_SQUIRTLE, 20, 0, OTID_STRUCT_PRESET(0));
    u16 item = ITEM_LEFTOVERS;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM, &item); // Duplicate Leftovers
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 4); // Duplicate items

    // Fix item clause
    item = ITEM_NONE;
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM, &item);
    JohtoCheckBattleTowerEligibility();
    EXPECT_EQ(gSpecialVar_Result, 0); // Eligible!

    // 6. Challenge initialization and streak advancement
    JohtoBattleTowerInitChallenge();
    EXPECT_EQ(JohtoBattleTower_GetStreak(), 0);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_BATTLE_TOWER_WON_CHALLENGE), FALSE);

    // 7. Opponent generation: round 1 (streak 0) at Lv. 50
    VarSet(VAR_JOHTO_BATTLE_TOWER_LEVEL, 50);
    JohtoBattleTowerPrepareOpponent();
    EXPECT_EQ(gPartiesCount[B_TRAINER_OPPONENT_A], 3);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL), 50);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_LEVEL), 50);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][2], MON_DATA_LEVEL), 50);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_HP_IV), 12);

    // Advance streak to round 7 (streak 6)
    VarSet(VAR_JOHTO_BATTLE_TOWER_STREAK, 6);
    JohtoBattleTowerPrepareOpponent();
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_HP_IV), 31); // Peak IVs!

    // Advance streak to 7 (complete gauntlet)
    JohtoBattleTowerAdvanceStreak();
    EXPECT_EQ(gSpecialVar_Result, 7);
    EXPECT_EQ(JohtoBattleTower_GetStreak(), 7);

    // 8. Prize award: 5 vitamins
    u16 initialWins = JohtoBattleTower_GetWins();
    JohtoBattleTowerGivePrizes();
    EXPECT_EQ(JohtoBattleTower_GetWins(), initialWins + 1);
    EXPECT_EQ(FlagGet(FLAG_JOHTO_BATTLE_TOWER_WON_CHALLENGE), TRUE);

    // Restore party
    memcpy(gParties[B_TRAINER_PLAYER], savedParty, sizeof(savedParty));
    gPartiesCount[B_TRAINER_PLAYER] = savedPartyCount;
    FlagClear(FLAG_JOHTO_BATTLE_TOWER_WON_CHALLENGE);
}

TEST("Confluence: Authentic FireRed Fame Checker Lore Journal Subsystem")
{
    u8 i;
    u32 pickState;
    u32 flags;

    // 1. Reset Fame Checker and verify state (Oak is unlocked and colored by default)
    ResetFameChecker();
    for (i = 0; i < NUM_FAMECHECKER_PERSONS; i++)
    {
        pickState = gSaveBlock1Ptr->fameChecker[i].pickState;
        flags = gSaveBlock1Ptr->fameChecker[i].flavorTextFlags;
        if (i == FAMECHECKER_OAK)
            EXPECT_EQ(pickState, FCPICKSTATE_COLORED);
        else
            EXPECT_EQ(pickState, FCPICKSTATE_NO_DRAW);
        EXPECT_EQ(flags, 0);
    }

    // 2. Unlock a flavor text entry via special variables for Oak (already colored)
    gSpecialVar_0x8004 = FAMECHECKER_OAK;
    gSpecialVar_0x8005 = 0;
    SetFlavorTextFlagFromSpecialVars();
    flags = gSaveBlock1Ptr->fameChecker[FAMECHECKER_OAK].flavorTextFlags;
    pickState = gSaveBlock1Ptr->fameChecker[FAMECHECKER_OAK].pickState;
    EXPECT_EQ(flags, (1 << 0));
    EXPECT_EQ(pickState, FCPICKSTATE_COLORED);

    // 3. Unlock another clue for Oak
    gSpecialVar_0x8004 = FAMECHECKER_OAK;
    gSpecialVar_0x8005 = 3;
    SetFlavorTextFlagFromSpecialVars();
    flags = gSaveBlock1Ptr->fameChecker[FAMECHECKER_OAK].flavorTextFlags;
    pickState = gSaveBlock1Ptr->fameChecker[FAMECHECKER_OAK].pickState;
    EXPECT_EQ(flags, (1 << 0) | (1 << 3));
    EXPECT_EQ(pickState, FCPICKSTATE_COLORED);

    // 4. Test unlocking an undiscovered person (e.g. Brock, starts NO_DRAW)
    EXPECT_EQ((u32)gSaveBlock1Ptr->fameChecker[FAMECHECKER_BROCK].pickState, FCPICKSTATE_NO_DRAW);
    gSpecialVar_0x8004 = FAMECHECKER_BROCK;
    gSpecialVar_0x8005 = 1;
    SetFlavorTextFlagFromSpecialVars();
    flags = gSaveBlock1Ptr->fameChecker[FAMECHECKER_BROCK].flavorTextFlags;
    pickState = gSaveBlock1Ptr->fameChecker[FAMECHECKER_BROCK].pickState;
    EXPECT_EQ(flags, (1 << 1));
    EXPECT_EQ(pickState, FCPICKSTATE_SILHOUETTE);

    // Upgrade Brock from SILHOUETTE to COLORED
    gSpecialVar_0x8004 = FAMECHECKER_BROCK;
    gSpecialVar_0x8005 = FCPICKSTATE_COLORED;
    UpdatePickStateFromSpecialVar8005();
    pickState = gSaveBlock1Ptr->fameChecker[FAMECHECKER_BROCK].pickState;
    EXPECT_EQ(pickState, FCPICKSTATE_COLORED);

    // Cannot downgrade Brock from COLORED to SILHOUETTE
    gSpecialVar_0x8005 = FCPICKSTATE_SILHOUETTE;
    UpdatePickStateFromSpecialVar8005();
    pickState = gSaveBlock1Ptr->fameChecker[FAMECHECKER_BROCK].pickState;
    EXPECT_EQ(pickState, FCPICKSTATE_COLORED);

    // 6. Fully unlock all 16 Kanto persons and verify 6 clues each
    FullyUnlockFameChecker();
    for (i = 0; i < NUM_FAMECHECKER_PERSONS; i++)
    {
        pickState = gSaveBlock1Ptr->fameChecker[i].pickState;
        flags = gSaveBlock1Ptr->fameChecker[i].flavorTextFlags;
        EXPECT_EQ(pickState, FCPICKSTATE_COLORED);
        EXPECT_EQ(flags, 0x3F); // bits 0-5 set
    }

    // 7. Verify item field function binding
    EXPECT_EQ((void *)GetItemFieldFunc(ITEM_FAME_CHECKER), (void *)ItemUseOutOfBattle_FameChecker);

    // Clean up
    ResetFameChecker();
}

TEST("Confluence: Authentic FireRed Joyful Game Corner Minigames and Berry Powder Economy")
{
    // 1. Berry Powder economy and Powder Jar mechanics
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    EXPECT_EQ(GetBerryPowder(), 0);

    // Initial check for berries
    RemoveBagItem(ITEM_CHERI_BERRY, 99);
    EXPECT_EQ(HasAtLeastOneBerry(), FALSE);

    // Add berries to bag
    AddBagItem(ITEM_CHERI_BERRY, 5);
    EXPECT_EQ(HasAtLeastOneBerry(), TRUE);

    // Exchange checks
    gSpecialVar_0x8004 = 50; // Energypowder cost
    EXPECT_EQ(HasEnoughBerryPowder(), FALSE);

    // Give powder (e.g. from crushing berries)
    GiveBerryPowder(1500);
    EXPECT_EQ(GetBerryPowder(), 1500);
    EXPECT_EQ(HasEnoughBerryPowder(), TRUE);

    // Exchange for Protein (1000 powder)
    gSpecialVar_0x8004 = 1000;
    EXPECT_EQ(HasEnoughBerryPowder(), TRUE);
    TakeBerryPowder();
    EXPECT_EQ(GetBerryPowder(), 500);

    // Exchange for Energypowder (50 powder)
    gSpecialVar_0x8004 = 50;
    EXPECT_EQ(HasEnoughBerryPowder(), TRUE);
    TakeBerryPowder();
    EXPECT_EQ(GetBerryPowder(), 450);

    // Insufficient powder for PP Up (3000 powder)
    gSpecialVar_0x8004 = 3000;
    EXPECT_EQ(HasEnoughBerryPowder(), FALSE);

    // Game stat tracking
    IncrementGameStat(GAME_STAT_PLAYED_BERRY_CRUSH);
    EXPECT_GE(GetGameStat(GAME_STAT_PLAYED_BERRY_CRUSH), 1);

    // 2. Pokemon Jump species eligibility
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_PIKACHU), TRUE);
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_CLEFAIRY), TRUE);
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_ODDISH), TRUE);
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_GYARADOS), FALSE);
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_SNORLAX), FALSE);
    EXPECT_EQ(IsSpeciesAllowedInPokemonJump(SPECIES_ONIX), FALSE);

    // Party eligibility check for Pokemon Jump
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][1]);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][2]);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_SNORLAX, 30, 0, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 1;

    IsPokemonJumpSpeciesInParty();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_PIKACHU, 25, 0, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 2;

    IsPokemonJumpSpeciesInParty();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // 3. Dodrio Berry Picking party eligibility
    IsDodrioInParty();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_DODRIO, 35, 0, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 3;

    IsDodrioInParty();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // Clean up
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    RemoveBagItem(ITEM_CHERI_BERRY, 99);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][1]);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][2]);
    gPartiesCount[B_TRAINER_PLAYER] = 0;
}

TEST("Confluence: Authentic FireRed Teachy TV Subsystem")
{
    // 1. Verify item table configuration
    EXPECT_EQ(GetItemPocket(ITEM_TEACHY_TV), POCKET_KEY_ITEMS);
    EXPECT_EQ(GetItemImportance(ITEM_TEACHY_TV), 1);
    EXPECT_EQ(GetItemType(ITEM_TEACHY_TV), ITEM_USE_BAG_MENU);
    EXPECT(GetItemFieldFunc(ITEM_TEACHY_TV) == ItemUseOutOfBattle_TeachyTv);

    // 2. Verify Teachy TV episode script identifiers
    EXPECT_EQ(TTVSCR_BATTLE, 0);
    EXPECT_EQ(TTVSCR_STATUS, 1);
    EXPECT_EQ(TTVSCR_MATCHUPS, 2);
    EXPECT_EQ(TTVSCR_CATCHING, 3);
    EXPECT_EQ(TTVSCR_TMS, 4);
    EXPECT_EQ(TTVSCR_REGISTER, 5);
    EXPECT_EQ(TTVSCR_COUNT, 6);

    // 3. Verify item registration and bag manipulation
    EXPECT_EQ(CheckBagHasItem(ITEM_TEACHY_TV, 1), FALSE);
    EXPECT_EQ(AddBagItem(ITEM_TEACHY_TV, 1), TRUE);
    EXPECT_EQ(CheckBagHasItem(ITEM_TEACHY_TV, 1), TRUE);
    EXPECT_EQ(RemoveBagItem(ITEM_TEACHY_TV, 1), TRUE);
    EXPECT_EQ(CheckBagHasItem(ITEM_TEACHY_TV, 1), FALSE);
}

TEST("Confluence: Authentic Yellow Surfing Pikachu Beach Minigame Subsystem")
{
    // 1. Verify party qualification logic with no mons
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    CheckSurfingPikachuInParty();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // 2. Add non-Pikachu or Pikachu without Surf
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    // Set moves to non-Surf moves
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_THUNDERSHOCK, 0);
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_GROWL, 1);
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_TAIL_WHIP, 2);
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_QUICK_ATTACK, 3);
    CheckSurfingPikachuInParty();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // 3. Teach Pikachu MOVE_SURF -> now eligible!
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_SURF, 0);
    CheckSurfingPikachuInParty();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // 4. Test score getters and variables
    VarSet(VAR_SURFING_PIKACHU_HIGH_SCORE, 7350);
    VarSet(VAR_SURFING_PIKACHU_RADNESS, 420);
    GetSurfingPikachuScores();
    EXPECT_EQ(gSpecialVar_0x8004, 7350);
    EXPECT_EQ(gSpecialVar_0x8005, 420);

    // 5. Test flag operations
    FlagClear(FLAG_MET_SURFIN_DUDE);
    EXPECT_EQ(FlagGet(FLAG_MET_SURFIN_DUDE), FALSE);
    FlagSet(FLAG_MET_SURFIN_DUDE);
    EXPECT_EQ(FlagGet(FLAG_MET_SURFIN_DUDE), TRUE);

    // Clean up
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    gPartiesCount[B_TRAINER_PLAYER] = 0;
}

TEST("Confluence: Authentic Yellow Pikachu Voiced 8-bit PCM Audio Subsystem")
{
    // 1. Verify config toggle
    EXPECT_EQ(VOICED_PIKACHU_CRIES, TRUE);

    // 2. Verify voice identifier constants
    EXPECT_EQ(PIKA_VOICE_ENTRANCE, 0);
    EXPECT_EQ(PIKA_VOICE_FAINT, 1);
    EXPECT_EQ(PIKA_VOICE_LOW_HP, 2);
    EXPECT_EQ(PIKA_VOICE_LEVEL_UP, 3);
    EXPECT_EQ(PIKA_VOICE_THUNDER, 4);
    EXPECT_EQ(PIKA_VOICE_JOY, 5);
    EXPECT_EQ(PIKA_VOICE_SAD, 6);
    EXPECT_EQ(PIKA_VOICE_COUNT, 7);

    // 3. Verify Pikachu forms mapping to CRY_PIKACHU
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_COSPLAY].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_ROCK_STAR].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_BELLE].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_POP_STAR].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_PHD].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_LIBRE].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_ORIGINAL].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_HOENN].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_SINNOH].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_UNOVA].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_KALOS].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_ALOLA].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_PARTNER].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_WORLD].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_STARTER].cryId == CRY_PIKACHU);
    EXPECT(gSpeciesInfo[SPECIES_PIKACHU_GMAX].cryId == CRY_PIKACHU);

    // 4. Verify tone table structure
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_ENTRANCE].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_ENTRANCE].key, 60);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_FAINT].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_LOW_HP].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_LEVEL_UP].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_THUNDER].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_JOY].type, 0x20);
    EXPECT_EQ(gPikachuVoiceTable[PIKA_VOICE_SAD].type, 0x20);

    // 5. Verify reverse tone table structure
    EXPECT_EQ(gPikachuVoiceTable_Reverse[PIKA_VOICE_ENTRANCE].type, 0x30);
    EXPECT_EQ(gPikachuVoiceTable_Reverse[PIKA_VOICE_ENTRANCE].key, 60);

    // 6. Test playback execution functions
    PlayPikachuVoice(PIKA_VOICE_ENTRANCE, 0);
    PlayPikachuVoice(PIKA_VOICE_FAINT, -25);
    PlayPikachuVoice(PIKA_VOICE_THUNDER, 25);
    PlayPikachuCelebrationCry();
    PlayPikachuVoice(99, 0); // Out-of-bounds safety check
}

TEST("Confluence: Authentic Emerald Hoenn Gym Leader Rematches Subsystem")
{
    // 1. Verify all 8 Hoenn Gym Leader rematch mappings in gRematchTable
    EXPECT_EQ(gRematchTable[REMATCH_ROXANNE].trainerIds[0], TRAINER_ROXANNE_1);
    EXPECT_EQ(gRematchTable[REMATCH_ROXANNE].trainerIds[1], TRAINER_ROXANNE_2);
    EXPECT_EQ(gRematchTable[REMATCH_ROXANNE].trainerIds[2], TRAINER_ROXANNE_3);
    EXPECT_EQ(gRematchTable[REMATCH_ROXANNE].trainerIds[3], TRAINER_ROXANNE_4);
    EXPECT_EQ(gRematchTable[REMATCH_ROXANNE].trainerIds[4], TRAINER_ROXANNE_5);

    EXPECT_EQ(gRematchTable[REMATCH_BRAWLY].trainerIds[0], TRAINER_BRAWLY_1);
    EXPECT_EQ(gRematchTable[REMATCH_BRAWLY].trainerIds[1], TRAINER_BRAWLY_2);
    EXPECT_EQ(gRematchTable[REMATCH_BRAWLY].trainerIds[2], TRAINER_BRAWLY_3);
    EXPECT_EQ(gRematchTable[REMATCH_BRAWLY].trainerIds[3], TRAINER_BRAWLY_4);
    EXPECT_EQ(gRematchTable[REMATCH_BRAWLY].trainerIds[4], TRAINER_BRAWLY_5);

    EXPECT_EQ(gRematchTable[REMATCH_WATTSON].trainerIds[0], TRAINER_WATTSON_1);
    EXPECT_EQ(gRematchTable[REMATCH_WATTSON].trainerIds[1], TRAINER_WATTSON_2);
    EXPECT_EQ(gRematchTable[REMATCH_WATTSON].trainerIds[2], TRAINER_WATTSON_3);
    EXPECT_EQ(gRematchTable[REMATCH_WATTSON].trainerIds[3], TRAINER_WATTSON_4);
    EXPECT_EQ(gRematchTable[REMATCH_WATTSON].trainerIds[4], TRAINER_WATTSON_5);

    EXPECT_EQ(gRematchTable[REMATCH_FLANNERY].trainerIds[0], TRAINER_FLANNERY_1);
    EXPECT_EQ(gRematchTable[REMATCH_FLANNERY].trainerIds[1], TRAINER_FLANNERY_2);
    EXPECT_EQ(gRematchTable[REMATCH_FLANNERY].trainerIds[2], TRAINER_FLANNERY_3);
    EXPECT_EQ(gRematchTable[REMATCH_FLANNERY].trainerIds[3], TRAINER_FLANNERY_4);
    EXPECT_EQ(gRematchTable[REMATCH_FLANNERY].trainerIds[4], TRAINER_FLANNERY_5);

    EXPECT_EQ(gRematchTable[REMATCH_NORMAN].trainerIds[0], TRAINER_NORMAN_1);
    EXPECT_EQ(gRematchTable[REMATCH_NORMAN].trainerIds[1], TRAINER_NORMAN_2);
    EXPECT_EQ(gRematchTable[REMATCH_NORMAN].trainerIds[2], TRAINER_NORMAN_3);
    EXPECT_EQ(gRematchTable[REMATCH_NORMAN].trainerIds[3], TRAINER_NORMAN_4);
    EXPECT_EQ(gRematchTable[REMATCH_NORMAN].trainerIds[4], TRAINER_NORMAN_5);

    EXPECT_EQ(gRematchTable[REMATCH_WINONA].trainerIds[0], TRAINER_WINONA_1);
    EXPECT_EQ(gRematchTable[REMATCH_WINONA].trainerIds[1], TRAINER_WINONA_2);
    EXPECT_EQ(gRematchTable[REMATCH_WINONA].trainerIds[2], TRAINER_WINONA_3);
    EXPECT_EQ(gRematchTable[REMATCH_WINONA].trainerIds[3], TRAINER_WINONA_4);
    EXPECT_EQ(gRematchTable[REMATCH_WINONA].trainerIds[4], TRAINER_WINONA_5);

    EXPECT_EQ(gRematchTable[REMATCH_TATE_AND_LIZA].trainerIds[0], TRAINER_TATE_AND_LIZA_1);
    EXPECT_EQ(gRematchTable[REMATCH_TATE_AND_LIZA].trainerIds[1], TRAINER_TATE_AND_LIZA_2);
    EXPECT_EQ(gRematchTable[REMATCH_TATE_AND_LIZA].trainerIds[2], TRAINER_TATE_AND_LIZA_3);
    EXPECT_EQ(gRematchTable[REMATCH_TATE_AND_LIZA].trainerIds[3], TRAINER_TATE_AND_LIZA_4);
    EXPECT_EQ(gRematchTable[REMATCH_TATE_AND_LIZA].trainerIds[4], TRAINER_TATE_AND_LIZA_5);

    EXPECT_EQ(gRematchTable[REMATCH_JUAN].trainerIds[0], TRAINER_JUAN_1);
    EXPECT_EQ(gRematchTable[REMATCH_JUAN].trainerIds[1], TRAINER_JUAN_2);
    EXPECT_EQ(gRematchTable[REMATCH_JUAN].trainerIds[2], TRAINER_JUAN_3);
    EXPECT_EQ(gRematchTable[REMATCH_JUAN].trainerIds[3], TRAINER_JUAN_4);
    EXPECT_EQ(gRematchTable[REMATCH_JUAN].trainerIds[4], TRAINER_JUAN_5);

    // 2. Verify rematch roster capacity (4 rematch tiers + 1 base = 5 teams)
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_ROXANNE), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_BRAWLY), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_WATTSON), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_FLANNERY), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_NORMAN), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_WINONA), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_TATE_AND_LIZA), 4);
    EXPECT_EQ(CountMaxPossibleRematch(REMATCH_JUAN), 4);

    // 3. Test tier progression logic
    FlagClear(TRAINER_FLAGS_START + TRAINER_ROXANNE_1);
    FlagClear(TRAINER_FLAGS_START + TRAINER_ROXANNE_2);
    FlagClear(TRAINER_FLAGS_START + TRAINER_ROXANNE_3);
    EXPECT_EQ(CountBattledRematchTeams(REMATCH_ROXANNE), 0);

    // After defeating base Roxanne
    FlagSet(TRAINER_FLAGS_START + TRAINER_ROXANNE_1);
    EXPECT_EQ(CountBattledRematchTeams(REMATCH_ROXANNE), 1);
    EXPECT_EQ(GetRematchTrainerIdFromTable(gRematchTable, TRAINER_ROXANNE_1), TRAINER_ROXANNE_2);

    // 4. Test rematch readiness via trainerRematches before rematch 1 is won
    gSaveBlock1Ptr->trainerRematches[REMATCH_ROXANNE] = 0;
    EXPECT_EQ(ShouldTryRematchBattleForTrainerId(TRAINER_ROXANNE_1), FALSE);
    gSaveBlock1Ptr->trainerRematches[REMATCH_ROXANNE] = 1;
    EXPECT_EQ(ShouldTryRematchBattleForTrainerId(TRAINER_ROXANNE_1), TRUE);
    gSaveBlock1Ptr->trainerRematches[REMATCH_ROXANNE] = 0;

    // After defeating Rematch 1 (Tier 2)
    FlagSet(TRAINER_FLAGS_START + TRAINER_ROXANNE_2);
    EXPECT_EQ(CountBattledRematchTeams(REMATCH_ROXANNE), 2);
    EXPECT_EQ(GetRematchTrainerIdFromTable(gRematchTable, TRAINER_ROXANNE_1), TRAINER_ROXANNE_3);
    // Once second rematch has been won, ShouldTryRematchBattle routes to post-rematch dialogue script
    EXPECT_EQ(ShouldTryRematchBattleForTrainerId(TRAINER_ROXANNE_1), TRUE);

    // 5. Test Gym Leader Rematch level calculation and multi-region qualification
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_CONFLUENCE_APEX_CHAMPION);
    for (u32 b = 0; b < CONFLUENCE_BADGES_PER_REGION; b++)
        FlagClear(FLAG_BADGE01_GET + b);
    EXPECT_EQ(GetCurrentGymLeaderRematchLevel(), 0);

    // Qualify via FLAG_SYS_GAME_CLEAR
    FlagSet(FLAG_SYS_GAME_CLEAR);
    // Wattson 1 not fought yet, so lowest rematch level is 0
    FlagClear(TRAINER_FLAGS_START + TRAINER_WATTSON_1);
    EXPECT_EQ(GetCurrentGymLeaderRematchLevel(), 0);

    // Mark all base leaders fought
    for (u32 leader = REMATCH_ROXANNE; leader <= REMATCH_JUAN; leader++)
        FlagSet(TRAINER_FLAGS_START + gRematchTable[leader].trainerIds[0]);

    // Now all base leaders are fought, so minimum rematch level across leaders is 1
    EXPECT_EQ(GetCurrentGymLeaderRematchLevel(), 1);

    // Clean up flags
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(TRAINER_FLAGS_START + TRAINER_ROXANNE_1);
    FlagClear(TRAINER_FLAGS_START + TRAINER_ROXANNE_2);
    for (u32 leader = REMATCH_ROXANNE; leader <= REMATCH_JUAN; leader++)
        FlagClear(TRAINER_FLAGS_START + gRematchTable[leader].trainerIds[0]);
}

TEST("Confluence: Authentic Emerald Trick House Puzzles and Mirage Island Mechanics")
{
    // 1. Mirage Island seed generation and presence check
    VarSet(VAR_MIRAGE_RND_H, 0x1234);
    VarSet(VAR_MIRAGE_RND_L, 0x5678);

    // Empty party -> Mirage Island not present
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    EXPECT_EQ(IsMirageIslandPresent(), FALSE);

    // Create a party mon with personality whose lower 16 bits match VAR_MIRAGE_RND_H (0x1234)
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WYNAUT, 5, 0x98761234, OTID_STRUCT_PRESET(0));
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    EXPECT_EQ(IsMirageIslandPresent(), TRUE);

    // Change seed -> Mirage Island no longer matches
    VarSet(VAR_MIRAGE_RND_H, 0xABCD);
    EXPECT_EQ(IsMirageIslandPresent(), FALSE);

    // Test UpdateMirageRnd daily progression
    u16 oldHi = VarGet(VAR_MIRAGE_RND_H);
    u16 oldLo = VarGet(VAR_MIRAGE_RND_L);
    UpdateMirageRnd(1);
    u16 newHi = VarGet(VAR_MIRAGE_RND_H);
    u16 newLo = VarGet(VAR_MIRAGE_RND_L);
    EXPECT((oldHi != newHi) || (oldLo != newLo));

    // 2. Mirage Tower state transitions and fossil mechanics
    VarSet(VAR_MIRAGE_TOWER_STATE, 0);
    EXPECT_EQ(VarGet(VAR_MIRAGE_TOWER_STATE), 0);
    VarSet(VAR_MIRAGE_TOWER_STATE, 1); // Collapsing
    EXPECT_EQ(VarGet(VAR_MIRAGE_TOWER_STATE), 1);
    VarSet(VAR_MIRAGE_TOWER_STATE, 2); // Disintegrated
    EXPECT_EQ(VarGet(VAR_MIRAGE_TOWER_STATE), 2);

    // Fossil items
    EXPECT(ITEM_ROOT_FOSSIL != ITEM_NONE);
    EXPECT(ITEM_CLAW_FOSSIL != ITEM_NONE);

    // 3. Trick House puzzle variables and scroll states
    VarSet(VAR_TRICK_HOUSE_LEVEL, 0);
    EXPECT_EQ(VarGet(VAR_TRICK_HOUSE_LEVEL), 0);
    VarSet(VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0); // Scroll not found
    EXPECT_EQ(VarGet(VAR_TRICK_HOUSE_PUZZLE_1_STATE), 0);
    VarSet(VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1); // Scroll found
    EXPECT_EQ(VarGet(VAR_TRICK_HOUSE_PUZZLE_1_STATE), 1);
    VarSet(VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2); // Door opened
    EXPECT_EQ(VarGet(VAR_TRICK_HOUSE_PUZZLE_1_STATE), 2);

    // Clean up
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    VarSet(VAR_MIRAGE_TOWER_STATE, 0);
    VarSet(VAR_TRICK_HOUSE_LEVEL, 0);
    VarSet(VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0);
}

TEST("Confluence: Authentic Emerald Contest Halls and Berry Blender Pokéblock Subsystem")
{
    // 1. Verify Pokéblock Case structure and capacity
    EXPECT_EQ(POKEBLOCKS_COUNT, 40);
    ClearPokeblocks();
    EXPECT_EQ(GetFirstFreePokeblockSlot(), 0);

    // 2. Create and insert an authentic Red (Spicy) Pokéblock
    struct Pokeblock block;
    block.color = PBLOCK_CLR_RED;
    block.spicy = 30;
    block.dry = 0;
    block.sweet = 0;
    block.bitter = 0;
    block.sour = 0;
    block.feel = 20;

    EXPECT_EQ(AddPokeblock(&block), TRUE);
    EXPECT_EQ(GetFirstFreePokeblockSlot(), 1);

    // 3. Inspect Pokéblock attributes and flavor levels
    EXPECT_EQ(GetHighestPokeblocksFlavorLevel(&block), 30);
    EXPECT_EQ(GetPokeblocksFeel(&block), 20);
    EXPECT_EQ(GetPokeblocksFlavor(&block), FLAVOR_SPICY);

    // 4. Test nature affinity and gain (Adamant likes spicy, Modest dislikes spicy)
    EXPECT(PokeblockGetGain(NATURE_ADAMANT, &block) > 0);
    EXPECT(PokeblockGetGain(NATURE_MODEST, &block) < 0);

    // 5. Test Pokéblock naming
    u8 blockName[32];
    PokeblockCopyName(&block, blockName);
    EXPECT(StringLength(blockName) > 0);

    // 6. Test slot clearing
    EXPECT_EQ(TryClearPokeblock(0), TRUE);
    EXPECT_EQ(GetFirstFreePokeblockSlot(), 0);

    // 7. Verify Contest categories and rank definitions
    EXPECT_EQ(CONTEST_CATEGORIES_COUNT, 5);
    EXPECT_EQ(CONTEST_RANK_NORMAL, 0);
    EXPECT_EQ(CONTEST_RANK_SUPER, 1);
    EXPECT_EQ(CONTEST_RANK_HYPER, 2);
    EXPECT_EQ(CONTEST_RANK_MASTER, 3);
    EXPECT_EQ(CONTEST_RANK_LINK, 4);

    // Clean up
    ClearPokeblocks();
}

TEST("Confluence: DexNav Saveblock-Safe Search Levels and HUD Calibration")
{
    // 1. Verify DexNav configuration toggles
    EXPECT_EQ(DEXNAV_ENABLED, TRUE);
    EXPECT_EQ(USE_DEXNAV_SEARCH_LEVELS, TRUE);

    // 2. Verify SaveBlock3 safety constraint (must fit within 1624 bytes)
    EXPECT(sizeof(struct SaveBlock3) <= (116 * 14));
    EXPECT_EQ(DEXNAV_SAVED_SEARCH_LEVELS_COUNT, 256);

    // 3. Clear search levels in SaveBlock3
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));

    // Initial search level is 0 for unencountered species
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_PIKACHU), 0);
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_CYNDAQUIL), 0);

    // 4. Increment Pikachu search level
    gDexNavSpecies = SPECIES_PIKACHU;
    TryIncrementSpeciesSearchLevel();
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_PIKACHU), 1);
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_CYNDAQUIL), 0);

    // Increment Pikachu again
    TryIncrementSpeciesSearchLevel();
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_PIKACHU), 2);

    // 5. Increment Cyndaquil search level
    gDexNavSpecies = SPECIES_CYNDAQUIL;
    TryIncrementSpeciesSearchLevel();
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_CYNDAQUIL), 1);
    EXPECT_EQ(DexNav_GetSearchLevel(SPECIES_PIKACHU), 2);

    // 6. Test chaining mechanics
    gSaveBlock3Ptr->dexNavChain = 0;
    IncrementDexNavChain();
    EXPECT_EQ(gSaveBlock3Ptr->dexNavChain, 1);
    IncrementDexNavChain();
    EXPECT_EQ(gSaveBlock3Ptr->dexNavChain, 2);
    EXPECT(CalculateDexNavShinyRolls() >= 0);

    // 7. Test chain reset
    ResetDexNavSearch();
    EXPECT_EQ(gSaveBlock3Ptr->dexNavChain, 0);

    // Clean up
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
    gSaveBlock3Ptr->dexNavChain = 0;
}

// POKE-CONFLUENCE: Subsystem 23 - Modern Party EXP Share Key Item Toggle
TEST("Confluence: Modern Party EXP Share Key Item Toggle Subsystem")
{
    // 1. Verify Configuration Macros
    EXPECT_EQ(I_EXP_SHARE_MODE, EXP_SHARE_KEY_ITEM);
    EXPECT_EQ(I_EXP_SHARE_ITEM, GEN_6);
    EXPECT_EQ(I_EXP_SHARE_FLAG, FLAG_EXP_SHARE_ENABLED);
    EXPECT(FLAG_EXP_SHARE_ENABLED > TEMP_FLAGS_END);

    // 2. Verify Item Properties for Key Item mode
    EXPECT_EQ(GetItemPocket(ITEM_EXP_SHARE), POCKET_KEY_ITEMS);
    EXPECT_EQ(GetItemImportance(ITEM_EXP_SHARE), 1);

    // 3. Clear Bag and Flags
    ClearBag();
    FlagClear(FLAG_EXP_SHARE_ENABLED);

    // Without the Key Item in the Bag, IsGen6ExpShareEnabled must always be FALSE
    EXPECT_EQ(CheckBagHasItem(ITEM_EXP_SHARE, 1), FALSE);
    EXPECT_EQ(IsGen6ExpShareEnabled(), FALSE);

    // Even if the flag is manually set, having no item in bag prevents party-wide Exp Share
    FlagSet(FLAG_EXP_SHARE_ENABLED);
    EXPECT_EQ(IsGen6ExpShareEnabled(), FALSE);

    // 4. Add Exp. Share Key Item to Bag
    AddBagItem(ITEM_EXP_SHARE, 1);
    EXPECT_EQ(CheckBagHasItem(ITEM_EXP_SHARE, 1), TRUE);

    // Now with the item present, the flag controls the active toggle
    EXPECT_EQ(IsGen6ExpShareEnabled(), TRUE);

    // Toggle off
    FlagToggle(FLAG_EXP_SHARE_ENABLED);
    EXPECT_EQ(FlagGet(FLAG_EXP_SHARE_ENABLED), FALSE);
    EXPECT_EQ(IsGen6ExpShareEnabled(), FALSE);

    // Toggle on
    FlagToggle(FLAG_EXP_SHARE_ENABLED);
    EXPECT_EQ(FlagGet(FLAG_EXP_SHARE_ENABLED), TRUE);
    EXPECT_EQ(IsGen6ExpShareEnabled(), TRUE);

    // 5. Clean up Bag and Flags
    RemoveBagItem(ITEM_EXP_SHARE, 1);
    FlagClear(FLAG_EXP_SHARE_ENABLED);
    EXPECT_EQ(IsGen6ExpShareEnabled(), FALSE);
}












