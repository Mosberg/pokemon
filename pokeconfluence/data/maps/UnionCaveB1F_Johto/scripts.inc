UnionCaveB1F_Johto_MapScripts::
	.byte 0

UnionCaveB1F_Johto_UnionCaveB1FTMSwift_Entry::
	lockall
	goto UnionCaveB1F_Johto_UnionCaveB1FTMSwift

UnionCaveB1F_Johto_UnionCaveB1FBoulder_Entry::
	lockall
	goto UnionCaveB1F_Johto_UnionCaveB1FBoulder

UnionCaveB1F_Johto_UnionCaveB1FXDefend_Entry::
	lockall
	goto UnionCaveB1F_Johto_UnionCaveB1FXDefend


UnionCaveB1F_Johto_TrainerPokemaniacAndrew::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_ANDREW, UnionCaveB1F_Johto_PokemaniacAndrewSeenText, UnionCaveB1F_Johto_PokemaniacAndrewBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_ANDREW
	lock
	faceplayer
	goto UnionCaveB1F_Johto_TrainerPokemaniacAndrew_Script

UnionCaveB1F_Johto_TrainerPokemaniacAndrew_Script:
	message UnionCaveB1F_Johto_PokemaniacAndrewAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB1F_Johto_TrainerPokemaniacCalvin::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_CALVIN, UnionCaveB1F_Johto_PokemaniacCalvinSeenText, UnionCaveB1F_Johto_PokemaniacCalvinBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_CALVIN
	lock
	faceplayer
	goto UnionCaveB1F_Johto_TrainerPokemaniacCalvin_Script

UnionCaveB1F_Johto_TrainerPokemaniacCalvin_Script:
	message UnionCaveB1F_Johto_PokemaniacCalvinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB1F_Johto_TrainerHikerPhillip::
	trainerbattle_single TRAINER_JOHTO_HIKER_PHILLIP, UnionCaveB1F_Johto_HikerPhillipSeenText, UnionCaveB1F_Johto_HikerPhillipBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_PHILLIP
	lock
	faceplayer
	goto UnionCaveB1F_Johto_TrainerHikerPhillip_Script

UnionCaveB1F_Johto_TrainerHikerPhillip_Script:
	message UnionCaveB1F_Johto_HikerPhillipAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB1F_Johto_TrainerHikerLeonard::
	trainerbattle_single TRAINER_JOHTO_HIKER_LEONARD, UnionCaveB1F_Johto_HikerLeonardSeenText, UnionCaveB1F_Johto_HikerLeonardBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_LEONARD
	lock
	faceplayer
	goto UnionCaveB1F_Johto_TrainerHikerLeonard_Script

UnionCaveB1F_Johto_TrainerHikerLeonard_Script:
	message UnionCaveB1F_Johto_HikerLeonardAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCaveB1F_Johto_UnionCaveB1FTMSwift:
	finditem ITEM_TM_AERIAL_ACE
	releaseall
	end

UnionCaveB1F_Johto_UnionCaveB1FXDefend:
	finditem ITEM_X_DEFEND
	releaseall
	end

UnionCaveB1F_Johto_UnionCaveB1FBoulder:
	goto Johto_Std_StrengthBoulderScript

UnionCaveB1F_Johto_HikerPhillipSeenText:
	.string "It's been a while\n"
	.string "since I last saw\l"
	.string "another person."
	.string "\pDon't be shy.\n"
	.string "Let's battle!$"

UnionCaveB1F_Johto_HikerPhillipBeatenText:
	.string "Uurggh…$"

UnionCaveB1F_Johto_HikerPhillipAfterBattleText:
	.string "I've been lost for\n"
	.string "a long time…"
	.string "\pI don't mind it\n"
	.string "here, but I am\l"
	.string "soooo hungry!$"

UnionCaveB1F_Johto_HikerLeonardSeenText:
	.string "What do you know!\n"
	.string "A visitor!$"

UnionCaveB1F_Johto_HikerLeonardBeatenText:
	.string "Wahahah! You're a\n"
	.string "feisty one!$"

UnionCaveB1F_Johto_HikerLeonardAfterBattleText:
	.string "I live down here."
	.string "\pYou can, too, if\n"
	.string "you'd like."
	.string "\pThere's plenty of\n"
	.string "room, you see.$"

UnionCaveB1F_Johto_PokemaniacAndrewSeenText:
	.string "Who's there?"
	.string "\pLeave me and my\n"
	.string "POKéMON alone!$"

UnionCaveB1F_Johto_PokemaniacAndrewBeatenText:
	.string "Go…\n"
	.string "Go away!$"

UnionCaveB1F_Johto_PokemaniacAndrewAfterBattleText:
	.string "Just me and my\n"
	.string "POKéMON. I'm de-\l"
	.string "lirious with joy.$"

UnionCaveB1F_Johto_PokemaniacCalvinSeenText:
	.string "I came all the way\n"
	.string "here to conduct my\l"
	.string "POKéMON research."
	.string "\pLet me demonstrate\n"
	.string "my findings in a\l"
	.string "real battle!$"

UnionCaveB1F_Johto_PokemaniacCalvinBeatenText:
	.string "You demonstrated\n"
	.string "on me!$"

UnionCaveB1F_Johto_PokemaniacCalvinAfterBattleText:
	.string "I should compile\n"
	.string "and announce my\l"
	.string "study findings."
	.string "\pI might even be-\n"
	.string "come famous like\l"
	.string "PROF.ELM.$"
