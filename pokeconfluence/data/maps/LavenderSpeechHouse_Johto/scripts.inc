LavenderSpeechHouse_Johto_MapScripts::
	.byte 0

LavenderSpeechHouse_Johto_LavenderSpeechHousePokefanFScript_Entry::
	lockall
	goto LavenderSpeechHouse_Johto_LavenderSpeechHousePokefanFScript

LavenderSpeechHouse_Johto_LavenderSpeechHouseBookshelf_Entry::
	lockall
	goto LavenderSpeechHouse_Johto_LavenderSpeechHouseBookshelf


LavenderSpeechHouse_Johto_LavenderSpeechHousePokefanFScript:
	faceplayer
	message LavenderSpeechHouse_Johto_LavenderSpeechHousePokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderSpeechHouse_Johto_LavenderSpeechHouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

LavenderSpeechHouse_Johto_LavenderSpeechHousePokefanFText:
	.string "LAVENDER is a\n"
	.string "tiny, quiet town"
	.string "\pat the foot of the\n"
	.string "mountains."
	.string "\pIt's gotten a bit\n"
	.string "busier since the"
	.string "\pRADIO TOWER was\n"
	.string "built.$"
