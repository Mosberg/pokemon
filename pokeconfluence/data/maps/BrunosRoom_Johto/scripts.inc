BrunosRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BrunosRoom_Johto_OnFrame
	.byte 0

BrunosRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_BRUNOS_ROOM, 0, BrunosRoom_Johto_BrunosRoomDoorLocksBehindYouScript_Entry
	.2byte 0

BrunosRoom_Johto_BrunoScript_Battle_Entry::
	lockall
	goto BrunosRoom_Johto_BrunoScript_Battle

BrunosRoom_Johto_BrunosRoomDoorLocksBehindYouScript_Entry::
	lockall
	goto BrunosRoom_Johto_BrunosRoomDoorLocksBehindYouScript


BrunosRoom_Johto_BrunosRoomDoorLocksBehindYouScript:
	applymovement OBJ_EVENT_ID_PLAYER, BrunosRoom_Johto_BrunosRoom_EnterMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_STRENGTH
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_BRUNOS_ROOM, 1
	setflag FLAG_JOHTO_BRUNOS_ROOM_ENTRANCE_CLOSED
	waitse
	releaseall
	end

BrunosRoom_Johto_BrunoScript_Battle:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_ELITE_4_BRUNO, BrunosRoom_Johto_BrunoScript_AfterBattle
	message BrunosRoom_Johto_BrunoScript_BrunoBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_BRUNO_BRUNO1, BrunosRoom_Johto_BrunoScript_BrunoBeatenText
	setflag FLAG_JOHTO_BEAT_ELITE_4_BRUNO
	message BrunosRoom_Johto_BrunoScript_BrunoDefeatText
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
	setflag FLAG_JOHTO_BRUNOS_ROOM_EXIT_OPEN
	waitse
	releaseall
	end

BrunosRoom_Johto_BrunoScript_AfterBattle:
	message BrunosRoom_Johto_BrunoScript_BrunoDefeatText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BrunosRoom_Johto_BrunosRoom_EnterMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BrunosRoom_Johto_BrunoScript_BrunoBeforeText:
	.string "I am BRUNO of the\n"
	.string "ELITE FOUR."
	.string "\pI always train to\n"
	.string "the extreme be-\l"
	.string "cause I believe in\l"
	.string "our potential."
	.string "\pThat is how we\n"
	.string "became strong."
	.string "\pCan you withstand\n"
	.string "our power?"
	.string "\pHm? I see no fear\n"
	.string "in you. You look"
	.string "\pdetermined. Per-\n"
	.string "fect for battle!"
	.string "\pReady, {PLAYER}?\n"
	.string "You will bow down"
	.string "\pto our overwhelm-\n"
	.string "ing power!"
	.string "\pHoo hah!$"

BrunosRoom_Johto_BrunoScript_BrunoBeatenText:
	.string "Why? How could we\n"
	.string "lose?$"

BrunosRoom_Johto_BrunoScript_BrunoDefeatText:
	.string "Having lost, I\n"
	.string "have no right to\l"
	.string "say anything…"
	.string "\pGo face your next\n"
	.string "challenge!$"
