VermilionPort_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionPort_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VermilionPort_Johto_OnFrame
	.byte 0

VermilionPort_Johto_OnTransition:
	call VermilionPort_Johto_VermilionPortFlypointCallback_Cb
	end

VermilionPort_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_VERMILION_PORT, 1, VermilionPort_Johto_VermilionPortLeaveShipScript_Entry
	.2byte 0

VermilionPort_Johto_VermilionPortSailorAtGangwayScript_Entry::
	lockall
	goto VermilionPort_Johto_VermilionPortSailorAtGangwayScript

VermilionPort_Johto_VermilionPortSailorScript_Entry::
	lockall
	goto VermilionPort_Johto_VermilionPortSailorScript

VermilionPort_Johto_VermilionPortSuperNerdScript_Entry::
	lockall
	goto VermilionPort_Johto_VermilionPortSuperNerdScript

VermilionPort_Johto_VermilionPortWalkUpToShipScript_Entry::
	lockall
	goto VermilionPort_Johto_VermilionPortWalkUpToShipScript

VermilionPort_Johto_VermilionPortLeaveShipScript_Entry::
	lockall
	goto VermilionPort_Johto_VermilionPortLeaveShipScript


VermilionPort_Johto_VermilionPortLeaveShipScript:
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortLeaveFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	clearflag FLAG_JOHTO_VERMILION_PORT_SAILOR_AT_GANGWAY
	addobject 1
	setvar VAR_JOHTO_SCENE_VERMILION_PORT, 0
	setflag FLAG_JOHTO_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_1
	setflag FLAG_JOHTO_FAST_SHIP_CABINS_SE_SSE_GENTLEMAN
	setflag FLAG_JOHTO_FAST_SHIP_PASSENGERS_FIRST_TRIP
	clearflag FLAG_JOHTO_OLIVINE_PORT_PASSAGE_POKEFAN_M
	setflag FLAG_JOHTO_FAST_SHIP_FIRST_TIME
	setflag FLAG_TEMP_11
	setrespawn HEAL_LOCATION_JOHTO_VERMILION_CITY
	releaseall
	end

VermilionPort_Johto_VermilionPortSailorAtGangwayScript:
	faceplayer
	goto_if_set FLAG_TEMP_11, VermilionPort_Johto_VermilionPortAlreadyRodeScript
	message VermilionPort_Johto_VermilionPortDepartingText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 10
	playse SE_EXIT
	removeobject 1
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	setflag FLAG_JOHTO_FAST_SHIP_PASSENGERS_EASTBOUND
	clearflag FLAG_JOHTO_FAST_SHIP_PASSENGERS_WESTBOUND
	clearflag FLAG_JOHTO_BEAT_POKEMANIAC_ETHAN
	clearflag FLAG_JOHTO_BEAT_BURGLAR_COREY
	clearflag FLAG_JOHTO_BEAT_BUG_CATCHER_KEN
	clearflag FLAG_JOHTO_BEAT_GUITARIST_CLYDE
	clearflag FLAG_JOHTO_BEAT_POKEFANM_JEREMY
	clearflag FLAG_JOHTO_BEAT_POKEFANF_GEORGIA
	clearflag FLAG_JOHTO_BEAT_SAILOR_KENNETH
	clearflag FLAG_JOHTO_BEAT_TEACHER_SHIRLEY
	clearflag FLAG_JOHTO_BEAT_SCHOOLBOY_NATE
	clearflag FLAG_JOHTO_BEAT_SCHOOLBOY_RICKY
	setflag FLAG_JOHTO_FAST_SHIP_DESTINATION_OLIVINE
	clearflag FLAG_JOHTO_VERMILION_PORT_SAILOR_AT_GANGWAY
	addobject 1
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 1
	warp MAP_JOHTO_FAST_SHIP_1F, 25, 1
	waitstate

VermilionPort_Johto_VermilionPortAlreadyRodeScript:
	message VermilionPort_Johto_VermilionPortCantBoardText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortWalkUpToShipScript:
	applymovement 2, Johto_Movement_Face_Right
	waitmovement 2
	goto_if_set FLAG_TEMP_11, VermilionPort_Johto_VermilionPortWalkUpToShipScript_skip
	goto_if_set FLAG_TEMP_12, VermilionPort_Johto_VermilionPortWalkUpToShipScript_skip
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 1, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipWednesday
	goto_if_eq VAR_RESULT, 2, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipWednesday
	goto_if_eq VAR_RESULT, 4, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipSunday
	goto_if_eq VAR_RESULT, 5, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipSunday
	goto_if_eq VAR_RESULT, 6, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipSunday
	message VermilionPort_Johto_VermilionPortAskBoardingText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, VermilionPort_Johto_VermilionPortNotRidingMoveAwayScript
	message VermilionPort_Johto_VermilionPortAskTicketText
	waitmessage
	waitbuttonpress
	checkitem ITEM_SS_TICKET, 1
	goto_if_eq VAR_RESULT, 0, VermilionPort_Johto_VermilionPortWalkUpToShipScript_NoTicket
	message VermilionPort_Johto_VermilionPortSSTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_12
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortApproachFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionPort_Johto_VermilionPortSailorAtGangwayScript

VermilionPort_Johto_VermilionPortWalkUpToShipScript_NoTicket:
	message VermilionPort_Johto_VermilionPortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipWednesday:
	message VermilionPort_Johto_VermilionPortSailWednesdayText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

VermilionPort_Johto_VermilionPortWalkUpToShipScript_NextShipSunday:
	message VermilionPort_Johto_VermilionPortSailSundayText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

VermilionPort_Johto_VermilionPortWalkUpToShipScript_skip:
	releaseall
	end

VermilionPort_Johto_VermilionPortNotRidingScript:
	message VermilionPort_Johto_VermilionPortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortNotRidingMoveAwayScript:
	message VermilionPort_Johto_VermilionPortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

VermilionPort_Johto_VermilionPortSailorScript:
	faceplayer
	goto_if_set FLAG_TEMP_11, VermilionPort_Johto_VermilionPortAlreadyRodeScript
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 1, VermilionPort_Johto_VermilionPortSailorScript_NextShipWednesday
	goto_if_eq VAR_RESULT, 2, VermilionPort_Johto_VermilionPortSailorScript_NextShipWednesday
	goto_if_eq VAR_RESULT, 4, VermilionPort_Johto_VermilionPortSailorScript_NextShipSunday
	goto_if_eq VAR_RESULT, 5, VermilionPort_Johto_VermilionPortSailorScript_NextShipSunday
	goto_if_eq VAR_RESULT, 6, VermilionPort_Johto_VermilionPortSailorScript_NextShipSunday
	message VermilionPort_Johto_VermilionPortAskBoardingText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, VermilionPort_Johto_VermilionPortNotRidingScript
	message VermilionPort_Johto_VermilionPortAskTicketText
	waitmessage
	waitbuttonpress
	checkitem ITEM_SS_TICKET, 1
	goto_if_eq VAR_RESULT, 0, VermilionPort_Johto_VermilionPortSailorScript_NoTicket
	message VermilionPort_Johto_VermilionPortSSTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_12
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Johto_VermilionPortApproachFastShipRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionPort_Johto_VermilionPortSailorAtGangwayScript

VermilionPort_Johto_VermilionPortSailorScript_NoTicket:
	message VermilionPort_Johto_VermilionPortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortSailorScript_NextShipWednesday:
	message VermilionPort_Johto_VermilionPortSailWednesdayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortSailorScript_NextShipSunday:
	message VermilionPort_Johto_VermilionPortSailSundayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortSuperNerdScript:
	faceplayer
	message VermilionPort_Johto_VermilionPortSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPort_Johto_VermilionPortFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_VERMILION
	return

VermilionPort_Johto_VermilionPortEnterFastShipMovement:
	walk_down
	step_end

VermilionPort_Johto_VermilionPortLeaveFastShipMovement:
	walk_up
	step_end

VermilionPort_Johto_VermilionPortCannotEnterFastShipMovement:
	walk_right
	face_left
	step_end

VermilionPort_Johto_VermilionPortApproachFastShipMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VermilionPort_Johto_VermilionPortApproachFastShipRightMovement:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VermilionPort_Johto_VermilionPortDepartingText:
	.string "We're departing\n"
	.string "soon. Please get\l"
	.string "on board.$"

VermilionPort_Johto_VermilionPortCantBoardText:
	.string "Sorry. You can't\n"
	.string "board now.$"

VermilionPort_Johto_VermilionPortAskBoardingText:
	.string "Welcome to FAST\n"
	.string "SHIP S.S.AQUA."
	.string "\pWill you be board-\n"
	.string "ing today?$"

VermilionPort_Johto_VermilionPortAskTicketText:
	.string "May I see your\n"
	.string "S.S.TICKET?$"

VermilionPort_Johto_VermilionPortComeAgainText:
	.string "We hope to see you\n"
	.string "again!$"

VermilionPort_Johto_VermilionPortSSTicketText:
	.string "{PLAYER} flashed\n"
	.string "the S.S.TICKET."
	.string "\pThat's it.\n"
	.string "Thank you!$"

VermilionPort_Johto_VermilionPortNoTicketText:
	.string "{PLAYER} tried to\n"
	.string "show the S.S.\l"
	.string "TICKET…"
	.string "\p…But no TICKET!"
	.string "\pSorry!\n"
	.string "You may board only"
	.string "\pif you have an\n"
	.string "S.S.TICKET.$"

VermilionPort_Johto_VermilionPortSailWednesdayText:
	.string "The FAST SHIP will\n"
	.string "sail on Wednesday.$"

VermilionPort_Johto_VermilionPortSailSundayText:
	.string "The FAST SHIP will\n"
	.string "sail next Sunday.$"

VermilionPort_Johto_VermilionPortSuperNerdText:
	.string "You came from\n"
	.string "JOHTO?"
	.string "\pI hear many rare\n"
	.string "POKéMON live over\l"
	.string "there.$"
