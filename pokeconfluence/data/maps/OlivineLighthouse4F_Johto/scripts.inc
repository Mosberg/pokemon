OlivineLighthouse4F_Johto_MapScripts::
	.byte 0



OlivineLighthouse4F_Johto_TrainerLassConnie::
	trainerbattle_single TRAINER_JOHTO_LASS_CONNIE1, OlivineLighthouse4F_Johto_LassConnie1SeenText, OlivineLighthouse4F_Johto_LassConnie1BeatenText
	setflag FLAG_JOHTO_BEAT_LASS_CONNIE
	lock
	faceplayer
	goto OlivineLighthouse4F_Johto_TrainerLassConnie_Script

OlivineLighthouse4F_Johto_TrainerLassConnie_Script:
	message OlivineLighthouse4F_Johto_LassConnie1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse4F_Johto_TrainerSailorKent::
	trainerbattle_single TRAINER_JOHTO_SAILOR_KENT, OlivineLighthouse4F_Johto_SailorKentSeenText, OlivineLighthouse4F_Johto_SailorKentBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_KENT
	lock
	faceplayer
	goto OlivineLighthouse4F_Johto_TrainerSailorKent_Script

OlivineLighthouse4F_Johto_TrainerSailorKent_Script:
	message OlivineLighthouse4F_Johto_SailorKentAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse4F_Johto_SailorKentSeenText:
	.string "JASMINE must be\n"
	.string "worried sick about\l"
	.string "the POKéMON here."
	.string "\pShe won't even\n"
	.string "smile these days.$"

OlivineLighthouse4F_Johto_SailorKentBeatenText:
	.string "I can't manage a\n"
	.string "smile either…$"

OlivineLighthouse4F_Johto_SailorKentAfterBattleText:
	.string "Speaking of sick,\n"
	.string "I've heard there's"
	.string "\pa good PHARMACY in\n"
	.string "CIANWOOD.$"

OlivineLighthouse4F_Johto_LassConnie1SeenText:
	.string "JASMINE is this\n"
	.string "city's GYM LEADER."
	.string "\pI mean to bring\n"
	.string "her back with me."
	.string "\pNobody had better\n"
	.string "get in my way!$"

OlivineLighthouse4F_Johto_LassConnie1BeatenText:
	.string "Aaack! My POKéMON!$"

OlivineLighthouse4F_Johto_LassConnie1AfterBattleText:
	.string "Right. Anybody\n"
	.string "would be worried\l"
	.string "if his or her own\l"
	.string "POKéMON were hurt."
	.string "\pI'll pray for the\n"
	.string "POKéMON here, so"
	.string "\pJASMINE can come\n"
	.string "back to the GYM.$"
