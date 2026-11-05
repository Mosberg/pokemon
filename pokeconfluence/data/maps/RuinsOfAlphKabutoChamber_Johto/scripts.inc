RuinsOfAlphKabutoChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlphKabutoChamber_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphKabutoChamber_Johto_OnFrame
	.byte 0

RuinsOfAlphKabutoChamber_Johto_OnLoad:
	call RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_Cb
	end

RuinsOfAlphKabutoChamber_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_KABUTO_CHAMBER, 0, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene_Entry
	.2byte 0

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberReceptionistScript_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberReceptionistScript

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberAncientReplica_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberAncientReplica

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberPuzzle_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberPuzzle

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberDescriptionSign_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberDescriptionSign

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternLeft_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternLeft

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene_Entry::
	lockall
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene


RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene_OpenWall
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberCheckWallScene_OpenWall:
	goto RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallOpenScript

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallOpenScript:
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 30
	playse SE_M_STRENGTH
	setmetatile 4, 0, 553, 0
	setmetatile 5, 0, 529, 1
	setmetatile 4, 1, 521, 0
	setmetatile 5, 1, 521, 0
	special DrawWholeMapView
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_KABUTO_CHAMBER, 1
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberReceptionistScript:
	faceplayer
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberPuzzle:
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 1
	closemessage
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberPuzzle_PuzzleComplete
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberPuzzle_PuzzleComplete:
	setflag FLAG_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_JOHTO_SOLVED_KABUTO_PUZZLE
	setflag FLAG_JOHTO_ENGINE_UNLOCKED_UNOWNS_A_TO_K
	setflag FLAG_JOHTO_RUINS_OF_ALPH_KABUTO_CHAMBER_RECEPTIONIST
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	setmetatile 2, 2, 513, 1
	setmetatile 3, 2, 514, 1
	setmetatile 2, 3, 515, 1
	setmetatile 3, 3, 539, 1
	special DrawWholeMapView
	setmetatile 4, 2, 517, 1
	setmetatile 5, 2, 513, 1
	setmetatile 4, 3, 539, 1
	setmetatile 5, 3, 515, 1
	special DrawWholeMapView
	playse SE_M_STRENGTH
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_PIN
	waitse
	delay 20
	warp MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER, 10, 13
	waitstate
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript:
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 26, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_AllUnownCaught
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_WallOpen
	goto_if_unset FLAG_JOHTO_SOLVED_KABUTO_PUZZLE, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_PuzzleIncomplete
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistTremorText
	waitmessage
	waitbuttonpress

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_PuzzleIncomplete:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistCrypticText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Up
	waitmovement 2
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_WallOpen:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript_AllUnownCaught:
	message Johto_Std_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberAncientReplica:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberDescriptionSign:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternLeft:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_Cb:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_WallOpen_Cb
	setmetatile 4, 0, 552, 1
	setmetatile 5, 0, 529, 1
	setmetatile 4, 1, 521, 0
	setmetatile 5, 1, 521, 0
	special DrawWholeMapView

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_WallOpen_Cb:
	goto_if_unset FLAG_JOHTO_SOLVED_KABUTO_PUZZLE, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_FloorClosed_Cb
	return

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberHiddenDoorsCallback_FloorClosed_Cb:
	setmetatile 2, 2, 513, 1
	setmetatile 3, 2, 514, 1
	setmetatile 2, 3, 515, 1
	setmetatile 3, 3, 516, 0
	special DrawWholeMapView
	setmetatile 4, 2, 517, 1
	setmetatile 5, 2, 513, 1
	setmetatile 4, 3, 518, 0
	setmetatile 5, 3, 515, 1
	special DrawWholeMapView
	return

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberSkyfallTopMovement:
	walk_fast_down
	step_end

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberReceptionistText:
	.string "Welcome to this\n"
	.string "chamber."
	.string "\pThere are sliding\n"
	.string "panels that depict"
	.string "\pa POKéMON drawn by\n"
	.string "the ancients."
	.string "\pSlide the panels\n"
	.string "around to form the\l"
	.string "picture."
	.string "\pTo the right is a\n"
	.string "description of the\l"
	.string "POKéMON."
	.string "\pScientists in the\n"
	.string "back are examining"
	.string "\psome newly found\n"
	.string "patterns.$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistCrypticText:
	.string "Recently, strange,\n"
	.string "cryptic patterns\l"
	.string "have appeared."
	.string "\pIt's odd. They\n"
	.string "weren't here a\l"
	.string "little while ago…"
	.string "\pYou should take a\n"
	.string "look at the walls.$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistHoleText:
	.string "Ah! Here's another\n"
	.string "huge hole!"
	.string "\pIt's big enough to\n"
	.string "go through!$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistTremorText:
	.string "That tremor was\n"
	.string "pretty scary!"
	.string "\pBut I'm more\n"
	.string "concerned about\l"
	.string "this wall here…$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternLeftText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRightText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallHoleText:
	.string "There's a big hole\n"
	.string "in the wall!$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberAncientReplicaText:
	.string "It's a replica of\n"
	.string "an ancient POKé-\l"
	.string "MON.$"

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberDescriptionText:
	.string "A POKéMON that hid\n"
	.string "on the sea floor."
	.string "\pEyes on its back\n"
	.string "scanned the area.$"
