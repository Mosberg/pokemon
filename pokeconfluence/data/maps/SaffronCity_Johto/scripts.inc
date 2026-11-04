SaffronCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_Johto_OnTransition
	.byte 0

SaffronCity_Johto_OnTransition:
	call SaffronCity_Johto_SaffronCityFlypointCallback_Cb
	end

SaffronCity_Johto_SaffronCityLass1Script_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityLass1Script

SaffronCity_Johto_SaffronCityPokefanMScript_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityPokefanMScript

SaffronCity_Johto_SaffronCityCooltrainerMScript_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityCooltrainerMScript

SaffronCity_Johto_SaffronCityCooltrainerFScript_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityCooltrainerFScript

SaffronCity_Johto_SaffronCityFisherScript_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityFisherScript

SaffronCity_Johto_SaffronCityYoungster1Script_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityYoungster1Script

SaffronCity_Johto_SaffronCityYoungster2Script_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityYoungster2Script

SaffronCity_Johto_SaffronCityLass2Script_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityLass2Script

SaffronCity_Johto_SaffronCitySign_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCitySign

SaffronCity_Johto_SaffronGymSign_Entry::
	lockall
	goto SaffronCity_Johto_SaffronGymSign

SaffronCity_Johto_FightingDojoSign_Entry::
	lockall
	goto SaffronCity_Johto_FightingDojoSign

SaffronCity_Johto_SilphCoSign_Entry::
	lockall
	goto SaffronCity_Johto_SilphCoSign

SaffronCity_Johto_MrPsychicsHouseSign_Entry::
	lockall
	goto SaffronCity_Johto_MrPsychicsHouseSign

SaffronCity_Johto_SaffronCityMagnetTrainStationSign_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityMagnetTrainStationSign

SaffronCity_Johto_SaffronCityPokecenterSign_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityPokecenterSign

SaffronCity_Johto_SaffronCityMartSign_Entry::
	lockall
	goto SaffronCity_Johto_SaffronCityMartSign


SaffronCity_Johto_SaffronCityLass1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, SaffronCity_Johto_SaffronCityLass1Script_ReturnedMachinePart
	message SaffronCity_Johto_SaffronCityLass1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityLass1Script_ReturnedMachinePart:
	message SaffronCity_Johto_SaffronCityLass1Text_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityPokefanMScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, SaffronCity_Johto_SaffronCityPokefanMScript_ReturnedMachinePart
	message SaffronCity_Johto_SaffronCityPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityPokefanMScript_ReturnedMachinePart:
	message SaffronCity_Johto_SaffronCityPokefanMText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityCooltrainerMScript:
	faceplayer
	message SaffronCity_Johto_SaffronCityCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityCooltrainerFScript:
	faceplayer
	message SaffronCity_Johto_SaffronCityCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, SaffronCity_Johto_SaffronCityFisherScript_ReturnedMachinePart
	message SaffronCity_Johto_SaffronCityFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityFisherScript_ReturnedMachinePart:
	message SaffronCity_Johto_SaffronCityFisherText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityYoungster1Script:
	faceplayer
	message SaffronCity_Johto_SaffronCityYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityYoungster2Script:
	faceplayer
	message SaffronCity_Johto_SaffronCityYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityLass2Script:
	faceplayer
	message SaffronCity_Johto_SaffronCityLass2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCitySign:
	message SaffronCity_Johto_SaffronCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronGymSign:
	message SaffronCity_Johto_SaffronGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_FightingDojoSign:
	message SaffronCity_Johto_FightingDojoSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SilphCoSign:
	message SaffronCity_Johto_SilphCoSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_MrPsychicsHouseSign:
	message SaffronCity_Johto_MrPsychicsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityMagnetTrainStationSign:
	message SaffronCity_Johto_SaffronCityMagnetTrainStationSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronCity_Johto_SaffronCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

SaffronCity_Johto_SaffronCityMartSign:
	goto Johto_Std_MartSignScript

SaffronCity_Johto_SaffronCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_SAFFRON
	return

SaffronCity_Johto_SaffronCityLass1Text:
	.string "A little girl who\n"
	.string "is an expert at"
	.string "\pmimicking people\n"
	.string "lives here."
	.string "\pShe even mimics\n"
	.string "the people she's"
	.string "\pconversing with.\n"
	.string "It's confusing.$"

SaffronCity_Johto_SaffronCityLass1Text_ReturnedMachinePart:
	.string "The COPYCAT girl\n"
	.string "looked unhappy."
	.string "\pShe said she lost\n"
	.string "her favorite POKé\l"
	.string "DOLL--CLEFAIRY.$"

SaffronCity_Johto_SaffronCityPokefanMText:
	.string "You came out from\n"
	.string "JOHTO?"
	.string "\pYou can zip back\n"
	.string "home if the MAGNET\l"
	.string "TRAIN's running.$"

SaffronCity_Johto_SaffronCityPokefanMText_ReturnedMachinePart:
	.string "You came out from\n"
	.string "JOHTO?"
	.string "\pYou can zip back\n"
	.string "home by hopping on\l"
	.string "the MAGNET TRAIN.$"

SaffronCity_Johto_SaffronCityCooltrainerMText:
	.string "I went to the GYM,\n"
	.string "raring for battles\l"
	.string "against trainers…"
	.string "\pIt turns out, I\n"
	.string "stumbled into the"
	.string "\punused GYM next\n"
	.string "door."
	.string "\pBoy, I was pretty\n"
	.string "embarrassed.$"

SaffronCity_Johto_SaffronCityCooltrainerFText:
	.string "This is SILPH CO.,\n"
	.string "famous for POKéMON\l"
	.string "merchandise."
	.string "\pIn the past, TEAM\n"
	.string "ROCKET wanted the"
	.string "\pcompany because of\n"
	.string "that.$"

SaffronCity_Johto_SaffronCityFisherText:
	.string "Chew… Chew…"
	.string "\pI hear there's big\n"
	.string "trouble brewing at\l"
	.string "the POWER PLANT."
	.string "\pChew… Chew…$"

SaffronCity_Johto_SaffronCityFisherText_ReturnedMachinePart:
	.string "Chew… Chew…"
	.string "\pI hear there was\n"
	.string "big trouble at the\l"
	.string "POWER PLANT."
	.string "\pChew… Chew…\n"
	.string "Haaah, I'm full!$"

SaffronCity_Johto_SaffronCityYoungster1Text:
	.string "Going into an\n"
	.string "alley for the"
	.string "\pfirst time makes\n"
	.string "me sorta anxious.$"

SaffronCity_Johto_SaffronCityYoungster2Text:
	.string "There's a place\n"
	.string "called TRAINER"
	.string "\pHOUSE in VIRIDIAN\n"
	.string "where trainers"
	.string "\pgather from all\n"
	.string "over the place.$"

SaffronCity_Johto_SaffronCityLass2Text:
	.string "Our city was\n"
	.string "featured on a\l"
	.string "radio program."
	.string "\pIt's nice to hear\n"
	.string "praise for your"
	.string "\pcity, but it's a\n"
	.string "bit embarrassing\l"
	.string "too.$"

SaffronCity_Johto_SaffronCitySignText:
	.string "SAFFRON CITY"
	.string "\pShining, Golden\n"
	.string "Land of Commerce$"

SaffronCity_Johto_SaffronGymSignText:
	.string "SAFFRON CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: SABRINA"
	.string "\pThe Master of\n"
	.string "Psychic POKéMON!$"

SaffronCity_Johto_FightingDojoSignText:
	.string "Everyone Welcome!\n"
	.string "FIGHTING DOJO$"

SaffronCity_Johto_SilphCoSignText:
	.string "SILPH CO.\n"
	.string "OFFICE BUILDING$"

SaffronCity_Johto_MrPsychicsHouseSignText:
	.string "MR.PSYCHIC'S\n"
	.string "HOUSE$"

SaffronCity_Johto_SaffronCityMagnetTrainStationSignText:
	.string "SAFFRON CITY\n"
	.string "MAGNET TRAIN\l"
	.string "STATION$"
