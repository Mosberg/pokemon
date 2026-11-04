MountMortar1FInside_Johto_MapScripts::
	.byte 0

MountMortar1FInside_Johto_MountMortar1FBoulder_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FBoulder

MountMortar1FInside_Johto_MountMortar1FInsideEscapeRope_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideEscapeRope

MountMortar1FInside_Johto_MountMortar1FInsideMaxRevive_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideMaxRevive

MountMortar1FInside_Johto_MountMortar1FInsideHyperPotion_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideHyperPotion

MountMortar1FInside_Johto_MountMortar1FInsideMaxPotion_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideMaxPotion

MountMortar1FInside_Johto_MountMortar1FInsideNugget_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideNugget

MountMortar1FInside_Johto_MountMortar1FInsideIron_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideIron

MountMortar1FInside_Johto_MountMortar1FInsideUltraBall_Entry::
	lockall
	goto MountMortar1FInside_Johto_MountMortar1FInsideUltraBall


MountMortar1FInside_Johto_TrainerPokemaniacMiller::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_MILLER, MountMortar1FInside_Johto_PokemaniacMillerSeenText, MountMortar1FInside_Johto_PokemaniacMillerBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_MILLER
	lock
	faceplayer
	goto MountMortar1FInside_Johto_TrainerPokemaniacMiller_Script

MountMortar1FInside_Johto_TrainerPokemaniacMiller_Script:
	message MountMortar1FInside_Johto_PokemaniacMillerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMortar1FInside_Johto_TrainerSupernerdMarkus::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_MARKUS, MountMortar1FInside_Johto_SupernerdMarkusSeenText, MountMortar1FInside_Johto_SupernerdMarkusBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_MARKUS
	lock
	faceplayer
	goto MountMortar1FInside_Johto_TrainerSupernerdMarkus_Script

MountMortar1FInside_Johto_TrainerSupernerdMarkus_Script:
	message MountMortar1FInside_Johto_SupernerdMarkusAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FBoulder:
	goto Johto_Std_StrengthBoulderScript

MountMortar1FInside_Johto_MountMortar1FInsideEscapeRope:
	finditem ITEM_ESCAPE_ROPE
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideMaxRevive:
	finditem ITEM_MAX_REVIVE
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideHyperPotion:
	finditem ITEM_HYPER_POTION
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideMaxPotion:
	finditem ITEM_MAX_POTION
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideNugget:
	finditem ITEM_NUGGET
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideIron:
	finditem ITEM_IRON
	releaseall
	end

MountMortar1FInside_Johto_MountMortar1FInsideUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

MountMortar1FInside_Johto_PokemaniacMillerSeenText:
	.string "I'm not losing\n"
	.string "this time!$"

MountMortar1FInside_Johto_PokemaniacMillerBeatenText:
	.string "I lost to some\n"
	.string "kid…?$"

MountMortar1FInside_Johto_PokemaniacMillerAfterBattleText:
	.string "A while back, this\n"
	.string "karate dude wanted"
	.string "\pto battle. He was\n"
	.string "ridiculously good."
	.string "\pHe just thrashed\n"
	.string "us silly."
	.string "\pHe went in deeper\n"
	.string "saying it was for"
	.string "\phis training. I\n"
	.string "wonder how he is?$"

MountMortar1FInside_Johto_SupernerdMarkusSeenText:
	.string "Hey! HUGH!$"

MountMortar1FInside_Johto_SupernerdMarkusBeatenText:
	.string "I mistook you for\n"
	.string "someone else…$"

MountMortar1FInside_Johto_SupernerdMarkusAfterBattleText:
	.string "I came to explore\n"
	.string "MT.MORTAR, but I"
	.string "\pgot separated from\n"
	.string "my partner…"
	.string "\pDid you run into a\n"
	.string "trainer who uses a"
	.string "\pSEADRA that knows\n"
	.string "WATERFALL?$"
