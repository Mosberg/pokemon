OlivineGoodRodHouse_Johto_MapScripts::
	.byte 0

OlivineGoodRodHouse_Johto_GoodRodGuru_Entry::
	lockall
	goto OlivineGoodRodHouse_Johto_GoodRodGuru


OlivineGoodRodHouse_Johto_GoodRodGuru:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_GOOD_ROD, OlivineGoodRodHouse_Johto_GoodRodGuru_AlreadyGotItem
	message OlivineGoodRodHouse_Johto_OfferGoodRodText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, OlivineGoodRodHouse_Johto_GoodRodGuru_DontWantIt
	message OlivineGoodRodHouse_Johto_GiveGoodRodText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GOOD_ROD
	message OlivineGoodRodHouse_Johto_GaveGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_GOT_GOOD_ROD
	releaseall
	end

OlivineGoodRodHouse_Johto_GoodRodGuru_DontWantIt:
	message OlivineGoodRodHouse_Johto_DontWantGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGoodRodHouse_Johto_GoodRodGuru_AlreadyGotItem:
	message OlivineGoodRodHouse_Johto_HaveGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGoodRodHouse_Johto_OfferGoodRodText:
	.string "OLIVINE is on the\n"
	.string "sea!"
	.string "\pAnd if it's on the\n"
	.string "sea, there are\l"
	.string "bound to be fish!"
	.string "\pI've fished here\n"
	.string "for 30 years."
	.string "\pWould you like to\n"
	.string "face the sea and\l"
	.string "fish?$"

OlivineGoodRodHouse_Johto_GiveGoodRodText:
	.string "Ah, hahah!\n"
	.string "We have ourselves\l"
	.string "a new angler!$"

OlivineGoodRodHouse_Johto_GaveGoodRodText:
	.string "Fish aren't found\n"
	.string "in the sea alone."
	.string "\pThey go wherever\n"
	.string "there is water.$"

OlivineGoodRodHouse_Johto_DontWantGoodRodText:
	.string "Whaaat? You don't\n"
	.string "like to fish!?\l"
	.string "Incomprehensible!$"

OlivineGoodRodHouse_Johto_HaveGoodRodText:
	.string "How are things?\n"
	.string "Land the big one?$"
