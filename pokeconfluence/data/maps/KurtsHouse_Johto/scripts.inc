KurtsHouse_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, KurtsHouse_Johto_OnTransition
	.byte 0

KurtsHouse_Johto_OnTransition:
	call KurtsHouse_Johto_KurtsHouseKurtCallback_Cb
	end

KurtsHouse_Johto_Kurt1_Entry::
	lockall
	goto KurtsHouse_Johto_Kurt1

KurtsHouse_Johto_KurtsGranddaughter1_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsGranddaughter1

KurtsHouse_Johto_KurtsHouseSlowpoke_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsHouseSlowpoke

KurtsHouse_Johto_Kurt2_Entry::
	lockall
	goto KurtsHouse_Johto_Kurt2

KurtsHouse_Johto_KurtsGranddaughter2_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsGranddaughter2

KurtsHouse_Johto_KurtsHouseRadio_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsHouseRadio

KurtsHouse_Johto_KurtsHouseOakPhoto_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsHouseOakPhoto

KurtsHouse_Johto_KurtsHouseBookshelf_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsHouseBookshelf

KurtsHouse_Johto_KurtsHouseCelebiStatue_Entry::
	lockall
	goto KurtsHouse_Johto_KurtsHouseCelebiStatue


KurtsHouse_Johto_Kurt1:
	faceplayer
	goto_if_set FLAG_JOHTO_KURT_GAVE_YOU_LURE_BALL, KurtsHouse_Johto_Kurt1_GotLureBall
	goto_if_set FLAG_JOHTO_CLEARED_SLOWPOKE_WELL, KurtsHouse_Johto_Kurt1_ClearedSlowpokeWell
	message KurtsHouse_Johto_KurtsHouseKurtMakingBallsMustWaitText
	waitmessage
	waitbuttonpress
	closemessage
	fadeoutbgm 4
	setflag FLAG_JOHTO_AZALEA_TOWN_SLOWPOKETAIL_ROCKET
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, KurtsHouse_Johto_Kurt1_RunAround
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_FLY
	applymovement 1, KurtsHouse_Johto_KurtsHouseKurtExitHouseMovement
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	waitse
	fadedefaultbgm
	releaseall
	end

KurtsHouse_Johto_Kurt1_RunAround:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_FLY
	applymovement 1, KurtsHouse_Johto_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	waitse
	fadedefaultbgm
	releaseall
	end

KurtsHouse_Johto_Kurt1_ClearedSlowpokeWell:
	message KurtsHouse_Johto_KurtsHouseKurtHonoredToMakeBallsText
	waitmessage
	waitbuttonpress
	giveitem ITEM_LURE_BALL
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_NoRoomForBall
	setflag FLAG_JOHTO_KURT_GAVE_YOU_LURE_BALL

KurtsHouse_Johto_Kurt1_GotLureBall:
	goto_if_set FLAG_TEMP_11, KurtsHouse_Johto_Kurt1_WaitForApricorns
	goto_if_set FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS, KurtsHouse_Johto_KurtMakingBallsScript
	goto_if_set FLAG_JOHTO_GAVE_KURT_RED_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_BLU_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_YLW_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_GRN_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_WHT_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_BLK_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_GAVE_KURT_PNK_APRICORN, KurtsHouse_Johto_Kurt1_DeliverBalls
	goto_if_set FLAG_JOHTO_CAN_GIVE_GS_BALL_TO_KURT, KurtsHouse_Johto_Kurt1_CanGiveGSBallToKurt

KurtsHouse_Johto_Kurt1_NoGSBall:
	goto_if_set FLAG_TEMP_12, KurtsHouse_Johto_Kurt1_CheckApricorns
	goto_if_set FLAG_TEMP_13, KurtsHouse_Johto_Kurt1_CheckApricorns
	message KurtsHouse_Johto_KurtsHouseKurtBallsFromApricornsText
	waitmessage
	waitbuttonpress

KurtsHouse_Johto_Kurt1_CheckApricorns:
	checkitem ITEM_RED_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_BLU_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_YLW_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_GRN_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_WHT_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_BLK_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	checkitem ITEM_PNK_APRICORN, 1
	goto_if_ne VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_AskApricorn
	goto_if_set FLAG_TEMP_12, KurtsHouse_Johto_Kurt1_ThatTurnedOutGreat
	goto_if_set FLAG_TEMP_13, KurtsHouse_Johto_Kurt1_IMakeBallsFromApricorns
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1_IMakeBallsFromApricorns:
	message KurtsHouse_Johto_KurtsHouseKurtBallsFromApricornsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1_AskApricorn:
	message KurtsHouse_Johto_KurtsHouseKurtAskYouHaveAnApricornText
	waitmessage
	waitbuttonpress
	setflag FLAG_TEMP_13
	call KurtsHouse_Johto_BuildApricornMenu
	dynmultipush KurtsHouse_Johto_Text_Cancel, 0
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_Cancel
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, KurtsHouse_Johto_Kurt1_Cancel

	copyvar VAR_0x8004, VAR_RESULT
	special JohtoGetApricornQuantity
	copyvar VAR_0x8005, VAR_RESULT
	goto_if_eq VAR_0x8005, 1, KurtsHouse_Johto_Kurt1_ConfirmSingle

	@ Batch crafting prompt when player has multiple of chosen Apricorn
	buffernumberstring STR_VAR_1, VAR_0x8005
	bufferitemname STR_VAR_2, VAR_0x8004
	message KurtsHouse_Johto_Text_HowManyApricorns
	waitmessage
	dynmultipush KurtsHouse_Johto_Text_MakeOne, 1
	dynmultipush KurtsHouse_Johto_Text_MakeAll, 2
	dynmultipush KurtsHouse_Johto_Text_Cancel, 0
	dynmultistack 0, 0, FALSE, 3, FALSE, 0, NULL
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_Cancel
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, KurtsHouse_Johto_Kurt1_Cancel
	goto_if_eq VAR_RESULT, 1, KurtsHouse_Johto_Kurt1_ConfirmSingle

	@ VAR_RESULT == 2 (All): VAR_0x8005 already holds the total count
	goto KurtsHouse_Johto_Kurt1_ExecuteGive

KurtsHouse_Johto_Kurt1_ConfirmSingle:
	setvar VAR_0x8005, 1

KurtsHouse_Johto_Kurt1_ExecuteGive:
	special JohtoGiveKurtApricorns
	setflag FLAG_TEMP_11
	goto KurtsHouse_Johto_Kurt1_WaitForApricorns

KurtsHouse_Johto_BuildApricornMenu:
	checkitem ITEM_RED_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipRed
	dynmultipush KurtsHouse_Johto_Text_RedApricorn, ITEM_RED_APRICORN
KurtsHouse_Johto_SkipRed:
	checkitem ITEM_BLU_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipBlu
	dynmultipush KurtsHouse_Johto_Text_BluApricorn, ITEM_BLU_APRICORN
KurtsHouse_Johto_SkipBlu:
	checkitem ITEM_YLW_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipYlw
	dynmultipush KurtsHouse_Johto_Text_YlwApricorn, ITEM_YLW_APRICORN
KurtsHouse_Johto_SkipYlw:
	checkitem ITEM_GRN_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipGrn
	dynmultipush KurtsHouse_Johto_Text_GrnApricorn, ITEM_GRN_APRICORN
KurtsHouse_Johto_SkipGrn:
	checkitem ITEM_WHT_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipWht
	dynmultipush KurtsHouse_Johto_Text_WhtApricorn, ITEM_WHT_APRICORN
KurtsHouse_Johto_SkipWht:
	checkitem ITEM_BLK_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipBlk
	dynmultipush KurtsHouse_Johto_Text_BlkApricorn, ITEM_BLK_APRICORN
KurtsHouse_Johto_SkipBlk:
	checkitem ITEM_PNK_APRICORN, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_SkipPnk
	dynmultipush KurtsHouse_Johto_Text_PnkApricorn, ITEM_PNK_APRICORN
KurtsHouse_Johto_SkipPnk:
	return

KurtsHouse_Johto_Kurt1_DeliverBalls:
	message KurtsHouse_Johto_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	special JohtoDeliverKurtBalls
	goto_if_eq VAR_RESULT, FALSE, KurtsHouse_Johto_Kurt1_NoRoomForBall
	bufferitemname STR_VAR_1, VAR_0x8000
	buffernumberstring STR_VAR_2, VAR_0x8001
	playfanfare MUS_OBTAIN_ITEM
	message KurtsHouse_Johto_Text_ObtainedKurtBalls
	waitfanfare
	waitbuttonpress
	goto KurtsHouse_Johto_Kurt1__ThatTurnedOutGreat

KurtsHouse_Johto_Kurt1_GiveLevelBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveLureBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveMoonBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveFriendBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveFastBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveHeavyBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_GiveLoveBall:
	goto KurtsHouse_Johto_Kurt1_DeliverBalls

KurtsHouse_Johto_Kurt1_WaitForApricorns:
	message KurtsHouse_Johto_KurtsHouseKurtItWillTakeADayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1_Cancel:
	message KurtsHouse_Johto_KurtsHouseKurtThatsALetdownText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1__ThatTurnedOutGreat:
	setflag FLAG_TEMP_12

KurtsHouse_Johto_Kurt1_ThatTurnedOutGreat:
	message KurtsHouse_Johto_KurtsHouseKurtTurnedOutGreatText
	waitmessage
	waitbuttonpress

KurtsHouse_Johto_Kurt1_NoRoomForBall:
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1_CanGiveGSBallToKurt:
	goto_if_set FLAG_JOHTO_GAVE_GS_BALL_TO_KURT, KurtsHouse_Johto_Kurt1_GaveGSBallToKurt
	checkitem ITEM_GS_BALL, 1
	goto_if_eq VAR_RESULT, 0, KurtsHouse_Johto_Kurt1_NoGSBall
	message KurtsHouse_Johto_KurtsHouseKurtWhatIsThatText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_GAVE_GS_BALL_TO_KURT
	removeitem ITEM_GS_BALL
	setflag FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS
	releaseall
	end

KurtsHouse_Johto_Kurt1_GaveGSBallToKurt:
	goto_if_unset FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS, KurtsHouse_Johto_Kurt1_NotMakingBalls
	message KurtsHouse_Johto_KurtsHouseKurtImCheckingItNowText
	waitmessage
	waitbuttonpress
	message KurtsHouse_Johto_KurtsHouseKurtAhHaISeeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_Kurt1_NotMakingBalls:
	message KurtsHouse_Johto_KurtsHouseKurtThisBallStartedToShakeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_FOREST_IS_RESTLESS
	clearflag FLAG_JOHTO_CAN_GIVE_GS_BALL_TO_KURT
	clearflag FLAG_JOHTO_GAVE_GS_BALL_TO_KURT
	fadeoutbgm 4
	delay 20
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, KurtsHouse_Johto_Kurt1_GSBallRunAround
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_FLY
	applymovement 1, KurtsHouse_Johto_KurtsHouseKurtExitHouseMovement
	waitmovement 1
	goto KurtsHouse_Johto_Kurt1_KurtHasLeftTheBuilding

KurtsHouse_Johto_Kurt1_GSBallRunAround:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_FLY
	applymovement 1, KurtsHouse_Johto_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement
	waitmovement 1

KurtsHouse_Johto_Kurt1_KurtHasLeftTheBuilding:
	playse SE_EXIT
	removeobject 1
	clearflag FLAG_JOHTO_AZALEA_TOWN_KURT
	waitse
	fadedefaultbgm
	setvar VAR_JOHTO_SCENE_AZALEA_TOWN, 2
	releaseall
	end

KurtsHouse_Johto_Kurt2:
	faceplayer
	goto_if_set FLAG_JOHTO_GAVE_GS_BALL_TO_KURT, KurtsHouse_Johto_KurtScript_ImCheckingItNow

KurtsHouse_Johto_KurtMakingBallsScript:
	goto_if_unset FLAG_JOHTO_BUGGING_KURT_TOO_MUCH, KurtsHouse_Johto_Script_FirstTimeBuggingKurt
	message KurtsHouse_Johto_KurtsHouseKurtDontBotherMeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	releaseall
	end

KurtsHouse_Johto_Script_FirstTimeBuggingKurt:
	message KurtsHouse_Johto_KurtsHouseKurtGranddaughterHelpingWorkFasterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	setflag FLAG_JOHTO_BUGGING_KURT_TOO_MUCH
	releaseall
	end

KurtsHouse_Johto_KurtScript_ImCheckingItNow:
	message KurtsHouse_Johto_KurtsHouseKurtImCheckingItNowText
	waitmessage
	waitbuttonpress
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	message KurtsHouse_Johto_KurtsHouseKurtAhHaISeeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter1:
	faceplayer
	goto_if_set FLAG_TEMP_11, KurtsHouse_Johto_KurtsGranddaughter2Subscript
	goto_if_set FLAG_TEMP_12, KurtsHouse_Johto_KurtsGranddaughterFunScript
	goto_if_set FLAG_JOHTO_FOREST_IS_RESTLESS, KurtsHouse_Johto_KurtsGranddaughter1_Lonely
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, KurtsHouse_Johto_KurtsGranddaughter1_Dad
	goto_if_set FLAG_JOHTO_CLEARED_SLOWPOKE_WELL, KurtsHouse_Johto_KurtsGranddaughter1_SlowpokeBack
	goto_if_set FLAG_JOHTO_AZALEA_TOWN_SLOWPOKETAIL_ROCKET, KurtsHouse_Johto_KurtsGranddaughter1_Lonely
	message KurtsHouse_Johto_KurtsGranddaughterSlowpokeGoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter1_SlowpokeBack:
	message KurtsHouse_Johto_KurtsGranddaughterSlowpokeBackText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter1_Lonely:
	message KurtsHouse_Johto_KurtsGranddaughterLonelyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter1_Dad:
	message KurtsHouse_Johto_KurtsGranddaughterDadText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter2:
	faceplayer

KurtsHouse_Johto_KurtsGranddaughter2Subscript:
	goto_if_set FLAG_JOHTO_GAVE_GS_BALL_TO_KURT, KurtsHouse_Johto_KurtsGranddaughter2Subscript_GSBall
	message KurtsHouse_Johto_KurtsGranddaughterHelpText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughter2Subscript_GSBall:
	message KurtsHouse_Johto_KurtsGranddaughterGSBallText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	releaseall
	end

KurtsHouse_Johto_KurtsGranddaughterFunScript:
	message KurtsHouse_Johto_KurtsGranddaughterFunText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsHouseSlowpoke:
	faceplayer
	message KurtsHouse_Johto_KurtsHouseSlowpokeText
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsHouseOakPhoto:
	message KurtsHouse_Johto_KurtsHouseOakPhotoText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsHouseCelebiStatue:
	message KurtsHouse_Johto_KurtsHouseCelebiStatueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

KurtsHouse_Johto_KurtsHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

KurtsHouse_Johto_KurtsHouseRadio:
	goto Johto_Std_Radio2Script

KurtsHouse_Johto_KurtsHouseKurtCallback_Cb:
	goto_if_unset FLAG_JOHTO_CLEARED_SLOWPOKE_WELL, KurtsHouse_Johto_KurtsHouseKurtCallback_Done_Cb
	goto_if_set FLAG_JOHTO_FOREST_IS_RESTLESS, KurtsHouse_Johto_KurtsHouseKurtCallback_Done_Cb
	goto_if_set FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS, KurtsHouse_Johto_KurtsHouseKurtCallback_MakingBalls_Cb
	setflag FLAG_JOHTO_KURTS_HOUSE_KURT_2
	clearflag FLAG_JOHTO_KURTS_HOUSE_KURT_1
	setflag FLAG_JOHTO_KURTS_HOUSE_GRANDDAUGHTER_2
	clearflag FLAG_JOHTO_KURTS_HOUSE_GRANDDAUGHTER_1
	return

KurtsHouse_Johto_KurtsHouseKurtCallback_MakingBalls_Cb:
	setflag FLAG_JOHTO_KURTS_HOUSE_KURT_1
	clearflag FLAG_JOHTO_KURTS_HOUSE_KURT_2
	setflag FLAG_JOHTO_KURTS_HOUSE_GRANDDAUGHTER_1
	clearflag FLAG_JOHTO_KURTS_HOUSE_GRANDDAUGHTER_2

KurtsHouse_Johto_KurtsHouseKurtCallback_Done_Cb:
	return

KurtsHouse_Johto_KurtsHouseKurtExitHouseMovement:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Johto_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Johto_KurtsHouseKurtMakingBallsMustWaitText:
	.string "Hm? Who are you?"
	.string "\p{PLAYER}, eh? You\n"
	.string "want me to make\l"
	.string "some BALLS?"
	.string "\pSorry, but that'll\n"
	.string "have to wait."
	.string "\pDo you know TEAM\n"
	.string "ROCKET? Ah, don't"
	.string "\pworry. I'll tell\n"
	.string "you anyhow."
	.string "\pTEAM ROCKET's an\n"
	.string "evil gang that"
	.string "\puses POKéMON for\n"
	.string "their dirty work."
	.string "\pThey're supposed\n"
	.string "to have disbanded\l"
	.string "three years ago."
	.string "\pAnyway, they're at\n"
	.string "the WELL, cutting"
	.string "\poff SLOWPOKETAILS\n"
	.string "for sale!"
	.string "\pSo I'm going to\n"
	.string "go give them a\l"
	.string "lesson in pain!"
	.string "\pHang on, SLOWPOKE!\n"
	.string "Old KURT is on his\l"
	.string "way!$"

KurtsHouse_Johto_KurtsHouseKurtHonoredToMakeBallsText:
	.string "KURT: Hi, {PLAYER}!"
	.string "\pYou handled your-\n"
	.string "self like a real\l"
	.string "hero at the WELL."
	.string "\pI like your style!"
	.string "\pI would be honored\n"
	.string "to make BALLS for"
	.string "\pa trainer like\n"
	.string "you."
	.string "\pThis is all I have\n"
	.string "now, but take it.$"

KurtsHouse_Johto_KurtsHouseKurtBallsFromApricornsText:
	.string "KURT: I make BALLS\n"
	.string "from APRICORNS."
	.string "\pCollect them from\n"
	.string "trees and bring\l"
	.string "'em to me."
	.string "\pI'll make BALLS\n"
	.string "out of them.$"

KurtsHouse_Johto_KurtsHouseKurtAskYouHaveAnApricornText:
	.string "KURT: You have an\n"
	.string "APRICORN for me?"
	.string "\pFine! I'll turn it\n"
	.string "into a BALL.$"

KurtsHouse_Johto_KurtsHouseKurtItWillTakeADayText:
	.string "KURT: It'll take a\n"
	.string "day to make you a"
	.string "\pBALL. Come back\n"
	.string "for it later.$"

KurtsHouse_Johto_KurtsHouseKurtThatsALetdownText:
	.string "KURT: Oh…\n"
	.string "That's a letdown.$"

KurtsHouse_Johto_KurtsHouseKurtDontBotherMeText:
	.string "KURT: I'm working!\n"
	.string "Don't bother me!$"

KurtsHouse_Johto_KurtsHouseKurtJustFinishedYourBallText:
	.string "KURT: Ah, {PLAYER}!\n"
	.string "I just finished\l"
	.string "your BALL. Here!$"

KurtsHouse_Johto_KurtsHouseKurtTurnedOutGreatText:
	.string "KURT: That turned\n"
	.string "out great."
	.string "\pTry catching\n"
	.string "POKéMON with it.$"

KurtsHouse_Johto_KurtsHouseKurtGranddaughterHelpingWorkFasterText:
	.string "KURT: Now that my\n"
	.string "granddaughter is"
	.string "\phelping me, I can\n"
	.string "work much faster.$"

KurtsHouse_Johto_KurtsHouseKurtWhatIsThatText:
	.string "Wh-what is that?"
	.string "\pI've never seen\n"
	.string "one before."
	.string "\pIt looks a lot\n"
	.string "like a POKé BALL,"
	.string "\pbut it appears to\n"
	.string "be something else."
	.string "\pLet me check it\n"
	.string "for you.$"

KurtsHouse_Johto_KurtsHouseKurtImCheckingItNowText:
	.string "I'm checking it\n"
	.string "now.$"

KurtsHouse_Johto_KurtsHouseKurtAhHaISeeText:
	.string "Ah-ha! I see!\n"
	.string "So…$"

KurtsHouse_Johto_KurtsHouseKurtThisBallStartedToShakeText:
	.string "{PLAYER}!"
	.string "\pThis BALL started\n"
	.string "to shake while I\l"
	.string "was checking it."
	.string "\pThere must be\n"
	.string "something to this!$"

KurtsHouse_Johto_KurtsGranddaughterSlowpokeGoneText:
	.string "The SLOWPOKE are\n"
	.string "gone… Were they"
	.string "\ptaken away by bad\n"
	.string "people?$"

KurtsHouse_Johto_KurtsGranddaughterLonelyText:
	.string "Grandpa's gone…\n"
	.string "I'm so lonely…$"

KurtsHouse_Johto_KurtsGranddaughterSlowpokeBackText:
	.string "The SLOWPOKE my\n"
	.string "dad gave me came"
	.string "\pback! Its TAIL is\n"
	.string "growing back too!$"

KurtsHouse_Johto_KurtsGranddaughterDadText:
	.string "Dad works at SILPH\n"
	.string "where he studies\l"
	.string "POKé BALLS."
	.string "\pI have to stay\n"
	.string "home with Grandpa\l"
	.string "and SLOWPOKE.$"

KurtsHouse_Johto_KurtsGranddaughterHelpText:
	.string "I get to help\n"
	.string "Grandpa now!"
	.string "\pWe'll make good\n"
	.string "BALLS for you, so\l"
	.string "please wait!$"

KurtsHouse_Johto_KurtsGranddaughterFunText:
	.string "It's fun to make\n"
	.string "BALLS!$"

KurtsHouse_Johto_KurtsGranddaughterGSBallText:
	.string "Grandpa's checking\n"
	.string "a BALL right now."
	.string "\pSo I'm waiting\n"
	.string "till he's done.$"

KurtsHouse_Johto_KurtsHouseSlowpokeText:
	.string "SLOWPOKE: …\n"
	.string "Yawn?$"

KurtsHouse_Johto_KurtsHouseOakPhotoText:
	.string "…A young PROF.\n"
	.string "OAK?$"

KurtsHouse_Johto_KurtsHouseCelebiStatueText:
	.string "It's a statue of\n"
	.string "the forest's pro-\l"
	.string "tector.$"

KurtsHouse_Johto_Text_RedApricorn:
	.string "Red Apricorn (Level Ball)$"

KurtsHouse_Johto_Text_BluApricorn:
	.string "Blu Apricorn (Lure Ball)$"

KurtsHouse_Johto_Text_YlwApricorn:
	.string "Ylw Apricorn (Moon Ball)$"

KurtsHouse_Johto_Text_GrnApricorn:
	.string "Grn Apricorn (Friend Ball)$"

KurtsHouse_Johto_Text_WhtApricorn:
	.string "Wht Apricorn (Fast Ball)$"

KurtsHouse_Johto_Text_BlkApricorn:
	.string "Blk Apricorn (Heavy Ball)$"

KurtsHouse_Johto_Text_PnkApricorn:
	.string "Pnk Apricorn (Love Ball)$"

KurtsHouse_Johto_Text_Cancel:
	.string "Cancel$"

KurtsHouse_Johto_Text_HowManyApricorns:
	.string "You have {STR_VAR_1} {STR_VAR_2}s.\nHow many should I turn into Balls?$"

KurtsHouse_Johto_Text_MakeOne:
	.string "Just 1 Ball$"

KurtsHouse_Johto_Text_MakeAll:
	.string "All {STR_VAR_1} of them$"

KurtsHouse_Johto_Text_ObtainedKurtBalls:
	.string "{PLAYER} received {STR_VAR_2}\n{STR_VAR_1}(s) from Kurt!$"

