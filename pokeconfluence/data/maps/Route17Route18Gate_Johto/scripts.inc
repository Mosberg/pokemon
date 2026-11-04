Route17Route18Gate_Johto_MapScripts::
	.byte 0

Route17Route18Gate_Johto_Route17Route18GateOfficerScript_Entry::
	lockall
	goto Route17Route18Gate_Johto_Route17Route18GateOfficerScript

Route17Route18Gate_Johto_Route17Route18GateBicycleCheck_Entry::
	lockall
	goto Route17Route18Gate_Johto_Route17Route18GateBicycleCheck


Route17Route18Gate_Johto_Route17Route18GateOfficerScript:
	faceplayer
	message Route17Route18Gate_Johto_Route17Route18GateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route17Route18Gate_Johto_Route17Route18GateBicycleCheck:
	checkitem ITEM_BICYCLE, 1
	goto_if_eq VAR_RESULT, 0, Route17Route18Gate_Johto_Route17Route18GateBicycleCheck_NoBicycle
	releaseall
	end

Route17Route18Gate_Johto_Route17Route18GateBicycleCheck_NoBicycle:
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message Route17Route18Gate_Johto_Route17Route18GateCannotPassText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route17Route18Gate_Johto_Route17Route18GateCannotPassMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

Route17Route18Gate_Johto_Route17Route18GateCannotPassMovement:
	walk_right
	face_left
	step_end

Route17Route18Gate_Johto_Route17Route18GateOfficerText:
	.string "CYCLING ROAD\n"
	.string "Uphill Starts Here$"

Route17Route18Gate_Johto_Route17Route18GateCannotPassText:
	.string "Hang on! Don't you\n"
	.string "have a BICYCLE?"
	.string "\pThe CYCLING ROAD\n"
	.string "is beyond here."
	.string "\pYou have to have a\n"
	.string "BICYCLE to go on.$"
