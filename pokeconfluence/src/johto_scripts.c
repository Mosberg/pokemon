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
#include "constants/items.h"
#include "constants/species.h"

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
