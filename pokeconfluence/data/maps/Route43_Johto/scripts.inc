Route43_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, Route43_Johto_OnLoad
	.byte 0

Route43_Johto_OnTransition:
	call Route43_Johto_Route43CheckIfRocketsScene_Cb
	end

Route43_Johto_Route43FruitTree_Entry::
	lockall
	goto Route43_Johto_Route43FruitTree

Route43_Johto_Route43MaxEther_Entry::
	lockall
	goto Route43_Johto_Route43MaxEther

Route43_Johto_Route43Sign1_Entry::
	lockall
	goto Route43_Johto_Route43Sign1

Route43_Johto_Route43Sign2_Entry::
	lockall
	goto Route43_Johto_Route43Sign2

Route43_Johto_Route43TrainerTips_Entry::
	lockall
	goto Route43_Johto_Route43TrainerTips


Route43_Johto_TrainerCamperSpencer::
	trainerbattle_single TRAINER_JOHTO_CAMPER_SPENCER, Route43_Johto_CamperSpencerSeenText, Route43_Johto_CamperSpencerBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_SPENCER
	lock
	faceplayer
	goto Route43_Johto_TrainerCamperSpencer_Script

Route43_Johto_TrainerCamperSpencer_Script:
	message Route43_Johto_CamperSpencerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_TrainerPokemaniacBen::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_BEN, Route43_Johto_PokemaniacBenSeenText, Route43_Johto_PokemaniacBenBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_BEN
	lock
	faceplayer
	goto Route43_Johto_TrainerPokemaniacBen_Script

Route43_Johto_TrainerPokemaniacBen_Script:
	message Route43_Johto_PokemaniacBenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_BRENT1, Route43_Johto_PokemaniacBrentSeenText, Route43_Johto_PokemaniacBrentBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_BRENT
	lock
	faceplayer
	goto Route43_Johto_TrainerPokemaniacBrent_Script

Route43_Johto_TrainerPokemaniacBrent_Script:
	setvar VAR_0x8007, 625
	goto_if_set FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH, Route43_Johto_TrainerPokemaniacBrent_WantsBattle
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_POKEMANIAC_BRENT_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route43_Johto_TrainerPokemaniacBrent_NumberAccepted
	goto_if_set FLAG_JOHTO_BRENT_ASKED_FOR_PHONE_NUMBER, Route43_Johto_TrainerPokemaniacBrent_AskedAlready
	message Route43_Johto_PokemaniacBrentAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_BRENT_ASKED_FOR_PHONE_NUMBER
	call Route43_Johto_TrainerPokemaniacBrent_AskNumber1_Sub
	goto Route43_Johto_TrainerPokemaniacBrent_AskForNumber

Route43_Johto_TrainerPokemaniacBrent_AskedAlready:
	call Route43_Johto_TrainerPokemaniacBrent_AskNumber2_Sub

Route43_Johto_TrainerPokemaniacBrent_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_POKEMANIAC_BRENT_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route43_Johto_TrainerPokemaniacBrent_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route43_Johto_TrainerPokemaniacBrent_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_POKEMANIAC_BRENT1
	call Route43_Johto_TrainerPokemaniacBrent_RegisteredNumber_Sub
	goto Route43_Johto_TrainerPokemaniacBrent_NumberAccepted

Route43_Johto_TrainerPokemaniacBrent_WantsBattle:
	call Route43_Johto_TrainerPokemaniacBrent_Rematch_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WBRENTFIGHTCOUNT
	goto_if_eq VAR_RESULT, 3, Route43_Johto_TrainerPokemaniacBrent_Fight3
	goto_if_eq VAR_RESULT, 2, Route43_Johto_TrainerPokemaniacBrent_Fight2
	goto_if_eq VAR_RESULT, 1, Route43_Johto_TrainerPokemaniacBrent_Fight1
	goto_if_eq VAR_RESULT, 0, Route43_Johto_TrainerPokemaniacBrent_LoadFight0

Route43_Johto_TrainerPokemaniacBrent_Fight3:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route43_Johto_TrainerPokemaniacBrent_LoadFight3

Route43_Johto_TrainerPokemaniacBrent_Fight2:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route43_Johto_TrainerPokemaniacBrent_LoadFight2

Route43_Johto_TrainerPokemaniacBrent_Fight1:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, Route43_Johto_TrainerPokemaniacBrent_LoadFight1

Route43_Johto_TrainerPokemaniacBrent_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_POKEMANIAC_BRENT1, Route43_Johto_PokemaniacBrentBeatenText
	setvar VAR_JOHTO_MEM_WBRENTFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_POKEMANIAC_BRENT2, Route43_Johto_PokemaniacBrentBeatenText
	setvar VAR_JOHTO_MEM_WBRENTFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_POKEMANIAC_BRENT3, Route43_Johto_PokemaniacBrentBeatenText
	setvar VAR_JOHTO_MEM_WBRENTFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_POKEMANIAC_BRENT4, Route43_Johto_PokemaniacBrentBeatenText
	clearflag FLAG_JOHTO_ENGINE_BRENT_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route43_Johto_TrainerPokemaniacBrent_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route43_Johto_TrainerPokemaniacBrent_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route43_Johto_TrainerPokemaniacRon::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_RON, Route43_Johto_PokemaniacRonSeenText, Route43_Johto_PokemaniacRonBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_RON
	lock
	faceplayer
	goto Route43_Johto_TrainerPokemaniacRon_Script

Route43_Johto_TrainerPokemaniacRon_Script:
	message Route43_Johto_PokemaniacRonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_TrainerFisherMarvin::
	trainerbattle_single TRAINER_JOHTO_FISHER_MARVIN, Route43_Johto_FisherMarvinSeenText, Route43_Johto_FisherMarvinBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_MARVIN
	lock
	faceplayer
	goto Route43_Johto_TrainerFisherMarvin_Script

Route43_Johto_TrainerFisherMarvin_Script:
	message Route43_Johto_FisherMarvinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_TIFFANY3, Route43_Johto_PicnickerTiffanySeenText, Route43_Johto_PicnickerTiffanyBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_TIFFANY
	lock
	faceplayer
	goto Route43_Johto_TrainerPicnickerTiffany_Script

Route43_Johto_TrainerPicnickerTiffany_Script:
	setvar VAR_0x8007, 365
	goto_if_set FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH, Route43_Johto_TrainerPicnickerTiffany_WantsBattle
	goto_if_set FLAG_JOHTO_ENGINE_TIFFANY_HAS_PINK_BOW, Route43_Johto_TrainerPicnickerTiffany_HasPinkBow
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_TIFFANY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route43_Johto_TrainerPicnickerTiffany_NumberAccepted
	setvar VAR_0x8004, SPECIES_CLEFAIRY
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, 0, Route43_Johto_TrainerPicnickerTiffany_NoClefairy
	goto_if_set FLAG_JOHTO_TIFFANY_ASKED_FOR_PHONE_NUMBER, Route43_Johto_TrainerPicnickerTiffany_AskedAlready
	message Route43_Johto_PicnickerTiffanyWantsPicnicText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_TIFFANY_ASKED_FOR_PHONE_NUMBER
	call Route43_Johto_TrainerPicnickerTiffany_AskNumber1_Sub
	goto Route43_Johto_TrainerPicnickerTiffany_AskForNumber

Route43_Johto_TrainerPicnickerTiffany_AskedAlready:
	call Route43_Johto_TrainerPicnickerTiffany_AskNumber2_Sub

Route43_Johto_TrainerPicnickerTiffany_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_TIFFANY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_TIFFANY_HAS_PINK_BOW
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route43_Johto_TrainerPicnickerTiffany_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route43_Johto_TrainerPicnickerTiffany_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_PICNICKER_TIFFANY3
	call Route43_Johto_TrainerPicnickerTiffany_RegisteredNumber_Sub
	goto Route43_Johto_TrainerPicnickerTiffany_NumberAccepted

Route43_Johto_TrainerPicnickerTiffany_WantsBattle:
	call Route43_Johto_TrainerPicnickerTiffany_Rematch_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WTIFFANYFIGHTCOUNT
	goto_if_eq VAR_RESULT, 3, Route43_Johto_TrainerPicnickerTiffany_Fight3
	goto_if_eq VAR_RESULT, 2, Route43_Johto_TrainerPicnickerTiffany_Fight2
	goto_if_eq VAR_RESULT, 1, Route43_Johto_TrainerPicnickerTiffany_Fight1
	goto_if_eq VAR_RESULT, 0, Route43_Johto_TrainerPicnickerTiffany_LoadFight0

Route43_Johto_TrainerPicnickerTiffany_Fight3:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route43_Johto_TrainerPicnickerTiffany_LoadFight3

Route43_Johto_TrainerPicnickerTiffany_Fight2:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route43_Johto_TrainerPicnickerTiffany_LoadFight2

Route43_Johto_TrainerPicnickerTiffany_Fight1:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route43_Johto_TrainerPicnickerTiffany_LoadFight1

Route43_Johto_TrainerPicnickerTiffany_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_TIFFANY3, Route43_Johto_PicnickerTiffanyBeatenText
	setvar VAR_JOHTO_MEM_WTIFFANYFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_TIFFANY1, Route43_Johto_PicnickerTiffanyBeatenText
	setvar VAR_JOHTO_MEM_WTIFFANYFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_TIFFANY2, Route43_Johto_PicnickerTiffanyBeatenText
	setvar VAR_JOHTO_MEM_WTIFFANYFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_TIFFANY4, Route43_Johto_PicnickerTiffanyBeatenText
	clearflag FLAG_JOHTO_ENGINE_TIFFANY_READY_FOR_REMATCH
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany_HasPinkBow:
	call Route43_Johto_TrainerPicnickerTiffany_Gift_Sub
	giveitem ITEM_PINK_BOW
	goto_if_eq VAR_RESULT, 0, Route43_Johto_TrainerPicnickerTiffany_NoRoom
	clearflag FLAG_JOHTO_ENGINE_TIFFANY_HAS_PINK_BOW
	setflag FLAG_JOHTO_TIFFANY_GAVE_PINK_BOW
	goto Route43_Johto_TrainerPicnickerTiffany_NumberAccepted

Route43_Johto_TrainerPicnickerTiffany_NoRoom:
	goto Route43_Johto_TrainerPicnickerTiffany_PackFull

Route43_Johto_TrainerPicnickerTiffany_NoClefairy:
	message Route43_Johto_PicnickerTiffanyClefairyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_TrainerPicnickerTiffany_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route43_Johto_TrainerPicnickerTiffany_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

Route43_Johto_TrainerPicnickerTiffany_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route43_Johto_TrainerPicnickerTiffany_PackFull:
	goto Johto_Std_PackFullFScript

Route43_Johto_Route43Sign1:
	message Route43_Johto_Route43Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_Route43Sign2:
	message Route43_Johto_Route43Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_Route43TrainerTips:
	message Route43_Johto_Route43TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43_Johto_Route43FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_43, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PERSIM_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_43
	releaseall
	end

Route43_Johto_Route43MaxEther:
	finditem ITEM_MAX_ETHER
	releaseall
	end

Route43_Johto_TrainerPokemaniacBrent_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route43_Johto_TrainerPokemaniacBrent_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route43_Johto_TrainerPokemaniacBrent_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route43_Johto_TrainerPokemaniacBrent_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route43_Johto_TrainerPicnickerTiffany_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route43_Johto_TrainerPicnickerTiffany_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route43_Johto_TrainerPicnickerTiffany_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route43_Johto_TrainerPicnickerTiffany_Rematch_Sub:
	goto Johto_Std_RematchFScript_Sub

Route43_Johto_TrainerPicnickerTiffany_Gift_Sub:
	goto Johto_Std_GiftFScript_Sub

Route43_Johto_Route43CheckIfRocketsScene_Cb:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, Route43_Johto_Route43CheckIfRocketsScene_NoRockets_Cb
	setvar VAR_JOHTO_SCENE_ROUTE_43_GATE, 0
	return

Route43_Johto_Route43CheckIfRocketsScene_NoRockets_Cb:
	setvar VAR_JOHTO_SCENE_ROUTE_43_GATE, 1
	return

Route43_Johto_PokemaniacBenSeenText:
	.string "I love POKéMON!"
	.string "\pThat's why I\n"
	.string "started--and why"
	.string "\pI'll keep on col-\n"
	.string "lecting POKéMON!$"

Route43_Johto_PokemaniacBenBeatenText:
	.string "How could you do\n"
	.string "this to me?$"

Route43_Johto_PokemaniacBenAfterBattleText:
	.string "What else do I\n"
	.string "like besides\l"
	.string "POKéMON?"
	.string "\pMARY on the radio.\n"
	.string "I bet she's cute!$"

Route43_Johto_PokemaniacBrentSeenText:
	.string "Hey! Do you have\n"
	.string "any rare POKéMON?$"

Route43_Johto_PokemaniacBrentBeatenText:
	.string "Oh, my poor POKé-\n"
	.string "MON! Darlings!$"

Route43_Johto_PokemaniacBrentAfterBattleText:
	.string "I'd be happy just\n"
	.string "to own a single\l"
	.string "rare POKéMON.$"

Route43_Johto_PokemaniacRonSeenText:
	.string "Would you get\n"
	.string "this?"
	.string "\pSome SILVER guy\n"
	.string "made fun of my\l"
	.string "POKéMON!"
	.string "\pDarn it! My POKé-\n"
	.string "MON's great!$"

Route43_Johto_PokemaniacRonBeatenText:
	.string "My NIDOKING did\n"
	.string "pretty right on!$"

Route43_Johto_PokemaniacRonAfterBattleText:
	.string "It's okay for\n"
	.string "people to like"
	.string "\pdifferent types\n"
	.string "of POKéMON."
	.string "\pPOKéMON isn't just\n"
	.string "about having the\l"
	.string "most powerful one.$"

Route43_Johto_FisherMarvinSeenText:
	.string "I'm in a slump."
	.string "\pMaybe it's the\n"
	.string "gear I'm using."
	.string "\pLet's battle for a\n"
	.string "change of pace!$"

Route43_Johto_FisherMarvinBeatenText:
	.string "I lost, but I feel\n"
	.string "better anyway.$"

Route43_Johto_FisherMarvinAfterBattleText:
	.string "KURT's LURE BALL\n"
	.string "is the best for"
	.string "\pcatching hooked\n"
	.string "POKéMON."
	.string "\pIt's much more\n"
	.string "effective than a\l"
	.string "ULTRA BALL.$"

Route43_Johto_CamperSpencerSeenText:
	.string "I can do so much\n"
	.string "with my POKéMON--\l"
	.string "it's super-fun!$"

Route43_Johto_CamperSpencerBeatenText:
	.string "Losing isn't fun\n"
	.string "at all…$"

Route43_Johto_CamperSpencerAfterBattleText:
	.string "What is going on\n"
	.string "at LAKE OF RAGE?"
	.string "\pWe were planning\n"
	.string "to camp there.$"

Route43_Johto_PicnickerTiffanySeenText:
	.string "Are you going to\n"
	.string "LAKE OF RAGE too?"
	.string "\pLet's play for a \n"
	.string "little while!$"

Route43_Johto_PicnickerTiffanyBeatenText:
	.string "I played too much!$"

Route43_Johto_PicnickerTiffanyWantsPicnicText:
	.string "I'm having a pic-\n"
	.string "nic with POKéMON."
	.string "\pWon't you join us?$"

Route43_Johto_PicnickerTiffanyClefairyText:
	.string "Isn't my CLEFAIRY\n"
	.string "just the most\l"
	.string "adorable thing?$"

Route43_Johto_Route43Sign1Text:
	.string "ROUTE 43"
	.string "\pLAKE OF RAGE -\n"
	.string "MAHOGANY TOWN$"

Route43_Johto_Route43Sign2Text:
	.string "ROUTE 43"
	.string "\pLAKE OF RAGE -\n"
	.string "MAHOGANY TOWN$"

Route43_Johto_Route43TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pAll POKéMON have\n"
	.string "pros and cons"
	.string "\pdepending on their\n"
	.string "types."
	.string "\pIf their types\n"
	.string "differ, a higher-"
	.string "\plevel POKéMON may\n"
	.string "lose in battle."
	.string "\pLearn which types\n"
	.string "are strong and"
	.string "\pweak against your\n"
	.string "POKéMON's type.$"

Route43_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_43_0, Route43_Johto_CutTree0_Keep
	setmetatile 2, 28, 514, 0
	setmetatile 3, 28, 514, 0
	setmetatile 2, 29, 591, 0
	setmetatile 3, 29, 514, 0
Route43_Johto_CutTree0_Keep:
	end

Route43_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route43_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_43_0
	setmetatile 2, 28, 514, 0
	setmetatile 3, 28, 514, 0
	setmetatile 2, 29, 591, 0
	setmetatile 3, 29, 514, 0
	special DrawWholeMapView
Route43_Johto_CutTree0_Done:
	releaseall
	end
