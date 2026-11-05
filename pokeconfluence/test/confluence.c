#include "global.h"
#include "test/test.h"
#include "test/overworld_script.h"
#include "caps.h"
#include "confluence.h"
#include "data.h"
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
    RemoveBagItem(ITEM_FIELD_KIT, 1);
}

TEST("Confluence: Meridian Station and the Apex Summit arena are Johto maps")
{
    // GetCurrentRegion() tells Johto by map group, so both must sit in the Johto groups
    EXPECT_GE(MAP_GROUP(MAP_JOHTO_MERIDIAN_STATION), MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F));
    EXPECT_GE(MAP_GROUP(MAP_JOHTO_APEX_SUMMIT), MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F));
    EXPECT_NE(MAP_NUM(MAP_JOHTO_MERIDIAN_STATION), MAP_NUM(MAP_JOHTO_APEX_SUMMIT));
}
