OlivineGym_Johto_MapScripts::
	.byte 0

OlivineGym_Johto_OlivineGymJasmineScript_Entry::
	lockall
	goto OlivineGym_Johto_OlivineGymJasmineScript

OlivineGym_Johto_OlivineGymGuideScript_Entry::
	lockall
	goto OlivineGym_Johto_OlivineGymGuideScript

OlivineGym_Johto_OlivineGymStatue_Entry::
	lockall
	goto OlivineGym_Johto_OlivineGymStatue


OlivineGym_Johto_OlivineGymJasmineScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_JASMINE, OlivineGym_Johto_OlivineGymJasmineScript_FightDone
	message OlivineGym_Johto_Jasmine_SteelTypeIntro
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_JASMINE_JASMINE1, OlivineGym_Johto_Jasmine_BetterTrainer
	setflag FLAG_JOHTO_BEAT_JASMINE
	message OlivineGym_Johto_Text_ReceivedMineralBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_MINERALBADGE
	special JohtoCountBadges
	call OlivineGym_Johto_OlivineGymActivateRockets_Sub

OlivineGym_Johto_OlivineGymJasmineScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM23_IRON_TAIL, OlivineGym_Johto_OlivineGymJasmineScript_GotIronTail
	message OlivineGym_Johto_Jasmine_BadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_IRON_TAIL
	goto_if_eq VAR_RESULT, 0, OlivineGym_Johto_OlivineGymJasmineScript_NoRoomForIronTail
	setflag FLAG_JOHTO_GOT_TM23_IRON_TAIL
	message OlivineGym_Johto_Jasmine_IronTailSpeech
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGym_Johto_OlivineGymJasmineScript_GotIronTail:
	message OlivineGym_Johto_Jasmine_GoodLuck
	waitmessage
	waitbuttonpress

OlivineGym_Johto_OlivineGymJasmineScript_NoRoomForIronTail:
	closemessage
	releaseall
	end

OlivineGym_Johto_OlivineGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_JASMINE, OlivineGym_Johto_OlivineGymGuideScript_OlivineGymGuideWinScript
	goto_if_unset FLAG_JOHTO_JASMINE_RETURNED_TO_GYM, OlivineGym_Johto_OlivineGymGuideScript_OlivineGymGuidePreScript
	message OlivineGym_Johto_OlivineGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGym_Johto_OlivineGymGuideScript_OlivineGymGuideWinScript:
	message OlivineGym_Johto_OlivineGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGym_Johto_OlivineGymGuideScript_OlivineGymGuidePreScript:
	message OlivineGym_Johto_OlivineGymGuidePreText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineGym_Johto_OlivineGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_MINERALBADGE, OlivineGym_Johto_OlivineGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

OlivineGym_Johto_OlivineGymStatue_Beaten:
	buffertrainername STR_VAR_2, TRAINER_JOHTO_JASMINE_JASMINE1
	goto Johto_Std_GymStatue2Script

OlivineGym_Johto_OlivineGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, OlivineGym_Johto_OlivineGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, OlivineGym_Johto_OlivineGymActivateRockets_GoldenrodRockets_Sub
	return

OlivineGym_Johto_OlivineGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

OlivineGym_Johto_OlivineGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

OlivineGym_Johto_Jasmine_SteelTypeIntro:
	.string "…Thank you for\n"
	.string "your help at the\l"
	.string "LIGHTHOUSE…"
	.string "\pBut this is dif-\n"
	.string "ferent. Please"
	.string "\pallow me to intro-\n"
	.string "duce myself."
	.string "\pI am JASMINE, a\n"
	.string "GYM LEADER. I use\l"
	.string "the steel-type."
	.string "\p…Do you know about\n"
	.string "the steel-type?"
	.string "\pIt's a type that\n"
	.string "was only recently\l"
	.string "discovered."
	.string "\p…Um… May I begin?$"

OlivineGym_Johto_Jasmine_BetterTrainer:
	.string "…You are a better\n"
	.string "trainer than me,"
	.string "\pin both skill and\n"
	.string "kindness."
	.string "\pIn accordance with\n"
	.string "LEAGUE rules, I"
	.string "\pconfer upon you\n"
	.string "this BADGE.$"

OlivineGym_Johto_Text_ReceivedMineralBadge:
	.string "{PLAYER} received\n"
	.string "MINERALBADGE.$"

OlivineGym_Johto_Jasmine_BadgeSpeech:
	.string "MINERALBADGE\n"
	.string "raises POKéMON's\l"
	.string "DEFENSE."
	.string "\p…Um… Please take\n"
	.string "this too…$"

OlivineGym_Johto_Jasmine_IronTailSpeech:
	.string "…You could use\n"
	.string "that TM to teach\l"
	.string "IRON TAIL.$"

OlivineGym_Johto_Jasmine_GoodLuck:
	.string "Um… I don't know\n"
	.string "how to say this,\l"
	.string "but good luck…$"

OlivineGym_Johto_OlivineGymGuideText:
	.string "JASMINE uses the\n"
	.string "newly discovered\l"
	.string "steel-type."
	.string "\pI don't know very\n"
	.string "much about it.$"

OlivineGym_Johto_OlivineGymGuideWinText:
	.string "That was awesome."
	.string "\pThe steel-type,\n"
	.string "huh?"
	.string "\pThat was a close\n"
	.string "encounter of an\l"
	.string "unknown kind!$"

OlivineGym_Johto_OlivineGymGuidePreText:
	.string "JASMINE, the GYM\n"
	.string "LEADER, is at the\l"
	.string "LIGHTHOUSE."
	.string "\pShe's been tending\n"
	.string "to a sick POKéMON."
	.string "\pA strong trainer\n"
	.string "has to be compas-\l"
	.string "sionate.$"
