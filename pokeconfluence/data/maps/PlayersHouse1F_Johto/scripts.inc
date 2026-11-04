PlayersHouse1F_Johto_MapScripts::
	.byte 0

PlayersHouse1F_Johto_MomScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_MomScript

PlayersHouse1F_Johto_NeighborScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_NeighborScript

PlayersHouse1F_Johto_PlayersHouse1FStoveScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_PlayersHouse1FStoveScript

PlayersHouse1F_Johto_PlayersHouse1FSinkScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_PlayersHouse1FSinkScript

PlayersHouse1F_Johto_PlayersHouse1FFridgeScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_PlayersHouse1FFridgeScript

PlayersHouse1F_Johto_PlayersHouse1FTVScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_PlayersHouse1FTVScript

PlayersHouse1F_Johto_MeetMomLeftScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_MeetMomLeftScript

PlayersHouse1F_Johto_MeetMomRightScript_Entry::
	lockall
	goto PlayersHouse1F_Johto_MeetMomRightScript


PlayersHouse1F_Johto_MeetMomLeftScript:
	setflag FLAG_TEMP_11

PlayersHouse1F_Johto_MeetMomRightScript:
	playbgm MUS_ENCOUNTER_FEMALE, FALSE
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_unset FLAG_TEMP_11, PlayersHouse1F_Johto_MeetMomRightScript_OnRight
	applymovement 1, PlayersHouse1F_Johto_MomTurnsTowardPlayerMovement
	waitmovement 1
	goto PlayersHouse1F_Johto_MeetMomScript

PlayersHouse1F_Johto_MeetMomRightScript_OnRight:
	applymovement 1, PlayersHouse1F_Johto_MomWalksToPlayerMovement
	waitmovement 1

PlayersHouse1F_Johto_MeetMomScript:
	message PlayersHouse1F_Johto_ElmsLookingForYouText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, PlayersHouse1F_Johto_PokegearName
	call PlayersHouse1F_Johto_PlayersHouse1FReceiveItemStd_Sub
	setflag FLAG_JOHTO_ENGINE_POKEGEAR
	setflag FLAG_JOHTO_ENGINE_PHONE_CARD
	setvar VAR_JOHTO_SCENE_PLAYERS_HOUSE_1F, 1
	setflag FLAG_JOHTO_PLAYERS_HOUSE_MOM_1
	clearflag FLAG_JOHTO_PLAYERS_HOUSE_MOM_2
	message PlayersHouse1F_Johto_MomGivesPokegearText
	waitmessage
	waitbuttonpress

PlayersHouse1F_Johto_MeetMomScript_SetDayOfWeek:
	message PlayersHouse1F_Johto_IsItDSTText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, PlayersHouse1F_Johto_MeetMomScript_WrongDay
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, PlayersHouse1F_Johto_MeetMomScript_SetDayOfWeek
	goto PlayersHouse1F_Johto_MeetMomScript_DayOfWeekDone

PlayersHouse1F_Johto_MeetMomScript_WrongDay:
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, PlayersHouse1F_Johto_MeetMomScript_SetDayOfWeek

PlayersHouse1F_Johto_MeetMomScript_DayOfWeekDone:
	message PlayersHouse1F_Johto_ComeHomeForDSTText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, PlayersHouse1F_Johto_MeetMomScript_ExplainPhone
	goto PlayersHouse1F_Johto_MeetMomScript_KnowPhone

PlayersHouse1F_Johto_MeetMomScript_KnowPhone:
	message PlayersHouse1F_Johto_KnowTheInstructionsText
	waitmessage
	waitbuttonpress
	goto PlayersHouse1F_Johto_MeetMomScript_FinishPhone

PlayersHouse1F_Johto_MeetMomScript_ExplainPhone:
	message PlayersHouse1F_Johto_DontKnowTheInstructionsText
	waitmessage
	waitbuttonpress
	goto PlayersHouse1F_Johto_MeetMomScript_FinishPhone

PlayersHouse1F_Johto_MeetMomScript_FinishPhone:
	message PlayersHouse1F_Johto_InstructionsNextText
	waitmessage
	waitbuttonpress
	closemessage
	goto_if_set FLAG_TEMP_11, PlayersHouse1F_Johto_MeetMomScript_FromRight
	goto_if_unset FLAG_TEMP_12, PlayersHouse1F_Johto_MeetMomScript_FromLeft
	goto PlayersHouse1F_Johto_MeetMomScript_Finish

PlayersHouse1F_Johto_MeetMomScript_FromRight:
	applymovement 1, PlayersHouse1F_Johto_MomTurnsBackMovement
	waitmovement 1
	goto PlayersHouse1F_Johto_MeetMomScript_Finish

PlayersHouse1F_Johto_MeetMomScript_FromLeft:
	applymovement 1, PlayersHouse1F_Johto_MomWalksBackMovement
	waitmovement 1
	goto PlayersHouse1F_Johto_MeetMomScript_Finish

PlayersHouse1F_Johto_MeetMomScript_Finish:
	fadedefaultbgm
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	releaseall
	end

PlayersHouse1F_Johto_MeetMomTalkedScript:
	playbgm MUS_ENCOUNTER_FEMALE, FALSE
	goto PlayersHouse1F_Johto_MeetMomScript

PlayersHouse1F_Johto_MomScript:
	faceplayer
	setflag FLAG_TEMP_12
	copyvar VAR_RESULT, VAR_JOHTO_SCENE_PLAYERS_HOUSE_1F
	goto_if_eq VAR_RESULT, 0, PlayersHouse1F_Johto_MeetMomTalkedScript
	goto_if_set FLAG_JOHTO_FIRST_TIME_BANKING_WITH_MOM, PlayersHouse1F_Johto_MomScript_FirstTimeBanking
	goto_if_set FLAG_JOHTO_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, PlayersHouse1F_Johto_MomScript_BankOfMom
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, PlayersHouse1F_Johto_MomScript_GaveMysteryEgg
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, PlayersHouse1F_Johto_MomScript_GotAPokemon
	message PlayersHouse1F_Johto_HurryUpElmIsWaitingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_MomScript_GotAPokemon:
	message PlayersHouse1F_Johto_SoWhatWasProfElmsErrandText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_MomScript_FirstTimeBanking:
	message PlayersHouse1F_Johto_ImBehindYouText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_MomScript_GaveMysteryEgg:
	setflag FLAG_JOHTO_FIRST_TIME_BANKING_WITH_MOM

PlayersHouse1F_Johto_MomScript_BankOfMom:
	setflag FLAG_JOHTO_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_NeighborScript:
	faceplayer
	setvar VAR_0x8004, 1
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, PlayersHouse1F_Johto_NeighborScript_MornScript
	setvar VAR_0x8004, 2
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, PlayersHouse1F_Johto_NeighborScript_DayScript
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, PlayersHouse1F_Johto_NeighborScript_NiteScript

PlayersHouse1F_Johto_NeighborScript_MornScript:
	message PlayersHouse1F_Johto_NeighborMornIntroText
	waitmessage
	waitbuttonpress
	goto PlayersHouse1F_Johto_NeighborScript_Main

PlayersHouse1F_Johto_NeighborScript_DayScript:
	message PlayersHouse1F_Johto_NeighborDayIntroText
	waitmessage
	waitbuttonpress
	goto PlayersHouse1F_Johto_NeighborScript_Main

PlayersHouse1F_Johto_NeighborScript_NiteScript:
	message PlayersHouse1F_Johto_NeighborNiteIntroText
	waitmessage
	waitbuttonpress
	goto PlayersHouse1F_Johto_NeighborScript_Main

PlayersHouse1F_Johto_NeighborScript_Main:
	message PlayersHouse1F_Johto_NeighborText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Right
	waitmovement 3
	releaseall
	end

PlayersHouse1F_Johto_PlayersHouse1FTVScript:
	message PlayersHouse1F_Johto_PlayersHouse1FTVText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_PlayersHouse1FStoveScript:
	message PlayersHouse1F_Johto_PlayersHouse1FStoveText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_PlayersHouse1FSinkScript:
	message PlayersHouse1F_Johto_PlayersHouse1FSinkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_PlayersHouse1FFridgeScript:
	message PlayersHouse1F_Johto_PlayersHouse1FFridgeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersHouse1F_Johto_PlayersHouse1FReceiveItemStd_Sub:
	goto Johto_Std_ReceiveItemScript_Sub

PlayersHouse1F_Johto_PokegearName:
	.string "POKéGEAR$"

PlayersHouse1F_Johto_MomTurnsTowardPlayerMovement:
	face_right
	step_end

PlayersHouse1F_Johto_MomWalksToPlayerMovement:
	walk_slow_right
	step_end

PlayersHouse1F_Johto_MomTurnsBackMovement:
	face_left
	step_end

PlayersHouse1F_Johto_MomWalksBackMovement:
	walk_slow_left
	step_end

PlayersHouse1F_Johto_ElmsLookingForYouText:
	.string "Oh, {PLAYER}…! Our\n"
	.string "neighbor, PROF."
	.string "\pELM, was looking\n"
	.string "for you."
	.string "\pHe said he wanted\n"
	.string "you to do some-\l"
	.string "thing for him."
	.string "\pOh! I almost for-\n"
	.string "got! Your POKéMON"
	.string "\pGEAR is back from\n"
	.string "the repair shop."
	.string "\pHere you go!$"

PlayersHouse1F_Johto_MomGivesPokegearText:
	.string "POKéMON GEAR, or\n"
	.string "just POKéGEAR."
	.string "\pIt's essential if\n"
	.string "you want to be a\l"
	.string "good trainer."
	.string "\pOh, the day of the\n"
	.string "week isn't set."
	.string "\pYou mustn't forget\n"
	.string "that!$"

PlayersHouse1F_Johto_IsItDSTText:
	.string "Is it Daylight\n"
	.string "Saving Time now?$"

PlayersHouse1F_Johto_ComeHomeForDSTText:
	.string "Come home to\n"
	.string "adjust your clock"
	.string "\pfor Daylight\n"
	.string "Saving Time."
	.string "\pBy the way, do you\n"
	.string "know how to use\l"
	.string "the PHONE?$"

PlayersHouse1F_Johto_KnowTheInstructionsText:
	.string "Don't you just\n"
	.string "turn the POKéGEAR"
	.string "\pon and select the\n"
	.string "PHONE icon?$"

PlayersHouse1F_Johto_DontKnowTheInstructionsText:
	.string "I'll read the\n"
	.string "instructions."
	.string "\pTurn the POKéGEAR\n"
	.string "on and select the\l"
	.string "PHONE icon.$"

PlayersHouse1F_Johto_InstructionsNextText:
	.string "Phone numbers are\n"
	.string "stored in memory."
	.string "\pJust choose a name\n"
	.string "you want to call."
	.string "\pGee, isn't that\n"
	.string "convenient?$"

PlayersHouse1F_Johto_HurryUpElmIsWaitingText:
	.string "PROF.ELM is wait-\n"
	.string "ing for you."
	.string "\pHurry up, baby!$"

PlayersHouse1F_Johto_SoWhatWasProfElmsErrandText:
	.string "So, what was PROF.\n"
	.string "ELM's errand?"
	.string "\p…"
	.string "\pThat does sound\n"
	.string "challenging."
	.string "\pBut, you should be\n"
	.string "proud that people\l"
	.string "rely on you.$"

PlayersHouse1F_Johto_ImBehindYouText:
	.string "{PLAYER}, do it!"
	.string "\pI'm behind you all\n"
	.string "the way!$"

PlayersHouse1F_Johto_NeighborMornIntroText:
	.string "Good morning,\n"
	.string "{PLAYER}!"
	.string "\pI'm visiting!$"

PlayersHouse1F_Johto_NeighborDayIntroText:
	.string "Hello, {PLAYER}!\n"
	.string "I'm visiting!$"

PlayersHouse1F_Johto_NeighborNiteIntroText:
	.string "Good evening,\n"
	.string "{PLAYER}!"
	.string "\pI'm visiting!$"

PlayersHouse1F_Johto_NeighborText:
	.string "{PLAYER}, have you\n"
	.string "heard?"
	.string "\pMy daughter is\n"
	.string "adamant about"
	.string "\pbecoming PROF.\n"
	.string "ELM's assistant."
	.string "\pShe really loves\n"
	.string "POKéMON!$"

PlayersHouse1F_Johto_PlayersHouse1FStoveText:
	.string "Mom's specialty!"
	.string "\pCINNABAR VOLCANO\n"
	.string "BURGER!$"

PlayersHouse1F_Johto_PlayersHouse1FSinkText:
	.string "The sink is spot-\n"
	.string "less. Mom likes it\l"
	.string "clean.$"

PlayersHouse1F_Johto_PlayersHouse1FFridgeText:
	.string "Let's see what's\n"
	.string "in the fridge…"
	.string "\pFRESH WATER and\n"
	.string "tasty LEMONADE!$"

PlayersHouse1F_Johto_PlayersHouse1FTVText:
	.string "There's a movie on\n"
	.string "TV: Stars dot the"
	.string "\psky as two boys\n"
	.string "ride on a train…"
	.string "\pI'd better get\n"
	.string "rolling too!$"
