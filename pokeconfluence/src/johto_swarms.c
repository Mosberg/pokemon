#include "global.h"
#include "event_data.h"
#include "johto_swarms.h"
#include "random.h"
#include "constants/maps.h"
#include "constants/species.h"
#include "constants/johto_flags.h"

// POKE-CONFLUENCE: Authentic Johto Swarm system (from pokecrystal swarm_grass.asm and swarm_water.asm)

static const struct JohtoSwarmData sJohtoSwarmTable[JOHTO_SWARM_COUNT] =
{
    [JOHTO_SWARM_NONE] = {0},
    [JOHTO_SWARM_DUNSPARCE] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE),
        .mapNum   = MAP_NUM(MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE),
        .species  = SPECIES_DUNSPARCE,
        .minLevel = 3,
        .maxLevel = 4,
        .isWater  = FALSE,
    },
    [JOHTO_SWARM_YANMA] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_35),
        .mapNum   = MAP_NUM(MAP_JOHTO_ROUTE_35),
        .species  = SPECIES_YANMA,
        .minLevel = 12,
        .maxLevel = 14,
        .isWater  = FALSE,
    },
    [JOHTO_SWARM_SNUBBULL] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_38),
        .mapNum   = MAP_NUM(MAP_JOHTO_ROUTE_38),
        .species  = SPECIES_SNUBBULL,
        .minLevel = 13,
        .maxLevel = 16,
        .isWater  = FALSE,
    },
    [JOHTO_SWARM_MARILL] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_34),
        .mapNum   = MAP_NUM(MAP_JOHTO_ROUTE_34),
        .species  = SPECIES_MARILL,
        .minLevel = 12,
        .maxLevel = 14,
        .isWater  = FALSE,
    },
    [JOHTO_SWARM_REMORAID] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_44),
        .mapNum   = MAP_NUM(MAP_JOHTO_ROUTE_44),
        .species  = SPECIES_REMORAID,
        .minLevel = 20,
        .maxLevel = 25,
        .isWater  = TRUE,
    },
    [JOHTO_SWARM_QWILFISH] =
    {
        .mapGroup = MAP_GROUP(MAP_JOHTO_ROUTE_32),
        .mapNum   = MAP_NUM(MAP_JOHTO_ROUTE_32),
        .species  = SPECIES_QWILFISH,
        .minLevel = 15,
        .maxLevel = 20,
        .isWater  = TRUE,
    },
};

u8 Johto_GetActiveSwarm(void)
{
    u16 swarm = VarGet(VAR_JOHTO_ACTIVE_SWARM);
    if (swarm >= JOHTO_SWARM_COUNT)
        return JOHTO_SWARM_NONE;
    return (u8)swarm;
}

void Johto_SetActiveSwarm(u8 swarmId)
{
    if (swarmId < JOHTO_SWARM_COUNT)
        VarSet(VAR_JOHTO_ACTIVE_SWARM, swarmId);
}

void Johto_DailyResetSwarm(void)
{
    // Pick a daily swarm: 1 to 6
    u8 swarm = (Random() % (JOHTO_SWARM_COUNT - 1)) + 1;
    Johto_SetActiveSwarm(swarm);
}

bool8 Johto_TryGetSwarmMon(u16 *species, u8 *minLevel, u8 *maxLevel, bool8 water)
{
    u8 swarmId = Johto_GetActiveSwarm();
    const struct JohtoSwarmData *data;
    u8 curGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 curNum = gSaveBlock1Ptr->location.mapNum;

    if (swarmId == JOHTO_SWARM_NONE || swarmId >= JOHTO_SWARM_COUNT)
        return FALSE;

    data = &sJohtoSwarmTable[swarmId];

    if (data->mapGroup != curGroup || data->mapNum != curNum)
        return FALSE;

    if (data->isWater != water)
        return FALSE;

    // In Crystal, swarms give ~50% encounter chance for the swarming species
    if ((Random() % 100) < 50)
    {
        *species = data->species;
        if (data->maxLevel > data->minLevel)
            *minLevel = data->minLevel + (Random() % (data->maxLevel - data->minLevel + 1));
        else
            *minLevel = data->minLevel;
        *maxLevel = *minLevel;
        return TRUE;
    }

    return FALSE;
}

