PewterCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_Johto_OnTransition
	.byte 0

PewterCity_Johto_OnTransition:
	call PewterCity_Johto_PewterCityFlypointCallback_Cb
	end

PewterCity_Johto_PewterCityCooltrainerFScript_Entry::
	lockall
	goto PewterCity_Johto_PewterCityCooltrainerFScript

PewterCity_Johto_PewterCityBugCatcherScript_Entry::
	lockall
	goto PewterCity_Johto_PewterCityBugCatcherScript

PewterCity_Johto_PewterCityGrampsScript_Entry::
	lockall
	goto PewterCity_Johto_PewterCityGrampsScript

PewterCity_Johto_PewterCityFruitTree1_Entry::
	lockall
	goto PewterCity_Johto_PewterCityFruitTree1

PewterCity_Johto_PewterCityFruitTree2_Entry::
	lockall
	goto PewterCity_Johto_PewterCityFruitTree2

PewterCity_Johto_PewterCitySign_Entry::
	lockall
	goto PewterCity_Johto_PewterCitySign

PewterCity_Johto_PewterGymSign_Entry::
	lockall
	goto PewterCity_Johto_PewterGymSign

PewterCity_Johto_PewterMuseumSign_Entry::
	lockall
	goto PewterCity_Johto_PewterMuseumSign

PewterCity_Johto_PewterCityMtMoonGiftShopSign_Entry::
	lockall
	goto PewterCity_Johto_PewterCityMtMoonGiftShopSign

PewterCity_Johto_PewterCityWelcomeSign_Entry::
	lockall
	goto PewterCity_Johto_PewterCityWelcomeSign

PewterCity_Johto_PewterCityPokecenterSign_Entry::
	lockall
	goto PewterCity_Johto_PewterCityPokecenterSign

PewterCity_Johto_PewterCityMartSign_Entry::
	lockall
	goto PewterCity_Johto_PewterCityMartSign


PewterCity_Johto_PewterCityCooltrainerFScript:
	faceplayer
	message PewterCity_Johto_PewterCityCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityBugCatcherScript:
	faceplayer
	message PewterCity_Johto_PewterCityBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityGrampsScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SILVER_WING, PewterCity_Johto_PewterCityGrampsScript_GotSilverWing
	message PewterCity_Johto_PewterCityGrampsText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SILVER_WING
	setflag FLAG_JOHTO_GOT_SILVER_WING
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityGrampsScript_GotSilverWing:
	message PewterCity_Johto_PewterCityGrampsText_GotSilverWing
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCitySign:
	message PewterCity_Johto_PewterCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterGymSign:
	message PewterCity_Johto_PewterGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterMuseumSign:
	message PewterCity_Johto_PewterMuseumSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityMtMoonGiftShopSign:
	message PewterCity_Johto_PewterCityMtMoonGiftShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityWelcomeSign:
	message PewterCity_Johto_PewterCityWelcomeSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterCity_Johto_PewterCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

PewterCity_Johto_PewterCityMartSign:
	goto Johto_Std_MartSignScript

PewterCity_Johto_PewterCityFruitTree1:
	goto_if_set FLAG_JOHTO_FRUITTREE_PEWTER_CITY_1, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ASPEAR_BERRY
	setflag FLAG_JOHTO_FRUITTREE_PEWTER_CITY_1
	releaseall
	end

PewterCity_Johto_PewterCityFruitTree2:
	goto_if_set FLAG_JOHTO_FRUITTREE_PEWTER_CITY_2, Johto_Std_FruitTreeEmpty
	giveitem ITEM_LUM_BERRY
	setflag FLAG_JOHTO_FRUITTREE_PEWTER_CITY_2
	releaseall
	end

PewterCity_Johto_PewterCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_PEWTER
	return

PewterCity_Johto_PewterCityCooltrainerFText:
	.string "Have you visited\n"
	.string "PEWTER GYM?"
	.string "\pThe LEADER uses\n"
	.string "rock-type POKéMON.$"

PewterCity_Johto_PewterCityBugCatcherText:
	.string "At night, CLEFAIRY\n"
	.string "come out to play\l"
	.string "at MT.MOON."
	.string "\pBut not every\n"
	.string "night.$"

PewterCity_Johto_PewterCityGrampsText:
	.string "Ah, you came all\n"
	.string "the way out here\l"
	.string "from JOHTO?"
	.string "\pThat brings back\n"
	.string "memories. When I"
	.string "\pwas young, I went\n"
	.string "to JOHTO to train."
	.string "\pYou remind me so\n"
	.string "much of what I was"
	.string "\plike as a young\n"
	.string "man."
	.string "\pHere. I want you\n"
	.string "to have this item\l"
	.string "I found in JOHTO.$"

PewterCity_Johto_PewterCityGrampsText_GotSilverWing:
	.string "Going to new, un-\n"
	.string "known places and\l"
	.string "seeing new people…"
	.string "\pThose are the joys\n"
	.string "of travel.$"

PewterCity_Johto_PewterCitySignText:
	.string "PEWTER CITY\n"
	.string "A Stone Gray City$"

PewterCity_Johto_PewterGymSignText:
	.string "PEWTER CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: BROCK"
	.string "\pThe Rock Solid\n"
	.string "POKéMON Trainer$"

PewterCity_Johto_PewterMuseumSignText:
	.string "There's a notice\n"
	.string "here…"
	.string "\pPEWTER MUSEUM OF\n"
	.string "SCIENCE is closed\l"
	.string "for renovations…$"

PewterCity_Johto_PewterCityMtMoonGiftShopSignText:
	.string "There's a notice\n"
	.string "here…"
	.string "\pMT.MOON GIFT SHOP\n"
	.string "NOW OPEN!$"

PewterCity_Johto_PewterCityWelcomeSignText:
	.string "WELCOME TO\n"
	.string "PEWTER CITY!$"
