RuinsOfAlphOutside_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlphOutside_Johto_OnTransition
	.byte 0

RuinsOfAlphOutside_Johto_OnTransition:
	call RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_Cb
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScript_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScript

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherScript_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherScript

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster1Script_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster1Script

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster2Script_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster2Script

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideMysteryChamberSign_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideMysteryChamberSign

RuinsOfAlphOutside_Johto_RuinsOfAlphSign_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphSign

RuinsOfAlphOutside_Johto_RuinsOfAlphResearchCenterSign_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphResearchCenterSign

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene1_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene1

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene2_Entry::
	lockall
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene2


RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene1:
	applymovement 2, Johto_Movement_Face_Up
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistSceneContinue

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScene2:
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistSceneContinue

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistScript:
	faceplayer

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistSceneContinue:
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistText
	waitmessage
	waitbuttonpress
	closemessage
	playbgm MUS_DUMMY, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistWalkToLabMovement
	applymovement 2, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistWalkToLabMovement
	waitmovement 2
	removeobject 2
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsidePlayerEnterLabMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 1
	warp MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER, 10, 13
	waitstate
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_TALKED_TO_RUINS_COWARD, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherScript_Next
	setflag FLAG_JOHTO_TALKED_TO_RUINS_COWARD
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherText1
	waitmessage
	waitbuttonpress

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherScript_Next:
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster1Script:
	faceplayer
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster2Script:
	faceplayer
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Up
	waitmovement 5
	releaseall
	end

RuinsOfAlphOutside_Johto_TrainerPsychicNathan::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_NATHAN, RuinsOfAlphOutside_Johto_PsychicNathanSeenText, RuinsOfAlphOutside_Johto_PsychicNathanBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_NATHAN
	lock
	faceplayer
	goto RuinsOfAlphOutside_Johto_TrainerPsychicNathan_Script

RuinsOfAlphOutside_Johto_TrainerPsychicNathan_Script:
	message RuinsOfAlphOutside_Johto_PsychicNathanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideMysteryChamberSign:
	message RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideMysteryChamberSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphSign:
	message RuinsOfAlphOutside_Johto_RuinsOfAlphSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphResearchCenterSign:
	message RuinsOfAlphOutside_Johto_RuinsOfAlphResearchCenterSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_UNOWN_DEX, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_NoScientist_Cb
	goto_if_set FLAG_JOHTO_MADE_UNOWN_APPEAR_IN_RUINS, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_MaybeScientist_Cb
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_NoScientist_Cb

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_MaybeScientist_Cb:
	setvar VAR_RESULT, 0
	goto_if_gt VAR_RESULT, 2, RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_YesScientist_Cb
	goto RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_NoScientist_Cb

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_YesScientist_Cb:
	clearflag FLAG_JOHTO_RUINS_OF_ALPH_OUTSIDE_SCIENTIST
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_OUTSIDE, 1
	return

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistCallback_NoScientist_Cb:
	setflag FLAG_JOHTO_RUINS_OF_ALPH_OUTSIDE_SCIENTIST
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_OUTSIDE, 0
	return

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistWalkToLabMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsidePlayerEnterLabMovement:
	walk_up
	step_end

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideScientistText:
	.string "Hm? That's a POKé-\n"
	.string "DEX, isn't it?\l"
	.string "May I see it?"
	.string "\pThere are so many\n"
	.string "kinds of POKéMON."
	.string "\pHm? What's this?"
	.string "\pWhat is this\n"
	.string "POKéMON?"
	.string "\pIt looks like the\n"
	.string "strange writing on"
	.string "\pthe walls of the\n"
	.string "RUINS."
	.string "\pIf those drawings\n"
	.string "are really POKé-\l"
	.string "MON, there should\l"
	.string "be many more."
	.string "\pI know! Let me up-\n"
	.string "grade your POKé-\l"
	.string "DEX. Follow me.$"

RuinsOfAlphOutside_Johto_PsychicNathanSeenText:
	.string "Hmmm… This is a\n"
	.string "strange place.$"

RuinsOfAlphOutside_Johto_PsychicNathanBeatenText:
	.string "…$"

RuinsOfAlphOutside_Johto_PsychicNathanAfterBattleText:
	.string "I like thinking\n"
	.string "here.$"

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideMysteryChamberSignText:
	.string "MYSTERY STONE\n"
	.string "PANEL CHAMBER$"

RuinsOfAlphOutside_Johto_RuinsOfAlphSignText:
	.string "RUINS OF ALPH\n"
	.string "VISITORS WELCOME$"

RuinsOfAlphOutside_Johto_RuinsOfAlphResearchCenterSignText:
	.string "RUINS OF ALPH\n"
	.string "RESEARCH CENTER"
	.string "\pTHE AUTHORITY ON\n"
	.string "THE RUINS OF ALPH$"

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherText1:
	.string "While exploring\n"
	.string "the RUINS, we"
	.string "\psuddenly noticed\n"
	.string "an odd presence."
	.string "\pWe all got scared\n"
	.string "and ran away."
	.string "\pYou should be\n"
	.string "careful too.$"

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideFisherText2:
	.string "The RUINS hide a\n"
	.string "huge secret!"
	.string "\p…I think…$"

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster1Text:
	.string "There are many\n"
	.string "kinds of UNOWN, so"
	.string "\pwe use them for\n"
	.string "our secret codes.$"

RuinsOfAlphOutside_Johto_RuinsOfAlphOutsideYoungster2Text:
	.string "A… H… E… A… D…\n"
	.string "Hmm…"
	.string "\pWhat?"
	.string "\pI'm decoding this\n"
	.string "message!$"
