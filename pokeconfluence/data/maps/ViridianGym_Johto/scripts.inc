ViridianGym_Johto_MapScripts::
	.byte 0

ViridianGym_Johto_ViridianGymBlueScript_Entry::
	lockall
	goto ViridianGym_Johto_ViridianGymBlueScript

ViridianGym_Johto_ViridianGymGuideScript_Entry::
	lockall
	goto ViridianGym_Johto_ViridianGymGuideScript

ViridianGym_Johto_ViridianGymStatue_Entry::
	lockall
	goto ViridianGym_Johto_ViridianGymStatue


ViridianGym_Johto_ViridianGymBlueScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_EARTHBADGE, ViridianGym_Johto_ViridianGymBlueScript_FightDone
	message ViridianGym_Johto_LeaderBlueBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_BLUE_BLUE1, ViridianGym_Johto_LeaderBlueWinText
	setflag FLAG_JOHTO_BEAT_BLUE
	message ViridianGym_Johto_Text_ReceivedEarthBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_EARTHBADGE
	message ViridianGym_Johto_LeaderBlueAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianGym_Johto_ViridianGymBlueScript_FightDone:
	message ViridianGym_Johto_LeaderBlueEpilogueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianGym_Johto_ViridianGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_BLUE, ViridianGym_Johto_ViridianGymGuideScript_ViridianGymGuideWinScript
	message ViridianGym_Johto_ViridianGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianGym_Johto_ViridianGymGuideScript_ViridianGymGuideWinScript:
	message ViridianGym_Johto_ViridianGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianGym_Johto_ViridianGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_EARTHBADGE, ViridianGym_Johto_ViridianGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

ViridianGym_Johto_ViridianGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

ViridianGym_Johto_LeaderBlueBeforeText:
	.string "BLUE: Yo! Finally\n"
	.string "got here, huh?"
	.string "\pI wasn't in the\n"
	.string "mood at CINNABAR,"
	.string "\pbut now I'm ready\n"
	.string "to battle you."
	.string "\p…"
	.string "\pYou're telling me\n"
	.string "you conquered all\l"
	.string "the GYMS in JOHTO?"
	.string "\pHeh! JOHTO's GYMS\n"
	.string "must be pretty\l"
	.string "pathetic then."
	.string "\pHey, don't worry\n"
	.string "about it."
	.string "\pI'll know if you\n"
	.string "are good or not by"
	.string "\pbattling you right\n"
	.string "now."
	.string "\pReady, JOHTO\n"
	.string "CHAMP?$"

ViridianGym_Johto_LeaderBlueWinText:
	.string "BLUE: What?"
	.string "\pHow the heck did I\n"
	.string "lose to you?"
	.string "\p…"
	.string "\pTch, all right…\n"
	.string "Here, take this--\l"
	.string "it's EARTHBADGE.$"

ViridianGym_Johto_Text_ReceivedEarthBadge:
	.string "{PLAYER} received\n"
	.string "EARTHBADGE.$"

ViridianGym_Johto_LeaderBlueAfterText:
	.string "BLUE: …"
	.string "\pAll right, I was\n"
	.string "wrong. You're the"
	.string "\preal deal. You are\n"
	.string "a good trainer."
	.string "\pBut I'm going to\n"
	.string "beat you someday."
	.string "\pDon't you forget\n"
	.string "it!$"

ViridianGym_Johto_LeaderBlueEpilogueText:
	.string "BLUE: Listen, you."
	.string "\pYou'd better not\n"
	.string "lose until I beat\l"
	.string "you. Got it?$"

ViridianGym_Johto_ViridianGymGuideText:
	.string "Yo, CHAMP in\n"
	.string "making!"
	.string "\pHow's it going?\n"
	.string "Looks like you're\l"
	.string "on a roll."
	.string "\pThe GYM LEADER is\n"
	.string "a guy who battled"
	.string "\pthe CHAMPION three\n"
	.string "years ago."
	.string "\pHe's no pushover."
	.string "\pGive it everything\n"
	.string "you've got!$"

ViridianGym_Johto_ViridianGymGuideWinText:
	.string "Man, you are truly\n"
	.string "tough…"
	.string "\pThat was a heck of\n"
	.string "an inspirational"
	.string "\pbattle. It brought\n"
	.string "tears to my eyes.$"
