IlexForest_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IlexForest_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, IlexForest_Johto_OnLoad
	.byte 0

IlexForest_Johto_OnTransition:
	call IlexForest_Johto_IlexForestFarfetchdCallback_Cb
	end

IlexForest_Johto_IlexForestFarfetchdScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestFarfetchdScript

IlexForest_Johto_IlexForestCharcoalApprenticeScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestCharcoalApprenticeScript

IlexForest_Johto_IlexForestCharcoalMasterScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestCharcoalMasterScript

IlexForest_Johto_IlexForestHeadbuttGuyScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestHeadbuttGuyScript

IlexForest_Johto_IlexForestRevive_Entry::
	lockall
	goto IlexForest_Johto_IlexForestRevive

IlexForest_Johto_IlexForestLassScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestLassScript

IlexForest_Johto_IlexForestXAttack_Entry::
	lockall
	goto IlexForest_Johto_IlexForestXAttack

IlexForest_Johto_IlexForestAntidote_Entry::
	lockall
	goto IlexForest_Johto_IlexForestAntidote

IlexForest_Johto_IlexForestEther_Entry::
	lockall
	goto IlexForest_Johto_IlexForestEther

IlexForest_Johto_IlexForestSignpost_Entry::
	lockall
	goto IlexForest_Johto_IlexForestSignpost

IlexForest_Johto_IlexForestShrineScript_Entry::
	lockall
	goto IlexForest_Johto_IlexForestShrineScript


IlexForest_Johto_IlexForestCharcoalApprenticeScript:
	faceplayer
	goto_if_set FLAG_JOHTO_HERDED_FARFETCHD, IlexForest_Johto_IlexForestCharcoalApprenticeScript_DoneFarfetchd
	message IlexForest_Johto_IlexForestApprenticeIntroText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestCharcoalApprenticeScript_DoneFarfetchd:
	message IlexForest_Johto_IlexForestApprenticeAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestFarfetchdScript:
	@ TODO unsupported: readmem wFarfetchdPosition
	goto Johto_EventScript_Unimplemented

IlexForest_Johto_IlexForestCharcoalMasterScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HM01_CUT, IlexForest_Johto_IlexForestCharcoalMasterScript_AlreadyGotCut
	message IlexForest_Johto_Text_CharcoalMasterIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM_CUT
	setflag FLAG_JOHTO_GOT_HM01_CUT
	message IlexForest_Johto_Text_CharcoalMasterOutro
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_ILEX_FOREST_FARFETCHD
	setflag FLAG_JOHTO_ILEX_FOREST_APPRENTICE
	setflag FLAG_JOHTO_ILEX_FOREST_CHARCOAL_MASTER
	clearflag FLAG_JOHTO_CHARCOAL_KILN_FARFETCH_D
	clearflag FLAG_JOHTO_CHARCOAL_KILN_APPRENTICE
	clearflag FLAG_JOHTO_CHARCOAL_KILN_BOSS
	releaseall
	end

IlexForest_Johto_IlexForestCharcoalMasterScript_AlreadyGotCut:
	message IlexForest_Johto_Text_CharcoalMasterTalkAfter
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestHeadbuttGuyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM02_HEADBUTT, IlexForest_Johto_IlexForestHeadbuttGuyScript_AlreadyGotHeadbutt
	message IlexForest_Johto_Text_HeadbuttIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, IlexForest_Johto_IlexForestHeadbuttGuyScript_BagFull
	setflag FLAG_JOHTO_GOT_TM02_HEADBUTT

IlexForest_Johto_IlexForestHeadbuttGuyScript_AlreadyGotHeadbutt:
	message IlexForest_Johto_Text_HeadbuttOutro
	waitmessage
	waitbuttonpress

IlexForest_Johto_IlexForestHeadbuttGuyScript_BagFull:
	closemessage
	releaseall
	end

IlexForest_Johto_TrainerBugCatcherWayne::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_WAYNE, IlexForest_Johto_BugCatcherWayneSeenText, IlexForest_Johto_BugCatcherWayneBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_WAYNE
	lock
	faceplayer
	goto IlexForest_Johto_TrainerBugCatcherWayne_Script

IlexForest_Johto_TrainerBugCatcherWayne_Script:
	message IlexForest_Johto_BugCatcherWayneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestLassScript:
	faceplayer
	message IlexForest_Johto_Text_IlexForestLass
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestRevive:
	finditem ITEM_REVIVE
	releaseall
	end

IlexForest_Johto_IlexForestXAttack:
	finditem ITEM_X_ATTACK
	releaseall
	end

IlexForest_Johto_IlexForestAntidote:
	finditem ITEM_ANTIDOTE
	releaseall
	end

IlexForest_Johto_IlexForestEther:
	finditem ITEM_ETHER
	releaseall
	end

IlexForest_Johto_IlexForestSignpost:
	message IlexForest_Johto_IlexForestSignpostText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestShrineScript:
	goto_if_set FLAG_JOHTO_FOREST_IS_RESTLESS, IlexForest_Johto_IlexForestShrineScript_ForestIsRestless
	goto IlexForest_Johto_IlexForestShrineScript_DontDoCelebiEvent

IlexForest_Johto_IlexForestShrineScript_ForestIsRestless:
	checkitem ITEM_GS_BALL, 1
	goto_if_ne VAR_RESULT, 0, IlexForest_Johto_IlexForestShrineScript_AskCelebiEvent

IlexForest_Johto_IlexForestShrineScript_DontDoCelebiEvent:
	message IlexForest_Johto_Text_IlexForestShrine
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestShrineScript_AskCelebiEvent:
	message IlexForest_Johto_Text_ShrineCelebiEvent
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, IlexForest_Johto_IlexForestShrineScript_CelebiEvent
	closemessage
	releaseall
	end

IlexForest_Johto_IlexForestShrineScript_CelebiEvent:
	removeitem ITEM_GS_BALL
	clearflag FLAG_JOHTO_FOREST_IS_RESTLESS
	setflag FLAG_JOHTO_AZALEA_TOWN_KURT
	removeobject 7
	clearflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_LASS
	message IlexForest_Johto_Text_InsertGSBall
	waitmessage
	waitbuttonpress
	closemessage
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	applymovement OBJ_EVENT_ID_PLAYER, IlexForest_Johto_IlexForestPlayerStepsDownMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 20
	clearflag FLAG_JOHTO_ENGINE_FOREST_IS_RESTLESS
	@ TODO unsupported: special CelebiShrineEvent
	goto Johto_EventScript_Unimplemented

IlexForest_Johto_IlexForestFarfetchdCallback_Cb:
	goto_if_set FLAG_JOHTO_GOT_HM01_CUT, IlexForest_Johto_IlexForestFarfetchdCallback_Static_Cb
	@ TODO unsupported: readmem wFarfetchdPosition
	return

IlexForest_Johto_IlexForestFarfetchdCallback_Static_Cb:
	return

IlexForest_Johto_IlexForestPlayerStepsDownMovement:
	lock_facing_direction
	walk_slow_down
	unlock_facing_direction
	step_end

IlexForest_Johto_IlexForestApprenticeIntroText:
	.string "Oh, man… My boss\n"
	.string "is going to be\l"
	.string "steaming…"
	.string "\pThe FARFETCH'D\n"
	.string "that CUTS trees"
	.string "\pfor charcoal took\n"
	.string "off on me."
	.string "\pI can't go looking\n"
	.string "for it here in the\l"
	.string "ILEX FOREST."
	.string "\pIt's too big, dark\n"
	.string "and scary for me…$"

IlexForest_Johto_IlexForestApprenticeAfterText:
	.string "Wow! Thanks a\n"
	.string "whole bunch!"
	.string "\pMy boss's POKéMON\n"
	.string "won't obey me be-\l"
	.string "cause I don't have\l"
	.string "a BADGE.$"

IlexForest_Johto_Text_CharcoalMasterIntro:
	.string "Ah! My FARFETCH'D!"
	.string "\pYou found it for\n"
	.string "us, kid?"
	.string "\pWithout it, we\n"
	.string "wouldn't be able"
	.string "\pto CUT trees for\n"
	.string "charcoal."
	.string "\pThanks, kid!"
	.string "\pNow, how can I\n"
	.string "thank you…"
	.string "\pI know! Here, take\n"
	.string "this.$"

IlexForest_Johto_Text_CharcoalMasterOutro:
	.string "That's the CUT HM.\n"
	.string "Teach that to a"
	.string "\pPOKéMON to clear\n"
	.string "small trees."
	.string "\pOf course, you\n"
	.string "have to have the"
	.string "\pGYM BADGE from\n"
	.string "AZALEA to use it.$"

IlexForest_Johto_Text_CharcoalMasterTalkAfter:
	.string "Do you want to\n"
	.string "apprentice as a"
	.string "\pcharcoal maker\n"
	.string "with me?"
	.string "\pYou'll be first-\n"
	.string "rate in ten years!$"

IlexForest_Johto_Text_HeadbuttIntro:
	.string "What am I doing?"
	.string "\pI'm shaking trees\n"
	.string "using HEADBUTT."
	.string "\pIt's fun. Here,\n"
	.string "you try it too!$"

IlexForest_Johto_Text_HeadbuttOutro:
	.string "Rattle trees with\n"
	.string "HEADBUTT. Some-\l"
	.string "times, sleeping\l"
	.string "POKéMON fall out.$"

IlexForest_Johto_Text_IlexForestLass:
	.string "Did something\n"
	.string "happen to the\l"
	.string "forest's guardian?$"

IlexForest_Johto_IlexForestSignpostText:
	.string "ILEX FOREST is\n"
	.string "so overgrown with"
	.string "\ptrees that you\n"
	.string "can't see the sky."
	.string "\pPlease watch out\n"
	.string "for items that may\l"
	.string "have been dropped.$"

IlexForest_Johto_Text_IlexForestShrine:
	.string "ILEX FOREST\n"
	.string "SHRINE…"
	.string "\pIt's in honor of\n"
	.string "the forest's\l"
	.string "protector…$"

IlexForest_Johto_Text_ShrineCelebiEvent:
	.string "ILEX FOREST\n"
	.string "SHRINE…"
	.string "\pIt's in honor of\n"
	.string "the forest's\l"
	.string "protector…"
	.string "\pOh? What is this?"
	.string "\pIt's a hole.\n"
	.string "It looks like the"
	.string "\pGS BALL would fit\n"
	.string "inside it."
	.string "\pWant to put the GS\n"
	.string "BALL here?$"

IlexForest_Johto_Text_InsertGSBall:
	.string "{PLAYER} put in the\n"
	.string "GS BALL.$"

IlexForest_Johto_BugCatcherWayneSeenText:
	.string "Don't sneak up on\n"
	.string "me like that!"
	.string "\pYou frightened a\n"
	.string "POKéMON away!$"

IlexForest_Johto_BugCatcherWayneBeatenText:
	.string "I hadn't seen that\n"
	.string "POKéMON before…$"

IlexForest_Johto_BugCatcherWayneAfterBattleText:
	.string "A POKéMON I've\n"
	.string "never seen before"
	.string "\pfell out of the\n"
	.string "tree when I used\l"
	.string "HEADBUTT."
	.string "\pI ought to use\n"
	.string "HEADBUTT in other\l"
	.string "places too.$"

IlexForest_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ILEX_FOREST_0, IlexForest_Johto_CutTree0_Keep
	setmetatile 8, 24, 516, 0
	setmetatile 9, 24, 516, 0
	setmetatile 8, 25, 516, 0
	setmetatile 9, 25, 524, 0
IlexForest_Johto_CutTree0_Keep:
	end

IlexForest_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, IlexForest_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ILEX_FOREST_0
	setmetatile 8, 24, 516, 0
	setmetatile 9, 24, 516, 0
	setmetatile 8, 25, 516, 0
	setmetatile 9, 25, 524, 0
	special DrawWholeMapView
IlexForest_Johto_CutTree0_Done:
	releaseall
	end
