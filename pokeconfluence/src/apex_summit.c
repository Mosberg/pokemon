#include "global.h"
#include "apex_summit.h"
#include "battle.h"
#include "battle_setup.h"
#include "confluence.h"
#include "event_data.h"
#include "item.h"
#include "main.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "strings.h"
#include "constants/battle.h"
#include "constants/decorations.h"
#include "constants/event_objects.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/opponents.h"
#include "constants/opponents_johto.h"
#include "constants/vars.h"
#include "constants/confluence.h"

// POKE-CONFLUENCE: Apex Summit 24-Leader Boss Gauntlet Subsystem

struct ApexSummitContender
{
    u16 trainerId;
    u16 gfxId;
    u8 tier; // 0 = Gym Leader, 1 = Elite Four, 2 = Champion
    const u8 *name;
    const u8 *introText;
    const u8 *defeatText;
};

// Contender speech strings
static const u8 sText_Brock_Name[] = _("BROCK");
static const u8 sText_Brock_Intro[] = _("I am BROCK, the Pewter Gym Leader!\nMy rock-hard willpower will test you!$");
static const u8 sText_Brock_Defeat[] = _("Your willpower is harder than bedrock!$");

static const u8 sText_Misty_Name[] = _("MISTY");
static const u8 sText_Misty_Intro[] = _("I am MISTY, the Tomboyish Mermaid!\nPrepare to be washed away by my team!$");
static const u8 sText_Misty_Defeat[] = _("You're much too good for me!$");

static const u8 sText_LtSurge_Name[] = _("LT. SURGE");
static const u8 sText_LtSurge_Intro[] = _("Ten-hut! LT. SURGE is ready for battle!\nMy electric Pokémon will shock you!$");
static const u8 sText_LtSurge_Defeat[] = _("Argh! Your combat power is staggering!$");

static const u8 sText_Erika_Name[] = _("ERIKA");
static const u8 sText_Erika_Intro[] = _("Hello. I am ERIKA from Celadon.\nPlease allow my blossoms to test you.$");
static const u8 sText_Erika_Defeat[] = _("I concede defeat... You are remarkably strong.$");

static const u8 sText_Janine_Name[] = _("JANINE");
static const u8 sText_Janine_Intro[] = _("I am JANINE, the Poisonous Ninja Master!\nYou cannot dodge my shadow techniques!$");
static const u8 sText_Janine_Defeat[] = _("You saw right through my ninjutsu!$");

static const u8 sText_Sabrina_Name[] = _("SABRINA");
static const u8 sText_Sabrina_Intro[] = _("I foresaw your arrival at the summit.\nI am SABRINA. Witness true psychic power!$");
static const u8 sText_Sabrina_Defeat[] = _("Your power exceeded my psychic foresight...$");

static const u8 sText_Blaine_Name[] = _("BLAINE");
static const u8 sText_Blaine_Intro[] = _("Hah! BLAINE the Hotheaded Quiz Master!\nCan your team handle my scorching flames?!$");
static const u8 sText_Blaine_Defeat[] = _("I've been extinguished! A brilliant burn!$");

static const u8 sText_Blue_Name[] = _("BLUE");
static const u8 sText_Blue_Intro[] = _("Yo! BLUE here! Think you've conquered\nall three regions? Show me your best!$");
static const u8 sText_Blue_Defeat[] = _("What?! Unbelievable... You're the real deal.$");

static const u8 sText_Falkner_Name[] = _("FALKNER");
static const u8 sText_Falkner_Intro[] = _("I am FALKNER of Violet City!\nFeel the wind from our majestic wings!$");
static const u8 sText_Falkner_Defeat[] = _("Our wings have been clipped by your greatness.$");

static const u8 sText_Bugsy_Name[] = _("BUGSY");
static const u8 sText_Bugsy_Intro[] = _("I am BUGSY, the bug encyclopedia!\nNever underestimate bug Pokémon!$");
static const u8 sText_Bugsy_Defeat[] = _("Whoa, amazing! You really know your stuff!$");

static const u8 sText_Whitney_Name[] = _("WHITNEY");
static const u8 sText_Whitney_Intro[] = _("Hi! I am WHITNEY!\nMy cute Pokémon pack a monstrous punch!$");
static const u8 sText_Whitney_Defeat[] = _("Waaah! You're mean! But so strong...$");

static const u8 sText_Morty_Name[] = _("MORTY");
static const u8 sText_Morty_Intro[] = _("I am MORTY. The ancient spirits whisper\nthat you are a worthy summit challenger.$");
static const u8 sText_Morty_Defeat[] = _("The spirits were right... Magnificent.$");

static const u8 sText_Chuck_Name[] = _("CHUCK");
static const u8 sText_Chuck_Intro[] = _("WAHAHA! I am CHUCK of Cianwood!\nTwenty-four hours of training begins now!$");
static const u8 sText_Chuck_Defeat[] = _("Gwah! I've been tossed over the mountain!$");

static const u8 sText_Jasmine_Name[] = _("JASMINE");
static const u8 sText_Jasmine_Intro[] = _("I am JASMINE of Olivine...\nSteel looks cold, but our spirit burns hot!$");
static const u8 sText_Jasmine_Defeat[] = _("Your radiant strength is truly dazzling...$");

static const u8 sText_Pryce_Name[] = _("PRYCE");
static const u8 sText_Pryce_Intro[] = _("I am PRYCE. Fifty years of winter have\ntempered my Pokémon and my spirit.$");
static const u8 sText_Pryce_Defeat[] = _("A warming fire... Your bond is formidable.$");

static const u8 sText_Clair_Name[] = _("CLAIR");
static const u8 sText_Clair_Intro[] = _("I am CLAIR, the dragon master!\nOnly the greatest can match my dragons!$");
static const u8 sText_Clair_Defeat[] = _("I lost?! I acknowledge your supreme power!$");

static const u8 sText_Roxanne_Name[] = _("ROXANNE");
static const u8 sText_Roxanne_Intro[] = _("I am ROXANNE of Rustboro!\nLet me test your tactical mastery!$");
static const u8 sText_Roxanne_Defeat[] = _("A stellar demonstration of competitive skill!$");

static const u8 sText_Brawly_Name[] = _("BRAWLY");
static const u8 sText_Brawly_Intro[] = _("I am BRAWLY! Let's see if you can ride\nthe massive waves of my fighting spirit!$");
static const u8 sText_Brawly_Defeat[] = _("Whoa! You wiped me right out!$");

static const u8 sText_Wattson_Name[] = _("WATTSON");
static const u8 sText_Wattson_Intro[] = _("WAHAHAHA! WATTSON here!\nPrepare to be completely electrified!$");
static const u8 sText_Wattson_Defeat[] = _("Wahahaha! You gave me quite a jolt!$");

static const u8 sText_Flannery_Name[] = _("FLANNERY");
static const u8 sText_Flannery_Intro[] = _("I am FLANNERY of Lavaridge!\nOur fiery passions will scorch the summit!$");
static const u8 sText_Flannery_Defeat[] = _("I burned out! What incredible intensity!$");

static const u8 sText_Norman_Name[] = _("NORMAN");
static const u8 sText_Norman_Intro[] = _("I am NORMAN. Let us battle with all our\nmight, without holding anything back.$");
static const u8 sText_Norman_Defeat[] = _("A proud battle. You have surpassed all limits.$");

static const u8 sText_Winona_Name[] = _("WINONA");
static const u8 sText_Winona_Intro[] = _("I am WINONA. We soar on graceful winds\nbeyond the highest mountain clouds.$");
static const u8 sText_Winona_Defeat[] = _("Our flight path was guided by your brilliance.$");

static const u8 sText_TateLiza_Name[] = _("TATE & LIZA");
static const u8 sText_TateLiza_Intro[] = _("We are TATE and LIZA!\nOur telepathic combination is invincible!$");
static const u8 sText_TateLiza_Defeat[] = _("Our synergy was broken by your mastery!$");

static const u8 sText_Juan_Name[] = _("JUAN");
static const u8 sText_Juan_Intro[] = _("I am JUAN! Witness the magnificent water\nartistry that guided Wallace himself!$");
static const u8 sText_Juan_Defeat[] = _("Bravo! A truly exquisite performance!$");

// Elite Four contenders
static const u8 sText_Will_Name[] = _("WILL");
static const u8 sText_Will_Intro[] = _("I am WILL. My training around the world\nhas made my psychic team flawless!$");
static const u8 sText_Will_Defeat[] = _("Even after all my training... You won!$");

static const u8 sText_Koga_Name[] = _("KOGA");
static const u8 sText_Koga_Intro[] = _("Fwahahaha! KOGA of the Elite Four!\nExperience the agony of my ninja venom!$");
static const u8 sText_Koga_Defeat[] = _("You possess the true heart of a shinobi.$");

static const u8 sText_Bruno_Name[] = _("BRUNO");
static const u8 sText_Bruno_Intro[] = _("I am BRUNO! We have trained with rock\nand steel to forge the ultimate power!$");
static const u8 sText_Bruno_Defeat[] = _("Our strength fell short... A tremendous battle!$");

static const u8 sText_Karen_Name[] = _("KAREN");
static const u8 sText_Karen_Intro[] = _("I am KAREN of the Elite Four.\nStrong Pokémon. Weak Pokémon. Truly skilled\ntrainers win with their favorites.$");
static const u8 sText_Karen_Defeat[] = _("You understand what truly matters.$");

static const u8 sText_Sidney_Name[] = _("SIDNEY");
static const u8 sText_Sidney_Intro[] = _("Welcome! I am SIDNEY of the Elite Four!\nLet's enjoy this battle to the absolute max!$");
static const u8 sText_Sidney_Defeat[] = _("Haha! That was an awesome blast!$");

static const u8 sText_Phoebe_Name[] = _("PHOEBE");
static const u8 sText_Phoebe_Intro[] = _("I am PHOEBE! The spirits on Mt. Pyre\nempowered my bond with ghost Pokémon!$");
static const u8 sText_Phoebe_Defeat[] = _("Oh, darn! My spirits couldn't frighten you!$");

static const u8 sText_Glacia_Name[] = _("GLACIA");
static const u8 sText_Glacia_Intro[] = _("I am GLACIA. I traveled from afar to\nhone my mastery over freezing ice!$");
static const u8 sText_Glacia_Defeat[] = _("My ice could not withstand your burning spirit.$");

static const u8 sText_Drake_Name[] = _("DRAKE");
static const u8 sText_Drake_Intro[] = _("I am DRAKE! Dragons are wild and proud!\nShow me what it means to trust your team!$");
static const u8 sText_Drake_Defeat[] = _("Splendid! You understand the heart of battle.$");

static const u8 sText_Kestrel_Name[] = _("KESTREL");
static const u8 sText_Kestrel_Intro[] = _("I am KESTREL, Warden of Kanto!\nLet's see if you can conquer Kanto's peak!$");
static const u8 sText_Kestrel_Defeat[] = _("Kanto's winds bow to you.$");

static const u8 sText_Maren_Name[] = _("MAREN");
static const u8 sText_Maren_Intro[] = _("I am MAREN, Warden of Johto!\nAscend higher, challenger, if you dare!$");
static const u8 sText_Maren_Defeat[] = _("Johto's towers ring for you.$");

static const u8 sText_Orville_Name[] = _("ORVILLE");
static const u8 sText_Orville_Intro[] = _("I am ORVILLE, Warden of Hoenn!\nLet the ancient oceanic depths test you!$");
static const u8 sText_Orville_Defeat[] = _("Hoenn's seas part for you.$");

// Champion contenders
static const u8 sText_Lance_Name[] = _("LANCE");
static const u8 sText_Lance_Intro[] = _("I am LANCE, the Dragon Master Champion!\nThere is no need for words. Let us battle!$");
static const u8 sText_Lance_Defeat[] = _("You are truly worthy of the Champion title!$");

static const u8 sText_Steven_Name[] = _("STEVEN");
static const u8 sText_Steven_Intro[] = _("Welcome. I am STEVEN. Together with my team,\nwe have unearthed the ultimate bond of steel!$");
static const u8 sText_Steven_Defeat[] = _("Marvelous... You are an extraordinary trainer.$");

static const u8 sText_Wallace_Name[] = _("WALLACE");
static const u8 sText_Wallace_Intro[] = _("I am WALLACE! I shall choreograph a dance\nof sheer elegance and unstoppable power!$");
static const u8 sText_Wallace_Defeat[] = _("Dazzling! You have bathed the summit in glory!$");

static const u8 sText_Red_Name[] = _("RED");
static const u8 sText_Red_Intro[] = _("... ... ...\n... ... ...!$");
static const u8 sText_Red_Defeat[] = _("...!$");

static const u8 sText_SummitRed_Name[] = _("SUMMIT RED");
static const u8 sText_SummitRed_Intro[] = _("... ... ...\n(The Apex Champion awaits your challenge!)$");
static const u8 sText_SummitRed_Defeat[] = _("... ... ...!$");

// Master table of all 40 contenders
static const struct ApexSummitContender sApexContenders[] =
{
    // 0..23: 24 Gym Leaders
    { TRAINER_JOHTO_BROCK_BROCK1,      OBJ_EVENT_GFX_BROCK,       0, sText_Brock_Name,     sText_Brock_Intro,     sText_Brock_Defeat },
    { TRAINER_JOHTO_MISTY_MISTY1,      OBJ_EVENT_GFX_MISTY,       0, sText_Misty_Name,     sText_Misty_Intro,     sText_Misty_Defeat },
    { TRAINER_JOHTO_LT_SURGE_LT_SURGE1,OBJ_EVENT_GFX_LT_SURGE,   0, sText_LtSurge_Name,   sText_LtSurge_Intro,   sText_LtSurge_Defeat },
    { TRAINER_JOHTO_ERIKA_ERIKA1,      OBJ_EVENT_GFX_ERIKA,       0, sText_Erika_Name,     sText_Erika_Intro,     sText_Erika_Defeat },
    { TRAINER_JOHTO_JANINE_JANINE1,    OBJ_EVENT_GFX_LIZA,        0, sText_Janine_Name,    sText_Janine_Intro,    sText_Janine_Defeat },
    { TRAINER_JOHTO_SABRINA_SABRINA1,  OBJ_EVENT_GFX_SABRINA,     0, sText_Sabrina_Name,   sText_Sabrina_Intro,   sText_Sabrina_Defeat },
    { TRAINER_JOHTO_BLAINE_BLAINE1,    OBJ_EVENT_GFX_BLAINE,      0, sText_Blaine_Name,    sText_Blaine_Intro,    sText_Blaine_Defeat },
    { TRAINER_JOHTO_BLUE_BLUE1,        OBJ_EVENT_GFX_BLUE,        0, sText_Blue_Name,      sText_Blue_Intro,      sText_Blue_Defeat },
    { TRAINER_JOHTO_FALKNER_FALKNER1,  OBJ_EVENT_GFX_WALLY,       0, sText_Falkner_Name,   sText_Falkner_Intro,   sText_Falkner_Defeat },
    { TRAINER_JOHTO_BUGSY_BUGSY1,      OBJ_EVENT_GFX_BUG_CATCHER, 0, sText_Bugsy_Name,     sText_Bugsy_Intro,     sText_Bugsy_Defeat },
    { TRAINER_JOHTO_WHITNEY_WHITNEY1,  OBJ_EVENT_GFX_FLANNERY,    0, sText_Whitney_Name,   sText_Whitney_Intro,   sText_Whitney_Defeat },
    { TRAINER_JOHTO_MORTY_MORTY1,      OBJ_EVENT_GFX_CHANNELER,   0, sText_Morty_Name,     sText_Morty_Intro,     sText_Morty_Defeat },
    { TRAINER_JOHTO_CHUCK_CHUCK1,      OBJ_EVENT_GFX_BRAWLY,      0, sText_Chuck_Name,     sText_Chuck_Intro,     sText_Chuck_Defeat },
    { TRAINER_JOHTO_JASMINE_JASMINE1,  OBJ_EVENT_GFX_ANABEL,      0, sText_Jasmine_Name,   sText_Jasmine_Intro,   sText_Jasmine_Defeat },
    { TRAINER_JOHTO_PRYCE_PRYCE1,      OBJ_EVENT_GFX_SPENSER,     0, sText_Pryce_Name,     sText_Pryce_Intro,     sText_Pryce_Defeat },
    { TRAINER_JOHTO_CLAIR_CLAIR1,      OBJ_EVENT_GFX_LUCY,        0, sText_Clair_Name,     sText_Clair_Intro,     sText_Clair_Defeat },
    { TRAINER_ROXANNE_5,               OBJ_EVENT_GFX_ROXANNE,     0, sText_Roxanne_Name,   sText_Roxanne_Intro,   sText_Roxanne_Defeat },
    { TRAINER_BRAWLY_5,                OBJ_EVENT_GFX_BRAWLY,      0, sText_Brawly_Name,    sText_Brawly_Intro,    sText_Brawly_Defeat },
    { TRAINER_WATTSON_5,               OBJ_EVENT_GFX_WATTSON,     0, sText_Wattson_Name,   sText_Wattson_Intro,   sText_Wattson_Defeat },
    { TRAINER_FLANNERY_5,              OBJ_EVENT_GFX_FLANNERY,    0, sText_Flannery_Name,  sText_Flannery_Intro,  sText_Flannery_Defeat },
    { TRAINER_NORMAN_5,                OBJ_EVENT_GFX_NORMAN,      0, sText_Norman_Name,    sText_Norman_Intro,    sText_Norman_Defeat },
    { TRAINER_WINONA_5,                OBJ_EVENT_GFX_WINONA,      0, sText_Winona_Name,    sText_Winona_Intro,    sText_Winona_Defeat },
    { TRAINER_TATE_AND_LIZA_5,         OBJ_EVENT_GFX_TATE,        0, sText_TateLiza_Name,  sText_TateLiza_Intro,  sText_TateLiza_Defeat },
    { TRAINER_JUAN_5,                  OBJ_EVENT_GFX_JUAN,        0, sText_Juan_Name,      sText_Juan_Intro,      sText_Juan_Defeat },

    // 24..34: 11 Elite Four
    { TRAINER_JOHTO_WILL_WILL1,        OBJ_EVENT_GFX_LUCY,        1, sText_Will_Name,      sText_Will_Intro,      sText_Will_Defeat },
    { TRAINER_JOHTO_KOGA_KOGA1,        OBJ_EVENT_GFX_KOGA,        1, sText_Koga_Name,      sText_Koga_Intro,      sText_Koga_Defeat },
    { TRAINER_JOHTO_BRUNO_BRUNO1,      OBJ_EVENT_GFX_BRUNO,       1, sText_Bruno_Name,     sText_Bruno_Intro,     sText_Bruno_Defeat },
    { TRAINER_JOHTO_KAREN_KAREN1,      OBJ_EVENT_GFX_ANABEL,      1, sText_Karen_Name,     sText_Karen_Intro,     sText_Karen_Defeat },
    { TRAINER_SIDNEY,                  OBJ_EVENT_GFX_SIDNEY,      1, sText_Sidney_Name,    sText_Sidney_Intro,    sText_Sidney_Defeat },
    { TRAINER_PHOEBE,                  OBJ_EVENT_GFX_PHOEBE,      1, sText_Phoebe_Name,    sText_Phoebe_Intro,    sText_Phoebe_Defeat },
    { TRAINER_GLACIA,                  OBJ_EVENT_GFX_GLACIA,      1, sText_Glacia_Name,    sText_Glacia_Intro,    sText_Glacia_Defeat },
    { TRAINER_DRAKE,                   OBJ_EVENT_GFX_DRAKE,       1, sText_Drake_Name,     sText_Drake_Intro,     sText_Drake_Defeat },
    { TRAINER_APEX_KANTO,              OBJ_EVENT_GFX_BLUE,        1, sText_Kestrel_Name,   sText_Kestrel_Intro,   sText_Kestrel_Defeat },
    { TRAINER_APEX_JOHTO,              OBJ_EVENT_GFX_LANCE,       1, sText_Maren_Name,     sText_Maren_Intro,     sText_Maren_Defeat },
    { TRAINER_APEX_HOENN,              OBJ_EVENT_GFX_STEVEN,      1, sText_Orville_Name,   sText_Orville_Intro,   sText_Orville_Defeat },

    // 35..39: 5 Champions & Legends
    { TRAINER_JOHTO_CHAMPION_LANCE,    OBJ_EVENT_GFX_LANCE,       2, sText_Lance_Name,     sText_Lance_Intro,     sText_Lance_Defeat },
    { TRAINER_STEVEN,                  OBJ_EVENT_GFX_STEVEN,      2, sText_Steven_Name,    sText_Steven_Intro,    sText_Steven_Defeat },
    { TRAINER_WALLACE,                 OBJ_EVENT_GFX_WALLACE,     2, sText_Wallace_Name,   sText_Wallace_Intro,   sText_Wallace_Defeat },
    { TRAINER_RED,                     OBJ_EVENT_GFX_RED,         2, sText_Red_Name,       sText_Red_Intro,       sText_Red_Defeat },
    { TRAINER_APEX_CHAMPION,           OBJ_EVENT_GFX_RED,         2, sText_SummitRed_Name, sText_SummitRed_Intro, sText_SummitRed_Defeat },
};

// Generates a random 5-round tournament bracket and saves to persistent vars
void ApexSummit_GenerateBracket(void)
{
    u8 r1, r2, r3, r4, r5;

    // Round 1: Gym Leader (0..23)
    r1 = Random() % 24;

    // Round 2: Distinct Gym Leader (0..23)
    do {
        r2 = Random() % 24;
    } while (r2 == r1);

    // Round 3: Elite Four member (24..34)
    r3 = 24 + (Random() % 11);

    // Round 4: Elite Four or Champion (24..38)
    do {
        r4 = 24 + (Random() % 15);
    } while (r4 == r3);

    // Round 5: Apex Legend Champion (35..39)
    r5 = 35 + (Random() % 5);

    VarSet(VAR_APEX_OPPONENT_0, r1);
    VarSet(VAR_APEX_OPPONENT_1, r2);
    VarSet(VAR_APEX_OPPONENT_2, r3);
    VarSet(VAR_APEX_OPPONENT_3, r4);
    VarSet(VAR_APEX_OPPONENT_4, r5);

    VarSet(VAR_APEX_CURRENT_ROUND, 0);
    FlagSet(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE);
}

// Configures current round's contender sprite, name, and intro lines
void ApexSummit_SetUpCurrentRound(void)
{
    u8 round = VarGet(VAR_APEX_CURRENT_ROUND);
    u8 contenderIdx;
    const struct ApexSummitContender *contender;

    if (round >= APEX_ROUNDS_COUNT)
        round = APEX_ROUNDS_COUNT - 1;

    contenderIdx = VarGet(VAR_APEX_OPPONENT_0 + round);
    if (contenderIdx >= ARRAY_COUNT(sApexContenders))
        contenderIdx = 0;

    contender = &sApexContenders[contenderIdx];

    // Set dynamic sprite tag for contender object event
    VarSet(VAR_OBJ_GFX_ID_0, contender->gfxId);

    // Buffer strings for scripts:
    // STR_VAR_1: Contender Name
    // STR_VAR_2: Current Round (1..5)
    // STR_VAR_3: Next Round (2..5)
    // STR_VAR_4: Intro Text
    StringCopy(gStringVar1, contender->name);
    ConvertIntToDecimalStringN(gStringVar2, round + 1, STR_CONV_MODE_LEFT_ALIGN, 1);
    ConvertIntToDecimalStringN(gStringVar3, round + 2, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringCopy(gStringVar4, contender->introText);
}

// Initiates the Level 100 battle with the current contender
void ApexSummit_StartBattle(void)
{
    u8 round = VarGet(VAR_APEX_CURRENT_ROUND);
    u8 contenderIdx;
    u16 trainerId;

    if (round >= APEX_ROUNDS_COUNT)
        round = APEX_ROUNDS_COUNT - 1;

    contenderIdx = VarGet(VAR_APEX_OPPONENT_0 + round);
    if (contenderIdx >= ARRAY_COUNT(sApexContenders))
        contenderIdx = 0;

    trainerId = sApexContenders[contenderIdx].trainerId;

    InitTrainerBattleParameter();
    TRAINER_BATTLE_PARAM.opponentA = trainerId;
    TRAINER_BATTLE_PARAM.opponentB = 0xFFFF;
    TRAINER_BATTLE_PARAM.skipFlagCheck = TRUE;
    TRAINER_BATTLE_PARAM.continueScript = TRUE;
    TRAINER_BATTLE_PARAM.defeatTextA = (u8 *)sApexContenders[contenderIdx].defeatText;

    BattleSetup_StartTrainerBattle();
}

// Advanced round tracking, party heal, and completion evaluation
void ApexSummit_OnRoundWon(void)
{
    u8 round = VarGet(VAR_APEX_CURRENT_ROUND) + 1;
    VarSet(VAR_APEX_CURRENT_ROUND, round);
    HealPlayerParty();

    if (round >= APEX_ROUNDS_COUNT)
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

// Awards Apex Champion Trophy, Ribbon, Trainer Card Star, and lifts level cap to 100
void ApexSummit_AwardPrizes(void)
{
    u32 i;
    u8 ribbonVal = TRUE;

    FlagSet(FLAG_CONFLUENCE_APEX_CHAMPION);
    FlagClear(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE);
    VarSet(VAR_APEX_STREAK, VarGet(VAR_APEX_STREAK) + 1);

    // Award the Victory Ribbon to all participating party Pokémon
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SANITY_HAS_SPECIES)
         && !GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SANITY_IS_EGG))
        {
            SetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_VICTORY_RIBBON, &ribbonVal);
        }
    }
    IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
    FlagSet(FLAG_SYS_RIBBON_GET);
}

// Safely forfeits or exits the challenge
void ApexSummit_ExitChallenge(void)
{
    FlagClear(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE);
    HealPlayerParty();
}
