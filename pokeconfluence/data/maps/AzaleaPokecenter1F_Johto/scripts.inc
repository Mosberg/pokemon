AzaleaPokecenter1F_Johto_MapScripts::
	.byte 0

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FNurseScript_Entry::
	lockall
	goto AzaleaPokecenter1F_Johto_AzaleaPokecenter1FNurseScript

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FGentlemanScript_Entry::
	lockall
	goto AzaleaPokecenter1F_Johto_AzaleaPokecenter1FGentlemanScript

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FFishingGuruScript_Entry::
	lockall
	goto AzaleaPokecenter1F_Johto_AzaleaPokecenter1FFishingGuruScript

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FPokefanFScript_Entry::
	lockall
	goto AzaleaPokecenter1F_Johto_AzaleaPokecenter1FPokefanFScript


AzaleaPokecenter1F_Johto_AzaleaPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_AZALEA_TOWN
	goto Johto_Std_PokecenterNurseScript

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FGentlemanScript:
	faceplayer
	message AzaleaPokecenter1F_Johto_AzaleaPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FFishingGuruScript:
	faceplayer
	message AzaleaPokecenter1F_Johto_AzaleaPokecenter1FFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FPokefanFScript:
	faceplayer
	message AzaleaPokecenter1F_Johto_AzaleaPokecenter1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FGentlemanText:
	.string "Do your POKéMON\n"
	.string "know HM moves?"
	.string "\pThose moves can\n"
	.string "be used even if"
	.string "\pyour POKéMON has\n"
	.string "fainted.$"

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FFishingGuruText:
	.string "BILL's PC can\n"
	.string "store up to 20\l"
	.string "POKéMON per BOX.$"

AzaleaPokecenter1F_Johto_AzaleaPokecenter1FPokefanFText:
	.string "Do you know about\n"
	.string "APRICORNS?"
	.string "\pCrack one open,\n"
	.string "hollow it out and"
	.string "\pfit it with a\n"
	.string "special device."
	.string "\pThen you can catch\n"
	.string "POKéMON with it."
	.string "\pBefore POKé BALLS\n"
	.string "were invented,"
	.string "\peveryone used\n"
	.string "APRICORNS.$"
