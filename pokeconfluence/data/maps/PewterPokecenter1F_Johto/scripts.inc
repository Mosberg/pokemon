PewterPokecenter1F_Johto_MapScripts::
	.byte 0

PewterPokecenter1F_Johto_PewterPokecenter1FNurseScript_Entry::
	lockall
	goto PewterPokecenter1F_Johto_PewterPokecenter1FNurseScript

PewterPokecenter1F_Johto_PewterPokecenter1FTeacherScript_Entry::
	lockall
	goto PewterPokecenter1F_Johto_PewterPokecenter1FTeacherScript

PewterPokecenter1F_Johto_PewterJigglypuff_Entry::
	lockall
	goto PewterPokecenter1F_Johto_PewterJigglypuff

PewterPokecenter1F_Johto_PewterPokecenter1FBugCatcherScript_Entry::
	lockall
	goto PewterPokecenter1F_Johto_PewterPokecenter1FBugCatcherScript

PewterPokecenter1F_Johto_Chris_Entry::
	lockall
	goto PewterPokecenter1F_Johto_Chris


PewterPokecenter1F_Johto_PewterPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_PEWTER_CITY
	goto Johto_Std_PokecenterNurseScript

PewterPokecenter1F_Johto_PewterPokecenter1FTeacherScript:
	faceplayer
	message PewterPokecenter1F_Johto_PewterPokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterPokecenter1F_Johto_PewterJigglypuff:
	message PewterPokecenter1F_Johto_PewterJigglypuffText
	waitmessage
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

PewterPokecenter1F_Johto_PewterPokecenter1FBugCatcherScript:
	faceplayer
	message PewterPokecenter1F_Johto_PewterPokecenter1FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterPokecenter1F_Johto_Chris:
	faceplayer
	goto Johto_Std_Trade_CHRIS

PewterPokecenter1F_Johto_PewterPokecenter1FTeacherText:
	.string "…Yeah, and the\n"
	.string "GYM in CINNABAR's"
	.string "\pgone. I was really\n"
	.string "amazed."
	.string "\p…Yes? I'm on the\n"
	.string "phone. Go away!$"

PewterPokecenter1F_Johto_PewterJigglypuffText:
	.string "JIGGLYPUFF: Puu\n"
	.string "pupuu.$"

PewterPokecenter1F_Johto_PewterPokecenter1FBugCatcherText:
	.string "Most POKéMON get\n"
	.string "drowsy if they"
	.string "\phear a JIGGLYPUFF\n"
	.string "singing."
	.string "\pThere are several\n"
	.string "moves that can be"
	.string "\pused only while a\n"
	.string "POKéMON is asleep.$"
