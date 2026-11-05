#ifndef GUARD_CONFLUENCE_H
#define GUARD_CONFLUENCE_H

#include "global.h"
#include "constants/confluence.h"

// Gym badges earned across Kanto, Johto and Hoenn (0-24).
u32 Confluence_CountBadges(void);
// Legendary Birds, Beasts and Titans registered as caught (0-9).
u32 Confluence_CountResonanceCalmed(void);
// Level cap for a number of badges; the Apex Summit champion lifts it completely.
u32 Confluence_GetLevelCapForBadges(u32 badges);

#include "constants/field_move.h"
#include "constants/weather.h"

// Weather that replaces clear weather while a region's Resonance is uncalmed (see the Convergence Crisis).
enum OverworldWeather Confluence_GetAnomalyWeather(enum OverworldWeather weather);
// The Field Kit lets the first non-egg party Pokemon use the HM field moves; PARTY_SIZE when it does not apply.
u32 Confluence_GetFieldKitMon(enum FieldMove fieldMove);

// True when the Field Kit is in the bag and this party slot is the Kit mon (first non-egg Pokemon).
bool32 Confluence_IsFieldKitSlot(u32 slot);
// The n-th field move the Field Kit offers in the party menu, in menu order; FIELD_MOVES_COUNT past the end.
enum FieldMove Confluence_GetFieldKitMoveByIndex(u32 index);

struct Trainer;
// Levels to add to a gym leader's party so that, whatever order the circuit is played in, the leader matches the player's level cap.
u32 Confluence_GetTrainerLevelBoost(const struct Trainer *trainer);

// Script specials
void ConfluenceCheckMeridianAccess(void);
void ConfluenceCheckApexEligible(void);
void ConfluenceBufferProgress(void);

// POKE-CONFLUENCE: Authentic Johto Shuckle Berry Juice fermentation
void Johto_ConvertShuckleBerryJuice(void);

#endif // GUARD_CONFLUENCE_H
