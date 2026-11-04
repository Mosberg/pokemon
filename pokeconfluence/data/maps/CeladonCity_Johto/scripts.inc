CeladonCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, CeladonCity_Johto_OnLoad
	.byte 0

CeladonCity_Johto_OnTransition:
	call CeladonCity_Johto_CeladonCityFlypointCallback_Cb
	end

CeladonCity_Johto_CeladonCityFisherScript_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityFisherScript

CeladonCity_Johto_CeladonCityPoliwrath_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityPoliwrath

CeladonCity_Johto_CeladonCityTeacher1Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityTeacher1Script

CeladonCity_Johto_CeladonCityGramps1Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityGramps1Script

CeladonCity_Johto_CeladonCityGramps2Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityGramps2Script

CeladonCity_Johto_CeladonCityYoungster1Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityYoungster1Script

CeladonCity_Johto_CeladonCityYoungster2Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityYoungster2Script

CeladonCity_Johto_CeladonCityTeacher2Script_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityTeacher2Script

CeladonCity_Johto_CeladonCityLassScript_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityLassScript

CeladonCity_Johto_CeladonCitySign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCitySign

CeladonCity_Johto_CeladonGymSign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonGymSign

CeladonCity_Johto_CeladonCityDeptStoreSign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityDeptStoreSign

CeladonCity_Johto_CeladonCityMansionSign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityMansionSign

CeladonCity_Johto_CeladonCityGameCornerSign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityGameCornerSign

CeladonCity_Johto_CeladonCityTrainerTips_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityTrainerTips

CeladonCity_Johto_CeladonCityPokecenterSign_Entry::
	lockall
	goto CeladonCity_Johto_CeladonCityPokecenterSign


CeladonCity_Johto_CeladonCityFisherScript:
	faceplayer
	message CeladonCity_Johto_CeladonCityFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityPoliwrath:
	message CeladonCity_Johto_CeladonCityPoliwrathText
	waitmessage
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityTeacher1Script:
	@ TODO unsupported: jumptextfaceplayer CeladonCityTeacher1Text
	goto Johto_EventScript_Unimplemented

CeladonCity_Johto_CeladonCityGramps1Script:
	faceplayer
	message CeladonCity_Johto_CeladonCityGramps1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityGramps2Script:
	faceplayer
	message CeladonCity_Johto_CeladonCityGramps2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityYoungster1Script:
	faceplayer
	message CeladonCity_Johto_CeladonCityYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityYoungster2Script:
	faceplayer
	message CeladonCity_Johto_CeladonCityYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityTeacher2Script:
	faceplayer
	message CeladonCity_Johto_CeladonCityTeacher2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityLassScript:
	faceplayer
	message CeladonCity_Johto_CeladonCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCitySign:
	message CeladonCity_Johto_CeladonCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonGymSign:
	message CeladonCity_Johto_CeladonGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityDeptStoreSign:
	message CeladonCity_Johto_CeladonCityDeptStoreSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityMansionSign:
	message CeladonCity_Johto_CeladonCityMansionSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityGameCornerSign:
	@ TODO unsupported: jumptext CeladonCityGameCornerSignText
	goto Johto_EventScript_Unimplemented

CeladonCity_Johto_CeladonCityTrainerTips:
	message CeladonCity_Johto_CeladonCityTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCity_Johto_CeladonCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

CeladonCity_Johto_CeladonCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_CELADON
	return

CeladonCity_Johto_CeladonCityFisherText:
	.string "This POLIWRATH is\n"
	.string "my partner."
	.string "\pI wonder if it'll\n"
	.string "ever evolve into a\l"
	.string "frog POKéMON.$"

CeladonCity_Johto_CeladonCityPoliwrathText:
	.string "POLIWRATH: Croak!$"

CeladonCity_Johto_CeladonCityGramps1Text:
	.string "GRIMER have been\n"
	.string "appearing lately."
	.string "\pSee that pond out\n"
	.string "in front of the"
	.string "\phouse? GRIMER live\n"
	.string "there now."
	.string "\pWhere did they\n"
	.string "come from? This is\l"
	.string "a serious problem…$"

CeladonCity_Johto_CeladonCityGramps2Text:
	.string "Nihihi! This GYM\n"
	.string "is great! Only"
	.string "\pgirls are allowed\n"
	.string "here!$"

CeladonCity_Johto_CeladonCityYoungster1Text:
	.string "Want to know a\n"
	.string "secret?"
	.string "\pCELADON MANSION\n"
	.string "has a hidden back\l"
	.string "door.$"

CeladonCity_Johto_CeladonCityYoungster2Text:
	.string "They're holding an\n"
	.string "eating contest at\l"
	.string "the restaurant."
	.string "\pJust watching them\n"
	.string "go at it makes me\l"
	.string "feel bloated…$"

CeladonCity_Johto_CeladonCityTeacher2Text:
	.string "CELADON DEPT.STORE\n"
	.string "has the biggest"
	.string "\pand best selection\n"
	.string "of merchandise."
	.string "\pIf you can't get\n"
	.string "it there, you"
	.string "\pcan't get it any-\n"
	.string "where."
	.string "\pGee… I sound like\n"
	.string "a sales clerk.$"

CeladonCity_Johto_CeladonCityLassText:
	.string "Looking at the\n"
	.string "ground while I was"
	.string "\pwalking made me\n"
	.string "dizzy.$"

CeladonCity_Johto_CeladonCitySignText:
	.string "CELADON CITY"
	.string "\pThe City of\n"
	.string "Rainbow Dreams$"

CeladonCity_Johto_CeladonGymSignText:
	.string "CELADON CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: ERIKA"
	.string "\pThe Nature-Loving\n"
	.string "Princess$"

CeladonCity_Johto_CeladonCityDeptStoreSignText:
	.string "Find What You\n"
	.string "Need at CELADON\l"
	.string "DEPT.STORE!$"

CeladonCity_Johto_CeladonCityMansionSignText:
	.string "CELADON MANSION$"

CeladonCity_Johto_CeladonCityTrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pGUARD SPEC.\n"
	.string "protects POKéMON"
	.string "\pagainst SPECIAL\n"
	.string "attacks such as\l"
	.string "fire and water."
	.string "\pGet your items at\n"
	.string "CELADON DEPT.\l"
	.string "STORE!$"

CeladonCity_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_CELADON_CITY_0, CeladonCity_Johto_CutTree0_Keep
	setmetatile 28, 34, 533, 0
	setmetatile 29, 34, 541, 1
	setmetatile 28, 35, 533, 0
	setmetatile 29, 35, 541, 1
CeladonCity_Johto_CutTree0_Keep:
	end

CeladonCity_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_CELADON_CITY_0
	setmetatile 28, 34, 533, 0
	setmetatile 29, 34, 541, 1
	setmetatile 28, 35, 533, 0
	setmetatile 29, 35, 541, 1
	special DrawWholeMapView
CeladonCity_Johto_CutTree0_Done:
	releaseall
	end
