#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "unown.h"
#include "constants/maps.h"
#include "constants/johto_flags.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Ruins of Alph Unown unlock stages (unlocked_unowns.asm)

u8 GetRuinsOfAlphUnownLetter(void)
{
    u8 curGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 curNum = gSaveBlock1Ptr->location.mapNum;
    u8 pool[NUM_UNOWN_FORMS];
    u8 count = 0;
    u8 letter;

    // Only applies to Ruins of Alph Inner Chamber
    if (curGroup != MAP_GROUP(MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER) ||
        curNum != MAP_NUM(MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER))
    {
        return RANDOM_UNOWN_LETTER;
    }

    // Set A-K (letters 1..11) unlocked by Kabuto puzzle
    if (FlagGet(FLAG_JOHTO_SOLVED_KABUTO_PUZZLE))
    {
        for (letter = 1; letter <= 11; letter++)
            pool[count++] = letter;
    }

    // Set L-R (letters 12..18) unlocked by Omanyte puzzle
    if (FlagGet(FLAG_JOHTO_SOLVED_OMANYTE_PUZZLE))
    {
        for (letter = 12; letter <= 18; letter++)
            pool[count++] = letter;
    }

    // Set S-W (letters 19..23) unlocked by Aerodactyl puzzle
    if (FlagGet(FLAG_JOHTO_SOLVED_AERODACTYL_PUZZLE))
    {
        for (letter = 19; letter <= 23; letter++)
            pool[count++] = letter;
    }

    // Set X-Z (letters 24..26) unlocked by Ho-Oh puzzle
    if (FlagGet(FLAG_JOHTO_SOLVED_HO_OH_PUZZLE))
    {
        for (letter = 24; letter <= 26; letter++)
            pool[count++] = letter;
    }

    // When all four puzzles are solved, '?' (27) and '!' (28) are also unlocked
    if (FlagGet(FLAG_JOHTO_SOLVED_KABUTO_PUZZLE) &&
        FlagGet(FLAG_JOHTO_SOLVED_OMANYTE_PUZZLE) &&
        FlagGet(FLAG_JOHTO_SOLVED_AERODACTYL_PUZZLE) &&
        FlagGet(FLAG_JOHTO_SOLVED_HO_OH_PUZZLE))
    {
        pool[count++] = 27; // '?'
        pool[count++] = 28; // '!'
    }

    if (count == 0)
        return RANDOM_UNOWN_LETTER;

    return pool[Random() % count];
}

