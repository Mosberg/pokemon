#include "global.h"
#include "ai_bridge.h"
#include "battle.h"
#include "battle_util.h"
#include "main.h"
#include "constants/moves.h"

EWRAM_DATA struct AiBridgeMailbox gAiBridgeMailbox = {0};

static u8 HpPercent(u32 battler)
{
    u32 max = gBattleMons[battler].maxHP;
    return max == 0 ? 0 : (gBattleMons[battler].hp * 100) / max;
}

// Returns the move slot the opponent should use. Called with the slot the built-in AI chose.
u32 AiBridge_Override(u32 battler, u32 moveIndex)
{
#if AI_BRIDGE_ENABLED
    struct AiBridgeMailbox *mb = &gAiBridgeMailbox;
    u32 target = battler ^ 1; // battlers 0/2 are the player side, 1/3 the opponent: the opposing one is in the same lane
    u32 i, frames, timeout;

    if (!mb->enabled || moveIndex >= MAX_MON_MOVES)
        return moveIndex;

    mb->playerSpecies = gBattleMons[target].species;
    mb->aiSpecies = gBattleMons[battler].species;
    mb->playerHpPct = HpPercent(target);
    mb->aiHpPct = HpPercent(battler);
    mb->playerLevel = gBattleMons[target].level;
    mb->aiLevel = gBattleMons[battler].level;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        mb->playerMoves[i] = gBattleMons[target].moves[i];
        mb->aiMoves[i] = gBattleMons[battler].moves[i];
        mb->aiPp[i] = gBattleMons[battler].pp[i];
    }
    mb->builtInChoice = moveIndex;
    mb->turn = gBattleResults.battleTurnCounter;
    mb->action = 0xFF;
    mb->status = AI_BRIDGE_REQUEST;

    timeout = (mb->timeoutFrames ? mb->timeoutFrames : 8) * 8; // the field counts 8-frame units: up to ~34 s
    for (frames = 0; frames < timeout && mb->status == AI_BRIDGE_REQUEST; frames++)
        VBlankIntrWait();

    if (mb->status == AI_BRIDGE_READY
     && mb->action < MAX_MON_MOVES
     && gBattleMons[battler].moves[mb->action] != MOVE_NONE
     && gBattleMons[battler].pp[mb->action] != 0)
    {
        moveIndex = mb->action;
        mb->answered++;
    }
    else
    {
        mb->timedOut++;
    }
    mb->status = AI_BRIDGE_IDLE;
#endif
    return moveIndex;
}
