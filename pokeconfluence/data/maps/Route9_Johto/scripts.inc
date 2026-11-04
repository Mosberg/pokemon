Route9_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route9_Johto_OnLoad
	.byte 0

Route9_Johto_Route9Sign_Entry::
	lockall
	goto Route9_Johto_Route9Sign


Route9_Johto_TrainerCamperDean::
	trainerbattle_single TRAINER_JOHTO_CAMPER_DEAN, Route9_Johto_CamperDeanSeenText, Route9_Johto_CamperDeanBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_DEAN
	lock
	faceplayer
	goto Route9_Johto_TrainerCamperDean_Script

Route9_Johto_TrainerCamperDean_Script:
	message Route9_Johto_CamperDeanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_TrainerPicnickerHeidi::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_HEIDI, Route9_Johto_PicnickerHeidiSeenText, Route9_Johto_PicnickerHeidiBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_HEIDI
	lock
	faceplayer
	goto Route9_Johto_TrainerPicnickerHeidi_Script

Route9_Johto_TrainerPicnickerHeidi_Script:
	message Route9_Johto_PicnickerHeidiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_TrainerCamperSid::
	trainerbattle_single TRAINER_JOHTO_CAMPER_SID, Route9_Johto_CamperSidSeenText, Route9_Johto_CamperSidBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_SID
	lock
	faceplayer
	goto Route9_Johto_TrainerCamperSid_Script

Route9_Johto_TrainerCamperSid_Script:
	message Route9_Johto_CamperSidAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_TrainerPicnickerEdna::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_EDNA, Route9_Johto_PicnickerEdnaSeenText, Route9_Johto_PicnickerEdnaBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_EDNA
	lock
	faceplayer
	goto Route9_Johto_TrainerPicnickerEdna_Script

Route9_Johto_TrainerPicnickerEdna_Script:
	message Route9_Johto_PicnickerEdnaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_TrainerHikerTim::
	trainerbattle_single TRAINER_JOHTO_HIKER_TIM, Route9_Johto_HikerTimSeenText, Route9_Johto_HikerTimBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_TIM
	lock
	faceplayer
	goto Route9_Johto_TrainerHikerTim_Script

Route9_Johto_TrainerHikerTim_Script:
	message Route9_Johto_HikerTimAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_TrainerHikerSidney::
	trainerbattle_single TRAINER_JOHTO_HIKER_SIDNEY, Route9_Johto_HikerSidneySeenText, Route9_Johto_HikerSidneyBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_SIDNEY
	lock
	faceplayer
	goto Route9_Johto_TrainerHikerSidney_Script

Route9_Johto_TrainerHikerSidney_Script:
	message Route9_Johto_HikerSidneyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_Route9Sign:
	message Route9_Johto_Route9SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route9_Johto_CamperDeanSeenText:
	.string "I came to explore\n"
	.string "ROCK TUNNEL.$"

Route9_Johto_CamperDeanBeatenText:
	.string "Whoa! Danger, man.$"

Route9_Johto_CamperDeanAfterBattleText:
	.string "My POKéMON were\n"
	.string "hurt before even"
	.string "\pentering ROCK\n"
	.string "TUNNEL."
	.string "\pI'd better take\n"
	.string "them to a POKéMON\l"
	.string "CENTER right away.$"

Route9_Johto_PicnickerHeidiSeenText:
	.string "Have you ever been\n"
	.string "to a picnic?"
	.string "\pThey're so much\n"
	.string "fun!$"

Route9_Johto_PicnickerHeidiBeatenText:
	.string "Ohhhh!$"

Route9_Johto_PicnickerHeidiAfterBattleText:
	.string "We bake lots of\n"
	.string "goodies and share"
	.string "\pthem all around.\n"
	.string "They're delicious!$"

Route9_Johto_CamperSidSeenText:
	.string "Hey, you!\n"
	.string "Don't litter!$"

Route9_Johto_CamperSidBeatenText:
	.string "I was just point-\n"
	.string "ing out…$"

Route9_Johto_CamperSidAfterBattleText:
	.string "Sorry. You weren't\n"
	.string "littering. It was\l"
	.string "my mistake.$"

Route9_Johto_PicnickerEdnaSeenText:
	.string "People shouldn't\n"
	.string "leave any litter\l"
	.string "behind.$"

Route9_Johto_PicnickerEdnaBeatenText:
	.string "Ohh… I lost…$"

Route9_Johto_PicnickerEdnaAfterBattleText:
	.string "Conserving energy\n"
	.string "is important, but"
	.string "\pthe environment is\n"
	.string "even more vital.$"

Route9_Johto_HikerTimSeenText:
	.string "She'll be coming\n"
	.string "'round MT.SILVER\l"
	.string "when she comes…"
	.string "\pMT.SILVER is in\n"
	.string "JOHTO, right?$"

Route9_Johto_HikerTimBeatenText:
	.string "I was too busy\n"
	.string "singing…$"

Route9_Johto_HikerTimAfterBattleText:
	.string "Battles are about\n"
	.string "concentration.$"

Route9_Johto_HikerSidneySeenText:
	.string "I'll tell you a\n"
	.string "secret."
	.string "\pBut first, we\n"
	.string "battle!$"

Route9_Johto_HikerSidneyBeatenText:
	.string "Oh, dang!\n"
	.string "I lost that…$"

Route9_Johto_HikerSidneyAfterBattleText:
	.string "The POWER PLANT is\n"
	.string "across a small\l"
	.string "river.$"

Route9_Johto_Route9SignText:
	.string "ROUTE 9"
	.string "\pCERULEAN CITY -\n"
	.string "ROCK TUNNEL$"

Route9_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_9_0, Route9_Johto_CutTree0_Keep
	setmetatile 4, 8, 533, 0
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
Route9_Johto_CutTree0_Keep:
	end

Route9_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route9_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_9_0
	setmetatile 4, 8, 533, 0
	setmetatile 5, 8, 533, 0
	setmetatile 4, 9, 541, 1
	setmetatile 5, 9, 533, 0
	special DrawWholeMapView
Route9_Johto_CutTree0_Done:
	releaseall
	end
