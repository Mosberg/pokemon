#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "headbutt.h"
#include "item.h"
#include "party_menu.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"
#include "wild_encounter.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/moves.h"
#include "constants/species.h"

// POKE-CONFLUENCE: Authentic Johto Headbutt Tree encounter system (from pokecrystal)

struct TreeMonSlot
{
    u16 species;
    u8 level;
};

struct TreeMonTable
{
    struct TreeMonSlot common[6];
    struct TreeMonSlot rare[6];
};

static const struct TreeMonTable sTreeMonTables[] =
{
    [TREEMON_SET_NONE] =
    {
        .common = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
        .rare   = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    },
    [TREEMON_SET_CANYON] =
    {
        .common =
        {
            { SPECIES_SPEAROW,  10 }, // 50%
            { SPECIES_SPEAROW,  10 }, // 15%
            { SPECIES_SPEAROW,  10 }, // 15%
            { SPECIES_AIPOM,    10 }, // 10%
            { SPECIES_AIPOM,    10 }, // 5%
            { SPECIES_AIPOM,    10 }, // 5%
        },
        .rare =
        {
            { SPECIES_SPEAROW,  10 }, // 50%
            { SPECIES_HERACROSS,10 }, // 15%
            { SPECIES_HERACROSS,10 }, // 15%
            { SPECIES_AIPOM,    10 }, // 10%
            { SPECIES_AIPOM,    10 }, // 5%
            { SPECIES_AIPOM,    10 }, // 5%
        },
    },
    [TREEMON_SET_TOWN] =
    {
        .common =
        {
            { SPECIES_SPEAROW,  10 }, // 50%
            { SPECIES_EKANS,    10 }, // 15%
            { SPECIES_SPEAROW,  10 }, // 15%
            { SPECIES_AIPOM,    10 }, // 10%
            { SPECIES_AIPOM,    10 }, // 5%
            { SPECIES_AIPOM,    10 }, // 5%
        },
        .rare =
        {
            { SPECIES_SPEAROW,  10 }, // 50%
            { SPECIES_HERACROSS,10 }, // 15%
            { SPECIES_HERACROSS,10 }, // 15%
            { SPECIES_AIPOM,    10 }, // 10%
            { SPECIES_AIPOM,    10 }, // 5%
            { SPECIES_AIPOM,    10 }, // 5%
        },
    },
    [TREEMON_SET_ROUTE] =
    {
        .common =
        {
            { SPECIES_HOOTHOOT, 10 }, // 50%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_LEDYBA,   10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
        .rare =
        {
            { SPECIES_HOOTHOOT, 10 }, // 50%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_LEDYBA,   10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
    },
    [TREEMON_SET_KANTO] =
    {
        .common =
        {
            { SPECIES_HOOTHOOT, 10 }, // 50%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_LEDYBA,   10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
        .rare =
        {
            { SPECIES_HOOTHOOT, 10 }, // 50%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_LEDYBA,   10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
    },
    [TREEMON_SET_LAKE] =
    {
        .common =
        {
            { SPECIES_VENONAT,  10 }, // 50%
            { SPECIES_HOOTHOOT, 10 }, // 15%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
        .rare =
        {
            { SPECIES_VENONAT,  10 }, // 50%
            { SPECIES_HOOTHOOT, 10 }, // 15%
            { SPECIES_SPINARAK, 10 }, // 15%
            { SPECIES_EXEGGCUTE,10 }, // 10%
            { SPECIES_PINECO,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
    },
    [TREEMON_SET_FOREST] =
    {
        .common =
        {
            { SPECIES_NOCTOWL,  10 }, // 50%
            { SPECIES_CATERPIE, 10 }, // 15%
            { SPECIES_WEEDLE,   10 }, // 15%
            { SPECIES_METAPOD,  10 }, // 10%
            { SPECIES_KAKUNA,   10 }, // 5%
            { SPECIES_PINECO,   10 }, // 5%
        },
        .rare =
        {
            { SPECIES_NOCTOWL,   10 }, // 50%
            { SPECIES_BUTTERFREE,10 }, // 15%
            { SPECIES_BEEDRILL,  10 }, // 15%
            { SPECIES_METAPOD,   10 }, // 10%
            { SPECIES_KAKUNA,    10 }, // 5%
            { SPECIES_PINECO,    10 }, // 5%
        },
    },
    [TREEMON_SET_ROCK] =
    {
        .common =
        {
            { SPECIES_GEODUDE,  10 }, // 50%
            { SPECIES_GEODUDE,  10 }, // 15%
            { SPECIES_GEODUDE,  10 }, // 15%
            { SPECIES_SHUCKLE,  10 }, // 10%
            { SPECIES_SHUCKLE,  10 }, // 5%
            { SPECIES_SHUCKLE,  10 }, // 5%
        },
        .rare =
        {
            { SPECIES_GEODUDE,  10 }, // 50%
            { SPECIES_GEODUDE,  10 }, // 15%
            { SPECIES_GEODUDE,  10 }, // 15%
            { SPECIES_SHUCKLE,  10 }, // 10%
            { SPECIES_SHUCKLE,  10 }, // 5%
            { SPECIES_SHUCKLE,  10 }, // 5%
        },
    },
};

struct MapTreeMonSet
{
    u8 mapGroup;
    u8 mapNum;
    u8 set;
};

static const struct MapTreeMonSet sMapTreeMonSets[] =
{
    { MAP_GROUP(MAP_JOHTO_ROUTE_26), MAP_NUM(MAP_JOHTO_ROUTE_26), TREEMON_SET_KANTO },
    { MAP_GROUP(MAP_JOHTO_ROUTE_27), MAP_NUM(MAP_JOHTO_ROUTE_27), TREEMON_SET_KANTO },
    { MAP_GROUP(MAP_JOHTO_ROUTE_29), MAP_NUM(MAP_JOHTO_ROUTE_29), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_30), MAP_NUM(MAP_JOHTO_ROUTE_30), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_31), MAP_NUM(MAP_JOHTO_ROUTE_31), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_32), MAP_NUM(MAP_JOHTO_ROUTE_32), TREEMON_SET_KANTO },
    { MAP_GROUP(MAP_JOHTO_ROUTE_33), MAP_NUM(MAP_JOHTO_ROUTE_33), TREEMON_SET_TOWN },
    { MAP_GROUP(MAP_JOHTO_ROUTE_34), MAP_NUM(MAP_JOHTO_ROUTE_34), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_35), MAP_NUM(MAP_JOHTO_ROUTE_35), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_36), MAP_NUM(MAP_JOHTO_ROUTE_36), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_37), MAP_NUM(MAP_JOHTO_ROUTE_37), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_38), MAP_NUM(MAP_JOHTO_ROUTE_38), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_39), MAP_NUM(MAP_JOHTO_ROUTE_39), TREEMON_SET_ROUTE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_42), MAP_NUM(MAP_JOHTO_ROUTE_42), TREEMON_SET_TOWN },
    { MAP_GROUP(MAP_JOHTO_ROUTE_43), MAP_NUM(MAP_JOHTO_ROUTE_43), TREEMON_SET_LAKE },
    { MAP_GROUP(MAP_JOHTO_ROUTE_44), MAP_NUM(MAP_JOHTO_ROUTE_44), TREEMON_SET_CANYON },
    { MAP_GROUP(MAP_JOHTO_ROUTE_45), MAP_NUM(MAP_JOHTO_ROUTE_45), TREEMON_SET_CANYON },
    { MAP_GROUP(MAP_JOHTO_ROUTE_46), MAP_NUM(MAP_JOHTO_ROUTE_46), TREEMON_SET_CANYON },
    { MAP_GROUP(MAP_JOHTO_AZALEA_TOWN), MAP_NUM(MAP_JOHTO_AZALEA_TOWN), TREEMON_SET_TOWN },
    { MAP_GROUP(MAP_JOHTO_LAKE_OF_RAGE), MAP_NUM(MAP_JOHTO_LAKE_OF_RAGE), TREEMON_SET_LAKE },
    { MAP_GROUP(MAP_JOHTO_ILEX_FOREST), MAP_NUM(MAP_JOHTO_ILEX_FOREST), TREEMON_SET_FOREST },
    { MAP_GROUP(MAP_JOHTO_CIANWOOD_CITY), MAP_NUM(MAP_JOHTO_CIANWOOD_CITY), TREEMON_SET_ROCK },
    { MAP_GROUP(MAP_JOHTO_ROUTE_40), MAP_NUM(MAP_JOHTO_ROUTE_40), TREEMON_SET_ROCK },
    { MAP_GROUP(MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE), MAP_NUM(MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE), TREEMON_SET_ROCK },
    { MAP_GROUP(MAP_JOHTO_SLOWPOKE_WELL_B1F), MAP_NUM(MAP_JOHTO_SLOWPOKE_WELL_B1F), TREEMON_SET_ROCK },
};

enum TreeMonSet GetCurrentMapTreeMonSet(void)
{
    u32 i;
    u8 curGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 curNum = gSaveBlock1Ptr->location.mapNum;

    for (i = 0; i < ARRAY_COUNT(sMapTreeMonSets); i++)
    {
        if (sMapTreeMonSets[i].mapGroup == curGroup && sMapTreeMonSets[i].mapNum == curNum)
            return sMapTreeMonSets[i].set;
    }
    return TREEMON_SET_NONE;
}

// Diurnal Pokémon fall asleep at night; nocturnal Pokémon sleep during morning/day
bool8 CheckSleepingTreeMon(u16 species, enum TimeOfDay timeOfDay)
{
    if (timeOfDay == TIME_NIGHT)
    {
        switch (species)
        {
        case SPECIES_CATERPIE:
        case SPECIES_METAPOD:
        case SPECIES_BUTTERFREE:
        case SPECIES_WEEDLE:
        case SPECIES_KAKUNA:
        case SPECIES_BEEDRILL:
        case SPECIES_SPEAROW:
        case SPECIES_EKANS:
        case SPECIES_EXEGGCUTE:
        case SPECIES_LEDYBA:
        case SPECIES_AIPOM:
            return TRUE;
        default:
            return FALSE;
        }
    }
    else
    {
        switch (species)
        {
        case SPECIES_VENONAT:
        case SPECIES_HOOTHOOT:
        case SPECIES_NOCTOWL:
        case SPECIES_SPINARAK:
        case SPECIES_HERACROSS:
            return TRUE;
        default:
            return FALSE;
        }
    }
}

static u8 PickTreeMonSlot(void)
{
    u16 roll = Random() % 100;
    if (roll < 50)
        return 0; // 50%
    else if (roll < 65)
        return 1; // 15%
    else if (roll < 80)
        return 2; // 15%
    else if (roll < 90)
        return 3; // 10%
    else if (roll < 95)
        return 4; // 5%
    else
        return 5; // 5%
}

void JohtoHeadbuttWildEncounter(void)
{
    enum TreeMonSet set = GetCurrentMapTreeMonSet();
    const struct TreeMonSlot *slot;
    u16 roll;
    u8 slotIdx;
    u16 species;
    u8 level;

    if (set == TREEMON_SET_NONE || set >= TREEMON_SET_COUNT)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    // 50% chance nothing drops out of the tree
    roll = Random() % 100;
    if (roll < 50)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    slotIdx = PickTreeMonSlot();
    // 35% chance common table (50..84), 15% chance rare table (85..99)
    if (roll < 85)
        slot = &sTreeMonTables[set].common[slotIdx];
    else
        slot = &sTreeMonTables[set].rare[slotIdx];

    species = slot->species;
    level = slot->level;

    if (species == SPECIES_NONE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    CreateWildMon(species, level);

    // Apply sleep status if sleeping mon for current time of day
    if (CheckSleepingTreeMon(species, GenConfigTimeOfDay(GetTimeOfDay())))
    {
        u32 sleepStatus = (Random() % 3) + 2; // 2-4 sleep turns
        SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_STATUS, &sleepStatus);
    }

    BattleSetup_StartWildBattle();
    gSpecialVar_Result = TRUE;
}

// POKE-CONFLUENCE: Check if party has a Pokémon that can use Headbutt
void JohtoCheckHeadbuttUser(void)
{
    u32 i;
    gSpecialVar_Result = PARTY_SIZE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
        if (!GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG)
         && MonKnowsMove(&gParties[B_TRAINER_PLAYER][i], MOVE_HEADBUTT))
        {
            gSpecialVar_Result = i;
            gSpecialVar_0x8004 = i;
            return;
        }
    }

    if (CheckBagHasItem(ITEM_FIELD_KIT, 1))
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_NONE)
                break;
            if (!GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
            {
                gSpecialVar_Result = i;
                gSpecialVar_0x8004 = i;
                return;
            }
        }
    }
}
