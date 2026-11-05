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
	@ TODO unsupported: special HoOhChamber
	goto Johto_EventScript_Unimplemented

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberPuzzle:
	setvar VAR_RESULT, 0
	@ TODO unsupported: special UnownPuzzle
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special DisplayUnownWords
	goto Johto_EventScript_Unimplemented

RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER, RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRight_WallOpen
	message RuinsOfAlphHoOhChamber_Johto_RuinsOfAlphHoOhChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	@ TODO unsupported: special DisplayUnownWords
	goto Johto_EventScript_Unimplemented

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
