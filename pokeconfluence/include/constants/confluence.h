#ifndef GUARD_CONSTANTS_CONFLUENCE_H
#define GUARD_CONSTANTS_CONFLUENCE_H

#include "constants/flags.h"

// POKE-CONFLUENCE: constants of the Confluence layer (the Meridian Transit, the 24-badge circuit, Resonance Encounters, the Apex Summit).

#define CONFLUENCE_BADGES_PER_REGION    8
#define CONFLUENCE_REGION_COUNT         3
#define CONFLUENCE_TOTAL_BADGES         (CONFLUENCE_BADGES_PER_REGION * CONFLUENCE_REGION_COUNT)

// Badges needed before the Meridian Transit line lets the player leave the starting region.
#define CONFLUENCE_MERIDIAN_MIN_BADGES  2

// Resonance Encounters: the Legendary Birds, Beasts and Titans. A Resonance is calmed once the species is registered as caught.
#define CONFLUENCE_RESONANCE_COUNT      9

// Meridian Transit destinations (VAR_RESULT of the destination menu).
#define CONFLUENCE_DEST_KANTO           0
#define CONFLUENCE_DEST_JOHTO           1
#define CONFLUENCE_DEST_HOENN           2

// Flags of the Confluence layer. They reuse flags that no script, map or trainer references.
#define FLAG_CONFLUENCE_APEX_UNLOCKED   FLAG_UNUSED_0x020 // All 24 badges shown to the Summit warden
#define FLAG_CONFLUENCE_APEX_CHAMPION   FLAG_UNUSED_0x021 // The Apex Summit was cleared
#define FLAG_CONFLUENCE_MERIDIAN_USED   FLAG_UNUSED_0x022 // The player has ridden the Meridian line at least once

#define FLAG_CONFLUENCE_CRISIS_RESOLVED FLAG_UNUSED_0x023 // The syndicate chairman was beaten: the Resonance anomalies stop
#define FLAG_CONFLUENCE_GOT_FIELD_KIT   FLAG_UNUSED_0x024 // The conductors handed out the Field Kit

// The Convergence Crisis: the syndicate enforcers wait at the Meridian terminals once enough badges are held.
#define CONFLUENCE_SYNDICATE_MIN_BADGES 6
#define CONFLUENCE_CHAIRMAN_MIN_BADGES  12

#endif // GUARD_CONSTANTS_CONFLUENCE_H
