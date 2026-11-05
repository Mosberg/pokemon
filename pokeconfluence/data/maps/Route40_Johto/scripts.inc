Route40_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route40_Johto_OnTransition
	.byte 0

Route40_Johto_OnTransition:
	call Route40_Johto_Route40MonicaCallback_Cb
	end

Route40_Johto_Route40Rock_Entry::
	lockall
	goto Route40_Johto_Route40Rock

Route40_Johto_Route40Lass1Script_Entry::
	lockall
	goto Route40_Johto_Route40Lass1Script

Route40_Johto_MonicaScript_Entry::
	lockall
	goto Route40_Johto_MonicaScript

Route40_Johto_Route40PokefanMScript_Entry::
	lockall
	goto Route40_Johto_Route40PokefanMScript

Route40_Johto_Route40Lass2Script_Entry::
	lockall
	goto Route40_Johto_Route40Lass2Script

Route40_Johto_Route40StandingYoungsterScript_Entry::
	lockall
	goto Route40_Johto_Route40StandingYoungsterScript

Route40_Johto_Route40Sign_Entry::
	lockall
	goto Route40_Johto_Route40Sign


Route40_Johto_TrainerSwimmerfElaine::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_ELAINE, Route40_Johto_SwimmerfElaineSeenText, Route40_Johto_SwimmerfElaineBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_ELAINE
	lock
	faceplayer
	goto Route40_Johto_TrainerSwimmerfElaine_Script

Route40_Johto_TrainerSwimmerfElaine_Script:
	message Route40_Johto_SwimmerfElaineAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_TrainerSwimmerfPaula::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_PAULA, Route40_Johto_SwimmerfPaulaSeenText, Route40_Johto_SwimmerfPaulaBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_PAULA
	lock
	faceplayer
	goto Route40_Johto_TrainerSwimmerfPaula_Script

Route40_Johto_TrainerSwimmerfPaula_Script:
	message Route40_Johto_SwimmerfPaulaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_TrainerSwimmermSimon::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_SIMON, Route40_Johto_SwimmermSimonSeenText, Route40_Johto_SwimmermSimonBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_SIMON
	lock
	faceplayer
	goto Route40_Johto_TrainerSwimmermSimon_Script

Route40_Johto_TrainerSwimmermSimon_Script:
	message Route40_Johto_SwimmermSimonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_TrainerSwimmermRandall::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_RANDALL, Route40_Johto_SwimmermRandallSeenText, Route40_Johto_SwimmermRandallBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_RANDALL
	lock
	faceplayer
	goto Route40_Johto_TrainerSwimmermRandall_Script

Route40_Johto_TrainerSwimmermRandall_Script:
	message Route40_Johto_SwimmermRandallAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40Lass1Script:
	faceplayer
	message Route40_Johto_Route40Lass1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40PokefanMScript:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route40_Johto_Route40PokefanMScript_mobile
	faceplayer
	message Route40_Johto_Route40PokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40PokefanMScript_mobile:
	faceplayer
	message Route40_Johto_Route40PokefanMText_Mobile
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40Lass2Script:
	faceplayer
	message Route40_Johto_Route40Lass2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40StandingYoungsterScript:
	faceplayer
	message Route40_Johto_Route40StandingYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_MonicaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SHARP_BEAK_FROM_MONICA, Route40_Johto_MonicaScript_Monday
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 1, Route40_Johto_MonicaScript_NotMonday
	goto_if_set FLAG_JOHTO_MET_MONICA_OF_MONDAY, Route40_Johto_MonicaScript_MetMonica
	message Route40_Johto_MeetMonicaText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_MONICA_OF_MONDAY

Route40_Johto_MonicaScript_MetMonica:
	message Route40_Johto_MonicaGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SHARP_BEAK
	goto_if_eq VAR_RESULT, 0, Route40_Johto_MonicaScript_done
	setflag FLAG_JOHTO_GOT_SHARP_BEAK_FROM_MONICA
	message Route40_Johto_MonicaGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_MonicaScript_Monday:
	message Route40_Johto_MonicaMondayText
	waitmessage
	waitbuttonpress

Route40_Johto_MonicaScript_done:
	closemessage
	releaseall
	end

Route40_Johto_MonicaScript_NotMonday:
	message Route40_Johto_MonicaNotMondayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40Sign:
	message Route40_Johto_Route40SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40_Johto_Route40Rock:
	goto Johto_Std_SmashRockScript

Route40_Johto_Route40MonicaCallback_Cb:
	clearflag FLAG_JOHTO_BATTLE_TOWER_OPEN_CIVILIANS
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 1, Route40_Johto_Route40MonicaCallback_MonicaAppears_Cb
	setflag FLAG_JOHTO_ROUTE_40_MONICA_OF_MONDAY
	return

Route40_Johto_Route40MonicaCallback_MonicaAppears_Cb:
	clearflag FLAG_JOHTO_ROUTE_40_MONICA_OF_MONDAY
	return

Route40_Johto_SwimmermSimonSeenText:
	.string "You have to warm\n"
	.string "up before going\l"
	.string "into the water."
	.string "\pThat's basic.$"

Route40_Johto_SwimmermSimonBeatenText:
	.string "OK! Uncle! I give!$"

Route40_Johto_SwimmermSimonAfterBattleText:
	.string "CIANWOOD CITY is\n"
	.string "a good distance\l"
	.string "away from here.$"

Route40_Johto_SwimmermRandallSeenText:
	.string "Hey, you're young\n"
	.string "and fit!"
	.string "\pDon't ride your\n"
	.string "POKéMON! Swim!$"

Route40_Johto_SwimmermRandallBeatenText:
	.string "Uh-oh. I lost…$"

Route40_Johto_SwimmermRandallAfterBattleText:
	.string "Swimming exercises\n"
	.string "your entire body.\l"
	.string "It's healthy.$"

Route40_Johto_SwimmerfElaineSeenText:
	.string "Are you going to\n"
	.string "CIANWOOD?"
	.string "\pHow about a quick\n"
	.string "battle first?$"

Route40_Johto_SwimmerfElaineBeatenText:
	.string "I lost that one!$"

Route40_Johto_SwimmerfElaineAfterBattleText:
	.string "I'd say I'm a bet-\n"
	.string "ter swimmer than\l"
	.string "you. Yeah!$"

Route40_Johto_SwimmerfPaulaSeenText:
	.string "No inner tube for\n"
	.string "me."
	.string "\pI'm hanging on to\n"
	.string "a sea POKéMON!$"

Route40_Johto_SwimmerfPaulaBeatenText:
	.string "Ooh, I'm feeling\n"
	.string "dizzy!$"

Route40_Johto_SwimmerfPaulaAfterBattleText:
	.string "While I float like\n"
	.string "this, the waves\l"
	.string "carry me along.$"

Route40_Johto_Route40Lass1Text:
	.string "Although you can't\n"
	.string "see it from here,"
	.string "\pCIANWOOD is across\n"
	.string "the sea.$"

Route40_Johto_Route40PokefanMText:
	.string "Hm! There's a big\n"
	.string "building up ahead!"
	.string "\pWhat is it?$"

Route40_Johto_Route40PokefanMText_Mobile:
	.string "Hm! Look at all\n"
	.string "those serious-\l"
	.string "looking trainers\l"
	.string "streaming in."
	.string "\pWhat? What?$"

Route40_Johto_Route40Lass2Text:
	.string "I came to OLIVINE\n"
	.string "by ship to see the"
	.string "\psights and soak up\n"
	.string "the atmosphere."
	.string "\pBeing a port, it\n"
	.string "feels so different\l"
	.string "from a big city.$"

Route40_Johto_Route40StandingYoungsterText:
	.string "Have you gone to\n"
	.string "the BATTLE TOWER?"
	.string "\pI think a lot of\n"
	.string "tough trainers"
	.string "\phave gathered\n"
	.string "there already."
	.string "\pBut since you have\n"
	.string "so many BADGES,"
	.string "\pyou shouldn't do\n"
	.string "badly at all.$"

Route40_Johto_MeetMonicaText:
	.string "MONICA: Glad to\n"
	.string "meet you. I'm"
	.string "\pMONICA of Monday.$"

Route40_Johto_MonicaGivesGiftText:
	.string "As a token of our\n"
	.string "friendship, I have\l"
	.string "a gift for you!$"

Route40_Johto_MonicaGaveGiftText:
	.string "MONICA: It's an\n"
	.string "item that raises"
	.string "\pthe power of fly-\n"
	.string "ing-type moves."
	.string "\pYou should equip a\n"
	.string "bird POKéMON with\l"
	.string "that item.$"

Route40_Johto_MonicaMondayText:
	.string "MONICA: My broth-\n"
	.string "ers and sisters"
	.string "\pare all over the\n"
	.string "place."
	.string "\pSee if you could\n"
	.string "find them all!$"

Route40_Johto_MonicaNotMondayText:
	.string "MONICA: I don't\n"
	.string "think today is\l"
	.string "Monday. How sad…$"

Route40_Johto_Route40SignText:
	.string "ROUTE 40"
	.string "\pCIANWOOD CITY -\n"
	.string "OLIVINE CITY$"
