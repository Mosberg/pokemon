SaffronMagnetTrainStation_Johto_MapScripts::
	.byte 0

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_Entry::
	lockall
	goto SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideScript_Entry::
	lockall
	goto SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideScript

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationTeacherScript_Entry::
	lockall
	goto SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationTeacherScript

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationLassScript_Entry::
	lockall
	goto SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationLassScript

SaffronMagnetTrainStation_Johto_Script_ArriveFromGoldenrod_Entry::
	lockall
	goto SaffronMagnetTrainStation_Johto_Script_ArriveFromGoldenrod


SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_MagnetTrainToGoldenrod
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerTrainIsntOperatingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_MagnetTrainToGoldenrod:
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerAreYouComingOnBoardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_DecidedNotToRide
	checkitem ITEM_PASS, 1
	goto_if_eq VAR_RESULT, 0, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_PassNotInBag
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerRightThisWayText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationPlayerApproachAndEnterTrainMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_RESULT, TRUE
	@ TODO unsupported: special MagnetTrain
	goto Johto_EventScript_Unimplemented

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_PassNotInBag:
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerYouDontHaveAPassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerScript_DecidedNotToRide:
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerHopeToSeeYouAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_Script_ArriveFromGoldenrod:
	applymovement 1, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerReturnToBoardingGateMovement
	waitmovement 1
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerArrivedInSaffronText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideScript_ReturnedMachinePart
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideScript_ReturnedMachinePart:
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationTeacherScript:
	faceplayer
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationLassScript:
	faceplayer
	message SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerApproachTrainDoorMovement:
	walk_up
	walk_up
	walk_right
	face_left
	step_end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerReturnToBoardingGateMovement:
	walk_left
	walk_down
	walk_down
	step_end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationPlayerApproachAndEnterTrainMovement:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_up
	step_end

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerTrainIsntOperatingText:
	.string "I'm sorry, but the\n"
	.string "MAGNET TRAIN isn't\l"
	.string "operating now.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerAreYouComingOnBoardText:
	.string "We'll soon depart\n"
	.string "for GOLDENROD."
	.string "\pAre you coming on\n"
	.string "board?$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerRightThisWayText:
	.string "May I see your\n"
	.string "rail PASS, please?"
	.string "\pOK. Right this\n"
	.string "way, please.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerYouDontHaveAPassText:
	.string "Sorry, but you\n"
	.string "don't have a PASS.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerHopeToSeeYouAgainText:
	.string "We hope to see you\n"
	.string "again.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationOfficerArrivedInSaffronText:
	.string "We have arrived in\n"
	.string "SAFFRON."
	.string "\pWe hope to see you\n"
	.string "again.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideText:
	.string "The MAGNET TRAIN\n"
	.string "is a super-modern"
	.string "\prail liner that\n"
	.string "uses electricity"
	.string "\pand magnets to\n"
	.string "attain incredible\l"
	.string "speed."
	.string "\pHowever, if there\n"
	.string "isn't any elec-\l"
	.string "tricity…$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationGymGuideText_ReturnedMachinePart:
	.string "Whew…"
	.string "\pHow many times\n"
	.string "have I gone back"
	.string "\pand forth between\n"
	.string "KANTO and JOHTO?$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationTeacherText:
	.string "Before the MAGNET\n"
	.string "TRAIN STATION was"
	.string "\pbuilt, there was a\n"
	.string "house there."
	.string "\pA little girl\n"
	.string "named COPYCAT used\l"
	.string "to live there.$"

SaffronMagnetTrainStation_Johto_SaffronMagnetTrainStationLassText:
	.string "Hi. Do you have a\n"
	.string "rail PASS? I have"
	.string "\pone. All the peo-\n"
	.string "ple in SAFFRON who"
	.string "\pride the MAGNET\n"
	.string "TRAIN have PASSES.$"
