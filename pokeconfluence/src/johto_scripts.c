#include "global.h"
#include "rtc.h"
#include "event_data.h"
#include "regions.h"
#include "new_game.h"
#include "pokemon.h"
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
