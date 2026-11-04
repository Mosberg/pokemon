Route2_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route2_Johto_OnLoad
	.byte 0

Route2_Johto_Route2DireHit_Entry::
	lockall
	goto Route2_Johto_Route2DireHit

Route2_Johto_Route2MaxPotion_Entry::
	lockall
	goto Route2_Johto_Route2MaxPotion

Route2_Johto_Route2Carbos_Entry::
	lockall
	goto Route2_Johto_Route2Carbos

Route2_Johto_Route2Elixer_Entry::
	lockall
	goto Route2_Johto_Route2Elixer

Route2_Johto_Route2FruitTree_Entry::
	lockall
	goto Route2_Johto_Route2FruitTree

Route2_Johto_Route2Sign_Entry::
	lockall
	goto Route2_Johto_Route2Sign

Route2_Johto_Route2DiglettsCaveSign_Entry::
	lockall
	goto Route2_Johto_Route2DiglettsCaveSign


Route2_Johto_TrainerBugCatcherRob::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_ROB, Route2_Johto_BugCatcherRobSeenText, Route2_Johto_BugCatcherRobBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_ROB
	lock
	faceplayer
	goto Route2_Johto_TrainerBugCatcherRob_Script

Route2_Johto_TrainerBugCatcherRob_Script:
	message Route2_Johto_BugCatcherRobAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2_Johto_TrainerBugCatcherEd::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_ED, Route2_Johto_BugCatcherEdSeenText, Route2_Johto_BugCatcherEdBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_ED
	lock
	faceplayer
	goto Route2_Johto_TrainerBugCatcherEd_Script

Route2_Johto_TrainerBugCatcherEd_Script:
	message Route2_Johto_BugCatcherEdAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2_Johto_TrainerBugCatcherDoug::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_DOUG, Route2_Johto_BugCatcherDougSeenText, Route2_Johto_BugCatcherDougBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_DOUG
	lock
	faceplayer
	goto Route2_Johto_TrainerBugCatcherDoug_Script

Route2_Johto_TrainerBugCatcherDoug_Script:
	message Route2_Johto_BugCatcherDougAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2_Johto_Route2Sign:
	message Route2_Johto_Route2SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2_Johto_Route2DiglettsCaveSign:
	message Route2_Johto_Route2DiglettsCaveSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route2_Johto_Route2DireHit:
	finditem ITEM_DIRE_HIT
	releaseall
	end

Route2_Johto_Route2MaxPotion:
	finditem ITEM_MAX_POTION
	releaseall
	end

Route2_Johto_Route2Carbos:
	finditem ITEM_CARBOS
	releaseall
	end

Route2_Johto_Route2Elixer:
	finditem ITEM_ELIXER
	releaseall
	end

Route2_Johto_Route2FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_2, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PECHA_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_2
	releaseall
	end

Route2_Johto_BugCatcherRobSeenText:
	.string "My bug POKéMON are\n"
	.string "tough. Prepare to\l"
	.string "lose!$"

Route2_Johto_BugCatcherRobBeatenText:
	.string "I was whipped…$"

Route2_Johto_BugCatcherRobAfterBattleText:
	.string "I'm going to look\n"
	.string "for stronger bug\l"
	.string "POKéMON.$"

Route2_Johto_BugCatcherEdSeenText:
	.string "If you walk in\n"
	.string "tall grass wearing"
	.string "\pshorts, do you get\n"
	.string "nicks and cuts?$"

Route2_Johto_BugCatcherEdBeatenText:
	.string "Ouch, ouch, ouch!$"

Route2_Johto_BugCatcherEdAfterBattleText:
	.string "They'll really\n"
	.string "sting when you\l"
	.string "take a bath.$"

Route2_Johto_BugCatcherDougSeenText:
	.string "Why don't girls\n"
	.string "like bug POKéMON?$"

Route2_Johto_BugCatcherDougBeatenText:
	.string "No good!$"

Route2_Johto_BugCatcherDougAfterBattleText:
	.string "Bug POKéMON squish\n"
	.string "like plush toys"
	.string "\pwhen you squeeze\n"
	.string "their bellies."
	.string "\pI love how they\n"
	.string "feel!$"

Route2_Johto_Route2SignText:
	.string "ROUTE 2"
	.string "\pVIRIDIAN CITY -\n"
	.string "PEWTER CITY$"

Route2_Johto_Route2DiglettsCaveSignText:
	.string "DIGLETT'S CAVE$"

Route2_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_2_0, Route2_Johto_CutTree0_Keep
	setmetatile 4, 8, 541, 1
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
Route2_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_2_1, Route2_Johto_CutTree1_Keep
	setmetatile 14, 18, 541, 1
	setmetatile 15, 18, 533, 0
	setmetatile 14, 19, 541, 1
	setmetatile 15, 19, 533, 0
Route2_Johto_CutTree1_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_2_2, Route2_Johto_CutTree2_Keep
	setmetatile 10, 40, 533, 0
	setmetatile 11, 40, 533, 0
	setmetatile 10, 41, 541, 1
	setmetatile 11, 41, 541, 1
Route2_Johto_CutTree2_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_2_3, Route2_Johto_CutTree3_Keep
	setmetatile 12, 46, 533, 0
	setmetatile 13, 46, 533, 0
	setmetatile 12, 47, 541, 1
	setmetatile 13, 47, 541, 1
Route2_Johto_CutTree3_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_2_4, Route2_Johto_CutTree4_Keep
	setmetatile 12, 50, 533, 0
	setmetatile 13, 50, 533, 0
	setmetatile 12, 51, 541, 1
	setmetatile 13, 51, 541, 1
Route2_Johto_CutTree4_Keep:
	end

Route2_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route2_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_2_0
	setmetatile 4, 8, 541, 1
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
	special DrawWholeMapView
Route2_Johto_CutTree0_Done:
	releaseall
	end

Route2_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route2_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_2_1
	setmetatile 14, 18, 541, 1
	setmetatile 15, 18, 533, 0
	setmetatile 14, 19, 541, 1
	setmetatile 15, 19, 533, 0
	special DrawWholeMapView
Route2_Johto_CutTree1_Done:
	releaseall
	end

Route2_Johto_CutTree2::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route2_Johto_CutTree2_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_2_2
	setmetatile 10, 40, 533, 0
	setmetatile 11, 40, 533, 0
	setmetatile 10, 41, 541, 1
	setmetatile 11, 41, 541, 1
	special DrawWholeMapView
Route2_Johto_CutTree2_Done:
	releaseall
	end

Route2_Johto_CutTree3::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route2_Johto_CutTree3_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_2_3
	setmetatile 12, 46, 533, 0
	setmetatile 13, 46, 533, 0
	setmetatile 12, 47, 541, 1
	setmetatile 13, 47, 541, 1
	special DrawWholeMapView
Route2_Johto_CutTree3_Done:
	releaseall
	end

Route2_Johto_CutTree4::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route2_Johto_CutTree4_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_2_4
	setmetatile 12, 50, 533, 0
	setmetatile 13, 50, 533, 0
	setmetatile 12, 51, 541, 1
	setmetatile 13, 51, 541, 1
	special DrawWholeMapView
Route2_Johto_CutTree4_Done:
	releaseall
	end
