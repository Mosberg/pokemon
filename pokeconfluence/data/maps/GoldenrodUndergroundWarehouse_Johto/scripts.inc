GoldenrodUndergroundWarehouse_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodUndergroundWarehouse_Johto_OnTransition
	.byte 0

GoldenrodUndergroundWarehouse_Johto_OnTransition:
	call GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseResetSwitchesCallback_Cb
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseDirectorScript_Entry::
	lockall
	goto GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseDirectorScript

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseMaxEther_Entry::
	lockall
	goto GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseMaxEther

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseTMSleepTalk_Entry::
	lockall
	goto GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseTMSleepTalk

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseUltraBall_Entry::
	lockall
	goto GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseUltraBall


GoldenrodUndergroundWarehouse_Johto_TrainerGruntM24::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_24, GoldenrodUndergroundWarehouse_Johto_GruntM24SeenText, GoldenrodUndergroundWarehouse_Johto_GruntM24BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_24
	lock
	faceplayer
	goto GoldenrodUndergroundWarehouse_Johto_TrainerGruntM24_Script

GoldenrodUndergroundWarehouse_Johto_TrainerGruntM24_Script:
	message GoldenrodUndergroundWarehouse_Johto_GruntM24AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_TrainerGruntM14::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_14, GoldenrodUndergroundWarehouse_Johto_GruntM14SeenText, GoldenrodUndergroundWarehouse_Johto_GruntM14BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_14
	lock
	faceplayer
	goto GoldenrodUndergroundWarehouse_Johto_TrainerGruntM14_Script

GoldenrodUndergroundWarehouse_Johto_TrainerGruntM14_Script:
	message GoldenrodUndergroundWarehouse_Johto_GruntM14AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_TrainerGruntM15::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_15, GoldenrodUndergroundWarehouse_Johto_GruntM15SeenText, GoldenrodUndergroundWarehouse_Johto_GruntM15BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_15
	lock
	faceplayer
	goto GoldenrodUndergroundWarehouse_Johto_TrainerGruntM15_Script

GoldenrodUndergroundWarehouse_Johto_TrainerGruntM15_Script:
	message GoldenrodUndergroundWarehouse_Johto_GruntM15AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseDirectorScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RECEIVED_CARD_KEY, GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseDirectorScript_GotCardKey
	message GoldenrodUndergroundWarehouse_Johto_DirectorIntroText
	waitmessage
	waitbuttonpress
	giveitem ITEM_CARD_KEY
	setflag FLAG_JOHTO_RECEIVED_CARD_KEY
	setflag FLAG_JOHTO_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1
	clearflag FLAG_JOHTO_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2
	clearflag FLAG_JOHTO_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3
	message GoldenrodUndergroundWarehouse_Johto_DirectorCardKeyText
	waitmessage
	waitbuttonpress

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseDirectorScript_GotCardKey:
	message GoldenrodUndergroundWarehouse_Johto_DirectorAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseMaxEther:
	finditem ITEM_MAX_ETHER
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseTMSleepTalk:
	finditem ITEM_TM_CALM_MIND
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

GoldenrodUndergroundWarehouse_Johto_GoldenrodUndergroundWarehouseResetSwitchesCallback_Cb:
	clearflag FLAG_JOHTO_SWITCH_1
	clearflag FLAG_JOHTO_SWITCH_2
	clearflag FLAG_JOHTO_SWITCH_3
	clearflag FLAG_JOHTO_EMERGENCY_SWITCH
	clearflag FLAG_JOHTO_DOOR_1_OPEN
	clearflag FLAG_JOHTO_DOOR_2_OPEN
	clearflag FLAG_JOHTO_DOOR_3_OPEN
	clearflag FLAG_JOHTO_DOOR_4_OPEN
	clearflag FLAG_JOHTO_DOOR_5_OPEN
	clearflag FLAG_JOHTO_DOOR_6_OPEN
	clearflag FLAG_JOHTO_DOOR_7_OPEN
	clearflag FLAG_JOHTO_DOOR_8_OPEN
	clearflag FLAG_JOHTO_DOOR_9_OPEN
	clearflag FLAG_JOHTO_DOOR_10_OPEN
	clearflag FLAG_JOHTO_DOOR_11_OPEN
	setvar VAR_RESULT, 0
	copyvar VAR_JOHTO_MEM_WUNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	return

GoldenrodUndergroundWarehouse_Johto_GruntM24SeenText:
	.string "How did you get\n"
	.string "this far?"
	.string "\pI guess it can't\n"
	.string "be helped. I'll\l"
	.string "dispose of you.$"

GoldenrodUndergroundWarehouse_Johto_GruntM24BeatenText:
	.string "I got disposed of…$"

GoldenrodUndergroundWarehouse_Johto_GruntM24AfterBattleText:
	.string "TEAM ROCKET will\n"
	.string "keep going, wait-\l"
	.string "ing for the return\l"
	.string "of GIOVANNI."
	.string "\pWe'll do whatever\n"
	.string "it takes.$"

GoldenrodUndergroundWarehouse_Johto_GruntM14SeenText:
	.string "You're not going\n"
	.string "any farther!"
	.string "\pI don't show mercy\n"
	.string "to my enemies, not\l"
	.string "even brats!$"

GoldenrodUndergroundWarehouse_Johto_GruntM14BeatenText:
	.string "Blast it!$"

GoldenrodUndergroundWarehouse_Johto_GruntM14AfterBattleText:
	.string "I lost…"
	.string "\pPlease forgive me,\n"
	.string "GIOVANNI!$"

GoldenrodUndergroundWarehouse_Johto_GruntM15SeenText:
	.string "Hyuck-hyuck-hyuck!\n"
	.string "I remember you!"
	.string "\pYou got me good\n"
	.string "at our hideout!$"

GoldenrodUndergroundWarehouse_Johto_GruntM15BeatenText:
	.string "Hyuck-hyuck-hyuck!\n"
	.string "So, that's how?$"

GoldenrodUndergroundWarehouse_Johto_GruntM15AfterBattleText:
	.string "Hyuck-hyuck-hyuck!\n"
	.string "That was a blast!\l"
	.string "I'll remember you!$"

GoldenrodUndergroundWarehouse_Johto_DirectorIntroText:
	.string "DIRECTOR: Who?\n"
	.string "What? You came to\l"
	.string "rescue me?"
	.string "\pThank you!"
	.string "\pThe RADIO TOWER!"
	.string "\pWhat's happening\n"
	.string "there?"
	.string "\pTaken over by TEAM\n"
	.string "ROCKET?"
	.string "\pHere. Take this\n"
	.string "CARD KEY.$"

GoldenrodUndergroundWarehouse_Johto_DirectorCardKeyText:
	.string "DIRECTOR: Use that\n"
	.string "to open the shut-\l"
	.string "ters on 3F.$"

GoldenrodUndergroundWarehouse_Johto_DirectorAfterText:
	.string "I'm begging you to\n"
	.string "help."
	.string "\pThere's no telling\n"
	.string "what they'll do if"
	.string "\pthey control the\n"
	.string "transmitter."
	.string "\pThey may even be\n"
	.string "able to control"
	.string "\pPOKéMON using a\n"
	.string "special signal!"
	.string "\pYou're the only\n"
	.string "one I can call on."
	.string "\pPlease save the\n"
	.string "RADIO TOWER…"
	.string "\pAnd all the POKé-\n"
	.string "MON nationwide!$"
