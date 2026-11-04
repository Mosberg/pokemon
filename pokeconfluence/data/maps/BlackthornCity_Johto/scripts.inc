BlackthornCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_Johto_OnTransition
	.byte 0

BlackthornCity_Johto_OnTransition:
	call BlackthornCity_Johto_BlackthornCityFlypointCallback_Cb
	call BlackthornCity_Johto_BlackthornCitySantosCallback_Cb
	end

BlackthornCity_Johto_BlackthornSuperNerdScript_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornSuperNerdScript

BlackthornCity_Johto_BlackthornGramps1Script_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornGramps1Script

BlackthornCity_Johto_BlackthornGramps2Script_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornGramps2Script

BlackthornCity_Johto_BlackthornBlackBeltScript_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornBlackBeltScript

BlackthornCity_Johto_BlackthornCooltrainerF1Script_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCooltrainerF1Script

BlackthornCity_Johto_BlackthornYoungsterScript_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornYoungsterScript

BlackthornCity_Johto_SantosScript_Entry::
	lockall
	goto BlackthornCity_Johto_SantosScript

BlackthornCity_Johto_BlackthornCooltrainerF2Script_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCooltrainerF2Script

BlackthornCity_Johto_BlackthornCitySign_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCitySign

BlackthornCity_Johto_BlackthornGymSign_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornGymSign

BlackthornCity_Johto_MoveDeletersHouseSign_Entry::
	lockall
	goto BlackthornCity_Johto_MoveDeletersHouseSign

BlackthornCity_Johto_DragonDensSign_Entry::
	lockall
	goto BlackthornCity_Johto_DragonDensSign

BlackthornCity_Johto_BlackthornCityTrainerTips_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCityTrainerTips

BlackthornCity_Johto_BlackthornCityMartSign_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCityMartSign

BlackthornCity_Johto_BlackthornCityPokecenterSign_Entry::
	lockall
	goto BlackthornCity_Johto_BlackthornCityPokecenterSign


BlackthornCity_Johto_BlackthornSuperNerdScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_CLAIR, BlackthornCity_Johto_BlackthornSuperNerdScript_BeatClair
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, BlackthornCity_Johto_BlackthornSuperNerdScript_ClearedRadioTower
	message BlackthornCity_Johto_Text_ClairIsOut
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornSuperNerdScript_ClearedRadioTower:
	message BlackthornCity_Johto_Text_ClairIsIn
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornSuperNerdScript_BeatClair:
	message BlackthornCity_Johto_Text_ClairIsBeaten
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornGramps1Script:
	faceplayer
	message BlackthornCity_Johto_BlackthornGrampsRefusesEntryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornGramps2Script:
	faceplayer
	message BlackthornCity_Johto_BlackthornGrampsGrantsEntryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornBlackBeltScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, BlackthornCity_Johto_BlackthornBlackBeltScript_ClearedRadioTower
	message BlackthornCity_Johto_BlackBeltText_WeirdRadio
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornBlackBeltScript_ClearedRadioTower:
	message BlackthornCity_Johto_BlackBeltText_VoicesInMyHead
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornCooltrainerF1Script:
	faceplayer
	message BlackthornCity_Johto_BlackthornCooltrainerF1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornYoungsterScript:
	faceplayer
	message BlackthornCity_Johto_BlackthornYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornCooltrainerF2Script:
	faceplayer
	message BlackthornCity_Johto_BlackthornCooltrainerF2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_SantosScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SPELL_TAG_FROM_SANTOS, BlackthornCity_Johto_SantosScript_Saturday
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 6, BlackthornCity_Johto_SantosScript_NotSaturday
	goto_if_set FLAG_JOHTO_MET_SANTOS_OF_SATURDAY, BlackthornCity_Johto_SantosScript_MetSantos
	message BlackthornCity_Johto_MeetSantosText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_SANTOS_OF_SATURDAY

BlackthornCity_Johto_SantosScript_MetSantos:
	message BlackthornCity_Johto_SantosGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, 0, BlackthornCity_Johto_SantosScript_Done
	setflag FLAG_JOHTO_GOT_SPELL_TAG_FROM_SANTOS
	message BlackthornCity_Johto_SantosGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_SantosScript_Saturday:
	message BlackthornCity_Johto_SantosSaturdayText
	waitmessage
	waitbuttonpress

BlackthornCity_Johto_SantosScript_Done:
	closemessage
	releaseall
	end

BlackthornCity_Johto_SantosScript_NotSaturday:
	message BlackthornCity_Johto_SantosNotSaturdayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornCitySign:
	message BlackthornCity_Johto_BlackthornCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornGymSign:
	message BlackthornCity_Johto_BlackthornGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_MoveDeletersHouseSign:
	message BlackthornCity_Johto_MoveDeletersHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_DragonDensSign:
	message BlackthornCity_Johto_DragonDensSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornCityTrainerTips:
	message BlackthornCity_Johto_BlackthornCityTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornCity_Johto_BlackthornCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

BlackthornCity_Johto_BlackthornCityMartSign:
	goto Johto_Std_MartSignScript

BlackthornCity_Johto_BlackthornCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_BLACKTHORN
	return

BlackthornCity_Johto_BlackthornCitySantosCallback_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 6, BlackthornCity_Johto_BlackthornCitySantosCallback_SantosAppears_Cb
	setflag FLAG_JOHTO_BLACKTHORN_CITY_SANTOS_OF_SATURDAY
	return

BlackthornCity_Johto_BlackthornCitySantosCallback_SantosAppears_Cb:
	clearflag FLAG_JOHTO_BLACKTHORN_CITY_SANTOS_OF_SATURDAY
	return

BlackthornCity_Johto_Text_ClairIsOut:
	.string "I am sorry."
	.string "\pCLAIR, our GYM\n"
	.string "LEADER, entered"
	.string "\pthe DRAGON'S DEN\n"
	.string "behind the GYM."
	.string "\pI have no idea\n"
	.string "when our LEADER\l"
	.string "will return.$"

BlackthornCity_Johto_Text_ClairIsIn:
	.string "CLAIR, our GYM\n"
	.string "LEADER, is waiting\l"
	.string "for you."
	.string "\pHowever, it would\n"
	.string "be impossible for"
	.string "\pa run-of-the-mill\n"
	.string "trainer to win.$"

BlackthornCity_Johto_Text_ClairIsBeaten:
	.string "You defeated\n"
	.string "CLAIR?"
	.string "\pThat's amazing!"
	.string "\pI've never heard\n"
	.string "of her losing to"
	.string "\panyone other than\n"
	.string "LANCE.$"

BlackthornCity_Johto_BlackthornGrampsRefusesEntryText:
	.string "No. Only chosen\n"
	.string "trainers may train"
	.string "\phere.\n"
	.string "Please leave.$"

BlackthornCity_Johto_BlackthornGrampsGrantsEntryText:
	.string "If CLAIR allows\n"
	.string "it, her grand-\l"
	.string "father--our MASTER\l"
	.string "--will also."
	.string "\pYou may enter.$"

BlackthornCity_Johto_BlackBeltText_WeirdRadio:
	.string "My radio's busted?\n"
	.string "Lately, I only get\l"
	.string "this weird signal.$"

BlackthornCity_Johto_BlackBeltText_VoicesInMyHead:
	.string "Arooo! Voices in\n"
	.string "my head!"
	.string "\pHuh? I'm listening\n"
	.string "to my radio!$"

BlackthornCity_Johto_BlackthornCooltrainerF1Text:
	.string "Are you going to\n"
	.string "make your POKéMON\l"
	.string "forget some moves?$"

BlackthornCity_Johto_BlackthornYoungsterText:
	.string "Dragon masters all\n"
	.string "come from the city\l"
	.string "of BLACKTHORN.$"

BlackthornCity_Johto_MeetSantosText:
	.string "SANTOS: …"
	.string "\pIt's Saturday…"
	.string "\pI'm SANTOS of\n"
	.string "Saturday…$"

BlackthornCity_Johto_SantosGivesGiftText:
	.string "You can have this…$"

BlackthornCity_Johto_SantosGaveGiftText:
	.string "SANTOS: …"
	.string "\pSPELL TAG…"
	.string "\pGhost-type moves\n"
	.string "get stronger…"
	.string "\pIt will frighten\n"
	.string "you…$"

BlackthornCity_Johto_SantosSaturdayText:
	.string "SANTOS: …"
	.string "\pSee you again on\n"
	.string "another Saturday…"
	.string "\pI won't have any\n"
	.string "more gifts…$"

BlackthornCity_Johto_SantosNotSaturdayText:
	.string "SANTOS: Today's\n"
	.string "not Saturday…$"

BlackthornCity_Johto_BlackthornCooltrainerF2Text:
	.string "Wow, you came\n"
	.string "through the ICE\l"
	.string "PATH?"
	.string "\pYou must be a real\n"
	.string "hotshot trainer!$"

BlackthornCity_Johto_BlackthornCitySignText:
	.string "BLACKTHORN CITY"
	.string "\pA Quiet Mountain\n"
	.string "Retreat$"

BlackthornCity_Johto_BlackthornGymSignText:
	.string "BLACKTHORN CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: CLAIR"
	.string "\pThe Blessed User\n"
	.string "of Dragon POKéMON$"

BlackthornCity_Johto_MoveDeletersHouseSignText:
	.string "MOVE DELETER'S\n"
	.string "HOUSE$"

BlackthornCity_Johto_DragonDensSignText:
	.string "DRAGON'S DEN\n"
	.string "AHEAD$"

BlackthornCity_Johto_BlackthornCityTrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pA POKéMON holding\n"
	.string "a MIRACLEBERRY"
	.string "\pwill cure itself\n"
	.string "of any status\l"
	.string "problem.$"
