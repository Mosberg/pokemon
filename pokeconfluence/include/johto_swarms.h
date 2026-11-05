#ifndef GUARD_JOHTO_SWARMS_H
#define GUARD_JOHTO_SWARMS_H

#include "global.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Pokémon Swarm system
enum JohtoSwarm
{
    JOHTO_SWARM_NONE,
    JOHTO_SWARM_DUNSPARCE,
    JOHTO_SWARM_YANMA,
    JOHTO_SWARM_SNUBBULL,
    JOHTO_SWARM_MARILL,
    JOHTO_SWARM_REMORAID,
    JOHTO_SWARM_QWILFISH,
    JOHTO_SWARM_COUNT
};

struct JohtoSwarmData
{
    u8 mapGroup;
    u8 mapNum;
    u16 species;
    u8 minLevel;
    u8 maxLevel;
    bool8 isWater;
};

u8 Johto_GetActiveSwarm(void);
void Johto_SetActiveSwarm(u8 swarmId);
void Johto_DailyResetSwarm(void);
bool8 Johto_TryGetSwarmMon(u16 *species, u8 *minLevel, u8 *maxLevel, bool8 water);

#endif // GUARD_JOHTO_SWARMS_H

