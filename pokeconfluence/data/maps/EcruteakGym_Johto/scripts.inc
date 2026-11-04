EcruteakGym_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EcruteakGym_Johto_OnFrame
	.byte 0

EcruteakGym_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ECRUTEAK_GYM, 0, EcruteakGym_Johto_EcruteakGymClosed_Entry
	.2byte 0

EcruteakGym_Johto_EcruteakGymMortyScript_Entry::
	lockall
	goto EcruteakGym_Johto_EcruteakGymMortyScript

EcruteakGym_Johto_EcruteakGymGuideScript_Entry::
	lockall
	goto EcruteakGym_Johto_EcruteakGymGuideScript

EcruteakGym_Johto_EcruteakGymStatue_Entry::
	lockall
	goto EcruteakGym_Johto_EcruteakGymStatue

EcruteakGym_Johto_EcruteakGymClosed_Entry::
	lockall
	goto EcruteakGym_Johto_EcruteakGymClosed


EcruteakGym_Johto_EcruteakGymMortyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_MORTY, EcruteakGym_Johto_EcruteakGymMortyScript_FightDone
	message EcruteakGym_Johto_MortyIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_MORTY_MORTY1, EcruteakGym_Johto_MortyWinLossText
	setflag FLAG_JOHTO_BEAT_MORTY
	message EcruteakGym_Johto_Text_ReceivedFogBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_FOGBADGE
	special JohtoCountBadges
	call EcruteakGym_Johto_EcruteakGymActivateRockets_Sub
	setvar VAR_JOHTO_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 1
	setflag FLAG_JOHTO_RANG_CLEAR_BELL_1
	setflag FLAG_JOHTO_RANG_CLEAR_BELL_2

EcruteakGym_Johto_EcruteakGymMortyScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM30_SHADOW_BALL, EcruteakGym_Johto_EcruteakGymMortyScript_GotShadowBall
	setflag FLAG_JOHTO_BEAT_SAGE_JEFFREY
	setflag FLAG_JOHTO_BEAT_SAGE_PING
	setflag FLAG_JOHTO_BEAT_MEDIUM_MARTHA
	setflag FLAG_JOHTO_BEAT_MEDIUM_GRACE
	message EcruteakGym_Johto_MortyText_FogBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_SHADOW_BALL
	goto_if_eq VAR_RESULT, 0, EcruteakGym_Johto_EcruteakGymMortyScript_NoRoomForShadowBall
	setflag FLAG_JOHTO_GOT_TM30_SHADOW_BALL
	message EcruteakGym_Johto_MortyText_ShadowBallSpeech
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_EcruteakGymMortyScript_GotShadowBall:
	message EcruteakGym_Johto_MortyFightDoneText
	waitmessage
	waitbuttonpress

EcruteakGym_Johto_EcruteakGymMortyScript_NoRoomForShadowBall:
	closemessage
	releaseall
	end

EcruteakGym_Johto_EcruteakGymClosed:
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakGym_Johto_EcruteakGymPlayerStepUpMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 7, EcruteakGym_Johto_EcruteakGymGrampsSlowStepDownMovement
	waitmovement 7
	message EcruteakGym_Johto_EcruteakGymClosedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, EcruteakGym_Johto_EcruteakGymPlayerSlowStepDownMovement
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakGym_Johto_EcruteakGymPlayerSlowStepDownMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	fadescreen FADE_TO_WHITE
	playse SE_DOOR
	waitse
	warp MAP_JOHTO_ECRUTEAK_CITY, 6, 27
	waitstate

EcruteakGym_Johto_TrainerSageJeffrey::
	trainerbattle_single TRAINER_JOHTO_SAGE_JEFFREY, EcruteakGym_Johto_SageJeffreySeenText, EcruteakGym_Johto_SageJeffreyBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_JEFFREY
	lock
	faceplayer
	goto EcruteakGym_Johto_TrainerSageJeffrey_Script

EcruteakGym_Johto_TrainerSageJeffrey_Script:
	message EcruteakGym_Johto_SageJeffreyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_TrainerSagePing::
	trainerbattle_single TRAINER_JOHTO_SAGE_PING, EcruteakGym_Johto_SagePingSeenText, EcruteakGym_Johto_SagePingBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_PING
	lock
	faceplayer
	goto EcruteakGym_Johto_TrainerSagePing_Script

EcruteakGym_Johto_TrainerSagePing_Script:
	message EcruteakGym_Johto_SagePingAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_TrainerMediumMartha::
	trainerbattle_single TRAINER_JOHTO_MEDIUM_MARTHA, EcruteakGym_Johto_MediumMarthaSeenText, EcruteakGym_Johto_MediumMarthaBeatenText
	setflag FLAG_JOHTO_BEAT_MEDIUM_MARTHA
	lock
	faceplayer
	goto EcruteakGym_Johto_TrainerMediumMartha_Script

EcruteakGym_Johto_TrainerMediumMartha_Script:
	message EcruteakGym_Johto_MediumMarthaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_TrainerMediumGrace::
	trainerbattle_single TRAINER_JOHTO_MEDIUM_GRACE, EcruteakGym_Johto_MediumGraceSeenText, EcruteakGym_Johto_MediumGraceBeatenText
	setflag FLAG_JOHTO_BEAT_MEDIUM_GRACE
	lock
	faceplayer
	goto EcruteakGym_Johto_TrainerMediumGrace_Script

EcruteakGym_Johto_TrainerMediumGrace_Script:
	message EcruteakGym_Johto_MediumGraceAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_EcruteakGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_MORTY, EcruteakGym_Johto_EcruteakGymGuideScript_EcruteakGymGuideWinScript
	message EcruteakGym_Johto_EcruteakGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_EcruteakGymGuideScript_EcruteakGymGuideWinScript:
	message EcruteakGym_Johto_EcruteakGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakGym_Johto_EcruteakGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_FOGBADGE, EcruteakGym_Johto_EcruteakGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

EcruteakGym_Johto_EcruteakGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

EcruteakGym_Johto_EcruteakGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, EcruteakGym_Johto_EcruteakGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, EcruteakGym_Johto_EcruteakGymActivateRockets_GoldenrodRockets_Sub
	return

EcruteakGym_Johto_EcruteakGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

EcruteakGym_Johto_EcruteakGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

EcruteakGym_Johto_EcruteakGymPlayerStepUpMovement:
	walk_up
	step_end

EcruteakGym_Johto_EcruteakGymPlayerSlowStepDownMovement:
	lock_facing_direction
	walk_slow_down
	unlock_facing_direction
	step_end

EcruteakGym_Johto_EcruteakGymGrampsSlowStepDownMovement:
	walk_slow_down
	step_end

EcruteakGym_Johto_MortyIntroText:
	.string "Good of you to\n"
	.string "have come."
	.string "\pHere in ECRUTEAK,\n"
	.string "POKéMON have been\l"
	.string "revered."
	.string "\pIt's said that a\n"
	.string "rainbow-colored"
	.string "\pPOKéMON will come\n"
	.string "down to appear"
	.string "\pbefore a truly\n"
	.string "powerful trainer."
	.string "\pI believed that\n"
	.string "tale, so I have"
	.string "\psecretly trained\n"
	.string "here all my life."
	.string "\pAs a result, I can\n"
	.string "now see what\l"
	.string "others cannot."
	.string "\pJust a bit more…"
	.string "\pWith a little\n"
	.string "more, I could see"
	.string "\pa future in which\n"
	.string "I meet the POKéMON\l"
	.string "of rainbow colors."
	.string "\pYou're going to\n"
	.string "help me reach that\l"
	.string "level!$"

EcruteakGym_Johto_MortyWinLossText:
	.string "I'm not good\n"
	.string "enough yet…"
	.string "\pAll right. This\n"
	.string "BADGE is yours.$"

EcruteakGym_Johto_Text_ReceivedFogBadge:
	.string "{PLAYER} received\n"
	.string "FOGBADGE.$"

EcruteakGym_Johto_MortyText_FogBadgeSpeech:
	.string "By having FOG-\n"
	.string "BADGE, POKéMON up"
	.string "\pto L50 will obey\n"
	.string "you."
	.string "\pAlso, POKéMON that\n"
	.string "know SURF will be"
	.string "\pable to use that\n"
	.string "move anytime."
	.string "\pI want you to have\n"
	.string "this too.$"

EcruteakGym_Johto_MortyText_ShadowBallSpeech:
	.string "It's SHADOW BALL.\n"
	.string "It causes damage"
	.string "\pand may reduce\n"
	.string "SPCL.DEF."
	.string "\pUse it if it\n"
	.string "appeals to you.$"

EcruteakGym_Johto_MortyFightDoneText:
	.string "I see…"
	.string "\pYour journey has\n"
	.string "taken you to far-\l"
	.string "away places."
	.string "\pAnd you have wit-\n"
	.string "nessed much more\l"
	.string "than I."
	.string "\pI envy you for\n"
	.string "that…$"

EcruteakGym_Johto_SageJeffreySeenText:
	.string "I spent the spring\n"
	.string "with my POKéMON."
	.string "\pThen summer, fall\n"
	.string "and winter…"
	.string "\pThen spring came\n"
	.string "again. We have"
	.string "\plived together\n"
	.string "for a long time.$"

EcruteakGym_Johto_SageJeffreyBeatenText:
	.string "Wins and losses, I\n"
	.string "experienced both.$"

EcruteakGym_Johto_SageJeffreyAfterBattleText:
	.string "Where did POKéMON\n"
	.string "come from?$"

EcruteakGym_Johto_SagePingSeenText:
	.string "Can you inflict\n"
	.string "any damage on our\l"
	.string "POKéMON?$"

EcruteakGym_Johto_SagePingBeatenText:
	.string "Ah! Well done!$"

EcruteakGym_Johto_SagePingAfterBattleText:
	.string "We use only ghost-\n"
	.string "type POKéMON."
	.string "\pNo normal-type\n"
	.string "attack can harm\l"
	.string "them!$"

EcruteakGym_Johto_MediumMarthaSeenText:
	.string "I shall win!$"

EcruteakGym_Johto_MediumMarthaBeatenText:
	.string "I, I, I lost!$"

EcruteakGym_Johto_MediumMarthaAfterBattleText:
	.string "The one who wants\n"
	.string "to win most--will!$"

EcruteakGym_Johto_MediumGraceSeenText:
	.string "Stumped by our in-\n"
	.string "visible floor?"
	.string "\pDefeat me if you\n"
	.string "want a hint!$"

EcruteakGym_Johto_MediumGraceBeatenText:
	.string "Wha-what?$"

EcruteakGym_Johto_MediumGraceAfterBattleText:
	.string "Fine. I shall tell\n"
	.string "you the secret of"
	.string "\pthe invisible\n"
	.string "floor."
	.string "\pThe path is right\n"
	.string "before our eyes!$"

EcruteakGym_Johto_EcruteakGymGuideText:
	.string "The trainers here\n"
	.string "have secret mo-\l"
	.string "tives."
	.string "\pIf you win, they\n"
	.string "may tell you some"
	.string "\pdeep secrets about\n"
	.string "ECRUTEAK.$"

EcruteakGym_Johto_EcruteakGymGuideWinText:
	.string "Whew, {PLAYER}.\n"
	.string "You did great!"
	.string "\pI was cowering in\n"
	.string "the corner out of\l"
	.string "pure terror!$"

EcruteakGym_Johto_EcruteakGymClosedText:
	.string "MORTY, the GYM\n"
	.string "LEADER, is absent."
	.string "\pSorry, but you'll\n"
	.string "have to leave."
	.string "\pHohohoho.$"
