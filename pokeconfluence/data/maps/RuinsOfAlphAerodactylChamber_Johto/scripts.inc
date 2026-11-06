RuinsOfAlphAerodactylChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlphAerodactylChamber_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphAerodactylChamber_Johto_OnFrame
	.byte 0

RuinsOfAlphAerodactylChamber_Johto_OnLoad:
	call RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_Cb
	end

RuinsOfAlphAerodactylChamber_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_AERODACTYL_CHAMBER, 0, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene_Entry
	.2byte 0

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberAncientReplica_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberAncientReplica

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberPuzzle_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberPuzzle

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberDescriptionSign_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberDescriptionSign

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternLeft_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternLeft

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRight_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRight

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene_Entry::
	lockall
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene


RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene:
	checkitem ITEM_FIELD_KIT, 1
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphAerodactylChamber_Johto_AerodactylChamber_Open
	checkitem ITEM_HM05, 1
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphAerodactylChamber_Johto_AerodactylChamber_Open
	checkfieldmove FIELD_MOVE_FLASH
	goto_if_eq VAR_RESULT, PARTY_SIZE, RuinsOfAlphAerodactylChamber_Johto_AerodactylChamber_Skip
RuinsOfAlphAerodactylChamber_Johto_AerodactylChamber_Open:
	setflag FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER
RuinsOfAlphAerodactylChamber_Johto_AerodactylChamber_Skip:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene_OpenWall
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberCheckWallScene_OpenWall:
	goto RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallOpenScript

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallOpenScript:
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
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_AERODACTYL_CHAMBER, 1
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberPuzzle:
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 1
	closemessage
	goto_if_ne VAR_RESULT, 0, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberPuzzle_PuzzleComplete
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberPuzzle_PuzzleComplete:
	setflag FLAG_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_JOHTO_SOLVED_AERODACTYL_PUZZLE
	setflag FLAG_JOHTO_ENGINE_UNLOCKED_UNOWNS_S_TO_W
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
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_PIN
	waitse
	delay 20
	warp MAP_JOHTO_RUINS_OF_ALPH_INNER_CHAMBER, 10, 13
	waitstate
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberAncientReplica:
	message RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberDescriptionSign:
	message RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternLeft:
	message RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRight_WallOpen
	message RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRight_WallOpen:
	message RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_Cb:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_WallOpen_Cb
	setmetatile 4, 0, 552, 1
	setmetatile 5, 0, 529, 1
	setmetatile 4, 1, 521, 0
	setmetatile 5, 1, 521, 0
	special DrawWholeMapView

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_WallOpen_Cb:
	goto_if_unset FLAG_JOHTO_SOLVED_AERODACTYL_PUZZLE, RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_FloorClosed_Cb
	return

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_FloorClosed_Cb:
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

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberSkyfallTopMovement:
	walk_fast_down
	step_end

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternLeftText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallPatternRightText:
	.string "Patterns appeared\n"
	.string "on the walls…$"

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberWallHoleText:
	.string "There's a big hole\n"
	.string "in the wall!$"

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberAncientReplicaText:
	.string "It's a replica of\n"
	.string "an ancient POKé-\l"
	.string "MON.$"

RuinsOfAlphAerodactylChamber_Johto_RuinsOfAlphAerodactylChamberDescriptionText:
	.string "This flying POKé-\n"
	.string "MON attacked its"
	.string "\pprey with saw-like\n"
	.string "fangs.$"
