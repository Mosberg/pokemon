ViridianCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, ViridianCity_Johto_OnLoad
	.byte 0

ViridianCity_Johto_OnTransition:
	call ViridianCity_Johto_ViridianCityFlypointCallback_Cb
	end

ViridianCity_Johto_ViridianCityCoffeeGramps_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityCoffeeGramps

ViridianCity_Johto_ViridianCityGrampsNearGym_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityGrampsNearGym

ViridianCity_Johto_ViridianCityDreamEaterFisher_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityDreamEaterFisher

ViridianCity_Johto_ViridianCityYoungsterScript_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityYoungsterScript

ViridianCity_Johto_ViridianCitySign_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCitySign

ViridianCity_Johto_ViridianGymSign_Entry::
	lockall
	goto ViridianCity_Johto_ViridianGymSign

ViridianCity_Johto_ViridianCityWelcomeSign_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityWelcomeSign

ViridianCity_Johto_TrainerHouseSign_Entry::
	lockall
	goto ViridianCity_Johto_TrainerHouseSign

ViridianCity_Johto_ViridianCityPokecenterSign_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityPokecenterSign

ViridianCity_Johto_ViridianCityMartSign_Entry::
	lockall
	goto ViridianCity_Johto_ViridianCityMartSign


ViridianCity_Johto_ViridianCityCoffeeGramps:
	faceplayer
	message ViridianCity_Johto_ViridianCityCoffeeGrampsQuestionText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ViridianCity_Johto_ViridianCityCoffeeGramps_no
	message ViridianCity_Johto_ViridianCityCoffeeGrampsBelievedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityCoffeeGramps_no:
	message ViridianCity_Johto_ViridianCityCoffeeGrampsDoubtedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityGrampsNearGym:
	faceplayer
	goto_if_set FLAG_JOHTO_BLUE_IN_CINNABAR, ViridianCity_Johto_ViridianCityGrampsNearGym_BlueReturned
	message ViridianCity_Johto_ViridianCityGrampsNearGymText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityGrampsNearGym_BlueReturned:
	message ViridianCity_Johto_ViridianCityGrampsNearGymBlueReturnedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityDreamEaterFisher:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM42_DREAM_EATER, ViridianCity_Johto_ViridianCityDreamEaterFisher_GotDreamEater
	message ViridianCity_Johto_ViridianCityDreamEaterFisherText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, ViridianCity_Johto_ViridianCityDreamEaterFisher_NoRoomForDreamEater
	setflag FLAG_JOHTO_GOT_TM42_DREAM_EATER

ViridianCity_Johto_ViridianCityDreamEaterFisher_GotDreamEater:
	message ViridianCity_Johto_ViridianCityDreamEaterFisherGotDreamEaterText
	waitmessage
	waitbuttonpress

ViridianCity_Johto_ViridianCityDreamEaterFisher_NoRoomForDreamEater:
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityYoungsterScript:
	faceplayer
	message ViridianCity_Johto_ViridianCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCitySign:
	message ViridianCity_Johto_ViridianCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianGymSign:
	message ViridianCity_Johto_ViridianGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityWelcomeSign:
	message ViridianCity_Johto_ViridianCityWelcomeSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_TrainerHouseSign:
	message ViridianCity_Johto_TrainerHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianCity_Johto_ViridianCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

ViridianCity_Johto_ViridianCityMartSign:
	goto Johto_Std_MartSignScript

ViridianCity_Johto_ViridianCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_VIRIDIAN
	return

ViridianCity_Johto_ViridianCityCoffeeGrampsQuestionText:
	.string "Hey, kid! I just\n"
	.string "had a double shot"
	.string "\pof espresso, and\n"
	.string "I am wired!"
	.string "\pI need to talk to\n"
	.string "someone, so you'll\l"
	.string "have to do!"
	.string "\pI might not look\n"
	.string "like much now, but"
	.string "\pI was an expert at\n"
	.string "catching POKéMON."
	.string "\pDo you believe me?$"

ViridianCity_Johto_ViridianCityCoffeeGrampsBelievedText:
	.string "Good, good. Yes, I\n"
	.string "was something out"
	.string "\pof the ordinary,\n"
	.string "let me tell you!$"

ViridianCity_Johto_ViridianCityCoffeeGrampsDoubtedText:
	.string "What? You little\n"
	.string "whelp!"
	.string "\pIf I were just a\n"
	.string "bit younger, I'd"
	.string "\pshow you a thing\n"
	.string "or two. Humph!$"

ViridianCity_Johto_ViridianCityGrampsNearGymText:
	.string "This GYM didn't\n"
	.string "have a LEADER\l"
	.string "until recently."
	.string "\pA young man from\n"
	.string "PALLET became the"
	.string "\pLEADER, but he's\n"
	.string "often away.$"

ViridianCity_Johto_ViridianCityGrampsNearGymBlueReturnedText:
	.string "Are you going to\n"
	.string "battle the LEADER?"
	.string "\pGood luck to you.\n"
	.string "You'll need it.$"

ViridianCity_Johto_ViridianCityDreamEaterFisherText:
	.string "Yawn!"
	.string "\pI must have dozed\n"
	.string "off in the sun."
	.string "\p…I had this dream\n"
	.string "about a DROWZEE"
	.string "\peating my dream.\n"
	.string "Weird, huh?"
	.string "\pHuh?\n"
	.string "What's this?"
	.string "\pWhere did this TM\n"
	.string "come from?"
	.string "\pThis is spooky!\n"
	.string "Here, you can have\l"
	.string "this TM.$"

ViridianCity_Johto_ViridianCityDreamEaterFisherGotDreamEaterText:
	.string "TM42 contains\n"
	.string "DREAM EATER…"
	.string "\p…Zzzzz…$"

ViridianCity_Johto_ViridianCityYoungsterText:
	.string "I heard that there\n"
	.string "are many items on"
	.string "\pthe ground in\n"
	.string "VIRIDIAN FOREST.$"

ViridianCity_Johto_ViridianCitySignText:
	.string "VIRIDIAN CITY"
	.string "\pThe Eternally\n"
	.string "Green Paradise$"

ViridianCity_Johto_ViridianGymSignText:
	.string "VIRIDIAN CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: …"
	.string "\pThe rest of the\n"
	.string "text is illegible…$"

ViridianCity_Johto_ViridianCityWelcomeSignText:
	.string "WELCOME TO\n"
	.string "VIRIDIAN CITY,"
	.string "\pTHE GATEWAY TO\n"
	.string "INDIGO PLATEAU$"

ViridianCity_Johto_TrainerHouseSignText:
	.string "TRAINER HOUSE"
	.string "\pThe Club for Top\n"
	.string "Trainer Battles$"

ViridianCity_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_VIRIDIAN_CITY_0, ViridianCity_Johto_CutTree0_Keep
	setmetatile 14, 4, 533, 0
	setmetatile 15, 4, 533, 0
	setmetatile 14, 5, 541, 1
	setmetatile 15, 5, 541, 1
ViridianCity_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_VIRIDIAN_CITY_1, ViridianCity_Johto_CutTree1_Keep
	setmetatile 8, 22, 533, 0
	setmetatile 9, 22, 533, 0
	setmetatile 8, 23, 541, 1
	setmetatile 9, 23, 541, 1
ViridianCity_Johto_CutTree1_Keep:
	end

ViridianCity_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_VIRIDIAN_CITY_0
	setmetatile 14, 4, 533, 0
	setmetatile 15, 4, 533, 0
	setmetatile 14, 5, 541, 1
	setmetatile 15, 5, 541, 1
	special DrawWholeMapView
ViridianCity_Johto_CutTree0_Done:
	releaseall
	end

ViridianCity_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_VIRIDIAN_CITY_1
	setmetatile 8, 22, 533, 0
	setmetatile 9, 22, 533, 0
	setmetatile 8, 23, 541, 1
	setmetatile 9, 23, 541, 1
	special DrawWholeMapView
ViridianCity_Johto_CutTree1_Done:
	releaseall
	end
