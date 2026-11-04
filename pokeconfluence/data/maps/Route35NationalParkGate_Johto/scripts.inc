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
	@ TODO unsupported: readvar VAR_CONTESTMINUTES
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special ContestDropOffMons
	goto Johto_EventScript_Unimplemented

Route35NationalParkGate_Johto_Route35NationalParkGate_LeaveTheRestBehind:
	getpartysize
	goto_if_lt VAR_RESULT, 6, Route35NationalParkGate_Johto_Route35NationalParkGate_LessThanFullParty
	@ TODO unsupported: readvar VAR_BOXSPACE
	goto Johto_EventScript_Unimplemented

Route35NationalParkGate_Johto_Route35NationalParkGate_LessThanFullParty:
	@ TODO unsupported: special CheckFirstMonIsEgg
	goto Johto_EventScript_Unimplemented

Route35NationalParkGate_Johto_Route35NationalParkGate_DeclinedToParticipate:
	message Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1TakePartInFutureText
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

Route35NationalParkGate_Johto_Route35NationalParkGateOfficer1TakePartInFutureText:
	.string "OK. We hope you'll\n"
	.string "take part in the\l"
	.string "future.$"

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
