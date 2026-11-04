MahoganyPokecenter1F_Johto_MapScripts::
	.byte 0

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FNurseScript_Entry::
	lockall
	goto MahoganyPokecenter1F_Johto_MahoganyPokecenter1FNurseScript

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FPokefanMScript_Entry::
	lockall
	goto MahoganyPokecenter1F_Johto_MahoganyPokecenter1FPokefanMScript

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FYoungsterScript_Entry::
	lockall
	goto MahoganyPokecenter1F_Johto_MahoganyPokecenter1FYoungsterScript

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto MahoganyPokecenter1F_Johto_MahoganyPokecenter1FCooltrainerFScript


MahoganyPokecenter1F_Johto_MahoganyPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_MAHOGANY_TOWN
	goto Johto_Std_PokecenterNurseScript

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FPokefanMScript:
	faceplayer
	message MahoganyPokecenter1F_Johto_MahoganyPokecenter1FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FYoungsterScript:
	faceplayer
	message MahoganyPokecenter1F_Johto_MahoganyPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FCooltrainerFScript:
	faceplayer
	message MahoganyPokecenter1F_Johto_MahoganyPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FPokefanMText:
	.string "What's this? TEAM\n"
	.string "ROCKET has come\l"
	.string "back?"
	.string "\pI saw some men in\n"
	.string "black at LAKE OF\l"
	.string "RAGE…$"

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FYoungsterText:
	.string "I stop my POKéMON\n"
	.string "from evolving too\l"
	.string "early."
	.string "\pI make them learn\n"
	.string "certain moves be-\l"
	.string "fore I let them\l"
	.string "evolve.$"

MahoganyPokecenter1F_Johto_MahoganyPokecenter1FCooltrainerFText:
	.string "POKéMON do become\n"
	.string "stronger when they"
	.string "\pevolve, but they\n"
	.string "also learn moves\l"
	.string "more slowly.$"
