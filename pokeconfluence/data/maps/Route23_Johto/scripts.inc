Route23_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route23_Johto_OnTransition
	.byte 0

Route23_Johto_OnTransition:
	call Route23_Johto_Route23FlypointCallback_Cb
	end

Route23_Johto_IndigoPlateauSign_Entry::
	lockall
	goto Route23_Johto_IndigoPlateauSign


Route23_Johto_IndigoPlateauSign:
	message Route23_Johto_IndigoPlateauSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route23_Johto_Route23FlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_INDIGO_PLATEAU
	return

Route23_Johto_IndigoPlateauSignText:
	.string "INDIGO PLATEAU"
	.string "\pThe Ultimate Goal\n"
	.string "for Trainers!"
	.string "\pPOKéMON LEAGUE HQ$"
