GoldenrodUndergroundSwitchRoomEntrances_Johto_MapScripts::
	.byte 0

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSmokeBall_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSmokeBall

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesFullHeal_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesFullHeal

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch1Script_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch1Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch2Script_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch2Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch3Script_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch3Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_EmergencySwitchScript_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_EmergencySwitchScript

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene1_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene1

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene2_Entry::
	lockall
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene2


GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript:
	faceplayer
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript:
	faceplayer
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_TeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene1:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	playse SE_EXIT
	clearflag FLAG_JOHTO_RIVAL_GOLDENROD_UNDERGROUND
	addobject 11
	waitse
	applymovement 11, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalApproachMovement1
	waitmovement 11
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	call GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Sub
	applymovement 11, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalRetreatMovement1
	waitmovement 11
	playse SE_EXIT
	removeobject 11
	setvar VAR_JOHTO_SCENE_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1
	waitse
	fadedefaultbgm
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalScene2:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	playse SE_EXIT
	clearflag FLAG_JOHTO_RIVAL_GOLDENROD_UNDERGROUND
	addobject 11
	waitse
	applymovement 11, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalApproachMovement2
	waitmovement 11
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	call GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Sub
	applymovement 11, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalRetreatMovement2
	waitmovement 11
	playse SE_EXIT
	removeobject 11
	setvar VAR_JOHTO_SCENE_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1
	waitse
	fadedefaultbgm
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM11::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_11, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11SeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_11
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM11_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM11_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM25::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_25, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25SeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_25
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM25_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM25_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarDuncan::
	trainerbattle_single TRAINER_JOHTO_BURGLAR_DUNCAN, GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanSeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanBeatenText
	setflag FLAG_JOHTO_BEAT_BURGLAR_DUNCAN
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarDuncan_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarDuncan_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarEddie::
	trainerbattle_single TRAINER_JOHTO_BURGLAR_EDDIE, GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieSeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieBeatenText
	setflag FLAG_JOHTO_BEAT_BURGLAR_EDDIE
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarEddie_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerBurglarEddie_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM13::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_13, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13SeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_13
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM13_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntM13_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntF3::
	trainerbattle_single TRAINER_JOHTO_GRUNTF_GRUNTF_3, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3SeenText, GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTF_3
	lock
	faceplayer
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntF3_Script

GoldenrodUndergroundSwitchRoomEntrances_Johto_TrainerGruntF3_Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch1Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch1
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_JOHTO_SWITCH_1, GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch1Script_On
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch1Script_On:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch2Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch2
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_JOHTO_SWITCH_2, GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch2Script_On
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch2Script_On:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch3Script:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch3
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_JOHTO_SWITCH_3, GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch3Script_On
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_Switch3Script_On:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_EmergencySwitchScript:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Emergency
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_JOHTO_EMERGENCY_SWITCH, GoldenrodUndergroundSwitchRoomEntrances_Johto_EmergencySwitchScript_On
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	setvar VAR_RESULT, 7
	setflag FLAG_JOHTO_EMERGENCY_SWITCH
	setflag FLAG_JOHTO_SWITCH_1
	setflag FLAG_JOHTO_SWITCH_2
	setflag FLAG_JOHTO_SWITCH_3
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors

GoldenrodUndergroundSwitchRoomEntrances_Johto_EmergencySwitchScript_On:
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	setvar VAR_RESULT, 0
	clearflag FLAG_JOHTO_EMERGENCY_SWITCH
	clearflag FLAG_JOHTO_SWITCH_1
	clearflag FLAG_JOHTO_SWITCH_2
	clearflag FLAG_JOHTO_SWITCH_3
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_DontToggle:
	closemessage
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors:
	@ TODO unsupported: readmem wUndergroundSwitchPositions
	goto Johto_EventScript_Unimplemented

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesSmokeBall:
	finditem ITEM_SMOKE_BALL
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrancesFullHeal:
	finditem ITEM_FULL_HEAL
	releaseall
	end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Sub:
	goto_if_set FLAG_JOHTO_RIVAL_BURNED_TOWER, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Continue_Sub
	setflag FLAG_JOHTO_RIVAL_BURNED_TOWER
	setvar VAR_JOHTO_SCENE_BURNED_TOWER_1F, 1

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Continue_Sub:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_RIVAL_GOLDENROD_UNDERGROUND
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Totodile_Sub
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Chikorita_Sub
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_4_TOTODILE, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalWinText
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_FinishRivalBattle_Sub

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Totodile_Sub:
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_4_CHIKORITA, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalWinText
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_FinishRivalBattle_Sub

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_Chikorita_Sub:
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_4_CYNDAQUIL, GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalWinText
	goto GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_FinishRivalBattle_Sub

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBattleScript_FinishRivalBattle_Sub:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalApproachMovement1:
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalApproachMovement2:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalRetreatMovement1:
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalRetreatMovement2:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalBeforeText:
	.string "Hold it!"
	.string "\pI saw you, so I\n"
	.string "tailed you."
	.string "\pI don't need you\n"
	.string "underfoot while I"
	.string "\ptake care of TEAM\n"
	.string "ROCKET."
	.string "\p…Wait a second.\n"
	.string "You beat me be-\l"
	.string "fore, didn't you?"
	.string "\pThat was just a\n"
	.string "fluke."
	.string "\pBut I repay my\n"
	.string "debts!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalWinText:
	.string "…Why…\n"
	.string "Why do I lose?"
	.string "\pI've assembled the\n"
	.string "toughest POKéMON."
	.string "\pI didn't ease up\n"
	.string "on the gas."
	.string "\pSo why do I lose?$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_UndergroundRivalAfterText:
	.string "…I don't under-\n"
	.string "stand…"
	.string "\pIs what that LANCE\n"
	.string "guy said true?"
	.string "\pThat I don't treat\n"
	.string "POKéMON properly?"
	.string "\pLove…"
	.string "\pTrust…"
	.string "\pAre they really\n"
	.string "what I lack?"
	.string "\pAre they keeping\n"
	.string "me from winning?"
	.string "\pI… I just don't\n"
	.string "understand."
	.string "\pBut it's not going\n"
	.string "to end here."
	.string "\pNot now. Not\n"
	.string "because of this."
	.string "\pI won't give up my\n"
	.string "dream of becoming"
	.string "\pthe world's best\n"
	.string "POKéMON trainer!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText:
	.string "I was challenged\n"
	.string "to a battle down-\l"
	.string "stairs."
	.string "\pIt's rough down\n"
	.string "there. You'd\l"
	.string "better be careful.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GoldenrodUndergroundSwitchRoomEntrances_TeacherText:
	.string "There are some\n"
	.string "shops downstairs…"
	.string "\pBut there are\n"
	.string "also trainers."
	.string "\pI'm scared to go\n"
	.string "down there.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11SeenText:
	.string "Open one shutter,\n"
	.string "another closes."
	.string "\pBet you can't get\n"
	.string "where you want!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11BeatenText:
	.string "Drat! I was sunk\n"
	.string "by indecision!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM11AfterBattleText:
	.string "I'm confused too…\n"
	.string "The switch on the"
	.string "\pend is the one to\n"
	.string "press first, but…$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25SeenText:
	.string "Kwahaha!"
	.string "\pConfounded by the\n"
	.string "shutters, are we?"
	.string "\pI'll let you in on\n"
	.string "a secret if you\l"
	.string "can beat me!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25BeatenText:
	.string "Uwww…\n"
	.string "I blew it.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM25AfterBattleText:
	.string "All right. A hint!"
	.string "\pChange the order\n"
	.string "of switching."
	.string "\pThat'll change the\n"
	.string "ways the shutters\l"
	.string "open and close.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanSeenText:
	.string "Fork over your\n"
	.string "goodies!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanBeatenText:
	.string "Mercy!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarDuncanAfterBattleText:
	.string "Steal and sell!\n"
	.string "That's basic in\l"
	.string "crime, kid!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieSeenText:
	.string "They ditched this\n"
	.string "project before\l"
	.string "they finished."
	.string "\pI'm searching for\n"
	.string "leftover loot.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieBeatenText:
	.string "Over the top!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_BurglarEddieAfterBattleText:
	.string "UNDERGROUND WARE-\n"
	.string "HOUSE?"
	.string "\pWhat do you want\n"
	.string "to go there for?"
	.string "\pThere's nothing\n"
	.string "down there.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13SeenText:
	.string "I don't care if\n"
	.string "you're lost."
	.string "\pYou show up here,\n"
	.string "you're nothing but\l"
	.string "a victim!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13BeatenText:
	.string "Urk! Yeah, think\n"
	.string "you're cool, huh?$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntM13AfterBattleText:
	.string "You must have ice\n"
	.string "in your veins to\l"
	.string "dis TEAM ROCKET.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch1:
	.string "It's labeled\n"
	.string "SWITCH 1.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3SeenText:
	.string "Are you lost? No,\n"
	.string "you can't be."
	.string "\pYou don't have\n"
	.string "that scared look."
	.string "\pI'll give you\n"
	.string "something to be\l"
	.string "scared about!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3BeatenText:
	.string "How could you?$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_GruntF3AfterBattleText:
	.string "Go wherever you'd\n"
	.string "like! Get lost!\l"
	.string "See if I care!$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OffTurnOn:
	.string "It's OFF.\n"
	.string "Turn it ON?$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_OnTurnOff:
	.string "It's ON.\n"
	.string "Turn it OFF?$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch2:
	.string "It's labeled\n"
	.string "SWITCH 2.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Switch3:
	.string "It's labeled\n"
	.string "SWITCH 3.$"

GoldenrodUndergroundSwitchRoomEntrances_Johto_SwitchRoomText_Emergency:
	.string "It's labeled\n"
	.string "EMERGENCY.$"
