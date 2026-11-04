OlivinePokecenter1F_Johto_MapScripts::
	.byte 0

OlivinePokecenter1F_Johto_OlivinePokecenter1FNurseScript_Entry::
	lockall
	goto OlivinePokecenter1F_Johto_OlivinePokecenter1FNurseScript

OlivinePokecenter1F_Johto_OlivinePokecenter1FFishingGuruScript_Entry::
	lockall
	goto OlivinePokecenter1F_Johto_OlivinePokecenter1FFishingGuruScript

OlivinePokecenter1F_Johto_OlivinePokecenter1FFisherScript_Entry::
	lockall
	goto OlivinePokecenter1F_Johto_OlivinePokecenter1FFisherScript

OlivinePokecenter1F_Johto_OlivinePokecenter1FTeacherScript_Entry::
	lockall
	goto OlivinePokecenter1F_Johto_OlivinePokecenter1FTeacherScript


OlivinePokecenter1F_Johto_OlivinePokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_OLIVINE_CITY
	goto Johto_Std_PokecenterNurseScript

OlivinePokecenter1F_Johto_OlivinePokecenter1FFishingGuruScript:
	goto Johto_Std_HappinessCheckScript

OlivinePokecenter1F_Johto_OlivinePokecenter1FFisherScript:
	faceplayer
	message OlivinePokecenter1F_Johto_OlivinePokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePokecenter1F_Johto_OlivinePokecenter1FTeacherScript:
	faceplayer
	message OlivinePokecenter1F_Johto_OlivinePokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePokecenter1F_Johto_OlivinePokecenter1FFisherText:
	.string "The SAILOR in the\n"
	.string "OLIVINE CAFE next"
	.string "\pdoor is really\n"
	.string "generous."
	.string "\pHe taught my\n"
	.string "POKéMON STRENGTH."
	.string "\pNow it can move\n"
	.string "big boulders.$"

OlivinePokecenter1F_Johto_OlivinePokecenter1FTeacherText:
	.string "There's a person\n"
	.string "in CIANWOOD CITY\l"
	.string "across the sea."
	.string "\pI heard him brag-\n"
	.string "ging about his\l"
	.string "rare POKéMON.$"
