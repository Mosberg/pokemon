SaffronPokecenter1F_Johto_MapScripts::
	.byte 0

SaffronPokecenter1F_Johto_SaffronPokecenter1FNurseScript_Entry::
	lockall
	goto SaffronPokecenter1F_Johto_SaffronPokecenter1FNurseScript

SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherScript_Entry::
	lockall
	goto SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherScript

SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherScript_Entry::
	lockall
	goto SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherScript

SaffronPokecenter1F_Johto_SaffronPokecenter1FYoungsterScript_Entry::
	lockall
	goto SaffronPokecenter1F_Johto_SaffronPokecenter1FYoungsterScript


SaffronPokecenter1F_Johto_SaffronPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_SAFFRON_CITY
	goto Johto_Std_PokecenterNurseScript

SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherScript:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherScript_mobile
	faceplayer
	message SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherScript_mobile:
	faceplayer
	message SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherMobileText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherScript_SolvedKantoPowerCrisis
	message SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherScript_SolvedKantoPowerCrisis:
	message SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherReturnedMachinePartText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronPokecenter1F_Johto_SaffronPokecenter1FYoungsterScript:
	faceplayer
	message SaffronPokecenter1F_Johto_SaffronPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherText:
	.string "What are JOHTO's\n"
	.string "POKéMON CENTERS\l"
	.string "like?"
	.string "\p…Oh, I see. So\n"
	.string "they're not much"
	.string "\pdifferent from the\n"
	.string "ones in KANTO."
	.string "\pI can go to JOHTO\n"
	.string "without worrying,\l"
	.string "then!$"

SaffronPokecenter1F_Johto_SaffronPokecenter1FTeacherMobileText:
	.string "What are JOHTO's\n"
	.string "POKéMON CENTERS\l"
	.string "like?"
	.string "\p…Oh, I see.\n"
	.string "So they let you"
	.string "\plink with people\n"
	.string "far away?"
	.string "\pThen I'll get my\n"
	.string "friend in JOHTO to"
	.string "\pcatch a MARILL and\n"
	.string "trade it to me!$"

SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherText:
	.string "I just happened to\n"
	.string "come through ROCK"
	.string "\pTUNNEL. There was\n"
	.string "some commotion at\l"
	.string "the POWER PLANT.$"

SaffronPokecenter1F_Johto_SaffronPokecenter1FFisherReturnedMachinePartText:
	.string "Caves collapse\n"
	.string "easily."
	.string "\pSeveral caves have\n"
	.string "disappeared in the"
	.string "\ppast few years,\n"
	.string "like the one out-\l"
	.string "side CERULEAN."
	.string "\pAs a pro HIKER,\n"
	.string "that's common\l"
	.string "knowledge.$"

SaffronPokecenter1F_Johto_SaffronPokecenter1FYoungsterText:
	.string "SILPH CO.'s HEAD\n"
	.string "OFFICE and the"
	.string "\pMAGNET TRAIN STA-\n"
	.string "TION--they're the"
	.string "\pplaces to see in\n"
	.string "SAFFRON.$"
