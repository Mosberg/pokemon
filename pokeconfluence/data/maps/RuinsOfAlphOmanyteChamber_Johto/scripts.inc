RuinsOfAlphOmanyteChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlphOmanyteChamber_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphOmanyteChamber_Johto_OnFrame
	.byte 0

RuinsOfAlphOmanyteChamber_Johto_OnLoad:
	call RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_Cb
	end

RuinsOfAlphOmanyteChamber_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_OMANYTE_CHAMBER, 0, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene_Entry
	.2byte 0

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberAncientReplica_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberAncientReplica

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberPuzzle_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberPuzzle

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberDescriptionSign_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberDescriptionSign

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternLeft_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternLeft

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRight_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRight

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene_Entry::
	lockall
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene


RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene:
	checkitem ITEM_WATER_STONE, 1
	goto_if_eq VAR_RESULT, 0, RuinsOfAlphOmanyteChamber_Johto_OmanyteChamber_Skip
	setflag FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER
	RuinsOfAlphOmanyteChamber_Johto_OmanyteChamber_Skip:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene_OpenWall
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberCheckWallScene_OpenWall:
	goto RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallOpenScript

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallOpenScript:
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
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_OMANYTE_CHAMBER, 1
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberPuzzle:
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 1
	closemessage
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberPuzzle_PuzzleComplete
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberPuzzle_PuzzleComplete:
	setflag FLAG_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_JOHTO_SOLVED_OMANYTE_PUZZLE
	setflag FLAG_JOHTO_ENGINE_UNLOCKED_UNOWNS_L_TO_R
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
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_PIN
	waitse
	delay 20
	warp MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER, 10, 13
	waitstate
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberAncientReplica:
	message RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberDescriptionSign:
	message RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternLeft:
	message RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRight_WallOpen
	message RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRight_WallOpen:
	message RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_Cb:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_WallOpen_Cb
	setmetatile 4, 0, 552, 1
	setmetatile 5, 0, 529, 1
	setmetatile 4, 1, 521, 0
	setmetatile 5, 1, 521, 0
	special DrawWholeMapView

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_WallOpen_Cb:
	goto_if_unset FLAG_JOHTO_SOLVED_OMANYTE_PUZZLE, RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_FloorClosed_Cb
	return

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_FloorClosed_Cb:
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

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberSkyfallTopMovement:
	step_end

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternLeftText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallPatternRightText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberWallHoleText:
	.string "There's a big hole\n"
	.string "in the wall!$"

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberAncientReplicaText:
	.string "It's a replica of\n"
	.string "an ancient POKé-\l"
	.string "MON.$"

RuinsOfAlphOmanyteChamber_Johto_RuinsOfAlphOmanyteChamberDescriptionText:
	.string "This POKéMON\n"
	.string "drifted in the"
	.string "\psea by twisting\n"
	.string "its ten tentacles.$"
