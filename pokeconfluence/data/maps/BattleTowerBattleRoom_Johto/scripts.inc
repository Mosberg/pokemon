BattleTowerBattleRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleTowerBattleRoom_Johto_OnFrame
	.byte 0

BattleTowerBattleRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 0, BattleTowerBattleRoom_Johto_BattleTowerBattleRoomEnterScene_Entry
	.2byte 0

BattleTowerBattleRoom_Johto_BattleTowerBattleRoomEnterScene_Entry::
	lockall
	goto BattleTowerBattleRoom_Johto_BattleTowerBattleRoomEnterScene

BattleTowerBattleRoom_Johto_BattleTowerBattleRoomEnterScene:
	removeobject 1
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleTowerBattleRoom_Johto_Movement_PlayerWalksIn
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 2, BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsToPlayer
	waitmovement 2
	message BattleTowerBattleRoom_Johto_Text_WelcomeToBattleRoom
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsBack
	waitmovement 2

BattleTowerBattleRoom_Johto_NextOpponent:
	special JohtoBattleTowerPrepareOpponent
	addobject 1
	playse SE_DOOR
	applymovement 1, BattleTowerBattleRoom_Johto_Movement_OpponentWalksIn
	waitmovement 1
	message BattleTowerBattleRoom_Johto_Text_OpponentIntro
	waitmessage
	waitbuttonpress
	closemessage
	special JohtoBattleTowerStartBattle
	special JohtoBattleTowerGetOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne BattleTowerBattleRoom_Johto_PlayerLost

	special JohtoBattleTowerAdvanceStreak
	compare VAR_RESULT, 7
	goto_if_eq BattleTowerBattleRoom_Johto_PlayerWonAll

	applymovement 1, BattleTowerBattleRoom_Johto_Movement_OpponentWalksOut
	waitmovement 1
	removeobject 1
	playse SE_DOOR
	applymovement 2, BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsToPlayer
	waitmovement 2
	message BattleTowerBattleRoom_Johto_Text_HealMons
	waitmessage
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	message BattleTowerBattleRoom_Johto_Text_ReadyForNextOpponent
	waitmessage
	yesnobox 20, 8
	compare VAR_RESULT, YES
	goto_if_eq BattleTowerBattleRoom_Johto_ContinueToNextOpponent

	message BattleTowerBattleRoom_Johto_Text_ConfirmCancel
	waitmessage
	yesnobox 20, 8
	compare VAR_RESULT, YES
	goto_if_eq BattleTowerBattleRoom_Johto_CancelChallenge
	goto BattleTowerBattleRoom_Johto_ContinueToNextOpponent

BattleTowerBattleRoom_Johto_ContinueToNextOpponent:
	closemessage
	applymovement 2, BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsBack
	waitmovement 2
	goto BattleTowerBattleRoom_Johto_NextOpponent

BattleTowerBattleRoom_Johto_PlayerLost:
	message BattleTowerBattleRoom_Johto_Text_PlayerLost
	waitmessage
	waitbuttonpress
	closemessage
	special LoadPlayerParty
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_ELEVATOR, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_HALLWAY, 0
	warp MAP_JOHTO_BATTLE_TOWER_1F, 7, 7
	waitstate
	end

BattleTowerBattleRoom_Johto_CancelChallenge:
	message BattleTowerBattleRoom_Johto_Text_ChallengeCanceled
	waitmessage
	waitbuttonpress
	closemessage
	special LoadPlayerParty
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_ELEVATOR, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_HALLWAY, 0
	warp MAP_JOHTO_BATTLE_TOWER_1F, 7, 7
	waitstate
	end

BattleTowerBattleRoom_Johto_PlayerWonAll:
	message BattleTowerBattleRoom_Johto_Text_PlayerWonAllInRoom
	waitmessage
	waitbuttonpress
	closemessage
	special LoadPlayerParty
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_ELEVATOR, 0
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_HALLWAY, 0
	warp MAP_JOHTO_BATTLE_TOWER_1F, 7, 7
	waitstate
	end

BattleTowerBattleRoom_Johto_Movement_PlayerWalksIn:
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsToPlayer:
	walk_right
	walk_up
	face_right
	step_end

BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsBack:
	walk_down
	walk_left
	face_right
	step_end

BattleTowerBattleRoom_Johto_Movement_OpponentWalksIn:
	walk_down
	walk_down
	face_down
	step_end

BattleTowerBattleRoom_Johto_Movement_OpponentWalksOut:
	walk_up
	walk_up
	step_end

BattleTowerBattleRoom_Johto_Text_WelcomeToBattleRoom:
	.string "Welcome to the BATTLE ROOM!\pYour 7-trainer gauntlet is about\nto get underway!\lGive it your very best!$"

BattleTowerBattleRoom_Johto_Text_OpponentIntro:
	.string "{STR_VAR_1}: {STR_VAR_2}$"

BattleTowerBattleRoom_Johto_Text_HealMons:
	.string "Splendid victory!\pYour POKéMON will be healed to\nfull health before the next round.$"

BattleTowerBattleRoom_Johto_Text_ReadyForNextOpponent:
	.string "Next up is Trainer No. {STR_VAR_3}!\nAre you ready to continue?$"

BattleTowerBattleRoom_Johto_Text_ConfirmCancel:
	.string "Would you like to cancel your\nBATTLE ROOM challenge?$"

BattleTowerBattleRoom_Johto_Text_ChallengeCanceled:
	.string "We understand.\nWe will return you to the lobby.$"

BattleTowerBattleRoom_Johto_Text_PlayerLost:
	.string "You were defeated…\pBetter luck next time!\nWe will return you to the lobby.$"

BattleTowerBattleRoom_Johto_Text_PlayerWonAllInRoom:
	.string "Sensational!\pYou have defeated all 7 trainers!\nPlease return to the lobby to receive\lyour victory prize!$"
