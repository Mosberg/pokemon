LavenderTown_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_Johto_OnTransition
	.byte 0

LavenderTown_Johto_OnTransition:
	call LavenderTown_Johto_LavenderTownFlypointCallback_Cb
	end

LavenderTown_Johto_LavenderTownPokefanMScript_Entry::
	lockall
	goto LavenderTown_Johto_LavenderTownPokefanMScript

LavenderTown_Johto_LavenderTownTeacherScript_Entry::
	lockall
	goto LavenderTown_Johto_LavenderTownTeacherScript

LavenderTown_Johto_LavenderTownGrampsScript_Entry::
	lockall
	goto LavenderTown_Johto_LavenderTownGrampsScript

LavenderTown_Johto_LavenderTownYoungsterScript_Entry::
	lockall
	goto LavenderTown_Johto_LavenderTownYoungsterScript

LavenderTown_Johto_LavenderTownSign_Entry::
	lockall
	goto LavenderTown_Johto_LavenderTownSign

LavenderTown_Johto_KantoRadioStationSign_Entry::
	lockall
	goto LavenderTown_Johto_KantoRadioStationSign

LavenderTown_Johto_VolunteerPokemonHouseSign_Entry::
	lockall
	goto LavenderTown_Johto_VolunteerPokemonHouseSign

LavenderTown_Johto_SoulHouseSign_Entry::
	lockall
	goto LavenderTown_Johto_SoulHouseSign

LavenderTown_Johto_LavenderPokecenterSignText_Entry::
	lockall
	goto LavenderTown_Johto_LavenderPokecenterSignText

LavenderTown_Johto_LavenderMartSignText_Entry::
	lockall
	goto LavenderTown_Johto_LavenderMartSignText


LavenderTown_Johto_LavenderTownPokefanMScript:
	faceplayer
	message LavenderTown_Johto_LavenderTownPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_LavenderTownTeacherScript:
	faceplayer
	message LavenderTown_Johto_LavenderTownTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_LavenderTownGrampsScript:
	faceplayer
	message LavenderTown_Johto_LavenderTownGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_LavenderTownYoungsterScript:
	faceplayer
	message LavenderTown_Johto_LavenderTownYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_LavenderTownSign:
	message LavenderTown_Johto_LavenderTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_KantoRadioStationSign:
	message LavenderTown_Johto_KantoRadioStationSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_VolunteerPokemonHouseSign:
	message LavenderTown_Johto_VolunteerPokemonHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_SoulHouseSign:
	message LavenderTown_Johto_SoulHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderTown_Johto_LavenderPokecenterSignText:
	goto Johto_Std_PokecenterSignScript

LavenderTown_Johto_LavenderMartSignText:
	goto Johto_Std_MartSignScript

LavenderTown_Johto_LavenderTownFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_LAVENDER
	return

LavenderTown_Johto_LavenderTownPokefanMText:
	.string "That's quite some\n"
	.string "building, eh?"
	.string "\pIt's KANTO's RADIO\n"
	.string "TOWER.$"

LavenderTown_Johto_LavenderTownTeacherText:
	.string "KANTO has many\n"
	.string "good radio shows.$"

LavenderTown_Johto_LavenderTownGrampsText:
	.string "People come from\n"
	.string "all over to pay"
	.string "\ptheir respects to\n"
	.string "the departed souls\l"
	.string "of POKéMON.$"

LavenderTown_Johto_LavenderTownYoungsterText:
	.string "You need a POKé\n"
	.string "FLUTE to wake\l"
	.string "sleeping POKéMON."
	.string "\pEvery trainer has\n"
	.string "to know that!$"

LavenderTown_Johto_LavenderTownSignText:
	.string "LAVENDER TOWN"
	.string "\pThe Noble Purple\n"
	.string "Town$"

LavenderTown_Johto_KantoRadioStationSignText:
	.string "KANTO RADIO\n"
	.string "STATION"
	.string "\pYour Favorite\n"
	.string "Programs On-Air\l"
	.string "Around the Clock!$"

LavenderTown_Johto_VolunteerPokemonHouseSignText:
	.string "LAVENDER VOLUNTEER\n"
	.string "POKéMON HOUSE$"

LavenderTown_Johto_SoulHouseSignText:
	.string "SOUL HOUSE"
	.string "\pMay the Souls of\n"
	.string "POKéMON Rest Easy$"
