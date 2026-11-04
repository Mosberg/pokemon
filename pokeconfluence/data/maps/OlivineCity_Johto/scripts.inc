OlivineCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_Johto_OnTransition
	.byte 0

OlivineCity_Johto_OnTransition:
	call OlivineCity_Johto_OlivineCityFlypointCallback_Cb
	end

OlivineCity_Johto_OlivineCitySailor1Script_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCitySailor1Script

OlivineCity_Johto_OlivineCityStandingYoungsterScript_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityStandingYoungsterScript

OlivineCity_Johto_OlivineCitySailor2Script_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCitySailor2Script

OlivineCity_Johto_OlivineCitySign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCitySign

OlivineCity_Johto_OlivineCityPortSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityPortSign

OlivineCity_Johto_OlivineGymSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineGymSign

OlivineCity_Johto_OlivineLighthouseSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineLighthouseSign

OlivineCity_Johto_OlivineCityBattleTowerSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityBattleTowerSign

OlivineCity_Johto_OlivineCityPokecenterSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityPokecenterSign

OlivineCity_Johto_OlivineCityMartSign_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityMartSign

OlivineCity_Johto_OlivineCityRivalSceneTop_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityRivalSceneTop

OlivineCity_Johto_OlivineCityRivalSceneBottom_Entry::
	lockall
	goto OlivineCity_Johto_OlivineCityRivalSceneBottom


OlivineCity_Johto_OlivineCityRivalSceneTop:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	playse SE_DOOR
	clearflag FLAG_JOHTO_RIVAL_OLIVINE_CITY
	addobject 4
	waitse
	applymovement 4, OlivineCity_Johto_OlivineCityRivalApproachesTopMovement
	waitmovement 4
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message OlivineCity_Johto_OlivineCityRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivineCity_Johto_OlivineCityPlayerStepsAsideTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, OlivineCity_Johto_OlivineCityRivalLeavesTopMovement
	waitmovement 4
	setvar VAR_JOHTO_SCENE_OLIVINE_CITY, 1
	removeobject 4
	fadedefaultbgm
	releaseall
	end

OlivineCity_Johto_OlivineCityRivalSceneBottom:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	playse SE_DOOR
	clearflag FLAG_JOHTO_RIVAL_OLIVINE_CITY
	addobject 4
	waitse
	applymovement 4, OlivineCity_Johto_OlivineCityRivalApproachesBottomMovement
	waitmovement 4
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message OlivineCity_Johto_OlivineCityRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OlivineCity_Johto_OlivineCityPlayerStepsAsideBottomMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, OlivineCity_Johto_OlivineCityRivalLeavesBottomMovement
	waitmovement 4
	removeobject 4
	setvar VAR_JOHTO_SCENE_OLIVINE_CITY, 1
	fadedefaultbgm
	releaseall
	end

OlivineCity_Johto_OlivineCitySailor1Script:
	faceplayer
	message OlivineCity_Johto_OlivineCitySailor1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCityStandingYoungsterScript:
	faceplayer
	random 2
	goto_if_eq VAR_RESULT, 0, OlivineCity_Johto_OlivineCityStandingYoungsterScript_FiftyFifty
	message OlivineCity_Johto_OlivineCityStandingYoungsterPokegearText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCityStandingYoungsterScript_FiftyFifty:
	message OlivineCity_Johto_OlivineCityStandingYoungsterPokedexText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCitySailor2Script:
	faceplayer
	message OlivineCity_Johto_OlivineCitySailor2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCitySign:
	message OlivineCity_Johto_OlivineCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCityPortSign:
	message OlivineCity_Johto_OlivineCityPortSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineGymSign:
	message OlivineCity_Johto_OlivineGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineLighthouseSign:
	message OlivineCity_Johto_OlivineLighthouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCityBattleTowerSign:
	message OlivineCity_Johto_OlivineCityBattleTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCity_Johto_OlivineCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

OlivineCity_Johto_OlivineCityMartSign:
	goto Johto_Std_MartSignScript

OlivineCity_Johto_OlivineCityFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_OLIVINE
	return

OlivineCity_Johto_OlivineCityRivalApproachesTopMovement:
	walk_down
	walk_right
	walk_right
	step_end

OlivineCity_Johto_OlivineCityRivalApproachesBottomMovement:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

OlivineCity_Johto_OlivineCityRivalLeavesTopMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_Johto_OlivineCityRivalLeavesBottomMovement:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_Johto_OlivineCityPlayerStepsAsideTopMovement:
	walk_down
	face_up
	step_end

OlivineCity_Johto_OlivineCityPlayerStepsAsideBottomMovement:
	walk_up
	face_down
	step_end

OlivineCity_Johto_OlivineCityRivalText:
	.string "…"
	.string "\pYou again?"
	.string "\pThere's no need to\n"
	.string "panic. I don't"
	.string "\pbother with wimps\n"
	.string "like you."
	.string "\pSpeaking of weak-\n"
	.string "lings, the city's"
	.string "\pGYM LEADER isn't\n"
	.string "here."
	.string "\pSupposedly taking\n"
	.string "care of a sick"
	.string "\pPOKéMON at the\n"
	.string "LIGHTHOUSE."
	.string "\pHumph! Boo-hoo!\n"
	.string "Just let sick\l"
	.string "POKéMON go!"
	.string "\pA POKéMON that\n"
	.string "can't battle is\l"
	.string "worthless!"
	.string "\pWhy don't you go\n"
	.string "train at the\l"
	.string "LIGHTHOUSE?"
	.string "\pWho knows. It may\n"
	.string "make you a bit\l"
	.string "less weak!$"

OlivineCity_Johto_OlivineCitySailor1Text:
	.string "Dark roads are\n"
	.string "dangerous at\l"
	.string "night."
	.string "\pBut in the pitch-\n"
	.string "black of night,"
	.string "\pthe sea is even\n"
	.string "more treacherous!"
	.string "\pWithout the beacon\n"
	.string "of the LIGHTHOUSE"
	.string "\pto guide it, no\n"
	.string "ship can sail.$"

OlivineCity_Johto_OlivineCityStandingYoungsterPokegearText:
	.string "That thing you\n"
	.string "have--it's a POKé-\l"
	.string "GEAR, right? Wow,\l"
	.string "that's cool.$"

OlivineCity_Johto_OlivineCityStandingYoungsterPokedexText:
	.string "Wow, you have a\n"
	.string "POKéDEX!"
	.string "\pThat is just so\n"
	.string "awesome.$"

OlivineCity_Johto_OlivineCitySailor2Text:
	.string "The sea is sweet!"
	.string "\pSunsets on the sea\n"
	.string "are marvelous!"
	.string "\pSing with me! \n"
	.string "Yo-ho! Blow the\l"
	.string "man down!…$"

OlivineCity_Johto_OlivineCitySignText:
	.string "OLIVINE CITY"
	.string "\pThe Port Closest\n"
	.string "to Foreign Lands$"

OlivineCity_Johto_OlivineCityPortSignText:
	.string "OLIVINE PORT\n"
	.string "FAST SHIP PIER$"

OlivineCity_Johto_OlivineGymSignText:
	.string "OLIVINE CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: JASMINE"
	.string "\pThe Steel-Clad\n"
	.string "Defense Girl$"

OlivineCity_Johto_OlivineLighthouseSignText:
	.string "OLIVINE LIGHTHOUSE\n"
	.string "Also known as the\l"
	.string "GLITTER LIGHTHOUSE$"

OlivineCity_Johto_OlivineCityBattleTowerSignText:
	.string "BATTLE TOWER AHEAD\n"
	.string "Opening Now!$"
