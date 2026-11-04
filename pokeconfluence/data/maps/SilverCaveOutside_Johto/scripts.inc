SilverCaveOutside_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SilverCaveOutside_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, SilverCaveOutside_Johto_OnLoad
	.byte 0

SilverCaveOutside_Johto_OnTransition:
	call SilverCaveOutside_Johto_SilverCaveOutsideFlypointCallback_Cb
	end

SilverCaveOutside_Johto_MtSilverPokecenterSign_Entry::
	lockall
	goto SilverCaveOutside_Johto_MtSilverPokecenterSign

SilverCaveOutside_Johto_MtSilverSign_Entry::
	lockall
	goto SilverCaveOutside_Johto_MtSilverSign


SilverCaveOutside_Johto_MtSilverPokecenterSign:
	goto Johto_Std_PokecenterSignScript

SilverCaveOutside_Johto_MtSilverSign:
	message SilverCaveOutside_Johto_MtSilverSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SilverCaveOutside_Johto_SilverCaveOutsideFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_SILVER_CAVE
	return

SilverCaveOutside_Johto_MtSilverSignText:
	.string "MT.SILVER$"

SilverCaveOutside_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_SILVER_CAVE_OUTSIDE_0, SilverCaveOutside_Johto_CutTree0_Keep
	setmetatile 34, 22, 533, 0
	setmetatile 35, 22, 541, 1
	setmetatile 34, 23, 533, 0
	setmetatile 35, 23, 541, 1
SilverCaveOutside_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_SILVER_CAVE_OUTSIDE_1, SilverCaveOutside_Johto_CutTree1_Keep
	setmetatile 30, 24, 533, 0
	setmetatile 31, 24, 533, 0
	setmetatile 30, 25, 541, 1
	setmetatile 31, 25, 533, 0
SilverCaveOutside_Johto_CutTree1_Keep:
	end

SilverCaveOutside_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, SilverCaveOutside_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_SILVER_CAVE_OUTSIDE_0
	setmetatile 34, 22, 533, 0
	setmetatile 35, 22, 541, 1
	setmetatile 34, 23, 533, 0
	setmetatile 35, 23, 541, 1
	special DrawWholeMapView
SilverCaveOutside_Johto_CutTree0_Done:
	releaseall
	end

SilverCaveOutside_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, SilverCaveOutside_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_SILVER_CAVE_OUTSIDE_1
	setmetatile 30, 24, 533, 0
	setmetatile 31, 24, 533, 0
	setmetatile 30, 25, 541, 1
	setmetatile 31, 25, 533, 0
	special DrawWholeMapView
SilverCaveOutside_Johto_CutTree1_Done:
	releaseall
	end
