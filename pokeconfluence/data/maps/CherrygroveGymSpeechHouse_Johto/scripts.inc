CherrygroveGymSpeechHouse_Johto_MapScripts::
	.byte 0

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHousePokefanMScript_Entry::
	lockall
	goto CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHousePokefanMScript

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBugCatcherScript_Entry::
	lockall
	goto CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBugCatcherScript

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBookshelf_Entry::
	lockall
	goto CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBookshelf


CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHousePokefanMScript:
	faceplayer
	message CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHousePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBugCatcherScript:
	faceplayer
	message CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHousePokefanMText:
	.string "You're trying to\n"
	.string "see how good you"
	.string "\pare as a POKéMON\n"
	.string "trainer?"
	.string "\pYou better visit\n"
	.string "the POKéMON GYMS"
	.string "\pall over JOHTO and\n"
	.string "collect BADGES.$"

CherrygroveGymSpeechHouse_Johto_CherrygroveGymSpeechHouseBugCatcherText:
	.string "When I get older,\n"
	.string "I'm going to be a\l"
	.string "GYM LEADER!"
	.string "\pI make my POKéMON\n"
	.string "battle with my"
	.string "\pfriend's to make\n"
	.string "them tougher!$"
