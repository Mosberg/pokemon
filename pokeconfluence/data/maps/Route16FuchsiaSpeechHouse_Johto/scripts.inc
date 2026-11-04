Route16FuchsiaSpeechHouse_Johto_MapScripts::
	.byte 0

Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseSuperNerdScript_Entry::
	lockall
	goto Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseSuperNerdScript

Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseBookshelf_Entry::
	lockall
	goto Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseBookshelf


Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseSuperNerdScript:
	faceplayer
	message Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

Route16FuchsiaSpeechHouse_Johto_Route16FuchsiaSpeechHouseSuperNerdText:
	.string "If you cruise down\n"
	.string "CYCLING ROAD, you"
	.string "\pwill end up in\n"
	.string "FUCHSIA CITY.$"
