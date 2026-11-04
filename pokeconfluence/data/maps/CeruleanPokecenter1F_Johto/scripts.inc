CeruleanPokecenter1F_Johto_MapScripts::
	.byte 0

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FNurseScript_Entry::
	lockall
	goto CeruleanPokecenter1F_Johto_CeruleanPokecenter1FNurseScript

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdScript_Entry::
	lockall
	goto CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdScript

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideScript_Entry::
	lockall
	goto CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideScript


CeruleanPokecenter1F_Johto_CeruleanPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_CERULEAN_CITY
	goto Johto_Std_PokecenterNurseScript

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdScript:
	@ TODO unsupported: special CheckMobileAdapterStatusSpecial
	goto Johto_EventScript_Unimplemented

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideScript:
	faceplayer
	message CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideText:
	.string "The MAGNET TRAIN\n"
	.string "travels at over"
	.string "\p340 mph. It goes\n"
	.string "between KANTO and"
	.string "\pJOHTO in almost no\n"
	.string "time at all."
	.string "\pIt really makes\n"
	.string "JOHTO accessible.$"
