Route2NuggetHouse_Johto_MapScripts::
	.byte 0

Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript_Entry::
	lockall
	goto Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript


Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_NUGGET_FROM_GUY, Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript_GotNugget
	message Route2NuggetHouse_Johto_Route2NuggetHouseFisherText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript_NoRoom
	setflag FLAG_JOHTO_GOT_NUGGET_FROM_GUY

Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript_GotNugget:
	message Route2NuggetHouse_Johto_Route2NuggetHouseFisherText_GotNugget
	waitmessage
	waitbuttonpress

Route2NuggetHouse_Johto_Route2NuggetHouseFisherScript_NoRoom:
	closemessage
	releaseall
	end

Route2NuggetHouse_Johto_Route2NuggetHouseFisherText:
	.string "Hi! Wow, I'm glad\n"
	.string "to see you."
	.string "\pYou're the first\n"
	.string "visitor I've had\l"
	.string "in a long time."
	.string "\pI'm super-happy!\n"
	.string "Let me give you a\l"
	.string "little present.$"

Route2NuggetHouse_Johto_Route2NuggetHouseFisherText_GotNugget:
	.string "That's a NUGGET."
	.string "\pI can't give you\n"
	.string "any nuggets of"
	.string "\pwisdom, so that'll\n"
	.string "have to do!$"
