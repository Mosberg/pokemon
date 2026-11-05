Route39Farmhouse_Johto_MapScripts::
	.byte 0

Route39Farmhouse_Johto_PokefanM_DairyFarmer_Entry::
	lockall
	goto Route39Farmhouse_Johto_PokefanM_DairyFarmer

Route39Farmhouse_Johto_PokefanF_SnoreFarmer_Entry::
	lockall
	goto Route39Farmhouse_Johto_PokefanF_SnoreFarmer

Route39Farmhouse_Johto_FarmhouseBookshelf_Entry::
	lockall
	goto Route39Farmhouse_Johto_FarmhouseBookshelf


Route39Farmhouse_Johto_PokefanM_DairyFarmer:
	faceplayer
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Farmhouse_Johto_FarmerMScript_SellMilk
	message Route39Farmhouse_Johto_FarmerMText_SickCow
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_TALKED_TO_FARMER_ABOUT_MOOMOO
	releaseall
	end

Route39Farmhouse_Johto_FarmerMScript_SellMilk:
	checkitem ITEM_MOOMOO_MILK, 1
	goto_if_ne VAR_RESULT, 0, Route39Farmhouse_Johto_FarmerMScript_Milking
	message Route39Farmhouse_Johto_FarmerMText_BuyMilk
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route39Farmhouse_Johto_FarmerMScript_NoSale
	checkmoney 500
	goto_if_eq VAR_RESULT, 0, Route39Farmhouse_Johto_FarmerMScript_NoMoney
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, 0, Route39Farmhouse_Johto_FarmerMScript_NoRoom
	removemoney 500
	waitse
	playse SE_PIN
	message Route39Farmhouse_Johto_FarmerMText_GotMilk
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmerMScript_NoMoney:
	message Route39Farmhouse_Johto_FarmerMText_NoMoney
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmerMScript_NoRoom:
	message Route39Farmhouse_Johto_FarmerMText_NoRoom
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmerMScript_NoSale:
	message Route39Farmhouse_Johto_FarmerMText_NoSale
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmerMScript_Milking:
	message Route39Farmhouse_Johto_FarmerMText_Milking
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_PokefanF_SnoreFarmer:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM13_SNORE_FROM_MOOMOO_FARM, Route39Farmhouse_Johto_FarmerFScript_GotSnore
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Farmhouse_Johto_FarmerFScript_GiveSnore
	message Route39Farmhouse_Johto_FarmerFText_InTrouble
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmerFScript_GiveSnore:
	message Route39Farmhouse_Johto_FarmerFText_HealedMiltank
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_REST
	goto_if_eq VAR_RESULT, 0, Route39Farmhouse_Johto_FarmerFScript_NoRoomForSnore
	setflag FLAG_JOHTO_GOT_TM13_SNORE_FROM_MOOMOO_FARM

Route39Farmhouse_Johto_FarmerFScript_GotSnore:
	message Route39Farmhouse_Johto_FarmerFText_SnoreSpeech
	waitmessage
	waitbuttonpress

Route39Farmhouse_Johto_FarmerFScript_NoRoomForSnore:
	closemessage
	releaseall
	end

Route39Farmhouse_Johto_FarmhouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

Route39Farmhouse_Johto_FarmerMText_SickCow:
	.string "My MILTANK ain't\n"
	.string "givin' me milk\l"
	.string "n'more."
	.string "\pThis here FARM's\n"
	.string "got famous milk."
	.string "\pMost everyone\n"
	.string "wants a drink."
	.string "\pIt'll give me lots\n"
	.string "o' milk if'n I"
	.string "\pfeed it lots o'\n"
	.string "BERRIES, I reckon.$"

Route39Farmhouse_Johto_FarmerMText_BuyMilk:
	.string "How'd you like my\n"
	.string "MOOMOO MILK?"
	.string "\pIt's my pride and\n"
	.string "joy, there."
	.string "\pGive it to POKéMON\n"
	.string "to restore HP!"
	.string "\pI'll give it to ya\n"
	.string "fer just ¥500.$"

Route39Farmhouse_Johto_FarmerMText_GotMilk:
	.string "Here ya go!\n"
	.string "Drink up'n enjoy!$"

Route39Farmhouse_Johto_FarmerMText_NoMoney:
	.string "Sorry, there.\n"
	.string "No cash, no sale!$"

Route39Farmhouse_Johto_FarmerMText_NoRoom:
	.string "I reckon yer\n"
	.string "PACK's full.$"

Route39Farmhouse_Johto_FarmerMText_NoSale:
	.string "You don't want it?\n"
	.string "Come again, hear?$"

Route39Farmhouse_Johto_FarmerMText_Milking:
	.string "I best go do my\n"
	.string "milkin'.$"

Route39Farmhouse_Johto_FarmerFText_InTrouble:
	.string "Our milk even goes\n"
	.string "out to KANTO."
	.string "\pSo if our own\n"
	.string "MILTANK won't give"
	.string "\pus any milk, we're\n"
	.string "in trouble.$"

Route39Farmhouse_Johto_FarmerFText_HealedMiltank:
	.string "You fixed our\n"
	.string "MILTANK, hon. Now"
	.string "\pit gives MOOMOO\n"
	.string "MILK again."
	.string "\pHere's somethin'\n"
	.string "fer your trouble.$"

Route39Farmhouse_Johto_FarmerFText_SnoreSpeech:
	.string "That there's\n"
	.string "SNORE."
	.string "\pIt's a rare move\n"
	.string "that only works"
	.string "\pwhile the POKéMON\n"
	.string "is asleep."
	.string "\pYou best think how\n"
	.string "you ought to use\l"
	.string "it, hon.$"
