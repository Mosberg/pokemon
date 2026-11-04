CeruleanCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_Johto_OnTransition
	.byte 0

CeruleanCity_Johto_OnTransition:
	call CeruleanCity_Johto_CeruleanCityFlypointCallback_Cb
	end

CeruleanCity_Johto_CeruleanCityCooltrainerMScript_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityCooltrainerMScript

CeruleanCity_Johto_CeruleanCitySuperNerdScript_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCitySuperNerdScript

CeruleanCity_Johto_CeruleanCitySlowbro_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCitySlowbro

CeruleanCity_Johto_CeruleanCityCooltrainerFScript_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityCooltrainerFScript

CeruleanCity_Johto_CeruleanCityFisherScript_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityFisherScript

CeruleanCity_Johto_CeruleanCityYoungsterScript_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityYoungsterScript

CeruleanCity_Johto_CeruleanCitySign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCitySign

CeruleanCity_Johto_CeruleanGymSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanGymSign

CeruleanCity_Johto_CeruleanBikeShopSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanBikeShopSign

CeruleanCity_Johto_CeruleanPoliceSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanPoliceSign

CeruleanCity_Johto_CeruleanCapeSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCapeSign

CeruleanCity_Johto_CeruleanLockedDoor_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanLockedDoor

CeruleanCity_Johto_CeruleanCityPokecenterSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityPokecenterSign

CeruleanCity_Johto_CeruleanCityMartSign_Entry::
	lockall
	goto CeruleanCity_Johto_CeruleanCityMartSign


CeruleanCity_Johto_CeruleanCityCooltrainerMScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, CeruleanCity_Johto_CeruleanCityCooltrainerMScript_ReturnedMachinePart
	message CeruleanCity_Johto_CeruleanCityCooltrainerMText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityCooltrainerMScript_ReturnedMachinePart:
	message CeruleanCity_Johto_CeruleanCityCooltrainerMText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCitySuperNerdScript:
	faceplayer
	message CeruleanCity_Johto_CeruleanCitySuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCitySlowbro:
	message CeruleanCity_Johto_CeruleanCitySlowbroText
	waitmessage
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityCooltrainerFScript:
	faceplayer
	message CeruleanCity_Johto_CeruleanCityCooltrainerFText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Left
	waitmovement 4
	message CeruleanCity_Johto_CeruleanCityCooltrainerFText2
	waitmessage
	waitbuttonpress
	closemessage
	message CeruleanCity_Johto_CeruleanCitySlowbroText
	waitmessage
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	message CeruleanCity_Johto_CeruleanCityCooltrainerFText3
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, CeruleanCity_Johto_CeruleanCityFisherScript_ReturnedMachinePart
	goto_if_set FLAG_JOHTO_MET_ROCKET_GRUNT_AT_CERULEAN_GYM, CeruleanCity_Johto_CeruleanCityFisherScript_MetCeruleanRocket

CeruleanCity_Johto_CeruleanCityFisherScript_ReturnedMachinePart:
	message CeruleanCity_Johto_CeruleanCityFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityFisherScript_MetCeruleanRocket:
	message CeruleanCity_Johto_CeruleanCityFisherRocketTipText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityYoungsterScript:
	faceplayer
	message CeruleanCity_Johto_CeruleanCityYoungsterText1
	waitmessage
	waitbuttonpress
	closemessage
	goto_if_unset FLAG_JOHTO_FOUND_BERSERK_GENE_IN_CERULEAN_CITY, CeruleanCity_Johto_CeruleanCityYoungsterScript_BerserkGenePingsItemfinder
	releaseall
	end

CeruleanCity_Johto_CeruleanCityYoungsterScript_BerserkGenePingsItemfinder:
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	playse SE_PIN
	waitse
	applymovement 6, Johto_Movement_Emote_exclamation_mark
	waitmovement 6
	applymovement 6, Johto_Movement_Face_Left
	waitmovement 6
	message CeruleanCity_Johto_CeruleanCityYoungsterText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCitySign:
	message CeruleanCity_Johto_CeruleanCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanGymSign:
	message CeruleanCity_Johto_CeruleanGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanBikeShopSign:
	message CeruleanCity_Johto_CeruleanBikeShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanPoliceSign:
	message CeruleanCity_Johto_CeruleanPoliceSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCapeSign:
	message CeruleanCity_Johto_CeruleanCapeSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanLockedDoor:
	message CeruleanCity_Johto_CeruleanLockedDoorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanCity_Johto_CeruleanCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

CeruleanCity_Johto_CeruleanCityMartSign:
	goto Johto_Std_MartSignScript

CeruleanCity_Johto_CeruleanCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_CERULEAN
	return

CeruleanCity_Johto_CeruleanCityCooltrainerMText1:
	.string "KANTO's POWER\n"
	.string "PLANT?"
	.string "\pIt's near the end\n"
	.string "of ROUTE 9, the"
	.string "\proad that heads\n"
	.string "east from here."
	.string "\pI think there was\n"
	.string "an accident of\l"
	.string "some sort there.$"

CeruleanCity_Johto_CeruleanCityCooltrainerMText2:
	.string "You're collecting\n"
	.string "every single kind\l"
	.string "of POKéMON?"
	.string "\pThat must be quite\n"
	.string "a challenge, but\l"
	.string "it sounds fun too.$"

CeruleanCity_Johto_CeruleanCitySuperNerdText:
	.string "The CAPE in the\n"
	.string "north is a good"
	.string "\pplace for dates.\n"
	.string "Girls like it!$"

CeruleanCity_Johto_CeruleanCitySlowbroText:
	.string "SLOWBRO: Yarah?$"

CeruleanCity_Johto_CeruleanCityCooltrainerFText1:
	.string "My SLOWBRO and I\n"
	.string "make an awesome\l"
	.string "combination!$"

CeruleanCity_Johto_CeruleanCityCooltrainerFText2:
	.string "SLOWBRO, show me\n"
	.string "your CONFUSION!$"

CeruleanCity_Johto_CeruleanCityCooltrainerFText3:
	.string "…$"

CeruleanCity_Johto_CeruleanCityFisherText:
	.string "I'm a huge fan of\n"
	.string "CERULEAN GYM's\l"
	.string "MISTY.$"

CeruleanCity_Johto_CeruleanCityFisherRocketTipText:
	.string "I saw this shady\n"
	.string "guy go off toward\l"
	.string "CERULEAN's CAPE.$"

CeruleanCity_Johto_CeruleanCityYoungsterText1:
	.string "There used to be a\n"
	.string "cave here that had"
	.string "\phorribly powerful\n"
	.string "POKéMON in it.$"

CeruleanCity_Johto_CeruleanCityYoungsterText2:
	.string "Ayuh?"
	.string "\pMy ITEMFINDER is\n"
	.string "responding…$"

CeruleanCity_Johto_CeruleanCitySignText:
	.string "CERULEAN CITY"
	.string "\pA Mysterious Blue\n"
	.string "Aura Surrounds It$"

CeruleanCity_Johto_CeruleanGymSignText:
	.string "CERULEAN CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: MISTY"
	.string "\pThe Tomboyish\n"
	.string "Mermaid$"

CeruleanCity_Johto_CeruleanBikeShopSignText:
	.string "There's a notice\n"
	.string "here…"
	.string "\pThe BIKE SHOP has\n"
	.string "moved to GOLDENROD\l"
	.string "CITY in JOHTO…$"

CeruleanCity_Johto_CeruleanPoliceSignText:
	.string "There's a notice\n"
	.string "here…"
	.string "\pStamp out thievery\n"
	.string "and make the city"
	.string "\pa friendlier, more\n"
	.string "cheerful place!"
	.string "\pCERULEAN POLICE$"

CeruleanCity_Johto_CeruleanCapeSignText:
	.string "CERULEAN CAPE\n"
	.string "AHEAD$"

CeruleanCity_Johto_CeruleanLockedDoorText:
	.string "It's locked…$"
