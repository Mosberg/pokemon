SlowpokeWellB2F_Johto_MapScripts::
	.byte 0

SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript_Entry::
	lockall
	goto SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript

SlowpokeWellB2F_Johto_SlowpokeWellB2FTMRainDance_Entry::
	lockall
	goto SlowpokeWellB2F_Johto_SlowpokeWellB2FTMRainDance


SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL, SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript_GotKingsRock
	message SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideText
	waitmessage
	waitbuttonpress
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, 0, SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript_NoRoom
	setflag FLAG_JOHTO_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL

SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript_NoRoom:
	closemessage
	releaseall
	end

SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideScript_GotKingsRock:
	message SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideText_GotKingsRock
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB2F_Johto_SlowpokeWellB2FTMRainDance:
	finditem ITEM_TM_RAIN_DANCE
	releaseall
	end

SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideText:
	.string "I'm waiting to see\n"
	.string "SLOWPOKE's moment\l"
	.string "of evolution."
	.string "\pThrough observa-\n"
	.string "tion, I made a new\l"
	.string "discovery."
	.string "\pA SLOWPOKE with a\n"
	.string "KING'S ROCK often"
	.string "\pgets bitten by a\n"
	.string "SHELLDER."
	.string "\pHere, I'll share a\n"
	.string "KING'S ROCK with\l"
	.string "you.$"

SlowpokeWellB2F_Johto_SlowpokeWellB2FGymGuideText_GotKingsRock:
	.string "I'm going to be\n"
	.string "like SLOWPOKE."
	.string "\pI'll wait patient-\n"
	.string "ly, so I can see\l"
	.string "one evolve.$"
