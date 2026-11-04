WiseTriosRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WiseTriosRoom_Johto_OnTransition
	.byte 0

WiseTriosRoom_Johto_OnTransition:
	call WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_Cb
	end

WiseTriosRoom_Johto_WiseTriosRoomSage1Script_Entry::
	lockall
	goto WiseTriosRoom_Johto_WiseTriosRoomSage1Script

WiseTriosRoom_Johto_WiseTriosRoomSage2Script_Entry::
	lockall
	goto WiseTriosRoom_Johto_WiseTriosRoomSage2Script

WiseTriosRoom_Johto_WiseTriosRoomSage3Script_Entry::
	lockall
	goto WiseTriosRoom_Johto_WiseTriosRoomSage3Script

WiseTriosRoom_Johto_WiseTriosRoom_CannotEnterTinTowerScript_Entry::
	lockall
	goto WiseTriosRoom_Johto_WiseTriosRoom_CannotEnterTinTowerScript


WiseTriosRoom_Johto_WiseTriosRoomSage1Script:
	faceplayer
	message WiseTriosRoom_Johto_WiseTriosRoomSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_WiseTriosRoomSage2Script:
	faceplayer
	message WiseTriosRoom_Johto_WiseTriosRoomSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_WiseTriosRoomSage3Script:
	faceplayer
	message WiseTriosRoom_Johto_WiseTriosRoomSage3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_WiseTriosRoom_CannotEnterTinTowerScript:
	applymovement 3, Johto_Movement_Face_Up
	waitmovement 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	applymovement 3, WiseTriosRoom_Johto_WiseTriosRoomSageBlocksPlayerMovement
	applymovement OBJ_EVENT_ID_PLAYER, WiseTriosRoom_Johto_WiseTriosRoomSageBlocksPlayerMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message WiseTriosRoom_Johto_WiseTriosRoomSage3BlocksExitText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, WiseTriosRoom_Johto_WiseTriosRoomSageReturnsMovement
	waitmovement 3
	applymovement 3, Johto_Movement_Face_Left
	waitmovement 3
	releaseall
	end

WiseTriosRoom_Johto_TrainerSageGaku::
	trainerbattle_single TRAINER_JOHTO_SAGE_GAKU, WiseTriosRoom_Johto_SageGakuSeenText, WiseTriosRoom_Johto_SageGakuBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_GAKU
	lock
	faceplayer
	goto WiseTriosRoom_Johto_TrainerSageGaku_Script

WiseTriosRoom_Johto_TrainerSageGaku_Script:
	message WiseTriosRoom_Johto_SageGakuAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_TrainerSageMasa::
	trainerbattle_single TRAINER_JOHTO_SAGE_MASA, WiseTriosRoom_Johto_SageMasaSeenText, WiseTriosRoom_Johto_SageMasaBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_MASA
	lock
	faceplayer
	goto WiseTriosRoom_Johto_TrainerSageMasa_Script

WiseTriosRoom_Johto_TrainerSageMasa_Script:
	message WiseTriosRoom_Johto_SageMasaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_TrainerSageKoji::
	trainerbattle_single TRAINER_JOHTO_SAGE_KOJI, WiseTriosRoom_Johto_SageKojiSeenText, WiseTriosRoom_Johto_SageKojiBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_KOJI
	lock
	faceplayer
	goto WiseTriosRoom_Johto_TrainerSageKoji_Script

WiseTriosRoom_Johto_TrainerSageKoji_Script:
	goto_if_set FLAG_JOHTO_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, WiseTriosRoom_Johto_TrainerSageKoji_KojiAllowsPassage
	delay 10
	applymovement 6, Johto_Movement_Emote_exclamation_mark
	waitmovement 6
	message WiseTriosRoom_Johto_SageKojiAfterBattleQuestionText
	waitmessage
	waitbuttonpress
	message WiseTriosRoom_Johto_SageKojiAfterBattleSpeechText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, WiseTriosRoom_Johto_WiseTriosRoomSageAllowsPassageMovement
	waitmovement 6
	applymovement 6, Johto_Movement_Face_Up
	waitmovement 6
	setflag FLAG_JOHTO_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER
	setvar VAR_JOHTO_SCENE_WISE_TRIOS_ROOM, 1
	releaseall
	end

WiseTriosRoom_Johto_TrainerSageKoji_KojiAllowsPassage:
	message WiseTriosRoom_Johto_SageKojiAfterBattleFinalText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_Cb:
	goto_if_set FLAG_JOHTO_FOUGHT_SUICUNE, WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_NoWiseTrio_Cb
	goto_if_set FLAG_JOHTO_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_WiseTrio2_Cb
	checkitem ITEM_CLEAR_BELL, 1
	goto_if_ne VAR_RESULT, 0, WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_WiseTrio2_Cb
	clearflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_1
	setflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_2
	return

WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_WiseTrio2_Cb:
	setflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_1
	clearflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_2
	return

WiseTriosRoom_Johto_WiseTriosRoomWiseTrioCallback_NoWiseTrio_Cb:
	setflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_1
	setflag FLAG_JOHTO_WISE_TRIOS_ROOM_WISE_TRIO_2
	return

WiseTriosRoom_Johto_WiseTriosRoomSageBlocksPlayerMovement:
	walk_left
	walk_left
	step_end

WiseTriosRoom_Johto_WiseTriosRoomSageReturnsMovement:
	walk_right
	walk_down
	step_end

WiseTriosRoom_Johto_WiseTriosRoomSageAllowsPassageMovement:
	walk_right
	walk_down
	step_end

WiseTriosRoom_Johto_WiseTriosRoomSage1Text:
	.string "Astounding…"
	.string "\pSUICUNE, ENTEI and\n"
	.string "RAIKOU have arisen\l"
	.string "from their sleep…"
	.string "\pIs the legend\n"
	.string "coming true?$"

WiseTriosRoom_Johto_WiseTriosRoomSage2Text:
	.string "We train at the\n"
	.string "BURNED TOWER, but"
	.string "\pwe've never heard\n"
	.string "of a hole opening"
	.string "\pup there before.\n"
	.string "It must have been"
	.string "\pdeliberately made\n"
	.string "by someone.$"

WiseTriosRoom_Johto_WiseTriosRoomSage3BlocksExitText:
	.string "TIN TOWER may be\n"
	.string "entered by those"
	.string "\pbearing ECRUTEAK's\n"
	.string "GYM BADGE."
	.string "\pHowever, now that\n"
	.string "SUICUNE, RAIKOU"
	.string "\pand ENTEI have\n"
	.string "arisen, I ask you"
	.string "\pto refrain from\n"
	.string "entering!$"

WiseTriosRoom_Johto_WiseTriosRoomSage3Text:
	.string "We, the WISE TRIO,\n"
	.string "are the protectors"
	.string "\pof the legendary\n"
	.string "POKéMON.$"

WiseTriosRoom_Johto_SageGakuSeenText:
	.string "Legend has it that\n"
	.string "upon the emergence"
	.string "\pof a trainer who\n"
	.string "has the ability to"
	.string "\ptouch the souls of\n"
	.string "POKéMON, a POKéMON"
	.string "\pwill come forth to\n"
	.string "put that trainer"
	.string "\pto test at the TIN\n"
	.string "TOWER."
	.string "\pThe legend has\n"
	.string "come true!"
	.string "\pThe legendary\n"
	.string "POKéMON SUICUNE\l"
	.string "has arrived!"
	.string "\pWe, the WISE TRIO,\n"
	.string "shall test your"
	.string "\pworthiness to go\n"
	.string "inside!$"

WiseTriosRoom_Johto_SageGakuBeatenText:
	.string "Stronger than we\n"
	.string "thought? Perhaps…$"

WiseTriosRoom_Johto_SageGakuAfterBattleText:
	.string "Ah, so it is you\n"
	.string "who claim to have"
	.string "\pseen SUICUNE,\n"
	.string "ENTEI and RAIKOU\l"
	.string "while they slept?"
	.string "\pUnbelievable!"
	.string "\pLegend has it that\n"
	.string "they can't be seen\l"
	.string "while they sleep…$"

WiseTriosRoom_Johto_SageMasaSeenText:
	.string "Can you be trusted\n"
	.string "with the truth?"
	.string "\pI must ascertain\n"
	.string "your worthiness.$"

WiseTriosRoom_Johto_SageMasaBeatenText:
	.string "…I will tell you\n"
	.string "the truth…$"

WiseTriosRoom_Johto_SageMasaAfterBattleText:
	.string "In the past, there\n"
	.string "were two nine-tier\l"
	.string "towers here."
	.string "\pThe BRASS TOWER,\n"
	.string "which was said to"
	.string "\pawaken POKéMON,\n"
	.string "and the TIN TOWER,"
	.string "\pwhere POKéMON were\n"
	.string "said to rest."
	.string "\pThe view from the\n"
	.string "tops of the TOWERS"
	.string "\pmust have been\n"
	.string "magnificent."
	.string "\pAt the time, an\n"
	.string "immense, silver-"
	.string "\pcolored POKéMON\n"
	.string "was said to make"
	.string "\pits roost atop the\n"
	.string "BRASS TOWER."
	.string "\pHowever…"
	.string "\pAbout 150 years\n"
	.string "ago, a lightning"
	.string "\pbolt struck one of\n"
	.string "the TOWERS."
	.string "\pIt was engulfed in\n"
	.string "flames that raged\l"
	.string "for three days."
	.string "\pA sudden downpour\n"
	.string "finally put out\l"
	.string "the blaze."
	.string "\pAnd that is how\n"
	.string "the BURNED TOWER\l"
	.string "came to be.$"

WiseTriosRoom_Johto_SageKojiSeenText:
	.string "Let me see your\n"
	.string "power!$"

WiseTriosRoom_Johto_SageKojiBeatenText:
	.string "Too strong!\n"
	.string "Why?$"

WiseTriosRoom_Johto_SageKojiAfterBattleQuestionText:
	.string "You… Are you the\n"
	.string "trainer who is"
	.string "\pawaited by the\n"
	.string "legendary POKéMON?$"

WiseTriosRoom_Johto_SageKojiAfterBattleSpeechText:
	.string "I see…"
	.string "\pWe, the WISE TRIO,\n"
	.string "have been given "
	.string "\pthe responsibility\n"
	.string "of protecting the"
	.string "\plegendary POKéMON.\n"
	.string "We are to allow"
	.string "\ppassage only to\n"
	.string "those people who"
	.string "\ppossess the power\n"
	.string "and soul of truth."
	.string "\pPlease, do go on\n"
	.string "and enter the TIN\l"
	.string "TOWER ahead."
	.string "\pSUICUNE will put\n"
	.string "you to the test.$"

WiseTriosRoom_Johto_SageKojiAfterBattleFinalText:
	.string "Please, do go on."
	.string "\pSUICUNE will put\n"
	.string "you to the test.$"
