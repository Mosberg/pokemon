OlivineLighthouse3F_Johto_MapScripts::
	.byte 0

OlivineLighthouse3F_Johto_OlivineLighthouse3FEther_Entry::
	lockall
	goto OlivineLighthouse3F_Johto_OlivineLighthouse3FEther


OlivineLighthouse3F_Johto_TrainerBirdKeeperTheo::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_THEO, OlivineLighthouse3F_Johto_BirdKeeperTheoSeenText, OlivineLighthouse3F_Johto_BirdKeeperTheoBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_THEO
	lock
	faceplayer
	goto OlivineLighthouse3F_Johto_TrainerBirdKeeperTheo_Script

OlivineLighthouse3F_Johto_TrainerBirdKeeperTheo_Script:
	message OlivineLighthouse3F_Johto_BirdKeeperTheoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse3F_Johto_TrainerGentlemanPreston::
	trainerbattle_single TRAINER_JOHTO_GENTLEMAN_PRESTON, OlivineLighthouse3F_Johto_GentlemanPrestonSeenText, OlivineLighthouse3F_Johto_GentlemanPrestonBeatenText
	setflag FLAG_JOHTO_BEAT_GENTLEMAN_PRESTON
	lock
	faceplayer
	goto OlivineLighthouse3F_Johto_TrainerGentlemanPreston_Script

OlivineLighthouse3F_Johto_TrainerGentlemanPreston_Script:
	message OlivineLighthouse3F_Johto_GentlemanPrestonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse3F_Johto_TrainerSailorTerrell::
	trainerbattle_single TRAINER_JOHTO_SAILOR_TERRELL, OlivineLighthouse3F_Johto_SailorTerrellSeenText, OlivineLighthouse3F_Johto_SailorTerrellBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_TERRELL
	lock
	faceplayer
	goto OlivineLighthouse3F_Johto_TrainerSailorTerrell_Script

OlivineLighthouse3F_Johto_TrainerSailorTerrell_Script:
	message OlivineLighthouse3F_Johto_SailorTerrellAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse3F_Johto_OlivineLighthouse3FEther:
	finditem ITEM_ETHER
	releaseall
	end

OlivineLighthouse3F_Johto_BirdKeeperTheoSeenText:
	.string "Why are you here?\n"
	.string "Are you just going"
	.string "\pto gawk? I suggest\n"
	.string "that you leave!$"

OlivineLighthouse3F_Johto_BirdKeeperTheoBeatenText:
	.string "You really are\n"
	.string "concerned…$"

OlivineLighthouse3F_Johto_BirdKeeperTheoAfterBattleText:
	.string "How the heck do\n"
	.string "you go up?"
	.string "\pI want to visit\n"
	.string "the sick POKéMON,"
	.string "\pbut I can't get up\n"
	.string "there…$"

OlivineLighthouse3F_Johto_SailorTerrellSeenText:
	.string "Sailors are both\n"
	.string "kind and strong.\l"
	.string "How about you?$"

OlivineLighthouse3F_Johto_SailorTerrellBeatenText:
	.string "You are both kind\n"
	.string "and strong…$"

OlivineLighthouse3F_Johto_SailorTerrellAfterBattleText:
	.string "Every time I come\n"
	.string "back to OLIVINE, I\l"
	.string "visit the GYM."
	.string "\pThe GYM LEADER's\n"
	.string "POKéMON type has"
	.string "\pchanged without me\n"
	.string "noticing.$"

OlivineLighthouse3F_Johto_GentlemanPrestonSeenText:
	.string "I travel the world\n"
	.string "to train my POKé-\l"
	.string "MON. I wish to\l"
	.string "battle with you.$"

OlivineLighthouse3F_Johto_GentlemanPrestonBeatenText:
	.string "…sigh… I must\n"
	.string "train some more…$"

OlivineLighthouse3F_Johto_GentlemanPrestonAfterBattleText:
	.string "JASMINE used to\n"
	.string "use rock POKéMON\l"
	.string "like ONIX.$"
