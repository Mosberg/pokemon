Route19_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route19_Johto_OnLoad
	.byte 0

Route19_Johto_OnLoad:
	call Route19_Johto_Route19ClearRocksCallback_Cb
	end

Route19_Johto_Route19Fisher1Script_Entry::
	lockall
	goto Route19_Johto_Route19Fisher1Script

Route19_Johto_Route19Fisher2Script_Entry::
	lockall
	goto Route19_Johto_Route19Fisher2Script

Route19_Johto_Route19Sign_Entry::
	lockall
	goto Route19_Johto_Route19Sign

Route19_Johto_CarefulSwimmingSign_Entry::
	lockall
	goto Route19_Johto_CarefulSwimmingSign


Route19_Johto_TrainerSwimmerfDawn::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_DAWN, Route19_Johto_SwimmerfDawnSeenText, Route19_Johto_SwimmerfDawnBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_DAWN
	lock
	faceplayer
	goto Route19_Johto_TrainerSwimmerfDawn_Script

Route19_Johto_TrainerSwimmerfDawn_Script:
	message Route19_Johto_SwimmerfDawnAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_TrainerSwimmermHarold::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_HAROLD, Route19_Johto_SwimmermHaroldSeenText, Route19_Johto_SwimmermHaroldBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_HAROLD
	lock
	faceplayer
	goto Route19_Johto_TrainerSwimmermHarold_Script

Route19_Johto_TrainerSwimmermHarold_Script:
	message Route19_Johto_SwimmermHaroldAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_TrainerSwimmermJerome::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_JEROME, Route19_Johto_SwimmermJeromeSeenText, Route19_Johto_SwimmermJeromeBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_JEROME
	lock
	faceplayer
	goto Route19_Johto_TrainerSwimmermJerome_Script

Route19_Johto_TrainerSwimmermJerome_Script:
	message Route19_Johto_SwimmermJeromeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_TrainerSwimmermTucker::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_TUCKER, Route19_Johto_SwimmermTuckerSeenText, Route19_Johto_SwimmermTuckerBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_TUCKER
	lock
	faceplayer
	goto Route19_Johto_TrainerSwimmermTucker_Script

Route19_Johto_TrainerSwimmermTucker_Script:
	message Route19_Johto_SwimmermTuckerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19Fisher1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_CINNABAR_ROCKS_CLEARED, Route19_Johto_Route19Fisher1Script_RocksCleared
	message Route19_Johto_Route19Fisher1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19Fisher1Script_RocksCleared:
	message Route19_Johto_Route19Fisher1Text_RocksCleared
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19Fisher2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_CINNABAR_ROCKS_CLEARED, Route19_Johto_Route19Fisher2Script_RocksCleared
	message Route19_Johto_Route19Fisher2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19Fisher2Script_RocksCleared:
	message Route19_Johto_Route19Fisher2Text_RocksCleared
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19Sign:
	message Route19_Johto_Route19SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_CarefulSwimmingSign:
	message Route19_Johto_CarefulSwimmingSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19_Johto_Route19ClearRocksCallback_Cb:
	goto_if_set FLAG_JOHTO_CINNABAR_ROCKS_CLEARED, Route19_Johto_Route19ClearRocksCallback_Done_Cb
	setmetatile 6, 6, 649, 1
	setmetatile 7, 6, 650, 1
	setmetatile 6, 7, 651, 1
	setmetatile 7, 7, 652, 1
	special DrawWholeMapView
	setmetatile 8, 6, 649, 1
	setmetatile 9, 6, 650, 1
	setmetatile 8, 7, 651, 1
	setmetatile 9, 7, 652, 1
	special DrawWholeMapView
	setmetatile 10, 6, 649, 1
	setmetatile 11, 6, 650, 1
	setmetatile 10, 7, 651, 1
	setmetatile 11, 7, 652, 1
	special DrawWholeMapView
	setmetatile 12, 8, 649, 1
	setmetatile 13, 8, 650, 1
	setmetatile 12, 9, 651, 1
	setmetatile 13, 9, 652, 1
	special DrawWholeMapView
	setmetatile 4, 8, 649, 1
	setmetatile 5, 8, 650, 1
	setmetatile 4, 9, 651, 1
	setmetatile 5, 9, 652, 1
	special DrawWholeMapView
	setmetatile 10, 10, 649, 1
	setmetatile 11, 10, 650, 1
	setmetatile 10, 11, 651, 1
	setmetatile 11, 11, 652, 1
	special DrawWholeMapView

Route19_Johto_Route19ClearRocksCallback_Done_Cb:
	return

Route19_Johto_SwimmermHaroldSeenText:
	.string "Have you ever gone\n"
	.string "swimming in the\l"
	.string "sea at night?$"

Route19_Johto_SwimmermHaroldBeatenText:
	.string "Glub…$"

Route19_Johto_SwimmermHaroldAfterBattleText:
	.string "At night, the sea\n"
	.string "turns black. It"
	.string "\pfeels like it will\n"
	.string "swallow you up.$"

Route19_Johto_SwimmermTuckerSeenText:
	.string "Pant, pant…\n"
	.string "Just… a little…"
	.string "\pfarther… to…\n"
	.string "FUCHSIA…$"

Route19_Johto_SwimmermTuckerBeatenText:
	.string "I'm drowning!$"

Route19_Johto_SwimmermTuckerAfterBattleText:
	.string "I… asked my girl-\n"
	.string "friend to swim to\l"
	.string "FUCHSIA… Gasp…$"

Route19_Johto_SwimmerfDawnSeenText:
	.string "I'm disgusted by\n"
	.string "wimpy people!$"

Route19_Johto_SwimmerfDawnBeatenText:
	.string "I could beat you\n"
	.string "at swimming…$"

Route19_Johto_SwimmerfDawnAfterBattleText:
	.string "It's a quick swim\n"
	.string "between FUCHSIA"
	.string "\pand SEAFOAM IS-\n"
	.string "LANDS…"
	.string "\pSheesh, some big\n"
	.string "man my boyfriend"
	.string "\pis! What a wimp!$"

Route19_Johto_SwimmermJeromeSeenText:
	.string "Swimming?\n"
	.string "I'm lousy at it."
	.string "\pI'm just splashing\n"
	.string "around in these\l"
	.string "shallow waters.$"

Route19_Johto_SwimmermJeromeBeatenText:
	.string "I thought I could\n"
	.string "win.$"

Route19_Johto_SwimmermJeromeAfterBattleText:
	.string "I might be bad at\n"
	.string "swimming, but I\l"
	.string "love the sea.$"

Route19_Johto_Route19Fisher1Text:
	.string "Sorry. This road\n"
	.string "is closed for\l"
	.string "construction."
	.string "\pIf you want to get\n"
	.string "to CINNABAR, you'd"
	.string "\pbetter go south\n"
	.string "from PALLET TOWN.$"

Route19_Johto_Route19Fisher1Text_RocksCleared:
	.string "I'm all sweaty.\n"
	.string "Time for a swim!$"

Route19_Johto_Route19Fisher2Text:
	.string "Who knows how long\n"
	.string "it would take to\l"
	.string "move this boulder…$"

Route19_Johto_Route19Fisher2Text_RocksCleared:
	.string "The roadwork is\n"
	.string "finally finished."
	.string "\pNow I can go\n"
	.string "fishing again.$"

Route19_Johto_Route19SignText:
	.string "ROUTE 19"
	.string "\pFUCHSIA CITY -\n"
	.string "SEAFOAM ISLANDS$"

Route19_Johto_CarefulSwimmingSignText:
	.string "Please be careful\n"
	.string "if you are swim-\l"
	.string "ming to SEAFOAM\l"
	.string "ISLANDS."
	.string "\pFUCHSIA POLICE$"
