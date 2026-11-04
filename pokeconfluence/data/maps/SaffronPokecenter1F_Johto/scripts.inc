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
	@ TODO unsupported: special CheckMobileAdapterStatusSpecial
	goto Johto_EventScript_Unimplemented

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
