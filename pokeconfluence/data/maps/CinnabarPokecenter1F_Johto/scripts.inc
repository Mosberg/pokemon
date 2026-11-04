CinnabarPokecenter1F_Johto_MapScripts::
	.byte 0

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FNurseScript_Entry::
	lockall
	goto CinnabarPokecenter1F_Johto_CinnabarPokecenter1FNurseScript

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto CinnabarPokecenter1F_Johto_CinnabarPokecenter1FCooltrainerFScript

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FFisherScript_Entry::
	lockall
	goto CinnabarPokecenter1F_Johto_CinnabarPokecenter1FFisherScript


CinnabarPokecenter1F_Johto_CinnabarPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_CINNABAR_ISLAND
	goto Johto_Std_PokecenterNurseScript

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FCooltrainerFScript:
	faceplayer
	message CinnabarPokecenter1F_Johto_CinnabarPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FFisherScript:
	faceplayer
	message CinnabarPokecenter1F_Johto_CinnabarPokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FCooltrainerFText:
	.string "CINNABAR GYM's\n"
	.string "BLAINE apparently"
	.string "\plives alone in the\n"
	.string "SEAFOAM ISLANDS\l"
	.string "cave…$"

CinnabarPokecenter1F_Johto_CinnabarPokecenter1FFisherText:
	.string "It's been a year\n"
	.string "since the volcano\l"
	.string "erupted.$"
