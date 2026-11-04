#include "global.h"
#include "confluence.h"
#include "event_data.h"
#include "pokedex.h"
#include "regions.h"
#include "string_util.h"
#include "constants/species.h"

// Level cap by number of badges, whatever their region. 8 badges match a classic gym run, 24 match the Apex Summit.
static const u8 sBadgeLevelCaps[CONFLUENCE_TOTAL_BADGES + 1] =
{
    15, 19, 24, 28, 32, 36, 40, 44, 48,
    50, 52, 54, 56, 58, 60, 62, 64,
    66, 68, 70, 72, 74, 76, 78, 80,
};

static const u16 sResonanceSpecies[CONFLUENCE_RESONANCE_COUNT] =
{
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
    SPECIES_SUICUNE,
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
};

u32 Confluence_CountBadges(void)
{
    u32 count = 0;
    u32 region, i;
    static const enum Region regions[CONFLUENCE_REGION_COUNT] = { REGION_KANTO, REGION_JOHTO, REGION_HOENN };

    for (region = 0; region < CONFLUENCE_REGION_COUNT; region++)
    {
        for (i = 0; i < CONFLUENCE_BADGES_PER_REGION; i++)
        {
            if (FlagGet(GetBadgeFlagForRegion(regions[region], i)))
                count++;
        }
    }
    return count;
}

u32 Confluence_CountResonanceCalmed(void)
{
    u32 i, count = 0;

    for (i = 0; i < CONFLUENCE_RESONANCE_COUNT; i++)
    {
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(sResonanceSpecies[i]), FLAG_GET_CAUGHT))
            count++;
    }
    return count;
}

u32 Confluence_GetLevelCapForBadges(u32 badges)
{
    if (FlagGet(FLAG_CONFLUENCE_APEX_CHAMPION))
        return MAX_LEVEL;
    if (badges > CONFLUENCE_TOTAL_BADGES)
        badges = CONFLUENCE_TOTAL_BADGES;
    return sBadgeLevelCaps[badges];
}

// VAR_RESULT = badges across all three regions.
void ConfluenceCountBadges(void)
{
    gSpecialVar_Result = Confluence_CountBadges();
}

// VAR_RESULT = Resonance legends already calmed and caught.
void ConfluenceCountResonance(void)
{
    gSpecialVar_Result = Confluence_CountResonanceCalmed();
}

// VAR_RESULT is TRUE when the player may board the Meridian line (second badge secured).
void ConfluenceCheckMeridianAccess(void)
{
    gSpecialVar_Result = Confluence_CountBadges() >= CONFLUENCE_MERIDIAN_MIN_BADGES;
}

// VAR_RESULT is TRUE when all 24 badges are held, which is what the Apex Summit warden asks for.
void ConfluenceCheckApexEligible(void)
{
    gSpecialVar_Result = Confluence_CountBadges() >= CONFLUENCE_TOTAL_BADGES;
}

// STR_VAR_1 = badges held, STR_VAR_2 = level cap, STR_VAR_3 = Resonance legends calmed.
void ConfluenceBufferProgress(void)
{
    u32 badges = Confluence_CountBadges();

    ConvertIntToDecimalStringN(gStringVar1, badges, STR_CONV_MODE_LEFT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar2, Confluence_GetLevelCapForBadges(badges), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, Confluence_CountResonanceCalmed(), STR_CONV_MODE_LEFT_ALIGN, 1);
}
