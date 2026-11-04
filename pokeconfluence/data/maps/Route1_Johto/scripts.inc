Route1_Johto_MapScripts::
	.byte 0

Route1_Johto_Route1FruitTree_Entry::
	lockall
	goto Route1_Johto_Route1FruitTree

Route1_Johto_Route1Sign_Entry::
	lockall
	goto Route1_Johto_Route1Sign


Route1_Johto_TrainerSchoolboyDanny::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_DANNY, Route1_Johto_SchoolboyDannySeenText, Route1_Johto_SchoolboyDannyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_DANNY
	lock
	faceplayer
	goto Route1_Johto_TrainerSchoolboyDanny_Script

Route1_Johto_TrainerSchoolboyDanny_Script:
	message Route1_Johto_SchoolboyDannyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route1_Johto_TrainerCooltrainerfQuinn::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_QUINN, Route1_Johto_CooltrainerfQuinnSeenText, Route1_Johto_CooltrainerfQuinnBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_QUINN
	lock
	faceplayer
	goto Route1_Johto_TrainerCooltrainerfQuinn_Script

Route1_Johto_TrainerCooltrainerfQuinn_Script:
	message Route1_Johto_CooltrainerfQuinnAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route1_Johto_Route1Sign:
	message Route1_Johto_Route1SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route1_Johto_Route1FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_1, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PERSIM_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_1
	releaseall
	end

Route1_Johto_SchoolboyDannySeenText:
	.string "If trainers meet,\n"
	.string "the first thing to\l"
	.string "do is battle.$"

Route1_Johto_SchoolboyDannyBeatenText:
	.string "Awww… I've got a\n"
	.string "losing record…$"

Route1_Johto_SchoolboyDannyAfterBattleText:
	.string "For trainers, it's\n"
	.string "a given that we'll"
	.string "\pbattle whenever we\n"
	.string "meet.$"

Route1_Johto_CooltrainerfQuinnSeenText:
	.string "You there!\n"
	.string "Want to battle?$"

Route1_Johto_CooltrainerfQuinnBeatenText:
	.string "Down and out…$"

Route1_Johto_CooltrainerfQuinnAfterBattleText:
	.string "You're strong."
	.string "\pYou obviously must\n"
	.string "have trained hard.$"

Route1_Johto_Route1SignText:
	.string "ROUTE 1"
	.string "\pPALLET TOWN -\n"
	.string "VIRIDIAN CITY$"
