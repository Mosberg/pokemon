VioletGym_Johto_MapScripts::
	.byte 0

VioletGym_Johto_VioletGymFalknerScript_Entry::
	lockall
	goto VioletGym_Johto_VioletGymFalknerScript

VioletGym_Johto_VioletGymGuideScript_Entry::
	lockall
	goto VioletGym_Johto_VioletGymGuideScript

VioletGym_Johto_VioletGymStatue_Entry::
	lockall
	goto VioletGym_Johto_VioletGymStatue


VioletGym_Johto_VioletGymFalknerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_FALKNER, VioletGym_Johto_VioletGymFalknerScript_FightDone
	message VioletGym_Johto_FalknerIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_FALKNER_FALKNER1, VioletGym_Johto_FalknerWinLossText
	setflag FLAG_JOHTO_BEAT_FALKNER
	message VioletGym_Johto_ReceivedZephyrBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_ZEPHYRBADGE
	special JohtoCountBadges
	call VioletGym_Johto_VioletGymActivateRockets_Sub

VioletGym_Johto_VioletGymFalknerScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM31_MUD_SLAP, VioletGym_Johto_VioletGymFalknerScript_SpeechAfterTM
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_ROD
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_ABE
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 2
	message VioletGym_Johto_FalknerZephyrBadgeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, 0, VioletGym_Johto_VioletGymFalknerScript_NoRoomForMudSlap
	setflag FLAG_JOHTO_GOT_TM31_MUD_SLAP
	message VioletGym_Johto_FalknerTMMudSlapText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletGym_Johto_VioletGymFalknerScript_SpeechAfterTM:
	message VioletGym_Johto_FalknerFightDoneText
	waitmessage
	waitbuttonpress

VioletGym_Johto_VioletGymFalknerScript_NoRoomForMudSlap:
	closemessage
	releaseall
	end

VioletGym_Johto_TrainerBirdKeeperRod::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_ROD, VioletGym_Johto_BirdKeeperRodSeenText, VioletGym_Johto_BirdKeeperRodBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_ROD
	lock
	faceplayer
	goto VioletGym_Johto_TrainerBirdKeeperRod_Script

VioletGym_Johto_TrainerBirdKeeperRod_Script:
	message VioletGym_Johto_BirdKeeperRodAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletGym_Johto_TrainerBirdKeeperAbe::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_ABE, VioletGym_Johto_BirdKeeperAbeSeenText, VioletGym_Johto_BirdKeeperAbeBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_ABE
	lock
	faceplayer
	goto VioletGym_Johto_TrainerBirdKeeperAbe_Script

VioletGym_Johto_TrainerBirdKeeperAbe_Script:
	message VioletGym_Johto_BirdKeeperAbeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletGym_Johto_VioletGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_FALKNER, VioletGym_Johto_VioletGymGuideScript_VioletGymGuideWinScript
	message VioletGym_Johto_VioletGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletGym_Johto_VioletGymGuideScript_VioletGymGuideWinScript:
	message VioletGym_Johto_VioletGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletGym_Johto_VioletGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_ZEPHYRBADGE, VioletGym_Johto_VioletGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

VioletGym_Johto_VioletGymStatue_Beaten:
	buffertrainername STR_VAR_2, TRAINER_JOHTO_FALKNER_FALKNER1
	goto Johto_Std_GymStatue2Script

VioletGym_Johto_VioletGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, VioletGym_Johto_VioletGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, VioletGym_Johto_VioletGymActivateRockets_GoldenrodRockets_Sub
	return

VioletGym_Johto_VioletGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

VioletGym_Johto_VioletGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

VioletGym_Johto_FalknerIntroText:
	.string "I'm FALKNER, the\n"
	.string "VIOLET POKéMON GYM\l"
	.string "leader!"
	.string "\pPeople say you can\n"
	.string "clip flying-type"
	.string "\pPOKéMON's wings\n"
	.string "with a jolt of\l"
	.string "electricity…"
	.string "\pI won't allow such\n"
	.string "insults to bird\l"
	.string "POKéMON!"
	.string "\pI'll show you the\n"
	.string "real power of the"
	.string "\pmagnificent bird\n"
	.string "POKéMON!$"

VioletGym_Johto_FalknerWinLossText:
	.string "…Darn! My dad's\n"
	.string "cherished bird\l"
	.string "POKéMON…"
	.string "\pAll right.\n"
	.string "Take this."
	.string "\pIt's the official\n"
	.string "POKéMON LEAGUE\l"
	.string "ZEPHYRBADGE.$"

VioletGym_Johto_ReceivedZephyrBadgeText:
	.string "{PLAYER} received\n"
	.string "ZEPHYRBADGE.$"

VioletGym_Johto_FalknerZephyrBadgeText:
	.string "ZEPHYRBADGE\n"
	.string "raises the attack\l"
	.string "power of POKéMON."
	.string "\pIt also enables\n"
	.string "POKéMON to use"
	.string "\pFLASH, if they\n"
	.string "have it, anytime."
	.string "\pHere--take this\n"
	.string "too.$"

VioletGym_Johto_FalknerTMMudSlapText:
	.string "By using a TM, a\n"
	.string "POKéMON will"
	.string "\pinstantly learn a\n"
	.string "new move."
	.string "\pThink before you\n"
	.string "act--a TM can be\l"
	.string "used only once."
	.string "\pTM31 contains\n"
	.string "MUD-SLAP."
	.string "\pIt reduces the\n"
	.string "enemy's accuracy"
	.string "\pwhile it causes\n"
	.string "damage."
	.string "\pIn other words, it\n"
	.string "is both defensive\l"
	.string "and offensive.$"

VioletGym_Johto_FalknerFightDoneText:
	.string "There are POKéMON\n"
	.string "GYMS in cities and\l"
	.string "towns ahead."
	.string "\pYou should test\n"
	.string "your skills at\l"
	.string "these GYMS."
	.string "\pI'm going to train\n"
	.string "harder to become"
	.string "\pthe greatest bird\n"
	.string "master!$"

VioletGym_Johto_BirdKeeperRodSeenText:
	.string "The keyword is\n"
	.string "guts!"
	.string "\pThose here are\n"
	.string "training night and"
	.string "\pday to become bird\n"
	.string "POKéMON masters."
	.string "\pCome on!$"

VioletGym_Johto_BirdKeeperRodBeatenText:
	.string "Gaaah!$"

VioletGym_Johto_BirdKeeperRodAfterBattleText:
	.string "FALKNER's skills\n"
	.string "are for real!"
	.string "\pDon't get cocky\n"
	.string "just because you\l"
	.string "beat me!$"

VioletGym_Johto_BirdKeeperAbeSeenText:
	.string "Let me see if you\n"
	.string "are good enough to\l"
	.string "face FALKNER!$"

VioletGym_Johto_BirdKeeperAbeBeatenText:
	.string "This can't be\n"
	.string "true!$"

VioletGym_Johto_BirdKeeperAbeAfterBattleText:
	.string "This is pathetic,\n"
	.string "losing to some\l"
	.string "rookie trainer…$"

VioletGym_Johto_VioletGymGuideText:
	.string "Hey! I'm no train-\n"
	.string "er but I can give\l"
	.string "some advice!"
	.string "\pBelieve me!\n"
	.string "If you believe, a"
	.string "\pchampionship dream\n"
	.string "can come true."
	.string "\pYou believe?\n"
	.string "Then listen."
	.string "\pThe grass-type is\n"
	.string "weak against the"
	.string "\pflying-type. Keep\n"
	.string "this in mind.$"

VioletGym_Johto_VioletGymGuideWinText:
	.string "Nice battle! Keep\n"
	.string "it up, and you'll"
	.string "\pbe the CHAMP in no\n"
	.string "time at all!$"
