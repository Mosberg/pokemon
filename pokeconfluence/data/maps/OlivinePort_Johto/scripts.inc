OlivinePort_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivinePort_Johto_OnFrame
	.byte 0

OlivinePort_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_OLIVINE_PORT, 1, OlivinePort_Johto_OlivinePortLeaveShipScript_Entry
	.2byte 0

OlivinePort_Johto_OlivinePortSailorAtGangwayScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortSailorAtGangwayScript

OlivinePort_Johto_OlivinePortSailorBeforeHOFScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortSailorBeforeHOFScript

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortSailorAfterHOFScript

OlivinePort_Johto_OlivinePortFishingGuru1Script_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortFishingGuru1Script

OlivinePort_Johto_OlivinePortFishingGuru2Script_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortFishingGuru2Script

OlivinePort_Johto_OlivinePortYoungsterScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortYoungsterScript

OlivinePort_Johto_OlivinePortCooltrainerFScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortCooltrainerFScript

OlivinePort_Johto_OlivinePortWalkUpToShipScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortWalkUpToShipScript

OlivinePort_Johto_OlivinePortLeaveShipScript_Entry::
	lockall
	goto OlivinePort_Johto_OlivinePortLeaveShipScript


OlivinePort_Johto_OlivinePortLeaveShipScript:
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortLeaveFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	clearflag FLAG_JOHTO_OLIVINE_PORT_SAILOR_AT_GANGWAY
	addobject 1
	setvar VAR_JOHTO_SCENE_OLIVINE_PORT, 0
	setflag FLAG_TEMP_11
	setrespawn HEAL_LOCATION_JOHTO_OLIVINE_CITY
	releaseall
	end

OlivinePort_Johto_OlivinePortSailorAtGangwayScript:
	faceplayer
	goto_if_set FLAG_TEMP_11, OlivinePort_Johto_OlivinePortAlreadyRodeScript
	message OlivinePort_Johto_OlivinePortSailorGetOnBoardText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 10
	playse SE_EXIT
	removeobject 1
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	goto_if_unset FLAG_JOHTO_FAST_SHIP_FIRST_TIME, OlivinePort_Johto_OlivinePortSailorAtGangwayScript_FirstTime
	clearflag FLAG_JOHTO_FAST_SHIP_PASSENGERS_EASTBOUND
	setflag FLAG_JOHTO_FAST_SHIP_PASSENGERS_WESTBOUND
	clearflag FLAG_JOHTO_BEAT_COOLTRAINERM_SEAN
	clearflag FLAG_JOHTO_BEAT_COOLTRAINERF_CAROL
	clearflag FLAG_JOHTO_BEAT_GENTLEMAN_EDWARD
	clearflag FLAG_JOHTO_BEAT_BEAUTY_CASSIE
	clearflag FLAG_JOHTO_BEAT_PSYCHIC_RODNEY
	clearflag FLAG_JOHTO_BEAT_SUPER_NERD_SHAWN
	clearflag FLAG_JOHTO_BEAT_SAILOR_GARRETT
	clearflag FLAG_JOHTO_BEAT_FISHER_JONAH
	clearflag FLAG_JOHTO_BEAT_BLACKBELT_WAI

OlivinePort_Johto_OlivinePortSailorAtGangwayScript_FirstTime:
	clearflag FLAG_JOHTO_FAST_SHIP_DESTINATION_OLIVINE
	clearflag FLAG_JOHTO_OLIVINE_PORT_SAILOR_AT_GANGWAY
	addobject 1
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 1
	warp MAP_JOHTO_FAST_SHIP_1F, 25, 1
	waitstate

OlivinePort_Johto_OlivinePortAlreadyRodeScript:
	message OlivinePort_Johto_OlivinePortCantBoardText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortWalkUpToShipScript:
	applymovement 3, Johto_Movement_Face_Right
	waitmovement 3
	goto_if_set FLAG_TEMP_11, OlivinePort_Johto_OlivinePortWalkUpToShipScript_skip
	goto_if_set FLAG_TEMP_12, OlivinePort_Johto_OlivinePortWalkUpToShipScript_skip
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_unset FLAG_JOHTO_FAST_SHIP_FIRST_TIME, OlivinePort_Johto_OlivinePortWalkUpToShipScript_FirstTime
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipMonday
	goto_if_eq VAR_RESULT, 6, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipMonday
	goto_if_eq VAR_RESULT, 2, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipFriday
	goto_if_eq VAR_RESULT, 3, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipFriday
	goto_if_eq VAR_RESULT, 4, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipFriday

OlivinePort_Johto_OlivinePortWalkUpToShipScript_FirstTime:
	message OlivinePort_Johto_OlivinePortAskBoardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortNotRidingMoveAwayScript
	message OlivinePort_Johto_OlivinePortAskTicketText
	waitmessage
	waitbuttonpress
	checkitem ITEM_SS_TICKET, 1
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortWalkUpToShipScript_NoTicket
	message OlivinePort_Johto_OlivinePortFlashTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_12
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortApproachFastShipFirstTimeMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto OlivinePort_Johto_OlivinePortSailorAtGangwayScript

OlivinePort_Johto_OlivinePortWalkUpToShipScript_NoTicket:
	message OlivinePort_Johto_OlivinePortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipMonday:
	message OlivinePort_Johto_OlivinePortMondayShipText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

OlivinePort_Johto_OlivinePortWalkUpToShipScript_NextShipFriday:
	message OlivinePort_Johto_OlivinePortFridayShipText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

OlivinePort_Johto_OlivinePortWalkUpToShipScript_skip:
	releaseall
	end

OlivinePort_Johto_OlivinePortNotRidingScript:
	message OlivinePort_Johto_OlivinePortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortNotRidingMoveAwayScript:
	message OlivinePort_Johto_OlivinePortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

OlivinePort_Johto_OlivinePortSailorAfterHOFScript:
	faceplayer
	goto_if_set FLAG_TEMP_11, OlivinePort_Johto_OlivinePortAlreadyRodeScript
	goto_if_unset FLAG_JOHTO_FAST_SHIP_FIRST_TIME, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_FirstTime
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipMonday
	goto_if_eq VAR_RESULT, 6, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipMonday
	goto_if_eq VAR_RESULT, 2, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipFriday
	goto_if_eq VAR_RESULT, 3, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipFriday
	goto_if_eq VAR_RESULT, 4, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipFriday

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_FirstTime:
	message OlivinePort_Johto_OlivinePortAskBoardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortNotRidingScript
	message OlivinePort_Johto_OlivinePortAskTicketText
	waitmessage
	waitbuttonpress
	checkitem ITEM_SS_TICKET, 1
	goto_if_eq VAR_RESULT, 0, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NoTicket
	message OlivinePort_Johto_OlivinePortFlashTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_12
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, OlivinePort_Johto_OlivinePortSailorAfterHOFScript_Right
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortApproachFastShipAfterHOFMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto OlivinePort_Johto_OlivinePortSailorAtGangwayScript

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_Right:
	applymovement OBJ_EVENT_ID_PLAYER, OlivinePort_Johto_OlivinePortApproachFastShipAfterHOFRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto OlivinePort_Johto_OlivinePortSailorAtGangwayScript

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NoTicket:
	message OlivinePort_Johto_OlivinePortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipMonday:
	message OlivinePort_Johto_OlivinePortMondayShipText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortSailorAfterHOFScript_NextShipFriday:
	message OlivinePort_Johto_OlivinePortFridayShipText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortSailorBeforeHOFScript:
	faceplayer
	message OlivinePort_Johto_OlivinePortSailorBeforeHOFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePort_Johto_OlivinePortFishingGuru1Script:
	faceplayer
	message OlivinePort_Johto_OlivinePortFishingGuru1Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	releaseall
	end

OlivinePort_Johto_OlivinePortFishingGuru2Script:
	faceplayer
	message OlivinePort_Johto_OlivinePortFishingGuru2Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Up
	waitmovement 5
	releaseall
	end

OlivinePort_Johto_OlivinePortYoungsterScript:
	faceplayer
	message OlivinePort_Johto_OlivinePortYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, Johto_Movement_Face_Down
	waitmovement 6
	releaseall
	end

OlivinePort_Johto_OlivinePortCooltrainerFScript:
	faceplayer
	message OlivinePort_Johto_OlivinePortCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, Johto_Movement_Face_Down
	waitmovement 7
	releaseall
	end

OlivinePort_Johto_OlivinePortEnterFastShipMovement:
	walk_down
	step_end

OlivinePort_Johto_OlivinePortLeaveFastShipMovement:
	walk_up
	step_end

OlivinePort_Johto_OlivinePortCannotEnterFastShipMovement:
	walk_right
	face_left
	step_end

OlivinePort_Johto_OlivinePortApproachFastShipFirstTimeMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OlivinePort_Johto_OlivinePortApproachFastShipAfterHOFMovement:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OlivinePort_Johto_OlivinePortApproachFastShipAfterHOFRightMovement:
	walk_up
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OlivinePort_Johto_OlivinePortSailorGetOnBoardText:
	.string "We're departing\n"
	.string "soon. Please get\l"
	.string "on board.$"

OlivinePort_Johto_OlivinePortCantBoardText:
	.string "Sorry. You can't\n"
	.string "board now.$"

OlivinePort_Johto_OlivinePortAskBoardText:
	.string "Welcome to FAST\n"
	.string "SHIP S.S.AQUA."
	.string "\pWill you be board-\n"
	.string "ing today?$"

OlivinePort_Johto_OlivinePortAskTicketText:
	.string "May I see your\n"
	.string "S.S.TICKET?$"

OlivinePort_Johto_OlivinePortComeAgainText:
	.string "We hope to see you\n"
	.string "again!$"

OlivinePort_Johto_OlivinePortFlashTicketText:
	.string "{PLAYER} flashed\n"
	.string "the S.S.TICKET."
	.string "\pThat's it.\n"
	.string "Thank you!$"

OlivinePort_Johto_OlivinePortNoTicketText:
	.string "{PLAYER} tried to\n"
	.string "show the S.S.\l"
	.string "TICKET…"
	.string "\p…But no TICKET!"
	.string "\pSorry!\n"
	.string "You may board only"
	.string "\pif you have an\n"
	.string "S.S.TICKET.$"

OlivinePort_Johto_OlivinePortMondayShipText:
	.string "The FAST SHIP will\n"
	.string "sail next Monday.$"

OlivinePort_Johto_OlivinePortFridayShipText:
	.string "The FAST SHIP will\n"
	.string "sail next Friday.$"

OlivinePort_Johto_OlivinePortFishingGuru1Text:
	.string "SHELLDER are easy\n"
	.string "to catch here."
	.string "\pThey're kind of\n"
	.string "rare elsewhere.$"

OlivinePort_Johto_OlivinePortFishingGuru2Text:
	.string "How many RODS do\n"
	.string "you have?"
	.string "\pDifferent RODS\n"
	.string "catch different\l"
	.string "POKéMON.$"

OlivinePort_Johto_OlivinePortYoungsterText:
	.string "S.S.AQUA uses jets\n"
	.string "to skim over the\l"
	.string "waves!$"

OlivinePort_Johto_OlivinePortCooltrainerFText:
	.string "There are lots of\n"
	.string "POKéMON in KANTO."
	.string "\pI wish I could go…$"

OlivinePort_Johto_OlivinePortSailorBeforeHOFText:
	.string "We don't want you\n"
	.string "to fall into the"
	.string "\psea, so you're not\n"
	.string "allowed in.$"
