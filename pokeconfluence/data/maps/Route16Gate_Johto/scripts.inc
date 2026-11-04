Route16Gate_Johto_MapScripts::
	.byte 0

Route16Gate_Johto_Route16GateOfficerScript_Entry::
	lockall
	goto Route16Gate_Johto_Route16GateOfficerScript

Route16Gate_Johto_Route16GateBicycleCheck_Entry::
	lockall
	goto Route16Gate_Johto_Route16GateBicycleCheck


Route16Gate_Johto_Route16GateOfficerScript:
	faceplayer
	message Route16Gate_Johto_Route16GateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route16Gate_Johto_Route16GateBicycleCheck:
	checkitem ITEM_BICYCLE, 1
	goto_if_eq VAR_RESULT, 0, Route16Gate_Johto_Route16GateBicycleCheck_NoBicycle
	releaseall
	end

Route16Gate_Johto_Route16GateBicycleCheck_NoBicycle:
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message Route16Gate_Johto_Route16GateCannotPassText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route16Gate_Johto_Route16GateCannotPassMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

Route16Gate_Johto_Route16GateCannotPassMovement:
	walk_right
	face_left
	step_end

Route16Gate_Johto_Route16GateOfficerText:
	.string "CYCLING ROAD\n"
	.string "starts here."
	.string "\pIt's all downhill,\n"
	.string "so it's totally\l"
	.string "exhilarating."
	.string "\pIt's a great sort\n"
	.string "of feeling that"
	.string "\pyou can't get from\n"
	.string "a ship or train.$"

Route16Gate_Johto_Route16GateCannotPassText:
	.string "Hey! Whoa! Stop!"
	.string "\pYou can't go out\n"
	.string "on the CYCLING"
	.string "\pROAD without a\n"
	.string "BICYCLE.$"
