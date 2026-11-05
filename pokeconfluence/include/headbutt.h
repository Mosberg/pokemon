#ifndef GUARD_HEADBUTT_H
#define GUARD_HEADBUTT_H

#include "global.h"
#include "rtc.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Headbutt tree encounters and mechanics
enum TreeMonSet
{
    TREEMON_SET_NONE,
    TREEMON_SET_CANYON,
    TREEMON_SET_TOWN,
    TREEMON_SET_ROUTE,
    TREEMON_SET_KANTO,
    TREEMON_SET_LAKE,
    TREEMON_SET_FOREST,
    TREEMON_SET_ROCK,
    TREEMON_SET_COUNT
};

struct TreeMon
{
    u16 species;
    u8 level;
    u8 chance;
};

enum TreeMonSet GetCurrentMapTreeMonSet(void);
bool8 CheckSleepingTreeMon(u16 species, enum TimeOfDay timeOfDay);
void JohtoHeadbuttWildEncounter(void);
void JohtoCheckHeadbuttUser(void);

#endif // GUARD_HEADBUTT_H
