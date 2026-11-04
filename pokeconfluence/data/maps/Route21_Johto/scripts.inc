Route21_Johto_MapScripts::
	.byte 0



Route21_Johto_TrainerSwimmermSeth::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_SETH, Route21_Johto_SwimmermSethSeenText, Route21_Johto_SwimmermSethBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_SETH
	lock
	faceplayer
	goto Route21_Johto_TrainerSwimmermSeth_Script

Route21_Johto_TrainerSwimmermSeth_Script:
	message Route21_Johto_SwimmermSethAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route21_Johto_TrainerSwimmerfNikki::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_NIKKI, Route21_Johto_SwimmerfNikkiSeenText, Route21_Johto_SwimmerfNikkiBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_NIKKI
	lock
	faceplayer
	goto Route21_Johto_TrainerSwimmerfNikki_Script

Route21_Johto_TrainerSwimmerfNikki_Script:
	message Route21_Johto_SwimmerfNikkiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route21_Johto_TrainerFisherArnold::
	trainerbattle_single TRAINER_JOHTO_FISHER_ARNOLD, Route21_Johto_FisherArnoldSeenText, Route21_Johto_FisherArnoldBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_ARNOLD
	lock
	faceplayer
	goto Route21_Johto_TrainerFisherArnold_Script

Route21_Johto_TrainerFisherArnold_Script:
	message Route21_Johto_FisherArnoldAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route21_Johto_SwimmermSethSeenText:
	.string "Land ho! Gotta\n"
	.string "keep going!$"

Route21_Johto_SwimmermSethBeatenText:
	.string "Glug…$"

Route21_Johto_SwimmermSethAfterBattleText:
	.string "This arrogant guy\n"
	.string "was at CINNABAR's\l"
	.string "volcano.$"

Route21_Johto_SwimmerfNikkiSeenText:
	.string "If I win, you have\n"
	.string "to help me with my\l"
	.string "suntan lotion!$"

Route21_Johto_SwimmerfNikkiBeatenText:
	.string "I'm worried about\n"
	.string "sunburn…$"

Route21_Johto_SwimmerfNikkiAfterBattleText:
	.string "I have to watch\n"
	.string "out for blemishes\l"
	.string "caused by the sun.$"

Route21_Johto_FisherArnoldSeenText:
	.string "I'm bored by fish-\n"
	.string "ing. Let's battle!$"

Route21_Johto_FisherArnoldBeatenText:
	.string "Utter failure…$"

Route21_Johto_FisherArnoldAfterBattleText:
	.string "I'll just go back\n"
	.string "to fishing…$"
