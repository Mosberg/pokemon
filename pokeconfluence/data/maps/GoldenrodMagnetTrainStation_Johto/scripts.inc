GoldenrodMagnetTrainStation_Johto_MapScripts::
	.byte 0

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_Entry::
	lockall
	goto GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationGentlemanScript_Entry::
	lockall
	goto GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationGentlemanScript

GoldenrodMagnetTrainStation_Johto_Script_ArriveFromSaffron_Entry::
	lockall
	goto GoldenrodMagnetTrainStation_Johto_Script_ArriveFromSaffron


GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_MagnetTrainToSaffron
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_MagnetTrainToSaffron:
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerAreYouComingAboardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_DecidedNotToRide
	checkitem ITEM_PASS, 1
	goto_if_eq VAR_RESULT, 0, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_PassNotInBag
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerRightThisWayText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_RESULT, FALSE
	warp MAP_JOHTO_SAFFRON_MAGNET_TRAIN_STATION, 11, 5
	waitstate
	applymovement OBJ_EVENT_ID_PLAYER, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_MovementBoardTheTrain
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_PassNotInBag:
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_DecidedNotToRide:
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_Script_ArriveFromSaffron:
	applymovement 1, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement
	waitmovement 1
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationGentlemanScript:
	faceplayer
	message GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerScript_MovementBoardTheTrain:
	face_down
	step_end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement:
	walk_up
	walk_up
	walk_right
	face_left
	step_end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement:
	walk_left
	walk_down
	walk_down
	step_end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_up
	step_end

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText:
	.string "The train hasn't\n"
	.string "come in…"
	.string "\pI know! I'll carry\n"
	.string "the passengers on\l"
	.string "my back!"
	.string "\pThat won't work.$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerAreYouComingAboardText:
	.string "We'll soon depart\n"
	.string "for SAFFRON."
	.string "\pAre you coming\n"
	.string "aboard?$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerRightThisWayText:
	.string "May I see your\n"
	.string "rail PASS, please?"
	.string "\pOK. Right this\n"
	.string "way, please.$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText:
	.string "Sorry. You don't\n"
	.string "have a rail PASS.$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText:
	.string "We hope to see you\n"
	.string "again!$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText:
	.string "We have arrived in\n"
	.string "GOLDENROD."
	.string "\pWe hope to see you\n"
	.string "again.$"

GoldenrodMagnetTrainStation_Johto_GoldenrodMagnetTrainStationGentlemanText:
	.string "I'm the PRESIDENT."
	.string "\pMy dream was to\n"
	.string "build a train that"
	.string "\pis faster than any\n"
	.string "POKéMON."
	.string "\pIt really brings\n"
	.string "JOHTO much closer\l"
	.string "to KANTO.$"
