EcruteakCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_Johto_OnTransition
	.byte 0

EcruteakCity_Johto_OnTransition:
	call EcruteakCity_Johto_EcruteakCityFlypointCallback_Cb
	end

EcruteakCity_Johto_EcruteakCityGramps1Script_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityGramps1Script

EcruteakCity_Johto_EcruteakCityGramps2Script_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityGramps2Script

EcruteakCity_Johto_EcruteakCityLass1Script_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityLass1Script

EcruteakCity_Johto_EcruteakCityLass2Script_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityLass2Script

EcruteakCity_Johto_EcruteakCityFisherScript_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityFisherScript

EcruteakCity_Johto_EcruteakCityYoungsterScript_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityYoungsterScript

EcruteakCity_Johto_EcruteakCityGramps3Script_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityGramps3Script

EcruteakCity_Johto_EcruteakCitySign_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCitySign

EcruteakCity_Johto_TinTowerSign_Entry::
	lockall
	goto EcruteakCity_Johto_TinTowerSign

EcruteakCity_Johto_EcruteakGymSign_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakGymSign

EcruteakCity_Johto_EcruteakDanceTheaterSign_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakDanceTheaterSign

EcruteakCity_Johto_BurnedTowerSign_Entry::
	lockall
	goto EcruteakCity_Johto_BurnedTowerSign

EcruteakCity_Johto_EcruteakCityPokecenterSign_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityPokecenterSign

EcruteakCity_Johto_EcruteakCityMartSign_Entry::
	lockall
	goto EcruteakCity_Johto_EcruteakCityMartSign


EcruteakCity_Johto_EcruteakCityGramps1Script:
	faceplayer
	message EcruteakCity_Johto_EcruteakCityGramps1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityGramps2Script:
	faceplayer
	message EcruteakCity_Johto_EcruteakCityGramps2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityGramps3Script:
	faceplayer
	message EcruteakCity_Johto_EcruteakCityGramps3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityLass1Script:
	faceplayer
	message EcruteakCity_Johto_EcruteakCityLass1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityLass2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RELEASED_THE_BEASTS, EcruteakCity_Johto_EcruteakCityLass2Script_ReleasedBeasts
	message EcruteakCity_Johto_EcruteakCityLass2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityLass2Script_ReleasedBeasts:
	message EcruteakCity_Johto_EcruteakCityLass2Text_ReleasedBeasts
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_JASMINE_RETURNED_TO_GYM, EcruteakCity_Johto_EcruteakCityFisherScript_JasmineReturned
	message EcruteakCity_Johto_EcruteakCityFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityFisherScript_JasmineReturned:
	message EcruteakCity_Johto_EcruteakCityFisherText_JasmineReturned
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityYoungsterScript:
	faceplayer
	message EcruteakCity_Johto_EcruteakCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCitySign:
	message EcruteakCity_Johto_EcruteakCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_TinTowerSign:
	message EcruteakCity_Johto_TinTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakGymSign:
	message EcruteakCity_Johto_EcruteakGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakDanceTheaterSign:
	message EcruteakCity_Johto_EcruteakDanceTheaterSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_BurnedTowerSign:
	message EcruteakCity_Johto_BurnedTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakCity_Johto_EcruteakCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

EcruteakCity_Johto_EcruteakCityMartSign:
	goto Johto_Std_MartSignScript

EcruteakCity_Johto_EcruteakCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_ECRUTEAK
	return

EcruteakCity_Johto_EcruteakCityGramps1Text:
	.string "ECRUTEAK used to\n"
	.string "have two towers:"
	.string "\pone each in the\n"
	.string "east and west.$"

EcruteakCity_Johto_EcruteakCityGramps2Text:
	.string "Ah, child.\n"
	.string "Have you learned"
	.string "\pto dance like the\n"
	.string "KIMONO GIRLS?"
	.string "\pIf you go to their\n"
	.string "DANCE THEATER, an"
	.string "\podd old man will\n"
	.string "give you something\l"
	.string "nice, I hear.$"

EcruteakCity_Johto_EcruteakCityLass1Text:
	.string "I'm going to prac-\n"
	.string "tice at the DANCE"
	.string "\pTHEATER. Care to\n"
	.string "join me?$"

EcruteakCity_Johto_EcruteakCityLass2Text:
	.string "The tower that\n"
	.string "used to be here…"
	.string "\pMy grandma told me\n"
	.string "it used to be much\l"
	.string "taller.$"

EcruteakCity_Johto_EcruteakCityLass2Text_ReleasedBeasts:
	.string "Three big POKéMON\n"
	.string "ran off in differ-\l"
	.string "ent directions.\l"
	.string "What were they?$"

EcruteakCity_Johto_EcruteakCityFisherText:
	.string "I heard a rumor\n"
	.string "about OLIVINE\l"
	.string "LIGHTHOUSE."
	.string "\pThe POKéMON that\n"
	.string "serves as the"
	.string "\pbeacon fell ill.\n"
	.string "Sounds like they\l"
	.string "are in trouble.$"

EcruteakCity_Johto_EcruteakCityFisherText_JasmineReturned:
	.string "The POKéMON at\n"
	.string "OLIVINE LIGHTHOUSE\l"
	.string "has been cured."
	.string "\pBoats can safely\n"
	.string "sail out to sea at\l"
	.string "night again.$"

EcruteakCity_Johto_EcruteakCityYoungsterText:
	.string "I hear POKéMON are\n"
	.string "rampaging at the"
	.string "\pLAKE OF RAGE. I'd\n"
	.string "like to see that.$"

EcruteakCity_Johto_EcruteakCityGramps3Text:
	.string "In the distant\n"
	.string "past…"
	.string "\pThis tower burned\n"
	.string "in a fire. Three"
	.string "\pnameless POKéMON\n"
	.string "perished in it."
	.string "\pA rainbow-colored\n"
	.string "POKéMON descended"
	.string "\pfrom the sky and\n"
	.string "resurrected them…"
	.string "\pIt's a legend that\n"
	.string "has been passed"
	.string "\pdown by ECRUTEAK\n"
	.string "GYM LEADERS."
	.string "\pMe?"
	.string "\pI was a trainer\n"
	.string "way back when.\l"
	.string "Hohoho!$"

EcruteakCity_Johto_EcruteakCitySignText:
	.string "ECRUTEAK CITY\n"
	.string "A Historical City"
	.string "\pWhere the Past\n"
	.string "Meets the Present$"

EcruteakCity_Johto_TinTowerSignText:
	.string "TIN TOWER"
	.string "\pA legendary POKé-\n"
	.string "MON is said to\l"
	.string "roost here.$"

EcruteakCity_Johto_EcruteakGymSignText:
	.string "ECRUTEAK CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: MORTY"
	.string "\pThe Mystic Seer of\n"
	.string "the Future$"

EcruteakCity_Johto_EcruteakDanceTheaterSignText:
	.string "ECRUTEAK DANCE\n"
	.string "THEATER$"

EcruteakCity_Johto_BurnedTowerSignText:
	.string "BURNED TOWER"
	.string "\pIt was destroyed\n"
	.string "by a mysterious\l"
	.string "fire."
	.string "\pPlease stay away,\n"
	.string "as it is unsafe.$"
