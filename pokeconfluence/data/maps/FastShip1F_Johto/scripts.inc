FastShip1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FastShip1F_Johto_OnFrame
	.byte 0

FastShip1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_FAST_SHIP_1F, 1, FastShip1F_Johto_FastShip1FEnterShipScript_Entry
	.2byte 0

FastShip1F_Johto_FastShip1FSailor1Script_Entry::
	lockall
	goto FastShip1F_Johto_FastShip1FSailor1Script

FastShip1F_Johto_FastShip1FSailor2Script_Entry::
	lockall
	goto FastShip1F_Johto_FastShip1FSailor2Script

FastShip1F_Johto_FastShip1FSailor3Script_Entry::
	lockall
	goto FastShip1F_Johto_FastShip1FSailor3Script

FastShip1F_Johto_WorriedGrandpaSceneLeft_Entry::
	lockall
	goto FastShip1F_Johto_WorriedGrandpaSceneLeft

FastShip1F_Johto_WorriedGrandpaSceneRight_Entry::
	lockall
	goto FastShip1F_Johto_WorriedGrandpaSceneRight

FastShip1F_Johto_FastShip1FEnterShipScript_Entry::
	lockall
	goto FastShip1F_Johto_FastShip1FEnterShipScript


FastShip1F_Johto_FastShip1FEnterShipScript:
	applymovement 1, FastShip1F_Johto_FastShip1F_SailorStepAsideMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, FastShip1F_Johto_FastShip1F_PlayerEntersShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, FastShip1F_Johto_FastShip1F_SailorBlocksDoorMovement
	waitmovement 1
	delay 30
	playse SE_PIN
	clearflag FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, FastShip1F_Johto_FastShip1FEnterShipScript_SkipGrandpa
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 2
	releaseall
	end

FastShip1F_Johto_FastShip1FEnterShipScript_SkipGrandpa:
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 0
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED, FastShip1F_Johto_FastShip1FSailor1Script_Arrived
	goto_if_set FLAG_JOHTO_FAST_SHIP_DESTINATION_OLIVINE, FastShip1F_Johto_FastShip1FSailor1Script_Olivine
	message FastShip1F_Johto_FastShip1FSailor1Text_ToVermilion
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor1Script_Olivine:
	message FastShip1F_Johto_FastShip1FSailor1Text_ToOlivine
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor1Script_Arrived:
	goto_if_set FLAG_JOHTO_FAST_SHIP_DESTINATION_OLIVINE, FastShip1F_Johto_FastShip1FSailor1Script__Olivine
	message FastShip1F_Johto_FastShip1FSailor1Text_InVermilion
	waitmessage
	waitbuttonpress
	closemessage
	call FastShip1F_Johto_FastShip1FSailor1Script_LetThePlayerOut_Sub
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	setflag FLAG_JOHTO_VERMILION_PORT_SAILOR_AT_GANGWAY
	setvar VAR_JOHTO_SCENE_VERMILION_PORT, 1
	warp MAP_JOHTO_VERMILION_PORT, 7, 17
	waitstate

FastShip1F_Johto_FastShip1FSailor1Script__Olivine:
	message FastShip1F_Johto_FastShip1FSailor1Text_InOlivine
	waitmessage
	waitbuttonpress
	closemessage
	call FastShip1F_Johto_FastShip1FSailor1Script_LetThePlayerOut_Sub
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	setflag FLAG_JOHTO_OLIVINE_PORT_SAILOR_AT_GANGWAY
	setvar VAR_JOHTO_SCENE_OLIVINE_PORT, 1
	warp MAP_JOHTO_OLIVINE_PORT, 7, 23
	waitstate

FastShip1F_Johto_FastShip1FSailor2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, FastShip1F_Johto_FastShip1FSailor2Script_Vermilion
	message FastShip1F_Johto_FastShip1FSailor2Text_FirstTime
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor2Script_Vermilion:
	message FastShip1F_Johto_FastShip1FSailor2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor3Script:
	faceplayer
	message FastShip1F_Johto_FastShip1FSailor3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShip1F_Johto_WorriedGrandpaSceneRight:
	setobjectxyperm 4, 20, 6

FastShip1F_Johto_WorriedGrandpaSceneLeft:
	clearflag FLAG_JOHTO_FAST_SHIP_1F_GENTLEMAN
	addobject 4
	applymovement 4, FastShip1F_Johto_FastShip1F_GrandpaRunsInMovement
	waitmovement 4
	playse SE_M_TAIL_WHIP
	applymovement OBJ_EVENT_ID_PLAYER, FastShip1F_Johto_FastShip1F_PlayerHitByGrandpaMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, FastShip1F_Johto_FastShip1F_GrandpaApproachesPlayerMovement
	waitmovement 4
	message FastShip1F_Johto_FastShip1FGrandpaText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, FastShip1F_Johto_FastShip1F_GrandpaRunsOutMovement
	waitmovement 4
	removeobject 4
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 0
	releaseall
	end

FastShip1F_Johto_FastShip1FSailor1Script_LetThePlayerOut_Sub:
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, FastShip1F_Johto_FastShip1FSailor1Script_YouAreFacingRight_Sub
	applymovement 1, FastShip1F_Johto_FastShip1F_SailorStepAsideMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, FastShip1F_Johto_FastShip1F_PlayerLeavesShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return

FastShip1F_Johto_FastShip1FSailor1Script_YouAreFacingRight_Sub:
	applymovement 1, FastShip1F_Johto_FastShip1F_SailorStepAsideDownMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, FastShip1F_Johto_FastShip1F_PlayerLeavesShipRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return

FastShip1F_Johto_FastShip1F_SailorStepAsideMovement:
	walk_slow_left
	face_right
	step_end

FastShip1F_Johto_FastShip1F_SailorBlocksDoorMovement:
	walk_slow_right
	face_down
	step_end

FastShip1F_Johto_FastShip1F_SailorStepAsideDownMovement:
	walk_slow_down
	face_up
	step_end

FastShip1F_Johto_FastShip1F_PlayerEntersShipMovement:
	walk_down
	walk_down
	face_down
	step_end

FastShip1F_Johto_FastShip1F_GrandpaRunsInMovement:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

FastShip1F_Johto_FastShip1F_GrandpaApproachesPlayerMovement:
	walk_right
	step_end

FastShip1F_Johto_FastShip1F_GrandpaRunsOutMovement:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

FastShip1F_Johto_FastShip1F_PlayerHitByGrandpaMovement:
	walk_fast_right
	face_left
	step_end

FastShip1F_Johto_FastShip1F_PlayerLeavesShipMovement:
	walk_up
	walk_up
	step_end

FastShip1F_Johto_FastShip1F_PlayerLeavesShipRightMovement:
	walk_right
	walk_up
	step_end

FastShip1F_Johto_FastShip1FSailor1Text_ToVermilion:
	.string "FAST SHIP S.S.AQUA\n"
	.string "is en route to\l"
	.string "VERMILION CITY."
	.string "\pWe will make an\n"
	.string "announcement when\l"
	.string "we arrive.$"

FastShip1F_Johto_FastShip1FSailor1Text_ToOlivine:
	.string "FAST SHIP S.S.AQUA\n"
	.string "is en route to\l"
	.string "OLIVINE CITY."
	.string "\pWe will make an\n"
	.string "announcement when\l"
	.string "we arrive.$"

FastShip1F_Johto_FastShip1FSailor2Text_FirstTime:
	.string "Here's your cabin."
	.string "\pIf your POKéMON\n"
	.string "are hurt, take a\l"
	.string "nap in the bed."
	.string "\pThat will heal\n"
	.string "them.$"

FastShip1F_Johto_FastShip1FSailor2Text:
	.string "Here's your cabin."
	.string "\pYou can heal your\n"
	.string "POKéMON by taking\l"
	.string "a nap in the bed."
	.string "\pThe ship will\n"
	.string "arrive while\l"
	.string "you're sleeping.$"

FastShip1F_Johto_FastShip1FSailor3Text:
	.string "The passengers are\n"
	.string "all trainers."
	.string "\pThey're all itch-\n"
	.string "ing to battle in\l"
	.string "their cabins.$"

FastShip1F_Johto_FastShip1FGrandpaText:
	.string "Whoa! Excuse me.\n"
	.string "I was in a hurry!"
	.string "\pMy granddaughter\n"
	.string "is missing!"
	.string "\pShe's just a wee\n"
	.string "girl. If you see"
	.string "\pher, please let me\n"
	.string "know!$"

FastShip1F_Johto_FastShip1FSailor1Text_InOlivine:
	.string "FAST SHIP S.S.AQUA\n"
	.string "has arrived in\l"
	.string "OLIVINE CITY.$"

FastShip1F_Johto_FastShip1FSailor1Text_InVermilion:
	.string "FAST SHIP S.S.AQUA\n"
	.string "has arrived in\l"
	.string "VERMILION CITY.$"
