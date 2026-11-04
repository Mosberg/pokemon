Route41_Johto_MapScripts::
	.byte 0



Route41_Johto_TrainerSwimmerfKaylee::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_KAYLEE, Route41_Johto_SwimmerfKayleeSeenText, Route41_Johto_SwimmerfKayleeBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_KAYLEE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmerfKaylee_Script

Route41_Johto_TrainerSwimmerfKaylee_Script:
	message Route41_Johto_SwimmerfKayleeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmerfSusie::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_SUSIE, Route41_Johto_SwimmerfSusieSeenText, Route41_Johto_SwimmerfSusieBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_SUSIE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmerfSusie_Script

Route41_Johto_TrainerSwimmerfSusie_Script:
	message Route41_Johto_SwimmerfSusieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmerfDenise::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_DENISE, Route41_Johto_SwimmerfDeniseSeenText, Route41_Johto_SwimmerfDeniseBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_DENISE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmerfDenise_Script

Route41_Johto_TrainerSwimmerfDenise_Script:
	message Route41_Johto_SwimmerfDeniseAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmerfKara::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_KARA, Route41_Johto_SwimmerfKaraSeenText, Route41_Johto_SwimmerfKaraBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_KARA
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmerfKara_Script

Route41_Johto_TrainerSwimmerfKara_Script:
	message Route41_Johto_SwimmerfKaraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmerfWendy::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_WENDY, Route41_Johto_SwimmerfWendySeenText, Route41_Johto_SwimmerfWendyBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_WENDY
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmerfWendy_Script

Route41_Johto_TrainerSwimmerfWendy_Script:
	message Route41_Johto_SwimmerfWendyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmermCharlie::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_CHARLIE, Route41_Johto_SwimmermCharlieSeenText, Route41_Johto_SwimmermCharlieBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_CHARLIE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmermCharlie_Script

Route41_Johto_TrainerSwimmermCharlie_Script:
	message Route41_Johto_SwimmermCharlieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmermGeorge::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_GEORGE, Route41_Johto_SwimmermGeorgeSeenText, Route41_Johto_SwimmermGeorgeBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_GEORGE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmermGeorge_Script

Route41_Johto_TrainerSwimmermGeorge_Script:
	message Route41_Johto_SwimmermGeorgeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmermBerke::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_BERKE, Route41_Johto_SwimmermBerkeSeenText, Route41_Johto_SwimmermBerkeBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_BERKE
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmermBerke_Script

Route41_Johto_TrainerSwimmermBerke_Script:
	message Route41_Johto_SwimmermBerkeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmermKirk::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_KIRK, Route41_Johto_SwimmermKirkSeenText, Route41_Johto_SwimmermKirkBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_KIRK
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmermKirk_Script

Route41_Johto_TrainerSwimmermKirk_Script:
	message Route41_Johto_SwimmermKirkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_TrainerSwimmermMathew::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_MATHEW, Route41_Johto_SwimmermMathewSeenText, Route41_Johto_SwimmermMathewBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_MATHEW
	lock
	faceplayer
	goto Route41_Johto_TrainerSwimmermMathew_Script

Route41_Johto_TrainerSwimmermMathew_Script:
	message Route41_Johto_SwimmermMathewAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route41_Johto_SwimmermCharlieSeenText:
	.string "The water's warm\n"
	.string "here. I'm loose\l"
	.string "and limber."
	.string "\pSure, I'll take\n"
	.string "you on!$"

Route41_Johto_SwimmermCharlieBeatenText:
	.string "Yikes! I've got\n"
	.string "prune skin!$"

Route41_Johto_SwimmermCharlieAfterBattleText:
	.string "Isn't it relaxing\n"
	.string "just floating like\l"
	.string "this?$"

Route41_Johto_SwimmermGeorgeSeenText:
	.string "I'm a bit tired.\n"
	.string "If I win, lend me\l"
	.string "your POKéMON.$"

Route41_Johto_SwimmermGeorgeBeatenText:
	.string "Pant, pant…$"

Route41_Johto_SwimmermGeorgeAfterBattleText:
	.string "It's so far to\n"
	.string "CIANWOOD."
	.string "\pBut it's no easy\n"
	.string "return trip to\l"
	.string "OLIVINE either."
	.string "\pWhat should I do?$"

Route41_Johto_SwimmermBerkeSeenText:
	.string "See those islands\n"
	.string "that are blocked\l"
	.string "by whirlpools?"
	.string "\pThere just has to\n"
	.string "be a secret!$"

Route41_Johto_SwimmermBerkeBeatenText:
	.string "What's the secret\n"
	.string "to your strength?$"

Route41_Johto_SwimmermBerkeAfterBattleText:
	.string "It was a dark and\n"
	.string "stormy night…"
	.string "\pI saw this giant\n"
	.string "POKéMON flying\l"
	.string "from the islands."
	.string "\pIt was scattering\n"
	.string "feathers from its\l"
	.string "silver wings.$"

Route41_Johto_SwimmermKirkSeenText:
	.string "The waves are wild\n"
	.string "here."
	.string "\pThey tire you out\n"
	.string "while you swim.$"

Route41_Johto_SwimmermKirkBeatenText:
	.string "I'm beat!$"

Route41_Johto_SwimmermKirkAfterBattleText:
	.string "The currents keep\n"
	.string "me from reaching\l"
	.string "that island.$"

Route41_Johto_SwimmermMathewSeenText:
	.string "Are you seeking\n"
	.string "the secrets of\l"
	.string "WHIRL ISLANDS?$"

Route41_Johto_SwimmermMathewBeatenText:
	.string "Ooh, you've got\n"
	.string "great endurance!$"

Route41_Johto_SwimmermMathewAfterBattleText:
	.string "A secret about\n"
	.string "WHIRL ISLANDS…"
	.string "\pIt's pitch-black\n"
	.string "inside!$"

Route41_Johto_SwimmerfKayleeSeenText:
	.string "I'm on my way to\n"
	.string "WHIRL ISLANDS."
	.string "\pI'm going explor-\n"
	.string "ing with friends.$"

Route41_Johto_SwimmerfKayleeBeatenText:
	.string "Is that how you do\n"
	.string "it?$"

Route41_Johto_SwimmerfKayleeAfterBattleText:
	.string "There's supposed\n"
	.string "to be a big POKé-\l"
	.string "MON deep beneath\l"
	.string "WHIRL ISLANDS."
	.string "\pI wonder what it\n"
	.string "could be?$"

Route41_Johto_SwimmerfSusieSeenText:
	.string "You look so ele-\n"
	.string "gant, riding your\l"
	.string "POKéMON.$"

Route41_Johto_SwimmerfSusieBeatenText:
	.string "I'm crushed…$"

Route41_Johto_SwimmerfSusieAfterBattleText:
	.string "Wasn't there a hit\n"
	.string "song about a boy\l"
	.string "riding a LAPRAS?$"

Route41_Johto_SwimmerfDeniseSeenText:
	.string "The weather is so\n"
	.string "beautiful, I'm in\l"
	.string "a daze!$"

Route41_Johto_SwimmerfDeniseBeatenText:
	.string "Ohhh!$"

Route41_Johto_SwimmerfDeniseAfterBattleText:
	.string "A sunburn is the\n"
	.string "worst for skin."
	.string "\pBut I don't use a\n"
	.string "sunblock."
	.string "\pI won't pollute\n"
	.string "the water.$"

Route41_Johto_SwimmerfKaraSeenText:
	.string "If you need to\n"
	.string "rest, just tread\l"
	.string "water."
	.string "\pYou'll get your\n"
	.string "wind back, so you"
	.string "\pcan keep on going\n"
	.string "strong.$"

Route41_Johto_SwimmerfKaraBeatenText:
	.string "Oh! You have more\n"
	.string "energy than I do.$"

Route41_Johto_SwimmerfKaraAfterBattleText:
	.string "I heard roars from\n"
	.string "deep inside the\l"
	.string "ISLANDS.$"

Route41_Johto_SwimmerfWendySeenText:
	.string "At night, STARYU\n"
	.string "gather near the\l"
	.string "water's surface.$"

Route41_Johto_SwimmerfWendyBeatenText:
	.string "Oh, dear…$"

Route41_Johto_SwimmerfWendyAfterBattleText:
	.string "The clusters of\n"
	.string "STARYU light up\l"
	.string "at the same time."
	.string "\pIt's so beautiful,\n"
	.string "it's scary.$"
