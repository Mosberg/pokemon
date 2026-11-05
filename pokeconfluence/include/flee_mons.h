#ifndef GUARD_FLEE_MONS_H
#define GUARD_FLEE_MONS_H

#include "global.h"

// POKE-CONFLUENCE: Authentic GBC Crystal fleeing wild Pokémon tables (flee_mons.asm)
bool8 IsFleeingMon(u16 species);
bool8 TryWildMonFlee(u8 battler);

#endif // GUARD_FLEE_MONS_H

