#include "global.h"
#include "event_data.h"
#include "ow_abilities.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 0
#define ROAMER_MAP_GROUP 0

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

#define ROAMER(index) (&gSaveBlock1Ptr->roamer[index])
EWRAM_DATA static u8 sLocationHistory[ROAMER_COUNT][3][2] = {0};
EWRAM_DATA static u8 sRoamerLocation[ROAMER_COUNT][2] = {0};
EWRAM_DATA u8 gEncounteredRoamerIndex = 0;

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.
static const u8 sRoamerLocations[][6] =
{
    { MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE134), ___ },
    { MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE123) },
    { MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE120), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE121), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE123), ___, ___ },
    { MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE123), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE123), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE118), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), ___, ___ },
    { MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE128), ___, ___ },
    { MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE129), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE130), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE131), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE132), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE133), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE134), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE134), MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE110), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

struct RoamerMapLocation
{
    u8 mapGroup;
    u8 mapNum;
};

#define ROAM_MAP(map) { MAP_GROUP(map), MAP_NUM(map) }
#define ROAM_EMPTY     { 0, MAP_NUM(MAP_UNDEFINED) }

// POKE-CONFLUENCE: Authentic Johto roaming beast route network (from pokecrystal roammon_maps.asm)
static const struct RoamerMapLocation sJohtoRoamerLocations[][6] =
{
    { ROAM_MAP(MAP_JOHTO_ROUTE_29), ROAM_MAP(MAP_JOHTO_ROUTE_30), ROAM_MAP(MAP_JOHTO_ROUTE_46), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_30), ROAM_MAP(MAP_JOHTO_ROUTE_29), ROAM_MAP(MAP_JOHTO_ROUTE_31), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_31), ROAM_MAP(MAP_JOHTO_ROUTE_30), ROAM_MAP(MAP_JOHTO_ROUTE_32), ROAM_MAP(MAP_JOHTO_ROUTE_36), ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_32), ROAM_MAP(MAP_JOHTO_ROUTE_36), ROAM_MAP(MAP_JOHTO_ROUTE_31), ROAM_MAP(MAP_JOHTO_ROUTE_33), ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_33), ROAM_MAP(MAP_JOHTO_ROUTE_32), ROAM_MAP(MAP_JOHTO_ROUTE_34), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_34), ROAM_MAP(MAP_JOHTO_ROUTE_33), ROAM_MAP(MAP_JOHTO_ROUTE_35), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_35), ROAM_MAP(MAP_JOHTO_ROUTE_34), ROAM_MAP(MAP_JOHTO_ROUTE_36), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_36), ROAM_MAP(MAP_JOHTO_ROUTE_35), ROAM_MAP(MAP_JOHTO_ROUTE_31), ROAM_MAP(MAP_JOHTO_ROUTE_32), ROAM_MAP(MAP_JOHTO_ROUTE_37), ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_37), ROAM_MAP(MAP_JOHTO_ROUTE_36), ROAM_MAP(MAP_JOHTO_ROUTE_38), ROAM_MAP(MAP_JOHTO_ROUTE_42), ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_38), ROAM_MAP(MAP_JOHTO_ROUTE_37), ROAM_MAP(MAP_JOHTO_ROUTE_39), ROAM_MAP(MAP_JOHTO_ROUTE_42), ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_39), ROAM_MAP(MAP_JOHTO_ROUTE_38), ROAM_MAP(MAP_JOHTO_ROUTE_37), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_42), ROAM_MAP(MAP_JOHTO_ROUTE_43), ROAM_MAP(MAP_JOHTO_ROUTE_44), ROAM_MAP(MAP_JOHTO_ROUTE_37), ROAM_MAP(MAP_JOHTO_ROUTE_38), ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_43), ROAM_MAP(MAP_JOHTO_ROUTE_42), ROAM_MAP(MAP_JOHTO_ROUTE_44), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_44), ROAM_MAP(MAP_JOHTO_ROUTE_42), ROAM_MAP(MAP_JOHTO_ROUTE_43), ROAM_MAP(MAP_JOHTO_ROUTE_45), ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_45), ROAM_MAP(MAP_JOHTO_ROUTE_44), ROAM_MAP(MAP_JOHTO_ROUTE_46), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_MAP(MAP_JOHTO_ROUTE_46), ROAM_MAP(MAP_JOHTO_ROUTE_45), ROAM_MAP(MAP_JOHTO_ROUTE_29), ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
    { ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY, ROAM_EMPTY },
};

#define NUM_JOHTO_LOCATION_SETS (ARRAY_COUNT(sJohtoRoamerLocations) - 1)

#undef ___
#define NUM_LOCATION_SETS (ARRAY_COUNT(sRoamerLocations) - 1)
#define NUM_LOCATIONS_PER_SET (ARRAY_COUNT(sRoamerLocations[0]))

void DeactivateAllRoamers(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        SetRoamerInactive(i);
}

static void ClearRoamerLocationHistory(u32 roamerIndex)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sLocationHistory[roamerIndex]); i++)
    {
        sLocationHistory[roamerIndex][i][MAP_GRP] = 0;
        sLocationHistory[roamerIndex][i][MAP_NUM] = 0;
    }
}

void MoveAllRoamersToOtherLocationSets(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        RoamerMoveToOtherLocationSet(i);
}

void MoveAllRoamers(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        RoamerMove(i);
}

static bool8 IsJohtoRoamer(u32 roamerIndex)
{
    u16 species = ROAMER(roamerIndex)->species;
    return (species == SPECIES_RAIKOU || species == SPECIES_ENTEI || species == SPECIES_SUICUNE);
}

static void CreateInitialRoamerMon(u8 index, enum Species species, u8 level)
{
    ClearRoamerLocationHistory(index);
    u32 personality = GetMonPersonality(species,
        GetSynchronizedGender(ROAMER_ORIGIN, species),
        GetSynchronizedNature(ROAMER_ORIGIN, species),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gParties[B_TRAINER_OPPONENT_A][0]);
    ROAMER(index)->ivs = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_IVS);
    ROAMER(index)->personality = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_PERSONALITY);
    ROAMER(index)->species = species;
    ROAMER(index)->level = level;
    ROAMER(index)->statusA = 0;
    ROAMER(index)->statusB = 0;
    ROAMER(index)->hp = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_MAX_HP);
    ROAMER(index)->cool = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_COOL);
    ROAMER(index)->beauty = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_BEAUTY);
    ROAMER(index)->cute = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_CUTE);
    ROAMER(index)->smart = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SMART);
    ROAMER(index)->tough = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_TOUGH);
    ROAMER(index)->shiny = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_IS_SHINY);
    ROAMER(index)->active = TRUE;

    if (IsJohtoRoamer(index))
    {
        u8 locSet = Random() % NUM_JOHTO_LOCATION_SETS;
        sRoamerLocation[index][MAP_GRP] = sJohtoRoamerLocations[locSet][0].mapGroup;
        sRoamerLocation[index][MAP_NUM] = sJohtoRoamerLocations[locSet][0].mapNum;
    }
    else
    {
        sRoamerLocation[index][MAP_GRP] = ROAMER_MAP_GROUP;
        sRoamerLocation[index][MAP_NUM] = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
    }
}

static u8 GetFirstInactiveRoamerIndex(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (!ROAMER(i)->active)
            return i;
    }
    return ROAMER_COUNT;
}

bool8 TryAddRoamer(enum Species species, u8 level)
{
    u8 index = GetFirstInactiveRoamerIndex();

    if (index < ROAMER_COUNT)
    {
        // Create the roamer and stop searching
        CreateInitialRoamerMon(index, species, level);
        return TRUE;
    }

    // Maximum active roamers found: do nothing and let the calling function know
    return FALSE;
}

// gSpecialVar_0x8004 here corresponds to the options in the multichoice MULTI_TV_LATI (0 for 'Red', 1 for 'Blue')
void InitRoamer(void)
{
    if (gSpecialVar_0x8004 == 0) // Red
        TryAddRoamer(SPECIES_LATIAS, 40);
    else
        TryAddRoamer(SPECIES_LATIOS, 40);
}

// POKE-CONFLUENCE: Initialize Raikou and Entei to roam Johto (Authentic GBC Crystal Burned Tower event)
void InitJohtoRoamMons(void)
{
    TryAddRoamer(SPECIES_RAIKOU, 40);
    TryAddRoamer(SPECIES_ENTEI, 40);
}

void UpdateLocationHistoryForRoamer(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        sLocationHistory[i][2][MAP_GRP] = sLocationHistory[i][1][MAP_GRP];
        sLocationHistory[i][2][MAP_NUM] = sLocationHistory[i][1][MAP_NUM];

        sLocationHistory[i][1][MAP_GRP] = sLocationHistory[i][0][MAP_GRP];
        sLocationHistory[i][1][MAP_NUM] = sLocationHistory[i][0][MAP_NUM];

        sLocationHistory[i][0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
        sLocationHistory[i][0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
    }
}

void RoamerMoveToOtherLocationSet(u32 roamerIndex)
{
    u8 mapNum = 0;

    if (!ROAMER(roamerIndex)->active)
        return;

    if (IsJohtoRoamer(roamerIndex))
    {
        u8 mapGroup = 0;
        do
        {
            u8 locSet = Random() % NUM_JOHTO_LOCATION_SETS;
            mapGroup = sJohtoRoamerLocations[locSet][0].mapGroup;
            mapNum = sJohtoRoamerLocations[locSet][0].mapNum;
            if (sRoamerLocation[roamerIndex][MAP_GRP] != mapGroup || sRoamerLocation[roamerIndex][MAP_NUM] != mapNum)
            {
                sRoamerLocation[roamerIndex][MAP_GRP] = mapGroup;
                sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
                return;
            }
        } while (sRoamerLocation[roamerIndex][MAP_GRP] == mapGroup && sRoamerLocation[roamerIndex][MAP_NUM] == mapNum);
        sRoamerLocation[roamerIndex][MAP_GRP] = mapGroup;
        sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
    }
    else
    {
        sRoamerLocation[roamerIndex][MAP_GRP] = ROAMER_MAP_GROUP;

        // Choose a location set that starts with a map
        // different from the roamer's current map
        do
        {
            mapNum = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
            if (sRoamerLocation[roamerIndex][MAP_NUM] != mapNum)
            {
                sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
                return;
            }
        } while (sRoamerLocation[roamerIndex][MAP_NUM] == mapNum);
        sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
    }
}

void RoamerMove(u32 roamerIndex)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet(roamerIndex);
    }
    else
    {
        if (!ROAMER(roamerIndex)->active)
            return;

        if (IsJohtoRoamer(roamerIndex))
        {
            while (locSet < NUM_JOHTO_LOCATION_SETS)
            {
                if (sRoamerLocation[roamerIndex][MAP_GRP] == sJohtoRoamerLocations[locSet][0].mapGroup
                 && sRoamerLocation[roamerIndex][MAP_NUM] == sJohtoRoamerLocations[locSet][0].mapNum)
                {
                    u8 validCount = 0;
                    u8 j;
                    for (j = 1; j < 6; j++)
                    {
                        if (sJohtoRoamerLocations[locSet][j].mapNum != (u8)MAP_NUM(MAP_UNDEFINED))
                            validCount++;
                    }
                    if (validCount == 0)
                    {
                        RoamerMoveToOtherLocationSet(roamerIndex);
                        return;
                    }
                    {
                        u8 attempts = 0;
                        do
                        {
                            u8 pick = (Random() % validCount) + 1;
                            u8 mapGroup = sJohtoRoamerLocations[locSet][pick].mapGroup;
                            u8 mapNum = sJohtoRoamerLocations[locSet][pick].mapNum;
                            if ((sLocationHistory[roamerIndex][2][MAP_GRP] != mapGroup
                              || sLocationHistory[roamerIndex][2][MAP_NUM] != mapNum)
                              || attempts > 8)
                            {
                                sRoamerLocation[roamerIndex][MAP_GRP] = mapGroup;
                                sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
                                return;
                            }
                            attempts++;
                        } while (1);
                    }
                }
                locSet++;
            }
            RoamerMoveToOtherLocationSet(roamerIndex);
        }
        else
        {
            while (locSet < NUM_LOCATION_SETS)
            {
                // Find the location set that starts with the roamer's current map
                if (sRoamerLocation[roamerIndex][MAP_NUM] == sRoamerLocations[locSet][0])
                {
                    u8 mapNum;
                    // Choose a new map (excluding the first) within this set
                    // Also exclude a map if the roamer was there 2 moves ago
                    do
                    {
                        mapNum = sRoamerLocations[locSet][(Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1];
                    } while ((sLocationHistory[roamerIndex][2][MAP_GRP] == ROAMER_MAP_GROUP
                            && sLocationHistory[roamerIndex][2][MAP_NUM] == mapNum)
                            || mapNum == MAP_NUM(MAP_UNDEFINED));
                    sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
                    return;
                }
                locSet++;
            }
        }
    }
}

bool8 IsRoamerAt(u32 roamerIndex, u8 mapGroup, u8 mapNum)
{
    if (ROAMER(roamerIndex)->active && mapGroup == sRoamerLocation[roamerIndex][MAP_GRP] && mapNum == sRoamerLocation[roamerIndex][MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(u32 roamerIndex)
{
    u32 status = ROAMER(roamerIndex)->statusA + (ROAMER(roamerIndex)->statusB << 8);
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, ROAMER(roamerIndex)->species, ROAMER(roamerIndex)->level, ROAMER(roamerIndex)->ivs, ROAMER(roamerIndex)->personality);
    SetMonData(mon, MON_DATA_STATUS, &status);
    SetMonData(mon, MON_DATA_HP, &ROAMER(roamerIndex)->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER(roamerIndex)->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER(roamerIndex)->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER(roamerIndex)->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER(roamerIndex)->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER(roamerIndex)->tough);
    SetMonData(mon, MON_DATA_IS_SHINY, &ROAMER(roamerIndex)->shiny);
}

bool8 TryStartRoamerEncounter(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (IsRoamerAt(i, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) == TRUE && (Random() % 4) == 0)
        {
            CreateRoamerMonInstance(i);
            gEncounteredRoamerIndex = i;
            return TRUE;
        }
    }
    return FALSE;
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    u32 status = GetMonData(mon, MON_DATA_STATUS);

    ROAMER(gEncounteredRoamerIndex)->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER(gEncounteredRoamerIndex)->statusA = status;
    ROAMER(gEncounteredRoamerIndex)->statusB = status >> 8;

    RoamerMoveToOtherLocationSet(gEncounteredRoamerIndex);
}

void SetRoamerInactive(u32 roamerIndex)
{
    ROAMER(roamerIndex)->active = FALSE;
}

void GetRoamerLocation(u32 roamerIndex, u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[roamerIndex][MAP_GRP];
    *mapNum = sRoamerLocation[roamerIndex][MAP_NUM];
}
