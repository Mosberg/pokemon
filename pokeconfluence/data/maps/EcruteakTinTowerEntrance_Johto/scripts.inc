EcruteakTinTowerEntrance_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakTinTowerEntrance_Johto_OnTransition
	.byte 0

EcruteakTinTowerEntrance_Johto_OnTransition:
	call EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_Cb
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_Entry::
	lockall
	goto EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageScript_Entry::
	lockall
	goto EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageScript

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceGrampsScript_Entry::
	lockall
	goto EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceGrampsScript

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksLeft_Entry::
	lockall
	goto EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksLeft

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksRight_Entry::
	lockall
	goto EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksRight


EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksLeft:
	goto_if_set FLAG_JOHTO_RANG_CLEAR_BELL_2, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceAlreadyBlocked
	applymovement 2, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksLeftMovement
	waitmovement 2
	setobjectxyperm 1, 4, 6
	clearflag FLAG_JOHTO_RANG_CLEAR_BELL_1
	addobject 1
	delay 5
	removeobject 2
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksRight:
	goto_if_set FLAG_JOHTO_RANG_CLEAR_BELL_1, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceAlreadyBlocked
	applymovement 1, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksRightMovement
	waitmovement 1
	setobjectxyperm 2, 5, 6
	clearflag FLAG_JOHTO_RANG_CLEAR_BELL_2
	addobject 2
	delay 5
	removeobject 1
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceAlreadyBlocked:
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_CheckForClearBell
	goto_if_set FLAG_JOHTO_ENGINE_FOGBADGE, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_BlockPassage_GotFogBadge
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_BlockPassage_GotFogBadge:
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_GotFogBadge
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_CheckForClearBell:
	goto_if_set FLAG_JOHTO_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_AllowedThrough
	goto_if_set FLAG_TEMP_11, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_RangClearBell
	checkitem ITEM_CLEAR_BELL, 1
	goto_if_ne VAR_RESULT, 0, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_GotClearBell
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_NoClearBell
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_GotClearBell:
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_HearsClearBell
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 1
	setflag FLAG_JOHTO_RANG_CLEAR_BELL_2
	clearflag FLAG_JOHTO_RANG_CLEAR_BELL_1
	setflag FLAG_TEMP_11
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_AllowedThrough:
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_PleaseDoGoOn
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageScript_RangClearBell:
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_HeardClearBell
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_CLEAR_BELL, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageScript_GotClearBell
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageScript_GotClearBell:
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageText_GotClearBell
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceGrampsScript:
	faceplayer
	message EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_Cb:
	goto_if_set FLAG_JOHTO_FOUGHT_SUICUNE, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower_Cb
	goto_if_set FLAG_JOHTO_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower_Cb
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_BlockTower_Cb
	return

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_BlockTower_Cb:
	clearflag FLAG_JOHTO_RANG_CLEAR_BELL_1
	setflag FLAG_JOHTO_RANG_CLEAR_BELL_2
	setflag FLAG_JOHTO_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE
	checkitem ITEM_CLEAR_BELL, 1
	goto_if_ne VAR_RESULT, 0, EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_NoClearBell_Cb
	setvar VAR_JOHTO_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 0

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_NoClearBell_Cb:
	return

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower_Cb:
	clearflag FLAG_JOHTO_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE
	return

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksLeftMovement:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_down
	step_end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageBlocksRightMovement:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	face_down
	step_end

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText:
	.string "TIN TOWER is off\n"
	.string "limits to anyone"
	.string "\pwithout ECRUTEAK\n"
	.string "GYM's BADGE."
	.string "\pSorry, but you'll\n"
	.string "have to leave.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_GotFogBadge:
	.string "TIN TOWER is off\n"
	.string "limits to anyone"
	.string "\pwithout ECRUTEAK\n"
	.string "GYM's BADGE."
	.string "\pAh!"
	.string "\pECRUTEAK's GYM\n"
	.string "BADGE! Please, go\l"
	.string "right through.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_NoClearBell:
	.string "A momentous event\n"
	.string "has occurred."
	.string "\pI beg your pardon,\n"
	.string "but I must ask you\l"
	.string "to leave."
	.string "\p…What soothes the\n"
	.string "soul…"
	.string "\pThe WISE TRIO say\n"
	.string "things that are so"
	.string "\pvery difficult to\n"
	.string "understand…$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_HearsClearBell:
	.string "A momentous event\n"
	.string "has occurred."
	.string "\pI beg your pardon,\n"
	.string "but I must ask you\l"
	.string "to leave."
	.string "\p<……><……><……>"
	.string "\pAh!"
	.string "\pThe sound of that\n"
	.string "CLEAR BELL!"
	.string "\pIt… It's sublime!"
	.string "\pI've never heard\n"
	.string "so beautiful a\l"
	.string "sound before!"
	.string "\pThat bell's chime\n"
	.string "is indicative of\l"
	.string "the bearer's soul."
	.string "\pYou…"
	.string "\pYou may be able to\n"
	.string "make it through\l"
	.string "TIN TOWER."
	.string "\pPlease, do go on.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_PleaseDoGoOn:
	.string "Please, do go on.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceSageText_HeardClearBell:
	.string "That bell's chime\n"
	.string "is indicative of\l"
	.string "the bearer's soul."
	.string "\pYou…"
	.string "\pYou may be able to\n"
	.string "make it through\l"
	.string "TIN TOWER."
	.string "\pPlease, do go on.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageText:
	.string "The TIN TOWER\n"
	.string "ahead is a nine-"
	.string "\ptier tower of\n"
	.string "divine beauty."
	.string "\pIt soothes the\n"
	.string "soul of all who\l"
	.string "see it.$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceWanderingSageText_GotClearBell:
	.string "The TIN TOWER\n"
	.string "shook! A POKéMON"
	.string "\pmust have returned\n"
	.string "to the top!$"

EcruteakTinTowerEntrance_Johto_EcruteakTinTowerEntranceGrampsText:
	.string "Two towers…\n"
	.string "Two POKéMON…"
	.string "\pBut when one\n"
	.string "burned down, both"
	.string "\pPOKéMON flew away,\n"
	.string "never to return.$"
