CianwoodPokecenter1F_Johto_MapScripts::
	.byte 0

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FNurseScript_Entry::
	lockall
	goto CianwoodPokecenter1F_Johto_CianwoodPokecenter1FNurseScript

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FLassScript_Entry::
	lockall
	goto CianwoodPokecenter1F_Johto_CianwoodPokecenter1FLassScript

CianwoodPokecenter1F_Johto_CianwoodGymGuideScript_Entry::
	lockall
	goto CianwoodPokecenter1F_Johto_CianwoodGymGuideScript

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FSuperNerdScript_Entry::
	lockall
	goto CianwoodPokecenter1F_Johto_CianwoodPokecenter1FSuperNerdScript


CianwoodPokecenter1F_Johto_CianwoodPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_CIANWOOD_CITY
	goto Johto_Std_PokecenterNurseScript

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FLassScript:
	faceplayer
	message CianwoodPokecenter1F_Johto_CianwoodPokecenter1FLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPokecenter1F_Johto_CianwoodGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_CHUCK, CianwoodPokecenter1F_Johto_CianwoodGymGuideScript_CianwoodGymGuideWinScript
	message CianwoodPokecenter1F_Johto_CianwoodGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPokecenter1F_Johto_CianwoodGymGuideScript_CianwoodGymGuideWinScript:
	message CianwoodPokecenter1F_Johto_CianwoodGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FSuperNerdScript:
	faceplayer
	message CianwoodPokecenter1F_Johto_CianwoodPokecenter1FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FLassText:
	.string "Did you meet the\n"
	.string "POKéMANIAC?"
	.string "\pHe's always brag-\n"
	.string "ging about his\l"
	.string "rare POKéMON.$"

CianwoodPokecenter1F_Johto_CianwoodGymGuideText:
	.string "The POKéMON GYM\n"
	.string "trainers here are\l"
	.string "macho bullies."
	.string "\pIf I stick around,\n"
	.string "they might come\l"
	.string "after me."
	.string "\pHere's some ad-\n"
	.string "vice: the GYM"
	.string "\pLEADER uses the\n"
	.string "fighting-type."
	.string "\pSo you should\n"
	.string "confound him with\l"
	.string "psychic POKéMON."
	.string "\pWipe out his POKé-\n"
	.string "MON before they"
	.string "\pcan use their\n"
	.string "physical strength."
	.string "\pAnd those boulders\n"
	.string "in the middle of\l"
	.string "the GYM?"
	.string "\pIf you don't move\n"
	.string "them correctly,"
	.string "\pyou won't reach\n"
	.string "the GYM LEADER."
	.string "\pIf you get stuck,\n"
	.string "go outside.$"

CianwoodPokecenter1F_Johto_CianwoodGymGuideWinText:
	.string "{PLAYER}! You won!\n"
	.string "I could tell by\l"
	.string "looking at you!$"

CianwoodPokecenter1F_Johto_CianwoodPokecenter1FSuperNerdText:
	.string "I love showing off\n"
	.string "the POKéMON that"
	.string "\pI've raised.\n"
	.string "Don't you?"
	.string "\pI'm going to get\n"
	.string "into a bunch of"
	.string "\pbattles, and show\n"
	.string "off my POKéMON!$"
