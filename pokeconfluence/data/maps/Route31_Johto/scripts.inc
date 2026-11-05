Route31_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route31_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, Route31_Johto_OnLoad
	.byte 0

Route31_Johto_OnTransition:
	call Route31_Johto_Route31CheckMomCallCallback_Cb
	end

Route31_Johto_Route31MailRecipientScript_Entry::
	lockall
	goto Route31_Johto_Route31MailRecipientScript

Route31_Johto_Route31YoungsterScript_Entry::
	lockall
	goto Route31_Johto_Route31YoungsterScript

Route31_Johto_Route31CooltrainerMScript_Entry::
	lockall
	goto Route31_Johto_Route31CooltrainerMScript

Route31_Johto_Route31FruitTree_Entry::
	lockall
	goto Route31_Johto_Route31FruitTree

Route31_Johto_Route31Potion_Entry::
	lockall
	goto Route31_Johto_Route31Potion

Route31_Johto_Route31PokeBall_Entry::
	lockall
	goto Route31_Johto_Route31PokeBall

Route31_Johto_Route31Sign_Entry::
	lockall
	goto Route31_Johto_Route31Sign

Route31_Johto_DarkCaveSign_Entry::
	lockall
	goto Route31_Johto_DarkCaveSign


Route31_Johto_TrainerBugCatcherWade1::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_WADE1, Route31_Johto_BugCatcherWade1SeenText, Route31_Johto_BugCatcherWade1BeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_WADE
	lock
	faceplayer
	goto Route31_Johto_TrainerBugCatcherWade1_Script

Route31_Johto_TrainerBugCatcherWade1_Script:
	setvar VAR_0x8007, 711
	goto_if_set FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH, Route31_Johto_TrainerBugCatcherWade1_WadeRematch
	goto_if_set FLAG_JOHTO_ENGINE_WADE_HAS_ITEM, Route31_Johto_TrainerBugCatcherWade1_WadeItem
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_AcceptedNumberSTD
	goto_if_set FLAG_JOHTO_WADE_ASKED_FOR_PHONE_NUMBER, Route31_Johto_TrainerBugCatcherWade1_AskAgain
	message Route31_Johto_BugCatcherWade1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_WADE_ASKED_FOR_PHONE_NUMBER
	call Route31_Johto_TrainerBugCatcherWade1_AskPhoneNumberSTD_Sub
	goto Route31_Johto_TrainerBugCatcherWade1_Continue

Route31_Johto_TrainerBugCatcherWade1_AskAgain:
	call Route31_Johto_TrainerBugCatcherWade1_AskAgainSTD_Sub

Route31_Johto_TrainerBugCatcherWade1_Continue:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BUG_CATCHER_WADE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_WADE_HAS_ITEM
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route31_Johto_TrainerBugCatcherWade1_PhoneFullSTD
	goto_if_eq VAR_RESULT, 2, Route31_Johto_TrainerBugCatcherWade1_DeclinedNumberSTD
	buffertrainername STR_VAR_1, TRAINER_JOHTO_BUG_CATCHER_WADE1
	call Route31_Johto_TrainerBugCatcherWade1_RegisterNumberSTD_Sub
	goto Route31_Johto_TrainerBugCatcherWade1_AcceptedNumberSTD

Route31_Johto_TrainerBugCatcherWade1_WadeRematch:
	call Route31_Johto_TrainerBugCatcherWade1_RematchSTD_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WWADEFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route31_Johto_TrainerBugCatcherWade1_Fight4
	goto_if_eq VAR_RESULT, 3, Route31_Johto_TrainerBugCatcherWade1_Fight3
	goto_if_eq VAR_RESULT, 2, Route31_Johto_TrainerBugCatcherWade1_Fight2
	goto_if_eq VAR_RESULT, 1, Route31_Johto_TrainerBugCatcherWade1_Fight1
	goto_if_eq VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_LoadFight0

Route31_Johto_TrainerBugCatcherWade1_Fight4:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route31_Johto_TrainerBugCatcherWade1_LoadFight4

Route31_Johto_TrainerBugCatcherWade1_Fight3:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route31_Johto_TrainerBugCatcherWade1_LoadFight3

Route31_Johto_TrainerBugCatcherWade1_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_MAHOGANY, Route31_Johto_TrainerBugCatcherWade1_LoadFight2

Route31_Johto_TrainerBugCatcherWade1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_GOLDENROD, Route31_Johto_TrainerBugCatcherWade1_LoadFight1

Route31_Johto_TrainerBugCatcherWade1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_WADE1, Route31_Johto_BugCatcherWade1BeatenText
	setvar VAR_JOHTO_MEM_WWADEFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_WADE2, Route31_Johto_BugCatcherWade1BeatenText
	setvar VAR_JOHTO_MEM_WWADEFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_WADE3, Route31_Johto_BugCatcherWade1BeatenText
	setvar VAR_JOHTO_MEM_WWADEFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_WADE4, Route31_Johto_BugCatcherWade1BeatenText
	setvar VAR_JOHTO_MEM_WWADEFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_WADE5, Route31_Johto_BugCatcherWade1BeatenText
	clearflag FLAG_JOHTO_ENGINE_WADE_READY_FOR_REMATCH
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_WadeItem:
	call Route31_Johto_TrainerBugCatcherWade1_ItemSTD_Sub
	goto_if_set FLAG_JOHTO_WADE_HAS_BERRY, Route31_Johto_TrainerBugCatcherWade1_Berry
	goto_if_set FLAG_JOHTO_WADE_HAS_PSNCUREBERRY, Route31_Johto_TrainerBugCatcherWade1_Psncureberry
	goto_if_set FLAG_JOHTO_WADE_HAS_PRZCUREBERRY, Route31_Johto_TrainerBugCatcherWade1_Przcureberry
	goto_if_set FLAG_JOHTO_WADE_HAS_BITTER_BERRY, Route31_Johto_TrainerBugCatcherWade1_BitterBerry

Route31_Johto_TrainerBugCatcherWade1_Berry:
	giveitem ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_PackFull
	goto Route31_Johto_TrainerBugCatcherWade1_Done

Route31_Johto_TrainerBugCatcherWade1_Psncureberry:
	giveitem ITEM_PECHA_BERRY
	goto_if_eq VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_PackFull
	goto Route31_Johto_TrainerBugCatcherWade1_Done

Route31_Johto_TrainerBugCatcherWade1_Przcureberry:
	giveitem ITEM_CHERI_BERRY
	goto_if_eq VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_PackFull
	goto Route31_Johto_TrainerBugCatcherWade1_Done

Route31_Johto_TrainerBugCatcherWade1_BitterBerry:
	giveitem ITEM_PERSIM_BERRY
	goto_if_eq VAR_RESULT, 0, Route31_Johto_TrainerBugCatcherWade1_PackFull

Route31_Johto_TrainerBugCatcherWade1_Done:
	clearflag FLAG_JOHTO_ENGINE_WADE_HAS_ITEM
	goto Route31_Johto_TrainerBugCatcherWade1_AcceptedNumberSTD

Route31_Johto_TrainerBugCatcherWade1_PackFull:
	goto Route31_Johto_TrainerBugCatcherWade1_PackFullSTD

Route31_Johto_TrainerBugCatcherWade1_AcceptedNumberSTD:
	goto Johto_Std_NumberAcceptedMScript

Route31_Johto_TrainerBugCatcherWade1_DeclinedNumberSTD:
	goto Johto_Std_NumberDeclinedMScript

Route31_Johto_TrainerBugCatcherWade1_PhoneFullSTD:
	goto Johto_Std_PhoneFullMScript

Route31_Johto_TrainerBugCatcherWade1_PackFullSTD:
	goto Johto_Std_PackFullMScript

Route31_Johto_Route31MailRecipientScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM50_NIGHTMARE, Route31_Johto_Route31MailRecipientScript_DescribeNightmare
	goto_if_set FLAG_JOHTO_GOT_KENYA, Route31_Johto_Route31MailRecipientScript_TryGiveKenya
	message Route31_Johto_Text_Route31SleepyMan
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31MailRecipientScript_TryGiveKenya:
	message Route31_Johto_Text_Route31SleepyManGotMail
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 0, Route31_Johto_Route31MailRecipientScript_WrongMail
	goto_if_eq VAR_RESULT, 2, Route31_Johto_Route31MailRecipientScript_Refused
	goto_if_eq VAR_RESULT, 3, Route31_Johto_Route31MailRecipientScript_NoMail
	goto_if_eq VAR_RESULT, 4, Route31_Johto_Route31MailRecipientScript_LastMon
	message Route31_Johto_Text_Route31HandOverMailMon
	waitmessage
	waitbuttonpress
	message Route31_Johto_Text_Route31ReadingMail
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_GAVE_KENYA
	giveitem ITEM_TM_TAUNT
	goto_if_eq VAR_RESULT, 0, Route31_Johto_Route31MailRecipientScript_NoRoomForItems
	setflag FLAG_JOHTO_GOT_TM50_NIGHTMARE

Route31_Johto_Route31MailRecipientScript_DescribeNightmare:
	message Route31_Johto_Text_Route31DescribeNightmare
	waitmessage
	waitbuttonpress

Route31_Johto_Route31MailRecipientScript_NoRoomForItems:
	closemessage
	releaseall
	end

Route31_Johto_Route31MailRecipientScript_WrongMail:
	message Route31_Johto_Text_Route31WrongMail
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31MailRecipientScript_NoMail:
	message Route31_Johto_Text_Route31MissingMail
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31MailRecipientScript_Refused:
	message Route31_Johto_Text_Route31DeclinedToHandOverMail
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31MailRecipientScript_LastMon:
	message Route31_Johto_Text_Route31CantTakeLastMon
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31YoungsterScript:
	faceplayer
	message Route31_Johto_Route31YoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31Sign:
	message Route31_Johto_Route31SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_DarkCaveSign:
	message Route31_Johto_DarkCaveSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31CooltrainerMScript:
	faceplayer
	message Route31_Johto_Route31CooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31_Johto_Route31FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_31, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PERSIM_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_31
	releaseall
	end

Route31_Johto_Route31Potion:
	finditem ITEM_POTION
	releaseall
	end

Route31_Johto_Route31PokeBall:
	finditem ITEM_POKE_BALL
	releaseall
	end

Route31_Johto_TrainerBugCatcherWade1_AskPhoneNumberSTD_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route31_Johto_TrainerBugCatcherWade1_AskAgainSTD_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route31_Johto_TrainerBugCatcherWade1_RegisterNumberSTD_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route31_Johto_TrainerBugCatcherWade1_RematchSTD_Sub:
	goto Johto_Std_RematchMScript_Sub

Route31_Johto_TrainerBugCatcherWade1_ItemSTD_Sub:
	goto Johto_Std_GiftMScript_Sub

Route31_Johto_Route31CheckMomCallCallback_Cb:
	goto_if_unset FLAG_JOHTO_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, Route31_Johto_Route31CheckMomCallCallback_DoMomCall_Cb
	return

Route31_Johto_Route31CheckMomCallCallback_DoMomCall_Cb:
	return

Route31_Johto_Route31CooltrainerMText:
	.string "DARK CAVE…"
	.string "\pIf POKéMON could\n"
	.string "light it up, I'd\l"
	.string "explore it.$"

Route31_Johto_BugCatcherWade1SeenText:
	.string "I caught a bunch\n"
	.string "of POKéMON. Let me\l"
	.string "battle with you!$"

Route31_Johto_BugCatcherWade1BeatenText:
	.string "Awwwww…$"

Route31_Johto_BugCatcherWade1AfterText:
	.string "You can catch\n"
	.string "POKéMON even if"
	.string "\pyou have six with\n"
	.string "you."
	.string "\pIf you catch one,\n"
	.string "it'll go to your\l"
	.string "BOX automatically.$"

Route31_Johto_Text_Route31SleepyMan:
	.string "… Hnuurg… Huh?"
	.string "\pI walked too far\n"
	.string "today looking for\l"
	.string "POKéMON."
	.string "\pMy feet hurt and\n"
	.string "I'm sleepy…"
	.string "\pIf I were a wild\n"
	.string "POKéMON, I'd be\l"
	.string "easy to catch…"
	.string "\p…Zzzz…$"

Route31_Johto_Text_Route31SleepyManGotMail:
	.string "…Zzzz… Huh?"
	.string "\pWhat's that? You\n"
	.string "have MAIL for me?$"

Route31_Johto_Text_Route31HandOverMailMon:
	.string "{PLAYER} handed\n"
	.string "over the POKéMON\l"
	.string "holding the MAIL.$"

Route31_Johto_Text_Route31ReadingMail:
	.string "Let's see…"
	.string "\p…DARK CAVE leads\n"
	.string "to another road…"
	.string "\pThat's good to\n"
	.string "know."
	.string "\pThanks for bring-\n"
	.string "ing this to me."
	.string "\pMy friend's a good\n"
	.string "guy, and you're\l"
	.string "swell too!"
	.string "\pI'd like to do\n"
	.string "something good in\l"
	.string "return too!"
	.string "\pI know! I want you\n"
	.string "to have this!$"

Route31_Johto_Text_Route31DescribeNightmare:
	.string "TM50 is NIGHTMARE."
	.string "\pIt's a wicked move\n"
	.string "that steadily cuts"
	.string "\pthe HP of a sleep-\n"
	.string "ing enemy."
	.string "\pOoooh…\n"
	.string "That's scary…"
	.string "\pI don't want to\n"
	.string "have bad dreams.$"

Route31_Johto_Text_Route31WrongMail:
	.string "This MAIL isn't\n"
	.string "for me.$"

Route31_Johto_Text_Route31MissingMail:
	.string "Why is this POKé-\n"
	.string "MON so special?"
	.string "\pIt doesn't have\n"
	.string "any MAIL.$"

Route31_Johto_Text_Route31DeclinedToHandOverMail:
	.string "What? You don't\n"
	.string "want anything?$"

Route31_Johto_Text_Route31CantTakeLastMon:
	.string "If I take that\n"
	.string "POKéMON from you,"
	.string "\pwhat are you going\n"
	.string "to use in battle?$"

Route31_Johto_Route31YoungsterText:
	.string "I found a good\n"
	.string "POKéMON in DARK\l"
	.string "CAVE."
	.string "\pI'm going to raise\n"
	.string "it to take on\l"
	.string "FALKNER."
	.string "\pHe's the leader of\n"
	.string "VIOLET CITY's GYM.$"

Route31_Johto_Route31SignText:
	.string "ROUTE 31"
	.string "\pVIOLET CITY -\n"
	.string "CHERRYGROVE CITY$"

Route31_Johto_DarkCaveSignText:
	.string "DARK CAVE$"

Route31_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_31_0, Route31_Johto_CutTree0_Keep
	setmetatile 12, 4, 514, 0
	setmetatile 13, 4, 591, 0
	setmetatile 12, 5, 514, 0
	setmetatile 13, 5, 514, 0
Route31_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_31_1, Route31_Johto_CutTree1_Keep
	setmetatile 24, 10, 591, 0
	setmetatile 25, 10, 514, 0
	setmetatile 24, 11, 514, 0
	setmetatile 25, 11, 514, 0
Route31_Johto_CutTree1_Keep:
	end

Route31_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route31_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_31_0
	setmetatile 12, 4, 514, 0
	setmetatile 13, 4, 591, 0
	setmetatile 12, 5, 514, 0
	setmetatile 13, 5, 514, 0
	special DrawWholeMapView
Route31_Johto_CutTree0_Done:
	releaseall
	end

Route31_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route31_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_31_1
	setmetatile 24, 10, 591, 0
	setmetatile 25, 10, 514, 0
	setmetatile 24, 11, 514, 0
	setmetatile 25, 11, 514, 0
	special DrawWholeMapView
Route31_Johto_CutTree1_Done:
	releaseall
	end
