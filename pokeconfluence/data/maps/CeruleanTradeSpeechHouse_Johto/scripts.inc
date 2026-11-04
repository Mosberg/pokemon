CeruleanTradeSpeechHouse_Johto_MapScripts::
	.byte 0

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrannyScript_Entry::
	lockall
	goto CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrannyScript

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrampsScript_Entry::
	lockall
	goto CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrampsScript

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseRhydonScript_Entry::
	lockall
	goto CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseRhydonScript

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseZubatScript_Entry::
	lockall
	goto CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseZubatScript


CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrannyScript:
	faceplayer
	message CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrampsScript:
	faceplayer
	message CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseRhydonScript:
	message CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseRhydonText
	waitmessage
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseZubatScript:
	message CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseZubatText
	waitmessage
	playmoncry SPECIES_ZUBAT, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrannyText:
	.string "My husband lives\n"
	.string "happily with POKé-\l"
	.string "MON he got through\l"
	.string "trades.$"

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseGrampsText:
	.string "Ah… I'm so happy…$"

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseRhydonText:
	.string "KANGASKHAN: Garu\n"
	.string "garuu.$"

CeruleanTradeSpeechHouse_Johto_CeruleanTradeSpeechHouseZubatText:
	.string "ZUBAT: Zuba zubaa.$"
