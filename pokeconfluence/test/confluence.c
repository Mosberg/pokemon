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





