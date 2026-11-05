#ifndef GUARD_MOOD_H
#define GUARD_MOOD_H

#include "global.h"
#include "constants/confluence.h"

// POKE-CONFLUENCE: Universal Mood System supporting all 386 Generation 1-3 Pokémon.
// Expands Yellow's Pikachu mood reactions into an engine-wide system for all species.

enum PokemonMood
{
    MOOD_ECSTATIC,   // Max/very high friendship (>= 220), complete adoration
    MOOD_HAPPY,      // High friendship (160..219), cheerful, enthusiastic
    MOOD_CONTENT,    // Normal/peaceful friendship (100..159), relaxed
    MOOD_NORMAL,     // Neutral friendship (50..99), attentive
    MOOD_DISTANT,    // Low friendship (< 50), wary, aloof
    MOOD_TIRED,      // HP <= 25%, breathing heavily, exhausted
    MOOD_SICK,       // Poisoned or Burned status
    MOOD_PARALYZED,  // Paralyzed or Frozen status, stiff
    MOOD_SLEEPING,   // Asleep, dozing peacefully
    MOOD_ANGRY,      // Refused evolution stone, defeated, frustrated
    MOOD_SURPRISED,  // Weather anomaly, legendary presence, sudden startle
    MOOD_COUNT
};

// Emotion portraits corresponding to PMD SpriteCollab emotions
enum PortraitEmotion
{
    PORTRAIT_EMOTION_NORMAL,
    PORTRAIT_EMOTION_HAPPY,
    PORTRAIT_EMOTION_PAIN,
    PORTRAIT_EMOTION_ANGRY,
    PORTRAIT_EMOTION_WORRIED,
    PORTRAIT_EMOTION_SAD,
    PORTRAIT_EMOTION_JOYOUS,
    PORTRAIT_EMOTION_INSPIRED,
    PORTRAIT_EMOTION_SURPRISED,
    PORTRAIT_EMOTION_DIZZY,
    PORTRAIT_EMOTION_SIGH,
    PORTRAIT_EMOTION_STUNNED,
    PORTRAIT_EMOTION_COUNT
};

struct PokemonMoodInfo
{
    enum PokemonMood mood;
    enum PortraitEmotion portraitEmotion;
    u32 followerEmotion;
    const u8 *flavorText;
};

// Core API
enum PokemonMood Confluence_GetPokemonMood(struct Pokemon *mon);
enum PortraitEmotion Confluence_GetPortraitEmotionForMood(enum PokemonMood mood);
u32 Confluence_GetFollowerEmotionForMood(enum PokemonMood mood);
const u8 *Confluence_GetPokemonMoodDescription(struct Pokemon *mon, enum PokemonMood mood);
bool32 Confluence_CheckStoneRefusal(struct Pokemon *mon, u16 itemId);
void Confluence_EvaluateLeadPokemonMood(struct PokemonMoodInfo *outInfo);

// Script specials
void Special_TalkToLeadPokemon(void);
void Special_ShowLeadPokemonMood(void);

extern const u8 gText_PokemonRefusedStone[];

#endif // GUARD_MOOD_H
