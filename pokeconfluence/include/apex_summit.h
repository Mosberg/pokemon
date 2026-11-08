#ifndef GUARD_APEX_SUMMIT_H
#define GUARD_APEX_SUMMIT_H

#include "global.h"

// POKE-CONFLUENCE: Apex Summit 24-Leader Boss Gauntlet Subsystem
#define APEX_ROUNDS_COUNT 5

void ApexSummit_GenerateBracket(void);
void ApexSummit_SetUpCurrentRound(void);
void ApexSummit_StartBattle(void);
void ApexSummit_OnRoundWon(void);
void ApexSummit_AwardPrizes(void);
void ApexSummit_ExitChallenge(void);

#endif // GUARD_APEX_SUMMIT_H
