#include "global.h"
#include "confluence.h"
#include "data.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "pokedex.h"
#include "random.h"
#include "regions.h"
#include "string_util.h"
#include "constants/battle.h"
#include "constants/field_move.h"
#include "constants/johto_flags.h"
#include "constants/map_types.h"
#include "constants/species.h"
#include "constants/weather.h"

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

static u32 GetBadgeTableCap(u32 badges)
{
    if (badges > CONFLUENCE_TOTAL_BADGES)
        badges = CONFLUENCE_TOTAL_BADGES;
    return sBadgeLevelCaps[badges];
}

u32 Confluence_GetLevelCapForBadges(u32 badges)
{
    if (FlagGet(FLAG_CONFLUENCE_APEX_CHAMPION))
        return MAX_LEVEL;
    return GetBadgeTableCap(badges);
}

u32 Confluence_GetTrainerLevelBoost(const struct Trainer *trainer)
{
    u32 i, highest = 0, target;

    switch (trainer->trainerClass)
    {
    case TRAINER_CLASS_LEADER:
    case TRAINER_CLASS_LEADER_FRLG:
    case TRAINER_CLASS_ELITE_FOUR:
    case TRAINER_CLASS_ELITE_FOUR_FRLG:
    case TRAINER_CLASS_CHAMPION:
    case TRAINER_CLASS_CHAMPION_FRLG:
        break;
    default:
        return 0;
    }
    if (trainer->party == NULL)
        return 0;

    for (i = 0; i < trainer->partySize; i++)
    {
        if (trainer->party[i].lvl > highest)
            highest = trainer->party[i].lvl;
    }
	if (gMapHeader.regionMapSectionId == MAPSEC_JOHTO_APEX_SUMMIT || FlagGet(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE))
		target = MAX_LEVEL;
	else
		target = GetBadgeTableCap(Confluence_CountBadges());
	return target > highest ? target - highest : 0;
}

// The legends that keep a region's Resonance going: its three Birds, Beasts or Titans.
static bool32 IsRegionResonanceCalmed(enum Region region)
{
    u32 first = region == REGION_KANTO ? 0 : region == REGION_JOHTO ? 3 : 6;
    u32 i;

    for (i = first; i < first + 3; i++)
    {
        if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(sResonanceSpecies[i]), FLAG_GET_CAUGHT))
            return FALSE;
    }
    return TRUE;
}

// Once the Meridian line is open the Convergence Crisis starts: outdoors, a region whose legends are not all calmed
// gets its own anomaly (Kanto storms, Johto fog, Hoenn downpours) in place of clear weather, until the chairman is beaten.
enum OverworldWeather Confluence_GetAnomalyWeather(enum OverworldWeather weather)
{
    enum Region region;

    if (weather != WEATHER_NONE && weather != WEATHER_SUNNY_CLOUDS && weather != WEATHER_SUNNY)
        return weather;
    if (gMapHeader.mapType != MAP_TYPE_TOWN && gMapHeader.mapType != MAP_TYPE_CITY
     && gMapHeader.mapType != MAP_TYPE_ROUTE && gMapHeader.mapType != MAP_TYPE_OCEAN_ROUTE)
        return weather;
    if (FlagGet(FLAG_CONFLUENCE_CRISIS_RESOLVED) || Confluence_CountBadges() < CONFLUENCE_MERIDIAN_MIN_BADGES)
        return weather;

    region = GetCurrentRegion();
    if (IsRegionResonanceCalmed(region))
        return weather;

    switch (region)
    {
    case REGION_KANTO:
        return WEATHER_RAIN_THUNDERSTORM;
    case REGION_JOHTO:
        return WEATHER_FOG_HORIZONTAL;
    default:
        return WEATHER_DOWNPOUR;
    }
}

static bool32 IsHmFieldMove(enum FieldMove fieldMove)
{
    switch (fieldMove)
    {
    case FIELD_MOVE_CUT:
    case FIELD_MOVE_ROCK_SMASH:
    case FIELD_MOVE_STRENGTH:
    case FIELD_MOVE_SURF:
    case FIELD_MOVE_WATERFALL:
    case FIELD_MOVE_DIVE:
    case FIELD_MOVE_ROCK_CLIMB:
        return TRUE;
    default:
        return FALSE;
    }
}

// Party slot that performs a field move for the Field Kit: the first Pokemon that is not an egg, or PARTY_SIZE.
u32 Confluence_GetFieldKitMon(enum FieldMove fieldMove)
{
    u32 i;

    if (!IsHmFieldMove(fieldMove) || !CheckBagHasItem(ITEM_FIELD_KIT, 1))
        return PARTY_SIZE;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
        if (!GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
            return i;
    }
    return PARTY_SIZE;
}

bool32 Confluence_IsFieldKitSlot(u32 slot)
{
    return slot < PARTY_SIZE && Confluence_GetFieldKitMon(FIELD_MOVE_CUT) == slot;
}

// Party menu order: the water moves first, then the travel moves and the rest. Every entry works for the Kit mon.
enum FieldMove Confluence_GetFieldKitMoveByIndex(u32 index)
{
    static const u8 sFieldKitMoves[] =
    {
        FIELD_MOVE_SURF, FIELD_MOVE_FLY, FIELD_MOVE_FLASH, FIELD_MOVE_DIG,
        FIELD_MOVE_TELEPORT, FIELD_MOVE_DIVE, FIELD_MOVE_WATERFALL,
    };

    return index < ARRAY_COUNT(sFieldKitMoves) ? sFieldKitMoves[index] : FIELD_MOVES_COUNT;
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

// POKE-CONFLUENCE: Authentic GBC Crystal Shuckle Berry Juice fermentation
void Johto_ConvertShuckleBerryJuice(void)
{
    u8 i;
    u16 heldItem;

    // In Crystal: requires having reached Goldenrod City at least once
    if (!FlagGet(FLAG_JOHTO_ENGINE_REACHED_GOLDENROD))
        return;

    // 1 in 16 chance (6.25%) after a wild battle
    if ((Random() % 16) != 0)
        return;

    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
            continue;

        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_SHUCKLE)
        {
            heldItem = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HELD_ITEM);
            if (heldItem == ITEM_ORAN_BERRY)
            {
                u16 juice = ITEM_BERRY_JUICE;
                SetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HELD_ITEM, &juice);
                break;
            }
        }
    }
}
