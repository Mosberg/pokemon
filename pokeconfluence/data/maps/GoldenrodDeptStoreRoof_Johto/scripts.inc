GoldenrodDeptStoreRoof_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodDeptStoreRoof_Johto_OnTransition
	.byte 0

GoldenrodDeptStoreRoof_Johto_OnTransition:
	call GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_Cb
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofClerkScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofClerkScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanFScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanFScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofFisherScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofFisherScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTwinScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTwinScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanMScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanMScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTeacherScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTeacherScript

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofBugCatcherScript_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofBugCatcherScript

GoldenrodDeptStoreRoof_Johto_Binoculars1_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_Binoculars1

GoldenrodDeptStoreRoof_Johto_Binoculars2_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_Binoculars2

GoldenrodDeptStoreRoof_Johto_Binoculars3_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_Binoculars3

GoldenrodDeptStoreRoof_Johto_PokeDollVendingMachine_Entry::
	lockall
	goto GoldenrodDeptStoreRoof_Johto_PokeDollVendingMachine


GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofClerkScript:
	@ TODO unsupported: pokemart MARTTYPE_ROOFTOP, 0
	goto Johto_EventScript_Unimplemented

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanFScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofFisherScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofFisherText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Up
	waitmovement 3
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTwinScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTwinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdScript:
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdOhWowText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Up
	waitmovement 5
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanMScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTeacherScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofBugCatcherScript:
	faceplayer
	message GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_Binoculars1:
	message GoldenrodDeptStoreRoof_Johto_Binoculars1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_Binoculars2:
	message GoldenrodDeptStoreRoof_Johto_Binoculars2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_Binoculars3:
	message GoldenrodDeptStoreRoof_Johto_Binoculars3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_PokeDollVendingMachine:
	message GoldenrodDeptStoreRoof_Johto_PokeDollVendingMachineText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON, GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_ChangeClerk_Cb
	setflag FLAG_JOHTO_GOLDENROD_SALE_OFF
	clearflag FLAG_JOHTO_GOLDENROD_SALE_ON
	return

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_ChangeClerk_Cb:
	clearflag FLAG_JOHTO_GOLDENROD_SALE_OFF
	setflag FLAG_JOHTO_GOLDENROD_SALE_ON
	return

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanFText:
	.string "Whew, I'm tired."
	.string "\pI sometimes come\n"
	.string "up to the rooftop"
	.string "\pto take a break\n"
	.string "from shopping.$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofFisherText:
	.string "Pardon? Who says\n"
	.string "an adult can't get\l"
	.string "into this?"
	.string "\pI'm going to be\n"
	.string "back every day to"
	.string "\pcollect all the\n"
	.string "dolls!$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTwinText:
	.string "They have bargain\n"
	.string "sales here every\l"
	.string "so often.$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdOhWowText:
	.string "Oh, wow!$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText:
	.string "Will you quit\n"
	.string "bothering me?$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofPokefanMText:
	.string "There's something\n"
	.string "I really want, but"
	.string "\pI don't have the\n"
	.string "necessary cash…"
	.string "\pMaybe I'll sell\n"
	.string "off the BERRIES\l"
	.string "I've collected…$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofTeacherText:
	.string "Oh, everything is\n"
	.string "so cheap!"
	.string "\pI bought so much,\n"
	.string "my PACK's crammed!$"

GoldenrodDeptStoreRoof_Johto_GoldenrodDeptStoreRoofBugCatcherText:
	.string "My POKéMON always\n"
	.string "get paralyzed or"
	.string "\ppoisoned when the\n"
	.string "chips are down…"
	.string "\pSo I came to buy\n"
	.string "some FULL HEAL."
	.string "\pI wonder if\n"
	.string "there's any left?$"

GoldenrodDeptStoreRoof_Johto_Binoculars1Text:
	.string "These binoculars\n"
	.string "let me see far"
	.string "\paway. Maybe I can\n"
	.string "see my own house."
	.string "\pIs it the one with\n"
	.string "the green roof?$"

GoldenrodDeptStoreRoof_Johto_Binoculars2Text:
	.string "Hey! Some trainers\n"
	.string "are battling on\l"
	.string "the road!"
	.string "\pA POKéMON fired a\n"
	.string "flurry of leaves!"
	.string "\pThat makes me feel\n"
	.string "like battling\l"
	.string "right now!$"

GoldenrodDeptStoreRoof_Johto_Binoculars3Text:
	.string "A FISHER caught a\n"
	.string "lot of MAGIKARP…"
	.string "\pThey're SPLASHing\n"
	.string "at the same time!"
	.string "\pLook at the water\n"
	.string "going everywhere!$"

GoldenrodDeptStoreRoof_Johto_PokeDollVendingMachineText:
	.string "A vending machine\n"
	.string "for POKéMON dolls?"
	.string "\pInsert money, then\n"
	.string "turn the crank…"
	.string "\pBut it's almost\n"
	.string "empty…$"
