CeruleanGym_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanGym_Johto_OnFrame
	.byte 0

CeruleanGym_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_CERULEAN_GYM, 1, CeruleanGym_Johto_CeruleanGymGruntRunsOutScript_Entry
	.2byte 0

CeruleanGym_Johto_CeruleanGymMistyScript_Entry::
	lockall
	goto CeruleanGym_Johto_CeruleanGymMistyScript

CeruleanGym_Johto_CeruleanGymGuideScript_Entry::
	lockall
	goto CeruleanGym_Johto_CeruleanGymGuideScript

CeruleanGym_Johto_CeruleanGymStatue1_Entry::
	lockall
	goto CeruleanGym_Johto_CeruleanGymStatue1

CeruleanGym_Johto_CeruleanGymStatue2_Entry::
	lockall
	goto CeruleanGym_Johto_CeruleanGymStatue2

CeruleanGym_Johto_CeruleanGymGruntRunsOutScript_Entry::
	lockall
	goto CeruleanGym_Johto_CeruleanGymGruntRunsOutScript


CeruleanGym_Johto_CeruleanGymGruntRunsOutScript:
	applymovement 1, CeruleanGym_Johto_CeruleanGymGruntRunsDownMovement
	waitmovement 1
	playse SE_M_TAIL_WHIP
	applymovement 1, CeruleanGym_Johto_CeruleanGymGruntRunsIntoYouMovement
	waitmovement 1
	playbgm MUS_DUMMY, FALSE
	message CeruleanGym_Johto_CeruleanGymGruntIntroText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, CeruleanGym_Johto_CeruleanGymGruntBacksAwayMovement
	waitmovement 1
	message CeruleanGym_Johto_CeruleanGymGruntBigMistakeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, CeruleanGym_Johto_CeruleanGymGruntMovesCloseMovement
	waitmovement 1
	message CeruleanGym_Johto_CeruleanGymGruntByeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, CeruleanGym_Johto_CeruleanGymGruntRunsOutMovement
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	setflag FLAG_JOHTO_MET_ROCKET_GRUNT_AT_CERULEAN_GYM
	clearflag FLAG_JOHTO_ROUTE_24_ROCKET
	clearflag FLAG_JOHTO_ROUTE_25_MISTY_BOYFRIEND
	setvar VAR_JOHTO_SCENE_CERULEAN_GYM, 0
	setvar VAR_JOHTO_SCENE_ROUTE_25, 1
	setvar VAR_JOHTO_SCENE_POWER_PLANT, 0
	waitse
	fadedefaultbgm
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	releaseall
	end

CeruleanGym_Johto_CeruleanGymMistyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_CASCADEBADGE, CeruleanGym_Johto_CeruleanGymMistyScript_FightDone
	message CeruleanGym_Johto_MistyIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_MISTY_MISTY1, CeruleanGym_Johto_MistyWinLossText
	setflag FLAG_JOHTO_BEAT_MISTY
	setflag FLAG_JOHTO_BEAT_SWIMMERF_DIANA
	setflag FLAG_JOHTO_BEAT_SWIMMERF_BRIANA
	setflag FLAG_JOHTO_BEAT_SWIMMERM_PARKER
	message CeruleanGym_Johto_ReceivedCascadeBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_CASCADEBADGE

CeruleanGym_Johto_CeruleanGymMistyScript_FightDone:
	message CeruleanGym_Johto_MistyFightDoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_TrainerSwimmerfDiana::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_DIANA, CeruleanGym_Johto_SwimmerfDianaSeenText, CeruleanGym_Johto_SwimmerfDianaBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_DIANA
	lock
	faceplayer
	goto CeruleanGym_Johto_TrainerSwimmerfDiana_Script

CeruleanGym_Johto_TrainerSwimmerfDiana_Script:
	message CeruleanGym_Johto_SwimmerfDianaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_TrainerSwimmerfBriana::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_BRIANA, CeruleanGym_Johto_SwimmerfBrianaSeenText, CeruleanGym_Johto_SwimmerfBrianaBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_BRIANA
	lock
	faceplayer
	goto CeruleanGym_Johto_TrainerSwimmerfBriana_Script

CeruleanGym_Johto_TrainerSwimmerfBriana_Script:
	message CeruleanGym_Johto_SwimmerfBrianaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_TrainerSwimmermParker::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_PARKER, CeruleanGym_Johto_SwimmermParkerSeenText, CeruleanGym_Johto_SwimmermParkerBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_PARKER
	lock
	faceplayer
	goto CeruleanGym_Johto_TrainerSwimmermParker_Script

CeruleanGym_Johto_TrainerSwimmermParker_Script:
	message CeruleanGym_Johto_SwimmermParkerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_CeruleanGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_MISTY, CeruleanGym_Johto_CeruleanGymGuideScript_CeruleanGymGuideWinScript
	message CeruleanGym_Johto_CeruleanGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_CeruleanGymGuideScript_CeruleanGymGuideWinScript:
	message CeruleanGym_Johto_CeruleanGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_CeruleanGymStatue1:
	goto_if_unset FLAG_JOHTO_TRAINERS_IN_CERULEAN_GYM, CeruleanGym_Johto_CeruleanGymStatue
	message CeruleanGym_Johto_CeruleanGymNote1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_CeruleanGymStatue2:
	goto_if_unset FLAG_JOHTO_TRAINERS_IN_CERULEAN_GYM, CeruleanGym_Johto_CeruleanGymStatue
	message CeruleanGym_Johto_CeruleanGymNote2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanGym_Johto_CeruleanGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_CASCADEBADGE, CeruleanGym_Johto_CeruleanGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

CeruleanGym_Johto_CeruleanGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

CeruleanGym_Johto_CeruleanGymGruntRunsDownMovement:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

CeruleanGym_Johto_CeruleanGymGruntRunsOutMovement:
	walk_fast_right
	walk_fast_down
	step_end

CeruleanGym_Johto_CeruleanGymGruntRunsIntoYouMovement:
	lock_facing_direction
	jump_up
	unlock_facing_direction
	delay_8
	delay_8
	walk_down
	walk_down
	step_end

CeruleanGym_Johto_CeruleanGymGruntMovesCloseMovement:
	walk_fast_down
	step_end

CeruleanGym_Johto_CeruleanGymGruntBacksAwayMovement:
	lock_facing_direction
	walk_slow_up
	unlock_facing_direction
	step_end

CeruleanGym_Johto_CeruleanGymGruntIntroText:
	.string "Oops! I so sorry!\n"
	.string "You not hurt,\l"
	.string "okay?"
	.string "\pI very busy.\n"
	.string "No time for talk-\l"
	.string "ing with you. Not\l"
	.string "good for me if\l"
	.string "seen by somebody.$"

CeruleanGym_Johto_CeruleanGymGruntBigMistakeText:
	.string "Oh no! You seen\n"
	.string "me already! I make\l"
	.string "big mistake!$"

CeruleanGym_Johto_CeruleanGymGruntByeText:
	.string "Hey, you! Forget\n"
	.string "you see me, okay?"
	.string "\pYou see, hear,\n"
	.string "know nothing,"
	.string "\pokay?\n"
	.string "Bye, kid! Nothing!"
	.string "\pBye-bye a go-go!$"

CeruleanGym_Johto_CeruleanGymNote1Text:
	.string "Sorry, I'll be out\n"
	.string "for a while.\l"
	.string "MISTY, GYM LEADER$"

CeruleanGym_Johto_CeruleanGymNote2Text:
	.string "Since MISTY's out,\n"
	.string "we'll be away too.\l"
	.string "GYM TRAINERS$"

CeruleanGym_Johto_MistyIntroText:
	.string "MISTY: I was ex-\n"
	.string "pecting you, you\l"
	.string "pest!"
	.string "\pYou may have a\n"
	.string "lot of JOHTO GYM"
	.string "\pBADGES, but you'd\n"
	.string "better not take me\l"
	.string "too lightly."
	.string "\pMy water-type\n"
	.string "POKéMON are tough!$"

CeruleanGym_Johto_MistyWinLossText:
	.string "MISTY: You really\n"
	.string "are good…"
	.string "\pI'll admit that\n"
	.string "you are skilled…"
	.string "\pHere you go. It's\n"
	.string "CASCADEBADGE.$"

CeruleanGym_Johto_ReceivedCascadeBadgeText:
	.string "{PLAYER} received\n"
	.string "CASCADEBADGE.$"

CeruleanGym_Johto_MistyFightDoneText:
	.string "MISTY: Are there\n"
	.string "many strong train-\l"
	.string "ers in JOHTO? Like\l"
	.string "you, I mean."
	.string "\pI'm going to\n"
	.string "travel one day, so"
	.string "\pI can battle some\n"
	.string "skilled trainers.$"

CeruleanGym_Johto_SwimmerfDianaSeenText:
	.string "Sorry about being\n"
	.string "away. Let's get on\l"
	.string "with it!$"

CeruleanGym_Johto_SwimmerfDianaBeatenText:
	.string "I give up! You're\n"
	.string "the winner!$"

CeruleanGym_Johto_SwimmerfDianaAfterBattleText:
	.string "I'll be swimming\n"
	.string "quietly.$"

CeruleanGym_Johto_SwimmerfBrianaSeenText:
	.string "Don't let my ele-\n"
	.string "gant swimming un-\l"
	.string "nerve you.$"

CeruleanGym_Johto_SwimmerfBrianaBeatenText:
	.string "Ooh, you calmly\n"
	.string "disposed of me…$"

CeruleanGym_Johto_SwimmerfBrianaAfterBattleText:
	.string "Don't be too smug\n"
	.string "about beating me."
	.string "\pMISTY will destroy\n"
	.string "you if you get\l"
	.string "complacent.$"

CeruleanGym_Johto_SwimmermParkerSeenText:
	.string "Glub…"
	.string "\pI'm first! Come\n"
	.string "and get me!$"

CeruleanGym_Johto_SwimmermParkerBeatenText:
	.string "This can't be…$"

CeruleanGym_Johto_SwimmermParkerAfterBattleText:
	.string "MISTY has gotten\n"
	.string "much better in the\l"
	.string "past few years."
	.string "\pDon't let your\n"
	.string "guard down, or\l"
	.string "you'll be crushed!$"

CeruleanGym_Johto_CeruleanGymGuideText:
	.string "Yo! CHAMP in\n"
	.string "making!"
	.string "\pSince MISTY was\n"
	.string "away, I went out"
	.string "\pfor some fun too.\n"
	.string "He-he-he.$"

CeruleanGym_Johto_CeruleanGymGuideWinText:
	.string "Hoo, you showed me\n"
	.string "how tough you are."
	.string "\pAs always, that\n"
	.string "was one heck of a\l"
	.string "great battle!$"
