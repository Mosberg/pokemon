AzaleaGym_Johto_MapScripts::
	.byte 0

AzaleaGym_Johto_AzaleaGymBugsyScript_Entry::
	lockall
	goto AzaleaGym_Johto_AzaleaGymBugsyScript

AzaleaGym_Johto_AzaleaGymGuideScript_Entry::
	lockall
	goto AzaleaGym_Johto_AzaleaGymGuideScript

AzaleaGym_Johto_AzaleaGymStatue_Entry::
	lockall
	goto AzaleaGym_Johto_AzaleaGymStatue


AzaleaGym_Johto_AzaleaGymBugsyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_BUGSY, AzaleaGym_Johto_AzaleaGymBugsyScript_FightDone
	message AzaleaGym_Johto_BugsyText_INeverLose
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_BUGSY_BUGSY1, AzaleaGym_Johto_BugsyText_ResearchIncomplete
	setflag FLAG_JOHTO_BEAT_BUGSY
	message AzaleaGym_Johto_Text_ReceivedHiveBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_HIVEBADGE
	special JohtoCountBadges
	call AzaleaGym_Johto_AzaleaGymActivateRockets_Sub

AzaleaGym_Johto_AzaleaGymBugsyScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM49_FURY_CUTTER, AzaleaGym_Johto_AzaleaGymBugsyScript_GotFuryCutter
	setflag FLAG_JOHTO_BEAT_TWINS_AMY_AND_MAY
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_BENNY
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_AL
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_JOSH
	message AzaleaGym_Johto_BugsyText_HiveBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, AzaleaGym_Johto_AzaleaGymBugsyScript_NoRoomForFuryCutter
	setflag FLAG_JOHTO_GOT_TM49_FURY_CUTTER
	message AzaleaGym_Johto_BugsyText_FuryCutterSpeech
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_AzaleaGymBugsyScript_GotFuryCutter:
	message AzaleaGym_Johto_BugsyText_BugMonsAreDeep
	waitmessage
	waitbuttonpress

AzaleaGym_Johto_AzaleaGymBugsyScript_NoRoomForFuryCutter:
	closemessage
	releaseall
	end

AzaleaGym_Johto_TrainerTwinsAmyandmay1::
	trainerbattle_single TRAINER_JOHTO_TWINS_AMYANDMAY1, AzaleaGym_Johto_TwinsAmyandmay1SeenText, AzaleaGym_Johto_TwinsAmyandmay1BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_AMY_AND_MAY
	lock
	faceplayer
	goto AzaleaGym_Johto_TrainerTwinsAmyandmay1_AfterScript

AzaleaGym_Johto_TrainerTwinsAmyandmay1_AfterScript:
	message AzaleaGym_Johto_TwinsAmyandmay1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_TrainerTwinsAmyandmay2::
	trainerbattle_single TRAINER_JOHTO_TWINS_AMYANDMAY2, AzaleaGym_Johto_TwinsAmyandmay2SeenText, AzaleaGym_Johto_TwinsAmyandmay2BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_AMY_AND_MAY
	lock
	faceplayer
	goto AzaleaGym_Johto_TrainerTwinsAmyandmay2_AfterScript

AzaleaGym_Johto_TrainerTwinsAmyandmay2_AfterScript:
	message AzaleaGym_Johto_TwinsAmyandmay2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_TrainerBugCatcherBenny::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_BUG_CATCHER_BENNY, AzaleaGym_Johto_BugCatcherBennySeenText, AzaleaGym_Johto_BugCatcherBennyBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_BENNY
	lock
	faceplayer
	goto AzaleaGym_Johto_TrainerBugCatcherBenny_AfterScript

AzaleaGym_Johto_TrainerBugCatcherBenny_AfterScript:
	message AzaleaGym_Johto_BugCatcherBennyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_TrainerBugCatcherAl::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_AL, AzaleaGym_Johto_BugCatcherAlSeenText, AzaleaGym_Johto_BugCatcherAlBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_AL
	lock
	faceplayer
	goto AzaleaGym_Johto_TrainerBugCatcherAl_AfterScript

AzaleaGym_Johto_TrainerBugCatcherAl_AfterScript:
	message AzaleaGym_Johto_BugCatcherAlAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_TrainerBugCatcherJosh::
	trainerbattle_single TRAINER_JOHTO_BUG_CATCHER_JOSH, AzaleaGym_Johto_BugCatcherJoshSeenText, AzaleaGym_Johto_BugCatcherJoshBeatenText
	setflag FLAG_JOHTO_BEAT_BUG_CATCHER_JOSH
	lock
	faceplayer
	goto AzaleaGym_Johto_TrainerBugCatcherJosh_AfterScript

AzaleaGym_Johto_TrainerBugCatcherJosh_AfterScript:
	message AzaleaGym_Johto_BugCatcherJoshAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_AzaleaGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_BUGSY, AzaleaGym_Johto_AzaleaGymGuideScript_AzaleaGymGuideWinScript
	message AzaleaGym_Johto_AzaleaGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_AzaleaGymGuideScript_AzaleaGymGuideWinScript:
	message AzaleaGym_Johto_AzaleaGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaGym_Johto_AzaleaGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_HIVEBADGE, AzaleaGym_Johto_AzaleaGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

AzaleaGym_Johto_AzaleaGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

AzaleaGym_Johto_AzaleaGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, AzaleaGym_Johto_AzaleaGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, AzaleaGym_Johto_AzaleaGymActivateRockets_GoldenrodRockets_Sub
	return

AzaleaGym_Johto_AzaleaGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

AzaleaGym_Johto_AzaleaGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

AzaleaGym_Johto_BugsyText_INeverLose:
	.string "I'm BUGSY!\n"
	.string "I never lose when"
	.string "\pit comes to bug\n"
	.string "POKéMON."
	.string "\pMy research is\n"
	.string "going to make me"
	.string "\pthe authority on\n"
	.string "bug POKéMON!"
	.string "\pLet me demonstrate\n"
	.string "what I've learned\l"
	.string "from my studies.$"

AzaleaGym_Johto_BugsyText_ResearchIncomplete:
	.string "Whoa, amazing!\n"
	.string "You're an expert\l"
	.string "on POKéMON!"
	.string "\pMy research isn't\n"
	.string "complete yet."
	.string "\pOK, you win. Take\n"
	.string "this BADGE.$"

AzaleaGym_Johto_Text_ReceivedHiveBadge:
	.string "{PLAYER} received\n"
	.string "HIVEBADGE.$"

AzaleaGym_Johto_BugsyText_HiveBadgeSpeech:
	.string "Do you know the\n"
	.string "benefits of HIVE-\l"
	.string "BADGE?"
	.string "\pIf you have it,\n"
	.string "POKéMON up to L30"
	.string "\pwill obey you,\n"
	.string "even traded ones."
	.string "\pPOKéMON that know\n"
	.string "CUT will be able"
	.string "\pto use it outside\n"
	.string "of battle too."
	.string "\pHere, I also want\n"
	.string "you to have this.$"

AzaleaGym_Johto_BugsyText_FuryCutterSpeech:
	.string "TM49 contains\n"
	.string "FURY CUTTER."
	.string "\pIf you don't miss,\n"
	.string "it gets stronger\l"
	.string "every turn."
	.string "\pThe longer your\n"
	.string "battle goes, the\l"
	.string "better it gets."
	.string "\pIsn't that great?\n"
	.string "I discovered it!$"

AzaleaGym_Johto_BugsyText_BugMonsAreDeep:
	.string "Bug POKéMON are\n"
	.string "deep. There are"
	.string "\pmany mysteries to\n"
	.string "be explored."
	.string "\pStudy your favor-\n"
	.string "ites thoroughly.$"

AzaleaGym_Johto_BugCatcherBennySeenText:
	.string "Bug POKéMON evolve\n"
	.string "young. So they get"
	.string "\pstronger that much\n"
	.string "faster.$"

AzaleaGym_Johto_BugCatcherBennyBeatenText:
	.string "Just evolving\n"
	.string "isn't enough!$"

AzaleaGym_Johto_BugCatcherBennyAfterBattleText:
	.string "POKéMON become\n"
	.string "stronger if they\l"
	.string "evolve. Really!$"

AzaleaGym_Johto_BugCatcherAlSeenText:
	.string "Bug POKéMON are\n"
	.string "cool and tough!"
	.string "\pI'll prove it to\n"
	.string "you!$"

AzaleaGym_Johto_BugCatcherAlBeatenText:
	.string "You proved how\n"
	.string "tough you are…$"

AzaleaGym_Johto_BugCatcherAlAfterBattleText:
	.string "They're so cool,\n"
	.string "but most girls"
	.string "\pdon't like bug\n"
	.string "POKéMON."
	.string "\pI don't know why…$"

AzaleaGym_Johto_BugCatcherJoshSeenText:
	.string "You saved all the\n"
	.string "SLOWPOKE? Whew,\l"
	.string "you're mighty!"
	.string "\pBut my grown-up\n"
	.string "POKéMON are pretty\l"
	.string "tough too!$"

AzaleaGym_Johto_BugCatcherJoshBeatenText:
	.string "Urrgggh!$"

AzaleaGym_Johto_BugCatcherJoshAfterBattleText:
	.string "I guess I should\n"
	.string "teach them better\l"
	.string "moves…$"

AzaleaGym_Johto_TwinsAmyandmay1SeenText:
	.string "AMY: Hi! Are you\n"
	.string "challenging the\l"
	.string "LEADER? No way!$"

AzaleaGym_Johto_TwinsAmyandmay1BeatenText:
	.string "AMY & MAY: Oh,\n"
	.string "double goodness!$"

AzaleaGym_Johto_TwinsAmyandmay1AfterBattleText:
	.string "AMY: You're\n"
	.string "really strong!$"

AzaleaGym_Johto_TwinsAmyandmay2SeenText:
	.string "MAY: You want to\n"
	.string "see the LEADER?\l"
	.string "We come first!$"

AzaleaGym_Johto_TwinsAmyandmay2BeatenText:
	.string "AMY & MAY: Oh,\n"
	.string "double goodness!$"

AzaleaGym_Johto_TwinsAmyandmay2AfterBattleText:
	.string "MAY: Our bug POKé-\n"
	.string "MON lost! Oh, what\l"
	.string "a shame.$"

AzaleaGym_Johto_AzaleaGymGuideText:
	.string "Yo, challenger!"
	.string "\pBUGSY's young, but\n"
	.string "his knowledge of"
	.string "\pbug POKéMON is for\n"
	.string "real."
	.string "\pIt's going to be\n"
	.string "tough without my\l"
	.string "advice."
	.string "\pLet's see… Bug\n"
	.string "POKéMON don't like\l"
	.string "fire."
	.string "\pFlying-type moves\n"
	.string "are super-effec-\l"
	.string "tive too.$"

AzaleaGym_Johto_AzaleaGymGuideWinText:
	.string "Well done! That\n"
	.string "was a great clash"
	.string "\pof talented young\n"
	.string "trainers."
	.string "\pWith people like\n"
	.string "you, the future of\l"
	.string "POKéMON is bright!$"
