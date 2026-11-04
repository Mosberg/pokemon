VioletPokecenter1F_Johto_MapScripts::
	.byte 0

VioletPokecenter1F_Johto_VioletPokecenterNurse_Entry::
	lockall
	goto VioletPokecenter1F_Johto_VioletPokecenterNurse

VioletPokecenter1F_Johto_VioletPokecenter1FGameboyKidScript_Entry::
	lockall
	goto VioletPokecenter1F_Johto_VioletPokecenter1FGameboyKidScript

VioletPokecenter1F_Johto_VioletPokecenter1FGentlemanScript_Entry::
	lockall
	goto VioletPokecenter1F_Johto_VioletPokecenter1FGentlemanScript

VioletPokecenter1F_Johto_VioletPokecenter1FYoungsterScript_Entry::
	lockall
	goto VioletPokecenter1F_Johto_VioletPokecenter1FYoungsterScript

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_Entry::
	lockall
	goto VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript


VioletPokecenter1F_Johto_VioletPokecenterNurse:
	setrespawn HEAL_LOCATION_JOHTO_VIOLET_CITY
	goto Johto_Std_PokecenterNurseScript

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE, VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_SecondTimeAsking
	message VioletPokecenter1F_Johto_VioletPokecenterElmsAideFavorText
	waitmessage

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AskTakeEgg:
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_RefusedEgg
	getpartysize
	goto_if_eq VAR_RESULT, 6, VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_PartyFull
	givemon SPECIES_TOGEPI, 5, isEgg=TRUE
	bufferstring STR_VAR_2, VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_eggname
	call VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AideGivesEgg_Sub
	setflag FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE
	clearflag FLAG_JOHTO_ELMS_AIDE_IN_LAB
	clearflag FLAG_JOHTO_TOGEPI_HATCHED
	setvar VAR_JOHTO_SCENE_ROUTE_32, 1
	message VioletPokecenter1F_Johto_VioletPokecenterElmsAideGiveEggText
	waitmessage
	waitbuttonpress
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AideWalksAroundPlayer
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 5, VioletPokecenter1F_Johto_MovementData_AideWalksStraightOutOfPokecenter
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AideWalksAroundPlayer:
	applymovement 5, VioletPokecenter1F_Johto_MovementData_AideWalksLeftToExitPokecenter
	waitmovement 5
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 5, VioletPokecenter1F_Johto_MovementData_AideFinishesLeavingPokecenter
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_PartyFull:
	message VioletPokecenter1F_Johto_VioletCityElmsAideFullPartyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_RefusedEgg:
	message VioletPokecenter1F_Johto_VioletPokecenterElmsAideRefuseText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_SecondTimeAsking:
	message VioletPokecenter1F_Johto_VioletPokecenterElmsAideAskEggText
	waitmessage
	goto VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AskTakeEgg

VioletPokecenter1F_Johto_VioletPokecenter1FGameboyKidScript:
	faceplayer
	message VioletPokecenter1F_Johto_VioletPokecenter1FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1FGentlemanScript:
	faceplayer
	message VioletPokecenter1F_Johto_VioletPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1FYoungsterScript:
	faceplayer
	message VioletPokecenter1F_Johto_VioletPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_AideGivesEgg_Sub:
	goto Johto_Std_ReceiveTogepiEggScript_Sub

VioletPokecenter1F_Johto_VioletPokecenter1F_ElmsAideScript_eggname:
	.string "EGG$"

VioletPokecenter1F_Johto_MovementData_AideWalksStraightOutOfPokecenter:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VioletPokecenter1F_Johto_MovementData_AideWalksLeftToExitPokecenter:
	walk_left
	walk_down
	step_end

VioletPokecenter1F_Johto_MovementData_AideFinishesLeavingPokecenter:
	walk_down
	walk_down
	walk_down
	step_end

VioletPokecenter1F_Johto_VioletPokecenterElmsAideFavorText:
	.string "{PLAYER}, long\n"
	.string "time, no see."
	.string "\pPROF.ELM asked me\n"
	.string "to find you."
	.string "\pHe has another\n"
	.string "favor to ask."
	.string "\pWould you take the\n"
	.string "POKéMON EGG?$"

VioletPokecenter1F_Johto_VioletPokecenterElmsAideGiveEggText:
	.string "We discovered that\n"
	.string "a POKéMON will not"
	.string "\phatch until it\n"
	.string "grows in the EGG."
	.string "\pIt also has to be\n"
	.string "with other active\l"
	.string "POKéMON to hatch."
	.string "\p{PLAYER}, you're\n"
	.string "the only person\l"
	.string "we can rely on."
	.string "\pPlease call PROF.\n"
	.string "ELM when that EGG\l"
	.string "hatches!$"

VioletPokecenter1F_Johto_VioletCityElmsAideFullPartyText:
	.string "Oh, no. You can't\n"
	.string "carry any more\l"
	.string "POKéMON with you."
	.string "\pI'll wait here\n"
	.string "while you make\l"
	.string "room for the EGG.$"

VioletPokecenter1F_Johto_VioletPokecenterElmsAideRefuseText:
	.string "B-but… PROF.ELM\n"
	.string "asked for you…$"

VioletPokecenter1F_Johto_VioletPokecenterElmsAideAskEggText:
	.string "{PLAYER}, will you\n"
	.string "take the EGG?$"

VioletPokecenter1F_Johto_VioletPokecenter1FGameboyKidText:
	.string "A guy named BILL\n"
	.string "made the POKéMON\l"
	.string "PC storage system.$"

VioletPokecenter1F_Johto_VioletPokecenter1FGentlemanText:
	.string "It was around\n"
	.string "three years ago."
	.string "\pTEAM ROCKET was up\n"
	.string "to no good with\l"
	.string "POKéMON."
	.string "\pBut justice pre-\n"
	.string "vailed--a young\l"
	.string "kid broke 'em up.$"

VioletPokecenter1F_Johto_VioletPokecenter1FYoungsterText:
	.string "POKéMON are smart.\n"
	.string "They won't obey a"
	.string "\ptrainer they don't\n"
	.string "respect."
	.string "\pWithout the right\n"
	.string "GYM BADGES, they"
	.string "\pwill just do as\n"
	.string "they please.$"
