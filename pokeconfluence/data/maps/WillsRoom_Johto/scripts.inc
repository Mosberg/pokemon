WillsRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, WillsRoom_Johto_OnFrame
	.byte 0

WillsRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_WILLS_ROOM, 0, WillsRoom_Johto_WillsRoomDoorLocksBehindYouScript_Entry
	.2byte 0

WillsRoom_Johto_WillScript_Battle_Entry::
	lockall
	goto WillsRoom_Johto_WillScript_Battle

WillsRoom_Johto_WillsRoomDoorLocksBehindYouScript_Entry::
	lockall
	goto WillsRoom_Johto_WillsRoomDoorLocksBehindYouScript


WillsRoom_Johto_WillsRoomDoorLocksBehindYouScript:
	applymovement OBJ_EVENT_ID_PLAYER, WillsRoom_Johto_WillsRoom_EnterMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_STRENGTH
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_WILLS_ROOM, 1
	setflag FLAG_JOHTO_WILLS_ROOM_ENTRANCE_CLOSED
	waitse
	releaseall
	end

WillsRoom_Johto_WillScript_Battle:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_ELITE_4_WILL, WillsRoom_Johto_WillScript_AfterBattle
	message WillsRoom_Johto_WillScript_WillBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_WILL_WILL1, WillsRoom_Johto_WillScript_WillBeatenText
	setflag FLAG_JOHTO_BEAT_ELITE_4_WILL
	message WillsRoom_Johto_WillScript_WillDefeatText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_DOOR
	setmetatile 4, 2, 530, 0
	setmetatile 5, 2, 530, 0
	setmetatile 4, 3, 519, 0
	setmetatile 5, 3, 519, 0
	special DrawWholeMapView
	closemessage
	setflag FLAG_JOHTO_WILLS_ROOM_EXIT_OPEN
	waitse
	releaseall
	end

WillsRoom_Johto_WillScript_AfterBattle:
	message WillsRoom_Johto_WillScript_WillDefeatText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WillsRoom_Johto_WillsRoom_EnterMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

WillsRoom_Johto_WillScript_WillBeforeText:
	.string "Welcome to POKéMON\n"
	.string "LEAGUE, {PLAYER}."
	.string "\pAllow me to intro-\n"
	.string "duce myself. I am\l"
	.string "WILL."
	.string "\pI have trained all\n"
	.string "around the world,"
	.string "\pmaking my psychic\n"
	.string "POKéMON powerful."
	.string "\pAnd, at last, I've\n"
	.string "been accepted into\l"
	.string "the ELITE FOUR."
	.string "\pI can only keep\n"
	.string "getting better!"
	.string "\pLosing is not an\n"
	.string "option!$"

WillsRoom_Johto_WillScript_WillBeatenText:
	.string "I… I can't…\n"
	.string "believe it…$"

WillsRoom_Johto_WillScript_WillDefeatText:
	.string "Even though I was\n"
	.string "defeated, I won't\l"
	.string "change my course."
	.string "\pI will continue\n"
	.string "battling until I"
	.string "\pstand above all\n"
	.string "trainers!"
	.string "\pNow, {PLAYER}, move\n"
	.string "on and experience"
	.string "\pthe true ferocity\n"
	.string "of the ELITE FOUR.$"
