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

#endif // GUARD_CONFLUENCE_H
