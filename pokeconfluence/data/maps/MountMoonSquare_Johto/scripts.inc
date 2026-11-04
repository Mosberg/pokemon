MountMoonSquare_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MountMoonSquare_Johto_OnTransition
	.byte 0

MountMoonSquare_Johto_OnTransition:
	call MountMoonSquare_Johto_MountMoonSquareDisappearMoonStoneCallback_Cb
	call MountMoonSquare_Johto_MountMoonSquareDisappearRockCallback_Cb
	end

MountMoonSquare_Johto_MtMoonSquareRock_Entry::
	lockall
	goto MountMoonSquare_Johto_MtMoonSquareRock

MountMoonSquare_Johto_DontLitterSign_Entry::
	lockall
	goto MountMoonSquare_Johto_DontLitterSign

MountMoonSquare_Johto_ClefairyDance_Entry::
	lockall
	goto MountMoonSquare_Johto_ClefairyDance


MountMoonSquare_Johto_ClefairyDance:
	goto_if_set FLAG_JOHTO_ENGINE_MT_MOON_SQUARE_CLEFAIRY, MountMoonSquare_Johto_ClefairyDance_NoDancing
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 1, MountMoonSquare_Johto_ClefairyDance_NoDancing
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_eq VAR_RESULT, 0, MountMoonSquare_Johto_ClefairyDance_NoDancing
	clearflag FLAG_JOHTO_MT_MOON_SQUARE_CLEFAIRY
	addobject 1
	clearflag FLAG_JOHTO_MT_MOON_SQUARE_CLEFAIRY
	addobject 2
	applymovement OBJ_EVENT_ID_PLAYER, MountMoonSquare_Johto_PlayerWalksUpToDancingClefairies
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	clearflag FLAG_JOHTO_MT_MOON_SQUARE_ROCK
	addobject 3
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	waitse
	delay 30
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep1
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep1
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep2
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep2
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep3
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep3
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep4
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep4
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep5
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep5
	waitmovement 1
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep6
	waitmovement 2
	applymovement 2, MountMoonSquare_Johto_ClefairyDanceStep7
	applymovement 1, MountMoonSquare_Johto_ClefairyDanceStep7
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 10
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	applymovement 2, MountMoonSquare_Johto_ClefairyFleeMovement
	applymovement 1, MountMoonSquare_Johto_ClefairyFleeMovement
	waitmovement 1
	removeobject 1
	removeobject 2
	clearflag FLAG_JOHTO_MOUNT_MOON_SQUARE_HIDDEN_MOON_STONE
	setflag FLAG_JOHTO_ENGINE_MT_MOON_SQUARE_CLEFAIRY
	releaseall
	end

MountMoonSquare_Johto_ClefairyDance_NoDancing:
	releaseall
	end

MountMoonSquare_Johto_DontLitterSign:
	message MountMoonSquare_Johto_DontLitterSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMoonSquare_Johto_MtMoonSquareRock:
	goto Johto_Std_SmashRockScript

MountMoonSquare_Johto_MountMoonSquareDisappearMoonStoneCallback_Cb:
	setflag FLAG_JOHTO_MOUNT_MOON_SQUARE_HIDDEN_MOON_STONE
	return

MountMoonSquare_Johto_MountMoonSquareDisappearRockCallback_Cb:
	setflag FLAG_JOHTO_MT_MOON_SQUARE_ROCK
	return

MountMoonSquare_Johto_PlayerWalksUpToDancingClefairies:
	walk_up
	step_end

MountMoonSquare_Johto_ClefairyDanceStep1:
	walk_slow_down
	step_end

MountMoonSquare_Johto_ClefairyDanceStep2:
	step_end

MountMoonSquare_Johto_ClefairyDanceStep3:
	walk_slow_up
	step_end

MountMoonSquare_Johto_ClefairyDanceStep4:
	step_end

MountMoonSquare_Johto_ClefairyDanceStep5:
	walk_slow_down
	step_end

MountMoonSquare_Johto_ClefairyDanceStep6:
	walk_slow_down
	step_end

MountMoonSquare_Johto_ClefairyDanceStep7:
	walk_slow_right
	step_end

MountMoonSquare_Johto_ClefairyFleeMovement:
	walk_right
	walk_right
	walk_right
	jump_right
	walk_right
	walk_right
	step_end

MountMoonSquare_Johto_DontLitterSignText:
	.string "MT.MOON SQUARE\n"
	.string "DON'T LITTER$"
