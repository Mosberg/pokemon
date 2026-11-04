VioletCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, VioletCity_Johto_OnLoad
	.byte 0

VioletCity_Johto_OnTransition:
	call VioletCity_Johto_VioletCityFlypointCallback_Cb
	end

VioletCity_Johto_VioletCityEarlScript_Entry::
	lockall
	goto VioletCity_Johto_VioletCityEarlScript

VioletCity_Johto_VioletCityLassScript_Entry::
	lockall
	goto VioletCity_Johto_VioletCityLassScript

VioletCity_Johto_VioletCitySuperNerdScript_Entry::
	lockall
	goto VioletCity_Johto_VioletCitySuperNerdScript

VioletCity_Johto_VioletCityGrampsScript_Entry::
	lockall
	goto VioletCity_Johto_VioletCityGrampsScript

VioletCity_Johto_VioletCityYoungsterScript_Entry::
	lockall
	goto VioletCity_Johto_VioletCityYoungsterScript

VioletCity_Johto_VioletCityFruitTree_Entry::
	lockall
	goto VioletCity_Johto_VioletCityFruitTree

VioletCity_Johto_VioletCityPPUp_Entry::
	lockall
	goto VioletCity_Johto_VioletCityPPUp

VioletCity_Johto_VioletCityRareCandy_Entry::
	lockall
	goto VioletCity_Johto_VioletCityRareCandy

VioletCity_Johto_VioletCitySign_Entry::
	lockall
	goto VioletCity_Johto_VioletCitySign

VioletCity_Johto_VioletGymSign_Entry::
	lockall
	goto VioletCity_Johto_VioletGymSign

VioletCity_Johto_SproutTowerSign_Entry::
	lockall
	goto VioletCity_Johto_SproutTowerSign

VioletCity_Johto_EarlsPokemonAcademySign_Entry::
	lockall
	goto VioletCity_Johto_EarlsPokemonAcademySign

VioletCity_Johto_VioletCityPokecenterSign_Entry::
	lockall
	goto VioletCity_Johto_VioletCityPokecenterSign

VioletCity_Johto_VioletCityMartSign_Entry::
	lockall
	goto VioletCity_Johto_VioletCityMartSign


VioletCity_Johto_VioletCityEarlScript:
	applymovement 1, VioletCity_Johto_VioletCitySpinningEarl_MovementData
	waitmovement 1
	faceplayer
	message VioletCity_Johto_Text_EarlAsksIfYouBeatFalkner
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, VioletCity_Johto_VioletCityEarlScript_FollowEarl
	goto VioletCity_Johto_VioletCityEarlScript_PointlessJump

VioletCity_Johto_VioletCityEarlScript_PointlessJump:
	message VioletCity_Johto_Text_VeryNiceIndeed
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCityEarlScript_FollowEarl:
	message VioletCity_Johto_Text_FollowEarl
	waitmessage
	waitbuttonpress
	closemessage
	playbgm MUS_DUMMY, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Johto_VioletCityFollowEarl_MovementData
	applymovement 1, VioletCity_Johto_VioletCityFollowEarl_MovementData
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Johto_VioletCitySpinningEarl_MovementData
	applymovement 1, VioletCity_Johto_VioletCitySpinningEarl_MovementData
	waitmovement 1
	fadedefaultbgm
	message VioletCity_Johto_Text_HereTeacherIAm
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, VioletCity_Johto_VioletCitySpinningEarl_MovementData
	waitmovement 1
	applymovement 1, VioletCity_Johto_VioletCityFinishFollowEarl_MovementData
	waitmovement 1
	playse SE_DOOR
	removeobject 1
	clearflag FLAG_JOHTO_EARLS_ACADEMY_EARL
	waitse
	releaseall
	end

VioletCity_Johto_VioletCityLassScript:
	faceplayer
	message VioletCity_Johto_VioletCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCitySuperNerdScript:
	faceplayer
	message VioletCity_Johto_VioletCitySuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCityGrampsScript:
	faceplayer
	message VioletCity_Johto_VioletCityGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCityYoungsterScript:
	faceplayer
	message VioletCity_Johto_VioletCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCitySign:
	message VioletCity_Johto_VioletCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletGymSign:
	message VioletCity_Johto_VioletGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_SproutTowerSign:
	message VioletCity_Johto_SproutTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_EarlsPokemonAcademySign:
	message VioletCity_Johto_EarlsPokemonAcademySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletCity_Johto_VioletCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

VioletCity_Johto_VioletCityMartSign:
	goto Johto_Std_MartSignScript

VioletCity_Johto_VioletCityPPUp:
	finditem ITEM_PP_UP
	releaseall
	end

VioletCity_Johto_VioletCityRareCandy:
	finditem ITEM_RARE_CANDY
	releaseall
	end

VioletCity_Johto_VioletCityFruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_VIOLET_CITY, Johto_Std_FruitTreeEmpty
	giveitem ITEM_CHERI_BERRY
	setflag FLAG_JOHTO_FRUITTREE_VIOLET_CITY
	releaseall
	end

VioletCity_Johto_VioletCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_VIOLET
	return

VioletCity_Johto_VioletCityFollowEarl_MovementData:
	walk_fast_down
	walk_fast_down
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	walk_fast_down
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	walk_fast_up
	face_down
	step_end

VioletCity_Johto_VioletCityFinishFollowEarl_MovementData:
	walk_up
	step_end

VioletCity_Johto_VioletCitySpinningEarl_MovementData:
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end

VioletCity_Johto_Text_EarlAsksIfYouBeatFalkner:
	.string "Hello!\n"
	.string "You are trainer?"
	.string "\pBattle GYM LEADER,\n"
	.string "win you did?$"

VioletCity_Johto_Text_VeryNiceIndeed:
	.string "Ooh, la la!\n"
	.string "Very indeed nice!$"

VioletCity_Johto_Text_FollowEarl:
	.string "Is that so? Then\n"
	.string "study shall you!\l"
	.string "Follow me!$"

VioletCity_Johto_Text_HereTeacherIAm:
	.string "Here, teacher I\n"
	.string "am. Good it is\l"
	.string "you study here!$"

VioletCity_Johto_VioletCityLassText:
	.string "Ghosts are rumored\n"
	.string "to appear in\l"
	.string "SPROUT TOWER."
	.string "\pThey said normal-\n"
	.string "type POKéMON moves"
	.string "\phad no effect on\n"
	.string "ghosts.$"

VioletCity_Johto_VioletCitySuperNerdText:
	.string "Hey, you're a\n"
	.string "POKéMON trainer?"
	.string "\pIf you beat the\n"
	.string "GYM LEADER here,"
	.string "\pyou'll be ready\n"
	.string "for prime time!$"

VioletCity_Johto_VioletCityGrampsText:
	.string "FALKNER, from the\n"
	.string "VIOLET POKéMON"
	.string "\pGYM, is a fine\n"
	.string "trainer!"
	.string "\pHe inherited his\n"
	.string "father's gym and"
	.string "\phas done a great\n"
	.string "job with it.$"

VioletCity_Johto_VioletCityYoungsterText:
	.string "I saw a wiggly\n"
	.string "tree up ahead!"
	.string "\pIf you touch it,\n"
	.string "it squirms and\l"
	.string "dances! Cool!$"

VioletCity_Johto_VioletCitySignText:
	.string "VIOLET CITY"
	.string "\pThe City of\n"
	.string "Nostalgic Scents$"

VioletCity_Johto_VioletGymSignText:
	.string "VIOLET CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: FALKNER"
	.string "\pThe Elegant Master\n"
	.string "of Flying POKéMON$"

VioletCity_Johto_SproutTowerSignText:
	.string "SPROUT TOWER"
	.string "\pExperience the\n"
	.string "Way of POKéMON$"

VioletCity_Johto_EarlsPokemonAcademySignText:
	.string "EARL'S POKéMON\n"
	.string "ACADEMY$"

VioletCity_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_VIOLET_CITY_0, VioletCity_Johto_CutTree0_Keep
	setmetatile 36, 18, 514, 0
	setmetatile 37, 18, 514, 0
	setmetatile 36, 19, 514, 0
	setmetatile 37, 19, 591, 0
VioletCity_Johto_CutTree0_Keep:
	end

VioletCity_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, VioletCity_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_VIOLET_CITY_0
	setmetatile 36, 18, 514, 0
	setmetatile 37, 18, 514, 0
	setmetatile 36, 19, 514, 0
	setmetatile 37, 19, 591, 0
	special DrawWholeMapView
VioletCity_Johto_CutTree0_Done:
	releaseall
	end
