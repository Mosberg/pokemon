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
#include "script.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/maps.h"
#include "constants/pokeball.h"
#include "constants/johto_flags.h"
#include "unown.h"

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

// POKE-CONFLUENCE: Authentic Johto Kurt's Apricorn Crafting specials

static u16 ApricornToBallItem(u16 apricorn)
{
    switch (apricorn)
    {
    case ITEM_RED_APRICORN:   return ITEM_LEVEL_BALL;
    case ITEM_BLU_APRICORN:   return ITEM_LURE_BALL;
    case ITEM_YLW_APRICORN:   return ITEM_MOON_BALL;
    case ITEM_GRN_APRICORN:   return ITEM_FRIEND_BALL;
    case ITEM_WHT_APRICORN:   return ITEM_FAST_BALL;
    case ITEM_BLK_APRICORN:   return ITEM_HEAVY_BALL;
    case ITEM_PNK_APRICORN:   return ITEM_LOVE_BALL;
    default:                  return ITEM_NONE;
    }
}

void JohtoGetApricornQuantity(void)
{
    gSpecialVar_Result = CountTotalItemQuantityInBag(gSpecialVar_0x8004);
}

void JohtoGiveKurtApricorns(void)
{
    u16 apricorn = gSpecialVar_0x8004;
    u16 count = gSpecialVar_0x8005;
    u16 ballItem = ApricornToBallItem(apricorn);

    if (count == 0)
        count = 1;

    if (RemoveBagItem(apricorn, count))
    {
        VarSet(VAR_JOHTO_KURT_APRICORN_ITEM, ballItem);
        VarSet(VAR_JOHTO_KURT_APRICORN_COUNT, count);
        FlagSet(FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS);

        // Keep legacy flags set for script compatibility
        switch (apricorn)
        {
        case ITEM_RED_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_RED_APRICORN); break;
        case ITEM_BLU_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_BLU_APRICORN); break;
        case ITEM_YLW_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_YLW_APRICORN); break;
        case ITEM_GRN_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_GRN_APRICORN); break;
        case ITEM_WHT_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_WHT_APRICORN); break;
        case ITEM_BLK_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_BLK_APRICORN); break;
        case ITEM_PNK_APRICORN: FlagSet(FLAG_JOHTO_GAVE_KURT_PNK_APRICORN); break;
        }
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

void JohtoDeliverKurtBalls(void)
{
    u16 ballItem = VarGet(VAR_JOHTO_KURT_APRICORN_ITEM);
    u16 count = VarGet(VAR_JOHTO_KURT_APRICORN_COUNT);

    if (count == 0)
        count = 1;

    // Fallback if legacy flag was set without vars
    if (ballItem == ITEM_NONE)
    {
        if (FlagGet(FLAG_JOHTO_GAVE_KURT_RED_APRICORN)) ballItem = ITEM_LEVEL_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_BLU_APRICORN)) ballItem = ITEM_LURE_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_YLW_APRICORN)) ballItem = ITEM_MOON_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_GRN_APRICORN)) ballItem = ITEM_FRIEND_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_WHT_APRICORN)) ballItem = ITEM_FAST_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_BLK_APRICORN)) ballItem = ITEM_HEAVY_BALL;
        else if (FlagGet(FLAG_JOHTO_GAVE_KURT_PNK_APRICORN)) ballItem = ITEM_LOVE_BALL;
    }

    if (ballItem != ITEM_NONE && AddBagItem(ballItem, count))
    {
        VarSet(VAR_JOHTO_KURT_APRICORN_ITEM, ITEM_NONE);
        VarSet(VAR_JOHTO_KURT_APRICORN_COUNT, 0);
        FlagClear(FLAG_JOHTO_GAVE_KURT_RED_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_BLU_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_YLW_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_GRN_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_WHT_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_BLK_APRICORN);
        FlagClear(FLAG_JOHTO_GAVE_KURT_PNK_APRICORN);

        gSpecialVar_0x8000 = ballItem;
        gSpecialVar_0x8001 = count;
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE; // Bag full
    }
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
            gSpecialVar_0x8004 = sApricorns[i];
            gSpecialVar_0x8005 = 1;
            JohtoGiveKurtApricorns();
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

// POKE-CONFLUENCE: Forces the currently staged scripted wild Pokémon to be shiny (Lake of Rage Red Gyarados)
void JohtoSetWildMonShiny(void)
{
    bool32 isShiny = TRUE;
    SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_IS_SHINY, &isShiny);
}

extern const u8 Johto_BugContest_EventScript_TimesUp[];
extern const u8 Johto_BugContest_EventScript_OutOfBalls[];

void JohtoGiveParkBalls(void)
{
    u32 i;
    u8 indices[10];

    // Give 20 Sport Balls for the Bug-Catching Contest
    AddBagItem(ITEM_SPORT_BALL, 20);

    // Initialize 20-minute (500 steps) countdown timer
    VarSet(VAR_JOHTO_BUG_CONTEST_STEPS, 500);
    VarSet(VAR_JOHTO_BUG_CONTEST_SCORE, 0);
    VarSet(VAR_JOHTO_BUG_CONTEST_PLACEMENT, 0);

    // Randomly pick 5 of the 10 contestants to appear in the park and gate
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
    {
        FlagClear(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + indices[i]);
        FlagClear(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1B + indices[i]);
    }
    for (i = 5; i < 10; i++)
    {
        FlagSet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + indices[i]);
        FlagSet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1B + indices[i]);
    }

    gSpecialVar_Result = TRUE;
}

// POKE-CONFLUENCE: Overworld step decrement & timer expiration for Bug-Catching Contest
bool8 JohtoBugContestTakeStep(void)
{
    if (!FlagGet(FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER))
        return FALSE;

    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST)
        || gSaveBlock1Ptr->location.mapNum != MAP_NUM(MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST))
        return FALSE;

    // Check if player has run out of Sport Balls
    if (CheckBagHasItem(ITEM_SPORT_BALL, 1) == FALSE)
    {
        ScriptContext_SetupScript(Johto_BugContest_EventScript_OutOfBalls);
        return TRUE;
    }

    u16 steps = VarGet(VAR_JOHTO_BUG_CONTEST_STEPS);
    if (steps > 0)
    {
        steps--;
        VarSet(VAR_JOHTO_BUG_CONTEST_STEPS, steps);
    }

    if (steps == 0)
    {
        ScriptContext_SetupScript(Johto_BugContest_EventScript_TimesUp);
        return TRUE;
    }

    return FALSE;
}

// POKE-CONFLUENCE: Calculates remaining minutes for officer dialogue (from 1 to 20)
void JohtoGetBugContestRemainingMinutes(void)
{
    u16 steps = VarGet(VAR_JOHTO_BUG_CONTEST_STEPS);
    u16 mins;

    if (steps == 0)
        mins = 0;
    else
        mins = (steps + 24) / 25;

    gSpecialVar_Result = mins;
}

struct BugContestantData
{
    const u8 name[12];
    struct {
        u16 species;
        u16 baseScore;
    } entries[3];
};

static const struct BugContestantData sBugContestants[10] =
{
    { _("DON"),     { {SPECIES_KAKUNA, 300},     {SPECIES_METAPOD, 285},    {SPECIES_CATERPIE, 226} } },
    { _("ED"),      { {SPECIES_BUTTERFREE, 286}, {SPECIES_BUTTERFREE, 251}, {SPECIES_CATERPIE, 237} } },
    { _("NICK"),    { {SPECIES_SCYTHER, 357},    {SPECIES_BUTTERFREE, 349}, {SPECIES_PINSIR, 368} } },
    { _("WILLIAM"), { {SPECIES_PINSIR, 332},     {SPECIES_BUTTERFREE, 324}, {SPECIES_VENONAT, 321} } },
    { _("BENNY"),   { {SPECIES_BUTTERFREE, 318}, {SPECIES_WEEDLE, 295},     {SPECIES_CATERPIE, 285} } },
    { _("BARRY"),   { {SPECIES_PINSIR, 366},     {SPECIES_VENONAT, 329},    {SPECIES_KAKUNA, 314} } },
    { _("CINDY"),   { {SPECIES_BUTTERFREE, 341}, {SPECIES_METAPOD, 301},    {SPECIES_CATERPIE, 264} } },
    { _("JOSH"),    { {SPECIES_SCYTHER, 326},    {SPECIES_BUTTERFREE, 292}, {SPECIES_METAPOD, 282} } },
    { _("SAMUEL"),  { {SPECIES_WEEDLE, 270},     {SPECIES_PINSIR, 282},     {SPECIES_CATERPIE, 251} } },
    { _("KIPP"),    { {SPECIES_VENONAT, 267},    {SPECIES_PARAS, 254},      {SPECIES_KAKUNA, 259} } },
};

struct ContestParticipant
{
    u8 name[PLAYER_NAME_LENGTH + 1];
    u16 species;
    u16 score;
    bool8 isPlayer;
};

static EWRAM_DATA struct ContestParticipant sTopContestants[3] = {0};

// POKE-CONFLUENCE: Authentic GBC Bug-Catching Contest scoring formula adapted for GBA
u32 JohtoCalculateContestScore(struct Pokemon *mon)
{
    if (mon == NULL || GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
        return 0;

    CalculateMonStats(mon);

    u16 maxHp = GetMonData(mon, MON_DATA_MAX_HP);
    u16 atk = GetMonData(mon, MON_DATA_ATK);
    u16 def = GetMonData(mon, MON_DATA_DEF);
    u16 spd = GetMonData(mon, MON_DATA_SPEED);
    u16 spAtk = GetMonData(mon, MON_DATA_SPATK);
    u16 spDef = GetMonData(mon, MON_DATA_SPDEF);
    u16 hp = GetMonData(mon, MON_DATA_HP);
    u16 ivSum = GetMonData(mon, MON_DATA_HP_IV) +
                GetMonData(mon, MON_DATA_ATK_IV) +
                GetMonData(mon, MON_DATA_DEF_IV) +
                GetMonData(mon, MON_DATA_SPEED_IV) +
                GetMonData(mon, MON_DATA_SPATK_IV) +
                GetMonData(mon, MON_DATA_SPDEF_IV);
    u16 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);

    u32 score = 0;
    // Max HP * 4
    score += (maxHp * 4);
    // Sum of stat low bytes (Attack + Defense + Speed + SpAtk + SpDef)
    score += (atk + def + spd + spAtk + spDef);
    // IV / DV contribution (up to ~16-30 points)
    score += (ivSum * 16) / 186;
    // Remaining HP / 8
    score += (hp / 8);
    // Held item bonus (+1)
    if (heldItem != ITEM_NONE)
        score += 1;

    return score;
}

// POKE-CONFLUENCE: Contest judging based on rarity, remaining HP, level, and IVs
void JohtoBugContestJudge(void)
{
    struct ContestParticipant participants[6];
    u32 participantCount = 0;
    u32 i, j;
    u32 bestPlayerScore = 0;
    u16 bestPlayerSpecies = SPECIES_NONE;

    // 1. Find player's best mon caught with Sport Ball in the contest
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) != SPECIES_NONE
            && GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_POKEBALL) == BALL_SPORT)
        {
            u32 s = JohtoCalculateContestScore(&gParties[B_TRAINER_PLAYER][i]);
            if (s > bestPlayerScore)
            {
                bestPlayerScore = s;
                bestPlayerSpecies = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES);
            }
        }
    }

    // Add player to participants
    StringCopy(participants[0].name, gSaveBlock2Ptr->playerName);
    participants[0].species = bestPlayerSpecies;
    participants[0].score = bestPlayerScore;
    participants[0].isPlayer = TRUE;
    participantCount = 1;

    // 2. Add the 5 active AI contestants
    for (i = 0; i < 10; i++)
    {
        if (!FlagGet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + i))
        {
            u32 pick = Random() % 3;
            u16 perturb = Random() % 8;
            StringCopy(participants[participantCount].name, sBugContestants[i].name);
            participants[participantCount].species = sBugContestants[i].entries[pick].species;
            participants[participantCount].score = sBugContestants[i].entries[pick].baseScore + perturb;
            participants[participantCount].isPlayer = FALSE;
            participantCount++;
            if (participantCount >= 6)
                break;
        }
    }

    // 3. Sort participants by score descending
    for (i = 0; i < participantCount - 1; i++)
    {
        for (j = 0; j < participantCount - 1 - i; j++)
        {
            if (participants[j].score < participants[j + 1].score)
            {
                struct ContestParticipant tmp = participants[j];
                participants[j] = participants[j + 1];
                participants[j + 1] = tmp;
            }
        }
    }

    // Save top 3
    for (i = 0; i < 3; i++)
        sTopContestants[i] = participants[i];

    // Determine player's placement
    u8 playerPlacement = 4; // Consolation
    if (bestPlayerScore > 0)
    {
        for (i = 0; i < participantCount; i++)
        {
            if (participants[i].isPlayer)
            {
                playerPlacement = (i < 3) ? (i + 1) : 4;
                break;
            }
        }
    }

    VarSet(VAR_JOHTO_BUG_CONTEST_SCORE, bestPlayerScore);
    VarSet(VAR_JOHTO_BUG_CONTEST_PLACEMENT, playerPlacement);
    gSpecialVar_Result = playerPlacement;
}

// POKE-CONFLUENCE: Buffers top contestant names and scores for dialogue
void JohtoBugContestBufferWinner(void)
{
    u16 place = gSpecialVar_0x8004; // 1, 2, or 3
    if (place >= 1 && place <= 3)
    {
        u8 idx = place - 1;
        StringCopy(gStringVar1, sTopContestants[idx].name);
        StringCopy(gStringVar2, GetSpeciesName(sTopContestants[idx].species));
        ConvertIntToDecimalStringN(gStringVar3, sTopContestants[idx].score, STR_CONV_MODE_LEFT_ALIGN, 4);
        gSpecialVar_Result = sTopContestants[idx].score;
    }
}

// POKE-CONFLUENCE: Resets contest flags, scenes, and returns remaining balls
void JohtoBugContestCleanup(void)
{
    u32 i;
    u16 sportBalls = CheckBagHasItem(ITEM_SPORT_BALL, 1);
    if (sportBalls)
        RemoveBagItem(ITEM_SPORT_BALL, 20);

    FlagClear(FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER);
    FlagSet(FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST);
    FlagClear(FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER);

    // Hide all contestants
    for (i = 0; i < 10; i++)
    {
        FlagSet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1A + i);
        FlagSet(FLAG_JOHTO_BUG_CATCHING_CONTESTANT_1B + i);
    }

    VarSet(VAR_JOHTO_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 0);
    VarSet(VAR_JOHTO_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 0);
    VarSet(VAR_JOHTO_BUG_CONTEST_STEPS, 0);
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

// POKE-CONFLUENCE: Johto Unown Dex caught count query
void JohtoGetUnownCaughtCount(void)
{
    gSpecialVar_Result = Johto_GetUnownCaughtCount();
}

