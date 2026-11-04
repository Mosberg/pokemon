Route18_Johto_MapScripts::
	.byte 0

Route18_Johto_Route18Sign_Entry::
	lockall
	goto Route18_Johto_Route18Sign


Route18_Johto_TrainerBirdKeeperBoris::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_BORIS, Route18_Johto_BirdKeeperBorisSeenText, Route18_Johto_BirdKeeperBorisBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_BORIS
	lock
	faceplayer
	goto Route18_Johto_TrainerBirdKeeperBoris_Script

Route18_Johto_TrainerBirdKeeperBoris_Script:
	message Route18_Johto_BirdKeeperBorisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route18_Johto_TrainerBirdKeeperBob::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_BOB, Route18_Johto_BirdKeeperBobSeenText, Route18_Johto_BirdKeeperBobBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_BOB
	lock
	faceplayer
	goto Route18_Johto_TrainerBirdKeeperBob_Script

Route18_Johto_TrainerBirdKeeperBob_Script:
	message Route18_Johto_BirdKeeperBobAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route18_Johto_Route18Sign:
	message Route18_Johto_Route18SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route18_Johto_BirdKeeperBorisSeenText:
	.string "If you're looking\n"
	.string "for POKéMON, you"
	.string "\phave to look in\n"
	.string "the tall grass.$"

Route18_Johto_BirdKeeperBorisBeatenText:
	.string "Ayieee!$"

Route18_Johto_BirdKeeperBorisAfterBattleText:
	.string "Since you're so\n"
	.string "strong, it must be\l"
	.string "fun to battle.$"

Route18_Johto_BirdKeeperBobSeenText:
	.string "CYCLING ROAD is a\n"
	.string "quick shortcut to\l"
	.string "CELADON.$"

Route18_Johto_BirdKeeperBobBeatenText:
	.string "…Whew!$"

Route18_Johto_BirdKeeperBobAfterBattleText:
	.string "If you don't have\n"
	.string "a BICYCLE, you're"
	.string "\pnot allowed to use\n"
	.string "the shortcut.$"

Route18_Johto_Route18SignText:
	.string "ROUTE 18"
	.string "\pCELADON CITY -\n"
	.string "FUCHSIA CITY$"
