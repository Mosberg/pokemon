BurnedTowerB1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BurnedTowerB1F_Johto_OnLoad
	.byte 0

BurnedTowerB1F_Johto_OnLoad:
	call BurnedTowerB1F_Johto_BurnedTowerB1FLadderCallback_Cb
	end

BurnedTowerB1F_Johto_BurnedTowerB1FBoulder_Entry::
	lockall
	goto BurnedTowerB1F_Johto_BurnedTowerB1FBoulder

BurnedTowerB1F_Johto_BurnedTowerB1FTMEndure_Entry::
	lockall
	goto BurnedTowerB1F_Johto_BurnedTowerB1FTMEndure

BurnedTowerB1F_Johto_BurnedTowerB1FEusine_Entry::
	lockall
	goto BurnedTowerB1F_Johto_BurnedTowerB1FEusine

BurnedTowerB1F_Johto_ReleaseTheBeasts_Entry::
	lockall
	goto BurnedTowerB1F_Johto_ReleaseTheBeasts


BurnedTowerB1F_Johto_ReleaseTheBeasts:
	playbgm MUS_DUMMY, FALSE
	delay 30
	clearflag FLAG_JOHTO_BURNED_TOWER_B1F_BEASTS_1
	addobject 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	removeobject 5
	delay 15
	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	waitmoncry
	clearflag FLAG_JOHTO_BURNED_TOWER_B1F_BEASTS_1
	addobject 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	removeobject 6
	delay 15
	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	waitmoncry
	clearflag FLAG_JOHTO_BURNED_TOWER_B1F_BEASTS_1
	addobject 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	removeobject 7
	delay 15
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	playse SE_WARP_OUT
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 2, BurnedTowerB1F_Johto_BurnedTowerRaikouMovement
	waitmovement 2
	removeobject 2
	waitse
	playse SE_WARP_OUT
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, BurnedTowerB1F_Johto_BurnedTowerEnteiMovement
	waitmovement 3
	removeobject 3
	waitse
	delay 15
	playse SE_WARP_OUT
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement1
	waitmovement 4
	playse SE_WARP_OUT
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement2
	waitmovement 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 20
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 30
	playse SE_WARP_OUT
	applymovement 4, BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement3
	waitmovement 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	removeobject 4
	waitse
	fadedefaultbgm
	setvar VAR_JOHTO_SCENE_BURNED_TOWER_B1F, 1
	setflag FLAG_JOHTO_RELEASED_THE_BEASTS
	special InitJohtoRoamMons
	setvar VAR_JOHTO_SCENE_ECRUTEAK_GYM, 1
	setvar VAR_JOHTO_SCENE_CIANWOOD_CITY, 1
	clearflag FLAG_JOHTO_SAW_SUICUNE_AT_CIANWOOD_CITY
	setflag FLAG_JOHTO_ECRUTEAK_GYM_GRAMPS
	clearflag FLAG_JOHTO_ECRUTEAK_CITY_GRAMPS
	setflag FLAG_JOHTO_BURNED_TOWER_MORTY
	setflag FLAG_JOHTO_BURNED_TOWER_1F_EUSINE
	clearflag FLAG_JOHTO_EUSINE_IN_BURNED_TOWER
	addobject 9
	setmetatile 6, 14, 513, 0
	setmetatile 7, 14, 513, 0
	setmetatile 6, 15, 513, 0
	setmetatile 7, 15, 534, 0
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_BURNED_TOWER_B1F, 1
	releaseall
	end

BurnedTowerB1F_Johto_BurnedTowerB1FEusine:
	faceplayer
	message BurnedTowerB1F_Johto_BurnedTowerB1FEusineText
	waitmessage
	waitbuttonpress
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, BurnedTowerB1F_Johto_BurnedTowerB1FEusine_Movement2
	applymovement 9, BurnedTowerB1F_Johto_BurnedTowerB1FEusineMovement1
	waitmovement 9
	goto BurnedTowerB1F_Johto_BurnedTowerB1FEusine_Finish

BurnedTowerB1F_Johto_BurnedTowerB1FEusine_Movement2:
	applymovement 9, BurnedTowerB1F_Johto_BurnedTowerB1FEusineMovement2
	waitmovement 9

BurnedTowerB1F_Johto_BurnedTowerB1FEusine_Finish:
	removeobject 9
	playse SE_EXIT
	waitse
	releaseall
	end

BurnedTowerB1F_Johto_BurnedTowerB1FTMEndure:
	finditem ITEM_TM_SAFEGUARD
	releaseall
	end

BurnedTowerB1F_Johto_BurnedTowerB1FBoulder:
	goto Johto_Std_StrengthBoulderScript

BurnedTowerB1F_Johto_BurnedTowerB1FLadderCallback_Cb:
	goto_if_set FLAG_JOHTO_RELEASED_THE_BEASTS, BurnedTowerB1F_Johto_BurnedTowerB1FLadderCallback_HideLadder_Cb
	setmetatile 6, 14, 513, 0
	setmetatile 7, 14, 513, 0
	setmetatile 6, 15, 513, 0
	setmetatile 7, 15, 513, 0
	special DrawWholeMapView

BurnedTowerB1F_Johto_BurnedTowerB1FLadderCallback_HideLadder_Cb:
	return

BurnedTowerB1F_Johto_BurnedTowerRaikouMovement:
	jump_down
	jump_left
	step_end

BurnedTowerB1F_Johto_BurnedTowerEnteiMovement:
	jump_right
	jump_down
	jump_right
	step_end

BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement1:
	jump_right
	jump_down
	jump_down
	jump_left
	step_end

BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement2:
	jump_left
	jump_up
	walk_fast_up
	jump_right
	step_end

BurnedTowerB1F_Johto_BurnedTowerSuicuneMovement3:
	walk_fast_up
	jump_right
	jump_down
	jump_down
	jump_down
	jump_down
	step_end

BurnedTowerB1F_Johto_BurnedTowerB1FEusineMovement2:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_down
	step_end

BurnedTowerB1F_Johto_BurnedTowerB1FEusineMovement1:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

BurnedTowerB1F_Johto_BurnedTowerB1FEusineText:
	.string "EUSINE: I dug a\n"
	.string "hole here, too…"
	.string "\pI was shocked!"
	.string "\pSUICUNE raced by\n"
	.string "like a blur, right"
	.string "\pin front of my\n"
	.string "eyes!"
	.string "\pFor ten years I\n"
	.string "chased SUICUNE,"
	.string "\pand I finally got\n"
	.string "to see it."
	.string "\pI'm all choked up!"
	.string "\p{PLAYER}, I owe\n"
	.string "this all to you!"
	.string "\pThank you!"
	.string "\pI heard that the\n"
	.string "legendary POKéMON"
	.string "\pof ECRUTEAK test\n"
	.string "chosen humans by"
	.string "\pallowing them to\n"
	.string "get close."
	.string "\pI'm going to track\n"
	.string "SUICUNE."
	.string "\p{PLAYER}, let's\n"
	.string "meet again!"
	.string "\pFarewell!$"
