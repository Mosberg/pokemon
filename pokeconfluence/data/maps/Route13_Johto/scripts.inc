Route13_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route13_Johto_OnLoad
	.byte 0

Route13_Johto_Route13TrainerTips_Entry::
	lockall
	goto Route13_Johto_Route13TrainerTips

Route13_Johto_Route13Sign_Entry::
	lockall
	goto Route13_Johto_Route13Sign

Route13_Johto_Route13DirectionsSign_Entry::
	lockall
	goto Route13_Johto_Route13DirectionsSign


Route13_Johto_TrainerPokefanmAlex::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_ALEX, Route13_Johto_PokefanmAlexSeenText, Route13_Johto_PokefanmAlexBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_ALEX
	lock
	faceplayer
	goto Route13_Johto_TrainerPokefanmAlex_Script

Route13_Johto_TrainerPokefanmAlex_Script:
	message Route13_Johto_PokefanmAlexAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_TrainerPokefanmJoshua::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_JOSHUA, Route13_Johto_PokefanmJoshuaSeenText, Route13_Johto_PokefanmJoshuaBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_JOSHUA
	lock
	faceplayer
	goto Route13_Johto_TrainerPokefanmJoshua_Script

Route13_Johto_TrainerPokefanmJoshua_Script:
	message Route13_Johto_PokefanmJoshuaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_TrainerBirdKeeperPerry::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_PERRY, Route13_Johto_BirdKeeperPerrySeenText, Route13_Johto_BirdKeeperPerryBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_PERRY
	lock
	faceplayer
	goto Route13_Johto_TrainerBirdKeeperPerry_Script

Route13_Johto_TrainerBirdKeeperPerry_Script:
	message Route13_Johto_BirdKeeperPerryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_TrainerBirdKeeperBret::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_BRET, Route13_Johto_BirdKeeperBretSeenText, Route13_Johto_BirdKeeperBretBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_BRET
	lock
	faceplayer
	goto Route13_Johto_TrainerBirdKeeperBret_Script

Route13_Johto_TrainerBirdKeeperBret_Script:
	message Route13_Johto_BirdKeeperBretAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_TrainerHikerKenny::
	trainerbattle_single TRAINER_JOHTO_HIKER_KENNY, Route13_Johto_HikerKennySeenText, Route13_Johto_HikerKennyBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_KENNY
	lock
	faceplayer
	goto Route13_Johto_TrainerHikerKenny_Script

Route13_Johto_TrainerHikerKenny_Script:
	message Route13_Johto_HikerKennyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_Route13TrainerTips:
	message Route13_Johto_Route13TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_Route13Sign:
	message Route13_Johto_Route13SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_Route13DirectionsSign:
	message Route13_Johto_Route13DirectionsSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route13_Johto_PokefanmAlexSeenText:
	.string "Bow down before my\n"
	.string "regal POKéMON!$"

Route13_Johto_PokefanmAlexBeatenText:
	.string "How… How dare you\n"
	.string "mock royalty!$"

Route13_Johto_PokefanmAlexAfterBattleText:
	.string "Doesn't everyone\n"
	.string "wish to someday be\l"
	.string "a king?$"

Route13_Johto_PokefanmJoshuaSeenText:
	.string "Nihihi! Would you\n"
	.string "like to battle my\l"
	.string "PIKACHU gang?$"

Route13_Johto_PokefanmJoshuaBeatenText:
	.string "PI-PIKACHU!$"

Route13_Johto_PokefanmJoshuaAfterBattleText:
	.string "You look like you\n"
	.string "have many POKéMON,"
	.string "\pbut PIKACHU is\n"
	.string "still the best.$"

Route13_Johto_BirdKeeperPerrySeenText:
	.string "Agility is the key\n"
	.string "attribute of bird\l"
	.string "POKéMON.$"

Route13_Johto_BirdKeeperPerryBeatenText:
	.string "You beat me with\n"
	.string "your speed…$"

Route13_Johto_BirdKeeperPerryAfterBattleText:
	.string "Your POKéMON are\n"
	.string "remarkably well-\l"
	.string "trained.$"

Route13_Johto_BirdKeeperBretSeenText:
	.string "Check out my POKé-\n"
	.string "MON. Just look at"
	.string "\ptheir coloring and\n"
	.string "their plumage.$"

Route13_Johto_BirdKeeperBretBeatenText:
	.string "Shoot!\n"
	.string "Not good enough!$"

Route13_Johto_BirdKeeperBretAfterBattleText:
	.string "If you groom them,\n"
	.string "POKéMON get happy.$"

Route13_Johto_HikerKennySeenText:
	.string "I should go to\n"
	.string "ROCK TUNNEL to get\l"
	.string "myself an ONIX.$"

Route13_Johto_HikerKennyBeatenText:
	.string "I lost…$"

Route13_Johto_HikerKennyAfterBattleText:
	.string "Geological fea-\n"
	.string "tures don't appear\l"
	.string "to change."
	.string "\pBut they actually\n"
	.string "change, little by\l"
	.string "little.$"

Route13_Johto_Route13TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pLook! Right there,\n"
	.string "at the left side\l"
	.string "of the post.$"

Route13_Johto_Route13SignText:
	.string "ROUTE 13"
	.string "\pNORTH TO SILENCE\n"
	.string "BRIDGE$"

Route13_Johto_Route13DirectionsSignText:
	.string "NORTH TO LAVENDER\n"
	.string "TOWN"
	.string "\pWEST TO FUCHSIA\n"
	.string "CITY$"

Route13_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_13_0, Route13_Johto_CutTree0_Keep
	setmetatile 44, 4, 533, 0
	setmetatile 45, 4, 533, 0
	setmetatile 44, 5, 541, 1
	setmetatile 45, 5, 541, 1
Route13_Johto_CutTree0_Keep:
	end

Route13_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route13_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_13_0
	setmetatile 44, 4, 533, 0
	setmetatile 45, 4, 533, 0
	setmetatile 44, 5, 541, 1
	setmetatile 45, 5, 541, 1
	special DrawWholeMapView
Route13_Johto_CutTree0_Done:
	releaseall
	end
