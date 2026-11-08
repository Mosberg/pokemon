#include "global.h"
#include "regions.h"
#include "event_data.h"
#include "pokemon.h"


static const u16 sKantoSubregionMapsecs[KANTO_SUBREGION_COUNT][30] = {
    [KANTO_SUBREGION_KANTO] =
    {
        MAPSEC_NONE
    },
    [KANTO_SUBREGION_SEVII123] =
    {
        MAPSEC_ONE_ISLAND,
        MAPSEC_TWO_ISLAND,
        MAPSEC_THREE_ISLAND,
        MAPSEC_KINDLE_ROAD,
        MAPSEC_TREASURE_BEACH,
        MAPSEC_CAPE_BRINK,
        MAPSEC_BOND_BRIDGE,
        MAPSEC_THREE_ISLE_PORT,
        MAPSEC_MT_EMBER,
        MAPSEC_BERRY_FOREST,
        MAPSEC_THREE_ISLE_PATH,
        MAPSEC_EMBER_SPA,
        MAPSEC_NONE
    },
    [KANTO_SUBREGION_SEVII45] =
    {
        MAPSEC_FOUR_ISLAND,
        MAPSEC_FIVE_ISLAND,
        MAPSEC_RESORT_GORGEOUS,
        MAPSEC_WATER_LABYRINTH,
        MAPSEC_FIVE_ISLE_MEADOW,
        MAPSEC_MEMORIAL_PILLAR,
        MAPSEC_NAVEL_ROCK_FRLG,
        MAPSEC_ICEFALL_CAVE,
        MAPSEC_ROCKET_WAREHOUSE,
        MAPSEC_LOST_CAVE,
        MAPSEC_NONE
    },
    [KANTO_SUBREGION_SEVII67] =
    {
        MAPSEC_SEVEN_ISLAND,
        MAPSEC_SIX_ISLAND,
        MAPSEC_OUTCAST_ISLAND,
        MAPSEC_GREEN_PATH,
        MAPSEC_WATER_PATH,
        MAPSEC_RUIN_VALLEY,
        MAPSEC_TRAINER_TOWER,
        MAPSEC_CANYON_ENTRANCE,
        MAPSEC_SEVAULT_CANYON,
        MAPSEC_TANOBY_RUINS,
        MAPSEC_SEVII_ISLE_22,
        MAPSEC_SEVII_ISLE_23,
        MAPSEC_SEVII_ISLE_24,
        MAPSEC_TRAINER_TOWER_2,
        MAPSEC_DOTTED_HOLE,
        MAPSEC_PATTERN_BUSH,
        MAPSEC_ALTERING_CAVE_FRLG,
        MAPSEC_TANOBY_CHAMBERS,
        MAPSEC_TANOBY_KEY,
        MAPSEC_BIRTH_ISLAND_FRLG,
        MAPSEC_MONEAN_CHAMBER,
        MAPSEC_LIPTOO_CHAMBER,
        MAPSEC_WEEPTH_CHAMBER,
        MAPSEC_DILFORD_CHAMBER,
        MAPSEC_SCUFIB_CHAMBER,
        MAPSEC_RIXY_CHAMBER,
        MAPSEC_VIAPOIS_CHAMBER,
        MAPSEC_NONE
    }
};

static const u16 sJohtoBadgeFlags[8] =
{
    FLAG_JOHTO_ENGINE_ZEPHYRBADGE,
    FLAG_JOHTO_ENGINE_HIVEBADGE,
    FLAG_JOHTO_ENGINE_PLAINBADGE,
    FLAG_JOHTO_ENGINE_FOGBADGE,
    FLAG_JOHTO_ENGINE_STORMBADGE,
    FLAG_JOHTO_ENGINE_MINERALBADGE,
    FLAG_JOHTO_ENGINE_GLACIERBADGE,
    FLAG_JOHTO_ENGINE_RISINGBADGE,
};

u16 GetBadgeFlagForRegion(enum Region region, u32 index)
{
    if (index >= 8)
        return 0;

    switch (region)
    {
    case REGION_JOHTO:
        return sJohtoBadgeFlags[index];
    case REGION_KANTO:
        return FLAG_BADGE09_GET + index;
    default:
        return FLAG_BADGE01_GET + index;
    }
}

enum KantoSubRegion GetKantoSubregion(u32 mapSecId)
{
    for (u32 i = KANTO_SUBREGION_KANTO; i <= KANTO_SUBREGION_SEVII67; i++)
    {
        for (u32 j = 0; sKantoSubregionMapsecs[i][j] != MAPSEC_NONE; j++)
        {
            if (mapSecId == sKantoSubregionMapsecs[i][j])
                return i;
        }
    }
    return KANTO_SUBREGION_KANTO;
}

// Crystal's GetFirstPokemonHappiness: VAR_RESULT = friendship of the first party Pokemon.
void JohtoGetFirstMonHappiness(void)
{
    if (gPlayerPartyCount == 0)
    {
        gSpecialVar_Result = 0;
        return;
    }
    gSpecialVar_Result = GetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP);
}
