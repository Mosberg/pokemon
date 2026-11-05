BlackthornGym1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BlackthornGym1F_Johto_OnLoad
	.byte 0

BlackthornGym1F_Johto_OnLoad:
	call BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_Cb
	end

BlackthornGym1F_Johto_BlackthornGymClairScript_Entry::
	lockall
	goto BlackthornGym1F_Johto_BlackthornGymClairScript

BlackthornGym1F_Johto_BlackthornGymGuideScript_Entry::
	lockall
	goto BlackthornGym1F_Johto_BlackthornGymGuideScript

BlackthornGym1F_Johto_BlackthornGymStatue_Entry::
	lockall
	goto BlackthornGym1F_Johto_BlackthornGymStatue


BlackthornGym1F_Johto_BlackthornGymClairScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_RISINGBADGE, BlackthornGym1F_Johto_BlackthornGymClairScript_AlreadyGotBadge
	goto_if_set FLAG_JOHTO_BEAT_CLAIR, BlackthornGym1F_Johto_BlackthornGymClairScript_FightDone
	message BlackthornGym1F_Johto_ClairIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_CLAIR_CLAIR1, BlackthornGym1F_Johto_ClairWinText
	setflag FLAG_JOHTO_BEAT_CLAIR
	message BlackthornGym1F_Johto_ClairText_GoToDragonsDen
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_PAUL
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_CODY
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_MIKE
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_FRAN
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_LOLA
	clearflag FLAG_JOHTO_MAHOGANY_MART_OWNERS
	setflag FLAG_JOHTO_BLACKTHORN_CITY_GRAMPS_BLOCKS_DRAGONS_DEN
	clearflag FLAG_JOHTO_BLACKTHORN_CITY_GRAMPS_NOT_BLOCKING_DRAGONS_DEN
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymClairScript_FightDone:
	message BlackthornGym1F_Johto_ClairText_TooMuchToExpect
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymClairScript_AlreadyGotBadge:
	goto_if_set FLAG_JOHTO_GOT_TM24_DRAGONBREATH, BlackthornGym1F_Johto_BlackthornGymClairScript_GotTM24
	message BlackthornGym1F_Johto_BlackthornGymClairText_YouKeptMeWaiting
	waitmessage
	waitbuttonpress
	additem ITEM_TM_DRAGON_CLAW
	goto_if_eq VAR_RESULT, 0, BlackthornGym1F_Johto_BlackthornGymClairScript_BagFull
	bufferitemname STR_VAR_1, ITEM_TM_DRAGON_CLAW
	message BlackthornGym1F_Johto_BlackthornGymText_ReceivedTM24
	waitmessage
	playse SE_PIN
	waitse
	setflag FLAG_JOHTO_GOT_TM24_DRAGONBREATH
	message BlackthornGym1F_Johto_BlackthornGymClairText_DescribeTM24
	waitmessage
	waitbuttonpress
	goto BlackthornGym1F_Johto_BlackthornGymClairScript_GotTM24

BlackthornGym1F_Johto_BlackthornGymClairScript_BagFull:
	message BlackthornGym1F_Johto_BlackthornGymClairText_BagFull
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymClairScript_GotTM24:
	message BlackthornGym1F_Johto_BlackthornGymClairText_League
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_TrainerCooltrainermPaul::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_PAUL, BlackthornGym1F_Johto_CooltrainermPaulSeenText, BlackthornGym1F_Johto_CooltrainermPaulBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_PAUL
	lock
	faceplayer
	goto BlackthornGym1F_Johto_TrainerCooltrainermPaul_Script

BlackthornGym1F_Johto_TrainerCooltrainermPaul_Script:
	message BlackthornGym1F_Johto_CooltrainermPaulAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_TrainerCooltrainermMike::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_MIKE, BlackthornGym1F_Johto_CooltrainermMikeSeenText, BlackthornGym1F_Johto_CooltrainermMikeBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_MIKE
	lock
	faceplayer
	goto BlackthornGym1F_Johto_TrainerCooltrainermMike_Script

BlackthornGym1F_Johto_TrainerCooltrainermMike_Script:
	message BlackthornGym1F_Johto_CooltrainermMikeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_TrainerCooltrainerfLola::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_LOLA, BlackthornGym1F_Johto_CooltrainerfLolaSeenText, BlackthornGym1F_Johto_CooltrainerfLolaBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_LOLA
	lock
	faceplayer
	goto BlackthornGym1F_Johto_TrainerCooltrainerfLola_Script

BlackthornGym1F_Johto_TrainerCooltrainerfLola_Script:
	message BlackthornGym1F_Johto_CooltrainerfLolaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_CLAIR, BlackthornGym1F_Johto_BlackthornGymGuideScript_BlackthornGymGuideWinScript
	message BlackthornGym1F_Johto_BlackthornGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymGuideScript_BlackthornGymGuideWinScript:
	message BlackthornGym1F_Johto_BlackthornGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym1F_Johto_BlackthornGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_RISINGBADGE, BlackthornGym1F_Johto_BlackthornGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

BlackthornGym1F_Johto_BlackthornGymStatue_Beaten:
	buffertrainername STR_VAR_2, TRAINER_JOHTO_CLAIR_CLAIR1
	goto Johto_Std_GymStatue2Script

BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_Cb:
	goto_if_unset FLAG_JOHTO_BOULDER_IN_BLACKTHORN_GYM_1, BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip1_Cb
	setmetatile 8, 2, 558, 1
	setmetatile 9, 2, 519, 0
	setmetatile 8, 3, 566, 0
	setmetatile 9, 3, 519, 0
	special DrawWholeMapView

BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip1_Cb:
	goto_if_unset FLAG_JOHTO_BOULDER_IN_BLACKTHORN_GYM_2, BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip2_Cb
	setmetatile 2, 4, 534, 1
	setmetatile 3, 4, 519, 0
	setmetatile 2, 5, 566, 0
	setmetatile 3, 5, 532, 1
	special DrawWholeMapView

BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip2_Cb:
	goto_if_unset FLAG_JOHTO_BOULDER_IN_BLACKTHORN_GYM_3, BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip3_Cb
	setmetatile 8, 6, 558, 1
	setmetatile 9, 6, 519, 0
	setmetatile 8, 7, 566, 0
	setmetatile 9, 7, 519, 0
	special DrawWholeMapView

BlackthornGym1F_Johto_BlackthornGym1FBouldersCallback_skip3_Cb:
	return

BlackthornGym1F_Johto_ClairIntroText:
	.string "I am CLAIR."
	.string "\pThe world's best\n"
	.string "dragon master."
	.string "\pI can hold my own\n"
	.string "against even the"
	.string "\pPOKéMON LEAGUE's\n"
	.string "ELITE FOUR."
	.string "\pDo you still want\n"
	.string "to take me on?"
	.string "\p…Fine.\n"
	.string "Let's do it!"
	.string "\pAs a GYM LEADER,\n"
	.string "I will use my full"
	.string "\ppower against any\n"
	.string "opponent!$"

BlackthornGym1F_Johto_ClairWinText:
	.string "I lost?"
	.string "\pI don't believe\n"
	.string "it. There must be\l"
	.string "some mistake…$"

BlackthornGym1F_Johto_ClairText_GoToDragonsDen:
	.string "I won't admit\n"
	.string "this."
	.string "\pI may have lost,\n"
	.string "but you're still"
	.string "\pnot ready for the\n"
	.string "POKéMON LEAGUE."
	.string "\pI know. You should\n"
	.string "take the dragon\l"
	.string "user challenge."
	.string "\pBehind this GYM is\n"
	.string "a place called\l"
	.string "DRAGON'S DEN."
	.string "\pThere is a small\n"
	.string "shrine at its"
	.string "\pcenter.\n"
	.string "Go there."
	.string "\pIf you can prove\n"
	.string "that you've lost"
	.string "\pyour lazy ideals,\n"
	.string "I will recognize"
	.string "\pyou as a trainer\n"
	.string "worthy of a GYM\l"
	.string "BADGE!$"

BlackthornGym1F_Johto_ClairText_TooMuchToExpect:
	.string "What's the matter?"
	.string "\pIs it too much to\n"
	.string "expect of you?$"

BlackthornGym1F_Johto_BlackthornGymClairText_YouKeptMeWaiting:
	.string "You've kept me\n"
	.string "waiting!"
	.string "\pHere! Take this!$"

BlackthornGym1F_Johto_BlackthornGymText_ReceivedTM24:
	.string "{PLAYER} received\n"
	.string "TM24.$"

BlackthornGym1F_Johto_BlackthornGymClairText_DescribeTM24:
	.string "That contains\n"
	.string "DRAGONBREATH."
	.string "\pNo, it doesn't\n"
	.string "have anything to\l"
	.string "do with my breath."
	.string "\pIf you don't want\n"
	.string "it, you don't have\l"
	.string "to take it.$"

BlackthornGym1F_Johto_BlackthornGymClairText_BagFull:
	.string "What is this? You\n"
	.string "don't have room?$"

BlackthornGym1F_Johto_BlackthornGymClairText_League:
	.string "What's the matter?"
	.string "\pAren't you headed\n"
	.string "to the POKéMON\l"
	.string "LEAGUE?"
	.string "\pDon't you know\n"
	.string "where it is?"
	.string "\pFrom here, go to\n"
	.string "NEW BARK TOWN."
	.string "\pThen SURF east.\n"
	.string "The route there is\l"
	.string "very tough."
	.string "\pDon't you dare\n"
	.string "lose at the POKé-\l"
	.string "MON LEAGUE!"
	.string "\pIf you do, I'll\n"
	.string "feel even worse"
	.string "\pabout having lost\n"
	.string "to you!"
	.string "\pGive it every-\n"
	.string "thing you've got.$"

BlackthornGym1F_Johto_CooltrainermPaulSeenText:
	.string "Your first battle\n"
	.string "against dragons?"
	.string "\pI'll show you how\n"
	.string "tough they are!$"

BlackthornGym1F_Johto_CooltrainermPaulBeatenText:
	.string "My dragon POKéMON\n"
	.string "lost?$"

BlackthornGym1F_Johto_CooltrainermPaulAfterBattleText:
	.string "LANCE told you\n"
	.string "that he'd like to"
	.string "\psee you again?\n"
	.string "Not a chance!$"

BlackthornGym1F_Johto_CooltrainermMikeSeenText:
	.string "My chance of\n"
	.string "losing? Not even\l"
	.string "one percent!$"

BlackthornGym1F_Johto_CooltrainermMikeBeatenText:
	.string "That's odd.$"

BlackthornGym1F_Johto_CooltrainermMikeAfterBattleText:
	.string "I know my short-\n"
	.string "comings now."
	.string "\pThanks for showing\n"
	.string "me!$"

BlackthornGym1F_Johto_CooltrainerfLolaSeenText:
	.string "Dragons are sacred\n"
	.string "POKéMON."
	.string "\pThey are full of\n"
	.string "life energy."
	.string "\pIf you're not\n"
	.string "serious, you won't"
	.string "\pbe able to beat\n"
	.string "them.$"

BlackthornGym1F_Johto_CooltrainerfLolaBeatenText:
	.string "Way to go!$"

BlackthornGym1F_Johto_CooltrainerfLolaAfterBattleText:
	.string "Dragons are weak\n"
	.string "against dragon-\l"
	.string "type moves.$"

BlackthornGym1F_Johto_BlackthornGymGuideText:
	.string "Yo! CHAMP in\n"
	.string "making!"
	.string "\pIt's been a long\n"
	.string "journey, but we"
	.string "\pare almost done!\n"
	.string "Count on me!"
	.string "\pCLAIR uses the\n"
	.string "mythical and sac-\l"
	.string "red dragon-type\l"
	.string "POKéMON."
	.string "\pYou can't damage\n"
	.string "them very easily."
	.string "\pBut you know,\n"
	.string "they're supposed"
	.string "\pto be weak against\n"
	.string "ice-type moves.$"

BlackthornGym1F_Johto_BlackthornGymGuideWinText:
	.string "You were great to\n"
	.string "beat CLAIR!"
	.string "\pAll that's left is\n"
	.string "the POKéMON LEAGUE\l"
	.string "challenge."
	.string "\pYou're on the way\n"
	.string "to becoming the\l"
	.string "POKéMON CHAMPION!$"
