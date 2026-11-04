EarlsPokemonAcademy_Johto_MapScripts::
	.byte 0

EarlsPokemonAcademy_Johto_AcademyEarl_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_AcademyEarl

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster1Script_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster1Script

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid1Script_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid1Script

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid2Script_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid2Script

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster2Script_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster2Script

EarlsPokemonAcademy_Johto_AcademyNotebook_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_AcademyNotebook

EarlsPokemonAcademy_Johto_AcademyBookshelf_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_AcademyBookshelf

EarlsPokemonAcademy_Johto_AcademyBlackboard_Entry::
	lockall
	goto EarlsPokemonAcademy_Johto_AcademyBlackboard


EarlsPokemonAcademy_Johto_AcademyEarl:
	applymovement 1, EarlsPokemonAcademy_Johto_AcademyEarlSpinMovement
	waitmovement 1
	faceplayer
	message EarlsPokemonAcademy_Johto_AcademyEarlIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyEarl_Part1
	message EarlsPokemonAcademy_Johto_AcademyEarlTeachHowToWinText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyEarl_Done

EarlsPokemonAcademy_Johto_AcademyEarl_Part1:
	message EarlsPokemonAcademy_Johto_AcademyEarlTeachMoreText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyEarl_Done
	message EarlsPokemonAcademy_Johto_AcademyEarlTeachHowToRaiseWellText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EarlsPokemonAcademy_Johto_AcademyEarl_Done:
	message EarlsPokemonAcademy_Johto_AcademyEarlNoMoreToTeachText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster1Script:
	faceplayer
	message EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid1Script:
	faceplayer
	message EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid1Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	releaseall
	end

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid2Script:
	faceplayer
	message EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid2Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Down
	waitmovement 4
	releaseall
	end

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster2Script:
	faceplayer
	message EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EarlsPokemonAcademy_Johto_AcademyBlackboard:
	message EarlsPokemonAcademy_Johto_AcademyBlackboardText
	waitmessage

EarlsPokemonAcademy_Johto_AcademyBlackboard_Loop:
	@ TODO unsupported: loadmenu .BlackboardMenuHeader
	goto Johto_EventScript_Unimplemented

EarlsPokemonAcademy_Johto_AcademyNotebook:
	message EarlsPokemonAcademy_Johto_AcademyNotebookText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyNotebook_Done
	message EarlsPokemonAcademy_Johto_AcademyNotebookText1
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyNotebook_Done
	message EarlsPokemonAcademy_Johto_AcademyNotebookText2
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EarlsPokemonAcademy_Johto_AcademyNotebook_Done
	message EarlsPokemonAcademy_Johto_AcademyNotebookText3
	waitmessage
	waitbuttonpress

EarlsPokemonAcademy_Johto_AcademyNotebook_Done:
	closemessage
	releaseall
	end

EarlsPokemonAcademy_Johto_AcademyBookshelf:
	goto Johto_Std_DifficultBookshelfScript

EarlsPokemonAcademy_Johto_AcademyEarlSpinMovement:
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end

EarlsPokemonAcademy_Johto_AcademyEarlIntroText:
	.string "EARL, I am!"
	.string "\pWonderful are\n"
	.string "POKéMON, yes!"
	.string "\pTeach you I will\n"
	.string "to be a better\l"
	.string "trainer!"
	.string "\pWhat you want to\n"
	.string "know? Want to be\l"
	.string "a winner is you?$"

EarlsPokemonAcademy_Johto_AcademyEarlTeachHowToWinText:
	.string "Good! Teach you,\n"
	.string "I will!"
	.string "\pIn battle, POKéMON\n"
	.string "top on list jump\l"
	.string "out first!"
	.string "\pChange order in\n"
	.string "list, make battle\l"
	.string "easy, maybe!"
	.string "\pMore from me you\n"
	.string "want to hear?$"

EarlsPokemonAcademy_Johto_AcademyEarlTeachMoreText:
	.string "So, want to know\n"
	.string "how to raise\l"
	.string "POKéMON well?$"

EarlsPokemonAcademy_Johto_AcademyEarlTeachHowToRaiseWellText:
	.string "Fine! Teach you,\n"
	.string "I will!"
	.string "\pIf POKéMON come\n"
	.string "out in battle even"
	.string "\pbriefly, some EXP.\n"
	.string "Points it gets."
	.string "\pAt top of list put\n"
	.string "weak POKéMON."
	.string "\pSwitch in battle\n"
	.string "quick!"
	.string "\pThis way, weak\n"
	.string "POKéMON strong\l"
	.string "become!$"

EarlsPokemonAcademy_Johto_AcademyEarlNoMoreToTeachText:
	.string "Oh! Smart student\n"
	.string "you are! Nothing\l"
	.string "more do I teach!"
	.string "\pGood to POKéMON\n"
	.string "you must be!$"

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster1Text:
	.string "I'm taking notes\n"
	.string "of the teacher's\l"
	.string "lecture."
	.string "\pI'd better copy\n"
	.string "the stuff on the\l"
	.string "blackboard too.$"

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid1Text:
	.string "I traded my best\n"
	.string "POKéMON to the\l"
	.string "guy beside me.$"

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyGameboyKid2Text:
	.string "Huh? The POKéMON I\n"
	.string "just got is hold-\l"
	.string "ing something!$"

EarlsPokemonAcademy_Johto_EarlsPokemonAcademyYoungster2Text:
	.string "A POKéMON holding\n"
	.string "a BERRY will heal\l"
	.string "itself in battle."
	.string "\pMany other items\n"
	.string "can be held by\l"
	.string "POKéMON…"
	.string "\pIt sure is tough\n"
	.string "taking notes…$"

EarlsPokemonAcademy_Johto_AcademyBlackboardText:
	.string "The blackboard\n"
	.string "describes POKéMON"
	.string "\pstatus changes in\n"
	.string "battle.$"

EarlsPokemonAcademy_Johto_AcademyNotebookText:
	.string "It's this kid's\n"
	.string "notebook…"
	.string "\pCatch POKéMON\n"
	.string "using POKé BALLS."
	.string "\pUp to six can be\n"
	.string "in your party."
	.string "\pKeep reading?$"

EarlsPokemonAcademy_Johto_AcademyNotebookText1:
	.string "Before throwing a\n"
	.string "POKé BALL, weaken\l"
	.string "the target first."
	.string "\pA poisoned or\n"
	.string "burned POKéMON is\l"
	.string "easier to catch."
	.string "\pKeep reading?$"

EarlsPokemonAcademy_Johto_AcademyNotebookText2:
	.string "Some moves may\n"
	.string "cause confusion."
	.string "\pConfusion may make\n"
	.string "a POKéMON attack\l"
	.string "itself."
	.string "\pLeaving battle\n"
	.string "clears up any\l"
	.string "confusion."
	.string "\pKeep reading?$"

EarlsPokemonAcademy_Johto_AcademyNotebookText3:
	.string "People who catch\n"
	.string "and use POKéMON"
	.string "\pin battle are\n"
	.string "POKéMON trainers."
	.string "\pThey are expected\n"
	.string "to visit POKéMON"
	.string "\pGYMS and defeat\n"
	.string "other trainers."
	.string "\pThe next page\n"
	.string "is… Blank!"
	.string "\pBoy: E-he-he…"
	.string "\pI haven't written\n"
	.string "anymore…$"
