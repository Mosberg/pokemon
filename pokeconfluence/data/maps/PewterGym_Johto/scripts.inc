PewterGym_Johto_MapScripts::
	.byte 0

PewterGym_Johto_PewterGymBrockScript_Entry::
	lockall
	goto PewterGym_Johto_PewterGymBrockScript

PewterGym_Johto_PewterGymGuideScript_Entry::
	lockall
	goto PewterGym_Johto_PewterGymGuideScript

PewterGym_Johto_PewterGymStatue_Entry::
	lockall
	goto PewterGym_Johto_PewterGymStatue


PewterGym_Johto_PewterGymBrockScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_BOULDERBADGE, PewterGym_Johto_PewterGymBrockScript_FightDone
	message PewterGym_Johto_BrockIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_BROCK_BROCK1, PewterGym_Johto_BrockWinLossText
	setflag FLAG_JOHTO_BEAT_BROCK
	setflag FLAG_JOHTO_BEAT_CAMPER_JERRY
	message PewterGym_Johto_ReceivedBoulderBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_BOULDERBADGE
	message PewterGym_Johto_BrockBoulderBadgeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterGym_Johto_PewterGymBrockScript_FightDone:
	message PewterGym_Johto_BrockFightDoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterGym_Johto_TrainerCamperJerry::
	trainerbattle_single TRAINER_JOHTO_CAMPER_JERRY, PewterGym_Johto_CamperJerrySeenText, PewterGym_Johto_CamperJerryBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_JERRY
	lock
	faceplayer
	goto PewterGym_Johto_TrainerCamperJerry_Script

PewterGym_Johto_TrainerCamperJerry_Script:
	message PewterGym_Johto_CamperJerryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterGym_Johto_PewterGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_BROCK, PewterGym_Johto_PewterGymGuideScript_PewterGymGuideWinScript
	message PewterGym_Johto_PewterGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterGym_Johto_PewterGymGuideScript_PewterGymGuideWinScript:
	message PewterGym_Johto_PewterGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterGym_Johto_PewterGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_BOULDERBADGE, PewterGym_Johto_PewterGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

PewterGym_Johto_PewterGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

PewterGym_Johto_BrockIntroText:
	.string "BROCK: Wow, it's\n"
	.string "not often that we"
	.string "\pget a challenger\n"
	.string "from JOHTO."
	.string "\pI'm BROCK, the\n"
	.string "PEWTER GYM LEADER."
	.string "\pI'm an expert on\n"
	.string "rock-type POKéMON."
	.string "\pMy POKéMON are im-\n"
	.string "pervious to most"
	.string "\pphysical attacks.\n"
	.string "You'll have a hard"
	.string "\ptime inflicting\n"
	.string "any damage."
	.string "\pCome on!$"

PewterGym_Johto_BrockWinLossText:
	.string "BROCK: Your POKé-\n"
	.string "MON's powerful at-\l"
	.string "tacks overcame my\l"
	.string "rock-hard defense…"
	.string "\pYou're stronger\n"
	.string "than I expected…"
	.string "\pGo ahead--take\n"
	.string "this BADGE.$"

PewterGym_Johto_ReceivedBoulderBadgeText:
	.string "{PLAYER} received\n"
	.string "BOULDERBADGE.$"

PewterGym_Johto_BrockBoulderBadgeText:
	.string "BROCK: {PLAYER},\n"
	.string "thanks. I enjoyed"
	.string "\pbattling you, even\n"
	.string "though I am a bit\l"
	.string "upset."
	.string "\pThat BOULDERBADGE\n"
	.string "will make your"
	.string "\pPOKéMON even more\n"
	.string "powerful.$"

PewterGym_Johto_BrockFightDoneText:
	.string "BROCK: The world\n"
	.string "is huge. There are"
	.string "\pstill many strong\n"
	.string "trainers like you."
	.string "\pJust wait and see.\n"
	.string "I'm going to be-\l"
	.string "come a lot strong-\l"
	.string "er too.$"

PewterGym_Johto_CamperJerrySeenText:
	.string "The trainers of\n"
	.string "this GYM use rock-\l"
	.string "type POKéMON."
	.string "\pThe rock-type has\n"
	.string "high DEFENSE."
	.string "\pBattles could end\n"
	.string "up going a long"
	.string "\ptime. Are you\n"
	.string "ready for this?$"

PewterGym_Johto_CamperJerryBeatenText:
	.string "I have to win\n"
	.string "these battles…$"

PewterGym_Johto_CamperJerryAfterBattleText:
	.string "Hey, you! Trainer\n"
	.string "from JOHTO! BROCK"
	.string "\pis tough. He'll\n"
	.string "punish you if you"
	.string "\pdon't take him\n"
	.string "seriously.$"

PewterGym_Johto_PewterGymGuideText:
	.string "Yo! CHAMP in\n"
	.string "making! You're"
	.string "\preally rocking.\n"
	.string "Are you battling"
	.string "\pthe GYM LEADERS of\n"
	.string "KANTO?"
	.string "\pThey're strong and\n"
	.string "dedicated people,"
	.string "\pjust like JOHTO's\n"
	.string "GYM LEADERS.$"

PewterGym_Johto_PewterGymGuideWinText:
	.string "Yo! CHAMP in\n"
	.string "making! That GYM"
	.string "\pdidn't give you\n"
	.string "much trouble."
	.string "\pThe way you took\n"
	.string "charge was really"
	.string "\pinspiring. I mean\n"
	.string "that seriously.$"
