TeamRocketBaseB2F_Johto_MapScripts::
	.byte 0

TeamRocketBaseB2F_Johto_RocketElectrode1_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketElectrode1

TeamRocketBaseB2F_Johto_RocketElectrode2_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketElectrode2

TeamRocketBaseB2F_Johto_RocketElectrode3_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketElectrode3

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTMThief_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTMThief

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTransmitterScript_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTransmitterScript

TeamRocketBaseB2F_Johto_LanceHealsScript1_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_LanceHealsScript1

TeamRocketBaseB2F_Johto_LanceHealsScript2_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_LanceHealsScript2

TeamRocketBaseB2F_Johto_RocketBaseBossFLeft_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketBaseBossFLeft

TeamRocketBaseB2F_Johto_RocketBaseBossFRight_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketBaseBossFRight

TeamRocketBaseB2F_Johto_RocketBaseCantLeaveScript_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketBaseCantLeaveScript

TeamRocketBaseB2F_Johto_RocketBaseLancesSideScript_Entry::
	lockall
	goto TeamRocketBaseB2F_Johto_RocketBaseLancesSideScript


TeamRocketBaseB2F_Johto_RocketBaseBossFLeft:
	setobjectxyperm 3, 9, 13
	goto TeamRocketBaseB2F_Johto_RocketBaseBossFScript

TeamRocketBaseB2F_Johto_RocketBaseBossFRight:
	setobjectxyperm 2, 21, 16
	setobjectxyperm 1, 21, 16
	setobjectxyperm 4, 10, 13
	setobjectxyperm 3, 10, 13

TeamRocketBaseB2F_Johto_RocketBaseBossFScript:
	clearflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_EXECUTIVE
	addobject 2
	clearflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE
	addobject 1
	message TeamRocketBaseB2F_Johto_RocketBaseExecutiveFHoldItText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB2F_Johto_RocketBasePlayerApproachesBossFMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_DUMMY, FALSE
	applymovement 2, TeamRocketBaseB2F_Johto_RocketBaseBossFApproachesPlayerMovement
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, TeamRocketBaseB2F_Johto_RocketBaseGruntApproachesPlayerMovement
	waitmovement 1
	message TeamRocketBaseB2F_Johto_RocketBaseBossFThrashText
	waitmessage
	waitbuttonpress
	closemessage
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	clearflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_DRAGONITE
	addobject 4
	applymovement 4, TeamRocketBaseB2F_Johto_RocketBaseDragoniteAttacksMovement
	waitmovement 4
	applymovement 2, TeamRocketBaseB2F_Johto_RocketBaseBossFHitMovement
	waitmovement 2
	applymovement 1, TeamRocketBaseB2F_Johto_RocketBaseGruntProtectsBossFMovement
	waitmovement 1
	clearflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_LANCE
	addobject 3
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesBossFMovement
	waitmovement 3
	message TeamRocketBaseB2F_Johto_RocketBaseLanceShareFunText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 2, TeamRocketBaseB2F_Johto_RocketBaseBossFFacesPlayerMovement
	waitmovement 2
	message TeamRocketBaseB2F_Johto_RocketBaseBossDontMeddleText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, TeamRocketBaseB2F_Johto_RocketBaseGruntBattlesLanceMovement
	waitmovement 1
	applymovement 2, TeamRocketBaseB2F_Johto_RocketBaseBossFBattlesPlayerMovement
	waitmovement 2
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_JOHTO_EXECUTIVEF_EXECUTIVEF_2, TeamRocketBaseB2F_Johto_RocketBaseBossWinText
	removeobject 4
	setflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_EXECUTIVE
	setflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE
	setflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_LANCE
	setflag FLAG_JOHTO_BEAT_ROCKET_EXECUTIVEF_2
	message TeamRocketBaseB2F_Johto_RocketBaseBossRetreatText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	removeobject 2
	removeobject 11
	removeobject 12
	removeobject 13
	delay 15
	fadescreen FADE_FROM_BLACK
	setvar VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B2F, 2
	clearflag FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_LANCE
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	message TeamRocketBaseB2F_Johto_RocketBaseLancePostBattleText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceChecksPlayerMovement
	waitmovement 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message TeamRocketBaseB2F_Johto_RocketBaseLancePowerOffText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesMachineMovement
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesMachineMovement
	waitmovement 3
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLancePacesMovement
	waitmovement 3
	message TeamRocketBaseB2F_Johto_RockerBaseLanceElectrodeFaintText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesElectrodesMovement
	waitmovement 3
	removeobject 3

TeamRocketBaseB2F_Johto_RocketBaseCantLeaveScript:
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB2F_Johto_RocketBasePlayerCantLeaveElectrodesMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

TeamRocketBaseB2F_Johto_RocketBaseLancesSideScript:
	message TeamRocketBaseB2F_Johto_RocketBaseLancesSideText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB2F_Johto_RocketBasePlayerCantGoRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

TeamRocketBaseB2F_Johto_LanceHealsScript1:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	goto TeamRocketBaseB2F_Johto_LanceHealsCommon

TeamRocketBaseB2F_Johto_LanceHealsScript2:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, Johto_Movement_Face_Left
	waitmovement 3

TeamRocketBaseB2F_Johto_LanceHealsCommon:
	message TeamRocketBaseB2F_Johto_LanceHealsText1
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	playse SE_PIN
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	message TeamRocketBaseB2F_Johto_LanceHealsText2
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B2F, 1
	setflag FLAG_JOHTO_LANCE_HEALED_YOU_IN_TEAM_ROCKET_BASE
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, TeamRocketBaseB2F_Johto_LanceHealsCommon_FacingRight
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceLeavesAfterHealMovement
	waitmovement 3
	removeobject 3
	releaseall
	end

TeamRocketBaseB2F_Johto_LanceHealsCommon_FacingRight:
	applymovement 3, TeamRocketBaseB2F_Johto_RocketBaseLanceLeavesAfterHealRightMovement
	waitmovement 3
	removeobject 3
	releaseall
	end

TeamRocketBaseB2F_Johto_TrainerGruntM17::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_17, TeamRocketBaseB2F_Johto_GruntM17SeenText, TeamRocketBaseB2F_Johto_GruntM17BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_17
	lock
	faceplayer
	goto TeamRocketBaseB2F_Johto_TrainerGruntM17_Script

TeamRocketBaseB2F_Johto_TrainerGruntM17_Script:
	message TeamRocketBaseB2F_Johto_GruntM17AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB2F_Johto_TrainerGruntM18::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_18, TeamRocketBaseB2F_Johto_GruntM18SeenText, TeamRocketBaseB2F_Johto_GruntM18BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_18
	lock
	faceplayer
	goto TeamRocketBaseB2F_Johto_TrainerGruntM18_Script

TeamRocketBaseB2F_Johto_TrainerGruntM18_Script:
	message TeamRocketBaseB2F_Johto_GruntM18AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB2F_Johto_TrainerGruntM19::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_19, TeamRocketBaseB2F_Johto_GruntM19SeenText, TeamRocketBaseB2F_Johto_GruntM19BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_19
	lock
	faceplayer
	goto TeamRocketBaseB2F_Johto_TrainerGruntM19_Script

TeamRocketBaseB2F_Johto_TrainerGruntM19_Script:
	message TeamRocketBaseB2F_Johto_GruntM19AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB2F_Johto_RocketElectrode1:
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	removeobject 5
	removeobject 8
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	@ TODO unsupported: special PlayMapMusic
	goto Johto_EventScript_Unimplemented

TeamRocketBaseB2F_Johto_RocketElectrode2:
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	removeobject 6
	removeobject 9
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	@ TODO unsupported: special PlayMapMusic
	goto Johto_EventScript_Unimplemented

TeamRocketBaseB2F_Johto_RocketElectrode3:
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	removeobject 7
	removeobject 10
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	goto_if_unset FLAG_JOHTO_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap
	@ TODO unsupported: special PlayMapMusic
	goto Johto_EventScript_Unimplemented

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FReloadMap:
	releaseall
	end

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTransmitterScript:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTransmitterScript_Deactivated
	message TeamRocketBaseB2F_Johto_RocketBaseB2FTransmitterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTransmitterScript_Deactivated:
	message TeamRocketBaseB2F_Johto_RocketBaseB2FDeactivateTransmitterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB2F_Johto_TeamRocketBaseB2FTMThief:
	finditem ITEM_TM_THIEF
	releaseall
	end

TeamRocketBaseB2F_Johto_RocketBaseLanceLeavesAfterHealMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLanceLeavesAfterHealRightMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TeamRocketBaseB2F_Johto_RocketBasePlayerApproachesBossFMovement:
	walk_down
	walk_down
	walk_down
	face_right
	step_end

TeamRocketBaseB2F_Johto_RocketBaseBossFApproachesPlayerMovement:
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_down
	step_end

TeamRocketBaseB2F_Johto_RocketBaseGruntApproachesPlayerMovement:
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseDragoniteAttacksMovement:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

TeamRocketBaseB2F_Johto_RocketBaseBossFHitMovement:
	lock_facing_direction
	jump_right
	unlock_facing_direction
	step_end

TeamRocketBaseB2F_Johto_RocketBaseBossFFacesPlayerMovement:
	walk_slow_down
	face_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesBossFMovement:
	walk_right
	walk_right
	walk_right
	step_end

TeamRocketBaseB2F_Johto_RocketBaseBossFBattlesPlayerMovement:
	walk_fast_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseGruntBattlesLanceMovement:
	walk_fast_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseGruntProtectsBossFMovement:
	walk_fast_left
	walk_fast_up
	face_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLanceChecksPlayerMovement:
	walk_right
	walk_right
	face_down
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesMachineMovement:
	walk_up
	walk_up
	walk_up
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLancePacesMovement:
	delay_8
	walk_left
	walk_left
	face_up
	delay_8
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	delay_8
	walk_left
	walk_left
	face_down
	step_end

TeamRocketBaseB2F_Johto_RocketBaseLanceApproachesElectrodesMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

TeamRocketBaseB2F_Johto_RocketBasePlayerCantLeaveElectrodesMovement:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

TeamRocketBaseB2F_Johto_RocketBasePlayerCantGoRightMovement:
	walk_left
	step_end

TeamRocketBaseB2F_Johto_RocketBaseExecutiveFHoldItText:
	.string "Hold it right\n"
	.string "there!$"

TeamRocketBaseB2F_Johto_RocketBaseBossFThrashText:
	.string "We can't have a\n"
	.string "brat like you on\l"
	.string "the loose."
	.string "\pIt's harmful to\n"
	.string "TEAM ROCKET's\l"
	.string "pride, you see."
	.string "\pHowever strong you\n"
	.string "may be, you can't"
	.string "\ptake both of us at\n"
	.string "the same time."
	.string "\pSorry, baby. Now\n"
	.string "get ready to be\l"
	.string "thrashed.$"

TeamRocketBaseB2F_Johto_RocketBaseLanceShareFunText:
	.string "Hey! Don't be so\n"
	.string "selfish. Spread\l"
	.string "the fun around.$"

TeamRocketBaseB2F_Johto_RocketBaseBossDontMeddleText:
	.string "What? You had an\n"
	.string "accomplice?"
	.string "\pWhere is your\n"
	.string "sense of honor?"
	.string "\pAs the interim\n"
	.string "boss in place of"
	.string "\pGIOVANNI, I'll\n"
	.string "show you how wrong"
	.string "\pit is to meddle\n"
	.string "with TEAM ROCKET!$"

TeamRocketBaseB2F_Johto_RocketBaseBossWinText:
	.string "Tch, you really\n"
	.string "are strong."
	.string "\pIt's too bad."
	.string "\pIf you were to\n"
	.string "join TEAM ROCKET,"
	.string "\pyou could become\n"
	.string "an EXECUTIVE.$"

TeamRocketBaseB2F_Johto_RocketBaseBossRetreatText:
	.string "…This hideout is\n"
	.string "done for…"
	.string "\pBut that's fine.\n"
	.string "The broadcast ex-\l"
	.string "periment was a\l"
	.string "total success."
	.string "\pIt doesn't matter\n"
	.string "what happens to\l"
	.string "this hideout now."
	.string "\pWe have much big-\n"
	.string "ger plans."
	.string "\pYou'll come to\n"
	.string "appreciate TEAM"
	.string "\pROCKET's true\n"
	.string "power soon enough."
	.string "\pEnjoy yourself\n"
	.string "while you can…"
	.string "\pFufufufu…$"

TeamRocketBaseB2F_Johto_RocketBaseLancePostBattleText:
	.string "LANCE: That did\n"
	.string "it. We defeated"
	.string "\pall the ROCKETS\n"
	.string "here."
	.string "\pBut I'm concerned\n"
	.string "about the young"
	.string "\pguy I battled in\n"
	.string "the process…$"

TeamRocketBaseB2F_Johto_RocketBaseLancePowerOffText:
	.string "Sorry, {PLAYER}.\n"
	.string "I saw how well you"
	.string "\pwere doing, so I\n"
	.string "just hung back."
	.string "\pNow all there is\n"
	.string "left to do is to"
	.string "\pturn off that odd\n"
	.string "radio signal.$"

TeamRocketBaseB2F_Johto_RockerBaseLanceElectrodeFaintText:
	.string "It's this machine\n"
	.string "that's causing all\l"
	.string "the problems."
	.string "\pI don't see a\n"
	.string "switch on it…"
	.string "\pWe have no choice.\n"
	.string "We have to make"
	.string "\pall the ELECTRODE\n"
	.string "faint."
	.string "\pThat should stop\n"
	.string "this machine from"
	.string "\ptransmitting that\n"
	.string "strange signal."
	.string "\pIt's no fault of\n"
	.string "the POKéMON, so it"
	.string "\pmakes me feel\n"
	.string "guilty."
	.string "\p{PLAYER}, let's\n"
	.string "split the job.$"

TeamRocketBaseB2F_Johto_RocketBaseLancesSideText:
	.string "LANCE: Leave this\n"
	.string "side to me.$"

TeamRocketBaseB2F_Johto_LanceHealsText1:
	.string "LANCE: Are you all\n"
	.string "right?"
	.string "\pYour POKéMON are\n"
	.string "hurt and tired."
	.string "\pHere, give them\n"
	.string "some of my medi-\l"
	.string "cine.$"

TeamRocketBaseB2F_Johto_LanceHealsText2:
	.string "LANCE: {PLAYER},\n"
	.string "let's give it our\l"
	.string "best for POKéMON.$"

TeamRocketBaseB2F_Johto_GruntM17SeenText:
	.string "The door won't\n"
	.string "open?"
	.string "\pWell, duh.\n"
	.string "It has to have a"
	.string "\ppassword that only\n"
	.string "TEAM ROCKET knows.$"

TeamRocketBaseB2F_Johto_GruntM17BeatenText:
	.string "What? I lost?$"

TeamRocketBaseB2F_Johto_GruntM17AfterBattleText:
	.string "Heh, I'm just a\n"
	.string "GRUNT."
	.string "\pI don't know the\n"
	.string "password. Too bad\l"
	.string "for you.$"

TeamRocketBaseB2F_Johto_GruntM18SeenText:
	.string "Oh, a kid? I don't\n"
	.string "really like this,"
	.string "\pbut eliminate you\n"
	.string "I must.$"

TeamRocketBaseB2F_Johto_GruntM18BeatenText:
	.string "I knew I'd lose…$"

TeamRocketBaseB2F_Johto_GruntM18AfterBattleText:
	.string "I got wiped out on\n"
	.string "the last mission\l"
	.string "by a kid too."
	.string "\pWhen we were ab-\n"
	.string "ducting POKéMON,"
	.string "\pthis kid with long\n"
	.string "red hair and mean-"
	.string "\plooking eyes just\n"
	.string "creamed me…$"

TeamRocketBaseB2F_Johto_GruntM19SeenText:
	.string "You rotten little\n"
	.string "pest!$"

TeamRocketBaseB2F_Johto_GruntM19BeatenText:
	.string "Grrrr…$"

TeamRocketBaseB2F_Johto_GruntM19AfterBattleText:
	.string "Heh, only the boss\n"
	.string "knows the password\l"
	.string "for that door."
	.string "\pWhere's the boss?\n"
	.string "Who knows? Go look\l"
	.string "for yourself.$"

TeamRocketBaseB2F_Johto_RocketBaseB2FTransmitterText:
	.string "It's the radio\n"
	.string "transmitter that's"
	.string "\psending the\n"
	.string "sinister signal."
	.string "\pIt's working at\n"
	.string "full capacity.$"

TeamRocketBaseB2F_Johto_RocketBaseB2FDeactivateTransmitterText:
	.string "The radio trans-\n"
	.string "mitter has finally"
	.string "\pstopped its evil\n"
	.string "broadcast.$"
