CeladonMansionRoof_Johto_MapScripts::
	.byte 0

CeladonMansionRoof_Johto_CeladonMansionRoofFisherScript_Entry::
	lockall
	goto CeladonMansionRoof_Johto_CeladonMansionRoofFisherScript

CeladonMansionRoof_Johto_CeladonMansionRoofGraffiti_Entry::
	lockall
	goto CeladonMansionRoof_Johto_CeladonMansionRoofGraffiti


CeladonMansionRoof_Johto_CeladonMansionRoofFisherScript:
	faceplayer
	message CeladonMansionRoof_Johto_CeladonMansionRoofFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansionRoof_Johto_CeladonMansionRoofGraffiti:
	message CeladonMansionRoof_Johto_CeladonMansionRoofGraffitiText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansionRoof_Johto_CeladonMansionRoofFisherText:
	.string "High places--I do\n"
	.string "love them so!"
	.string "\pI'd say the only\n"
	.string "thing that loves"
	.string "\pheights as much as\n"
	.string "me is smoke!$"

CeladonMansionRoof_Johto_CeladonMansionRoofGraffitiText:
	.string "There's graffiti\n"
	.string "on the wall…"
	.string "\p{PLAYER} added a\n"
	.string "moustache!$"
