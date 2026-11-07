#ifndef GUARD_SURFING_PIKACHU_H
#define GUARD_SURFING_PIKACHU_H

#include "main.h"

// POKE-CONFLUENCE: Surfing Pikachu Beach Minigame (pokeyellow)
bool32 HasSurfingPikachuInParty(void);
void CheckSurfingPikachuInParty(void);
void StartSurfingPikachuMinigame(MainCallback exitCallback);
void StartSurfingPikachuMinigameSpecial(void);
void GetSurfingPikachuScores(void);

#endif // GUARD_SURFING_PIKACHU_H
