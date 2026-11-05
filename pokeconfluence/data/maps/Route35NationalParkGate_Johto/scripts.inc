Route35NationalParkGate_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route35NationalParkGate_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route35NationalParkGate_Johto_OnFrame
	.byte 0

Route35NationalParkGate_Johto_OnTransition:
	call Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestRunningCallback_Cb
	call Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_Cb
	end

Route35NationalParkGate_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 2, Route35NationalParkGate_Johto_Route35NationalParkGateLeavingContestEarlyScript_Entry
	.2byte 0

Route35NationalParkGate_Johto_Route35OfficerScriptContest_Entry::
	lockall
	goto Route35NationalParkGate_Johto_Route35OfficerScriptContest

Route35NationalParkGate_Johto_Route35NationalParkGateYoungsterScript_Entry::
	lockall
	goto Route35NationalParkGate_Johto_Route35NationalParkGateYoungsterScript

Route35NationalParkGate_Johto_Route35NationalParkGateOfficerScript_Entry::
	lockall
	goto Route35NationalParkGate_Johto_Route35NationalParkGateOfficerScript

Route35NationalParkGate_Johto_BugCatchingContestExplanationSign_Entry::
	lockall
	goto Route35NationalParkGate_Johto_BugCatchingContestExplanationSign

Route35NationalParkGate_Johto_Route35NationalParkGateLeavingContestEarlyScript_Entry::
	lockall
	goto Route35NationalParkGate_Johto_Route35NationalParkGateLeavingContestEarlyScript


Route35NationalParkGate_Johto_Route35NationalParkGateLeavingContestEarlyScript:
	applymovement OBJ_EVENT_ID_PLAYER, Route35NationalParkGate_Johto_Route35NationalParkGatePlayerApproachOfficer1Movement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	setvar VAR_RESULT, 10
	addvar VAR_RESULT, 1
	buffernumberstring STR_VAR_3, VAR_RESULT
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WantToFinishText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_GoBackToContest
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WaitAtNorthGateText
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER
	setflag FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_GoBackToContest:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1OkGoFinishText
	waitmessage
	waitbuttonpress
	closemessage
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 10, 47
	waitstate
	end

Route35NationalParkGate_Johto_Route35OfficerScriptContest:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 1, Route35NationalParkGate_Johto_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 3, Route35NationalParkGate_Johto_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 5, Route35NationalParkGate_Johto_Route35NationalParkGate_NoContestToday
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST, Route35NationalParkGate_Johto_Route35NationalParkGate_ContestIsOver
	call Route35NationalParkGate_Johto_Route35NationalParkGate_GetDayOfWeek_Sub
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1AskToParticipateText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_DeclinedToParticipate
	getpartysize
	goto_if_gt VAR_RESULT, 1, Route35NationalParkGate_Johto_Route35NationalParkGate_LeaveTheRestBehind
	clearflag FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER

Route35NationalParkGate_Johto_Route35NationalParkGate_OkayToProceed:
	setflag FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER
	fadedefaultbgm
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1GiveParkBallsText
	waitmessage
	waitbuttonpress
	message Route35NationalParkGate_Johto_Route35NationalParkGatePlayerReceivedParkBallsText
	waitmessage
	playse SE_PIN
	waitse
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ExplainsRulesText
	waitmessage
	waitbuttonpress
	closemessage
	special JohtoGiveParkBalls
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 10, 47
	waitstate
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_LeaveTheRestBehind:
	getpartysize
	goto_if_lt VAR_RESULT, 6, Route35NationalParkGate_Johto_Route35NationalParkGate_LessThanFullParty
	setvar VAR_RESULT, 20
	goto_if_eq VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_NoRoomInBox

Route35NationalParkGate_Johto_Route35NationalParkGate_LessThanFullParty:
	special JohtoCheckFirstMonIsEgg
	goto_if_eq VAR_RESULT, TRUE, Route35NationalParkGate_Johto_Route35NationalParkGate_FirstMonIsEgg
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1AskToUseFirstMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_DeclinedToLeaveMonsBehind
	goto_if_ne VAR_RESULT, 0, Route35NationalParkGate_Johto_Route35NationalParkGate_FirstMonIsFainted
	setflag FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WellHoldYourMonText
	waitmessage
	waitbuttonpress
	message Route35NationalParkGate_Johto_Route35NationalParkGatePlayersMonLeftWithHelperText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	goto Route35NationalParkGate_Johto_Route35NationalParkGate_OkayToProceed

Route35NationalParkGate_Johto_Route35NationalParkGate_DeclinedToParticipate:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1TakePartInFutureText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_DeclinedToLeaveMonsBehind:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ChooseMonAndComeBackText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_FirstMonIsFainted:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1FirstMonCantBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_NoRoomInBox:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1MakeRoomText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_FirstMonIsEgg:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1EggAsFirstMonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_ContestIsOver:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ContestIsOverText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_NoContestToday:
	faceplayer
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WeHoldContestsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGateOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST, Route35NationalParkGate_Johto_Route35NationalParkGate_ContestIsOver
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WeHoldContestsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGateYoungsterScript:
	faceplayer
	message Route35NationalParkGate_Johto_Route35NationalParkGateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_BugCatchingContestExplanationSign:
	message Route35NationalParkGate_Johto_BugCatchingContestExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35NationalParkGate_Johto_Route35NationalParkGate_GetDayOfWeek_Sub:
	goto Johto_Std_DayToTextScript_Sub

Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestRunningCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER, Route35NationalParkGate_Johto_Route35NationalParkBugContestIsRunningScript_Cb
	setvar VAR_JOHTO_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 0
	return

Route35NationalParkGate_Johto_Route35NationalParkBugContestIsRunningScript_Cb:
	setvar VAR_JOHTO_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 2
	return

Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 2, Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_eq VAR_RESULT, 4, Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_eq VAR_RESULT, 6, Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb
	goto_if_set FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER, Route35NationalParkGate_Johto_Route35NationalParkBugContestIsRunningScript_Cb
	setflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	clearflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_YOUNGSTER
	clearflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return

Route35NationalParkGate_Johto_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer_Cb:
	clearflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	setflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_YOUNGSTER
	setflag FLAG_JOHTO_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return

Route35NationalParkGate_Johto_Route35NationalParkGatePlayerApproachOfficer1Movement:
	walk_down
	face_left
	step_end

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1AskToParticipateText:
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

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1GiveParkBallsText:
	.string "Here are the PARK\n"
	.string "BALLS for the\l"
	.string "Contest.$"

Route35NationalParkGate_Johto_Route35NationalParkGatePlayerReceivedParkBallsText:
	.string "{PLAYER} received\n"
	.string "BUG_CONTEST_BALLS PARK BALLS.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ExplainsRulesText:
	.string "The person who\n"
	.string "gets the strong-\l"
	.string "est bug POKéMON\l"
	.string "is the winner."
	.string "\pYou have BUG_CONTEST_MINUTES\n"
	.string "minutes."
	.string "\pIf you run out of\n"
	.string "PARK BALLS, you're\l"
	.string "done."
	.string "\pYou can keep the\n"
	.string "last POKéMON you\l"
	.string "catch as your own."
	.string "\pGo out and catch\n"
	.string "the strongest bug"
	.string "\pPOKéMON you can\n"
	.string "find!$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1AskToUseFirstMonText:
	.string "Uh-oh…"
	.string "\pYou have more than\n"
	.string "one POKéMON."
	.string "\pYou'll have to use\n"
	.string "{STR_VAR_1}, the"
	.string "\pfirst POKéMON in\n"
	.string "your party."
	.string "\pIs that OK with\n"
	.string "you?$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WellHoldYourMonText:
	.string "Fine, we'll hold\n"
	.string "your other POKéMON\l"
	.string "while you compete.$"

Route35NationalParkGate_Johto_Route35NationalParkGatePlayersMonLeftWithHelperText:
	.string "{PLAYER}'s POKéMON\n"
	.string "were left with the\l"
	.string "CONTEST HELPER.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ChooseMonAndComeBackText:
	.string "Please choose the\n"
	.string "POKéMON to be used"
	.string "\pin the Contest,\n"
	.string "then come see me.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1TakePartInFutureText:
	.string "OK. We hope you'll\n"
	.string "take part in the\l"
	.string "future.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1FirstMonCantBattleText:
	.string "Uh-oh…\n"
	.string "The first POKéMON"
	.string "\pin your party\n"
	.string "can't battle."
	.string "\pPlease switch it\n"
	.string "with the POKéMON"
	.string "\pyou want to use,\n"
	.string "then come see me.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1MakeRoomText:
	.string "Uh-oh…\n"
	.string "Both your party"
	.string "\pand your PC BOX\n"
	.string "are full."
	.string "\pYou have no room\n"
	.string "to put the bug\l"
	.string "POKéMON you catch."
	.string "\pPlease make room\n"
	.string "in your party or"
	.string "\pyour PC BOX, then\n"
	.string "come see me.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1EggAsFirstMonText:
	.string "Uh-oh…\n"
	.string "You have an EGG as"
	.string "\pthe first POKéMON\n"
	.string "in your party."
	.string "\pPlease switch it\n"
	.string "with the POKéMON"
	.string "\pyou want to use,\n"
	.string "then come see me.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1ContestIsOverText:
	.string "Today's Contest is\n"
	.string "over. We hope you"
	.string "\pwill participate\n"
	.string "in the future.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WeHoldContestsText:
	.string "We hold Contests\n"
	.string "regularly in the"
	.string "\pPARK. You should\n"
	.string "give it a shot.$"

Route35NationalParkGate_Johto_Route35NationalParkGateYoungsterText:
	.string "When is the next\n"
	.string "Bug-Catching Con-\l"
	.string "test going to be?$"

Route35NationalParkGate_Johto_BugCatchingContestExplanationText:
	.string "The Bug-Catching\n"
	.string "Contest is held on"
	.string "\pTuesday, Thursday\n"
	.string "and Saturday."
	.string "\pNot only do you\n"
	.string "earn a prize just"
	.string "\pfor participating,\n"
	.string "you also get to"
	.string "\pkeep the bug\n"
	.string "POKéMON you may"
	.string "\phave at the end of\n"
	.string "the contest.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WantToFinishText:
	.string "You still have {STR_VAR_3}\n"
	.string "minute(s) left.\p"
	.string "Do you want to\n"
	.string "finish now?$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1WaitAtNorthGateText:
	.string "OK. Please wait at\n"
	.string "the North Gate for\l"
	.string "the announcement\n"
	.string "of the winners.$"

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1OkGoFinishText:
	.string "OK. Please get\n"
	.string "back outside and\l"
	.string "finish up.$"
