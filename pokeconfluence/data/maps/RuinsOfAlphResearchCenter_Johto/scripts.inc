RuinsOfAlphResearchCenter_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlphResearchCenter_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphResearchCenter_Johto_OnFrame
	.byte 0

RuinsOfAlphResearchCenter_Johto_OnTransition:
	call RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientistCallback_Cb
	end

RuinsOfAlphResearchCenter_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 1, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterGetUnownDexScript_Entry
	.2byte 0

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Script_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Script

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterBookshelf_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterBookshelf

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterGetUnownDexScript_Entry::
	lockall
	goto RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterGetUnownDexScript


RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterGetUnownDexScript:
	applymovement 3, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterApproachesComputerMovement
	waitmovement 3
	playse SE_PC_ON
	delay 60
	playse SE_PIN
	delay 30
	playse SE_PIN
	delay 30
	playse SE_PIN
	delay 30
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterModifiedDexText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterApproachesPlayerMovement
	waitmovement 3
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterDexUpgradedText
	waitmessage
	playse SE_PIN
	waitse
	setflag FLAG_JOHTO_ENGINE_UNOWN_DEX
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterLeavesPlayerMovement
	waitmovement 3
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 0
	fadedefaultbgm
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Script:
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 26, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Script_PrinterAvailable
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Script_PrinterAvailable:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3_PrinterAvailable
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script:
	faceplayer
	special JohtoGetUnownCaughtCount
	goto_if_ge VAR_RESULT, 26, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_GotAllUnown
	goto_if_set FLAG_JOHTO_ENGINE_UNOWN_DEX, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_GotUnownDex
	goto_if_set FLAG_JOHTO_MADE_UNOWN_APPEAR_IN_RUINS, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_UnownAppeared
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_UnownAppeared:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_UnownAppeared
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_GotUnownDex:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_GotUnownDex
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script_GotAllUnown:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_JOHTO_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script:
	faceplayer
	special JohtoGetUnownCaughtCount
	goto_if_ge VAR_RESULT, 26, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script_GotAllUnown
	goto_if_set FLAG_JOHTO_MADE_UNOWN_APPEAR_IN_RUINS, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script_UnownAppeared
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script_UnownAppeared:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text_UnownAppeared
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script_GotAllUnown:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer:
	goto_if_set FLAG_JOHTO_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_SkipChecking
	special JohtoGetUnownCaughtCount
	goto_if_ge VAR_RESULT, 26, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_GotAllUnown

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_SkipChecking:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_GotAllUnown:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter:
	goto_if_set FLAG_JOHTO_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_SkipChecking
	special JohtoGetUnownCaughtCount
	goto_if_ge VAR_RESULT, 26, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_PrinterAvailable

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_SkipChecking:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinterText_DoesntWork
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_PrinterAvailable:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterUnownPrinterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterBookshelf:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterAcademicBooksText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientistCallback_Cb:
	copyvar VAR_RESULT, VAR_JOHTO_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER
	goto_if_eq VAR_RESULT, 1, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientistCallback_ShowScientist_Cb
	return

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientistCallback_ShowScientist_Cb:
	setobjectxyperm 3, 3, 7
	clearflag FLAG_JOHTO_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST
	return

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterApproachesComputerMovement:
	walk_up
	walk_up
	walk_left
	face_up
	step_end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterApproachesPlayerMovement:
	walk_down
	step_end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterLeavesPlayerMovement:
	walk_up
	step_end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterModifiedDexText:
	.string "Done!"
	.string "\pI modified your\n"
	.string "POKéDEX."
	.string "\pI added an\n"
	.string "optional POKéDEX"
	.string "\pto store UNOWN\n"
	.string "data."
	.string "\pIt records them in\n"
	.string "the sequence that\l"
	.string "they were caught.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterDexUpgradedText:
	.string "{PLAYER}'s POKéDEX\n"
	.string "was upgraded.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3Text:
	.string "The UNOWN you\n"
	.string "catch will all be\l"
	.string "recorded."
	.string "\pCheck to see how\n"
	.string "many kinds exist.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist3_PrinterAvailable:
	.string "You caught all the\n"
	.string "UNOWN variations?"
	.string "\pThat's a great\n"
	.string "achievement!"
	.string "\pI've set up the\n"
	.string "printer here for\l"
	.string "handling UNOWN."
	.string "\pFeel free to use\n"
	.string "it anytime.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text:
	.string "The RUINS are\n"
	.string "about 1500 years\l"
	.string "old."
	.string "\pBut it's not known\n"
	.string "why they were\l"
	.string "built--or by whom.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_GotUnownDex:
	.string "I wonder how many\n"
	.string "kinds of POKéMON\l"
	.string "are in the RUINS?$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_UnownAppeared:
	.string "POKéMON appeared\n"
	.string "in the RUINS?"
	.string "\pThat's incredible\n"
	.string "news!"
	.string "\pWe'll need to\n"
	.string "investigate this.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown:
	.string "Our investigation,\n"
	.string "with your help, is"
	.string "\pgiving us insight\n"
	.string "into the RUINS."
	.string "\pThe RUINS appear\n"
	.string "to have been built"
	.string "\pas a habitat for\n"
	.string "POKéMON.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text:
	.string "There are odd pat-\n"
	.string "terns drawn on the"
	.string "\pwalls of the\n"
	.string "RUINS."
	.string "\pThey must be the\n"
	.string "keys for unravel-\l"
	.string "ing the mystery\l"
	.string "of the RUINS.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text_UnownAppeared:
	.string "The strange POKé-\n"
	.string "MON you saw in the\l"
	.string "RUINS?"
	.string "\pThey appear to be\n"
	.string "very much like the"
	.string "\pdrawings on the\n"
	.string "walls there."
	.string "\pHmm…"
	.string "\pThat must mean\n"
	.string "there are many\l"
	.string "kinds of them…$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Text_GotAllUnown:
	.string "Why did those\n"
	.string "ancient patterns"
	.string "\pappear on the wall\n"
	.string "now?"
	.string "\pThe mystery\n"
	.string "deepens…$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText:
	.string "RUINS OF ALPH"
	.string "\pExploration\n"
	.string "Year 10$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText_GotAllUnown:
	.string "Mystery POKéMON\n"
	.string "Name: UNOWN"
	.string "\pA total of NUM_UNOWN\n"
	.string "kinds found.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinterText_DoesntWork:
	.string "This doesn't seem\n"
	.string "to work yet.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterUnownPrinterText:
	.string "UNOWN may be\n"
	.string "printed out.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterAcademicBooksText:
	.string "There are many\n"
	.string "academic books."
	.string "\pAncient Ruins…\n"
	.string "Mysteries of the\l"
	.string "Ancients…$"
