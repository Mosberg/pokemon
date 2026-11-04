EcruteakItemfinderHouse_Johto_MapScripts::
	.byte 0

EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy_Entry::
	lockall
	goto EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy

EcruteakItemfinderHouse_Johto_EcruteakHistoryBook_Entry::
	lockall
	goto EcruteakItemfinderHouse_Johto_EcruteakHistoryBook

EcruteakItemfinderHouse_Johto_ItemFinderHouseRadio_Entry::
	lockall
	goto EcruteakItemfinderHouse_Johto_ItemFinderHouseRadio


EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_ITEMFINDER, EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy_itemfinder
	message EcruteakItemfinderHouse_Johto_EcruteakItemfinderAdventureText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy_no
	message EcruteakItemfinderHouse_Johto_EcruteakItemfinderTrueSpiritText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ITEMFINDER
	setflag FLAG_JOHTO_GOT_ITEMFINDER

EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy_itemfinder:
	message EcruteakItemfinderHouse_Johto_ItemfinderExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakItemfinderHouse_Johto_EcruteakItemfinderGuy_no:
	message EcruteakItemfinderHouse_Johto_EcruteakItemfinderToEachHisOwnText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakItemfinderHouse_Johto_EcruteakHistoryBook:
	message EcruteakItemfinderHouse_Johto_EcruteakHistoryBookText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, EcruteakItemfinderHouse_Johto_EcruteakHistoryBook_ReadBook
	closemessage
	releaseall
	end

EcruteakItemfinderHouse_Johto_EcruteakHistoryBook_ReadBook:
	message EcruteakItemfinderHouse_Johto_EcruteakTwoTowersText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, EcruteakItemfinderHouse_Johto_EcruteakHistoryBook_KeepReading
	closemessage
	releaseall
	end

EcruteakItemfinderHouse_Johto_EcruteakHistoryBook_KeepReading:
	message EcruteakItemfinderHouse_Johto_EcruteakThreeMonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakItemfinderHouse_Johto_ItemFinderHouseRadio:
	goto Johto_Std_Radio2Script

EcruteakItemfinderHouse_Johto_EcruteakItemfinderAdventureText:
	.string "Ah. You're on an\n"
	.string "adventure with\l"
	.string "your POKéMON?"
	.string "\pWell, what's an\n"
	.string "adventure without\l"
	.string "treasure hunting?"
	.string "\pAm I right, or am\n"
	.string "I right?$"

EcruteakItemfinderHouse_Johto_EcruteakItemfinderTrueSpiritText:
	.string "Good! You under-\n"
	.string "stand the true"
	.string "\pspirit of adven-\n"
	.string "ture."
	.string "\pI like that! Take\n"
	.string "this with you.$"

EcruteakItemfinderHouse_Johto_ItemfinderExplanationText:
	.string "There are many\n"
	.string "items lying about"
	.string "\pthat aren't ob-\n"
	.string "vious."
	.string "\pUse ITEMFINDER to\n"
	.string "check if there is"
	.string "\pan item on the\n"
	.string "ground near you."
	.string "\pIt doesn't show\n"
	.string "the exact spot,"
	.string "\pso you'll have to\n"
	.string "look yourself."
	.string "\pOh yeah--I heard\n"
	.string "there are items"
	.string "\pin ECRUTEAK's\n"
	.string "BURNED TOWER.$"

EcruteakItemfinderHouse_Johto_EcruteakItemfinderToEachHisOwnText:
	.string "Oh… To each his\n"
	.string "own, I suppose…$"

EcruteakItemfinderHouse_Johto_EcruteakHistoryBookText:
	.string "HISTORY OF\n"
	.string "ECRUTEAK"
	.string "\pWant to read it?$"

EcruteakItemfinderHouse_Johto_EcruteakTwoTowersText:
	.string "In ECRUTEAK, there\n"
	.string "were two towers."
	.string "\pEach tower was the\n"
	.string "roost of powerful\l"
	.string "flying POKéMON."
	.string "\pBut one of the\n"
	.string "towers burned to\l"
	.string "the ground."
	.string "\pThe two POKéMON\n"
	.string "haven't been seen\l"
	.string "since…"
	.string "\pKeep reading?$"

EcruteakItemfinderHouse_Johto_EcruteakThreeMonText:
	.string "ECRUTEAK was also\n"
	.string "home to three"
	.string "\pPOKéMON that raced\n"
	.string "around the town."
	.string "\pThey were said to\n"
	.string "have been born of"
	.string "\pwater, lightning\n"
	.string "and fire."
	.string "\pBut they could not\n"
	.string "contain their\l"
	.string "excessive power."
	.string "\pSo they say the\n"
	.string "three ran like the"
	.string "\pwind off into the\n"
	.string "grassland.$"
