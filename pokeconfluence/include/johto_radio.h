#ifndef GUARD_JOHTO_RADIO_H
#define GUARD_JOHTO_RADIO_H

#include "global.h"

// POKE-CONFLUENCE: Authentic Johto Pokégear Radio subsystem (from pokecrystal radio.asm)

enum JohtoRadioStation
{
    RADIO_STATION_OFF = 0,
    RADIO_STATION_OAK_TALK,        // 4.5 MHz - Prof. Oak's Pokémon Talk & Mary
    RADIO_STATION_POKEMON_MUSIC,   // 7.5 MHz - Pokémon Music Channel (March & Lullaby)
    RADIO_STATION_BUENA_PASSWORD,  // 10.5 MHz - Buena's Password Show
    RADIO_STATION_UNOWN_SIGNAL,    // 13.5 MHz - Ruins of Alph Mysterious Transmission
    RADIO_STATION_POKE_FLUTE,      // 20.0 MHz - Poké Flute Broadcast (Kanto with EXPN Card)
    RADIO_STATION_ROCKET_CRISIS,   // Team Rocket Takeover broadcast
    RADIO_STATION_COUNT
};

enum JohtoRadioMusicEffect
{
    RADIO_EFFECT_NONE = 0,
    RADIO_EFFECT_MARCH,   // +50% wild encounter rate
    RADIO_EFFECT_LULLABY, // -50% wild encounter rate
};

bool32 Johto_HasRadioCard(void);
bool32 Johto_HasExpnCard(void);
u8 Johto_GetActiveRadioStation(void);
u8 Johto_GetActiveRadioMusicEffect(void);
void Johto_ApplyRadioMusicRateMod(u32 *encounterRate);
bool8 Johto_IsPokeFluteRadioPlaying(void);
void Johto_TurnOffRadio(void);

// Buena's Password helpers
u8 Johto_GetBuenaPasswordCategory(void);
u8 Johto_GetBuenaCorrectOption(void);
const u8 *Johto_GetBuenaOptionString(u8 category, u8 option);

// Script specials
void JohtoOpenRadioMenu(void);
void JohtoCheckRadioCard(void);
void JohtoCheckExpnCard(void);
void JohtoTuneRadioOakTalk(void);
void JohtoTuneRadioPokemonMusic(void);
void JohtoTuneRadioBuenasPassword(void);
void JohtoTuneRadioUnownSignal(void);
void JohtoTuneRadioPokeFlute(void);
void JohtoStopRadio(void);
void JohtoCheckInRuinsOfAlph(void);
void JohtoCheckCanPlayPokeFlute(void);
void JohtoCheckRocketCrisis(void);
void JohtoGetBuenaPasswordChoices(void);
void JohtoCheckBuenaAnswer(void);

extern bool8 sPokenavWantsToOpenRadio;

#endif // GUARD_JOHTO_RADIO_H
