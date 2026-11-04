#ifndef GUARD_AI_BRIDGE_H
#define GUARD_AI_BRIDGE_H

// POKE-MULTIREGION: external AI hook. A debugger, script or editor extension (see pokeemerald-ai-bridge) can take
// over the opponent's move choice by answering a request written to gAiBridgeMailbox. Disabled (and free of any
// delay) until something writes 1 to .enabled. Layout is fixed: the first 24 bytes are read by the VS Code extension.

#ifndef AI_BRIDGE_ENABLED
#define AI_BRIDGE_ENABLED TRUE
#endif

#define AI_BRIDGE_IDLE    0
#define AI_BRIDGE_REQUEST 1 // the game wrote a request and is waiting
#define AI_BRIDGE_READY   2 // the external side wrote .action
#define AI_BRIDGE_ERROR   3 // timed out or invalid answer, the built-in AI choice was kept

struct AiBridgeMailbox
{
    /*0x00*/ u8 status;
    /*0x01*/ u16 playerSpecies;
    /*0x03*/ u16 aiSpecies;
    /*0x05*/ u8 playerHpPct;
    /*0x06*/ u8 aiHpPct;
    /*0x07*/ u16 playerMoves[4];
    /*0x0F*/ u16 aiMoves[4];
    /*0x17*/ u8 action;          // 0-3: move slot to use. Anything else keeps the built-in choice
    /*0x18*/ u8 enabled;         // written by the external side
    /*0x19*/ u8 timeoutFrames;   // how long to wait for an answer, in units of 8 frames (0 = 8 units = ~1 s)
    /*0x1A*/ u8 builtInChoice;   // the move slot the normal AI picked
    /*0x1B*/ u8 aiPp[4];
    /*0x1F*/ u8 playerLevel;
    /*0x20*/ u8 aiLevel;
    /*0x21*/ u16 turn;
    /*0x23*/ u16 answered;       // requests that were answered in time
    /*0x25*/ u16 timedOut;
} __attribute__((packed));

extern struct AiBridgeMailbox gAiBridgeMailbox;

u32 AiBridge_Override(u32 battler, u32 moveIndex);

#endif // GUARD_AI_BRIDGE_H
