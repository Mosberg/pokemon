MountMortar2FInside_Johto_MapScripts::
	.byte 0

MountMortar2FInside_Johto_MountMortar2FInsideMaxPotion_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideMaxPotion

MountMortar2FInside_Johto_MountMortar2FInsideRareCandy_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideRareCandy

MountMortar2FInside_Johto_MountMortar2FInsideTMDefenseCurl_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideTMDefenseCurl

MountMortar2FInside_Johto_MountMortar2FInsideDragonScale_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideDragonScale

MountMortar2FInside_Johto_MountMortar2FInsideElixer_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideElixer

MountMortar2FInside_Johto_MountMortar2FInsideEscapeRope_Entry::
	lockall
	goto MountMortar2FInside_Johto_MountMortar2FInsideEscapeRope


MountMortar2FInside_Johto_TrainerSupernerdHugh::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_HUGH, MountMortar2FInside_Johto_SupernerdHughSeenText, MountMortar2FInside_Johto_SupernerdHughBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_HUGH
	lock
	faceplayer
	goto MountMortar2FInside_Johto_TrainerSupernerdHugh_Script

MountMortar2FInside_Johto_TrainerSupernerdHugh_Script:
	message MountMortar2FInside_Johto_SupernerdHughAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideMaxPotion:
	finditem ITEM_MAX_POTION
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideRareCandy:
	finditem ITEM_RARE_CANDY
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideTMDefenseCurl:
	finditem ITEM_NUGGET
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideDragonScale:
	finditem ITEM_DRAGON_SCALE
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideElixer:
	finditem ITEM_ELIXER
	releaseall
	end

MountMortar2FInside_Johto_MountMortar2FInsideEscapeRope:
	finditem ITEM_ESCAPE_ROPE
	releaseall
	end

MountMortar2FInside_Johto_SupernerdHughSeenText:
	.string "Yo! MARKUS!$"

MountMortar2FInside_Johto_SupernerdHughBeatenText:
	.string "Sorry, my mistake.$"

MountMortar2FInside_Johto_SupernerdHughAfterBattleText:
	.string "I'm investigating\n"
	.string "MT.MORTAR, but my\l"
	.string "pal's gone AWOL."
	.string "\pHave you seen a\n"
	.string "trainer who has a"
	.string "\pSLOWPOKE that can\n"
	.string "use STRENGTH?$"
