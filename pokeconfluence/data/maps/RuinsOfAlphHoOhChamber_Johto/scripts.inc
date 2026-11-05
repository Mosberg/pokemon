RuinsOfAlphHoOhChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlphHoOhChamber_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphHoOhChamber_Johto_OnFrame
	.byte 0

RuinsOfAlphHoOhChamber_Johto_OnLoad:
	call RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_Cb
	end

RuinsOfAlphHoOhChamber_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_HO_OH_CHAMBER, 0, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene_Entry
	.2byte 0

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberAncientReplica_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberAncientReplica

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberDescriptionSign_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberDescriptionSign

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternLeft_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternLeft

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene_Entry::
	lockall
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene


RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene:
	setvar VAR_0x8004, SPECIES_HO_OH
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, 0, RuinsOfAlphHoOhChamber_Johto_HoOhChamber_Skip
	setflag FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER
	RuinsOfAlphHoOhChamber_Johto_HoOhChamber_Skip:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene_OpenWall
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberCheckWallScene_OpenWall:
	goto RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallOpenScript

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallOpenScript:
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
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_HO_OH_CHAMBER, 1
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle:
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 1
	closemessage
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle_PuzzleComplete
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle_PuzzleComplete:
	setflag FLAG_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_JOHTO_SOLVED_HO_OH_PUZZLE
	setflag FLAG_JOHTO_ENGINE_UNLOCKED_UNOWNS_X_TO_Z
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
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_PIN
	waitse
	delay 20
	warp MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER, 10, 13
	waitstate
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberAncientReplica:
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberDescriptionSign:
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternLeft:
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight_WallOpen
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight_WallOpen:
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_Cb:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_WallOpen_Cb
	setmetatile 4, 0, 552, 1
	setmetatile 5, 0, 529, 1
	setmetatile 4, 1, 521, 0
	setmetatile 5, 1, 521, 0
	special DrawWholeMapView

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_WallOpen_Cb:
	goto_if_unset FLAG_JOHTO_SOLVED_HO_OH_PUZZLE, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_FloorClosed_Cb
	return

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberHiddenDoorsCallback_FloorClosed_Cb:
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

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberSkyfallTopMovement:
	step_end

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternLeftText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRightText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallHoleText:
	.string "There's a big hole\n"
	.string "in the wall!$"

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberAncientReplicaText:
	.string "It's a replica of\n"
	.string "an ancient POKé-\l"
	.string "MON.$"

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberDescriptionText:
	.string "A POKéMON that\n"
	.string "flew gracefully on"
	.string "\prainbow-colored\n"
	.string "wings.$"
