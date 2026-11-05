Route34IlexForestGate_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route34IlexForestGate_Johto_OnTransition
	.byte 0

Route34IlexForestGate_Johto_OnTransition:
	call Route34IlexForestGate_Johto_Route34IsForestRestlessCallback_Cb
	end

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_Entry::
	lockall
	goto Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript

Route34IlexForestGate_Johto_Route34IlexForestGateButterfreeScript_Entry::
	lockall
	goto Route34IlexForestGate_Johto_Route34IlexForestGateButterfreeScript

Route34IlexForestGate_Johto_Route34IlexForestGateLassScript_Entry::
	lockall
	goto Route34IlexForestGate_Johto_Route34IlexForestGateLassScript

Route34IlexForestGate_Johto_Route34IlexForestGateCelebiEvent_Entry::
	lockall
	goto Route34IlexForestGate_Johto_Route34IlexForestGateCelebiEvent


Route34IlexForestGate_Johto_Route34IlexForestGateCelebiEvent:
	goto_if_unset FLAG_JOHTO_FOREST_IS_RESTLESS, Route34IlexForestGate_Johto_Route34IlexForestGateCelebiEvent_skip
	applymovement 4, Johto_Movement_Emote_exclamation_mark
	waitmovement 4
	applymovement 4, Johto_Movement_Face_Left
	waitmovement 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherBlocksPlayerMovement
	applymovement OBJ_EVENT_ID_PLAYER, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherBlocksPlayerMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	message Route34IlexForestGate_Johto_Route34IlexForestGateTeacher_ForestIsRestless
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherReturnsMovement
	waitmovement 4

Route34IlexForestGate_Johto_Route34IlexForestGateCelebiEvent_skip:
	releaseall
	end

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FOREST_IS_RESTLESS, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_ForestIsRestless
	goto_if_set FLAG_JOHTO_GOT_TM12_SWEET_SCENT, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_GotSweetScent
	message Route34IlexForestGate_Johto_Route34IlexForestGateTeacherText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_GIGA_DRAIN
	goto_if_eq VAR_RESULT, 0, Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_NoRoom
	setflag FLAG_JOHTO_GOT_TM12_SWEET_SCENT

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_GotSweetScent:
	message Route34IlexForestGate_Johto_Route34IlexForestGateTeacher_GotSweetScent
	waitmessage
	waitbuttonpress

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_NoRoom:
	closemessage
	releaseall
	end

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherScript_ForestIsRestless:
	message Route34IlexForestGate_Johto_Route34IlexForestGateTeacher_ForestIsRestless
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34IlexForestGate_Johto_Route34IlexForestGateButterfreeScript:
	message Route34IlexForestGate_Johto_Route34IlexForestGateButterfreeText
	waitmessage
	playmoncry SPECIES_BUTTERFREE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

Route34IlexForestGate_Johto_Route34IlexForestGateLassScript:
	faceplayer
	message Route34IlexForestGate_Johto_Route34IlexForestGateLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34IlexForestGate_Johto_Route34IsForestRestlessCallback_Cb:
	goto_if_unset FLAG_JOHTO_FOREST_IS_RESTLESS, Route34IlexForestGate_Johto_Route34IsForestRestlessCallback_Normal_Cb
	setflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER
	clearflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY
	return

Route34IlexForestGate_Johto_Route34IsForestRestlessCallback_Normal_Cb:
	setflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY
	clearflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER
	return

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherBlocksPlayerMovement:
	walk_up
	walk_up
	step_end

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherReturnsMovement:
	walk_down
	walk_right
	step_end

Route34IlexForestGate_Johto_Route34IlexForestGateTeacherText:
	.string "Oh, honey. You're\n"
	.string "making a POKéDEX?"
	.string "\pIt must be hard if\n"
	.string "POKéMON won't"
	.string "\pappear. Try using\n"
	.string "this TM.$"

Route34IlexForestGate_Johto_Route34IlexForestGateTeacher_GotSweetScent:
	.string "It's SWEET SCENT."
	.string "\pUse it wherever\n"
	.string "POKéMON appear."
	.string "\pPOKéMON will be\n"
	.string "enticed by it.$"

Route34IlexForestGate_Johto_Route34IlexForestGateTeacher_ForestIsRestless:
	.string "Something's wrong\n"
	.string "in ILEX FOREST…"
	.string "\pYou should stay\n"
	.string "away right now.$"

Route34IlexForestGate_Johto_Route34IlexForestGateButterfreeText:
	.string "BUTTERFREE: Freeh!$"

Route34IlexForestGate_Johto_Route34IlexForestGateLassText:
	.string "Did you see the\n"
	.string "shrine honoring\l"
	.string "the protector?"
	.string "\pIt watches over\n"
	.string "the FOREST from\l"
	.string "across time."
	.string "\pI think that it\n"
	.string "must be a grass-\l"
	.string "type POKéMON.$"
