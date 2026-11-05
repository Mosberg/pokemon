#include "global.h"
#include "rtc.h"
#include "event_data.h"
#include "overworld.h"
#include "region_map.h"
#include "regions.h"
#include "new_game.h"
#include "pokemon.h"
#include "string_util.h"
#include "coins.h"
#include "item.h"
#include "pokedex.h"
#include "battle.h"
#include "random.h"
#include "daycare.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/johto_flags.h"

// Crystal's time-of-day slots: MORN 4-9, DAY 10-17, NITE 18-3. VAR_0x8004 holds a mask (1 MORN, 2 DAY, 4 NITE);
// VAR_RESULT is TRUE when the current slot is one of them.
void JohtoCheckTime(void)
{
    u16 mask = gSpecialVar_0x8004;
    u8 hour;
    u8 slot;

    RtcCalcLocalTime();
    hour = gLocalTime.hours;
    if (hour >= 4 && hour < 10)
        slot = 1;
    else if (hour >= 10 && hour < 18)
        slot = 2;
    else
        slot = 4;
    gSpecialVar_Result = (mask & slot) != 0;
}

// Crystal's VAR_WEEKDAY: 0 = Sunday ... 6 = Saturday.
void JohtoGetWeekday(void)
{
    gSpecialVar_Result = GetDayOfWeek();
}

// POKE-CONFLUENCE
// Calibrate/sync RTC with cartridge hardware. If cartridge RTC is healthy, returns 1 in VAR_RESULT.
// If RTC error status indicates power loss/dry battery/invalid time, returns 0.
void JohtoSyncRtcTime(void)
{
    RtcInit();
    RtcCalcLocalTime();
    gSpecialVar_Result = (RtcGetErrorStatus() == 0);
}

// POKE-CONFLUENCE
// Sets the current weekday (0 = Sunday ... 6 = Saturday) based on gSpecialVar_0x8004.
// Adjusts localTimeOffset days so that GetDayOfWeek() returns the chosen weekday.
void JohtoSetWeekday(void)
{
    u8 targetWeekday = gSpecialVar_0x8004 % WEEKDAY_COUNT;
    u8 currentWeekday;
    s32 dayDiff;

    RtcCalcLocalTime();
    currentWeekday = GetDayOfWeek();
    dayDiff = (targetWeekday - currentWeekday + 7) % 7;

    RtcCalcLocalTimeOffset(gLocalTime.days + dayDiff, gLocalTime.hours, gLocalTime.minutes, gLocalTime.seconds);
    RtcCalcLocalTime();
    gSpecialVar_Result = GetDayOfWeek();
}

// Crystal's VAR_HOUR: 0 .. 23.
void JohtoGetHour(void)
{
    RtcCalcLocalTime();
    gSpecialVar_Result = gLocalTime.hours;
}

// Goldenrod Underground Haircut Brothers & Daisy's Grooming: boosts lead mon friendship and returns 3.
void JohtoHaircut(void)
{
    struct Pokemon *mon;
    u32 friendship;

    if (gPlayerPartyCount == 0)
    {
        gSpecialVar_Result = 0;
        return;
    }
    mon = &gPlayerParty[0];
    friendship = GetMonData(mon, MON_DATA_FRIENDSHIP) + 10;
    if (friendship > MAX_FRIENDSHIP)
        friendship = MAX_FRIENDSHIP;
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
    StringGet_Nickname(gStringVar1);
    gSpecialVar_Result = 3;
}

// Bill's Grandfather: checks if any party mon matches VAR_0x8004 (target species); returns that species in VAR_RESULT if found.
void JohtoBillsGrandfather(void)
{
    u32 i;

    if (gPlayerPartyCount == 0)
    {
        gSpecialVar_Result = 0;
        return;
    }
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == gSpecialVar_0x8004)
        {
            StringCopy(gStringVar1, GetSpeciesName(gSpecialVar_0x8004));
            gSpecialVar_Result = gSpecialVar_0x8004;
            return;
        }
    }
    gSpecialVar_Result = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES_OR_EGG);
}

// Phone book: VAR_0x8004 is the contact's FLAG_JOHTO_PHONE_*_REGISTERED flag;
// VAR_0x8005 is the contact's optional rematch flag (or 0).
// VAR_RESULT is TRUE when the number is saved; when saved, also readies the contact for rematch on the next visit.
void JohtoPhoneIsRegistered(void)
{
    gSpecialVar_Result = FlagGet(gSpecialVar_0x8004);
    if (gSpecialVar_Result && gSpecialVar_0x8005 != 0)
        FlagSet(gSpecialVar_0x8005);
}

// Saves the contact (VAR_0x8004 flag), readies their optional rematch/gift flags (VAR_0x8005, VAR_0x8006),
// and answers VAR_RESULT = 0 like Crystal's "number registered".
void JohtoPhoneRegister(void)
{
    FlagSet(gSpecialVar_0x8004);
    if (gSpecialVar_0x8005 != 0)
        FlagSet(gSpecialVar_0x8005);
    if (gSpecialVar_0x8006 != 0)
        FlagSet(gSpecialVar_0x8006);
    gSpecialVar_Result = 0;
}

void JohtoBufferLandmarkName(void)
{
    GetMapNameGeneric(gStringVar1, gMapHeader.regionMapSectionId);
}

// Crystal's VAR_BADGES: number of Johto gym badges.
void JohtoCountBadges(void)
{
    u32 i, count = 0;

    for (i = 0; i < 8; i++)
    {
        if (FlagGet(GetBadgeFlagForRegion(REGION_JOHTO, i)))
            count++;
    }
    gSpecialVar_Result = count;
}

// Crystal's FindPartyMonThatSpeciesYourTrainerID: VAR_0x8004 = species. VAR_RESULT is TRUE when a party Pokemon of that species
// (eggs report SPECIES_EGG, so they never match) was originally the player's, i.e. hatched or raised by them.
void JohtoFindPartyMonSpecies(void)
{
    u32 i;
    u32 playerId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);

    gSpecialVar_Result = FALSE;
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];

        if (GetMonData(mon, MON_DATA_SPECIES) == gSpecialVar_0x8004 && GetMonData(mon, MON_DATA_OT_ID) == playerId)
        {
            gSpecialVar_Result = TRUE;
            return;
        }
    }
}

void JohtoCheckCoins(void)
{
    gSpecialVar_Result = (GetCoins() >= gSpecialVar_0x8004) ? 1 : 0;
}

void JohtoSelectApricornForKurt(void)
{
    static const u16 sApricorns[] = {
        ITEM_RED_APRICORN, ITEM_BLU_APRICORN, ITEM_YLW_APRICORN,
        ITEM_GRN_APRICORN, ITEM_WHT_APRICORN, ITEM_BLK_APRICORN, ITEM_PNK_APRICORN
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sApricorns); i++)
    {
        if (CheckBagHasItem(sApricorns[i], 1))
        {
            RemoveBagItem(sApricorns[i], 1);
            gSpecialVar_Result = sApricorns[i];
            return;
        }
    }
    gSpecialVar_Result = FALSE;
}

void JohtoGetDexCaught(void)
{
    gSpecialVar_Result = GetNationalPokedexCount(FLAG_GET_CAUGHT);
}

void JohtoCheckFirstMonIsEgg(void)
{
    gSpecialVar_Result = (gPlayerPartyCount > 0 && GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG));
}

void JohtoCheckCaughtCelebi(void)
{
    gSpecialVar_Result = (gBattleOutcome == B_OUTCOME_CAUGHT);
}

void JohtoInvertResult(void)
{
    gSpecialVar_Result = (gSpecialVar_Result == 0);
}

struct OddEggData {
    u16 species;
    u8 shinyProb; // out of totalProb
    u8 totalProb; // percentage
    u16 moves[MAX_MON_MOVES];
};

static const struct OddEggData sOddEggs[] = {
    // Pichu: 8% normal, 1% shiny (9% total)
    { SPECIES_PICHU, 1, 9, { MOVE_THUNDER_SHOCK, MOVE_CHARM, MOVE_DIZZY_PUNCH, MOVE_NONE } },
    // Cleffa: 16% normal, 3% shiny (19% total)
    { SPECIES_CLEFFA, 3, 19, { MOVE_POUND, MOVE_CHARM, MOVE_ENCORE, MOVE_DIZZY_PUNCH } },
    // Igglybuff: 16% normal, 3% shiny (19% total)
    { SPECIES_IGGLYBUFF, 3, 19, { MOVE_SING, MOVE_CHARM, MOVE_DEFENSE_CURL, MOVE_DIZZY_PUNCH } },
    // Smoochum: 14% normal, 2% shiny (16% total)
    { SPECIES_SMOOCHUM, 2, 16, { MOVE_POUND, MOVE_LICK, MOVE_SWEET_KISS, MOVE_DIZZY_PUNCH } },
    // Magby: 10% normal, 2% shiny (12% total)
    { SPECIES_MAGBY, 2, 12, { MOVE_EMBER, MOVE_LEER, MOVE_DIZZY_PUNCH, MOVE_NONE } },
    // Elekid: 12% normal, 2% shiny (14% total)
    { SPECIES_ELEKID, 2, 14, { MOVE_QUICK_ATTACK, MOVE_LEER, MOVE_DIZZY_PUNCH, MOVE_NONE } },
    // Tyrogue: 10% normal, 1% shiny (11% total)
    { SPECIES_TYROGUE, 1, 11, { MOVE_TACKLE, MOVE_DIZZY_PUNCH, MOVE_NONE, MOVE_NONE } },
};

void JohtoGiveOddEgg(void)
{
    struct Pokemon mon;
    u32 roll = Random() % 100;
    u32 accum = 0;
    u32 chosenIndex = 0;
    u32 i;
    bool8 isShiny = FALSE;
    u8 isEgg = TRUE;

    if (gPlayerPartyCount >= PARTY_SIZE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(sOddEggs); i++)
    {
        accum += sOddEggs[i].totalProb;
        if (roll < accum)
        {
            chosenIndex = i;
            if ((accum - 1 - roll) < sOddEggs[i].shinyProb)
                isShiny = TRUE;
            break;
        }
    }

    CreateEgg(&mon, sOddEggs[chosenIndex].species, FALSE);
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    SetMonData(&mon, MON_DATA_IS_SHINY, &isShiny);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = sOddEggs[chosenIndex].moves[i];
        u32 pp = (move != MOVE_NONE) ? GetMovePP(move) : 0;
        SetMonData(&mon, MON_DATA_MOVE1 + i, &move);
        SetMonData(&mon, MON_DATA_PP1 + i, &pp);
    }

    GiveCapturedMonToPlayer(&mon);
    gSpecialVar_Result = TRUE;
}

void JohtoGiveParkBalls(void)
{
    u32 i;
    u8 indices[10];

    // Give 20 Sport Balls for the Bug-Catching Contest
    AddBagItem(ITEM_SPORT_BALL, 20);

    // Randomly pick 5 of the 10 contestants to appear in the park
    for (i = 0; i < 10; i++)
        indices[i] = i;

    for (i = 9; i > 0; i--)
    {
        u32 j = Random() % (i + 1);
        u8 tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (i = 0; i < 5; i++)
        FlagClear(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + indices[i]);
    for (i = 5; i < 10; i++)
        FlagSet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + indices[i]);

    gSpecialVar_Result = TRUE;
}

static const u16 sJohtoFruitTreeFlags[] = {
    FLAG_JOHTO_FRUITTREE_ROUTE_38,
    FLAG_JOHTO_FRUITTREE_ROUTE_39,
    FLAG_JOHTO_FRUITTREE_ROUTE_42_1,
    FLAG_JOHTO_FRUITTREE_ROUTE_42_2,
    FLAG_JOHTO_FRUITTREE_ROUTE_42_3,
    FLAG_JOHTO_FRUITTREE_ROUTE_44,
    FLAG_JOHTO_FRUITTREE_ROUTE_45,
    FLAG_JOHTO_FRUITTREE_ROUTE_46_1,
    FLAG_JOHTO_FRUITTREE_ROUTE_46_2,
    FLAG_JOHTO_FRUITTREE_ROUTE_33,
    FLAG_JOHTO_FRUITTREE_AZALEA_TOWN,
    FLAG_JOHTO_FRUITTREE_ROUTE_43,
    FLAG_JOHTO_FRUITTREE_ROUTE_35,
    FLAG_JOHTO_FRUITTREE_ROUTE_36,
    FLAG_JOHTO_FRUITTREE_ROUTE_37_1,
    FLAG_JOHTO_FRUITTREE_ROUTE_37_2,
    FLAG_JOHTO_FRUITTREE_ROUTE_37_3,
    FLAG_JOHTO_FRUITTREE_VIOLET_CITY,
    FLAG_JOHTO_FRUITTREE_ROUTE_11,
    FLAG_JOHTO_FRUITTREE_ROUTE_1,
    FLAG_JOHTO_FRUITTREE_PEWTER_CITY_1,
    FLAG_JOHTO_FRUITTREE_PEWTER_CITY_2,
    FLAG_JOHTO_FRUITTREE_FUCHSIA_CITY,
    FLAG_JOHTO_FRUITTREE_ROUTE_8,
    FLAG_JOHTO_FRUITTREE_ROUTE_2,
    FLAG_JOHTO_FRUITTREE_ROUTE_26,
    FLAG_JOHTO_FRUITTREE_ROUTE_29,
    FLAG_JOHTO_FRUITTREE_ROUTE_30_1,
    FLAG_JOHTO_FRUITTREE_ROUTE_30_2,
    FLAG_JOHTO_FRUITTREE_ROUTE_31,
};

void JohtoDailyResetFruitTrees(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sJohtoFruitTreeFlags); i++)
        FlagClear(sJohtoFruitTreeFlags[i]);

    FlagClear(FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST);
}

// POKE-CONFLUENCE
// Checks if a Mystery Gift delivery is pending.
void JohtoCheckMysteryGift(void)
{
    // In GBC Crystal, delivery officer appeared if a gift was waiting in sMysteryGiftItem.
    // In pokeconfluence, delivery officer is hidden once claimed via FLAG_JOHTO_MYSTERY_GIFT_DELIVERY_GUY.
    if (FlagGet(FLAG_JOHTO_MYSTERY_GIFT_DELIVERY_GUY))
        gSpecialVar_Result = 0;
    else
        gSpecialVar_Result = 0;
}

// POKE-CONFLUENCE
// Delivers the Mystery Gift item.
void JohtoGetMysteryGiftItem(void)
{
    if (AddBagItem(ITEM_LUM_BERRY, 1))
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

// POKE-CONFLUENCE
// Checks if player party has at least 3 eligible battle-ready Pokémon for Battle Tower.
void JohtoCheckBattleTowerEligibility(void)
{
    u32 i;
    u32 count = 0;
    u8 partyCount = gPartiesCount[B_TRAINER_PLAYER];

    for (i = 0; i < partyCount; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (!GetMonData(mon, MON_DATA_IS_EGG)
            && GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE
            && GetMonData(mon, MON_DATA_HP) > 0)
        {
            count++;
        }
    }

    gSpecialVar_Result = (count >= 3) ? TRUE : FALSE;
}


