#ifndef GUARD_JOHTO_PHONE_H
#define GUARD_JOHTO_PHONE_H

#include "global.h"

// POKE-CONFLUENCE: Johto Pokégear phone subsystem supporting all 37 Crystal phone contacts,
// overworld random step triggers, rematch arming, item gift notifications, and authentic dialogue.

bool32 TryStartJohtoPhoneCall(void);
bool32 Johto_HasMapCard(void);
bool32 Johto_HasPhoneCard(void);
bool32 Johto_HasRadioCard(void);
u32 Johto_GetRegisteredPhoneCount(void);
void Johto_ArmRandomRematch(void);
void StartJohtoPhoneCall(const u8 *message);

#endif // GUARD_JOHTO_PHONE_H

