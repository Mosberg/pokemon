#ifndef GUARD_UNOWN_H
#define GUARD_UNOWN_H

#include "global.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Ruins of Alph Unown unlock stages (unlocked_unowns.asm)
u8 GetRuinsOfAlphUnownLetter(void);

// POKE-CONFLUENCE: Authentic GBC Crystal Unown Dex tracker and word lookups
void Johto_RegisterCaughtUnownForm(u8 form);
bool8 Johto_IsUnownFormCaught(u8 form);
u8 Johto_GetUnownCaughtCount(void);
u8 Johto_GetNthCaughtUnownForm(u8 index);
const u8 *Johto_GetUnownWord(u8 form);
enum Species Johto_GetUnownSpeciesByForm(u8 form);
u8 Johto_GetUnownCharByForm(u8 form);

#endif // GUARD_UNOWN_H


