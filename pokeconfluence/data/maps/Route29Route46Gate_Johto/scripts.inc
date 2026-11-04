Route29Route46Gate_Johto_MapScripts::
	.byte 0

Route29Route46Gate_Johto_Route29Route46GateOfficerScript_Entry::
	lockall
	goto Route29Route46Gate_Johto_Route29Route46GateOfficerScript

Route29Route46Gate_Johto_Route29Route46GateYoungsterScript_Entry::
	lockall
	goto Route29Route46Gate_Johto_Route29Route46GateYoungsterScript


Route29Route46Gate_Johto_Route29Route46GateOfficerScript:
	faceplayer
	message Route29Route46Gate_Johto_Route29Route46GateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29Route46Gate_Johto_Route29Route46GateYoungsterScript:
	faceplayer
	message Route29Route46Gate_Johto_Route29Route46GateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route29Route46Gate_Johto_Route29Route46GateOfficerText:
	.string "You can't climb\n"
	.string "ledges."
	.string "\pBut you can jump\n"
	.string "down from them to\l"
	.string "take a shortcut.$"

Route29Route46Gate_Johto_Route29Route46GateYoungsterText:
	.string "Different kinds of\n"
	.string "POKéMON appear\l"
	.string "past here."
	.string "\pIf you want to\n"
	.string "catch them all,"
	.string "\pyou have to look\n"
	.string "everywhere.$"
