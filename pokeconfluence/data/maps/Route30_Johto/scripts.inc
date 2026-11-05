Route30_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route30_Johto_OnLoad
	.byte 0

Route30_Johto_YoungsterJoey_ImportantBattleScript_Entry::
	lockall
	goto Route30_Johto_YoungsterJoey_ImportantBattleScript

Route30_Johto_Route30YoungsterScript_Entry::
	lockall
	goto Route30_Johto_Route30YoungsterScript

Route30_Johto_Route30FruitTree1_Entry::
	lockall
	goto Route30_Johto_Route30FruitTree1

Route30_Johto_Route30FruitTree2_Entry::
	lockall
	goto Route30_Johto_Route30FruitTree2

Route30_Johto_Route30CooltrainerFScript_Entry::
	lockall
	goto Route30_Johto_Route30CooltrainerFScript

Route30_Johto_Route30Antidote_Entry::
	lockall
	goto Route30_Johto_Route30Antidote

Route30_Johto_Route30Sign_Entry::
	lockall
	goto Route30_Johto_Route30Sign

Route30_Johto_MrPokemonsHouseDirectionsSign_Entry::
	lockall
	goto Route30_Johto_MrPokemonsHouseDirectionsSign

Route30_Johto_MrPokemonsHouseSign_Entry::
	lockall
	goto Route30_Johto_MrPokemonsHouseSign

Route30_Johto_Route30TrainerTips_Entry::
	lockall
	goto Route30_Johto_Route30TrainerTips


Route30_Johto_YoungsterJoey_ImportantBattleScript:
	waitse
	playbgm MUS_DUMMY, FALSE
	message Route30_Johto_Text_UseTackle
	waitmessage
	delay 30
	closemessage
	playse SE_M_TAIL_WHIP
	applymovement 7, Route30_Johto_Route30_JoeysRattataAttacksMovement
	waitmovement 7
	faceplayer
	message Route30_Johto_Text_ThisIsABigBattle
	waitmessage
	waitbuttonpress
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	closemessage
	playse SE_M_TAIL_WHIP
	applymovement 6, Route30_Johto_Route30_MikeysRattataAttacksMovement
	waitmovement 6
	fadedefaultbgm
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_JOEY1, Route30_Johto_YoungsterJoey1SeenText, Route30_Johto_YoungsterJoey1BeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_JOEY
	lock
	faceplayer
	goto Route30_Johto_TrainerYoungsterJoey_Script

Route30_Johto_TrainerYoungsterJoey_Script:
	setvar VAR_0x8007, 138
	goto_if_set FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH, Route30_Johto_TrainerYoungsterJoey_Rematch
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route30_Johto_TrainerYoungsterJoey_NumberAccepted
	goto_if_set FLAG_JOHTO_JOEY_ASKED_FOR_PHONE_NUMBER, Route30_Johto_TrainerYoungsterJoey_AskAgain
	message Route30_Johto_YoungsterJoey1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_JOEY_ASKED_FOR_PHONE_NUMBER
	call Route30_Johto_TrainerYoungsterJoey_AskNumber1_Sub
	goto Route30_Johto_TrainerYoungsterJoey_RequestNumber

Route30_Johto_TrainerYoungsterJoey_AskAgain:
	call Route30_Johto_TrainerYoungsterJoey_AskNumber2_Sub

Route30_Johto_TrainerYoungsterJoey_RequestNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route30_Johto_TrainerYoungsterJoey_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route30_Johto_TrainerYoungsterJoey_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_YOUNGSTER_JOEY1
	call Route30_Johto_TrainerYoungsterJoey_RegisteredNumber_Sub
	goto Route30_Johto_TrainerYoungsterJoey_NumberAccepted

Route30_Johto_TrainerYoungsterJoey_Rematch:
	call Route30_Johto_TrainerYoungsterJoey_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WJOEYFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route30_Johto_TrainerYoungsterJoey_Fight4
	goto_if_eq VAR_RESULT, 3, Route30_Johto_TrainerYoungsterJoey_Fight3
	goto_if_eq VAR_RESULT, 2, Route30_Johto_TrainerYoungsterJoey_Fight2
	goto_if_eq VAR_RESULT, 1, Route30_Johto_TrainerYoungsterJoey_Fight1
	goto_if_eq VAR_RESULT, 0, Route30_Johto_TrainerYoungsterJoey_LoadFight0

Route30_Johto_TrainerYoungsterJoey_Fight4:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route30_Johto_TrainerYoungsterJoey_LoadFight4

Route30_Johto_TrainerYoungsterJoey_Fight3:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route30_Johto_TrainerYoungsterJoey_LoadFight3

Route30_Johto_TrainerYoungsterJoey_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_OLIVINE, Route30_Johto_TrainerYoungsterJoey_LoadFight2

Route30_Johto_TrainerYoungsterJoey_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_GOLDENROD, Route30_Johto_TrainerYoungsterJoey_LoadFight1

Route30_Johto_TrainerYoungsterJoey_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_YOUNGSTER_JOEY1, Route30_Johto_YoungsterJoey1BeatenText
	setvar VAR_JOHTO_MEM_WJOEYFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_YOUNGSTER_JOEY2, Route30_Johto_YoungsterJoey1BeatenText
	setvar VAR_JOHTO_MEM_WJOEYFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_YOUNGSTER_JOEY3, Route30_Johto_YoungsterJoey1BeatenText
	setvar VAR_JOHTO_MEM_WJOEYFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_YOUNGSTER_JOEY4, Route30_Johto_YoungsterJoey1BeatenText
	setvar VAR_JOHTO_MEM_WJOEYFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_YOUNGSTER_JOEY5, Route30_Johto_YoungsterJoey1BeatenText
	clearflag FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH
	goto_if_set FLAG_JOHTO_JOEY_HP_UP, Route30_Johto_TrainerYoungsterJoey_GiveHPUp
	goto_if_set FLAG_JOHTO_GOT_HP_UP_FROM_JOEY, Route30_Johto_TrainerYoungsterJoey_done
	call Route30_Johto_TrainerYoungsterJoey_RematchGift_Sub
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, 0, Route30_Johto_TrainerYoungsterJoey_PackFull
	setflag FLAG_JOHTO_GOT_HP_UP_FROM_JOEY
	goto Route30_Johto_TrainerYoungsterJoey_NumberAccepted

Route30_Johto_TrainerYoungsterJoey_done:
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_GiveHPUp:
	message Route30_Johto_YoungsterJoeyText_GiveHPUpAfterBattle
	waitmessage
	waitbuttonpress
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, 0, Route30_Johto_TrainerYoungsterJoey_PackFull
	clearflag FLAG_JOHTO_JOEY_HP_UP
	setflag FLAG_JOHTO_GOT_HP_UP_FROM_JOEY
	goto Route30_Johto_TrainerYoungsterJoey_NumberAccepted

Route30_Johto_TrainerYoungsterJoey_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route30_Johto_TrainerYoungsterJoey_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route30_Johto_TrainerYoungsterJoey_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route30_Johto_TrainerYoungsterJoey_PackFull:
	setflag FLAG_JOHTO_JOEY_HP_UP
	goto Johto_Std_PackFullMScript

Route30_Johto_TrainerYoungsterMikey::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_MIKEY, Route30_Johto_YoungsterMikeySeenText, Route30_Johto_YoungsterMikeyBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_MIKEY
	lock
	faceplayer
	goto Route30_Johto_TrainerYoungsterMikey_Script

Route30_Johto_TrainerYoungsterMikey_Script:
	message Route30_Johto_YoungsterMikeyAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_TrainerBugCatcherDon::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_DON, Route30_Johto_BugCatcherDonSeenText, Route30_Johto_BugCatcherDonBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_DON
	lock
	faceplayer
	goto Route30_Johto_TrainerBugCatcherDon_Script

Route30_Johto_TrainerBugCatcherDon_Script:
	message Route30_Johto_BugCatcherDonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30YoungsterScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, Route30_Johto_Route30YoungsterScript_CompletedEggQuest
	message Route30_Johto_Route30YoungsterText_DirectionsToMrPokemonsHouse
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30YoungsterScript_CompletedEggQuest:
	message Route30_Johto_Route30YoungsterText_EveryoneIsBattling
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30CooltrainerFScript:
	faceplayer
	message Route30_Johto_Route30CooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30Sign:
	message Route30_Johto_Route30SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_MrPokemonsHouseDirectionsSign:
	message Route30_Johto_MrPokemonsHouseDirectionsSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_MrPokemonsHouseSign:
	message Route30_Johto_MrPokemonsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30TrainerTips:
	message Route30_Johto_Route30TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route30_Johto_Route30Antidote:
	finditem ITEM_ANTIDOTE
	releaseall
	end

Route30_Johto_Route30FruitTree1:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_30_1, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ORAN_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_30_1
	releaseall
	end

Route30_Johto_Route30FruitTree2:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_30_2, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PECHA_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_30_2
	releaseall
	end

Route30_Johto_TrainerYoungsterJoey_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route30_Johto_TrainerYoungsterJoey_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route30_Johto_TrainerYoungsterJoey_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route30_Johto_TrainerYoungsterJoey_RematchStd_Sub:
	goto Johto_Std_RematchMScript_Sub

Route30_Johto_TrainerYoungsterJoey_RematchGift_Sub:
	goto Johto_Std_RematchGiftMScript_Sub

Route30_Johto_Route30_JoeysRattataAttacksMovement:
	lock_facing_direction
	walk_fast_up
	walk_fast_down
	step_end

Route30_Johto_Route30_MikeysRattataAttacksMovement:
	lock_facing_direction
	walk_fast_down
	walk_fast_up
	step_end

Route30_Johto_Text_UseTackle:
	.string "Go, RATTATA!"
	.string "\pTACKLE!$"

Route30_Johto_Text_ThisIsABigBattle:
	.string "What? This is a\n"
	.string "big battle!\l"
	.string "Leave me alone!$"

Route30_Johto_YoungsterJoey1SeenText:
	.string "I just lost, so\n"
	.string "I'm trying to find\l"
	.string "more POKéMON."
	.string "\pWait! You look\n"
	.string "weak! Come on,\l"
	.string "let's battle!$"

Route30_Johto_YoungsterJoey1BeatenText:
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Johto_YoungsterJoey1AfterText:
	.string "Do I have to have\n"
	.string "more POKéMON in"
	.string "\porder to battle\n"
	.string "better?"
	.string "\pNo! I'm sticking\n"
	.string "with this one no\l"
	.string "matter what!$"

Route30_Johto_YoungsterMikeySeenText:
	.string "You're a POKéMON\n"
	.string "trainer, right?"
	.string "\pThen you have to\n"
	.string "battle!$"

Route30_Johto_YoungsterMikeyBeatenText:
	.string "That's strange.\n"
	.string "I won before.$"

Route30_Johto_YoungsterMikeyAfterText:
	.string "Becoming a good\n"
	.string "trainer is really\l"
	.string "tough."
	.string "\pI'm going to bat-\n"
	.string "tle other people\l"
	.string "to get better.$"

Route30_Johto_BugCatcherDonSeenText:
	.string "Instead of a bug\n"
	.string "POKéMON, I found\l"
	.string "a trainer!$"

Route30_Johto_BugCatcherDonBeatenText:
	.string "Argh! You're too\n"
	.string "strong!$"

Route30_Johto_BugCatcherDonAfterText:
	.string "I ran out of POKé\n"
	.string "BALLS while I was\l"
	.string "catching POKéMON."
	.string "\pI should've bought\n"
	.string "some more…$"

Route30_Johto_Route30YoungsterText_DirectionsToMrPokemonsHouse:
	.string "MR.POKéMON's\n"
	.string "house? It's a bit\l"
	.string "farther ahead.$"

Route30_Johto_Route30YoungsterText_EveryoneIsBattling:
	.string "Everyone's having\n"
	.string "fun battling!\l"
	.string "You should too!$"

Route30_Johto_Route30CooltrainerFText:
	.string "I'm not a trainer."
	.string "\pBut if you look\n"
	.string "one in the eyes,\l"
	.string "prepare to battle.$"

Route30_Johto_Route30SignText:
	.string "ROUTE 30"
	.string "\pVIOLET CITY -\n"
	.string "CHERRYGROVE CITY$"

Route30_Johto_MrPokemonsHouseDirectionsSignText:
	.string "MR.POKéMON'S HOUSE\n"
	.string "STRAIGHT AHEAD!$"

Route30_Johto_MrPokemonsHouseSignText:
	.string "MR.POKéMON'S HOUSE$"

Route30_Johto_Route30TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pNo stealing other\n"
	.string "people's POKéMON!"
	.string "\pPOKé BALLS are to\n"
	.string "be thrown only at\l"
	.string "wild POKéMON!$"

Route30_Johto_YoungsterJoeyText_GiveHPUpAfterBattle:
	.string "I lost again…\n"
	.string "Gee, you're tough!"
	.string "\pOh yeah, I almost\n"
	.string "forgot that I had\l"
	.string "to give you this."
	.string "\pUse it to get even\n"
	.string "tougher, OK?"
	.string "\pI'm going to get\n"
	.string "tougher too.$"

Route30_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_30_0, Route30_Johto_CutTree0_Keep
	setmetatile 8, 6, 514, 0
	setmetatile 9, 6, 514, 0
	setmetatile 8, 7, 591, 0
	setmetatile 9, 7, 514, 0
Route30_Johto_CutTree0_Keep:
	end

Route30_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route30_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_30_0
	setmetatile 8, 6, 514, 0
	setmetatile 9, 6, 514, 0
	setmetatile 8, 7, 591, 0
	setmetatile 9, 7, 514, 0
	special DrawWholeMapView
Route30_Johto_CutTree0_Done:
	releaseall
	end
