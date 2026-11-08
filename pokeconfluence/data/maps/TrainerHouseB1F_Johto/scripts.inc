TrainerHouseB1F_Johto_MapScripts::
	.byte 0

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_Entry::
	lockall
	goto TrainerHouseB1F_Johto_TrainerHouseReceptionistScript


TrainerHouseB1F_Johto_TrainerHouseReceptionistScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_set FLAG_JOHTO_ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_FoughtTooManyTimes
	message TrainerHouseB1F_Johto_TrainerHouseB1FIntroText
	waitmessage
	waitbuttonpress
	special JohtoTrainerHouseGetOpponent
	goto_if_eq VAR_RESULT, 0, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GetCal1Name
	goto_if_eq VAR_RESULT, 1, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GetCal2Name
	buffertrainername STR_VAR_1, TRAINER_JOHTO_CAL_CAL3
	goto TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GotName

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GetCal1Name:
	buffertrainername STR_VAR_1, TRAINER_JOHTO_CAL_CAL1
	goto TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GotName

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GetCal2Name:
	buffertrainername STR_VAR_1, TRAINER_JOHTO_CAL_CAL2

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_GotName:
	message TrainerHouseB1F_Johto_TrainerHouseB1FYourOpponentIsText
	waitmessage
	waitbuttonpress
	message TrainerHouseB1F_Johto_TrainerHouseB1FAskWantToBattleText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_Declined
	message TrainerHouseB1F_Johto_TrainerHouseB1FGoRightInText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHouseB1F_Johto_Movement_EnterTrainerHouseBattleRoom
	waitmovement OBJ_EVENT_ID_PLAYER
	message TrainerHouseB1F_Johto_TrainerHouseB1FCalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	special JohtoTrainerHouseGetOpponent
	goto_if_eq VAR_RESULT, 0, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_BattleCal1
	goto_if_eq VAR_RESULT, 1, TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_BattleCal2
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_JOHTO_CAL_CAL3, TrainerHouseB1F_Johto_TrainerHouseB1FCalBeatenText
	goto TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_End

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_BattleCal1:
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_JOHTO_CAL_CAL1, TrainerHouseB1F_Johto_TrainerHouseB1FCalBeatenText
	goto TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_End

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_BattleCal2:
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_JOHTO_CAL_CAL2, TrainerHouseB1F_Johto_TrainerHouseB1FCalBeatenText

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_End:
	setflag FLAG_JOHTO_ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHouseB1F_Johto_Movement_ExitTrainerHouseBattleRoom
	waitmovement OBJ_EVENT_ID_PLAYER
	message TrainerHouseB1F_Johto_TrainerHouseB1FVictoryRewardText
	waitmessage
	waitbuttonpress
	giveitem ITEM_PP_UP
	closemessage
	releaseall
	end

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_Declined:
	message TrainerHouseB1F_Johto_TrainerHouseB1FPleaseComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHouseB1F_Johto_Movement_TrainerHouseTurnBack
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_FoughtTooManyTimes:
	message TrainerHouseB1F_Johto_TrainerHouseB1FSecondChallengeDeniedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHouseB1F_Johto_Movement_TrainerHouseTurnBack
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

TrainerHouseB1F_Johto_Movement_EnterTrainerHouseBattleRoom:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	face_right
	step_end

TrainerHouseB1F_Johto_Movement_ExitTrainerHouseBattleRoom:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TrainerHouseB1F_Johto_Movement_TrainerHouseTurnBack:
	walk_right
	face_left
	step_end

TrainerHouseB1F_Johto_TrainerHouseB1FIntroText:
	.string "Hi. Welcome to our\n"
	.string "TRAINING HALL."
	.string "\pYou may battle a\n"
	.string "trainer once per\l"
	.string "day.$"

TrainerHouseB1F_Johto_TrainerHouseB1FYourOpponentIsText:
	.string "{STR_VAR_1} is your\n"
	.string "opponent today.$"

TrainerHouseB1F_Johto_TrainerHouseB1FAskWantToBattleText:
	.string "Would you like to\n"
	.string "battle?$"

TrainerHouseB1F_Johto_TrainerHouseB1FGoRightInText:
	.string "Please go right\n"
	.string "through."
	.string "\pYou may begin\n"
	.string "right away.$"

TrainerHouseB1F_Johto_TrainerHouseB1FPleaseComeAgainText:
	.string "Sorry. Only those\n"
	.string "trainers who will"
	.string "\pbe battling are\n"
	.string "allowed to go in.$"

TrainerHouseB1F_Johto_TrainerHouseB1FSecondChallengeDeniedText:
	.string "I'm sorry.\n"
	.string "This would be your"
	.string "\psecond time today.\n"
	.string "You're permitted"
	.string "\pto enter just once\n"
	.string "a day.$"

TrainerHouseB1F_Johto_TrainerHouseB1FCalBeatenText:
	.string "I lost…\n"
	.string "Darn…$"

TrainerHouseB1F_Johto_TrainerHouseB1FCalBeforeText:
	.string "I traveled out\n"
	.string "here just so I\l"
	.string "could battle you.$"

TrainerHouseB1F_Johto_TrainerHouseB1FVictoryRewardText:
	.string "Splendid battle!\pPlease take this reward for\nyour victory in today's challenge!$"
