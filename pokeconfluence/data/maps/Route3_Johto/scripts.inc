Route3_Johto_MapScripts::
	.byte 0

Route3_Johto_Route3MtMoonSquareSign_Entry::
	lockall
	goto Route3_Johto_Route3MtMoonSquareSign


Route3_Johto_TrainerFirebreatherOtis::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_OTIS, Route3_Johto_FirebreatherOtisSeenText, Route3_Johto_FirebreatherOtisBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_OTIS
	lock
	faceplayer
	goto Route3_Johto_TrainerFirebreatherOtis_Script

Route3_Johto_TrainerFirebreatherOtis_Script:
	message Route3_Johto_FirebreatherOtisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route3_Johto_TrainerYoungsterWarren::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_WARREN, Route3_Johto_YoungsterWarrenSeenText, Route3_Johto_YoungsterWarrenBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_WARREN
	lock
	faceplayer
	goto Route3_Johto_TrainerYoungsterWarren_Script

Route3_Johto_TrainerYoungsterWarren_Script:
	message Route3_Johto_YoungsterWarrenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route3_Johto_TrainerYoungsterJimmy::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_JIMMY, Route3_Johto_YoungsterJimmySeenText, Route3_Johto_YoungsterJimmyBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_JIMMY
	lock
	faceplayer
	goto Route3_Johto_TrainerYoungsterJimmy_Script

Route3_Johto_TrainerYoungsterJimmy_Script:
	message Route3_Johto_YoungsterJimmyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route3_Johto_TrainerFirebreatherBurt::
	trainerbattle_single TRAINER_JOHTO_FIREBREATHER_BURT, Route3_Johto_FirebreatherBurtSeenText, Route3_Johto_FirebreatherBurtBeatenText
	setflag FLAG_JOHTO_BEAT_FIREBREATHER_BURT
	lock
	faceplayer
	goto Route3_Johto_TrainerFirebreatherBurt_Script

Route3_Johto_TrainerFirebreatherBurt_Script:
	message Route3_Johto_FirebreatherBurtAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route3_Johto_Route3MtMoonSquareSign:
	message Route3_Johto_Route3MtMoonSquareSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route3_Johto_FirebreatherOtisSeenText:
	.string "Ah! The weather's\n"
	.string "as fine as ever.$"

Route3_Johto_FirebreatherOtisBeatenText:
	.string "It's sunny, but\n"
	.string "I'm all wet…$"

Route3_Johto_FirebreatherOtisAfterBattleText:
	.string "When it rains,\n"
	.string "it's hard to get\l"
	.string "ignition…$"

Route3_Johto_YoungsterWarrenSeenText:
	.string "Hmmm… I don't know\n"
	.string "what to do…$"

Route3_Johto_YoungsterWarrenBeatenText:
	.string "I knew I'd lose…$"

Route3_Johto_YoungsterWarrenAfterBattleText:
	.string "You looked strong."
	.string "\pI was afraid to\n"
	.string "take you on…$"

Route3_Johto_YoungsterJimmySeenText:
	.string "I can run like the\n"
	.string "wind!$"

Route3_Johto_YoungsterJimmyBeatenText:
	.string "Blown away!$"

Route3_Johto_YoungsterJimmyAfterBattleText:
	.string "I wear shorts the\n"
	.string "whole year round."
	.string "\pThat's my fashion\n"
	.string "policy.$"

Route3_Johto_FirebreatherBurtSeenText:
	.string "Step right up and\n"
	.string "take a look!$"

Route3_Johto_FirebreatherBurtBeatenText:
	.string "Yow! That's hot!$"

Route3_Johto_FirebreatherBurtAfterBattleText:
	.string "The greatest fire-\n"
	.string "breather in KANTO,\l"
	.string "that's me."
	.string "\pBut not the best\n"
	.string "trainer…$"

Route3_Johto_Route3MtMoonSquareSignText:
	.string "MT.MOON SQUARE"
	.string "\pJust go up the\n"
	.string "stairs.$"
