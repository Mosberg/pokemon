VermilionPokecenter1F_Johto_MapScripts::
	.byte 0

VermilionPokecenter1F_Johto_VermilionPokecenter1FNurseScript_Entry::
	lockall
	goto VermilionPokecenter1F_Johto_VermilionPokecenter1FNurseScript

VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruScript_Entry::
	lockall
	goto VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruScript

VermilionPokecenter1F_Johto_VermilionPokecenter1FSailorScript_Entry::
	lockall
	goto VermilionPokecenter1F_Johto_VermilionPokecenter1FSailorScript

VermilionPokecenter1F_Johto_VermilionPokecenter1FBugCatcherScript_Entry::
	lockall
	goto VermilionPokecenter1F_Johto_VermilionPokecenter1FBugCatcherScript


VermilionPokecenter1F_Johto_VermilionPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_VERMILION_CITY
	goto Johto_Std_PokecenterNurseScript

VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FOUGHT_SNORLAX, VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruScript_FoughtSnorlax
	message VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruScript_FoughtSnorlax:
	message VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruText_FoughtSnorlax
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPokecenter1F_Johto_VermilionPokecenter1FSailorScript:
	faceplayer
	message VermilionPokecenter1F_Johto_VermilionPokecenter1FSailorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPokecenter1F_Johto_VermilionPokecenter1FBugCatcherScript:
	faceplayer
	message VermilionPokecenter1F_Johto_VermilionPokecenter1FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruText:
	.string "A sleeping POKéMON\n"
	.string "is lying in front\l"
	.string "of DIGLETT'S CAVE."
	.string "\pIt's a fantastic\n"
	.string "opportunity to get"
	.string "\pit, but how do you\n"
	.string "wake it up?$"

VermilionPokecenter1F_Johto_VermilionPokecenter1FFishingGuruText_FoughtSnorlax:
	.string "There used to be a\n"
	.string "sleeping POKéMON"
	.string "\plying in front of\n"
	.string "DIGLETT'S CAVE."
	.string "\pBut it seems to\n"
	.string "have disappeared.$"

VermilionPokecenter1F_Johto_VermilionPokecenter1FSailorText:
	.string "The FAST SHIP is a\n"
	.string "great place to"
	.string "\pmeet and battle\n"
	.string "trainers.$"

VermilionPokecenter1F_Johto_VermilionPokecenter1FBugCatcherText:
	.string "Oh? You have some\n"
	.string "BADGES I've never\l"
	.string "seen before."
	.string "\pOh, I get it. You\n"
	.string "got them in JOHTO.$"
