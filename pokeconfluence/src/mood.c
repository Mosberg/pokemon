// POKE-CONFLUENCE: Universal Mood System supporting all 386 Generation 1-3 Pokémon.
// Adapts Pokémon Yellow's Pikachu mood & loyalty reactions into a multi-region feature.

#include "global.h"
#include "mood.h"
#include "pokemon.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "data.h"
#include "follower_helper.h"
#include "party_menu.h"
#include "field_weather.h"
#include "constants/abilities.h"
#include "constants/confluence.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/weather.h"

// Refusal Text
const u8 gText_PokemonRefusedStone[] = _("{STR_VAR_1} refused the stone!\pIt shook its head vigorously.");

// -------------------------------------------------------------------------
// Mood Dialogues: Generic (386 species support)
// -------------------------------------------------------------------------
static const u8 sText_Mood_Ecstatic_Generic[] = _("{STR_VAR_1} is regarding you with\ncomplete adoration and love!\pIt hugged you happily!");
static const u8 sText_Mood_Happy_Generic[]    = _("{STR_VAR_1} is feeling very energetic!\nIt smiled warmly and nodded.");
static const u8 sText_Mood_Content_Generic[]  = _("{STR_VAR_1} is walking peacefully by\nyour side, looking content.");
static const u8 sText_Mood_Normal_Generic[]   = _("{STR_VAR_1} is standing alert, quietly\nobserving the surroundings.");
static const u8 sText_Mood_Distant_Generic[]  = _("{STR_VAR_1} kept its distance...\nIt hasn't fully warmed up yet.");
static const u8 sText_Mood_Tired_Generic[]    = _("{STR_VAR_1} is panting heavily and\nlooks visibly exhausted...");
static const u8 sText_Mood_Sick_Generic[]     = _("{STR_VAR_1} is shivering in pain\nfrom its ailment...");
static const u8 sText_Mood_Paralyzed_Generic[]= _("{STR_VAR_1} is stiff and struggling\nto move smoothly...");
static const u8 sText_Mood_Sleeping_Generic[] = _("{STR_VAR_1} is sound asleep, breathing\nslowly and peacefully: Zzz...");
static const u8 sText_Mood_Angry_Generic[]    = _("{STR_VAR_1} turned away stubbornly and\npouted with folded arms!");
static const u8 sText_Mood_Surprised_Generic[]= _("{STR_VAR_1} froze in surprise at the\nstrange resonance in the air!");

// -------------------------------------------------------------------------
// Mood Dialogues: Pikachu & Pichu Family (Yellow Authenticity)
// -------------------------------------------------------------------------
static const u8 sText_Mood_Ecstatic_Pikachu[] = _("{STR_VAR_1} rubbed its glowing red cheeks\nagainst you affectionately!\pWarm, pleasant sparks tickled you!");
static const u8 sText_Mood_Happy_Pikachu[]    = _("{STR_VAR_1} let out a cheerful 'Pika!' and\nwagged its lightning tail excitedly!");
static const u8 sText_Mood_Content_Pikachu[]  = _("{STR_VAR_1} watched you intently and gave\na gentle, trusting nod.");
static const u8 sText_Mood_Normal_Pikachu[]   = _("{STR_VAR_1} perked its long ears up and\nsniffed the breeze curiously.");
static const u8 sText_Mood_Distant_Pikachu[]  = _("{STR_VAR_1} crossed its tiny paws, looking\naway with wary ears.");
static const u8 sText_Mood_Tired_Pikachu[]    = _("{STR_VAR_1} is drooping its ears and\npanting heavily for breath...");
static const u8 sText_Mood_Sick_Pikachu[]     = _("{STR_VAR_1} is winced in discomfort,\nfaint sparks fizzling out weakly...");
static const u8 sText_Mood_Paralyzed_Pikachu[]= _("{STR_VAR_1} is shivering with static and\ncan barely twitch its tail...");
static const u8 sText_Mood_Sleeping_Pikachu[] = _("{STR_VAR_1} is curled into a soft yellow ball:\n'pi... ka... zzz'");
static const u8 sText_Mood_Angry_Pikachu[]    = _("{STR_VAR_1} sparked angrily from both cheeks\nand shook its head stubbornly!");
static const u8 sText_Mood_Surprised_Pikachu[]= _("{STR_VAR_1} sprang up onto its hind legs\nwith wide, startled eyes!");

// -------------------------------------------------------------------------
// Mood Dialogues: Fire Starters (Charmander, Cyndaquil, Torchic families)
// -------------------------------------------------------------------------
static const u8 sText_Mood_Ecstatic_FireStarter[] = _("{STR_VAR_1}'s flame burned with bright warmth!\nIt nestled against you happily.");
static const u8 sText_Mood_Happy_FireStarter[]    = _("{STR_VAR_1} hopped in excitement, its flame\nflickering with joyful sparks!");
static const u8 sText_Mood_Content_FireStarter[]  = _("{STR_VAR_1} is basking comfortably, its flame\nradiating a calm, steady heat.");
static const u8 sText_Mood_Angry_FireStarter[]    = _("{STR_VAR_1} puffed a small plume of irritated\nsmoke and stomped stubbornly!");

// -------------------------------------------------------------------------
// Mood Dialogues: Water Starters (Squirtle, Totodile, Mudkip families)
// -------------------------------------------------------------------------
static const u8 sText_Mood_Ecstatic_WaterStarter[] = _("{STR_VAR_1} joyfully blew shimmering bubbles\nthat sparkled all around you!");
static const u8 sText_Mood_Happy_WaterStarter[]    = _("{STR_VAR_1} splashed its feet playfully and\ngave a big, cheerful grin!");
static const u8 sText_Mood_Content_WaterStarter[]  = _("{STR_VAR_1} patted its tummy contentedly\nand gazed happily at you.");
static const u8 sText_Mood_Angry_WaterStarter[]    = _("{STR_VAR_1} blew a grumpy splash of water\nand shook its head!");

// -------------------------------------------------------------------------
// Mood Dialogues: Grass Starters (Bulbasaur, Chikorita, Treecko families)
// -------------------------------------------------------------------------
static const u8 sText_Mood_Ecstatic_GrassStarter[] = _("{STR_VAR_1} released a soothing, sweet aroma\nthat calmed the surroundings gently.");
static const u8 sText_Mood_Happy_GrassStarter[]    = _("{STR_VAR_1} rustled its fresh green leaves\nwith exuberant energy!");
static const u8 sText_Mood_Content_GrassStarter[]  = _("{STR_VAR_1} absorbed the gentle sunlight\nand relaxed peacefully.");
static const u8 sText_Mood_Angry_GrassStarter[]    = _("{STR_VAR_1} rustled its foliage sharply and\nrefused to look your way!");

static bool32 IsPikachuFamily(enum Species species)
{
    return (species == SPECIES_PIKACHU || species == SPECIES_PICHU || species == SPECIES_RAICHU);
}

static bool32 IsFireStarterFamily(enum Species species)
{
    return (species == SPECIES_CHARMANDER || species == SPECIES_CHARMELEON || species == SPECIES_CHARIZARD ||
            species == SPECIES_CYNDAQUIL  || species == SPECIES_QUILAVA    || species == SPECIES_TYPHLOSION ||
            species == SPECIES_TORCHIC    || species == SPECIES_COMBUSKEN  || species == SPECIES_BLAZIKEN);
}

static bool32 IsWaterStarterFamily(enum Species species)
{
    return (species == SPECIES_SQUIRTLE || species == SPECIES_WARTORTLE || species == SPECIES_BLASTOISE ||
            species == SPECIES_TOTODILE || species == SPECIES_CROCONAW  || species == SPECIES_FERALIGATR ||
            species == SPECIES_MUDKIP   || species == SPECIES_MARSHTOMP || species == SPECIES_SWAMPERT);
}

static bool32 IsGrassStarterFamily(enum Species species)
{
    return (species == SPECIES_BULBASAUR || species == SPECIES_IVYSAUR  || species == SPECIES_VENUSAUR ||
            species == SPECIES_CHIKORITA || species == SPECIES_BAYLEEF  || species == SPECIES_MEGANIUM ||
            species == SPECIES_TREECKO   || species == SPECIES_GROVYLE  || species == SPECIES_SCEPTILE);
}

// -------------------------------------------------------------------------
// Core Mood Evaluation
// -------------------------------------------------------------------------
enum PokemonMood Confluence_GetPokemonMood(struct Pokemon *mon)
{
    u32 curHp;
    u32 maxHp;
    u32 status;
    u8 friendship;

    if (mon == NULL || GetMonData(mon, MON_DATA_IS_EGG))
        return MOOD_NORMAL;

    curHp = GetMonData(mon, MON_DATA_HP);
    maxHp = GetMonData(mon, MON_DATA_MAX_HP);
    status = GetMonData(mon, MON_DATA_STATUS);
    friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);

    // 1. Defeated / Fainted
    if (curHp == 0)
        return MOOD_ANGRY;

    // 2. Refusal / Spite
    if (FlagGet(FLAG_POKEMON_REFUSED_STONE))
        return MOOD_ANGRY;

    // 3. Status Conditions
    if (status & STATUS1_SLEEP)
        return MOOD_SLEEPING;

    if ((status & (STATUS1_PSN_ANY | STATUS1_BURN)) && GetMonAbility(mon) != ABILITY_POISON_HEAL)
        return MOOD_SICK;

    if (status & (STATUS1_PARALYSIS | STATUS1_FREEZE))
        return MOOD_PARALYZED;

    // 4. Low Health Peril (<= 25% max HP)
    if (maxHp > 0 && (curHp * 4 <= maxHp))
        return MOOD_TIRED;

    // 5. Environmental Resonance Weather Anomaly
    if (!FlagGet(FLAG_CONFLUENCE_CRISIS_RESOLVED))
    {
        u8 weather = GetCurrentWeather();
        if (weather == WEATHER_VOLCANIC_ASH || weather == WEATHER_FOG_DIAGONAL || weather == WEATHER_SANDSTORM)
            return MOOD_SURPRISED;
    }

    // 6. Friendship Tiers (Scaled 0..255)
    if (friendship >= 220)
        return MOOD_ECSTATIC;
    if (friendship >= 160)
        return MOOD_HAPPY;
    if (friendship >= 100)
        return MOOD_CONTENT;
    if (friendship >= 50)
        return MOOD_NORMAL;

    return MOOD_DISTANT;
}

enum PortraitEmotion Confluence_GetPortraitEmotionForMood(enum PokemonMood mood)
{
    switch (mood)
    {
    case MOOD_ECSTATIC:
        return PORTRAIT_EMOTION_JOYOUS;
    case MOOD_HAPPY:
        return PORTRAIT_EMOTION_HAPPY;
    case MOOD_CONTENT:
        return PORTRAIT_EMOTION_INSPIRED;
    case MOOD_NORMAL:
        return PORTRAIT_EMOTION_NORMAL;
    case MOOD_DISTANT:
        return PORTRAIT_EMOTION_SAD;
    case MOOD_TIRED:
        return PORTRAIT_EMOTION_WORRIED;
    case MOOD_SICK:
        return PORTRAIT_EMOTION_PAIN;
    case MOOD_PARALYZED:
        return PORTRAIT_EMOTION_STUNNED;
    case MOOD_SLEEPING:
        return PORTRAIT_EMOTION_SIGH;
    case MOOD_ANGRY:
        return PORTRAIT_EMOTION_ANGRY;
    case MOOD_SURPRISED:
        return PORTRAIT_EMOTION_SURPRISED;
    default:
        return PORTRAIT_EMOTION_NORMAL;
    }
}

u32 Confluence_GetFollowerEmotionForMood(enum PokemonMood mood)
{
    switch (mood)
    {
    case MOOD_ECSTATIC:
        return FOLLOWER_EMOTION_LOVE;
    case MOOD_HAPPY:
        return FOLLOWER_EMOTION_HAPPY;
    case MOOD_CONTENT:
        return FOLLOWER_EMOTION_MUSIC;
    case MOOD_NORMAL:
        return FOLLOWER_EMOTION_NEUTRAL;
    case MOOD_DISTANT:
        return FOLLOWER_EMOTION_PENSIVE;
    case MOOD_TIRED:
        return FOLLOWER_EMOTION_SAD;
    case MOOD_SICK:
        return FOLLOWER_EMOTION_POISONED;
    case MOOD_PARALYZED:
        return FOLLOWER_EMOTION_UPSET;
    case MOOD_SLEEPING:
        return FOLLOWER_EMOTION_NEUTRAL;
    case MOOD_ANGRY:
        return FOLLOWER_EMOTION_ANGRY;
    case MOOD_SURPRISED:
        return FOLLOWER_EMOTION_SURPRISE;
    default:
        return FOLLOWER_EMOTION_NEUTRAL;
    }
}

const u8 *Confluence_GetPokemonMoodDescription(struct Pokemon *mon, enum PokemonMood mood)
{
    enum Species species;

    if (mon == NULL)
        return sText_Mood_Normal_Generic;

    species = GetMonData(mon, MON_DATA_SPECIES);

    if (IsPikachuFamily(species))
    {
        switch (mood)
        {
        case MOOD_ECSTATIC:   return sText_Mood_Ecstatic_Pikachu;
        case MOOD_HAPPY:      return sText_Mood_Happy_Pikachu;
        case MOOD_CONTENT:    return sText_Mood_Content_Pikachu;
        case MOOD_NORMAL:     return sText_Mood_Normal_Pikachu;
        case MOOD_DISTANT:    return sText_Mood_Distant_Pikachu;
        case MOOD_TIRED:      return sText_Mood_Tired_Pikachu;
        case MOOD_SICK:       return sText_Mood_Sick_Pikachu;
        case MOOD_PARALYZED:  return sText_Mood_Paralyzed_Pikachu;
        case MOOD_SLEEPING:   return sText_Mood_Sleeping_Pikachu;
        case MOOD_ANGRY:      return sText_Mood_Angry_Pikachu;
        case MOOD_SURPRISED:  return sText_Mood_Surprised_Pikachu;
        default:              return sText_Mood_Normal_Pikachu;
        }
    }

    if (IsFireStarterFamily(species))
    {
        switch (mood)
        {
        case MOOD_ECSTATIC: return sText_Mood_Ecstatic_FireStarter;
        case MOOD_HAPPY:    return sText_Mood_Happy_FireStarter;
        case MOOD_CONTENT:  return sText_Mood_Content_FireStarter;
        case MOOD_ANGRY:    return sText_Mood_Angry_FireStarter;
        default:            break;
        }
    }

    if (IsWaterStarterFamily(species))
    {
        switch (mood)
        {
        case MOOD_ECSTATIC: return sText_Mood_Ecstatic_WaterStarter;
        case MOOD_HAPPY:    return sText_Mood_Happy_WaterStarter;
        case MOOD_CONTENT:  return sText_Mood_Content_WaterStarter;
        case MOOD_ANGRY:    return sText_Mood_Angry_WaterStarter;
        default:            break;
        }
    }

    if (IsGrassStarterFamily(species))
    {
        switch (mood)
        {
        case MOOD_ECSTATIC: return sText_Mood_Ecstatic_GrassStarter;
        case MOOD_HAPPY:    return sText_Mood_Happy_GrassStarter;
        case MOOD_CONTENT:  return sText_Mood_Content_GrassStarter;
        case MOOD_ANGRY:    return sText_Mood_Angry_GrassStarter;
        default:            break;
        }
    }

    switch (mood)
    {
    case MOOD_ECSTATIC:   return sText_Mood_Ecstatic_Generic;
    case MOOD_HAPPY:      return sText_Mood_Happy_Generic;
    case MOOD_CONTENT:    return sText_Mood_Content_Generic;
    case MOOD_NORMAL:     return sText_Mood_Normal_Generic;
    case MOOD_DISTANT:    return sText_Mood_Distant_Generic;
    case MOOD_TIRED:      return sText_Mood_Tired_Generic;
    case MOOD_SICK:       return sText_Mood_Sick_Generic;
    case MOOD_PARALYZED:  return sText_Mood_Paralyzed_Generic;
    case MOOD_SLEEPING:   return sText_Mood_Sleeping_Generic;
    case MOOD_ANGRY:      return sText_Mood_Angry_Generic;
    case MOOD_SURPRISED:  return sText_Mood_Surprised_Generic;
    default:              return sText_Mood_Normal_Generic;
    }
}

// -------------------------------------------------------------------------
// Evolutionary Stone Refusal
// -------------------------------------------------------------------------
bool32 Confluence_CheckStoneRefusal(struct Pokemon *mon, u16 itemId)
{
    enum Species species;
    u16 heldItem;
    u8 friendship;

    if (mon == NULL || GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    species = GetMonData(mon, MON_DATA_SPECIES);
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);

    // 1. Pikachu refusing Thunder Stone (Yellow authenticity)
    if (species == SPECIES_PIKACHU && itemId == ITEM_THUNDER_STONE)
    {
        if (FlagGet(FLAG_STARTER_PIKACHU) || friendship >= 100)
        {
            FlagSet(FLAG_POKEMON_REFUSED_STONE);
            return TRUE;
        }
    }

    // 2. Holding Everstone actively refuses item evolution
    if (heldItem == ITEM_EVERSTONE)
    {
        FlagSet(FLAG_POKEMON_REFUSED_STONE);
        return TRUE;
    }

    // 3. High-friendship starter loyalty refusal
    if (friendship >= 220 && FlagGet(FLAG_STARTER_LOYALTY_REFUSAL))
    {
        if (species == SPECIES_BULBASAUR  || species == SPECIES_IVYSAUR  ||
            species == SPECIES_CHARMANDER || species == SPECIES_CHARMELEON ||
            species == SPECIES_SQUIRTLE   || species == SPECIES_WARTORTLE ||
            species == SPECIES_CHIKORITA  || species == SPECIES_BAYLEEF  ||
            species == SPECIES_CYNDAQUIL  || species == SPECIES_QUILAVA  ||
            species == SPECIES_TOTODILE   || species == SPECIES_CROCONAW ||
            species == SPECIES_TREECKO    || species == SPECIES_GROVYLE  ||
            species == SPECIES_TORCHIC    || species == SPECIES_COMBUSKEN ||
            species == SPECIES_MUDKIP     || species == SPECIES_MARSHTOMP ||
            species == SPECIES_EEVEE)
        {
            FlagSet(FLAG_POKEMON_REFUSED_STONE);
            return TRUE;
        }
    }

    return FALSE;
}

void Confluence_EvaluateLeadPokemonMood(struct PokemonMoodInfo *outInfo)
{
    struct Pokemon *mon = GetFirstLiveMon();
    enum PokemonMood mood;

    if (outInfo == NULL)
        return;

    mood = Confluence_GetPokemonMood(mon);
    outInfo->mood = mood;
    outInfo->portraitEmotion = Confluence_GetPortraitEmotionForMood(mood);
    outInfo->followerEmotion = Confluence_GetFollowerEmotionForMood(mood);
    outInfo->flavorText = Confluence_GetPokemonMoodDescription(mon, mood);
}

void Special_ShowLeadPokemonMood(void)
{
    struct Pokemon *mon = GetFirstLiveMon();
    struct PokemonMoodInfo info;

    if (mon == NULL)
        return;

    Confluence_EvaluateLeadPokemonMood(&info);
    GetMonNickname(mon, gStringVar1);
    PlayCry_Normal(GetMonData(mon, MON_DATA_SPECIES), 0);
    gSpecialVar_Result = info.mood;
}
