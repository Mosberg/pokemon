#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "string_util.h"
#include "unown.h"
#include "constants/maps.h"
#include "constants/johto_flags.h"
#include "constants/species.h"

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

// POKE-CONFLUENCE: Authentic GBC Crystal Unown Dex ancient words (data/pokemon/unown_words.asm)
static const u8 sUnownWordA[] = _("ANGRY");
static const u8 sUnownWordB[] = _("BEAR");
static const u8 sUnownWordC[] = _("CHASE");
static const u8 sUnownWordD[] = _("DIRECT");
static const u8 sUnownWordE[] = _("ENGAGE");
static const u8 sUnownWordF[] = _("FIND");
static const u8 sUnownWordG[] = _("GIVE");
static const u8 sUnownWordH[] = _("HELP");
static const u8 sUnownWordI[] = _("INCREASE");
static const u8 sUnownWordJ[] = _("JOIN");
static const u8 sUnownWordK[] = _("KEEP");
static const u8 sUnownWordL[] = _("LAUGH");
static const u8 sUnownWordM[] = _("MAKE");
static const u8 sUnownWordN[] = _("NUZZLE");
static const u8 sUnownWordO[] = _("OBSERVE");
static const u8 sUnownWordP[] = _("PERFORM");
static const u8 sUnownWordQ[] = _("QUICKEN");
static const u8 sUnownWordR[] = _("REASSURE");
static const u8 sUnownWordS[] = _("SEARCH");
static const u8 sUnownWordT[] = _("TELL");
static const u8 sUnownWordU[] = _("UNDO");
static const u8 sUnownWordV[] = _("VANISH");
static const u8 sUnownWordW[] = _("WANT");
static const u8 sUnownWordX[] = _("XXXXX");
static const u8 sUnownWordY[] = _("YIELD");
static const u8 sUnownWordZ[] = _("ZOOM");
static const u8 sUnownWordExclamation[] = _("!!!!");
static const u8 sUnownWordQuestion[] = _("????");

static const u8 *const sUnownWords[NUM_UNOWN_FORMS] = {
    sUnownWordA,
    sUnownWordB,
    sUnownWordC,
    sUnownWordD,
    sUnownWordE,
    sUnownWordF,
    sUnownWordG,
    sUnownWordH,
    sUnownWordI,
    sUnownWordJ,
    sUnownWordK,
    sUnownWordL,
    sUnownWordM,
    sUnownWordN,
    sUnownWordO,
    sUnownWordP,
    sUnownWordQ,
    sUnownWordR,
    sUnownWordS,
    sUnownWordT,
    sUnownWordU,
    sUnownWordV,
    sUnownWordW,
    sUnownWordX,
    sUnownWordY,
    sUnownWordZ,
    sUnownWordExclamation,
    sUnownWordQuestion,
};

void Johto_RegisterCaughtUnownForm(u8 form)
{
    u16 lower, upper;
    if (form >= NUM_UNOWN_FORMS)
        return;
    lower = VarGet(VAR_JOHTO_UNOWN_CAUGHT_LOWER);
    upper = VarGet(VAR_JOHTO_UNOWN_CAUGHT_UPPER);
    if (form < 16)
        lower |= (1 << form);
    else
        upper |= (1 << (form - 16));
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_LOWER, lower);
    VarSet(VAR_JOHTO_UNOWN_CAUGHT_UPPER, upper);
}

bool8 Johto_IsUnownFormCaught(u8 form)
{
    u16 lower, upper;
    if (form >= NUM_UNOWN_FORMS)
        return FALSE;
    if (form < 16)
    {
        lower = VarGet(VAR_JOHTO_UNOWN_CAUGHT_LOWER);
        return (lower & (1 << form)) != 0;
    }
    else
    {
        upper = VarGet(VAR_JOHTO_UNOWN_CAUGHT_UPPER);
        return (upper & (1 << (form - 16))) != 0;
    }
}

u8 Johto_GetUnownCaughtCount(void)
{
    u32 mask = ((u32)VarGet(VAR_JOHTO_UNOWN_CAUGHT_UPPER) << 16) | VarGet(VAR_JOHTO_UNOWN_CAUGHT_LOWER);
    return __builtin_popcount(mask & 0x0FFFFFFF);
}

u8 Johto_GetNthCaughtUnownForm(u8 index)
{
    u8 form, count = 0;
    for (form = 0; form < NUM_UNOWN_FORMS; form++)
    {
        if (Johto_IsUnownFormCaught(form))
        {
            if (count == index)
                return form;
            count++;
        }
    }
    return 0;
}

const u8 *Johto_GetUnownWord(u8 form)
{
    if (form >= NUM_UNOWN_FORMS)
        return sUnownWords[0];
    return sUnownWords[form];
}

enum Species Johto_GetUnownSpeciesByForm(u8 form)
{
    if (form == 0)
        return SPECIES_UNOWN;
    if (form <= 25)
        return SPECIES_UNOWN_B + (form - 1);
    if (form == 26)
        return SPECIES_UNOWN_EXCLAMATION;
    if (form == 27)
        return SPECIES_UNOWN_QUESTION;
    return SPECIES_UNOWN;
}

u8 Johto_GetUnownCharByForm(u8 form)
{
    if (form <= 25)
        return 'A' + form;
    if (form == 26)
        return '!';
    if (form == 27)
        return '?';
    return '?';
}


