Route35_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route35_Johto_OnLoad
	.byte 0

Route35_Johto_TrainerOfficerDirk_Entry::
	lockall
	goto Route35_Johto_TrainerOfficerDirk

Route35_Johto_Route35FruitTree_Entry::
	lockall
	goto Route35_Johto_Route35FruitTree

Route35_Johto_Route35TMRollout_Entry::
	lockall
	goto Route35_Johto_Route35TMRollout

Route35_Johto_Route35Sign_Entry::
	lockall
	goto Route35_Johto_Route35Sign


Route35_Johto_TrainerBirdKeeperBryan::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_BRYAN, Route35_Johto_BirdKeeperBryanSeenText, Route35_Johto_BirdKeeperBryanBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_BRYAN
	lock
	faceplayer
	goto Route35_Johto_TrainerBirdKeeperBryan_Script

Route35_Johto_TrainerBirdKeeperBryan_Script:
	message Route35_Johto_BirdKeeperBryanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerJugglerIrwin::
	trainerbattle_single TRAINER_JOHTO_JUGGLER_IRWIN1, Route35_Johto_JugglerIrwin1SeenText, Route35_Johto_JugglerIrwin1BeatenText
	setflag FLAG_JOHTO_BEAT_JUGGLER_IRWIN
	lock
	faceplayer
	goto Route35_Johto_TrainerJugglerIrwin_Script

Route35_Johto_TrainerJugglerIrwin_Script:
	setvar VAR_0x8007, 1037
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_JUGGLER_IRWIN_REGISTERED
	setvar VAR_0x8005, 0
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route35_Johto_Route35NumberAcceptedM
	goto_if_set FLAG_JOHTO_IRWIN_ASKED_FOR_PHONE_NUMBER, Route35_Johto_TrainerJugglerIrwin_AskedAlready
	message Route35_Johto_JugglerIrwinAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_IRWIN_ASKED_FOR_PHONE_NUMBER
	call Route35_Johto_Route35AskNumber1M_Sub
	goto Route35_Johto_TrainerJugglerIrwin_AskForNumber

Route35_Johto_TrainerJugglerIrwin_AskedAlready:
	call Route35_Johto_Route35AskNumber2M_Sub

Route35_Johto_TrainerJugglerIrwin_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_JUGGLER_IRWIN_REGISTERED
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route35_Johto_Route35PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route35_Johto_Route35NumberDeclinedM
	buffertrainername STR_VAR_1, TRAINER_JOHTO_JUGGLER_IRWIN1
	call Route35_Johto_Route35RegisteredNumberM_Sub
	goto Route35_Johto_Route35NumberAcceptedM

Route35_Johto_Route35NumberAcceptedM:
	goto Johto_Std_NumberAcceptedMScript

Route35_Johto_Route35NumberDeclinedM:
	goto Johto_Std_NumberDeclinedMScript

Route35_Johto_Route35PhoneFullM:
	goto Johto_Std_PhoneFullMScript

Route35_Johto_TrainerCamperIvan::
	trainerbattle_single TRAINER_JOHTO_CAMPER_IVAN, Route35_Johto_CamperIvanSeenText, Route35_Johto_CamperIvanBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_IVAN
	lock
	faceplayer
	goto Route35_Johto_TrainerCamperIvan_Script

Route35_Johto_TrainerCamperIvan_Script:
	message Route35_Johto_CamperIvanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerCamperElliot::
	trainerbattle_single TRAINER_JOHTO_CAMPER_ELLIOT, Route35_Johto_CamperElliotSeenText, Route35_Johto_CamperElliotBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_ELLIOT
	lock
	faceplayer
	goto Route35_Johto_TrainerCamperElliot_Script

Route35_Johto_TrainerCamperElliot_Script:
	message Route35_Johto_CamperElliotAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerPicnickerBrooke::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_BROOKE, Route35_Johto_PicnickerBrookeSeenText, Route35_Johto_PicnickerBrookeBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_BROOKE
	lock
	faceplayer
	goto Route35_Johto_TrainerPicnickerBrooke_Script

Route35_Johto_TrainerPicnickerBrooke_Script:
	message Route35_Johto_PicnickerBrookeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerPicnickerKim::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_KIM, Route35_Johto_PicnickerKimSeenText, Route35_Johto_PicnickerKimBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_KIM
	lock
	faceplayer
	goto Route35_Johto_TrainerPicnickerKim_Script

Route35_Johto_TrainerPicnickerKim_Script:
	message Route35_Johto_PicnickerKimAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_ARNIE1, Route35_Johto_BugCatcherArnieSeenText, Route35_Johto_BugCatcherArnieBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_ARNIE
	lock
	faceplayer
	goto Route35_Johto_TrainerBugCatcherArnie_Script

Route35_Johto_TrainerBugCatcherArnie_Script:
	setvar VAR_0x8007, 894
	goto_if_set FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH, Route35_Johto_TrainerBugCatcherArnie_WantsBattle
	goto_if_set FLAG_JOHTO_ENGINE_YANMA_SWARM, Route35_Johto_TrainerBugCatcherArnie_YanmaSwarming
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BUG_CATCHER_ARNIE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route35_Johto_Route35NumberAcceptedM
	goto_if_set FLAG_JOHTO_ARNIE_ASKED_FOR_PHONE_NUMBER, Route35_Johto_TrainerBugCatcherArnie_AskedAlready
	message Route35_Johto_BugCatcherArnieAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_ARNIE_ASKED_FOR_PHONE_NUMBER
	call Route35_Johto_Route35AskNumber1M_Sub
	goto Route35_Johto_TrainerBugCatcherArnie_AskForNumber

Route35_Johto_TrainerBugCatcherArnie_AskedAlready:
	call Route35_Johto_Route35AskNumber2M_Sub

Route35_Johto_TrainerBugCatcherArnie_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BUG_CATCHER_ARNIE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route35_Johto_Route35PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route35_Johto_Route35NumberDeclinedM
	buffertrainername STR_VAR_1, TRAINER_JOHTO_BUG_CATCHER_ARNIE1
	call Route35_Johto_Route35RegisteredNumberM_Sub
	goto Route35_Johto_Route35NumberAcceptedM

Route35_Johto_TrainerBugCatcherArnie_WantsBattle:
	call Route35_Johto_Route35RematchM_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WARNIEFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route35_Johto_TrainerBugCatcherArnie_Fight4
	goto_if_eq VAR_RESULT, 3, Route35_Johto_TrainerBugCatcherArnie_Fight3
	goto_if_eq VAR_RESULT, 2, Route35_Johto_TrainerBugCatcherArnie_Fight2
	goto_if_eq VAR_RESULT, 1, Route35_Johto_TrainerBugCatcherArnie_Fight1
	goto_if_eq VAR_RESULT, 0, Route35_Johto_TrainerBugCatcherArnie_LoadFight0

Route35_Johto_TrainerBugCatcherArnie_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route35_Johto_TrainerBugCatcherArnie_LoadFight4

Route35_Johto_TrainerBugCatcherArnie_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route35_Johto_TrainerBugCatcherArnie_LoadFight3

Route35_Johto_TrainerBugCatcherArnie_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_BLACKTHORN, Route35_Johto_TrainerBugCatcherArnie_LoadFight2

Route35_Johto_TrainerBugCatcherArnie_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_LAKE_OF_RAGE, Route35_Johto_TrainerBugCatcherArnie_LoadFight1

Route35_Johto_TrainerBugCatcherArnie_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_ARNIE1, Route35_Johto_BugCatcherArnieBeatenText
	setvar VAR_JOHTO_MEM_WARNIEFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_ARNIE2, Route35_Johto_BugCatcherArnieBeatenText
	setvar VAR_JOHTO_MEM_WARNIEFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_ARNIE3, Route35_Johto_BugCatcherArnieBeatenText
	setvar VAR_JOHTO_MEM_WARNIEFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_ARNIE4, Route35_Johto_BugCatcherArnieBeatenText
	setvar VAR_JOHTO_MEM_WARNIEFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_BUG_CATCHER_ARNIE5, Route35_Johto_BugCatcherArnieBeatenText
	clearflag FLAG_JOHTO_ENGINE_ARNIE_READY_FOR_REMATCH
	releaseall
	end

Route35_Johto_TrainerBugCatcherArnie_YanmaSwarming:
	message Route35_Johto_BugCatcherArnieYanmaText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerFirebreatherWalt::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_WALT, Route35_Johto_FirebreatherWaltSeenText, Route35_Johto_FirebreatherWaltBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_WALT
	lock
	faceplayer
	goto Route35_Johto_TrainerFirebreatherWalt_Script

Route35_Johto_TrainerFirebreatherWalt_Script:
	message Route35_Johto_FirebreatherWaltAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerOfficerDirk:
	faceplayer
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_eq VAR_RESULT, 0, Route35_Johto_TrainerOfficerDirk_NotNight
	goto_if_set FLAG_JOHTO_BEAT_OFFICER_DIRK, Route35_Johto_TrainerOfficerDirk_AfterBattle
	playbgm MUS_DUMMY, FALSE
	message Route35_Johto_OfficerDirkSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_OFFICER_DIRK, Route35_Johto_OfficerDirkBeatenText
	setflag FLAG_JOHTO_BEAT_OFFICER_DIRK
	closemessage
	releaseall
	end

Route35_Johto_TrainerOfficerDirk_AfterBattle:
	message Route35_Johto_OfficerDirkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_TrainerOfficerDirk_NotNight:
	message Route35_Johto_OfficerDirkPrettyToughText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_Route35Sign:
	message Route35_Johto_Route35SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35_Johto_Route35TMRollout:
	finditem ITEM_TM_ROCK_TOMB
	releaseall
	end

Route35_Johto_Route35FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_35, Johto_Std_FruitTreeEmpty
	giveitem ITEM_LEPPA_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_35
	releaseall
	end

Route35_Johto_Route35AskNumber1M_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route35_Johto_Route35AskNumber2M_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route35_Johto_Route35RegisteredNumberM_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route35_Johto_Route35RematchM_Sub:
	goto Johto_Std_RematchMScript_Sub

Route35_Johto_CamperIvanSeenText:
	.string "I've been getting\n"
	.string "POKéMON data off"
	.string "\pmy radio. I think\n"
	.string "I'm good.$"

Route35_Johto_CamperIvanBeatenText:
	.string "I give!$"

Route35_Johto_CamperIvanAfterBattleText:
	.string "Music on the radio\n"
	.string "changes the moods\l"
	.string "of wild POKéMON.$"

Route35_Johto_CamperElliotSeenText:
	.string "I'm gonna show my\n"
	.string "girlfriend I'm hot\l"
	.string "stuff!$"

Route35_Johto_CamperElliotBeatenText:
	.string "I wish you would\n"
	.string "have lost for me…$"

Route35_Johto_CamperElliotAfterBattleText:
	.string "I was humiliated\n"
	.string "in front of my\l"
	.string "girlfriend…$"

Route35_Johto_PicnickerBrookeSeenText:
	.string "My boyfriend's\n"
	.string "weak, so I can't\l"
	.string "rely on him.$"

Route35_Johto_PicnickerBrookeBeatenText:
	.string "Oh, my! You're so\n"
	.string "strong!$"

Route35_Johto_PicnickerBrookeAfterBattleText:
	.string "I can count on my\n"
	.string "POKéMON more than\l"
	.string "my boyfriend.$"

Route35_Johto_PicnickerKimSeenText:
	.string "Are you going to\n"
	.string "the GYM? Me too!$"

Route35_Johto_PicnickerKimBeatenText:
	.string "Oh. I couldn't\n"
	.string "win…$"

Route35_Johto_PicnickerKimAfterBattleText:
	.string "The GYM BADGES are\n"
	.string "pretty. I collect\l"
	.string "them.$"

Route35_Johto_BirdKeeperBryanSeenText:
	.string "What kinds of\n"
	.string "BALLS do you use?$"

Route35_Johto_BirdKeeperBryanBeatenText:
	.string "Yikes! Not fast\n"
	.string "enough!$"

Route35_Johto_BirdKeeperBryanAfterBattleText:
	.string "Some POKéMON flee\n"
	.string "right away."
	.string "\pTry catching them\n"
	.string "with KURT's FAST\l"
	.string "BALL."
	.string "\pWhenever I find a\n"
	.string "WHT APRICORN, I\l"
	.string "take it to KURT."
	.string "\pHe turns it into a\n"
	.string "custom BALL.$"

Route35_Johto_JugglerIrwin1SeenText:
	.string "Behold my graceful\n"
	.string "BALL dexterity!$"

Route35_Johto_JugglerIrwin1BeatenText:
	.string "Whew! That was a\n"
	.string "jolt!$"

Route35_Johto_JugglerIrwinAfterBattleText:
	.string "I was going to\n"
	.string "dazzle you with my\l"
	.string "prize POKéMON."
	.string "\pBut your prowess\n"
	.string "electrified me!$"

Route35_Johto_BugCatcherArnieSeenText:
	.string "I'll go anywhere\n"
	.string "if bug POKéMON\l"
	.string "appear there.$"

Route35_Johto_BugCatcherArnieBeatenText:
	.string "Huh? I shouldn't\n"
	.string "have lost that…$"

Route35_Johto_BugCatcherArnieAfterBattleText:
	.string "My VENONAT won me\n"
	.string "the Bug-Catching"
	.string "\pContest at the\n"
	.string "NATIONAL PARK.$"

Route35_Johto_BugCatcherArnieYanmaText:
	.string "Wow… Look at all\n"
	.string "those YANMA!"
	.string "\pI'm so blown away,\n"
	.string "I can't move.$"

Route35_Johto_FirebreatherWaltSeenText:
	.string "I'm practicing my\n"
	.string "fire breathing.$"

Route35_Johto_FirebreatherWaltBeatenText:
	.string "Ow! I scorched the\n"
	.string "tip of my nose!$"

Route35_Johto_FirebreatherWaltAfterBattleText:
	.string "The POKéMON March\n"
	.string "on the radio lures\l"
	.string "wild POKéMON.$"

Route35_Johto_OfficerDirkSeenText:
	.string "Danger lurks in\n"
	.string "the night!$"

Route35_Johto_OfficerDirkBeatenText:
	.string "Whoops!$"

Route35_Johto_OfficerDirkAfterBattleText:
	.string "You know, night-\n"
	.string "time is fun in its\l"
	.string "own ways."
	.string "\pBut don't overdo\n"
	.string "it, OK?$"

Route35_Johto_OfficerDirkPrettyToughText:
	.string "Your POKéMON look\n"
	.string "pretty tough."
	.string "\pYou could go any-\n"
	.string "where safely.$"

Route35_Johto_Route35SignText:
	.string "ROUTE 35$"

Route35_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_35_0, Route35_Johto_CutTree0_Keep
	setmetatile 16, 6, 591, 0
	setmetatile 17, 6, 514, 0
	setmetatile 16, 7, 514, 0
	setmetatile 17, 7, 514, 0
Route35_Johto_CutTree0_Keep:
	end

Route35_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route35_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_35_0
	setmetatile 16, 6, 591, 0
	setmetatile 17, 6, 514, 0
	setmetatile 16, 7, 514, 0
	setmetatile 17, 7, 514, 0
	special DrawWholeMapView
Route35_Johto_CutTree0_Done:
	releaseall
	end
