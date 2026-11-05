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
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdScript_mobile
	faceplayer
	message CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdScript_mobile:
	faceplayer
	message CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdText_Mobile
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideScript:
	faceplayer
	message CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdText:
	.string "For battles, I'd\n"
	.string "much rather use"
	.string "\pPOKéMON I've been\n"
	.string "raising, even if"
	.string "\pthey're weaker\n"
	.string "than some newly\l"
	.string "caught POKéMON.$"

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FSuperNerdText_Mobile:
	.string "Do you battle by\n"
	.string "mobile phone?"
	.string "\pIf time runs out\n"
	.string "during a battle,"
	.string "\pwaiting to see who\n"
	.string "won is really\l"
	.string "nerve wracking.$"

CeruleanPokecenter1F_Johto_CeruleanPokecenter1FGymGuideText:
	.string "The MAGNET TRAIN\n"
	.string "travels at over"
	.string "\p340 mph. It goes\n"
	.string "between KANTO and"
	.string "\pJOHTO in almost no\n"
	.string "time at all."
	.string "\pIt really makes\n"
	.string "JOHTO accessible.$"
