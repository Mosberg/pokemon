#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "flee_mons.h"
#include "random.h"
#include "constants/species.h"

// POKE-CONFLUENCE: Authentic GBC Crystal flee mons (from pokecrystal flee_mons.asm)

static const u16 sSometimesFleeMons[] =
{
    SPECIES_MAGNEMITE,
    SPECIES_GRIMER,
    SPECIES_TANGELA,
    SPECIES_MR_MIME,
    SPECIES_EEVEE,
    SPECIES_PORYGON,
    SPECIES_DRATINI,
    SPECIES_DRAGONAIR,
    SPECIES_TOGETIC,
    SPECIES_UMBREON,
    SPECIES_UNOWN,
    SPECIES_SNUBBULL,
    SPECIES_HERACROSS,
};

static const u16 sOftenFleeMons[] =
{
    SPECIES_CUBONE,
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
    SPECIES_QUAGSIRE,
    SPECIES_DELIBIRD,
    SPECIES_PHANPY,
    SPECIES_TEDDIURSA,
};

static const u16 sAlwaysFleeMons[] =
{
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
};

bool8 IsFleeingMon(u16 species)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sSometimesFleeMons); i++)
    {
        if (sSometimesFleeMons[i] == species)
            return TRUE;
    }
    for (i = 0; i < ARRAY_COUNT(sOftenFleeMons); i++)
    {
        if (sOftenFleeMons[i] == species)
            return TRUE;
    }
    for (i = 0; i < ARRAY_COUNT(sAlwaysFleeMons); i++)
    {
        if (sAlwaysFleeMons[i] == species)
            return TRUE;
    }
    return FALSE;
}

bool8 TryWildMonFlee(u8 battler)
{
    u16 species;
    u32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        return FALSE;

    if (GetBattlerSide(battler) != B_SIDE_OPPONENT)
        return FALSE;

    if (!CanBattlerEscape(battler))
        return FALSE;

    species = gBattleMons[battler].species;

    for (i = 0; i < ARRAY_COUNT(sAlwaysFleeMons); i++)
    {
        if (sAlwaysFleeMons[i] == species)
            return TRUE;
    }

    for (i = 0; i < ARRAY_COUNT(sOftenFleeMons); i++)
    {
        if (sOftenFleeMons[i] == species)
            return ((Random() % 2) == 0); // 50%
    }

    for (i = 0; i < ARRAY_COUNT(sSometimesFleeMons); i++)
    {
        if (sSometimesFleeMons[i] == species)
            return ((Random() % 10) == 0); // 10%
    }

    return FALSE;
}

