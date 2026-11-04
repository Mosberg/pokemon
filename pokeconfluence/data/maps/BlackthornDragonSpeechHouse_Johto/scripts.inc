BlackthornDragonSpeechHouse_Johto_MapScripts::
	.byte 0

BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseGrannyScript_Entry::
	lockall
	goto BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseGrannyScript

BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseDratiniScript_Entry::
	lockall
	goto BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseDratiniScript


BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseGrannyScript:
	faceplayer
	message BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseDratiniScript:
	message BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseDratiniText
	waitmessage
	playmoncry SPECIES_DRATINI, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseGrannyText:
	.string "A clan of trainers\n"
	.string "who can freely"
	.string "\pcommand dragons\n"
	.string "live right here in\l"
	.string "BLACKTHORN."
	.string "\pAs a result, there\n"
	.string "are many legends"
	.string "\pabout dragons in\n"
	.string "this town.$"

BlackthornDragonSpeechHouse_Johto_BlackthornDragonSpeechHouseDratiniText:
	.string "DRATINI: Draa!$"
