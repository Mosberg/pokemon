BlackthornPokecenter1F_Johto_MapScripts::
	.byte 0

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FNurseScript_Entry::
	lockall
	goto BlackthornPokecenter1F_Johto_BlackthornPokecenter1FNurseScript

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FGentlemanScript_Entry::
	lockall
	goto BlackthornPokecenter1F_Johto_BlackthornPokecenter1FGentlemanScript

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FTwinScript_Entry::
	lockall
	goto BlackthornPokecenter1F_Johto_BlackthornPokecenter1FTwinScript

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FCooltrainerMScript_Entry::
	lockall
	goto BlackthornPokecenter1F_Johto_BlackthornPokecenter1FCooltrainerMScript


BlackthornPokecenter1F_Johto_BlackthornPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_BLACKTHORN_CITY
	goto Johto_Std_PokecenterNurseScript

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FGentlemanScript:
	faceplayer
	message BlackthornPokecenter1F_Johto_BlackthornPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FTwinScript:
	faceplayer
	message BlackthornPokecenter1F_Johto_BlackthornPokecenter1FTwinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FCooltrainerMScript:
	goto Johto_Std_HappinessCheckScript

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FGentlemanText:
	.string "Deep inside far-\n"
	.string "off INDIGO PLATEAU"
	.string "\pis the POKéMON\n"
	.string "LEAGUE."
	.string "\pI hear the best\n"
	.string "trainers gather"
	.string "\pthere from around\n"
	.string "the country.$"

BlackthornPokecenter1F_Johto_BlackthornPokecenter1FTwinText:
	.string "There was this\n"
	.string "move I just had"
	.string "\pto teach my POKé-\n"
	.string "MON."
	.string "\pSo I got the MOVE\n"
	.string "DELETER to make it\l"
	.string "forget an HM move.$"
