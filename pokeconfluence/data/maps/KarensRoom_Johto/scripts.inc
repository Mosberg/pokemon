KarensRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, KarensRoom_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KarensRoom_Johto_OnFrame
	.byte 0

KarensRoom_Johto_OnLoad:
	call KarensRoom_Johto_KarensRoomDoorsCallback_Cb
	end

KarensRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_KARENS_ROOM, 0, KarensRoom_Johto_KarensRoomDoorLocksBehindYouScript_Entry
	.2byte 0

KarensRoom_Johto_KarenScript_Battle_Entry::
	lockall
	goto KarensRoom_Johto_KarenScript_Battle

KarensRoom_Johto_KarensRoomDoorLocksBehindYouScript_Entry::
	lockall
	goto KarensRoom_Johto_KarensRoomDoorLocksBehindYouScript


KarensRoom_Johto_KarensRoomDoorLocksBehindYouScript:
	applymovement OBJ_EVENT_ID_PLAYER, KarensRoom_Johto_KarensRoom_EnterMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_STRENGTH
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_KARENS_ROOM, 1
	setflag FLAG_JOHTO_KARENS_ROOM_ENTRANCE_CLOSED
	waitse
	releaseall
	end

KarensRoom_Johto_KarenScript_Battle:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_ELITE_4_KAREN, KarensRoom_Johto_KarenScript_AfterBattle
	message KarensRoom_Johto_KarenScript_KarenBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_KAREN_KAREN1, KarensRoom_Johto_KarenScript_KarenBeatenText
	setflag FLAG_JOHTO_BEAT_ELITE_4_KAREN
	message KarensRoom_Johto_KarenScript_KarenDefeatText
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
	setflag FLAG_JOHTO_KARENS_ROOM_EXIT_OPEN
	waitse
	releaseall
	end

KarensRoom_Johto_KarenScript_AfterBattle:
	message KarensRoom_Johto_KarenScript_KarenDefeatText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KarensRoom_Johto_KarensRoomDoorsCallback_Cb:
	goto_if_unset FLAG_JOHTO_KARENS_ROOM_ENTRANCE_CLOSED, KarensRoom_Johto_KarensRoomDoorsCallback_KeepEntranceOpen_Cb
	setmetatile 4, 14, 527, 1
	setmetatile 5, 14, 526, 1
	setmetatile 4, 15, 528, 1
	setmetatile 5, 15, 528, 1
	special DrawWholeMapView

KarensRoom_Johto_KarensRoomDoorsCallback_KeepEntranceOpen_Cb:
	goto_if_unset FLAG_JOHTO_KARENS_ROOM_EXIT_OPEN, KarensRoom_Johto_KarensRoomDoorsCallback_KeepExitClosed_Cb
	setmetatile 4, 2, 530, 0
	setmetatile 5, 2, 530, 0
	setmetatile 4, 3, 519, 0
	setmetatile 5, 3, 519, 0
	special DrawWholeMapView

KarensRoom_Johto_KarensRoomDoorsCallback_KeepExitClosed_Cb:
	return

KarensRoom_Johto_KarensRoom_EnterMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

KarensRoom_Johto_KarenScript_KarenBeforeText:
	.string "I am KAREN of the\n"
	.string "ELITE FOUR."
	.string "\pYou're {PLAYER}?\n"
	.string "How amusing."
	.string "\pI love dark-type\n"
	.string "POKéMON."
	.string "\pI find their wild,\n"
	.string "tough image to be"
	.string "\pso appealing. And\n"
	.string "they're so strong."
	.string "\pThink you can take\n"
	.string "them? Just try to\l"
	.string "entertain me."
	.string "\pLet's go.$"

KarensRoom_Johto_KarenScript_KarenBeatenText:
	.string "Well, aren't you\n"
	.string "good. I like that\l"
	.string "in a trainer.$"

KarensRoom_Johto_KarenScript_KarenDefeatText:
	.string "Strong POKéMON."
	.string "\pWeak POKéMON."
	.string "\pThat is only the\n"
	.string "selfish perception\l"
	.string "of people."
	.string "\pTruly skilled\n"
	.string "trainers should"
	.string "\ptry to win with\n"
	.string "their favorites."
	.string "\pI like your style.\n"
	.string "You understand\l"
	.string "what's important."
	.string "\pGo on--the CHAM-\n"
	.string "PION is waiting.$"
