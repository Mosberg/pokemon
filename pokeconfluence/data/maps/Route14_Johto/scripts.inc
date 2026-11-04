Route14_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route14_Johto_OnLoad
	.byte 0

Route14_Johto_Kim_Entry::
	lockall
	goto Route14_Johto_Kim


Route14_Johto_Kim:
	faceplayer
	goto Johto_Std_Trade_KIM

Route14_Johto_TrainerPokefanmCarter::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_CARTER, Route14_Johto_PokefanmCarterSeenText, Route14_Johto_PokefanmCarterBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_CARTER
	lock
	faceplayer
	goto Route14_Johto_TrainerPokefanmCarter_Script

Route14_Johto_TrainerPokefanmCarter_Script:
	message Route14_Johto_PokefanmCarterAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route14_Johto_TrainerBirdKeeperRoy::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_ROY, Route14_Johto_BirdKeeperRoySeenText, Route14_Johto_BirdKeeperRoyBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_ROY
	lock
	faceplayer
	goto Route14_Johto_TrainerBirdKeeperRoy_Script

Route14_Johto_TrainerBirdKeeperRoy_Script:
	message Route14_Johto_BirdKeeperRoyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route14_Johto_TrainerPokefanmTrevor::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_TREVOR, Route14_Johto_PokefanmTrevorSeenText, Route14_Johto_PokefanmTrevorBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_TREVOR
	lock
	faceplayer
	goto Route14_Johto_TrainerPokefanmTrevor_Script

Route14_Johto_TrainerPokefanmTrevor_Script:
	message Route14_Johto_PokefanmTrevorAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route14_Johto_PokefanmCarterSeenText:
	.string "Let me tell you,\n"
	.string "I had a hard time"
	.string "\pcatching my prized\n"
	.string "POKéMON.$"

Route14_Johto_PokefanmCarterBeatenText:
	.string "Awaaah!$"

Route14_Johto_PokefanmCarterAfterBattleText:
	.string "SQUIRTLE, CHARMAN-\n"
	.string "DER and BULBASAUR…"
	.string "\pI think that's a\n"
	.string "well-balanced mix.$"

Route14_Johto_BirdKeeperRoySeenText:
	.string "My dream is to fly\n"
	.string "with my beloved\l"
	.string "bird POKéMON.$"

Route14_Johto_BirdKeeperRoyBeatenText:
	.string "I can dream, but I\n"
	.string "can't ever fly…$"

Route14_Johto_BirdKeeperRoyAfterBattleText:
	.string "You have POKéMON\n"
	.string "that know the HM"
	.string "\pmove FLY, don't\n"
	.string "you? I envy you.$"

Route14_Johto_PokefanmTrevorSeenText:
	.string "Hi. Did you know…?"
	.string "\pPOKéMON get more\n"
	.string "friendly if you"
	.string "\ptrain them in a\n"
	.string "place that they\l"
	.string "remember.$"

Route14_Johto_PokefanmTrevorBeatenText:
	.string "Where did I meet\n"
	.string "this PSYDUCK?$"

Route14_Johto_PokefanmTrevorAfterBattleText:
	.string "If only there were\n"
	.string "an easy way to"
	.string "\pidentify where I\n"
	.string "got my POKéMON…$"

Route14_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_14_0, Route14_Johto_CutTree0_Keep
	setmetatile 4, 8, 533, 0
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
Route14_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_14_1, Route14_Johto_CutTree1_Keep
	setmetatile 10, 14, 533, 0
	setmetatile 11, 14, 533, 0
	setmetatile 10, 15, 541, 1
	setmetatile 11, 15, 533, 0
Route14_Johto_CutTree1_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_14_2, Route14_Johto_CutTree2_Keep
	setmetatile 2, 24, 533, 0
	setmetatile 3, 24, 533, 0
	setmetatile 2, 25, 541, 1
	setmetatile 3, 25, 533, 0
Route14_Johto_CutTree2_Keep:
	end

Route14_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route14_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_14_0
	setmetatile 4, 8, 533, 0
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
	special DrawWholeMapView
Route14_Johto_CutTree0_Done:
	releaseall
	end

Route14_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route14_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_14_1
	setmetatile 10, 14, 533, 0
	setmetatile 11, 14, 533, 0
	setmetatile 10, 15, 541, 1
	setmetatile 11, 15, 533, 0
	special DrawWholeMapView
Route14_Johto_CutTree1_Done:
	releaseall
	end

Route14_Johto_CutTree2::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route14_Johto_CutTree2_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_14_2
	setmetatile 2, 24, 533, 0
	setmetatile 3, 24, 533, 0
	setmetatile 2, 25, 541, 1
	setmetatile 3, 25, 533, 0
	special DrawWholeMapView
Route14_Johto_CutTree2_Done:
	releaseall
	end
