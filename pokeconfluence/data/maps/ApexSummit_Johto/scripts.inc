ApexSummit_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ApexSummit_Johto_OnTransition
	.byte 0

ApexSummit_Johto_OnTransition:
	special ApexSummit_SetUpCurrentRound
	end

ApexSummit_Johto_EventScript_Attendant::
	lock
	faceplayer
	special ApexSummit_SetUpCurrentRound
	msgbox ApexSummit_Johto_Text_AttendantInfo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ApexSummit_Johto_EventScript_AttendantForfeit
	msgbox ApexSummit_Johto_Text_AttendantKeepGoing, MSGBOX_DEFAULT
	release
	end

ApexSummit_Johto_EventScript_AttendantForfeit::
	msgbox ApexSummit_Johto_Text_AttendantConfirmForfeit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ApexSummit_Johto_EventScript_AttendantKeepGoing
	msgbox ApexSummit_Johto_Text_AttendantForfeited, MSGBOX_DEFAULT
	closemessage
	special ApexSummit_ExitChallenge
	warp MAP_JOHTO_SILVER_CAVE_OUTSIDE, 24, 22
	waitstate
	end

ApexSummit_Johto_EventScript_AttendantKeepGoing::
	msgbox ApexSummit_Johto_Text_AttendantKeepGoing, MSGBOX_DEFAULT
	release
	end

ApexSummit_Johto_EventScript_Contender::
	lock
	faceplayer
	special ApexSummit_SetUpCurrentRound
	message gStringVar4
	waitmessage
	waitbuttonpress
	closemessage
	special ApexSummit_StartBattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, ApexSummit_Johto_EventScript_Defeated
	special ApexSummit_OnRoundWon
	goto_if_eq VAR_RESULT, TRUE, ApexSummit_Johto_EventScript_TournamentWon
	special ApexSummit_SetUpCurrentRound
	msgbox ApexSummit_Johto_Text_RoundCleared, MSGBOX_DEFAULT
	closemessage
	applymovement 2, ApexSummit_Johto_Movement_ContenderExit
	waitmovement 0
	removeobject 2
	delay 20
	setobjectxyperm 2, 6, 4
	addobject 2
	applymovement 2, ApexSummit_Johto_Movement_ContenderEnter
	waitmovement 0
	setobjectxyperm 2, 6, 7
	release
	end

ApexSummit_Johto_EventScript_Defeated::
	msgbox ApexSummit_Johto_Text_Defeated, MSGBOX_DEFAULT
	closemessage
	special ApexSummit_ExitChallenge
	warp MAP_JOHTO_SILVER_CAVE_OUTSIDE, 24, 22
	waitstate
	end

ApexSummit_Johto_EventScript_TournamentWon::
	playfanfare MUS_OBTAIN_ITEM
	msgbox ApexSummit_Johto_Text_TournamentWon, MSGBOX_DEFAULT
	waitfanfare
	special ApexSummit_AwardPrizes
	giveitem ITEM_RELIC_CROWN
	givedecoration DECOR_GOLD_SHIELD
	msgbox ApexSummit_Johto_Text_CrownAndTrophyAwarded, MSGBOX_DEFAULT
	closemessage
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	end

ApexSummit_Johto_Movement_ContenderExit:
	walk_up
	walk_up
	walk_up
	step_end

ApexSummit_Johto_Movement_ContenderEnter:
	walk_down
	walk_down
	walk_down
	step_end

ApexSummit_Johto_Text_AttendantInfo:
	.string "Welcome to the APEX SUMMIT!\p"
	.string "You are currently facing Round {STR_VAR_2}\n"
	.string "of 5 against {STR_VAR_1}.\p"
	.string "Would you like to forfeit your run\n"
	.string "and return to Mt. Silver?$"

ApexSummit_Johto_Text_AttendantConfirmForfeit:
	.string "Are you sure you want to forfeit\n"
	.string "your Apex Summit challenge?$"

ApexSummit_Johto_Text_AttendantForfeited:
	.string "Very well. Your challenge has ended.\n"
	.string "Come back when you are ready to climb!$"

ApexSummit_Johto_Text_AttendantKeepGoing:
	.string "Show no fear! Conquer all 5 rounds to\n"
	.string "claim the title of APEX CHAMPION!$"

ApexSummit_Johto_Text_RoundCleared:
	.string "Sensational victory!\p"
	.string "Your party has been completely restored.\n"
	.string "Here comes challenger No. {STR_VAR_3}: {STR_VAR_1}!$"

ApexSummit_Johto_Text_Defeated:
	.string "You fought valiantly!\p"
	.string "However, the Apex Summit Gauntlet is an\n"
	.string "unforgiving trial of absolute strength.\p"
	.string "Regroup and return when you are ready!$"

ApexSummit_Johto_Text_TournamentWon:
	.string "INCREDIBLE! SPECTACULAR!\p"
	.string "You have conquered all 5 rounds of the\n"
	.string "APEX SUMMIT GAUNTLET!\p"
	.string "By proving your mastery over history's\n"
	.string "greatest leaders, you are recognized\l"
	.string "across KANTO, JOHTO, and HOENN as the\l"
	.string "undisputed APEX CHAMPION!$"

ApexSummit_Johto_Text_CrownAndTrophyAwarded:
	.string "All Pokémon in your team have received\n"
	.string "the prestigious VICTORY RIBBON!\p"
	.string "The soft level caps across all three\n"
	.string "regions have been dissolved forever,\l"
	.string "and the golden APEX STAR now shines\l"
	.string "brightly on your TRAINER CARD!$"
