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
	goto BattleTowerBattleRoom_Johto_Script_BattleRoom

BattleTowerBattleRoom_Johto_Script_BattleRoom:
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_BATTLE_ROOM, 1
	applymovement OBJ_EVENT_ID_PLAYER, BattleTowerBattleRoom_Johto_Movement_PlayerWalksIn
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 2, BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsToPlayer
	waitmovement 2
	message BattleTowerBattleRoom_Johto_Text_WelcomeToBattleRoom
	waitmessage
	waitbuttonpress
	closemessage
	warp MAP_JOHTO_BATTLE_TOWER_1F, 7, 7
	waitstate
	end

BattleTowerBattleRoom_Johto_Movement_PlayerWalksIn:
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

BattleTowerBattleRoom_Johto_Movement_ReceptionistStepsToPlayer:
	walk_right
	walk_right
	walk_up
	walk_up
	face_right
	step_end

BattleTowerBattleRoom_Johto_Text_WelcomeToBattleRoom:
	.string "Welcome to the\n"
	.string "BATTLE ROOM!\pThe BATTLE TOWER\n"
	.string "challenge session\l"
	.string "is in preparation.\pWe will return you\n"
	.string "to the lobby.$"

