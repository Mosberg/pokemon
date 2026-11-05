OlivineLighthouse5F_Johto_MapScripts::
	.byte 0

OlivineLighthouse5F_Johto_OlivineLighthouse5FRareCandy_Entry::
	lockall
	goto OlivineLighthouse5F_Johto_OlivineLighthouse5FRareCandy

OlivineLighthouse5F_Johto_OlivineLighthouse5FSuperRepel_Entry::
	lockall
	goto OlivineLighthouse5F_Johto_OlivineLighthouse5FSuperRepel

OlivineLighthouse5F_Johto_OlivineLighthouse5FTMSwagger_Entry::
	lockall
	goto OlivineLighthouse5F_Johto_OlivineLighthouse5FTMSwagger


OlivineLighthouse5F_Johto_TrainerBirdKeeperDenis::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_DENIS, OlivineLighthouse5F_Johto_BirdKeeperDenisSeenText, OlivineLighthouse5F_Johto_BirdKeeperDenisBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_DENIS
	lock
	faceplayer
	goto OlivineLighthouse5F_Johto_TrainerBirdKeeperDenis_Script

OlivineLighthouse5F_Johto_TrainerBirdKeeperDenis_Script:
	message OlivineLighthouse5F_Johto_BirdKeeperDenisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse5F_Johto_TrainerSailorErnest::
	trainerbattle_single TRAINER_JOHTO_SAILOR_ERNEST, OlivineLighthouse5F_Johto_SailorErnestSeenText, OlivineLighthouse5F_Johto_SailorErnestBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_ERNEST
	lock
	faceplayer
	goto OlivineLighthouse5F_Johto_TrainerSailorErnest_Script

OlivineLighthouse5F_Johto_TrainerSailorErnest_Script:
	message OlivineLighthouse5F_Johto_SailorErnestAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse5F_Johto_OlivineLighthouse5FRareCandy:
	finditem ITEM_RARE_CANDY
	releaseall
	end

OlivineLighthouse5F_Johto_OlivineLighthouse5FSuperRepel:
	finditem ITEM_SUPER_REPEL
	releaseall
	end

OlivineLighthouse5F_Johto_OlivineLighthouse5FTMSwagger:
	finditem ITEM_TM_TORMENT
	releaseall
	end

OlivineLighthouse5F_Johto_SailorErnestSeenText:
	.string "I wanted to battle\n"
	.string "JASMINE, but she's"
	.string "\pnot up to it now.\n"
	.string "So, how about you?$"

OlivineLighthouse5F_Johto_SailorErnestBeatenText:
	.string "Whoa, whoa. You're\n"
	.string "overwhelming!$"

OlivineLighthouse5F_Johto_SailorErnestAfterBattleText:
	.string "A GYM LEADER isn't\n"
	.string "just about being"
	.string "\pstrong. A LEADER\n"
	.string "also needs to be\l"
	.string "compassionate.$"

OlivineLighthouse5F_Johto_BirdKeeperDenisSeenText:
	.string "We're pretty high\n"
	.string "up here. My bird"
	.string "\pPOKéMON are in\n"
	.string "prime form.$"

OlivineLighthouse5F_Johto_BirdKeeperDenisBeatenText:
	.string "Oops…They crashed…$"

OlivineLighthouse5F_Johto_BirdKeeperDenisAfterBattleText:
	.string "My POKéMON learned\n"
	.string "how to use FLY in\l"
	.string "CIANWOOD."
	.string "\pWell, since I'm a\n"
	.string "loser, I'll FLY\l"
	.string "across the sea…$"
