Route43Gate_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43Gate_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route43Gate_Johto_OnFrame
	.byte 0

Route43Gate_Johto_OnTransition:
	call Route43Gate_Johto_Route43GateCheckIfRocketsCallback_Cb
	end

Route43Gate_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ROUTE_43_GATE, 0, Route43Gate_Johto_Route43GateRocketTakeoverScript_Entry
	.2byte 0

Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb_Entry::
	lockall
	goto Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb

Route43Gate_Johto_RocketScript_MakingABundle_Entry::
	lockall
	goto Route43Gate_Johto_RocketScript_MakingABundle

Route43Gate_Johto_Route43GateRocketTakeoverScript_Entry::
	lockall
	goto Route43Gate_Johto_Route43GateRocketTakeoverScript


Route43Gate_Johto_Route43GateRocketTakeoverScript:
	playbgm MUS_DUMMY, FALSE
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, Route43Gate_Johto_RocketScript_Southbound
	goto_if_eq VAR_RESULT, DIR_NORTH, Route43Gate_Johto_RocketScript_Northbound
	setvar VAR_JOHTO_SCENE_ROUTE_43_GATE, 1
	releaseall
	end

Route43Gate_Johto_RocketScript_Southbound:
	applymovement OBJ_EVENT_ID_PLAYER, Route43Gate_Johto_PlayerStepsIn
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	applymovement 3, Route43Gate_Johto_Rocket2Script_BlocksYouSouth
	waitmovement 3
	applymovement 2, Johto_Movement_Face_Up
	waitmovement 2
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 2, Route43Gate_Johto_Rocket1Script_BlocksYouSouth
	waitmovement 2
	message Route43Gate_Johto_RocketText_TollFee
	waitmessage
	waitbuttonpress
	@ TODO unsupported: checkmoney YOUR_MONEY, ROUTE43GATE_TOLL - 1
	goto Johto_EventScript_Unimplemented

Route43Gate_Johto_RocketScript_Northbound:
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 2, Route43Gate_Johto_Rocket1Script_BlocksYouNorth
	waitmovement 2
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	applymovement 3, Route43Gate_Johto_Rocket2Script_BlocksYouNorth
	waitmovement 3
	message Route43Gate_Johto_RocketText_TollFee
	waitmessage
	waitbuttonpress
	@ TODO unsupported: checkmoney YOUR_MONEY, ROUTE43GATE_TOLL - 1
	goto Johto_EventScript_Unimplemented

Route43Gate_Johto_RocketScript_MakingABundle:
	faceplayer
	message Route43Gate_Johto_RocketText_MakingABundle
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM36_SLUDGE_BOMB, Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb_GotSludgeBomb
	message Route43Gate_Johto_OfficerText_FoundTM
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, 0, Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb_NoRoomForSludgeBomb
	setflag FLAG_JOHTO_GOT_TM36_SLUDGE_BOMB
	closemessage
	releaseall
	end

Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb_GotSludgeBomb:
	message Route43Gate_Johto_OfficerText_AvoidGrass
	waitmessage
	waitbuttonpress

Route43Gate_Johto_OfficerScript_GuardWithSludgeBomb_NoRoomForSludgeBomb:
	closemessage
	releaseall
	end

Route43Gate_Johto_Route43GateCheckIfRocketsCallback_Cb:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, Route43Gate_Johto_Route43GateCheckIfRocketsCallback_NoRockets_Cb
	@ TODO unsupported: setmapscene ROUTE_43, 0
	return

Route43Gate_Johto_Route43GateCheckIfRocketsCallback_NoRockets_Cb:
	@ TODO unsupported: setmapscene ROUTE_43, 1
	return

Route43Gate_Johto_PlayerStepsIn:
	walk_down
	step_end

Route43Gate_Johto_Rocket1Script_BlocksYouSouth:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	face_up
	step_end

Route43Gate_Johto_Rocket1Script_BlocksYouNorth:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	face_down
	step_end

Route43Gate_Johto_Rocket2Script_BlocksYouSouth:
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	face_up
	step_end

Route43Gate_Johto_Rocket2Script_BlocksYouNorth:
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	face_down
	step_end

Route43Gate_Johto_RocketText_TollFee:
	.string "(text not converted)$"

Route43Gate_Johto_RocketText_MakingABundle:
	.string "He-he-he. We're\n"
	.string "making a bundle."
	.string "\pEveryone wants to\n"
	.string "see what's going"
	.string "\pon up at LAKE OF\n"
	.string "RAGE.$"

Route43Gate_Johto_OfficerText_FoundTM:
	.string "I got chased from\n"
	.string "my post by these\l"
	.string "thugs in black."
	.string "\pThey left this\n"
	.string "behind."
	.string "\pIt makes me uncom-\n"
	.string "fortable. Could\l"
	.string "you take it away?$"

Route43Gate_Johto_OfficerText_AvoidGrass:
	.string "Use this gate to\n"
	.string "avoid walking in\l"
	.string "the grass.$"
