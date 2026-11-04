MahoganyMart1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MahoganyMart1F_Johto_OnFrame
	.byte 0

MahoganyMart1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_MAHOGANY_MART_1F, 1, MahoganyMart1F_Johto_MahoganyMart1FLanceUncoversStaircaseScript_Entry
	.2byte 0

MahoganyMart1F_Johto_MahoganyMart1FPharmacistScript_Entry::
	lockall
	goto MahoganyMart1F_Johto_MahoganyMart1FPharmacistScript

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltScript_Entry::
	lockall
	goto MahoganyMart1F_Johto_MahoganyMart1FBlackBeltScript

MahoganyMart1F_Johto_MahoganyMart1FGrannyScript_Entry::
	lockall
	goto MahoganyMart1F_Johto_MahoganyMart1FGrannyScript

MahoganyMart1F_Johto_MahoganyMart1FLanceUncoversStaircaseScript_Entry::
	lockall
	goto MahoganyMart1F_Johto_MahoganyMart1FLanceUncoversStaircaseScript


MahoganyMart1F_Johto_MahoganyMart1FPharmacistScript:
	faceplayer
	goto_if_set FLAG_JOHTO_DECIDED_TO_HELP_LANCE, MahoganyMart1F_Johto_MahoganyMart1FPharmacistScript_LanceEntered
	pokemart Johto_Mart_MAHOGANY_1
	closemessage
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FPharmacistScript_LanceEntered:
	message MahoganyMart1F_Johto_MahoganyMart1FPharmacistText_LanceEntered
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltScript:
	faceplayer
	goto_if_set FLAG_JOHTO_DECIDED_TO_HELP_LANCE, MahoganyMart1F_Johto_MahoganyMart1FBlackBeltScript_LanceEntered
	message MahoganyMart1F_Johto_MahoganyMart1FBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltScript_LanceEntered:
	message MahoganyMart1F_Johto_MahoganyMart1FBlackBeltText_LanceEntered
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FLanceUncoversStaircaseScript:
	delay 15
	message MahoganyMart1F_Johto_MahoganyMart1FLanceDragoniteHyperBeamText
	waitmessage
	delay 15
	closemessage
	playse SE_M_TAIL_WHIP
	applymovement 4, MahoganyMart1F_Johto_MahoganyMart1FDragoniteTackleMovement
	waitmovement 4
	applymovement 2, MahoganyMart1F_Johto_MahoganyMart1FBlackBeltKnockedBackMovement
	waitmovement 2
	delay 15
	removeobject 4
	delay 15
	applymovement 3, MahoganyMart1F_Johto_MahoganyMart1FLanceApproachPlayerMovement
	waitmovement 3
	message MahoganyMart1F_Johto_MahoganyMart1FLanceRadioText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyMart1F_Johto_MahoganyMart1FLanceApproachPharmacistMovement
	applymovement 3, MahoganyMart1F_Johto_MahoganyMart1FLanceApproachPharmacistMovement
	waitmovement 3
	applymovement 1, MahoganyMart1F_Johto_MahoganyMart1FPharmacistShovedAsideMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyMart1F_Johto_MahoganyMart1FLanceApproachHiddenStairsMovement
	applymovement 3, MahoganyMart1F_Johto_MahoganyMart1FLanceApproachHiddenStairsMovement
	waitmovement 3
	message MahoganyMart1F_Johto_MahoganyMart1FLanceStairsText
	waitmessage
	waitbuttonpress
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	playse SE_PIN
	setmetatile 6, 2, 548, 0
	setmetatile 7, 2, 521, 0
	setmetatile 6, 3, 521, 0
	setmetatile 7, 3, 549, 0
	special DrawWholeMapView
	closemessage
	setflag FLAG_JOHTO_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART
	applymovement 3, Johto_Movement_Face_Left
	waitmovement 3
	message MahoganyMart1F_Johto_MahoganyMart1FLanceSplitUpText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, MahoganyMart1F_Johto_MahoganyMart1FLanceGoDownStairsMovement
	waitmovement 3
	playse SE_EXIT
	removeobject 3
	setvar VAR_JOHTO_SCENE_MAHOGANY_MART_1F, 0
	waitse
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FGrannyScript:
	faceplayer
	pokemart Johto_Mart_MAHOGANY_2
	closemessage
	releaseall
	end

MahoganyMart1F_Johto_MahoganyMart1FDragoniteTackleMovement:
	lock_facing_direction
	walk_fast_left
	walk_fast_right
	unlock_facing_direction
	step_end

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltKnockedBackMovement:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_down
	face_left
	face_up
	face_right
	step_end

MahoganyMart1F_Johto_MahoganyMart1FPharmacistShovedAsideMovement:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

MahoganyMart1F_Johto_MahoganyMart1FLanceApproachPlayerMovement:
	walk_slow_left
	face_down
	step_end

MahoganyMart1F_Johto_MahoganyMart1FLanceApproachPharmacistMovement:
	walk_slow_right
	walk_slow_up
	walk_slow_up
	step_end

MahoganyMart1F_Johto_MahoganyMart1FLanceApproachHiddenStairsMovement:
	walk_slow_up
	walk_slow_right
	walk_slow_right
	step_end

MahoganyMart1F_Johto_MahoganyMart1FLanceGoDownStairsMovement:
	walk_slow_right
	step_end

MahoganyMart1F_Johto_MahoganyMart1FPharmacistText_LanceEntered:
	.string "Arrgh… You found\n"
	.string "the secret stair-\l"
	.string "way…$"

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltText:
	.string "Heheh! The experi-\n"
	.string "ment worked like a\l"
	.string "charm."
	.string "\pMAGIKARP are just\n"
	.string "worthless, but"
	.string "\pGYARADOS are big\n"
	.string "moneymakers.$"

MahoganyMart1F_Johto_MahoganyMart1FBlackBeltText_LanceEntered:
	.string "Urrgh…"
	.string "\pThat guy's dragon\n"
	.string "POKéMON are tough…$"

MahoganyMart1F_Johto_MahoganyMart1FLanceDragoniteHyperBeamText:
	.string "LANCE: DRAGONITE,\n"
	.string "HYPER BEAM.$"

MahoganyMart1F_Johto_MahoganyMart1FLanceRadioText:
	.string "What took you,\n"
	.string "{PLAYER}?"
	.string "\pJust as I thought,\n"
	.string "that strange radio"
	.string "\psignal is coming\n"
	.string "from here.$"

MahoganyMart1F_Johto_MahoganyMart1FLanceStairsText:
	.string "The stairs are\n"
	.string "right here.$"

MahoganyMart1F_Johto_MahoganyMart1FLanceSplitUpText:
	.string "LANCE: {PLAYER}, we\n"
	.string "should split up to"
	.string "\pcheck this place.\n"
	.string "I'll go first.$"
