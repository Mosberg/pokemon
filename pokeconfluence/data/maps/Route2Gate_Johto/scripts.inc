Route2Gate_Johto_MapScripts::
	.byte 0

Route2Gate_Johto_Route2GateScientistScript_Entry::
	lockall
	goto Route2Gate_Johto_Route2GateScientistScript


Route2Gate_Johto_Route2GateScientistScript:
	faceplayer
	message Route2Gate_Johto_Route2GateScientistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2Gate_Johto_Route2GateScientistText:
	.string "Are you {PLAYER}?"
	.string "\pI work as PROF.\n"
	.string "OAK's AIDE."
	.string "\pI had no idea that\n"
	.string "you were out here."
	.string "\pPROF.OAK's LAB is\n"
	.string "nearby in PALLET\l"
	.string "TOWN.$"
