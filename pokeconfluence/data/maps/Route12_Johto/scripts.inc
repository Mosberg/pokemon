Route12_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route12_Johto_OnLoad
	.byte 0

Route12_Johto_Route12Calcium_Entry::
	lockall
	goto Route12_Johto_Route12Calcium

Route12_Johto_Route12Nugget_Entry::
	lockall
	goto Route12_Johto_Route12Nugget

Route12_Johto_Route12Sign_Entry::
	lockall
	goto Route12_Johto_Route12Sign

Route12_Johto_FishingSpotSign_Entry::
	lockall
	goto Route12_Johto_FishingSpotSign


Route12_Johto_TrainerFisherKyle::
	trainerbattle_single TRAINER_JOHTO_FISHER_KYLE, Route12_Johto_FisherKyleSeenText, Route12_Johto_FisherKyleBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_KYLE
	lock
	faceplayer
	goto Route12_Johto_TrainerFisherKyle_Script

Route12_Johto_TrainerFisherKyle_Script:
	message Route12_Johto_FisherKyleAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_TrainerFisherMartin::
	trainerbattle_single TRAINER_JOHTO_FISHER_MARTIN, Route12_Johto_FisherMartinSeenText, Route12_Johto_FisherMartinBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_MARTIN
	lock
	faceplayer
	goto Route12_Johto_TrainerFisherMartin_Script

Route12_Johto_TrainerFisherMartin_Script:
	message Route12_Johto_FisherMartinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_TrainerFisherStephen::
	trainerbattle_single TRAINER_JOHTO_FISHER_STEPHEN, Route12_Johto_FisherStephenSeenText, Route12_Johto_FisherStephenBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_STEPHEN
	lock
	faceplayer
	goto Route12_Johto_TrainerFisherStephen_Script

Route12_Johto_TrainerFisherStephen_Script:
	message Route12_Johto_FisherStephenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_TrainerFisherBarney::
	trainerbattle_single TRAINER_JOHTO_FISHER_BARNEY, Route12_Johto_FisherBarneySeenText, Route12_Johto_FisherBarneyBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_BARNEY
	lock
	faceplayer
	goto Route12_Johto_TrainerFisherBarney_Script

Route12_Johto_TrainerFisherBarney_Script:
	message Route12_Johto_FisherBarneyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_Route12Sign:
	message Route12_Johto_Route12SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_FishingSpotSign:
	message Route12_Johto_FishingSpotSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route12_Johto_Route12Calcium:
	finditem ITEM_CALCIUM
	releaseall
	end

Route12_Johto_Route12Nugget:
	finditem ITEM_NUGGET
	releaseall
	end

Route12_Johto_FisherMartinSeenText:
	.string "Patience is the\n"
	.string "key to both fish-\l"
	.string "ing and POKéMON.$"

Route12_Johto_FisherMartinBeatenText:
	.string "Gwaaah!$"

Route12_Johto_FisherMartinAfterBattleText:
	.string "I'm too impatient\n"
	.string "for fishing…$"

Route12_Johto_FisherStephenSeenText:
	.string "I feel so content,\n"
	.string "fishing while lis-\l"
	.string "tening to some\l"
	.string "tunes on my radio.$"

Route12_Johto_FisherStephenBeatenText:
	.string "My stupid radio\n"
	.string "distracted me!$"

Route12_Johto_FisherStephenAfterBattleText:
	.string "Have you checked\n"
	.string "out KANTO's radio"
	.string "\pprograms? We get a\n"
	.string "good variety here.$"

Route12_Johto_FisherBarneySeenText:
	.string "What's most impor-\n"
	.string "tant in our every-\l"
	.string "day lives?$"

Route12_Johto_FisherBarneyBeatenText:
	.string "The answer is\n"
	.string "coming up next!$"

Route12_Johto_FisherBarneyAfterBattleText:
	.string "I think electric-\n"
	.string "ity is the most"
	.string "\pimportant thing in\n"
	.string "our daily lives."
	.string "\pIf it weren't,\n"
	.string "people wouldn't"
	.string "\phave made such a\n"
	.string "fuss when the"
	.string "\pPOWER PLANT went\n"
	.string "out of commission.$"

Route12_Johto_FisherKyleSeenText:
	.string "Do you remember?$"

Route12_Johto_FisherKyleBeatenText:
	.string "You do remember?$"

Route12_Johto_FisherKyleAfterBattleText:
	.string "The tug you feel\n"
	.string "on the ROD when"
	.string "\pyou hook a POKé-\n"
	.string "MON…"
	.string "\pThat's the best\n"
	.string "feeling ever for\l"
	.string "an angler like me.$"

Route12_Johto_Route12SignText:
	.string "ROUTE 12"
	.string "\pNORTH TO LAVENDER\n"
	.string "TOWN$"

Route12_Johto_FishingSpotSignText:
	.string "FISHING SPOT$"

Route12_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_12_0, Route12_Johto_CutTree0_Keep
	setmetatile 6, 44, 533, 0
	setmetatile 7, 44, 533, 0
	setmetatile 6, 45, 541, 1
	setmetatile 7, 45, 533, 0
Route12_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_12_1, Route12_Johto_CutTree1_Keep
	setmetatile 6, 48, 541, 1
	setmetatile 7, 48, 541, 1
	setmetatile 6, 49, 533, 0
	setmetatile 7, 49, 533, 0
Route12_Johto_CutTree1_Keep:
	end

Route12_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route12_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_12_0
	setmetatile 6, 44, 533, 0
	setmetatile 7, 44, 533, 0
	setmetatile 6, 45, 541, 1
	setmetatile 7, 45, 533, 0
	special DrawWholeMapView
Route12_Johto_CutTree0_Done:
	releaseall
	end

Route12_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route12_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_12_1
	setmetatile 6, 48, 541, 1
	setmetatile 7, 48, 541, 1
	setmetatile 6, 49, 533, 0
	setmetatile 7, 49, 533, 0
	special DrawWholeMapView
Route12_Johto_CutTree1_Done:
	releaseall
	end
