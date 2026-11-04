Route8_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route8_Johto_OnLoad
	.byte 0

Route8_Johto_Route8FruitTree_Entry::
	lockall
	goto Route8_Johto_Route8FruitTree

Route8_Johto_Route8UndergroundPathSign_Entry::
	lockall
	goto Route8_Johto_Route8UndergroundPathSign

Route8_Johto_Route8LockedDoor_Entry::
	lockall
	goto Route8_Johto_Route8LockedDoor


Route8_Johto_TrainerBikerDwayne::
	trainerbattle_single TRAINER_JOHTO_BIKER_DWAYNE, Route8_Johto_BikerDwayneSeenText, Route8_Johto_BikerDwayneBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_DWAYNE
	lock
	faceplayer
	goto Route8_Johto_TrainerBikerDwayne_Script

Route8_Johto_TrainerBikerDwayne_Script:
	message Route8_Johto_BikerDwayneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_TrainerBikerHarris::
	trainerbattle_single TRAINER_JOHTO_BIKER_HARRIS, Route8_Johto_BikerHarrisSeenText, Route8_Johto_BikerHarrisBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_HARRIS
	lock
	faceplayer
	goto Route8_Johto_TrainerBikerHarris_Script

Route8_Johto_TrainerBikerHarris_Script:
	message Route8_Johto_BikerHarrisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_TrainerBikerZeke::
	trainerbattle_single TRAINER_JOHTO_BIKER_ZEKE, Route8_Johto_BikerZekeSeenText, Route8_Johto_BikerZekeBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_ZEKE
	lock
	faceplayer
	goto Route8_Johto_TrainerBikerZeke_Script

Route8_Johto_TrainerBikerZeke_Script:
	message Route8_Johto_BikerZekeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_TrainerSupernerdSam::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_SAM, Route8_Johto_SupernerdSamSeenText, Route8_Johto_SupernerdSamBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_SAM
	lock
	faceplayer
	goto Route8_Johto_TrainerSupernerdSam_Script

Route8_Johto_TrainerSupernerdSam_Script:
	message Route8_Johto_SupernerdSamAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_TrainerSupernerdTom::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_TOM, Route8_Johto_SupernerdTomSeenText, Route8_Johto_SupernerdTomBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_TOM
	lock
	faceplayer
	goto Route8_Johto_TrainerSupernerdTom_Script

Route8_Johto_TrainerSupernerdTom_Script:
	message Route8_Johto_SupernerdTomAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_Route8LockedDoor:
	message Route8_Johto_Route8LockedDoorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_Route8UndergroundPathSign:
	message Route8_Johto_Route8UndergroundPathSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8_Johto_Route8FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_8, Johto_Std_FruitTreeEmpty
	giveitem ITEM_CHERI_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_8
	releaseall
	end

Route8_Johto_BikerDwayneSeenText:
	.string "We're the KANTO\n"
	.string "POKéMON FEDERATION\l"
	.string "trainer group."
	.string "\pWe'll drive you\n"
	.string "under our wheels!$"

Route8_Johto_BikerDwayneBeatenText:
	.string "S-sorry!$"

Route8_Johto_BikerDwayneAfterBattleText:
	.string "The KANTO POKéMON\n"
	.string "FEDERATION will\l"
	.string "never fall!$"

Route8_Johto_BikerHarrisSeenText:
	.string "The cops shut down\n"
	.string "our UNDERGROUND"
	.string "\pPATH! That really\n"
	.string "fries me!$"

Route8_Johto_BikerHarrisBeatenText:
	.string "F-forgive me!$"

Route8_Johto_BikerHarrisAfterBattleText:
	.string "Wiped out by some\n"
	.string "punk from JOHTO…$"

Route8_Johto_BikerZekeSeenText:
	.string "We're the KANTO\n"
	.string "POKéMON FEDERA-\l"
	.string "TION!\l"
	.string "Right on!$"

Route8_Johto_BikerZekeBeatenText:
	.string "Yikes! Sorry!$"

Route8_Johto_BikerZekeAfterBattleText:
	.string "We'll try not to\n"
	.string "disturb anyone\l"
	.string "from now on…$"

Route8_Johto_SupernerdSamSeenText:
	.string "How does the MAG-\n"
	.string "NET TRAIN work?$"

Route8_Johto_SupernerdSamBeatenText:
	.string "I just want to see\n"
	.string "the MAGNET TRAIN…$"

Route8_Johto_SupernerdSamAfterBattleText:
	.string "The power of mag-\n"
	.string "nets is awesome!$"

Route8_Johto_SupernerdTomSeenText:
	.string "Hm… You've got\n"
	.string "many GYM BADGES.$"

Route8_Johto_SupernerdTomBeatenText:
	.string "Just as I thought…\n"
	.string "You're tough!$"

Route8_Johto_SupernerdTomAfterBattleText:
	.string "GYM BADGES give\n"
	.string "you advantages in\l"
	.string "battles.$"

Route8_Johto_Route8LockedDoorText:
	.string "It's locked…$"

Route8_Johto_Route8UndergroundPathSignText:
	.string "The flyer's torn."
	.string "\pIt's impossible to\n"
	.string "read…$"

Route8_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_8_0, Route8_Johto_CutTree0_Keep
	setmetatile 26, 10, 533, 0
	setmetatile 27, 10, 533, 0
	setmetatile 26, 11, 541, 1
	setmetatile 27, 11, 533, 0
Route8_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_8_1, Route8_Johto_CutTree1_Keep
	setmetatile 20, 12, 533, 0
	setmetatile 21, 12, 533, 0
	setmetatile 20, 13, 541, 1
	setmetatile 21, 13, 533, 0
Route8_Johto_CutTree1_Keep:
	end

Route8_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route8_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_8_0
	setmetatile 26, 10, 533, 0
	setmetatile 27, 10, 533, 0
	setmetatile 26, 11, 541, 1
	setmetatile 27, 11, 533, 0
	special DrawWholeMapView
Route8_Johto_CutTree0_Done:
	releaseall
	end

Route8_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route8_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_8_1
	setmetatile 20, 12, 533, 0
	setmetatile 21, 12, 533, 0
	setmetatile 20, 13, 541, 1
	setmetatile 21, 13, 533, 0
	special DrawWholeMapView
Route8_Johto_CutTree1_Done:
	releaseall
	end
