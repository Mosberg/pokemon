Route29_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, Route29_Johto_OnLoad
	.byte 0

Route29_Johto_OnTransition:
	call Route29_Johto_Route29TuscanyCallback_Cb
	end

Route29_Johto_CatchingTutorialDudeScript_Entry::
	lockall
	goto Route29_Johto_CatchingTutorialDudeScript

Route29_Johto_Route29YoungsterScript_Entry::
	lockall
	goto Route29_Johto_Route29YoungsterScript

Route29_Johto_Route29TeacherScript_Entry::
	lockall
	goto Route29_Johto_Route29TeacherScript

Route29_Johto_Route29FruitTree_Entry::
	lockall
	goto Route29_Johto_Route29FruitTree

Route29_Johto_Route29FisherScript_Entry::
	lockall
	goto Route29_Johto_Route29FisherScript

Route29_Johto_Route29CooltrainerMScript_Entry::
	lockall
	goto Route29_Johto_Route29CooltrainerMScript

Route29_Johto_TuscanyScript_Entry::
	lockall
	goto Route29_Johto_TuscanyScript

Route29_Johto_Route29Potion_Entry::
	lockall
	goto Route29_Johto_Route29Potion

Route29_Johto_Route29Sign1_Entry::
	lockall
	goto Route29_Johto_Route29Sign1

Route29_Johto_Route29Sign2_Entry::
	lockall
	goto Route29_Johto_Route29Sign2

Route29_Johto_Route29Tutorial1_Entry::
	lockall
	goto Route29_Johto_Route29Tutorial1

Route29_Johto_Route29Tutorial2_Entry::
	lockall
	goto Route29_Johto_Route29Tutorial2


Route29_Johto_Route29Tutorial1:
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Route29_Johto_DudeMovementData1a
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	setflag FLAG_JOHTO_DUDE_TALKED_TO_YOU
	message Route29_Johto_CatchingTutorialIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route29_Johto_Script_RefusedTutorial1
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route29_Johto_DudeMovementData1b
	applymovement 1, Route29_Johto_DudeMovementData1b
	waitmovement 1
	setwildbattle SPECIES_RATTATA, 5
	@ TODO unsupported: catchtutorial BATTLETYPE_TUTORIAL
	goto Johto_EventScript_Unimplemented

Route29_Johto_Route29Tutorial2:
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Route29_Johto_DudeMovementData2a
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	setflag FLAG_JOHTO_DUDE_TALKED_TO_YOU
	message Route29_Johto_CatchingTutorialIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route29_Johto_Script_RefusedTutorial2
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route29_Johto_DudeMovementData2b
	applymovement 1, Route29_Johto_DudeMovementData2b
	waitmovement 1
	setwildbattle SPECIES_RATTATA, 5
	@ TODO unsupported: catchtutorial BATTLETYPE_TUTORIAL
	goto Johto_EventScript_Unimplemented

Route29_Johto_Script_RefusedTutorial1:
	message Route29_Johto_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Route29_Johto_DudeMovementData1b
	waitmovement 1
	setvar VAR_JOHTO_SCENE_ROUTE_29, 0
	releaseall
	end

Route29_Johto_Script_RefusedTutorial2:
	message Route29_Johto_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Route29_Johto_DudeMovementData2b
	waitmovement 1
	setvar VAR_JOHTO_SCENE_ROUTE_29, 0
	releaseall
	end

Route29_Johto_CatchingTutorialDudeScript:
	faceplayer
	setvar VAR_RESULT, 20
	goto_if_eq VAR_RESULT, 0, Route29_Johto_CatchingTutorialDudeScript_BoxFull
	goto_if_set FLAG_JOHTO_LEARNED_TO_CATCH_POKEMON, Route29_Johto_CatchingTutorialDudeScript_BoxFull
	goto_if_unset FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, Route29_Johto_CatchingTutorialDudeScript_BoxFull
	message Route29_Johto_CatchingTutorialRepeatText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route29_Johto_CatchingTutorialDudeScript_Declined
	closemessage
	setwildbattle SPECIES_RATTATA, 5
	@ TODO unsupported: catchtutorial BATTLETYPE_TUTORIAL
	goto Johto_EventScript_Unimplemented

Route29_Johto_CatchingTutorialDudeScript_BoxFull:
	message Route29_Johto_CatchingTutorialBoxFullText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_CatchingTutorialDudeScript_Declined:
	message Route29_Johto_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29YoungsterScript:
	faceplayer
	message Route29_Johto_Route29YoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29TeacherScript:
	faceplayer
	message Route29_Johto_Route29TeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29FisherScript:
	faceplayer
	message Route29_Johto_Route29FisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29CooltrainerMScript:
	faceplayer
	setvar VAR_0x8004, 2
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, Route29_Johto_Route29CooltrainerMScript_day_morn
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, Route29_Johto_Route29CooltrainerMScript_nite

Route29_Johto_Route29CooltrainerMScript_day_morn:
	message Route29_Johto_Route29CooltrainerMText_WaitingForNight
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29CooltrainerMScript_nite:
	message Route29_Johto_Route29CooltrainerMText_WaitingForMorning
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_TuscanyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_PINK_BOW_FROM_TUSCANY, Route29_Johto_TuscanyTuesdayScript
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 2, Route29_Johto_TuscanyNotTuesdayScript
	goto_if_set FLAG_JOHTO_MET_TUSCANY_OF_TUESDAY, Route29_Johto_TuscanyScript_MetTuscany
	message Route29_Johto_MeetTuscanyText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_TUSCANY_OF_TUESDAY

Route29_Johto_TuscanyScript_MetTuscany:
	message Route29_Johto_TuscanyGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_PINK_BOW
	goto_if_eq VAR_RESULT, 0, Route29_Johto_TuscanyDoneScript
	setflag FLAG_JOHTO_GOT_PINK_BOW_FROM_TUSCANY
	message Route29_Johto_TuscanyGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_TuscanyTuesdayScript:
	message Route29_Johto_TuscanyTuesdayText
	waitmessage
	waitbuttonpress

Route29_Johto_TuscanyDoneScript:
	closemessage
	releaseall
	end

Route29_Johto_TuscanyNotTuesdayScript:
	message Route29_Johto_TuscanyNotTuesdayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29Sign1:
	message Route29_Johto_Route29Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29Sign2:
	message Route29_Johto_Route29Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29_Johto_Route29FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_29, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ORAN_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_29
	releaseall
	end

Route29_Johto_Route29Potion:
	finditem ITEM_POTION
	releaseall
	end

Route29_Johto_Route29TuscanyCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_ZEPHYRBADGE, Route29_Johto_Route29TuscanyCallback_DoesTuscanyAppear_Cb

Route29_Johto_Route29TuscanyCallback_TuscanyDisappears_Cb:
	setflag FLAG_JOHTO_ROUTE_29_TUSCANY_OF_TUESDAY
	return

Route29_Johto_Route29TuscanyCallback_DoesTuscanyAppear_Cb:
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 2, Route29_Johto_Route29TuscanyCallback_TuscanyDisappears_Cb
	clearflag FLAG_JOHTO_ROUTE_29_TUSCANY_OF_TUESDAY
	return

Route29_Johto_DudeMovementData1a:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route29_Johto_DudeMovementData2a:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route29_Johto_DudeMovementData1b:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route29_Johto_DudeMovementData2b:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

Route29_Johto_CatchingTutorialBoxFullText:
	.string "POKéMON hide in\n"
	.string "the grass. Who"
	.string "\pknows when they'll\n"
	.string "pop out…$"

Route29_Johto_CatchingTutorialIntroText:
	.string "I've seen you a\n"
	.string "couple times. How"
	.string "\pmany POKéMON have\n"
	.string "you caught?"
	.string "\pWould you like me\n"
	.string "to show you how to\l"
	.string "catch POKéMON?$"

Route29_Johto_CatchingTutorialDeclinedText:
	.string "Oh. Fine, then."
	.string "\pAnyway, if you\n"
	.string "want to catch"
	.string "\pPOKéMON, you have\n"
	.string "to walk a lot.$"

Route29_Johto_CatchingTutorialRepeatText:
	.string "Huh? You want me\n"
	.string "to show you how to\l"
	.string "catch POKéMON?$"

Route29_Johto_Route29YoungsterText:
	.string "Yo. How are your\n"
	.string "POKéMON?"
	.string "\pIf they're weak\n"
	.string "and not ready for"
	.string "\pbattle, keep out\n"
	.string "of the grass.$"

Route29_Johto_Route29TeacherText:
	.string "See those ledges?\n"
	.string "It's scary to jump\l"
	.string "off them."
	.string "\pBut you can go to\n"
	.string "NEW BARK without"
	.string "\pwalking through\n"
	.string "the grass.$"

Route29_Johto_Route29FisherText:
	.string "I wanted to take a\n"
	.string "break, so I saved"
	.string "\pto record my\n"
	.string "progress.$"

Route29_Johto_Route29CooltrainerMText_WaitingForNight:
	.string "I'm waiting for\n"
	.string "POKéMON that"
	.string "\pappear only at\n"
	.string "night.$"

Route29_Johto_Route29CooltrainerMText_WaitingForMorning:
	.string "I'm waiting for\n"
	.string "POKéMON that"
	.string "\pappear only in the\n"
	.string "morning.$"

Route29_Johto_MeetTuscanyText:
	.string "TUSCANY: I do be-\n"
	.string "lieve that this is"
	.string "\pthe first time\n"
	.string "we've met?"
	.string "\pPlease allow me to\n"
	.string "introduce myself."
	.string "\pI am TUSCANY of\n"
	.string "Tuesday.$"

Route29_Johto_TuscanyGivesGiftText:
	.string "By way of intro-\n"
	.string "duction, please"
	.string "\paccept this gift,\n"
	.string "a PINK BOW.$"

Route29_Johto_TuscanyGaveGiftText:
	.string "TUSCANY: Wouldn't\n"
	.string "you agree that it\l"
	.string "is most adorable?"
	.string "\pIt strengthens\n"
	.string "normal-type moves."
	.string "\pI am certain it\n"
	.string "will be of use.$"

Route29_Johto_TuscanyTuesdayText:
	.string "TUSCANY: Have you\n"
	.string "met MONICA, my\l"
	.string "older sister?"
	.string "\pOr my younger\n"
	.string "brother, WESLEY?"
	.string "\pI am the second of\n"
	.string "seven children.$"

Route29_Johto_TuscanyNotTuesdayText:
	.string "TUSCANY: Today is\n"
	.string "not Tuesday. That\l"
	.string "is unfortunate…$"

Route29_Johto_Route29Sign1Text:
	.string "ROUTE 29"
	.string "\pCHERRYGROVE CITY -\n"
	.string "NEW BARK TOWN$"

Route29_Johto_Route29Sign2Text:
	.string "ROUTE 29"
	.string "\pCHERRYGROVE CITY -\n"
	.string "NEW BARK TOWN$"

Route29_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_29_0, Route29_Johto_CutTree0_Keep
	setmetatile 30, 8, 514, 0
	setmetatile 31, 8, 514, 0
	setmetatile 30, 9, 514, 0
	setmetatile 31, 9, 591, 0
Route29_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_29_1, Route29_Johto_CutTree1_Keep
	setmetatile 20, 10, 514, 0
	setmetatile 21, 10, 591, 0
	setmetatile 20, 11, 514, 0
	setmetatile 21, 11, 514, 0
Route29_Johto_CutTree1_Keep:
	end

Route29_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route29_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_29_0
	setmetatile 30, 8, 514, 0
	setmetatile 31, 8, 514, 0
	setmetatile 30, 9, 514, 0
	setmetatile 31, 9, 591, 0
	special DrawWholeMapView
Route29_Johto_CutTree0_Done:
	releaseall
	end

Route29_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route29_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_29_1
	setmetatile 20, 10, 514, 0
	setmetatile 21, 10, 591, 0
	setmetatile 20, 11, 514, 0
	setmetatile 21, 11, 514, 0
	special DrawWholeMapView
Route29_Johto_CutTree1_Done:
	releaseall
	end
