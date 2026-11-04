Route12SuperRodHouse_Johto_MapScripts::
	.byte 0

Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_Entry::
	lockall
	goto Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript


Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SUPER_ROD, Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_GotSuperRod
	message Route12SuperRodHouse_Johto_OfferSuperRodText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_Refused
	message Route12SuperRodHouse_Johto_GiveSuperRodText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, 0, Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_NoRoom
	setflag FLAG_JOHTO_GOT_SUPER_ROD

Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_GotSuperRod:
	message Route12SuperRodHouse_Johto_GaveSuperRodText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_Refused:
	message Route12SuperRodHouse_Johto_DontWantSuperRodText
	waitmessage
	waitbuttonpress

Route12SuperRodHouse_Johto_Route12SuperRodHouseFishingGuruScript_NoRoom:
	closemessage
	releaseall
	end

Route12SuperRodHouse_Johto_OfferSuperRodText:
	.string "I'm the FISHING\n"
	.string "GURU's younger\l"
	.string "brother."
	.string "\pI can see that you\n"
	.string "like fishing."
	.string "\pThere's no doubt\n"
	.string "in my mind at all!"
	.string "\pSo? I know I'm\n"
	.string "right.$"

Route12SuperRodHouse_Johto_GiveSuperRodText:
	.string "Yes, yes. Just as\n"
	.string "I thought!"
	.string "\pHere, fishing fan!\n"
	.string "Take this--it's a\l"
	.string "SUPER ROD.$"

Route12SuperRodHouse_Johto_GaveSuperRodText:
	.string "Try your hand at\n"
	.string "fishing wherever\l"
	.string "there is water."
	.string "\pRemember--you can\n"
	.string "catch different"
	.string "\pPOKéMON using\n"
	.string "different RODS.$"

Route12SuperRodHouse_Johto_DontWantSuperRodText:
	.string "Huh? My own eyes\n"
	.string "deceived me?$"
