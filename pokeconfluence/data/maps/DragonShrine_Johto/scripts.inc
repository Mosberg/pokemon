DragonShrine_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonShrine_Johto_OnFrame
	.byte 0

DragonShrine_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_DRAGON_SHRINE, 0, DragonShrine_Johto_DragonShrineTakeTestScript_Entry
	.2byte 0

DragonShrine_Johto_DragonShrineElder1Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder1Script

DragonShrine_Johto_DragonShrineElder2Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder2Script

DragonShrine_Johto_DragonShrineElder3Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder3Script

DragonShrine_Johto_DragonShrineTakeTestScript_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineTakeTestScript


DragonShrine_Johto_DragonShrineTakeTestScript:
	applymovement OBJ_EVENT_ID_PLAYER, DragonShrine_Johto_DragonShrinePlayerWalkInMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, DragonShrine_Johto_DragonShrineElderStepDownMovement
	waitmovement 1
	message DragonShrine_Johto_DragonShrineElderGreetingText
	waitmessage
	waitbuttonpress

DragonShrine_Johto_DragonShrineTakeTestScript_Question1:
	setflag FLAG_TEMP_12
	message DragonShrine_Johto_DragonShrineQuestion1Text
	waitmessage
	waitbuttonpress
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion1_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion1_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion1_MenuHeader_Opt3, 3
	dynmultistack 0, 0, TRUE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 3, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	releaseall
	end

DragonShrine_Johto_DragonShrineTakeTestScript_Question2:
	setflag FLAG_TEMP_13
	message DragonShrine_Johto_DragonShrineQuestion2Text
	waitmessage
	waitbuttonpress
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion2_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion2_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion2_MenuHeader_Opt3, 3
	dynmultistack 0, 0, TRUE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer

DragonShrine_Johto_DragonShrineTakeTestScript_Question3:
	setflag FLAG_TEMP_14
	message DragonShrine_Johto_DragonShrineQuestion3Text
	waitmessage
	waitbuttonpress
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion3_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion3_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion3_MenuHeader_Opt3, 3
	dynmultistack 0, 0, TRUE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 2, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer

DragonShrine_Johto_DragonShrineTakeTestScript_Question4:
	setflag FLAG_TEMP_15
	message DragonShrine_Johto_DragonShrineQuestion4Text
	waitmessage
	waitbuttonpress
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion4_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion4_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion4_MenuHeader_Opt3, 3
	dynmultistack 0, 0, TRUE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 3, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer

DragonShrine_Johto_DragonShrineTakeTestScript_Question5:
	setflag FLAG_TEMP_16
	message DragonShrine_Johto_DragonShrineQuestion5Text
	waitmessage
	waitbuttonpress
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion5_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion5_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_DragonShrine_DragonShrineQuestion5_MenuHeader_Opt3, 3
	dynmultistack 0, 0, TRUE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 2, DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer

DragonShrine_Johto_DragonShrineTakeTestScript_RightAnswer:
	goto_if_set FLAG_TEMP_16, DragonShrine_Johto_DragonShrineTakeTestScript_PassedTheTest
	message DragonShrine_Johto_DragonShrineRightAnswerText
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_TEMP_15, DragonShrine_Johto_DragonShrineTakeTestScript_Question5
	goto_if_set FLAG_TEMP_14, DragonShrine_Johto_DragonShrineTakeTestScript_Question4
	goto_if_set FLAG_TEMP_13, DragonShrine_Johto_DragonShrineTakeTestScript_Question3
	goto_if_set FLAG_TEMP_12, DragonShrine_Johto_DragonShrineTakeTestScript_Question2

DragonShrine_Johto_DragonShrineTakeTestScript_WrongAnswer:
	closemessage
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message DragonShrine_Johto_DragonShrineWrongAnswerText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	message DragonShrine_Johto_DragonShrineWrongAnswerText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_ANSWERED_DRAGON_MASTER_QUIZ_WRONG
	goto_if_set FLAG_TEMP_16, DragonShrine_Johto_DragonShrineTakeTestScript_Question5
	goto_if_set FLAG_TEMP_15, DragonShrine_Johto_DragonShrineTakeTestScript_Question4
	goto_if_set FLAG_TEMP_14, DragonShrine_Johto_DragonShrineTakeTestScript_Question3
	goto_if_set FLAG_TEMP_13, DragonShrine_Johto_DragonShrineTakeTestScript_Question2
	goto_if_set FLAG_TEMP_12, DragonShrine_Johto_DragonShrineTakeTestScript_Question1

DragonShrine_Johto_DragonShrineTakeTestScript_PassedTheTest:
	message DragonShrine_Johto_DragonShrinePassedTestText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_DOOR
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_DUMMY, FALSE
	clearflag FLAG_JOHTO_DRAGON_SHRINE_CLAIR
	addobject 4
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 30
	applymovement 4, DragonShrine_Johto_DragonShrineClairWalkInMovement
	waitmovement 4
	applymovement 4, Johto_Movement_Face_Right
	waitmovement 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message DragonShrine_Johto_DragonShrineClairYouPassedText
	waitmessage
	waitbuttonpress
	closemessage
	fadeoutbgm 4
	applymovement 4, DragonShrine_Johto_DragonShrineClairBigStepLeftMovement
	waitmovement 4
	message DragonShrine_Johto_DragonShrineClairThatCantBeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, DragonShrine_Johto_DragonShrineClairSlowStepLeftMovement
	waitmovement 4
	message DragonShrine_Johto_DragonShrineClairYoureLyingText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, DragonShrine_Johto_DragonShrineElderWalkToClairMovement
	waitmovement 1
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	message DragonShrine_Johto_DragonShrineMustIInformLanceText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Emote_exclamation_mark
	waitmovement 4
	message DragonShrine_Johto_DragonShrineIUnderstandText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, DragonShrine_Johto_DragonShrineClairTwoSlowStepsRightMovement
	waitmovement 4
	message DragonShrine_Johto_DragonShrineHereRisingBadgeText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_ENGINE_RISINGBADGE
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	fadedefaultbgm
	setvar VAR_JOHTO_SCENE_DRAGON_SHRINE, 1
	setvar VAR_JOHTO_SCENE_DRAGONS_DEN_B1F, 1
	message DragonShrine_Johto_DragonShrinePlayerReceivedRisingBadgeText
	waitmessage
	waitbuttonpress
	message DragonShrine_Johto_DragonShrineRisingBadgeExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, DragonShrine_Johto_DragonShrineElderWalkAway1Movement
	waitmovement 1
	applymovement 4, Johto_Movement_Face_Up
	waitmovement 4
	applymovement 1, DragonShrine_Johto_DragonShrineElderWalkAway2Movement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message DragonShrine_Johto_DragonShrineElderScoldsClairText
	waitmessage
	waitbuttonpress
	closemessage
	message DragonShrine_Johto_DragonShrineSpeechlessText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, DragonShrine_Johto_DragonShrineClairWalkOutMovement
	waitmovement 4
	playse SE_DOOR
	removeobject 4
	waitse
	setflag FLAG_TEMP_11
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script:
	faceplayer
	goto_if_set FLAG_TEMP_11, DragonShrine_Johto_DragonShrineElder1Script_DontGiveDratiniYet
	goto_if_set FLAG_TEMP_17, DragonShrine_Johto_DragonShrineElder1Script_ReceivedDratini
	goto_if_unset FLAG_JOHTO_GOT_DRATINI, DragonShrine_Johto_DragonShrineElder1Script_GiveDratini
	goto_if_set FLAG_JOHTO_BEAT_RIVAL_IN_MT_MOON, DragonShrine_Johto_DragonShrineElder1Script_BeatRivalInMtMoon
	message DragonShrine_Johto_DragonShrineClairsGrandfatherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_GiveDratini:
	message DragonShrine_Johto_DragonShrineTakeThisDratiniText
	waitmessage
	waitbuttonpress
	getpartysize
	goto_if_eq VAR_RESULT, 6, DragonShrine_Johto_DragonShrineElder1Script_PartyFull
	message DragonShrine_Johto_DragonShrinePlayerReceivedDratiniText
	waitmessage
	playse SE_PIN
	waitse
	givemon SPECIES_DRATINI, 15
	@ POKE-CONFLUENCE: Authentic Crystal ExtremeSpeed Dratini reward for honorable quiz answers
	goto_if_set FLAG_JOHTO_ANSWERED_DRAGON_MASTER_QUIZ_WRONG, DragonShrine_Johto_DragonShrineElder1Script_SkipExtremeSpeed
	setmonmove 255, 0, MOVE_WRAP
	setmonmove 255, 1, MOVE_THUNDER_WAVE
	setmonmove 255, 2, MOVE_TWISTER
	setmonmove 255, 3, MOVE_EXTREME_SPEED
DragonShrine_Johto_DragonShrineElder1Script_SkipExtremeSpeed:
	setflag FLAG_JOHTO_GOT_DRATINI
	setflag FLAG_TEMP_17
	message DragonShrine_Johto_DragonShrineSymbolicDragonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_PartyFull:
	message DragonShrine_Johto_DragonShrinePartyFullText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_BeatRivalInMtMoon:
	message DragonShrine_Johto_DragonShrineRivalIsInTrainingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_DontGiveDratiniYet:
	message DragonShrine_Johto_DragonShrineComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_ReceivedDratini:
	message DragonShrine_Johto_DragonShrineSymbolicDragonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder2Script:
	faceplayer
	message DragonShrine_Johto_DragonShrineElder2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder3Script:
	faceplayer
	message DragonShrine_Johto_DragonShrineElder3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrinePlayerWalkInMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

DragonShrine_Johto_DragonShrineElderStepDownMovement:
	walk_slow_down
	step_end

DragonShrine_Johto_DragonShrineElderWalkToClairMovement:
	walk_slow_left
	walk_slow_left
	walk_slow_left
	face_down
	step_end

DragonShrine_Johto_DragonShrineElderWalkAway1Movement:
	walk_slow_right
	walk_slow_right
	step_end

DragonShrine_Johto_DragonShrineElderWalkAway2Movement:
	walk_slow_right
	face_down
	step_end

DragonShrine_Johto_DragonShrineClairWalkInMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

DragonShrine_Johto_DragonShrineClairBigStepLeftMovement:
	lock_facing_direction
	walk_fast_left
	step_end

DragonShrine_Johto_DragonShrineClairSlowStepLeftMovement:
	walk_slow_left
	unlock_facing_direction
	step_end

DragonShrine_Johto_DragonShrineClairTwoSlowStepsRightMovement:
	walk_slow_right
	walk_slow_right
	step_end

DragonShrine_Johto_DragonShrineClairWalkOutMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

DragonShrine_Johto_DragonShrineElderGreetingText:
	.string "Hm… Good to see\n"
	.string "you here."
	.string "\pNo need to explain\n"
	.string "why you came."
	.string "\pCLAIR sent you\n"
	.string "here, didn't she?"
	.string "\pThat girl is a\n"
	.string "handful…"
	.string "\pI am sorry, but I\n"
	.string "must test you."
	.string "\pNot to worry, you\n"
	.string "are to answer only\l"
	.string "a few questions."
	.string "\pReady?$"

DragonShrine_Johto_DragonShrineQuestion1Text:
	.string "What are POKéMON\n"
	.string "to you?$"

DragonShrine_Johto_DragonShrineQuestion2Text:
	.string "What helps you to\n"
	.string "win battles?$"

DragonShrine_Johto_DragonShrineQuestion3Text:
	.string "What kind of\n"
	.string "trainer do you\l"
	.string "wish to battle?$"

DragonShrine_Johto_DragonShrineQuestion4Text:
	.string "What is most\n"
	.string "important for\l"
	.string "raising POKéMON?$"

DragonShrine_Johto_DragonShrineQuestion5Text:
	.string "Strong POKéMON.\n"
	.string "Weak POKéMON."
	.string "\pWhich is more\n"
	.string "important?$"

DragonShrine_Johto_DragonShrinePassedTestText:
	.string "Hm… I see…"
	.string "\pYou care deeply\n"
	.string "for POKéMON."
	.string "\pVery commendable."
	.string "\pThat conviction is\n"
	.string "what is important!"
	.string "\p{PLAYER}, don't\n"
	.string "lose that belief."
	.string "\pIt will see you\n"
	.string "through at the\l"
	.string "POKéMON LEAGUE.$"

DragonShrine_Johto_DragonShrineMustIInformLanceText:
	.string "CLAIR!"
	.string "\pThis child is\n"
	.string "impeccable, in\l"
	.string "skill and spirit!"
	.string "\pAdmit defeat and\n"
	.string "confer the RISING-\l"
	.string "BADGE!"
	.string "\p…Or must I inform\n"
	.string "LANCE of this?$"

DragonShrine_Johto_DragonShrineElderScoldsClairText:
	.string "CLAIR…"
	.string "\pReflect upon what\n"
	.string "it is that you"
	.string "\plack and this\n"
	.string "child has.$"

DragonShrine_Johto_DragonShrineComeAgainText:
	.string "Come again, if you\n"
	.string "so desire.$"

DragonShrine_Johto_DragonShrineTakeThisDratiniText:
	.string "Hm… Good to see\n"
	.string "you here."
	.string "\pYour arrival is\n"
	.string "most fortunate."
	.string "\pI have something\n"
	.string "for you."
	.string "\pTake this DRATINI\n"
	.string "as proof that I"
	.string "\phave recognized\n"
	.string "your worth.$"

DragonShrine_Johto_DragonShrinePlayerReceivedDratiniText:
	.string "{PLAYER} received\n"
	.string "DRATINI!$"

DragonShrine_Johto_DragonShrinePartyFullText:
	.string "Hm? Your POKéMON\n"
	.string "party is full.$"

DragonShrine_Johto_DragonShrineSymbolicDragonText:
	.string "Dragon POKéMON are\n"
	.string "symbolic of our\l"
	.string "clan."
	.string "\pYou have shown\n"
	.string "that you can be"
	.string "\pentrusted with\n"
	.string "one.$"

DragonShrine_Johto_DragonShrineClairsGrandfatherText:
	.string "CLAIR appears to\n"
	.string "have learned an"
	.string "\pinvaluable lesson\n"
	.string "from you."
	.string "\pI thank you as her\n"
	.string "grandfather.$"

DragonShrine_Johto_DragonShrineRivalIsInTrainingText:
	.string "A boy close to\n"
	.string "your age is in\l"
	.string "training here."
	.string "\pHe is much like\n"
	.string "CLAIR when she was"
	.string "\pyounger. It is a\n"
	.string "little worrisome…$"

DragonShrine_Johto_DragonShrineWrongAnswerText1:
	.string "Hah? I didn't\n"
	.string "quite catch that…$"

DragonShrine_Johto_DragonShrineWrongAnswerText2:
	.string "What was it you\n"
	.string "said?$"

DragonShrine_Johto_DragonShrineRightAnswerText:
	.string "Oh, I understand…$"

DragonShrine_Johto_DragonShrineElder2Text:
	.string "It's been quite\n"
	.string "some time since a"
	.string "\ptrainer has gained\n"
	.string "our MASTER's rare\l"
	.string "approval."
	.string "\pIn fact, not since\n"
	.string "Master LANCE.$"

DragonShrine_Johto_DragonShrineElder3Text:
	.string "You know young\n"
	.string "Master LANCE?"
	.string "\pHe looks so much\n"
	.string "like our MASTER\l"
	.string "did in his youth."
	.string "\pIt's in their\n"
	.string "blood.$"

DragonShrine_Johto_DragonShrineClairYouPassedText:
	.string "So how did it go?"
	.string "\pI guess there's no\n"
	.string "point in asking."
	.string "\pYou did fail?"
	.string "\p………………"
	.string "\p…What? You passed?$"

DragonShrine_Johto_DragonShrineClairThatCantBeText:
	.string "That can't be!$"

DragonShrine_Johto_DragonShrineClairYoureLyingText:
	.string "You're lying!"
	.string "\pEven I haven't\n"
	.string "been approved!$"

DragonShrine_Johto_DragonShrineIUnderstandText:
	.string "I-I understand…$"

DragonShrine_Johto_DragonShrineHereRisingBadgeText:
	.string "Here, this is the\n"
	.string "RISINGBADGE…"
	.string "\pHurry up! Take it!$"

DragonShrine_Johto_DragonShrinePlayerReceivedRisingBadgeText:
	.string "{PLAYER} received\n"
	.string "RISINGBADGE.$"

DragonShrine_Johto_DragonShrineRisingBadgeExplanationText:
	.string "RISINGBADGE will\n"
	.string "enable your"
	.string "\pPOKéMON to use the\n"
	.string "move for climbing\l"
	.string "waterfalls."
	.string "\pAlso, all POKéMON\n"
	.string "will recognize you"
	.string "\pas a trainer and\n"
	.string "obey your every"
	.string "\pcommand without\n"
	.string "question.$"

DragonShrine_Johto_DragonShrineSpeechlessText:
	.string "………………$"
