UnionCaveB2F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, UnionCaveB2F_Johto_OnTransition
	.byte 0

UnionCaveB2F_Johto_OnTransition:
	call UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_Cb
	end

UnionCaveB2F_Johto_UnionCaveB2FElixer_Entry::
	lockall
	goto UnionCaveB2F_Johto_UnionCaveB2FElixer

UnionCaveB2F_Johto_UnionCaveB2FHyperPotion_Entry::
	lockall
	goto UnionCaveB2F_Johto_UnionCaveB2FHyperPotion

UnionCaveB2F_Johto_UnionCaveLapras_Entry::
	lockall
	goto UnionCaveB2F_Johto_UnionCaveLapras


UnionCaveB2F_Johto_UnionCaveLapras:
	faceplayer
	playmoncry SPECIES_LAPRAS, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_LAPRAS, 20
	dowildbattle
	removeobject 6
	setflag FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS
	releaseall
	end

UnionCaveB2F_Johto_TrainerCooltrainermNick::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_NICK, UnionCaveB2F_Johto_CooltrainermNickSeenText, UnionCaveB2F_Johto_CooltrainermNickBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_NICK
	lock
	faceplayer
	goto UnionCaveB2F_Johto_TrainerCooltrainermNick_Script

UnionCaveB2F_Johto_TrainerCooltrainermNick_Script:
	message UnionCaveB2F_Johto_CooltrainermNickAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB2F_Johto_TrainerCooltrainerfGwen::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_GWEN, UnionCaveB2F_Johto_CooltrainerfGwenSeenText, UnionCaveB2F_Johto_CooltrainerfGwenBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_GWEN
	lock
	faceplayer
	goto UnionCaveB2F_Johto_TrainerCooltrainerfGwen_Script

UnionCaveB2F_Johto_TrainerCooltrainerfGwen_Script:
	message UnionCaveB2F_Johto_CooltrainerfGwenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB2F_Johto_TrainerCooltrainerfEmma::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_EMMA, UnionCaveB2F_Johto_CooltrainerfEmmaSeenText, UnionCaveB2F_Johto_CooltrainerfEmmaBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_EMMA
	lock
	faceplayer
	goto UnionCaveB2F_Johto_TrainerCooltrainerfEmma_Script

UnionCaveB2F_Johto_TrainerCooltrainerfEmma_Script:
	message UnionCaveB2F_Johto_CooltrainerfEmmaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB2F_Johto_UnionCaveB2FElixer:
	finditem ITEM_ELIXER
	releaseall
	end

UnionCaveB2F_Johto_UnionCaveB2FHyperPotion:
	finditem ITEM_HYPER_POTION
	releaseall
	end

UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS, UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_NoAppear_Cb
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 5, UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_Appear_Cb

UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_NoAppear_Cb:
	setflag FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS
	return

UnionCaveB2F_Johto_UnionCaveB2FLaprasCallback_Appear_Cb:
	clearflag FLAG_JOHTO_UNION_CAVE_B2F_LAPRAS
	return

UnionCaveB2F_Johto_CooltrainermNickSeenText:
	.string "There are two\n"
	.string "kinds of people."
	.string "\pThose who have\n"
	.string "style, and those\l"
	.string "who don't."
	.string "\pWhat kind of\n"
	.string "person are you?$"

UnionCaveB2F_Johto_CooltrainermNickBeatenText:
	.string "You've got\n"
	.string "dazzling style!$"

UnionCaveB2F_Johto_CooltrainermNickAfterBattleText:
	.string "Your POKéMON style\n"
	.string "is stunning and\l"
	.string "colorful, I admit."
	.string "\pYou'll just keep\n"
	.string "getting better!$"

UnionCaveB2F_Johto_CooltrainerfGwenSeenText:
	.string "I'm in training.\n"
	.string "Care for a round?$"

UnionCaveB2F_Johto_CooltrainerfGwenBeatenText:
	.string "Aww, no! You're\n"
	.string "too good for me.$"

UnionCaveB2F_Johto_CooltrainerfGwenAfterBattleText:
	.string "I'm going to train\n"
	.string "by myself until I\l"
	.string "improve.$"

UnionCaveB2F_Johto_CooltrainerfEmmaSeenText:
	.string "If the POKéMON I\n"
	.string "liked were there,\l"
	.string "I'd go anywhere."
	.string "\pThat's what a real\n"
	.string "trainer does.$"

UnionCaveB2F_Johto_CooltrainerfEmmaBeatenText:
	.string "I'd rather pet my\n"
	.string "babies than this!$"

UnionCaveB2F_Johto_CooltrainerfEmmaAfterBattleText:
	.string "Just once a week,\n"
	.string "a POKéMON comes to\l"
	.string "the water's edge."
	.string "\pI wanted to see\n"
	.string "that POKéMON…$"
