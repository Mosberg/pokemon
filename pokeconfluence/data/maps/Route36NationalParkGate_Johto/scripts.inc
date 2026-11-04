Route36NationalParkGate_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route36NationalParkGate_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route36NationalParkGate_Johto_OnFrame
	.byte 0

Route36NationalParkGate_Johto_OnTransition:
	call Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestRunningCallback_Cb
	call Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_Cb
	end

Route36NationalParkGate_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 2, Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript_Entry
	.2byte 0

Route36NationalParkGate_Johto_Route36OfficerScriptContest_Entry::
	lockall
	goto Route36NationalParkGate_Johto_Route36OfficerScriptContest

Route36NationalParkGate_Johto_BugCatchingContestant1BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant1BScript

Route36NationalParkGate_Johto_BugCatchingContestant2BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant2BScript

Route36NationalParkGate_Johto_BugCatchingContestant3BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant3BScript

Route36NationalParkGate_Johto_BugCatchingContestant4BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant4BScript

Route36NationalParkGate_Johto_BugCatchingContestant5BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant5BScript

Route36NationalParkGate_Johto_BugCatchingContestant6BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant6BScript

Route36NationalParkGate_Johto_BugCatchingContestant7BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant7BScript

Route36NationalParkGate_Johto_BugCatchingContestant8BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant8BScript

Route36NationalParkGate_Johto_BugCatchingContestant9BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant9BScript

Route36NationalParkGate_Johto_BugCatchingContestant10BScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestant10BScript

Route36NationalParkGate_Johto_Route36NationalParkGateOfficerScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_Route36NationalParkGateOfficerScript

Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript


Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	@ TODO unsupported: readvar VAR_CONTESTMINUTES
	goto Johto_EventScript_Unimplemented

Route36NationalParkGate_Johto_Route36OfficerScriptContest:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto__ContestNotOn
	goto_if_eq VAR_RESULT, 1, Route36NationalParkGate_Johto__ContestNotOn
	goto_if_eq VAR_RESULT, 3, Route36NationalParkGate_Johto__ContestNotOn
	goto_if_eq VAR_RESULT, 5, Route36NationalParkGate_Johto__ContestNotOn
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded
	call Route36NationalParkGate_Johto_Route36ParkGate_DayToText_Sub
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1AskToParticipateText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36OfficerScriptContest_DecidedNotToJoinContest
	getpartysize
	goto_if_gt VAR_RESULT, 1, Route36NationalParkGate_Johto_Route36OfficerScriptContest_LeaveMonsWithOfficer
	@ TODO unsupported: special ContestDropOffMons
	goto Johto_EventScript_Unimplemented

Route36NationalParkGate_Johto_Route36OfficerScriptContest_LeaveMonsWithOfficer:
	getpartysize
	goto_if_lt VAR_RESULT, 6, Route36NationalParkGate_Johto_Route36OfficerScriptContest_ContinueLeavingMons
	@ TODO unsupported: readvar VAR_BOXSPACE
	goto Johto_EventScript_Unimplemented

Route36NationalParkGate_Johto_Route36OfficerScriptContest_ContinueLeavingMons:
	@ TODO unsupported: special CheckFirstMonIsEgg
	goto Johto_EventScript_Unimplemented

Route36NationalParkGate_Johto_Route36OfficerScriptContest_DecidedNotToJoinContest:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1TakePartInFutureText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded:
	goto_if_set FLAG_JOHTO_CONTEST_OFFICER_HAS_SUN_STONE, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Sunstone
	goto_if_set FLAG_JOHTO_CONTEST_OFFICER_HAS_EVERSTONE, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Everstone
	goto_if_set FLAG_JOHTO_CONTEST_OFFICER_HAS_GOLD_BERRY, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_GoldBerry
	goto_if_set FLAG_JOHTO_CONTEST_OFFICER_HAS_BERRY, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Berry
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ContestIsOverText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Sunstone:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_JOHTO_CONTEST_OFFICER_HAS_SUN_STONE
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Everstone:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_JOHTO_CONTEST_OFFICER_HAS_EVERSTONE
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_GoldBerry:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SITRUS_BERRY
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_JOHTO_CONTEST_OFFICER_HAS_GOLD_BERRY
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_Berry:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_JOHTO_CONTEST_OFFICER_HAS_BERRY
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded_BagFull:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WellHoldPrizeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto__ContestNotOn:
	faceplayer
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36NationalParkGateOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST, Route36NationalParkGate_Johto_Route36Officer_ContestHasConcluded
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant1BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant1BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant1BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant1BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant1BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant2BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant2BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant2BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant2BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant2BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant3BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant3BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant3BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant3BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant3BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant4BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant4BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant4BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant4BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant4BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant5BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant5BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant5BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant5BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant5BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant6BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant6BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant6BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant6BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant6BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant7BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant7BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant7BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant7BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant7BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant8BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant8BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant8BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant8BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant8BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant9BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant9BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant9BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant9BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant9BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant10BScript:
	faceplayer
	goto_if_unset FLAG_TEMP_11, Route36NationalParkGate_Johto_BugCatchingContestant10BScript_StillCompeting
	message Route36NationalParkGate_Johto_BugCatchingContestant10BText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_BugCatchingContestant10BScript_StillCompeting:
	message Route36NationalParkGate_Johto_BugCatchingContestant10BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36ParkGate_DayToText_Sub:
	goto Johto_Std_DayToTextScript_Sub

Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestRunningCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestRunningCallback_BugContestIsRunning_Cb
	setvar VAR_JOHTO_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 0
	return

Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestRunningCallback_BugContestIsRunning_Cb:
	setvar VAR_JOHTO_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 2
	return

Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_Cb:
	goto_if_set FLAG_JOHTO_WARPED_FROM_ROUTE_35_NATIONAL_PARK_GATE, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_Return_Cb
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 2, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_eq VAR_RESULT, 4, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_eq VAR_RESULT, 6, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_set FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER, Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	setflag FLAG_JOHTO_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	clearflag FLAG_JOHTO_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return

Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb:
	clearflag FLAG_JOHTO_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	setflag FLAG_JOHTO_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY

Route36NationalParkGate_Johto_Route36NationalParkGateCheckIfContestAvailableCallback_Return_Cb:
	return

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1AskToParticipateText:
	.string "Today's {STR_VAR_1}.\n"
	.string "That means the"
	.string "\pBug-Catching Con-\n"
	.string "test is on today."
	.string "\pThe rules are sim-\n"
	.string "ple."
	.string "\pUsing one of your\n"
	.string "POKéMON, catch a"
	.string "\pbug POKéMON to be\n"
	.string "judged."
	.string "\pWould you like to\n"
	.string "give it a try?$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1TakePartInFutureText:
	.string "OK. We hope you'll\n"
	.string "take part in the\l"
	.string "future.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ContestIsOverText:
	.string "Today's Contest is\n"
	.string "over. We hope you"
	.string "\pwill participate\n"
	.string "in the future.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText:
	.string "Some POKéMON can\n"
	.string "only be seen in\l"
	.string "the PARK.$"

Route36NationalParkGate_Johto_BugCatchingContestant1BText:
	.string "DON: Wow, you beat\n"
	.string "me. You're pretty\l"
	.string "good.$"

Route36NationalParkGate_Johto_BugCatchingContestant1BStillCompetingText:
	.string "DON: Luck plays a\n"
	.string "big part in this."
	.string "\pYou never know\n"
	.string "what POKéMON will\l"
	.string "appear.$"

Route36NationalParkGate_Johto_BugCatchingContestant2BText:
	.string "ED: I envy you.\n"
	.string "I just couldn't\l"
	.string "do it this time.$"

Route36NationalParkGate_Johto_BugCatchingContestant2BStillCompetingText:
	.string "ED: Maybe you win\n"
	.string "with big POKéMON?$"

Route36NationalParkGate_Johto_BugCatchingContestant3BText:
	.string "NICK: Well done!\n"
	.string "I'm going to raise\l"
	.string "my POKéMON better.$"

Route36NationalParkGate_Johto_BugCatchingContestant3BStillCompetingText:
	.string "NICK: Maybe you\n"
	.string "get a higher score"
	.string "\pfor a POKéMON of\n"
	.string "an unusual color.$"

Route36NationalParkGate_Johto_BugCatchingContestant4BText:
	.string "WILLIAM: You're\n"
	.string "the winner? What\l"
	.string "did you catch?$"

Route36NationalParkGate_Johto_BugCatchingContestant4BStillCompetingText:
	.string "WILLIAM: Well, I'm\n"
	.string "satisfied because"
	.string "\pI caught a POKéMON\n"
	.string "that I wanted.$"

Route36NationalParkGate_Johto_BugCatchingContestant5BText:
	.string "BENNY: Congrats!\n"
	.string "You have earned my\l"
	.string "respect!$"

Route36NationalParkGate_Johto_BugCatchingContestant5BStillCompetingText:
	.string "BENNY: I caught a\n"
	.string "SCYTHER before,\l"
	.string "but I didn't win.$"

Route36NationalParkGate_Johto_BugCatchingContestant6BText:
	.string "BARRY: That POKé-\n"
	.string "MON you caught…\l"
	.string "it's awesome!$"

Route36NationalParkGate_Johto_BugCatchingContestant6BStillCompetingText:
	.string "BARRY: It's easier\n"
	.string "to win if you get"
	.string "\pa high-level bug\n"
	.string "POKéMON."
	.string "\pBut I think they\n"
	.string "also consider some\l"
	.string "other points.$"

Route36NationalParkGate_Johto_BugCatchingContestant7BText:
	.string "CINDY: You won?\n"
	.string "That's great!"
	.string "\pDo you feel like\n"
	.string "looking for bug\l"
	.string "POKéMON with me?$"

Route36NationalParkGate_Johto_BugCatchingContestant7BStillCompetingText:
	.string "CINDY: I really\n"
	.string "love bug POKéMON!$"

Route36NationalParkGate_Johto_BugCatchingContestant8BText:
	.string "JOSH: I… I can't\n"
	.string "believe I lost at\l"
	.string "bug-catching…$"

Route36NationalParkGate_Johto_BugCatchingContestant8BStillCompetingText:
	.string "JOSH: I heard that\n"
	.string "somebody won with\l"
	.string "a CATERPIE!$"

Route36NationalParkGate_Johto_BugCatchingContestant9BText:
	.string "SAMUEL: Next time,\n"
	.string "I'm going to win.$"

Route36NationalParkGate_Johto_BugCatchingContestant9BStillCompetingText:
	.string "SAMUEL: Darn.\n"
	.string "I thought I would\l"
	.string "score higher…$"

Route36NationalParkGate_Johto_BugCatchingContestant10BText:
	.string "KIPP: Could you\n"
	.string "give me some tips?"
	.string "\pI want to study\n"
	.string "your style.$"

Route36NationalParkGate_Johto_BugCatchingContestant10BStillCompetingText:
	.string "KIPP: I study a\n"
	.string "lot, but that's"
	.string "\pnot good enough to\n"
	.string "win.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WellHoldPrizeText:
	.string "Uh-oh… Your PACK\n"
	.string "is full."
	.string "\pWe'll hold on to\n"
	.string "your prize, but\l"
	.string "only for today."
	.string "\pPlease make room,\n"
	.string "then come see me.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1HeresThePrizeText:
	.string "{PLAYER}?"
	.string "\pHere's the prize\n"
	.string "we were holding\l"
	.string "for you.$"
