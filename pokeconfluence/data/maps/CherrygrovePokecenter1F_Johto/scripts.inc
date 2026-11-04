CherrygrovePokecenter1F_Johto_MapScripts::
	.byte 0

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FNurseScript_Entry::
	lockall
	goto CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FNurseScript

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FFisherScript_Entry::
	lockall
	goto CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FFisherScript

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FGentlemanScript_Entry::
	lockall
	goto CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FGentlemanScript

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherScript_Entry::
	lockall
	goto CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherScript


CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_CHERRYGROVE_CITY
	goto Johto_Std_PokecenterNurseScript

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FFisherScript:
	faceplayer
	message CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FGentlemanScript:
	faceplayer
	message CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherScript_CommCenterOpen
	message CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherScript_CommCenterOpen:
	message CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherText_CommCenterOpen
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FFisherText:
	.string "It's great. I can\n"
	.string "store any number"
	.string "\pof POKéMON, and\n"
	.string "it's all free.$"

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FGentlemanText:
	.string "That PC is free\n"
	.string "for any trainer\l"
	.string "to use.$"

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherText:
	.string "The COMMUNICATION\n"
	.string "CENTER upstairs\l"
	.string "was just built."
	.string "\pBut they're still\n"
	.string "finishing it up.$"

CherrygrovePokecenter1F_Johto_CherrygrovePokecenter1FTeacherText_CommCenterOpen:
	.string "The COMMUNICATION\n"
	.string "CENTER upstairs\l"
	.string "was just built."
	.string "\pI traded POKéMON\n"
	.string "there already!$"
