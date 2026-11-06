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

Route36NationalParkGate_Johto_BugCatchingContestExplanationSign_Entry::
	lockall
	goto Route36NationalParkGate_Johto_BugCatchingContestExplanationSign

Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript_Entry::
	lockall
	goto Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript


Route36NationalParkGate_Johto_Route36NationalParkGateLeavingContestEarlyScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	special JohtoGetBugContestRemainingMinutes
	buffernumberstring STR_VAR_3, VAR_RESULT
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36BugContestJudgeAndAward
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WantToFinishText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36OfficerScriptContest_GoBackToContest
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WaitHereForAnnouncementText
	waitmessage
	waitbuttonpress
	closemessage
	goto Route36NationalParkGate_Johto_Route36BugContestJudgeAndAward

Route36NationalParkGate_Johto_Route36BugContestJudgeAndAward:
	message Route36NationalParkGate_Johto_Text_ContestReadyToJudge
	waitmessage
	waitbuttonpress
	closemessage
	special JohtoBugContestJudge
	@ Announce 3rd place
	setvar VAR_0x8004, 3
	special JohtoBugContestBufferWinner
	message Route36NationalParkGate_Johto_Text_ContestThirdPlace
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	closemessage
	@ Announce 2nd place
	setvar VAR_0x8004, 2
	special JohtoBugContestBufferWinner
	message Route36NationalParkGate_Johto_Text_ContestSecondPlace
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	closemessage
	@ Announce 1st place
	setvar VAR_0x8004, 1
	special JohtoBugContestBufferWinner
	message Route36NationalParkGate_Johto_Text_ContestFirstPlace
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	closemessage
	@ Award prize according to player placement in VAR_RESULT
	goto_if_eq VAR_RESULT, 1, Route36NationalParkGate_Johto_Route36BugContest_1stPlace
	goto_if_eq VAR_RESULT, 2, Route36NationalParkGate_Johto_Route36BugContest_2ndPlace
	goto_if_eq VAR_RESULT, 3, Route36NationalParkGate_Johto_Route36BugContest_3rdPlace
	@ Consolation prize
	message Route36NationalParkGate_Johto_Text_ContestConsolationPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36BugContest_NoRoomConsolation
	goto Route36NationalParkGate_Johto_Route36BugContest_Finish

Route36NationalParkGate_Johto_Route36BugContest_1stPlace:
	bufferitemname STR_VAR_2, ITEM_SUN_STONE
	message Route36NationalParkGate_Johto_Text_ContestPlayerWonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36BugContest_NoRoom1st
	goto Route36NationalParkGate_Johto_Route36BugContest_Finish

Route36NationalParkGate_Johto_Route36BugContest_2ndPlace:
	bufferitemname STR_VAR_2, ITEM_EVERSTONE
	message Route36NationalParkGate_Johto_Text_ContestPlayerWonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36BugContest_NoRoom2nd
	goto Route36NationalParkGate_Johto_Route36BugContest_Finish

Route36NationalParkGate_Johto_Route36BugContest_3rdPlace:
	bufferitemname STR_VAR_2, ITEM_SITRUS_BERRY
	message Route36NationalParkGate_Johto_Text_ContestPlayerWonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_SITRUS_BERRY
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36BugContest_NoRoom3rd
	goto Route36NationalParkGate_Johto_Route36BugContest_Finish

Route36NationalParkGate_Johto_Route36BugContest_NoRoom1st:
	setflag FLAG_JOHTO_CONTEST_OFFICER_HAS_SUN_STONE
	goto Route36NationalParkGate_Johto_Route36BugContest_NoRoomCommon

Route36NationalParkGate_Johto_Route36BugContest_NoRoom2nd:
	setflag FLAG_JOHTO_CONTEST_OFFICER_HAS_EVERSTONE
	goto Route36NationalParkGate_Johto_Route36BugContest_NoRoomCommon

Route36NationalParkGate_Johto_Route36BugContest_NoRoom3rd:
	setflag FLAG_JOHTO_CONTEST_OFFICER_HAS_GOLD_BERRY
	goto Route36NationalParkGate_Johto_Route36BugContest_NoRoomCommon

Route36NationalParkGate_Johto_Route36BugContest_NoRoomConsolation:
	setflag FLAG_JOHTO_CONTEST_OFFICER_HAS_BERRY
	goto Route36NationalParkGate_Johto_Route36BugContest_NoRoomCommon

Route36NationalParkGate_Johto_Route36BugContest_NoRoomCommon:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WellHoldPrizeText
	waitmessage
	waitbuttonpress
	goto Route36NationalParkGate_Johto_Route36BugContest_Finish

Route36NationalParkGate_Johto_Route36BugContest_Finish:
	goto_if_unset FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER, Route36NationalParkGate_Johto_Route36BugContest_Done
	message Route36NationalParkGate_Johto_Text_ContestReturnParty
	waitmessage
	waitbuttonpress
	clearflag FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER

Route36NationalParkGate_Johto_Route36BugContest_Done:
	message Route36NationalParkGate_Johto_Text_ContestJoinUsNextTime
	waitmessage
	waitbuttonpress
	closemessage
	special JohtoBugContestCleanup
	releaseall
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_GoBackToContest:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1OkGoFinishText
	waitmessage
	waitbuttonpress
	closemessage
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 33, 18
	waitstate
	end

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
	clearflag FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER

Route36NationalParkGate_Johto_Route36OfficerScriptContest_ResumeStartingContest:
	setflag FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER
	fadedefaultbgm
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1GiveParkBallsText
	waitmessage
	waitbuttonpress
	waitse
	message Route36NationalParkGate_Johto_Route36NationalParkGatePlayerReceivedParkBallsText
	waitmessage
	playse SE_PIN
	waitse
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ExplainsRulesText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_ENGINE_BUG_CONTEST_TIMER
	special JohtoGiveParkBalls
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 33, 18
	waitstate
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_LeaveMonsWithOfficer:
	getpartysize
	goto_if_lt VAR_RESULT, 6, Route36NationalParkGate_Johto_Route36OfficerScriptContest_ContinueLeavingMons
	setvar VAR_RESULT, 20
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36OfficerScriptContest_BoxFull

Route36NationalParkGate_Johto_Route36OfficerScriptContest_ContinueLeavingMons:
	special JohtoCheckFirstMonIsEgg
	goto_if_eq VAR_RESULT, TRUE, Route36NationalParkGate_Johto_Route36OfficerScriptContest_FirstMonIsEgg
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1AskToUseFirstMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36OfficerScriptContest_RefusedToLeaveMons
	goto_if_ne VAR_RESULT, 0, Route36NationalParkGate_Johto_Route36OfficerScriptContest_FirstMonIsFainted
	setflag FLAG_JOHTO_LEFT_MONS_WITH_CONTEST_OFFICER
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WellHoldYourMonText
	waitmessage
	waitbuttonpress
	message Route36NationalParkGate_Johto_Route36NationalParkGatePlayersMonLeftWithHelperText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	goto Route36NationalParkGate_Johto_Route36OfficerScriptContest_ResumeStartingContest

Route36NationalParkGate_Johto_Route36OfficerScriptContest_DecidedNotToJoinContest:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1TakePartInFutureText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_RefusedToLeaveMons:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ChooseMonAndComeBackText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_FirstMonIsFainted:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1FirstMonCantBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_BoxFull:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1MakeRoomText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36NationalParkGate_Johto_Route36OfficerScriptContest_FirstMonIsEgg:
	message Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1EggAsFirstMonText
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

Route36NationalParkGate_Johto_BugCatchingContestExplanationSign:
	message Route36NationalParkGate_Johto_UnusedBugCatchingContestExplanationText
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

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1GiveParkBallsText:
	.string "Here are the PARK\n"
	.string "BALLS for the\l"
	.string "Contest.$"

Route36NationalParkGate_Johto_Route36NationalParkGatePlayerReceivedParkBallsText:
	.string "{PLAYER} received\n"
	.string "BUG_CONTEST_BALLS PARK BALLS.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ExplainsRulesText:
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

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1AskToUseFirstMonText:
	.string "Uh-oh…"
	.string "\pYou have more than\n"
	.string "one POKéMON."
	.string "\pYou'll have to use\n"
	.string "{STR_VAR_1}, the"
	.string "\pfirst POKéMON in\n"
	.string "your party."
	.string "\pIs that OK with\n"
	.string "you?$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WellHoldYourMonText:
	.string "Fine, we'll hold\n"
	.string "your other POKéMON\l"
	.string "while you compete.$"

Route36NationalParkGate_Johto_Route36NationalParkGatePlayersMonLeftWithHelperText:
	.string "{PLAYER}'s POKéMON\n"
	.string "were left with the\l"
	.string "CONTEST HELPER.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1ChooseMonAndComeBackText:
	.string "Please choose the\n"
	.string "POKéMON to be used"
	.string "\pin the Contest,\n"
	.string "then come see me.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1TakePartInFutureText:
	.string "OK. We hope you'll\n"
	.string "take part in the\l"
	.string "future.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1FirstMonCantBattleText:
	.string "Uh-oh…\n"
	.string "The first POKéMON"
	.string "\pin your party\n"
	.string "can't battle."
	.string "\pPlease switch it\n"
	.string "with the POKéMON"
	.string "\pyou want to use,\n"
	.string "then come see me.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1MakeRoomText:
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

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1EggAsFirstMonText:
	.string "Uh-oh…\n"
	.string "You have an EGG as"
	.string "\pthe first POKéMON\n"
	.string "in your party."
	.string "\pPlease switch it\n"
	.string "with the POKéMON"
	.string "\pyou want to use,\n"
	.string "then come see me.$"

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

Route36NationalParkGate_Johto_UnusedBugCatchingContestExplanationText:
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

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WantToFinishText:
	.string "You still have {STR_VAR_3}\n"
	.string "minute(s) left.\p"
	.string "Do you want to\n"
	.string "finish now?$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1WaitHereForAnnouncementText:
	.string "OK. Please wait\n"
	.string "here for the\l"
	.string "announcement of\n"
	.string "the winners.$"

Route36NationalParkGate_Johto_Route36NationalParkGateOfficer1OkGoFinishText:
	.string "OK. Please go back\n"
	.string "outside and finish\l"
	.string "up.$"

Route36NationalParkGate_Johto_Text_ContestReadyToJudge:
	.string "We will now judge the POKéMON\n"
	.string "you've caught.\p"
	.string "……\n"
	.string "……\p"
	.string "We have chosen the winners!\n"
	.string "Are you ready for this?$"

Route36NationalParkGate_Johto_Text_ContestThirdPlace:
	.string "Placing third was {STR_VAR_1},\n"
	.string "who caught a {STR_VAR_2}!\p"
	.string "The score was {STR_VAR_3} points!$"

Route36NationalParkGate_Johto_Text_ContestSecondPlace:
	.string "Placing second was {STR_VAR_1},\n"
	.string "who caught a {STR_VAR_2}!\p"
	.string "The score was {STR_VAR_3} points!$"

Route36NationalParkGate_Johto_Text_ContestFirstPlace:
	.string "This Bug-Catching Contest\n"
	.string "winner is… {STR_VAR_1},\l"
	.string "who caught a {STR_VAR_2}!\p"
	.string "The winning score was\n"
	.string "{STR_VAR_3} points!$"

Route36NationalParkGate_Johto_Text_ContestPlayerWonPrize:
	.string "{PLAYER}, the prize winner,\n"
	.string "wins a {STR_VAR_2}!$"

Route36NationalParkGate_Johto_Text_ContestConsolationPrize:
	.string "Everyone else gets an ORAN BERRY\n"
	.string "as a consolation prize!$"

Route36NationalParkGate_Johto_Text_ContestReturnParty:
	.string "We'll return the POKéMON we kept\n"
	.string "for you. Here you go!$"

Route36NationalParkGate_Johto_Text_ContestJoinUsNextTime:
	.string "Please join us for the next Contest!$"
