EcruteakLugiaSpeechHouse_Johto_MapScripts::
	.byte 0

EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseGrampsScript_Entry::
	lockall
	goto EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseGrampsScript

EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseYoungsterScript_Entry::
	lockall
	goto EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseYoungsterScript

EcruteakLugiaSpeechHouse_Johto_LugiaSpeechHouseRadio_Entry::
	lockall
	goto EcruteakLugiaSpeechHouse_Johto_LugiaSpeechHouseRadio


EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseGrampsScript:
	faceplayer
	message EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseYoungsterScript:
	faceplayer
	message EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakLugiaSpeechHouse_Johto_LugiaSpeechHouseRadio:
	goto Johto_Std_Radio2Script

EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseGrampsText:
	.string "This happened when\n"
	.string "I was young."
	.string "\pThe sky suddenly\n"
	.string "turned black. A"
	.string "\pgiant flying POKé-\n"
	.string "MON was blocking\l"
	.string "out the sun."
	.string "\pI wonder what that\n"
	.string "POKéMON was? "
	.string "\pIt was like a bird\n"
	.string "and a dragon.$"

EcruteakLugiaSpeechHouse_Johto_EcruteakLugiaSpeechHouseYoungsterText:
	.string "Is there really a\n"
	.string "POKéMON that big?"
	.string "\pIf it exists, it\n"
	.string "must be powerful.$"
