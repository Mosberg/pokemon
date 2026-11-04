ViridianPokecenter1F_Johto_MapScripts::
	.byte 0

ViridianPokecenter1F_Johto_ViridianPokecenter1FNurseScript_Entry::
	lockall
	goto ViridianPokecenter1F_Johto_ViridianPokecenter1FNurseScript

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMScript_Entry::
	lockall
	goto ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMScript

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerFScript

ViridianPokecenter1F_Johto_ViridianPokecenter1FBugCatcherScript_Entry::
	lockall
	goto ViridianPokecenter1F_Johto_ViridianPokecenter1FBugCatcherScript


ViridianPokecenter1F_Johto_ViridianPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_VIRIDIAN_CITY
	goto Johto_Std_PokecenterNurseScript

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BLUE_IN_CINNABAR, ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMScript_BlueReturned
	message ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMScript_BlueReturned:
	message ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMText_BlueReturned
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerFScript:
	faceplayer
	message ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianPokecenter1F_Johto_ViridianPokecenter1FBugCatcherScript:
	faceplayer
	message ViridianPokecenter1F_Johto_ViridianPokecenter1FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMText:
	.string "Where in the world\n"
	.string "is VIRIDIAN's GYM"
	.string "\pLEADER? I wanted\n"
	.string "to challenge him.$"

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerMText_BlueReturned:
	.string "There are no GYM\n"
	.string "TRAINERS at the\l"
	.string "VIRIDIAN GYM."
	.string "\pThe LEADER claims\n"
	.string "his policy is to"
	.string "\pwin without having\n"
	.string "any underlings.$"

ViridianPokecenter1F_Johto_ViridianPokecenter1FCooltrainerFText:
	.string "I heard that the\n"
	.string "GYM in CINNABAR is\l"
	.string "gone."
	.string "\pI wonder what be-\n"
	.string "came of BLAINE,\l"
	.string "the GYM LEADER.$"

ViridianPokecenter1F_Johto_ViridianPokecenter1FBugCatcherText:
	.string "My dream is to be-\n"
	.string "come a GYM LEADER.$"
