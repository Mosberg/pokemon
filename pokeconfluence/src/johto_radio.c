#include "global.h"
#include "event_data.h"
#include "sound.h"
#include "constants/songs.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "constants/species.h"
#include "constants/johto_flags.h"
#include "johto_radio.h"
#include "johto_swarms.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "overworld.h"
#include "field_message_box.h"
#include "script.h"
#include "regions.h"
#include "random.h"
#include "rtc.h"

// POKE-CONFLUENCE: Authentic Johto Pokégear Radio Subsystem (from pokecrystal radio.asm)

bool8 sPokenavWantsToOpenRadio = FALSE;

bool32 Johto_HasExpnCard(void)
{
    return FlagGet(FLAG_JOHTO_ENGINE_EXPN_CARD);
}

u8 Johto_GetActiveRadioStation(void)
{
    return (u8)VarGet(VAR_JOHTO_RADIO_STATION);
}

u8 Johto_GetActiveRadioMusicEffect(void)
{
    return (u8)VarGet(VAR_JOHTO_RADIO_EFFECT);
}

void Johto_ApplyRadioMusicRateMod(u32 *encounterRate)
{
    u8 effect = Johto_GetActiveRadioMusicEffect();

    if (effect == RADIO_EFFECT_MARCH)
    {
        // Pokémon March: boosts wild encounter rate by 50%
        *encounterRate = (*encounterRate * 3) / 2;
    }
    else if (effect == RADIO_EFFECT_LULLABY)
    {
        // Pokémon Lullaby: cuts wild encounter rate by 50%
        *encounterRate = *encounterRate / 2;
    }
}

bool8 Johto_IsPokeFluteRadioPlaying(void)
{
    return FlagGet(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);
}

void Johto_TurnOffRadio(void)
{
    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_OFF);
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    FlagClear(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);
    Overworld_PlaySpecialMapMusic();
}

// Authentic Buena's Password Table (from pokecrystal buenas_passwords.asm)
#define NUM_BUENA_CATEGORIES 11
#define NUM_BUENA_OPTIONS    3

static const u8 sBuenaCategory_Starters[NUM_BUENA_OPTIONS][16] = {
    _("CYNDAQUIL"),
    _("TOTODILE"),
    _("CHIKORITA")
};

static const u8 sBuenaCategory_Beverages[NUM_BUENA_OPTIONS][16] = {
    _("FRESH WATER"),
    _("SODA POP"),
    _("LEMONADE")
};

static const u8 sBuenaCategory_Healing[NUM_BUENA_OPTIONS][16] = {
    _("POTION"),
    _("ANTIDOTE"),
    _("PARLYZ HEAL")
};

static const u8 sBuenaCategory_Balls[NUM_BUENA_OPTIONS][16] = {
    _("POKé BALL"),
    _("GREAT BALL"),
    _("ULTRA BALL")
};

static const u8 sBuenaCategory_Pokemon1[NUM_BUENA_OPTIONS][16] = {
    _("PIKACHU"),
    _("RATTATA"),
    _("GEODUDE")
};

static const u8 sBuenaCategory_Pokemon2[NUM_BUENA_OPTIONS][16] = {
    _("HOOTHOOT"),
    _("SPINARAK"),
    _("DROWZEE")
};

static const u8 sBuenaCategory_Towns[NUM_BUENA_OPTIONS][20] = {
    _("NEW BARK TOWN"),
    _("CHERRYGROVE CITY"),
    _("AZALEA TOWN")
};

static const u8 sBuenaCategory_Types[NUM_BUENA_OPTIONS][16] = {
    _("FLYING"),
    _("BUG"),
    _("GRASS")
};

static const u8 sBuenaCategory_Moves[NUM_BUENA_OPTIONS][16] = {
    _("TACKLE"),
    _("GROWL"),
    _("MUD-SLAP")
};

static const u8 sBuenaCategory_XItems[NUM_BUENA_OPTIONS][16] = {
    _("X ATTACK"),
    _("X DEFEND"),
    _("X SPEED")
};

static const u8 sBuenaCategory_Stations[NUM_BUENA_OPTIONS][16] = {
    _("POKéMON TALK"),
    _("POKéMON MUSIC"),
    _("LUCKY CHANNEL")
};

static u32 GetDayOfYear(void)
{
    return (u32)(GetDay() + ((u32)GetMonth() * 31));
}

u8 Johto_GetBuenaPasswordCategory(void)
{
    return (u8)(GetDayOfYear() % NUM_BUENA_CATEGORIES);
}

u8 Johto_GetBuenaCorrectOption(void)
{
    return (u8)((GetDayOfYear() / NUM_BUENA_CATEGORIES) % NUM_BUENA_OPTIONS);
}

const u8 *Johto_GetBuenaOptionString(u8 category, u8 option)
{
    if (option >= NUM_BUENA_OPTIONS)
        option = 0;

    switch (category % NUM_BUENA_CATEGORIES)
    {
    case 0:  return sBuenaCategory_Starters[option];
    case 1:  return sBuenaCategory_Beverages[option];
    case 2:  return sBuenaCategory_Healing[option];
    case 3:  return sBuenaCategory_Balls[option];
    case 4:  return sBuenaCategory_Pokemon1[option];
    case 5:  return sBuenaCategory_Pokemon2[option];
    case 6:  return sBuenaCategory_Towns[option];
    case 7:  return sBuenaCategory_Types[option];
    case 8:  return sBuenaCategory_Moves[option];
    case 9:  return sBuenaCategory_XItems[option];
    case 10: return sBuenaCategory_Stations[option];
    default: return sBuenaCategory_Starters[option];
    }
}

// Script specials
void JohtoOpenRadioMenu(void)
{
    extern const u8 Johto_EventScript_RadioMenu[];
    ScriptContext_SetupScript(Johto_EventScript_RadioMenu);
}

void JohtoCheckRadioCard(void)
{
    gSpecialVar_Result = Johto_HasRadioCard();
}

void JohtoCheckExpnCard(void)
{
    gSpecialVar_Result = Johto_HasExpnCard();
}

void JohtoCheckInRuinsOfAlph(void)
{
    gSpecialVar_Result = (gMapHeader.regionMapSectionId == MAPSEC_JOHTO_RUINS_OF_ALPH);
}

void JohtoCheckCanPlayPokeFlute(void)
{
    gSpecialVar_Result = (GetCurrentRegion() == REGION_KANTO && Johto_HasExpnCard());
}

void JohtoCheckRocketCrisis(void)
{
    gSpecialVar_Result = (GetCurrentRegion() == REGION_JOHTO && FlagGet(FLAG_JOHTO_ENGINE_ROCKETS_IN_RADIO_TOWER));
}

static const u8 sSwarmLocationNames[JOHTO_SWARM_COUNT][20] = {
    [JOHTO_SWARM_NONE]      = _("JOHTO"),
    [JOHTO_SWARM_DUNSPARCE] = _("DARK CAVE"),
    [JOHTO_SWARM_YANMA]     = _("ROUTE 35"),
    [JOHTO_SWARM_SNUBBULL]  = _("ROUTE 38"),
    [JOHTO_SWARM_MARILL]    = _("ROUTE 34"),
    [JOHTO_SWARM_REMORAID]  = _("ROUTE 44"),
    [JOHTO_SWARM_QWILFISH]  = _("ROUTE 32"),
};

static const u16 sSwarmSpeciesNames[JOHTO_SWARM_COUNT] = {
    [JOHTO_SWARM_NONE]      = SPECIES_NONE,
    [JOHTO_SWARM_DUNSPARCE] = SPECIES_DUNSPARCE,
    [JOHTO_SWARM_YANMA]     = SPECIES_YANMA,
    [JOHTO_SWARM_SNUBBULL]  = SPECIES_SNUBBULL,
    [JOHTO_SWARM_MARILL]    = SPECIES_MARILL,
    [JOHTO_SWARM_REMORAID]  = SPECIES_REMORAID,
    [JOHTO_SWARM_QWILFISH]  = SPECIES_QWILFISH,
};

void JohtoTuneRadioOakTalk(void)
{
    u8 swarm = Johto_GetActiveSwarm();
    u16 species;

    if (swarm == JOHTO_SWARM_NONE || swarm >= JOHTO_SWARM_COUNT)
        swarm = JOHTO_SWARM_DUNSPARCE;

    species = sSwarmSpeciesNames[swarm];

    StringCopy(gStringVar1, GetSpeciesName(species));
    StringCopy(gStringVar2, sSwarmLocationNames[swarm]);

    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_OAK_TALK);
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    FlagClear(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);

    PlayBGM(MUS_RG_OAK);
}

void JohtoTuneRadioPokemonMusic(void)
{
    // Authentic Crystal day scheduling:
    // Sunday, Tuesday, Thursday, Saturday: Pokémon March (+encounter rate)
    // Monday, Wednesday, Friday: Pokémon Lullaby (-encounter rate)
    u8 weekday = (u8)GetDayOfWeek();

    if (weekday == 0 || weekday == 2 || weekday == 4 || weekday == 6)
    {
        // Pokémon March
        VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_MARCH);
        gSpecialVar_Result = 0; // March
        PlayBGM(MUS_C_ROUTE29);
    }
    else
    {
        // Pokémon Lullaby
        VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_LULLABY);
        gSpecialVar_Result = 1; // Lullaby
        PlayBGM(MUS_RG_POKE_FLUTE);
    }

    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_POKEMON_MUSIC);
    FlagClear(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);
}

void JohtoTuneRadioBuenasPassword(void)
{
    u8 category = Johto_GetBuenaPasswordCategory();
    u8 option = Johto_GetBuenaCorrectOption();
    const u8 *pw = Johto_GetBuenaOptionString(category, option);

    StringCopy(gStringVar1, pw);
    VarSet(VAR_JOHTO_BUENA_PASSWORD, (category << 8) | option);
    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_BUENA_PASSWORD);
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    FlagClear(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);
    FlagSet(FLAG_JOHTO_LISTENED_TO_BUENAS_PASSWORD);

    PlayBGM(MUS_C_GOLDENROD);
}

void JohtoTuneRadioUnownSignal(void)
{
    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_UNOWN_SIGNAL);
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    FlagClear(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);

    PlayBGM(MUS_C_RUINS_OF_ALPH);
}

void JohtoTuneRadioPokeFlute(void)
{
    VarSet(VAR_JOHTO_RADIO_STATION, RADIO_STATION_POKE_FLUTE);
    VarSet(VAR_JOHTO_RADIO_EFFECT, RADIO_EFFECT_NONE);
    FlagSet(FLAG_JOHTO_POKE_FLUTE_RADIO_PLAYING);

    PlayBGM(MUS_RG_POKE_FLUTE);
}

void JohtoStopRadio(void)
{
    Johto_TurnOffRadio();
}

void JohtoGetBuenaPasswordChoices(void)
{
    u8 category = Johto_GetBuenaPasswordCategory();

    StringCopy(gStringVar1, Johto_GetBuenaOptionString(category, 0));
    StringCopy(gStringVar2, Johto_GetBuenaOptionString(category, 1));
    StringCopy(gStringVar3, Johto_GetBuenaOptionString(category, 2));
}

void JohtoCheckBuenaAnswer(void)
{
    u8 chosen = (u8)gSpecialVar_Result;
    u8 correct = Johto_GetBuenaCorrectOption();

    if (chosen == correct)
    {
        u16 balance = VarGet(VAR_JOHTO_BLUE_CARD_BALANCE);
        if (balance < 30)
            VarSet(VAR_JOHTO_BLUE_CARD_BALANCE, balance + 1);
        FlagSet(FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY);
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}
