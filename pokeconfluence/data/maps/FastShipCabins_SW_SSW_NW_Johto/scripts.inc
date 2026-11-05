FastShipCabins_SW_SSW_NW_Johto_MapScripts::
	.byte 0

FastShipCabins_SW_SSW_NW_Johto_FastShipBed_Entry::
	lockall
	goto FastShipCabins_SW_SSW_NW_Johto_FastShipBed

FastShipCabins_SW_SSW_NW_Johto_FastShipCabinsNorthwestCabinTrashcan_Entry::
	lockall
	goto FastShipCabins_SW_SSW_NW_Johto_FastShipCabinsNorthwestCabinTrashcan


FastShipCabins_SW_SSW_NW_Johto_TrainerFirebreatherLyle::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_LYLE, FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleSeenText, FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_LYLE
	lock
	faceplayer
	goto FastShipCabins_SW_SSW_NW_Johto_TrainerFirebreatherLyle_Script

FastShipCabins_SW_SSW_NW_Johto_TrainerFirebreatherLyle_Script:
	message FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_TrainerBugCatcherKen::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_KEN, FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenSeenText, FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_KEN
	lock
	faceplayer
	goto FastShipCabins_SW_SSW_NW_Johto_TrainerBugCatcherKen_Script

FastShipCabins_SW_SSW_NW_Johto_TrainerBugCatcherKen_Script:
	message FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_TrainerBeautyCassie::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_CASSIE, FastShipCabins_SW_SSW_NW_Johto_BeautyCassieSeenText, FastShipCabins_SW_SSW_NW_Johto_BeautyCassieBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_CASSIE
	lock
	faceplayer
	goto FastShipCabins_SW_SSW_NW_Johto_TrainerBeautyCassie_Script

FastShipCabins_SW_SSW_NW_Johto_TrainerBeautyCassie_Script:
	message FastShipCabins_SW_SSW_NW_Johto_BeautyCassieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_TrainerGuitaristClyde::
	trainerbattle_single TRAINER_JOHTO_GUITARIST_CLYDE, FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeSeenText, FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeBeatenText
	setflag FLAG_JOHTO_BEAT_GUITARIST_CLYDE
	lock
	faceplayer
	goto FastShipCabins_SW_SSW_NW_Johto_TrainerGuitaristClyde_Script

FastShipCabins_SW_SSW_NW_Johto_TrainerGuitaristClyde_Script:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, FastShipCabins_SW_SSW_NW_Johto_TrainerGuitaristClyde_mobile
	message FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_TrainerGuitaristClyde_mobile:
	message FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeAfterBattleMobileText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_FastShipBed:
	message FastShipCabins_SW_SSW_NW_Johto_FastShipBedText1
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	special HealPlayerParty
	playbgm MUS_HEAL, FALSE
	delay 60
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	message FastShipCabins_SW_SSW_NW_Johto_FastShipBedText2
	waitmessage
	waitbuttonpress
	closemessage
	goto_if_set FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED, FastShipCabins_SW_SSW_NW_Johto_FastShipBed_AlreadyArrived
	goto_if_set FLAG_JOHTO_FAST_SHIP_FOUND_GIRL, FastShipCabins_SW_SSW_NW_Johto_FastShipBed_CanArrive
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, FastShipCabins_SW_SSW_NW_Johto_FastShipBed_CanArrive

FastShipCabins_SW_SSW_NW_Johto_FastShipBed_AlreadyArrived:
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_FastShipBed_CanArrive:
	playse SE_PIN
	delay 30
	goto_if_set FLAG_JOHTO_FAST_SHIP_DESTINATION_OLIVINE, FastShipCabins_SW_SSW_NW_Johto_FastShipBed_ArrivedOlivine
	message FastShipCabins_SW_SSW_NW_Johto_FastShipArrivedVermilionText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_FastShipBed_ArrivedOlivine:
	message FastShipCabins_SW_SSW_NW_Johto_FastShipArrivedOlivineText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED
	releaseall
	end

FastShipCabins_SW_SSW_NW_Johto_FastShipCabinsNorthwestCabinTrashcan:
	goto Johto_Std_TrashCanScript

FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleSeenText:
	.string "I'm going to KANTO\n"
	.string "to put on fire-\l"
	.string "breathing shows!$"

FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleBeatenText:
	.string "Fizzle… The\n"
	.string "flame's tiny…$"

FastShipCabins_SW_SSW_NW_Johto_FirebreatherLyleAfterBattleText:
	.string "I guess fire is\n"
	.string "weak on the sea."
	.string "\pIt doesn't matter?\n"
	.string "Really?$"

FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenSeenText:
	.string "I'm visiting my\n"
	.string "grandma to catch\l"
	.string "me some bugs!$"

FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenBeatenText:
	.string "Ooh, wow.\n"
	.string "You're tough!$"

FastShipCabins_SW_SSW_NW_Johto_BugCatcherKenAfterBattleText:
	.string "You can find lots\n"
	.string "of POKéMON in the\l"
	.string "trees of JOHTO!$"

FastShipCabins_SW_SSW_NW_Johto_BeautyCassieSeenText:
	.string "I'm trying to\n"
	.string "forget my woes.\l"
	.string "Let's battle!$"

FastShipCabins_SW_SSW_NW_Johto_BeautyCassieBeatenText:
	.string "My heart weeps…$"

FastShipCabins_SW_SSW_NW_Johto_BeautyCassieAfterBattleText:
	.string "A voyage is best\n"
	.string "for getting over\l"
	.string "a broken heart."
	.string "\pBut a FAST SHIP\n"
	.string "trip is too short\l"
	.string "for grieving.$"

FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeSeenText:
	.string "I'm going to audi-\n"
	.string "tion my songs at"
	.string "\pGOLDENROD's RADIO\n"
	.string "STATION.$"

FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeBeatenText:
	.string "Yowza!\n"
	.string "Total distortion!$"

FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeAfterBattleMobileText:
	.string "I was going to\n"
	.string "make my debut at\l"
	.string "the BATTLE TOWER…"
	.string "\pI should go back\n"
	.string "to VERMILION and\l"
	.string "redo my training…$"

FastShipCabins_SW_SSW_NW_Johto_GuitaristClydeAfterBattleText:
	.string "Speaking of the\n"
	.string "RADIO STATION,"
	.string "\pwhat's this week's\n"
	.string "lucky number?$"

FastShipCabins_SW_SSW_NW_Johto_FastShipBedText1:
	.string "A comfy bed!\n"
	.string "Time to sleep…$"

FastShipCabins_SW_SSW_NW_Johto_FastShipBedText2:
	.string "Ah, refreshed and\n"
	.string "restored!$"

FastShipCabins_SW_SSW_NW_Johto_FastShipArrivedOlivineText:
	.string "FAST SHIP S.S.AQUA\n"
	.string "has arrived in\l"
	.string "OLIVINE CITY.$"

FastShipCabins_SW_SSW_NW_Johto_FastShipArrivedVermilionText:
	.string "FAST SHIP S.S.AQUA\n"
	.string "has arrived in\l"
	.string "VERMILION CITY.$"
