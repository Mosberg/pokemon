LavenderPokecenter1F_Johto_MapScripts::
	.byte 0

LavenderPokecenter1F_Johto_LavenderPokecenter1FNurseScript_Entry::
	lockall
	goto LavenderPokecenter1F_Johto_LavenderPokecenter1FNurseScript

LavenderPokecenter1F_Johto_LavenderPokecenter1FGentlemanScript_Entry::
	lockall
	goto LavenderPokecenter1F_Johto_LavenderPokecenter1FGentlemanScript

LavenderPokecenter1F_Johto_LavenderPokecenter1FTeacherScript_Entry::
	lockall
	goto LavenderPokecenter1F_Johto_LavenderPokecenter1FTeacherScript

LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterScript_Entry::
	lockall
	goto LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterScript


LavenderPokecenter1F_Johto_LavenderPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_LAVENDER_TOWN
	goto Johto_Std_PokecenterNurseScript

LavenderPokecenter1F_Johto_LavenderPokecenter1FGentlemanScript:
	faceplayer
	message LavenderPokecenter1F_Johto_LavenderPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderPokecenter1F_Johto_LavenderPokecenter1FTeacherScript:
	faceplayer
	message LavenderPokecenter1F_Johto_LavenderPokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterScript_ReturnedMachinePart
	message LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterScript_ReturnedMachinePart:
	message LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderPokecenter1F_Johto_LavenderPokecenter1FGentlemanText:
	.string "To the north of\n"
	.string "LAVENDER is ROCK"
	.string "\pTUNNEL. Go through\n"
	.string "it to get to the\l"
	.string "POWER PLANT.$"

LavenderPokecenter1F_Johto_LavenderPokecenter1FTeacherText:
	.string "There's a radio\n"
	.string "program that plays\l"
	.string "POKé FLUTE music."
	.string "\pOh? Ah, your radio\n"
	.string "needs an EXPN CARD\l"
	.string "to tune into it.$"

LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterText:
	.string "If the POWER PLANT\n"
	.string "isn't running, the"
	.string "\pMAGNET TRAIN won't\n"
	.string "run either…"
	.string "\pIt also means the\n"
	.string "RADIO STATION\l"
	.string "can't broadcast…$"

LavenderPokecenter1F_Johto_LavenderPokecenter1FYoungsterText_ReturnedMachinePart:
	.string "The DIRECTOR of\n"
	.string "the RADIO STATION\l"
	.string "sure was happy."
	.string "\pHe said they're\n"
	.string "back on the air"
	.string "\pbecause the POWER\n"
	.string "PLANT is running\l"
	.string "smoothly again.$"
