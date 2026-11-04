Route11_Johto_MapScripts::
	.byte 0

Route11_Johto_Route11FruitTree_Entry::
	lockall
	goto Route11_Johto_Route11FruitTree

Route11_Johto_Route11Sign_Entry::
	lockall
	goto Route11_Johto_Route11Sign


Route11_Johto_TrainerYoungsterOwen::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_OWEN, Route11_Johto_YoungsterOwenSeenText, Route11_Johto_YoungsterOwenBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_OWEN
	lock
	faceplayer
	goto Route11_Johto_TrainerYoungsterOwen_Script

Route11_Johto_TrainerYoungsterOwen_Script:
	message Route11_Johto_YoungsterOwenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route11_Johto_TrainerYoungsterJason::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_JASON, Route11_Johto_YoungsterJasonSeenText, Route11_Johto_YoungsterJasonBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_JASON
	lock
	faceplayer
	goto Route11_Johto_TrainerYoungsterJason_Script

Route11_Johto_TrainerYoungsterJason_Script:
	message Route11_Johto_YoungsterJasonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route11_Johto_TrainerPsychicHerman::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_HERMAN, Route11_Johto_PsychicHermanSeenText, Route11_Johto_PsychicHermanBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_HERMAN
	lock
	faceplayer
	goto Route11_Johto_TrainerPsychicHerman_Script

Route11_Johto_TrainerPsychicHerman_Script:
	message Route11_Johto_PsychicHermanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route11_Johto_TrainerPsychicFidel::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_FIDEL, Route11_Johto_PsychicFidelSeenText, Route11_Johto_PsychicFidelBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_FIDEL
	lock
	faceplayer
	goto Route11_Johto_TrainerPsychicFidel_Script

Route11_Johto_TrainerPsychicFidel_Script:
	message Route11_Johto_PsychicFidelAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route11_Johto_Route11Sign:
	message Route11_Johto_Route11SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route11_Johto_Route11FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_11, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ORAN_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_11
	releaseall
	end

Route11_Johto_YoungsterOwenSeenText:
	.string "There's no cheat-\n"
	.string "ing in POKéMON."
	.string "\pLet's keep it fair\n"
	.string "and square!$"

Route11_Johto_YoungsterOwenBeatenText:
	.string "Huh? How did this\n"
	.string "happen?$"

Route11_Johto_YoungsterOwenAfterBattleText:
	.string "I fought fair and\n"
	.string "square with honor."
	.string "\pI don't regret\n"
	.string "this at all.$"

Route11_Johto_YoungsterJasonSeenText:
	.string "It itches and\n"
	.string "tickles a bit when"
	.string "\pI wear shorts in\n"
	.string "the grass.$"

Route11_Johto_YoungsterJasonBeatenText:
	.string "Aiyaaah!\n"
	.string "I got stomped!$"

Route11_Johto_YoungsterJasonAfterBattleText:
	.string "I'm going to catch\n"
	.string "more POKéMON in\l"
	.string "the grass.$"

Route11_Johto_PsychicHermanSeenText:
	.string "…$"

Route11_Johto_PsychicHermanBeatenText:
	.string "…$"

Route11_Johto_PsychicHermanAfterBattleText:
	.string "…"
	.string "\pI lost while I had\n"
	.string "my eyes closed…$"

Route11_Johto_PsychicFidelSeenText:
	.string "I can see it…"
	.string "\pEverything to see\n"
	.string "about you…$"

Route11_Johto_PsychicFidelBeatenText:
	.string "I couldn't foresee\n"
	.string "your power…$"

Route11_Johto_PsychicFidelAfterBattleText:
	.string "Strength in con-\n"
	.string "viction…"
	.string "\pYou're strong be-\n"
	.string "cause you believe\l"
	.string "in your POKéMON.$"

Route11_Johto_Route11SignText:
	.string "ROUTE 11$"
