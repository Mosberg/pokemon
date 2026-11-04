Route16_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, Route16_Johto_OnLoad
	.byte 0

Route16_Johto_OnTransition:
	call Route16_Johto_Route16AlwaysOnBikeCallback_Cb
	end

Route16_Johto_CyclingRoadSign_Entry::
	lockall
	goto Route16_Johto_CyclingRoadSign


Route16_Johto_CyclingRoadSign:
	message Route16_Johto_CyclingRoadSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route16_Johto_Route16AlwaysOnBikeCallback_Cb:
	@ TODO unsupported: readvar VAR_YCOORD
	return

Route16_Johto_CyclingRoadSignText:
	.string "CYCLING ROAD"
	.string "\pDOWNHILL COASTING\n"
	.string "ALL THE WAY!$"

Route16_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_16_0, Route16_Johto_CutTree0_Keep
	setmetatile 14, 4, 541, 1
	setmetatile 15, 4, 533, 0
	setmetatile 14, 5, 541, 1
	setmetatile 15, 5, 533, 0
Route16_Johto_CutTree0_Keep:
	end

Route16_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route16_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_16_0
	setmetatile 14, 4, 541, 1
	setmetatile 15, 4, 533, 0
	setmetatile 14, 5, 541, 1
	setmetatile 15, 5, 533, 0
	special DrawWholeMapView
Route16_Johto_CutTree0_Done:
	releaseall
	end
