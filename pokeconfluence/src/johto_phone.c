#include "global.h"
#include "constants/confluence.h"
#include "constants/event_objects.h"
#include "constants/johto_flags.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "johto_phone.h"
#include "map_name_popup.h"
#include "match_call.h"
#include "overworld.h"
#include "random.h"
#include "script.h"
#include "string_util.h"

// POKE-CONFLUENCE: Johto Pokégear Phone System
// Handles Map Card, Phone Card, Radio Card checks, overworld step counter,
// random incoming phone calls, rematch arming, item gift triggers, and authentic dialogues.

struct JohtoPhoneContact
{
    u16 registeredFlag;
    u16 rematchFlag;
    u16 giftFlag;
    const u8 *name;
    const u8 *rematchText;
    const u8 *giftText;
    const u8 *chatText;
};

// Text definitions
static const u8 sText_JoeyName[] = _("JOEY");
static const u8 sText_JoeyRematch[] = _("JOEY: Hey {PLAYER}!\nMy RATTATA is raring to go!\lCome meet me on ROUTE 30 for a rematch!");
static const u8 sText_JoeyChat[] = _("JOEY: Hey {PLAYER}! Just checking in.\nRemember, my RATTATA is in the\ltop percentage of RATTATA!");

static const u8 sText_WadeName[] = _("WADE");
static const u8 sText_WadeGift[] = _("WADE: Hey {PLAYER}! I found a nice BERRY\nin the woods! Come find me on ROUTE 31\lto pick it up!");
static const u8 sText_WadeRematch[] = _("WADE: Hey {PLAYER}! My bug POKéMON evolved\nand got super tough! Let's battle on ROUTE 31!");
static const u8 sText_WadeChat[] = _("WADE: Did you know? Caterpie and Weedle\nlove sugary tree sap in the morning!");

static const u8 sText_RalphName[] = _("RALPH");
static const u8 sText_RalphRematch[] = _("RALPH: Hey there, youngster!\nThe fish are biting and my team is ready!\lBattle me on ROUTE 32!");
static const u8 sText_RalphChat[] = _("RALPH: Patience is everything in fishing,\n{PLAYER}. That and a sturdy rod!");

static const u8 sText_LizName[] = _("LIZ");
static const u8 sText_LizRematch[] = _("LIZ: Hi {PLAYER}!\nLet's battle again! Meet me on ROUTE 32!");
static const u8 sText_LizChat[] = _("LIZ: Guess what? I saw Whitney at the\nGoldenrod Gym the other day!\lShe was so cute!");

static const u8 sText_AnthonyName[] = _("ANTHONY");
static const u8 sText_AnthonyRematch[] = _("ANTHONY: Yo {PLAYER}! My GEODUDE have\nbeen pounding rocks on ROUTE 33!\lLet's clash again!");
static const u8 sText_AnthonyChat[] = _("ANTHONY: Hiking in the rain is tough,\nbut a true mountain man never backs down!");

static const u8 sText_ToddName[] = _("TODD");
static const u8 sText_ToddRematch[] = _("TODD: Hey {PLAYER}! I've been training\nhard near Goldenrod!\lRematch on ROUTE 34?");
static const u8 sText_ToddChat[] = _("TODD: Goldenrod Dept. Store is having\na bargain sale on the rooftop sometime soon!");

static const u8 sText_GinaName[] = _("GINA");
static const u8 sText_GinaGift[] = _("GINA: Hi {PLAYER}! I found a LEAF STONE\nwhile exploring! Meet me on ROUTE 34\lto take it!");
static const u8 sText_GinaRematch[] = _("GINA: Hi {PLAYER}! My POKéMON want to see\nhow strong you've gotten. Come to ROUTE 34!");
static const u8 sText_GinaChat[] = _("GINA: I love taking walks near the ocean\nbreeze by Goldenrod City!");

static const u8 sText_IrwinName[] = _("IRWIN");
static const u8 sText_IrwinChat[] = _("IRWIN: Hello {PLAYER}! It's Irwin!\nHearing your voice always brightens my day!\lKeep up the great work!");

static const u8 sText_AlanName[] = _("ALAN");
static const u8 sText_AlanGift[] = _("ALAN: Hey {PLAYER}! I found a FIRE STONE\nnear the National Park gate!\lPick it up on ROUTE 36!");
static const u8 sText_AlanRematch[] = _("ALAN: Hey {PLAYER}! I studied battle theory\nand I'm ready to test it on ROUTE 36!");
static const u8 sText_AlanChat[] = _("ALAN: Reading battle manuals is great,\nbut real field experience is even better!");

static const u8 sText_DanaName[] = _("DANA");
static const u8 sText_DanaGift[] = _("DANA: Hi {PLAYER}! A wild POKéMON dropped\na THUNDER STONE! Come to ROUTE 38\land take it!");
static const u8 sText_DanaRematch[] = _("DANA: Hi {PLAYER}! Let's have another battle!\nI'm waiting on ROUTE 38!");
static const u8 sText_DanaChat[] = _("DANA: MooMoo Farm milk is so delicious!\nIt restores a lot of POKéMON energy!");

static const u8 sText_ChadName[] = _("CHAD");
static const u8 sText_ChadRematch[] = _("CHAD: Hey {PLAYER}! Let's battle on ROUTE 38!\nMy POKéMON are ready!");
static const u8 sText_ChadChat[] = _("CHAD: Did you know Mr. Pokémon knows\nProfessor Oak personally? Pretty cool, huh?");

static const u8 sText_DerekName[] = _("DEREK");
static const u8 sText_DerekGift[] = _("DEREK: Hi {PLAYER}! My PIKACHU found\na shiny NUGGET! I'm on ROUTE 39, come get it!");
static const u8 sText_DerekChat[] = _("DEREK: PIKACHU's cheeks are just\nthe cutest! Don't you agree?");

static const u8 sText_TullyName[] = _("TULLY");
static const u8 sText_TullyGift[] = _("TULLY: Ahoy {PLAYER}! Reeled in a WATER STONE\nwhile casting on ROUTE 42!\lDrop by and it's yours!");
static const u8 sText_TullyRematch[] = _("TULLY: Ahoy {PLAYER}! My water team is pumped!\nLet's battle on ROUTE 42!");
static const u8 sText_TullyChat[] = _("TULLY: The sea breeze in Olivine City\nis refreshing after a long trek!");

static const u8 sText_BrentName[] = _("BRENT");
static const u8 sText_BrentRematch[] = _("BRENT: Heheh, {PLAYER}! My rare POKéMON\nwant a challenge! Come to ROUTE 43!");
static const u8 sText_BrentChat[] = _("BRENT: Did you know Bill created the\nPOKéMON Storage System? He's a true genius!");

static const u8 sText_TiffanyName[] = _("TIFFANY");
static const u8 sText_TiffanyGift[] = _("TIFFANY: Hi {PLAYER}! CLEFAIRY found\na pretty PINK BOW! Meet me on ROUTE 43!");
static const u8 sText_TiffanyRematch[] = _("TIFFANY: Hi {PLAYER}! CLEFAIRY and I want\nto battle again on ROUTE 43!");
static const u8 sText_TiffanyChat[] = _("TIFFANY: CLEFAIRY dances under the full moon!\nIt's so magical to watch!");

static const u8 sText_VanceName[] = _("VANCE");
static const u8 sText_VanceRematch[] = _("VANCE: Hey {PLAYER}! The winds are perfect\non ROUTE 44! Let's have a battle!");
static const u8 sText_VanceChat[] = _("VANCE: Soaring with bird POKéMON makes you\nfeel completely free!");

static const u8 sText_WiltonName[] = _("WILTON");
static const u8 sText_WiltonGift[] = _("WILTON: Hello {PLAYER}. I dredged up an\nULTRA BALL on ROUTE 44. You may have it.");
static const u8 sText_WiltonRematch[] = _("WILTON: Hello {PLAYER}. My fishing POKéMON\nare vigorous today. Come to ROUTE 44.");
static const u8 sText_WiltonChat[] = _("WILTON: Quiet waters run deep.\nAlways observe before you strike.");

static const u8 sText_KenjiName[] = _("KENJI");
static const u8 sText_KenjiRematch[] = _("KENJI: WAHAHA {PLAYER}! My fists are burning\non ROUTE 45! Let's spar!");
static const u8 sText_KenjiChat[] = _("KENJI: One thousand push-ups done!\nNow for one thousand squats! KIYAH!");

static const u8 sText_ParryName[] = _("PARRY");
static const u8 sText_ParryRematch[] = _("PARRY: Hey {PLAYER}! My rock heads are\nrock-solid! Rematch on ROUTE 45!");
static const u8 sText_ParryChat[] = _("PARRY: Mountain air makes both humans\nand POKéMON grow sturdy!");

static const u8 sText_ErinName[] = _("ERIN");
static const u8 sText_ErinRematch[] = _("ERIN: Hi {PLAYER}! Let's battle on ROUTE 46!\nWe won't lose this time!");
static const u8 sText_ErinChat[] = _("ERIN: Route 46 has great vantage points\noverlooking New Bark Town!");

static const u8 sText_JackName[] = _("JACK");
static const u8 sText_JackRematch[] = _("JACK: Hey {PLAYER}! I'm practicing at\nNATIONAL PARK! Come test your skills!");
static const u8 sText_JackChat[] = _("JACK: The Bug-Catching Contest at\nNational Park is on Tue, Thu, and Sat!");

static const u8 sText_BeverlyName[] = _("BEVERLY");
static const u8 sText_BeverlyGift[] = _("BEVERLY: Hello dear {PLAYER}! My SNUBBULL\nfound a shiny NUGGET in NATIONAL PARK!\lCome receive it!");
static const u8 sText_BeverlyChat[] = _("BEVERLY: My SNUBBULL may look stern,\nbut it has the gentlest heart!");

static const u8 sText_HueyName[] = _("HUEY");
static const u8 sText_HueyRematch[] = _("HUEY: Ahoy {PLAYER}! My sea legs are steady!\nBattle me at OLIVINE LIGHTHOUSE!");
static const u8 sText_HueyChat[] = _("HUEY: A beacon in the night guides all\nsailors safely into harbor.");

static const u8 sText_GavenName[] = _("GAVEN");
static const u8 sText_GavenRematch[] = _("GAVEN: Greetings {PLAYER}. My team has achieved\npeak synergy on ROUTE 26. Come test your might!");
static const u8 sText_GavenChat[] = _("GAVEN: Only thorough preparation yields\nvictory against Elite trainers.");

static const u8 sText_BethName[] = _("BETH");
static const u8 sText_BethRematch[] = _("BETH: Hello {PLAYER}. On ROUTE 26, only the\ndisciplined prevail. Let us battle once more.");
static const u8 sText_BethChat[] = _("BETH: Every loss teaches more than a hundred\neffortless victories.");

static const u8 sText_JoseName[] = _("JOSE");
static const u8 sText_JoseGift[] = _("JOSE: Hey {PLAYER}! FARFETCH'D picked up\na STAR PIECE on ROUTE 27! Come get it!");
static const u8 sText_JoseRematch[] = _("JOSE: Hey {PLAYER}! My flying squad is ready\nto duel on ROUTE 27!");
static const u8 sText_JoseChat[] = _("JOSE: A leek in hand and wings in the wind--\nthat's how FARFETCH'D rolls!");

static const u8 sText_ReenaName[] = _("REENA");
static const u8 sText_ReenaRematch[] = _("REENA: {PLAYER}! I won't accept defeat from\nanyone! Battle me again on ROUTE 27!");
static const u8 sText_ReenaChat[] = _("REENA: Confidence is everything!\nNever hesitate in the middle of a battle!");

static const u8 sText_MomName[] = _("MOM");
static const u8 sText_MomChat[] = _("MOM: Hi {PLAYER}! How are you doing?\nRemember to rest your POKéMON and save\lyour progress often!");

static const u8 sText_ElmName[] = _("PROF. ELM");
static const u8 sText_ElmChat[] = _("PROF. ELM: Hello {PLAYER}!\nHow is the POKéDEX coming along?\lDiscovering new species is research's thrill!");
static const u8 sText_ElmTogepiHatchedCall[] = _("PROF. ELM: H-hello, {PLAYER}?\nDid something hatch from the EGG?\pWhat kind of POKéMON is it?\nPlease come show me now!");

static const u8 sText_BillName[] = _("BILL");
static const u8 sText_BillChat[] = _("BILL: Hey {PLAYER}! It's Bill!\nThe POKéMON Storage System is fully synced\lacross Hoenn, Kanto, and Johto!");

// Contact database table
static const struct JohtoPhoneContact sJohtoPhoneContacts[] =
{
    {
        .registeredFlag = FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_JoeyName,
        .rematchText = sText_JoeyRematch,
        .giftText = NULL,
        .chatText = sText_JoeyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_WADE_HAS_ITEM,
        .name = sText_WadeName,
        .rematchText = sText_WadeRematch,
        .giftText = sText_WadeGift,
        .chatText = sText_WadeChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_FISHER_RALPH_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_RalphName,
        .rematchText = sText_RalphRematch,
        .giftText = NULL,
        .chatText = sText_RalphChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_PICNICKER_LIZ_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_LizName,
        .rematchText = sText_LizRematch,
        .giftText = NULL,
        .chatText = sText_LizChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_HIKER_ANTHONY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_AnthonyName,
        .rematchText = sText_AnthonyRematch,
        .giftText = NULL,
        .chatText = sText_AnthonyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_CAMPER_TODD_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_ToddName,
        .rematchText = sText_ToddRematch,
        .giftText = NULL,
        .chatText = sText_ToddChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_PICNICKER_GINA_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_GINA_HAS_LEAF_STONE,
        .name = sText_GinaName,
        .rematchText = sText_GinaRematch,
        .giftText = sText_GinaGift,
        .chatText = sText_GinaChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_JUGGLER_IRWIN_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = 0,
        .name = sText_IrwinName,
        .rematchText = NULL,
        .giftText = NULL,
        .chatText = sText_IrwinChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_SCHOOLBOY_ALAN_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_ALAN_HAS_FIRE_STONE,
        .name = sText_AlanName,
        .rematchText = sText_AlanRematch,
        .giftText = sText_AlanGift,
        .chatText = sText_AlanChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_LASS_DANA_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_DANA_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_DANA_HAS_THUNDERSTONE,
        .name = sText_DanaName,
        .rematchText = sText_DanaRematch,
        .giftText = sText_DanaGift,
        .chatText = sText_DanaChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_SCHOOLBOY_CHAD_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_CHAD_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_ChadName,
        .rematchText = sText_ChadRematch,
        .giftText = NULL,
        .chatText = sText_ChadChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_POKEFANM_DEREK_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = FLAG_JOHTO_ENGINE_DEREK_HAS_NUGGET,
        .name = sText_DerekName,
        .rematchText = NULL,
        .giftText = sText_DerekGift,
        .chatText = sText_DerekChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_FISHER_TULLY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_TULLY_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_TULLY_HAS_WATER_STONE,
        .name = sText_TullyName,
        .rematchText = sText_TullyRematch,
        .giftText = sText_TullyGift,
        .chatText = sText_TullyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_POKEMANIAC_BRENT_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_BrentName,
        .rematchText = sText_BrentRematch,
        .giftText = NULL,
        .chatText = sText_BrentChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_PICNICKER_TIFFANY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_TIFFANY_HAS_PINK_BOW,
        .name = sText_TiffanyName,
        .rematchText = sText_TiffanyRematch,
        .giftText = sText_TiffanyGift,
        .chatText = sText_TiffanyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_BIRDKEEPER_VANCE_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_VanceName,
        .rematchText = sText_VanceRematch,
        .giftText = NULL,
        .chatText = sText_VanceChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_FISHER_WILTON_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_WILTON_HAS_ITEM,
        .name = sText_WiltonName,
        .rematchText = sText_WiltonRematch,
        .giftText = sText_WiltonGift,
        .chatText = sText_WiltonChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_BLACKBELT_KENJI_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = 0,
        .name = sText_KenjiName,
        .rematchText = NULL,
        .giftText = NULL,
        .chatText = sText_KenjiChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_HIKER_PARRY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_PARRY_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_ParryName,
        .rematchText = sText_ParryRematch,
        .giftText = NULL,
        .chatText = sText_ParryChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_PICNICKER_ERIN_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_ErinName,
        .rematchText = sText_ErinRematch,
        .giftText = NULL,
        .chatText = sText_ErinChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_SCHOOLBOY_JACK_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_JACK_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_JackName,
        .rematchText = sText_JackRematch,
        .giftText = NULL,
        .chatText = sText_JackChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_POKEFAN_BEVERLY_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = FLAG_JOHTO_ENGINE_BEVERLY_HAS_NUGGET,
        .name = sText_BeverlyName,
        .rematchText = NULL,
        .giftText = sText_BeverlyGift,
        .chatText = sText_BeverlyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_SAILOR_HUEY_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_HUEY_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_HueyName,
        .rematchText = sText_HueyRematch,
        .giftText = NULL,
        .chatText = sText_HueyChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_COOLTRAINERM_GAVEN_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_GAVEN_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_GavenName,
        .rematchText = sText_GavenRematch,
        .giftText = NULL,
        .chatText = sText_GavenChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_COOLTRAINERF_BETH_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_BETH_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_BethName,
        .rematchText = sText_BethRematch,
        .giftText = NULL,
        .chatText = sText_BethChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_BIRDKEEPER_JOSE_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_JOSE_READY_FOR_REMATCH,
        .giftFlag = FLAG_JOHTO_ENGINE_JOSE_HAS_STAR_PIECE,
        .name = sText_JoseName,
        .rematchText = sText_JoseRematch,
        .giftText = sText_JoseGift,
        .chatText = sText_JoseChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_COOLTRAINERF_REENA_REGISTERED,
        .rematchFlag = FLAG_JOHTO_ENGINE_REENA_READY_FOR_REMATCH,
        .giftFlag = 0,
        .name = sText_ReenaName,
        .rematchText = sText_ReenaRematch,
        .giftText = NULL,
        .chatText = sText_ReenaChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_MOM_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = 0,
        .name = sText_MomName,
        .rematchText = NULL,
        .giftText = NULL,
        .chatText = sText_MomChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_ELM_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = 0,
        .name = sText_ElmName,
        .rematchText = NULL,
        .giftText = NULL,
        .chatText = sText_ElmChat,
    },
    {
        .registeredFlag = FLAG_JOHTO_PHONE_BILL_REGISTERED,
        .rematchFlag = 0,
        .giftFlag = 0,
        .name = sText_BillName,
        .rematchText = NULL,
        .giftText = NULL,
        .chatText = sText_BillChat,
    },
};

static EWRAM_DATA u16 sJohtoPhoneStepCounter = 0;

bool32 Johto_HasMapCard(void)
{
    return FlagGet(FLAG_JOHTO_ENGINE_MAP_CARD);
}

bool32 Johto_HasPhoneCard(void)
{
    return FlagGet(FLAG_JOHTO_ENGINE_PHONE_CARD);
}

bool32 Johto_HasRadioCard(void)
{
    return FlagGet(FLAG_JOHTO_ENGINE_RADIO_CARD);
}

u32 Johto_GetRegisteredPhoneCount(void)
{
    u32 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(sJohtoPhoneContacts); i++)
    {
        if (FlagGet(sJohtoPhoneContacts[i].registeredFlag))
            count++;
    }

    return count;
}

static bool32 MapAllowsJohtoPhoneCall(void)
{
    u8 mapType;

    if (ScriptContext_IsEnabled() || IsMatchCallTaskActive())
        return FALSE;

    mapType = GetMapTypeByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
    switch (mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
    case MAP_TYPE_OCEAN_ROUTE:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 TryStartJohtoPhoneCall(void)
{
    const struct JohtoPhoneContact *candidates[ARRAY_COUNT(sJohtoPhoneContacts)];
    const struct JohtoPhoneContact *selected;
    u32 i, candidateCount = 0;
    const u8 *msg = NULL;

    if (!FlagGet(FLAG_JOHTO_ENGINE_POKEGEAR) || !FlagGet(FLAG_JOHTO_ENGINE_PHONE_CARD))
        return FALSE;

    if (!MapAllowsJohtoPhoneCall())
        return FALSE;

    // Check step interval (~60 steps between checks)
    if (++sJohtoPhoneStepCounter < 60)
        return FALSE;

    sJohtoPhoneStepCounter = 0;

    // POKE-CONFLUENCE: Authentic Crystal Elm Togepi hatch priority phone call
    if (FlagGet(FLAG_JOHTO_TOGEPI_HATCHED) && !FlagGet(FLAG_JOHTO_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE) && !FlagGet(FLAG_JOHTO_SHOWED_TOGEPI_TO_ELM))
    {
        FlagSet(FLAG_JOHTO_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE);
        StartJohtoPhoneCall(sText_ElmTogepiHatchedCall);
        return TRUE;
    }

    // 25% chance when step threshold is reached
    if ((Random() % 4) != 0)
        return FALSE;

    // Collect registered contacts
    for (i = 0; i < ARRAY_COUNT(sJohtoPhoneContacts); i++)
    {
        if (FlagGet(sJohtoPhoneContacts[i].registeredFlag))
            candidates[candidateCount++] = &sJohtoPhoneContacts[i];
    }

    if (candidateCount == 0)
        return FALSE;

    selected = candidates[Random() % candidateCount];

    // Priority 1: Rematch challenge if not yet armed
    if (selected->rematchFlag != 0 && !FlagGet(selected->rematchFlag) && selected->rematchText != NULL)
    {
        FlagSet(selected->rematchFlag);
        msg = selected->rematchText;
    }
    // Priority 2: Gift notification if not yet armed
    else if (selected->giftFlag != 0 && !FlagGet(selected->giftFlag) && selected->giftText != NULL)
    {
        FlagSet(selected->giftFlag);
        msg = selected->giftText;
    }
    // Priority 3: General chat / flavor call
    else if (selected->chatText != NULL)
    {
        msg = selected->chatText;
    }

    if (msg != NULL)
    {
        StartJohtoPhoneCall(msg);
        return TRUE;
    }

    return FALSE;
}

void Johto_ArmRandomRematch(void)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sJohtoPhoneContacts); i++)
    {
        if (FlagGet(sJohtoPhoneContacts[i].registeredFlag) && sJohtoPhoneContacts[i].rematchFlag != 0)
        {
            FlagSet(sJohtoPhoneContacts[i].rematchFlag);
        }
    }
}
