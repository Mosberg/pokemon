KogasRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, KogasRoom_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KogasRoom_Johto_OnFrame
	.byte 0

KogasRoom_Johto_OnLoad:
	call KogasRoom_Johto_KogasRoomDoorsCallback_Cb
	end

KogasRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_KOGAS_ROOM, 0, KogasRoom_Johto_KogasRoomDoorLocksBehindYouScript_Entry
	.2byte 0

KogasRoom_Johto_KogaScript_Battle_Entry::
	lockall
	goto KogasRoom_Johto_KogaScript_Battle

KogasRoom_Johto_KogasRoomDoorLocksBehindYouScript_Entry::
	lockall
	goto KogasRoom_Johto_KogasRoomDoorLocksBehindYouScript


KogasRoom_Johto_KogasRoomDoorLocksBehindYouScript:
	applymovement OBJ_EVENT_ID_PLAYER, KogasRoom_Johto_KogasRoom_EnterMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_STRENGTH
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_KOGAS_ROOM, 1
	setflag FLAG_JOHTO_KOGAS_ROOM_ENTRANCE_CLOSED
	waitse
	releaseall
	end

KogasRoom_Johto_KogaScript_Battle:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_ELITE_4_KOGA, KogasRoom_Johto_KogaScript_AfterBattle
	message KogasRoom_Johto_KogaScript_KogaBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_KOGA_KOGA1, KogasRoom_Johto_KogaScript_KogaBeatenText
	setflag FLAG_JOHTO_BEAT_ELITE_4_KOGA
	message KogasRoom_Johto_KogaScript_KogaDefeatText
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
	setflag FLAG_JOHTO_KOGAS_ROOM_EXIT_OPEN
	waitse
	releaseall
	end

KogasRoom_Johto_KogaScript_AfterBattle:
	message KogasRoom_Johto_KogaScript_KogaDefeatText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KogasRoom_Johto_KogasRoomDoorsCallback_Cb:
	goto_if_unset FLAG_JOHTO_KOGAS_ROOM_ENTRANCE_CLOSED, KogasRoom_Johto_KogasRoomDoorsCallback_KeepEntranceOpen_Cb
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView

KogasRoom_Johto_KogasRoomDoorsCallback_KeepEntranceOpen_Cb:
	goto_if_unset FLAG_JOHTO_KOGAS_ROOM_EXIT_OPEN, KogasRoom_Johto_KogasRoomDoorsCallback_KeepExitClosed_Cb
	setmetatile 4, 2, 530, 0
	setmetatile 5, 2, 530, 0
	setmetatile 4, 3, 519, 0
	setmetatile 5, 3, 519, 0
	special DrawWholeMapView

KogasRoom_Johto_KogasRoomDoorsCallback_KeepExitClosed_Cb:
	return

KogasRoom_Johto_KogasRoom_EnterMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

KogasRoom_Johto_KogaScript_KogaBeforeText:
	.string "Fwahahahaha!"
	.string "\pI am KOGA of the\n"
	.string "ELITE FOUR."
	.string "\pI live in shadows,\n"
	.string "a ninja!"
	.string "\pMy intricate style\n"
	.string "will confound and\l"
	.string "destroy you!"
	.string "\pConfusion, sleep,\n"
	.string "poison…"
	.string "\pPrepare to be the\n"
	.string "victim of my sin-\l"
	.string "ister technique!"
	.string "\pFwahahahaha!"
	.string "\pPOKéMON is not\n"
	.string "merely about brute"
	.string "\pforce--you shall\n"
	.string "see soon enough!$"

KogasRoom_Johto_KogaScript_KogaBeatenText:
	.string "Ah!\n"
	.string "You have proven\l"
	.string "your worth!$"

KogasRoom_Johto_KogaScript_KogaDefeatText:
	.string "I subjected you to\n"
	.string "everything I could\l"
	.string "muster."
	.string "\pBut my efforts\n"
	.string "failed. I must\l"
	.string "hone my skills."
	.string "\pGo on to the next\n"
	.string "room, and put your\l"
	.string "abilities to test!$"
