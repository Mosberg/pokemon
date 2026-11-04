HallOfFame_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, HallOfFame_Johto_OnFrame
	.byte 0

HallOfFame_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_HALL_OF_FAME, 0, HallOfFame_Johto_HallOfFameEnterScript_Entry
	.2byte 0

HallOfFame_Johto_HallOfFameEnterScript_Entry::
	lockall
	goto HallOfFame_Johto_HallOfFameEnterScript


HallOfFame_Johto_HallOfFameEnterScript:
	applymovement OBJ_EVENT_ID_PLAYER, HallOfFame_Johto_HallOfFame_WalkUpWithLance
	applymovement 1, HallOfFame_Johto_HallOfFame_WalkUpWithLance
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message HallOfFame_Johto_HallOfFame_LanceText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, HallOfFame_Johto_HallOfFame_SlowlyApproachMachine
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_JOHTO_SCENE_HALL_OF_FAME, 1
	delay 15
	setvar VAR_RESULT, 0
	setflag FLAG_JOHTO_BEAT_ELITE_FOUR
	setflag FLAG_JOHTO_TELEPORT_GUY
	setflag FLAG_JOHTO_RIVAL_SPROUT_TOWER
	clearflag FLAG_JOHTO_RED_IN_MT_SILVER
	setflag FLAG_JOHTO_OLIVINE_PORT_SPRITES_BEFORE_HALL_OF_FAME
	clearflag FLAG_JOHTO_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME
	setvar VAR_JOHTO_SCENE_SPROUT_TOWER_3F, 1
	special HealPlayerParty
	goto_if_set FLAG_JOHTO_GOT_SS_TICKET_FROM_ELM, HallOfFame_Johto_HallOfFameEnterScript_SkipPhoneCall

HallOfFame_Johto_HallOfFameEnterScript_SkipPhoneCall:
	@ TODO unsupported: halloffame 
	goto Johto_EventScript_Unimplemented

HallOfFame_Johto_HallOfFame_WalkUpWithLance:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_left
	step_end

HallOfFame_Johto_HallOfFame_SlowlyApproachMachine:
	walk_slow_up
	step_end

HallOfFame_Johto_HallOfFame_LanceText:
	.string "LANCE: It's been a\n"
	.string "long time since I\l"
	.string "last came here."
	.string "\pThis is where we\n"
	.string "honor the LEAGUE"
	.string "\pCHAMPIONS for all\n"
	.string "eternity."
	.string "\pTheir courageous\n"
	.string "POKéMON are also\l"
	.string "inducted."
	.string "\pHere today, we\n"
	.string "witnessed the rise"
	.string "\pof a new LEAGUE\n"
	.string "CHAMPION--a"
	.string "\ptrainer who feels\n"
	.string "compassion for,"
	.string "\pand trust toward,\n"
	.string "all POKéMON."
	.string "\pA trainer who\n"
	.string "succeeded through"
	.string "\pperseverance and\n"
	.string "determination."
	.string "\pThe new LEAGUE\n"
	.string "CHAMPION who has"
	.string "\pall the makings\n"
	.string "of greatness!"
	.string "\p{PLAYER}, allow me\n"
	.string "to register you"
	.string "\pand your partners\n"
	.string "as CHAMPIONS!$"
