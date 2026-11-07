#ifndef GUARD_JOHTO_BATTLE_TOWER_H
#define GUARD_JOHTO_BATTLE_TOWER_H

#include "global.h"

// POKE-CONFLUENCE: Authentic Johto Battle Tower 7-trainer ladder subsystem (from pokecrystal)

#define JOHTO_BATTLE_TOWER_STREAK_LENGTH 7

struct JohtoTowerTrainer
{
    u8 facilityClass;
    u16 gfxId;
    const u8 *name;
    const u8 *intro;
};

// Specials for scripts and test suite
void JohtoCheckBattleTowerEligibility(void);
void JohtoBattleTowerInitChallenge(void);
void JohtoBattleTowerPrepareOpponent(void);
void JohtoBattleTowerStartBattle(void);
void JohtoBattleTowerGetOutcome(void);
void JohtoBattleTowerAdvanceStreak(void);
void JohtoBattleTowerGivePrizes(void);

// C helpers
u8 JohtoBattleTower_GetRoomLevel(void);
u8 JohtoBattleTower_GetStreak(void);
u16 JohtoBattleTower_GetWins(void);

#endif // GUARD_JOHTO_BATTLE_TOWER_H
