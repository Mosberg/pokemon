DragonsDenB1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DragonsDenB1F_Johto_OnTransition
	.byte 0

DragonsDenB1F_Johto_OnTransition:
	call DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_Cb
	end

DragonsDenB1F_Johto_DragonsDenB1FDragonFangScript_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonsDenB1FDragonFangScript

DragonsDenB1F_Johto_DragonsDenB1FRivalScript_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonsDenB1FRivalScript

DragonsDenB1F_Johto_DragonsDenB1FCalcium_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonsDenB1FCalcium

DragonsDenB1F_Johto_DragonsDenB1FMaxElixer_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonsDenB1FMaxElixer

DragonsDenB1F_Johto_DragonShrineSignpost_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonShrineSignpost

DragonsDenB1F_Johto_DragonsDenB1F_ClairScene_Entry::
	lockall
	goto DragonsDenB1F_Johto_DragonsDenB1F_ClairScene


DragonsDenB1F_Johto_DragonsDenB1F_ClairScene:
	clearflag FLAG_JOHTO_DRAGONS_DEN_CLAIR
	addobject 2
	message DragonsDenB1F_Johto_ClairText_Wait
	waitmessage
	delay 30
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_DUMMY, FALSE
	applymovement 2, DragonsDenB1F_Johto_MovementDragonsDen_ClairWalksToYou
	waitmovement 2
	message DragonsDenB1F_Johto_ClairText_GiveDragonbreathDragonDen
	waitmessage
	waitbuttonpress
	additem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, DragonsDenB1F_Johto_DragonsDenB1F_ClairScene_BagFull
	@ TODO unsupported: getitemname STRING_BUFFER_3, TM_DRAGONBREATH
	goto Johto_EventScript_Unimplemented

DragonsDenB1F_Johto_DragonsDenB1F_ClairScene_BagFull:
	message DragonsDenB1F_Johto_ClairText_NoRoom
	waitmessage
	waitbuttonpress
	closemessage

DragonsDenB1F_Johto_DragonsDenB1F_ClairScene_FinishClair:
	applymovement 2, DragonsDenB1F_Johto_MovementDragonsDen_ClairWalksAway
	waitmovement 2
	fadeoutbgm 4
	delay 30
	fadedefaultbgm
	removeobject 2
	setvar VAR_JOHTO_SCENE_DRAGONS_DEN_B1F, 0
	releaseall
	end

DragonsDenB1F_Johto_TrainerCooltrainermDarin::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_DARIN, DragonsDenB1F_Johto_CooltrainermDarinSeenText, DragonsDenB1F_Johto_CooltrainermDarinBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_DARIN
	lock
	faceplayer
	goto DragonsDenB1F_Johto_TrainerCooltrainermDarin_Script

DragonsDenB1F_Johto_TrainerCooltrainermDarin_Script:
	message DragonsDenB1F_Johto_CooltrainermDarinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_TrainerCooltrainerfCara::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_CARA, DragonsDenB1F_Johto_CooltrainerfCaraSeenText, DragonsDenB1F_Johto_CooltrainerfCaraBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_CARA
	lock
	faceplayer
	goto DragonsDenB1F_Johto_TrainerCooltrainerfCara_Script

DragonsDenB1F_Johto_TrainerCooltrainerfCara_Script:
	message DragonsDenB1F_Johto_CooltrainerfCaraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_TrainerTwinsLeaandpia1::
	trainerbattle_single TRAINER_JOHTO_TWINS_LEAANDPIA1, DragonsDenB1F_Johto_TwinsLeaandpia1SeenText, DragonsDenB1F_Johto_TwinsLeaandpia1BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_LEA_AND_PIA
	lock
	faceplayer
	goto DragonsDenB1F_Johto_TrainerTwinsLeaandpia1_Script

DragonsDenB1F_Johto_TrainerTwinsLeaandpia1_Script:
	message DragonsDenB1F_Johto_TwinsLeaandpia1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_TrainerTwinsLeaandpia2::
	trainerbattle_single TRAINER_JOHTO_TWINS_LEAANDPIA1, DragonsDenB1F_Johto_TwinsLeaandpia2SeenText, DragonsDenB1F_Johto_TwinsLeaandpia2BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_LEA_AND_PIA
	lock
	faceplayer
	goto DragonsDenB1F_Johto_TrainerTwinsLeaandpia2_Script

DragonsDenB1F_Johto_TrainerTwinsLeaandpia2_Script:
	message DragonsDenB1F_Johto_TwinsLeaandpia2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FDragonFangScript:
	additem ITEM_DRAGON_FANG
	goto_if_eq VAR_RESULT, 0, DragonsDenB1F_Johto_DragonsDenB1FDragonFangScript_BagFull
	removeobject 1
	bufferitemname STR_VAR_1, ITEM_DRAGON_FANG
	message DragonsDenB1F_Johto_Text_FoundDragonFang
	waitmessage
	playse SE_PIN
	waitse
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FDragonFangScript_BagFull:
	bufferitemname STR_VAR_1, ITEM_DRAGON_FANG
	message DragonsDenB1F_Johto_Text_FoundDragonFang
	waitmessage
	waitbuttonpress
	message DragonsDenB1F_Johto_Text_NoRoomForDragonFang
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FRivalScript:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	faceplayer
	goto_if_set FLAG_TEMP_11, DragonsDenB1F_Johto_DragonsDenB1FRivalScript_RivalTalkAgain
	message DragonsDenB1F_Johto_RivalText_Training1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_TEMP_11
	fadedefaultbgm
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FRivalScript_RivalTalkAgain:
	message DragonsDenB1F_Johto_RivalText_Training2
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	releaseall
	end

DragonsDenB1F_Johto_DragonShrineSignpost:
	message DragonsDenB1F_Johto_DragonShrineSignpostText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FCalcium:
	finditem ITEM_CALCIUM
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FMaxElixer:
	finditem ITEM_MAX_ELIXER
	releaseall
	end

DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_Cb:
	goto_if_set FLAG_JOHTO_BEAT_RIVAL_IN_MT_MOON, DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_CheckDay_Cb
	setflag FLAG_JOHTO_RIVAL_DRAGONS_DEN
	return

DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_CheckDay_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 2, DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_AppearRival_Cb
	goto_if_eq VAR_RESULT, 4, DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_AppearRival_Cb
	setflag FLAG_JOHTO_RIVAL_DRAGONS_DEN
	return

DragonsDenB1F_Johto_DragonsDenB1FCheckRivalCallback_AppearRival_Cb:
	clearflag FLAG_JOHTO_RIVAL_DRAGONS_DEN
	return

DragonsDenB1F_Johto_MovementDragonsDen_ClairWalksToYou:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end

DragonsDenB1F_Johto_MovementDragonsDen_ClairWalksAway:
	walk_slow_left
	walk_slow_left
	walk_slow_left
	walk_slow_left
	step_end

DragonsDenB1F_Johto_ClairText_Wait:
	.string "Wait!$"

DragonsDenB1F_Johto_ClairText_GiveDragonbreathDragonDen:
	.string "CLAIR: I'm sorry\n"
	.string "about this."
	.string "\pHere, take this as\n"
	.string "my apology.$"

DragonsDenB1F_Johto_ClairText_NoRoom:
	.string "Oh? You don't have\n"
	.string "any room for this."
	.string "\pI'm going back to\n"
	.string "the GYM, so make"
	.string "\proom, then come\n"
	.string "see me there.$"

DragonsDenB1F_Johto_DragonShrineSignpostText:
	.string "DRAGON SHRINE"
	.string "\pA shrine honoring\n"
	.string "the dragon POKéMON"
	.string "\psaid to have lived\n"
	.string "in DRAGON'S DEN.$"

DragonsDenB1F_Johto_RivalText_Training1:
	.string "…\n"
	.string "What? {PLAYER}?"
	.string "\p…No, I won't\n"
	.string "battle you now…"
	.string "\pMy POKéMON aren't\n"
	.string "ready to beat you."
	.string "\pI can't push them\n"
	.string "too hard now."
	.string "\pI have to be dis-\n"
	.string "ciplined to become"
	.string "\pthe greatest POKé-\n"
	.string "MON trainer…$"

DragonsDenB1F_Johto_RivalText_Training2:
	.string "…"
	.string "\pWhew…"
	.string "\pLearn to stay out\n"
	.string "of my way…$"

DragonsDenB1F_Johto_CooltrainermDarinSeenText:
	.string "You! How dare you\n"
	.string "enter uninvited!$"

DragonsDenB1F_Johto_CooltrainermDarinBeatenText:
	.string "S-strong!$"

DragonsDenB1F_Johto_CooltrainermDarinAfterBattleText:
	.string "The SHRINE ahead\n"
	.string "is home to the"
	.string "\pMASTER of our\n"
	.string "dragon-user clan."
	.string "\pYou're not allowed\n"
	.string "to just go in!$"

DragonsDenB1F_Johto_CooltrainerfCaraSeenText:
	.string "You shouldn't be\n"
	.string "in here!$"

DragonsDenB1F_Johto_CooltrainerfCaraBeatenText:
	.string "Oh yikes, I lost!$"

DragonsDenB1F_Johto_CooltrainerfCaraAfterBattleText:
	.string "Soon I'm going to\n"
	.string "get permission"
	.string "\pfrom our MASTER to\n"
	.string "use dragons."
	.string "\pWhen I do, I'm\n"
	.string "going to become an"
	.string "\padmirable dragon\n"
	.string "trainer and gain"
	.string "\pour MASTER's\n"
	.string "approval.$"

DragonsDenB1F_Johto_TwinsLeaandpia1SeenText:
	.string "It's a stranger we\n"
	.string "don't know.$"

DragonsDenB1F_Johto_TwinsLeaandpia1BeatenText:
	.string "Ouchies.$"

DragonsDenB1F_Johto_TwinsLeaandpia1AfterBattleText:
	.string "It was like having\n"
	.string "to battle LANCE.$"

DragonsDenB1F_Johto_TwinsLeaandpia2SeenText:
	.string "Who are you?$"

DragonsDenB1F_Johto_TwinsLeaandpia2BeatenText:
	.string "Meanie.$"

DragonsDenB1F_Johto_TwinsLeaandpia2AfterBattleText:
	.string "We'll tell on you."
	.string "\pMASTER will be\n"
	.string "angry with you.$"

DragonsDenB1F_Johto_Text_FoundDragonFang:
	.string "{PLAYER} found\n"
	.string "{STR_VAR_1}!$"

DragonsDenB1F_Johto_Text_NoRoomForDragonFang:
	.string "But {PLAYER} can't\n"
	.string "carry any more\l"
	.string "items.$"
