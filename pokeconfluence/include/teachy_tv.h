#ifndef GUARD_TEACHY_TV_H
#define GUARD_TEACHY_TV_H

#include "main.h"

// POKE-CONFLUENCE: Teachy TV Subsystem
enum TeachyTvScript
{
    TTVSCR_BATTLE,
    TTVSCR_STATUS,
    TTVSCR_MATCHUPS,
    TTVSCR_CATCHING,
    TTVSCR_TMS,
    TTVSCR_REGISTER,
    TTVSCR_COUNT
};

void InitTeachyTvController(u8 mode, MainCallback cb);
void CB2_ReturnToTeachyTV(void);
void SetTeachyTvControllerModeToResume(void);

#endif // GUARD_TEACHY_TV_H
