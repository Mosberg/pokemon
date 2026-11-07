// POKE-CONFLUENCE: Authentic Johto Battle Tower 7-trainer ladder subsystem (from pokecrystal)

#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "data.h"
#include "event_data.h"
#include "field_specials.h"
#include "item.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "constants/battle.h"
#include "constants/battle_frontier.h"
#include "constants/battle_frontier_trainers.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/johto_flags.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "johto_battle_tower.h"

// Authentic Crystal Battle Tower Trainer definitions (games/gbc/pokecrystal/data/battle_tower/classes.asm)
static const u8 sText_TrainerNameHanson[] = _("HANSON");
static const u8 sText_TrainerIntroHanson[] = _("I'm fishing for a great battle!$");

static const u8 sText_TrainerNameSawyer[] = _("SAWYER");
static const u8 sText_TrainerIntroSawyer[] = _("My POKéMON collection is unmatched!$");

static const u8 sText_TrainerNameMasuda[] = _("MASUDA");
static const u8 sText_TrainerIntroMasuda[] = _("Listen to my rock 'n' roll beat!$");

static const u8 sText_TrainerNameNickel[] = _("NICKEL");
static const u8 sText_TrainerIntroNickel[] = _("Let us begin our battle experiment.$");

static const u8 sText_TrainerNameOlson[] = _("OLSON");
static const u8 sText_TrainerIntroOlson[] = _("My precious POKéMON will triumph!$");

static const u8 sText_TrainerNameZaborowski[] = _("ZABOROWSKI");
static const u8 sText_TrainerIntroZaborowski[] = _("Don't underestimate a girl!$");

static const u8 sText_TrainerNameWright[] = _("WRIGHT");
static const u8 sText_TrainerIntroWright[] = _("I won't lose to anyone!$");

static const u8 sText_TrainerNameAlexander[] = _("ALEXANDER");
static const u8 sText_TrainerIntroAlexander[] = _("Our teamwork is solid as rock!$");

static const u8 sText_TrainerNameKawakami[] = _("KAWAKAMI");
static const u8 sText_TrainerIntroKawakami[] = _("Class is now in session!$");

static const u8 sText_TrainerNameBickett[] = _("BICKETT");
static const u8 sText_TrainerIntroBickett[] = _("I take wonderful care of my POKéMON!$");

static const u8 sText_TrainerNameSaito[] = _("SAITO");
static const u8 sText_TrainerIntroSaito[] = _("May our dance of battle commence.$");

static const u8 sText_TrainerNameCrawford[] = _("CRAWFORD");
static const u8 sText_TrainerIntroCrawford[] = _("Chill out and feel the blizzard!$");

static const u8 sText_TrainerNameDiaz[] = _("DIAZ");
static const u8 sText_TrainerIntroDiaz[] = _("A picnic battle sounds delightful!$");

static const u8 sText_TrainerNameErickson[] = _("ERICKSON");
static const u8 sText_TrainerIntroErickson[] = _("Full throttle! Rev your engines!$");

static const u8 sText_TrainerNameFairfield[] = _("FAIRFIELD");
static const u8 sText_TrainerIntroFairfield[] = _("Can you keep up with my tempo?$");

static const u8 sText_TrainerNameHunter[] = _("HUNTER");
static const u8 sText_TrainerIntroHunter[] = _("My sweet POKéMON are so darling!$");

static const u8 sText_TrainerNameHill[] = _("HILL");
static const u8 sText_TrainerIntroHill[] = _("Hot! Hot! We're burning up!$");

static const u8 sText_TrainerNameJavier[] = _("JAVIER");
static const u8 sText_TrainerIntroJavier[] = _("Ready to dive into battle?$");

static const u8 sText_TrainerNameKaufman[] = _("KAUFMAN");
static const u8 sText_TrainerIntroKaufman[] = _("Ride the waves of victory!$");

static const u8 sText_TrainerNameLancaster[] = _("LANCASTER");
static const u8 sText_TrainerIntroLancaster[] = _("Gliding smooth like ice!$");

static const u8 sText_TrainerNameMcMahill[] = _("McMAHILL");
static const u8 sText_TrainerIntroMcMahill[] = _("Nature has prepared us well!$");

struct JohtoTowerTrainerEntry
{
    u16 frontierTrainerId;
    u16 gfxId;
    const u8 *name;
    const u8 *intro;
};

static const struct JohtoTowerTrainerEntry sJohtoTowerTrainers[] = {
    { FRONTIER_TRAINER_MITCH,    OBJ_EVENT_GFX_FISHERMAN,  sText_TrainerNameHanson,     sText_TrainerIntroHanson },
    { FRONTIER_TRAINER_CHEN,     OBJ_EVENT_GFX_MANIAC,     sText_TrainerNameSawyer,     sText_TrainerIntroSawyer },
    { FRONTIER_TRAINER_GILLIAN1, OBJ_EVENT_GFX_ROCKER,     sText_TrainerNameMasuda,     sText_TrainerIntroMasuda },
    { FRONTIER_TRAINER_DUSTIN,   OBJ_EVENT_GFX_SCIENTIST_1,sText_TrainerNameNickel,     sText_TrainerIntroNickel },
    { FRONTIER_TRAINER_MANUEL,   OBJ_EVENT_GFX_POKEFAN_M,  sText_TrainerNameOlson,      sText_TrainerIntroOlson },
    { FRONTIER_TRAINER_CYBIL,    OBJ_EVENT_GFX_LASS,       sText_TrainerNameZaborowski, sText_TrainerIntroZaborowski },
    { FRONTIER_TRAINER_BRADY,    OBJ_EVENT_GFX_YOUNGSTER,  sText_TrainerNameWright,     sText_TrainerIntroWright },
    { FRONTIER_TRAINER_AL,       OBJ_EVENT_GFX_HIKER,      sText_TrainerNameAlexander,  sText_TrainerIntroAlexander },
    { FRONTIER_TRAINER_KIPP,     OBJ_EVENT_GFX_WOMAN_1,    sText_TrainerNameKawakami,   sText_TrainerIntroKawakami },
    { FRONTIER_TRAINER_MANUEL,   OBJ_EVENT_GFX_POKEFAN_M,  sText_TrainerNameBickett,    sText_TrainerIntroBickett },
    { FRONTIER_TRAINER_ANNE,     OBJ_EVENT_GFX_BEAUTY,     sText_TrainerNameSaito,      sText_TrainerIntroSaito },
    { FRONTIER_TRAINER_BRADY,    OBJ_EVENT_GFX_YOUNGSTER,  sText_TrainerNameCrawford,   sText_TrainerIntroCrawford },
    { FRONTIER_TRAINER_RODETTE,  OBJ_EVENT_GFX_PICNICKER,  sText_TrainerNameDiaz,       sText_TrainerIntroDiaz },
    { FRONTIER_TRAINER_BRADY,    OBJ_EVENT_GFX_BIKER,      sText_TrainerNameErickson,   sText_TrainerIntroErickson },
    { FRONTIER_TRAINER_JASON,    OBJ_EVENT_GFX_PSYCHIC_M,  sText_TrainerNameFairfield,  sText_TrainerIntroFairfield },
    { FRONTIER_TRAINER_TINA,     OBJ_EVENT_GFX_POKEFAN_F,  sText_TrainerNameHunter,     sText_TrainerIntroHunter },
    { FRONTIER_TRAINER_BRADY,    OBJ_EVENT_GFX_MANIAC,     sText_TrainerNameHill,       sText_TrainerIntroHill },
    { FRONTIER_TRAINER_ZOEY,     OBJ_EVENT_GFX_SWIMMER_F,  sText_TrainerNameJavier,     sText_TrainerIntroJavier },
    { FRONTIER_TRAINER_GLENN,    OBJ_EVENT_GFX_SWIMMER_M,  sText_TrainerNameKaufman,    sText_TrainerIntroKaufman },
    { FRONTIER_TRAINER_ANNE,     OBJ_EVENT_GFX_BEAUTY,     sText_TrainerNameLancaster,  sText_TrainerIntroLancaster },
    { FRONTIER_TRAINER_KEITH,    OBJ_EVENT_GFX_CAMPER,     sText_TrainerNameMcMahill,   sText_TrainerIntroMcMahill },
};

// Authentic Crystal Battle Tower species pool
static const u16 sJohtoTowerPool[] = {
    SPECIES_JOLTEON,
    SPECIES_ESPEON,
    SPECIES_UMBREON,
    SPECIES_GENGAR,
    SPECIES_DRAGONITE,
    SPECIES_TYRANITAR,
    SPECIES_ALAKAZAM,
    SPECIES_SCIZOR,
    SPECIES_HERACROSS,
    SPECIES_FERALIGATR,
    SPECIES_TYPHLOSION,
    SPECIES_MEGANIUM,
    SPECIES_HOUNDOOM,
    SPECIES_KINGDRA,
    SPECIES_SNORLAX,
    SPECIES_STARMIE,
    SPECIES_LAPRAS,
    SPECIES_ARCANINE,
    SPECIES_AMPHAROS,
    SPECIES_RAICHU,
    SPECIES_MACHAMP,
    SPECIES_STEELIX,
    SPECIES_DONPHAN,
    SPECIES_SKARMORY,
    SPECIES_PORYGON2,
    SPECIES_POLITOED,
    SPECIES_SLOWBRO,
    SPECIES_CLOYSTER,
    SPECIES_EXEGGUTOR,
    SPECIES_PINSIR,
    SPECIES_AERODACTYL,
    SPECIES_NIDOKING,
    SPECIES_NIDOQUEEN,
};

static const u16 sJohtoTowerItems[] = {
    ITEM_LEFTOVERS,
    ITEM_BRIGHT_POWDER,
    ITEM_FOCUS_BAND,
    ITEM_LUM_BERRY,
    ITEM_SCOPE_LENS,
    ITEM_QUICK_CLAW,
    ITEM_KINGS_ROCK,
    ITEM_CHARCOAL,
    ITEM_MYSTIC_WATER,
    ITEM_MAGNET,
    ITEM_MIRACLE_SEED,
    ITEM_BLACK_GLASSES,
    ITEM_BLACK_BELT,
    ITEM_HARD_STONE,
    ITEM_DRAGON_SCALE,
};

static const u16 sVitamins[] = {
    ITEM_HP_UP,
    ITEM_PROTEIN,
    ITEM_IRON,
    ITEM_CARBOS,
    ITEM_CALCIUM,
};

static u8 sSelectedTrainerIdx = 0;

// POKE-CONFLUENCE: Eligibility check
void JohtoCheckBattleTowerEligibility(void)
{
    u32 i, j;
    u8 partyCount = gPartiesCount[B_TRAINER_PLAYER];
    u16 roomLevel = VarGet(VAR_JOHTO_BATTLE_TOWER_LEVEL);
    if (roomLevel == 0)
        roomLevel = 50;

    if (partyCount < 3)
    {
        gSpecialVar_Result = 1; // Less than 3 mons
        return;
    }

    for (i = 0; i < 3; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_IS_EGG))
        {
            gSpecialVar_Result = 5; // Egg
            return;
        }

        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        if (species == SPECIES_NONE)
        {
            gSpecialVar_Result = 1; // Unfit
            return;
        }

        if (GetMonData(mon, MON_DATA_MAX_HP) > 0 && GetMonData(mon, MON_DATA_HP) == 0)
        {
            gSpecialVar_Result = 1; // Fainted
            return;
        }

        u8 monLevel = GetMonData(mon, MON_DATA_LEVEL);
        if (monLevel > roomLevel)
        {
            GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
            StringGet_Nickname(gStringVar1);
            ConvertIntToDecimalStringN(gStringVar2, roomLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
            gSpecialVar_Result = 2; // Level exceeds room limit
            return;
        }

        // Species Clause
        for (j = i + 1; j < 3; j++)
        {
            struct Pokemon *other = &gParties[B_TRAINER_PLAYER][j];
            if (species == GetMonData(other, MON_DATA_SPECIES))
            {
                gSpecialVar_Result = 3; // Duplicate species
                return;
            }
        }

        // Item Clause
        u16 item = GetMonData(mon, MON_DATA_HELD_ITEM);
        if (item != ITEM_NONE)
        {
            for (j = i + 1; j < 3; j++)
            {
                struct Pokemon *other = &gParties[B_TRAINER_PLAYER][j];
                if (item == GetMonData(other, MON_DATA_HELD_ITEM))
                {
                    gSpecialVar_Result = 4; // Duplicate items
                    return;
                }
            }
        }
    }

    gSpecialVar_Result = 0; // Eligible!
}

void JohtoBattleTowerInitChallenge(void)
{
    VarSet(VAR_JOHTO_BATTLE_TOWER_STREAK, 0);
    FlagClear(FLAG_JOHTO_BATTLE_TOWER_WON_CHALLENGE);
}

void JohtoBattleTowerPrepareOpponent(void)
{
    u16 streak = VarGet(VAR_JOHTO_BATTLE_TOWER_STREAK);
    u8 level = VarGet(VAR_JOHTO_BATTLE_TOWER_LEVEL);
    if (level == 0)
        level = 50;

    sSelectedTrainerIdx = (streak * 3 + (level / 10)) % ARRAY_COUNT(sJohtoTowerTrainers);
    const struct JohtoTowerTrainerEntry *tr = &sJohtoTowerTrainers[sSelectedTrainerIdx];

    VarSet(VAR_OBJ_GFX_ID_0, tr->gfxId);

    StringCopy(gStringVar1, tr->name);
    StringCopy(gStringVar2, tr->intro);
    ConvertIntToDecimalStringN(gStringVar3, streak + 1, STR_CONV_MODE_LEFT_ALIGN, 1);

    ZeroEnemyPartyMons();
    gPartiesCount[B_TRAINER_OPPONENT_A] = 3;

    u8 iv;
    if (streak < 2)
        iv = 12;
    else if (streak < 4)
        iv = 18;
    else if (streak < 6)
        iv = 24;
    else
        iv = 31;

    u32 i, j;
    u16 chosenSpecies[3];
    u16 chosenItems[3];

    for (i = 0; i < 3; i++)
    {
        u16 sp;
        bool32 dup;
        do
        {
            sp = sJohtoTowerPool[(sSelectedTrainerIdx * 5 + streak * 7 + i * 11) % ARRAY_COUNT(sJohtoTowerPool)];
            dup = FALSE;
            for (j = 0; j < i; j++)
            {
                if (chosenSpecies[j] == sp)
                {
                    dup = TRUE;
                    break;
                }
            }
        } while (dup);
        chosenSpecies[i] = sp;

        u16 item;
        do
        {
            item = sJohtoTowerItems[(streak * 2 + i * 3) % ARRAY_COUNT(sJohtoTowerItems)];
            dup = FALSE;
            for (j = 0; j < i; j++)
            {
                if (chosenItems[j] == item)
                {
                    dup = TRUE;
                    break;
                }
            }
        } while (dup);
        chosenItems[i] = item;

        struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][i];
        CreateMonWithIVs(mon, sp, level, Random32(), OTID_STRUCT_PRESET(0), iv);
        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
        GiveBoxMonInitialMoveset(&mon->box);
        CalculateMonStats(mon);
    }
}

static void CB2_EndJohtoBattleTowerBattle(void)
{
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartJohtoTowerBattle(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = CB2_EndJohtoBattleTowerBattle;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

void JohtoBattleTowerStartBattle(void)
{
    gBattleScripting.specialTrainerBattleType = FACILITY_BATTLE_TOWER;
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
    TRAINER_BATTLE_PARAM.opponentA = sJohtoTowerTrainers[sSelectedTrainerIdx].frontierTrainerId;

    CreateTask(Task_StartJohtoTowerBattle, 1);
    PlayMapChosenOrBattleBGM(0);
    BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
}

void JohtoBattleTowerGetOutcome(void)
{
    gSpecialVar_Result = gBattleOutcome;
}

void JohtoBattleTowerAdvanceStreak(void)
{
    u16 streak = VarGet(VAR_JOHTO_BATTLE_TOWER_STREAK);
    streak++;
    VarSet(VAR_JOHTO_BATTLE_TOWER_STREAK, streak);
    gSpecialVar_Result = streak;
}

void JohtoBattleTowerGivePrizes(void)
{
    u32 i;
    for (i = 0; i < 5; i++)
    {
        u16 item = sVitamins[Random() % ARRAY_COUNT(sVitamins)];
        AddBagItem(item, 1);
    }
    u16 wins = VarGet(VAR_JOHTO_BATTLE_TOWER_WINS);
    VarSet(VAR_JOHTO_BATTLE_TOWER_WINS, wins + 1);
    FlagSet(FLAG_JOHTO_BATTLE_TOWER_WON_CHALLENGE);
}

u8 JohtoBattleTower_GetRoomLevel(void)
{
    return VarGet(VAR_JOHTO_BATTLE_TOWER_LEVEL);
}

u8 JohtoBattleTower_GetStreak(void)
{
    return VarGet(VAR_JOHTO_BATTLE_TOWER_STREAK);
}

u16 JohtoBattleTower_GetWins(void)
{
    return VarGet(VAR_JOHTO_BATTLE_TOWER_WINS);
}
