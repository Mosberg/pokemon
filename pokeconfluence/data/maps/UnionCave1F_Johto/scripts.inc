UnionCave1F_Johto_MapScripts::
	.byte 0

UnionCave1F_Johto_UnionCave1FGreatBall_Entry::
	lockall
	goto UnionCave1F_Johto_UnionCave1FGreatBall

UnionCave1F_Johto_UnionCave1FXAttack_Entry::
	lockall
	goto UnionCave1F_Johto_UnionCave1FXAttack

UnionCave1F_Johto_UnionCave1FPotion_Entry::
	lockall
	goto UnionCave1F_Johto_UnionCave1FPotion

UnionCave1F_Johto_UnionCave1FAwakening_Entry::
	lockall
	goto UnionCave1F_Johto_UnionCave1FAwakening


UnionCave1F_Johto_TrainerPokemaniacLarry::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_LARRY, UnionCave1F_Johto_PokemaniacLarrySeenText, UnionCave1F_Johto_PokemaniacLarryBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_LARRY
	lock
	faceplayer
	goto UnionCave1F_Johto_TrainerPokemaniacLarry_Script

UnionCave1F_Johto_TrainerPokemaniacLarry_Script:
	message UnionCave1F_Johto_PokemaniacLarryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCave1F_Johto_TrainerHikerRussell::
	trainerbattle_single TRAINER_JOHTO_HIKER_RUSSELL, UnionCave1F_Johto_HikerRussellSeenText, UnionCave1F_Johto_HikerRussellBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_RUSSELL
	lock
	faceplayer
	goto UnionCave1F_Johto_TrainerHikerRussell_Script

UnionCave1F_Johto_TrainerHikerRussell_Script:
	message UnionCave1F_Johto_HikerRussellAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCave1F_Johto_TrainerHikerDaniel::
	trainerbattle_single TRAINER_JOHTO_HIKER_DANIEL, UnionCave1F_Johto_HikerDanielSeenText, UnionCave1F_Johto_HikerDanielBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_DANIEL
	lock
	faceplayer
	goto UnionCave1F_Johto_TrainerHikerDaniel_Script

UnionCave1F_Johto_TrainerHikerDaniel_Script:
	message UnionCave1F_Johto_HikerDanielAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCave1F_Johto_TrainerFirebreatherBill::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_BILL, UnionCave1F_Johto_FirebreatherBillSeenText, UnionCave1F_Johto_FirebreatherBillBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_BILL
	lock
	faceplayer
	goto UnionCave1F_Johto_TrainerFirebreatherBill_Script

UnionCave1F_Johto_TrainerFirebreatherBill_Script:
	message UnionCave1F_Johto_FirebreatherBillAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCave1F_Johto_TrainerFirebreatherRay::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_RAY, UnionCave1F_Johto_FirebreatherRaySeenText, UnionCave1F_Johto_FirebreatherRayBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_RAY
	lock
	faceplayer
	goto UnionCave1F_Johto_TrainerFirebreatherRay_Script

UnionCave1F_Johto_TrainerFirebreatherRay_Script:
	message UnionCave1F_Johto_FirebreatherRayAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

UnionCave1F_Johto_UnionCave1FGreatBall:
	finditem ITEM_GREAT_BALL
	releaseall
	end

UnionCave1F_Johto_UnionCave1FXAttack:
	finditem ITEM_X_ATTACK
	releaseall
	end

UnionCave1F_Johto_UnionCave1FPotion:
	finditem ITEM_POTION
	releaseall
	end

UnionCave1F_Johto_UnionCave1FAwakening:
	finditem ITEM_AWAKENING
	releaseall
	end

UnionCave1F_Johto_HikerRussellSeenText:
	.string "You're headed to\n"
	.string "AZALEA, are you?"
	.string "\pLet my POKéMON see\n"
	.string "if you are good\l"
	.string "enough to battle.$"

UnionCave1F_Johto_HikerRussellBeatenText:
	.string "Oh, oh, oh!$"

UnionCave1F_Johto_HikerRussellAfterBattleText:
	.string "All right, then!\n"
	.string "I've decided."
	.string "\pI'm not leaving\n"
	.string "until my POKéMON\l"
	.string "get tougher!$"

UnionCave1F_Johto_PokemaniacLarrySeenText:
	.string "I roam far and\n"
	.string "wide in search of\l"
	.string "POKéMON."
	.string "\pAre you looking\n"
	.string "for POKéMON too?"
	.string "\pThen you're my\n"
	.string "collecting rival!$"

UnionCave1F_Johto_PokemaniacLarryBeatenText:
	.string "Ugh. My poor POKé-\n"
	.string "MON…$"

UnionCave1F_Johto_PokemaniacLarryAfterBattleText:
	.string "Every Friday, you\n"
	.string "can hear POKéMON"
	.string "\proars from deep\n"
	.string "inside the cave.$"

UnionCave1F_Johto_HikerDanielSeenText:
	.string "Whoa! What a\n"
	.string "surprise!"
	.string "\pI didn't expect to\n"
	.string "see anyone here!$"

UnionCave1F_Johto_HikerDanielBeatenText:
	.string "Whoa! I'm beaten\n"
	.string "big time!$"

UnionCave1F_Johto_HikerDanielAfterBattleText:
	.string "I was conned into\n"
	.string "buying a SLOWPOKE-\l"
	.string "TAIL."
	.string "\pI feel sorry for\n"
	.string "the poor POKéMON.$"

UnionCave1F_Johto_FirebreatherBillSeenText:
	.string "ZUBAT's SUPERSONIC\n"
	.string "keeps confusing\l"
	.string "my POKéMON."
	.string "\pI'm seriously\n"
	.string "upset about that!$"

UnionCave1F_Johto_FirebreatherBillBeatenText:
	.string "I flamed out!$"

UnionCave1F_Johto_FirebreatherBillAfterBattleText:
	.string "On weekends, you\n"
	.string "can hear strange"
	.string "\proars from deep in\n"
	.string "the cave.$"

UnionCave1F_Johto_FirebreatherRaySeenText:
	.string "If it's light, a\n"
	.string "cave isn't scary."
	.string "\pIf you're strong,\n"
	.string "POKéMON aren't\l"
	.string "scary.$"

UnionCave1F_Johto_FirebreatherRayBeatenText:
	.string "FLASH!$"

UnionCave1F_Johto_FirebreatherRayAfterBattleText:
	.string "It's my POKéMON's\n"
	.string "fire that lights\l"
	.string "up this cave.$"
