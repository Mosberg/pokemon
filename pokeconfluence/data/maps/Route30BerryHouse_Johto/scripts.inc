Route30BerryHouse_Johto_MapScripts::
	.byte 0

Route30BerryHouse_Johto_Route30BerryHousePokefanMScript_Entry::
	lockall
	goto Route30BerryHouse_Johto_Route30BerryHousePokefanMScript

Route30BerryHouse_Johto_Route30BerryHouseBookshelf_Entry::
	lockall
	goto Route30BerryHouse_Johto_Route30BerryHouseBookshelf


Route30BerryHouse_Johto_Route30BerryHousePokefanMScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_BERRY_FROM_ROUTE_30_HOUSE, Route30BerryHouse_Johto_Route30BerryHousePokefanMScript_GotBerry
	message Route30BerryHouse_Johto_Route30BerrySpeechHouseMonEatBerriesText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, 0, Route30BerryHouse_Johto_Route30BerryHousePokefanMScript_NoRoom
	setflag FLAG_JOHTO_GOT_BERRY_FROM_ROUTE_30_HOUSE

Route30BerryHouse_Johto_Route30BerryHousePokefanMScript_GotBerry:
	message Route30BerryHouse_Johto_Route30BerrySpeechHouseCheckTreesText
	waitmessage
	waitbuttonpress

Route30BerryHouse_Johto_Route30BerryHousePokefanMScript_NoRoom:
	closemessage
	releaseall
	end

Route30BerryHouse_Johto_Route30BerryHouseBookshelf:
	goto Johto_Std_MagazineBookshelfScript

Route30BerryHouse_Johto_Route30BerrySpeechHouseMonEatBerriesText:
	.string "You know, POKéMON\n"
	.string "eat BERRIES."
	.string "\pWell, my POKéMON\n"
	.string "got healthier by\l"
	.string "eating a BERRY."
	.string "\pHere. I'll share\n"
	.string "one with you!$"

Route30BerryHouse_Johto_Route30BerrySpeechHouseCheckTreesText:
	.string "Check trees for\n"
	.string "BERRIES. They just\l"
	.string "drop right off.$"
