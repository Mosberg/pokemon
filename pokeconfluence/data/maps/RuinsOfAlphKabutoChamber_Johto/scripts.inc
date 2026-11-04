RuinsOfAlphKabutoChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphKabutoChamber_Johto_OnFrame
	.byte 0

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
	@ TODO unsupported: sdefer RuinsOfAlphKabutoChamberWallOpenScript
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special UnownPuzzle
	goto Johto_EventScript_Unimplemented

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberScientistScript:
	faceplayer
	@ TODO unsupported: readvar VAR_UNOWNCOUNT
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special DisplayUnownWords
	goto Johto_EventScript_Unimplemented

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight:
	goto_if_set FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	@ TODO unsupported: special DisplayUnownWords
	goto Johto_EventScript_Unimplemented

RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen:
	message RuinsOfAlphKabutoChamber_Johto_RuinsOfAlphKabutoChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

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
