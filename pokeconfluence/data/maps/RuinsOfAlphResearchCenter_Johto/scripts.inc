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
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist1Script:
	faceplayer
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterScientist2Script:
	faceplayer
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer:
	goto_if_set FLAG_JOHTO_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_SkipChecking
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputer_SkipChecking:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter:
	goto_if_set FLAG_JOHTO_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_SkipChecking
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinter_SkipChecking:
	message RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinterText_DoesntWork
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
	@ TODO unsupported: ifequal SCENE_RUINSOFALPHRESEARCHCENTER_GET_UNOWN_DEX, .ShowScientist
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

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterComputerText:
	.string "RUINS OF ALPH"
	.string "\pExploration\n"
	.string "Year 10$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterPrinterText_DoesntWork:
	.string "This doesn't seem\n"
	.string "to work yet.$"

RuinsOfAlphResearchCenter_Johto_RuinsOfAlphResearchCenterAcademicBooksText:
	.string "There are many\n"
	.string "academic books."
	.string "\pAncient Ruins…\n"
	.string "Mysteries of the\l"
	.string "Ancients…$"
