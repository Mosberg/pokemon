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
	@ TODO unsupported: special TrainerHouse
	goto Johto_EventScript_Unimplemented

TrainerHouseB1F_Johto_TrainerHouseReceptionistScript_FoughtTooManyTimes:
	message TrainerHouseB1F_Johto_TrainerHouseB1FSecondChallengeDeniedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHouseB1F_Johto_Movement_TrainerHouseTurnBack
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

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

TrainerHouseB1F_Johto_TrainerHouseB1FSecondChallengeDeniedText:
	.string "I'm sorry.\n"
	.string "This would be your"
	.string "\psecond time today.\n"
	.string "You're permitted"
	.string "\pto enter just once\n"
	.string "a day.$"
