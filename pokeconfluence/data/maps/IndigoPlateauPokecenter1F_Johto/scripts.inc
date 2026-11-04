IndigoPlateauPokecenter1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateauPokecenter1F_Johto_OnTransition
	.byte 0

IndigoPlateauPokecenter1F_Johto_OnTransition:
	call IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FPrepareElite4Callback_Cb
	end

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FNurseScript_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FNurseScript

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FClerkScript_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FClerkScript

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FCooltrainerMScript_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FCooltrainerMScript

IndigoPlateauPokecenter1F_Johto_TeleportGuyScript_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_TeleportGuyScript

IndigoPlateauPokecenter1F_Johto_AbraScript_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_AbraScript

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle1_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle1

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle2_Entry::
	lockall
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle2


IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle1:
	goto_if_unset FLAG_JOHTO_BEAT_RIVAL_IN_MT_MOON, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_set FLAG_JOHTO_ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 2, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 4, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 5, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 6, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	setobjectxyperm 4, 17, 9
	clearflag FLAG_JOHTO_INDIGO_PLATEAU_POKECENTER_RIVAL
	addobject 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	applymovement 4, IndigoPlateauPokecenter1F_Johto_PlateauRivalMovement1
	waitmovement 4
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattle2:
	goto_if_unset FLAG_JOHTO_BEAT_RIVAL_IN_MT_MOON, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_set FLAG_JOHTO_ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 0, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 2, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 4, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 5, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	goto_if_eq VAR_RESULT, 6, IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone
	clearflag FLAG_JOHTO_INDIGO_PLATEAU_POKECENTER_RIVAL
	addobject 4
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	applymovement 4, IndigoPlateauPokecenter1F_Johto_PlateauRivalMovement2
	waitmovement 4
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon:
	message IndigoPlateauPokecenter1F_Johto_PlateauRivalText1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_INDIGO_PLATEAU_POKECENTER_RIVAL
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon_Totodile
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon_Chikorita
	setvar VAR_LAST_TALKED, 4
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL2_RIVAL2_2_TOTODILE, IndigoPlateauPokecenter1F_Johto_PlateauRivalWinText
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalPostBattle

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon_Totodile:
	setvar VAR_LAST_TALKED, 4
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL2_RIVAL2_2_CHIKORITA, IndigoPlateauPokecenter1F_Johto_PlateauRivalWinText
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalPostBattle

IndigoPlateauPokecenter1F_Johto_PlateauRivalBattleCommon_Chikorita:
	setvar VAR_LAST_TALKED, 4
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL2_RIVAL2_2_CYNDAQUIL, IndigoPlateauPokecenter1F_Johto_PlateauRivalWinText
	goto IndigoPlateauPokecenter1F_Johto_PlateauRivalPostBattle

IndigoPlateauPokecenter1F_Johto_PlateauRivalPostBattle:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message IndigoPlateauPokecenter1F_Johto_PlateauRivalText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 4, IndigoPlateauPokecenter1F_Johto_PlateauRivalLeavesMovement
	waitmovement 4
	removeobject 4
	setvar VAR_JOHTO_SCENE_INDIGO_PLATEAU_POKECENTER_1F, 0
	fadedefaultbgm
	setflag FLAG_JOHTO_ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT

IndigoPlateauPokecenter1F_Johto_PlateauRivalScriptDone:
	releaseall
	end

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_ROUTE_23
	goto Johto_Std_PokecenterNurseScript

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FClerkScript:
	pokemart Johto_Mart_INDIGO_PLATEAU
	closemessage
	releaseall
	end

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FCooltrainerMScript:
	faceplayer
	message IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IndigoPlateauPokecenter1F_Johto_TeleportGuyScript:
	faceplayer
	message IndigoPlateauPokecenter1F_Johto_TeleportGuyText1
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, IndigoPlateauPokecenter1F_Johto_TeleportGuyScript_No
	message IndigoPlateauPokecenter1F_Johto_TeleportGuyYesText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_WARP_IN
	fadescreen FADE_TO_WHITE
	waitse
	warp MAP_JOHTO_NEW_BARK_TOWN, 13, 6
	waitstate

IndigoPlateauPokecenter1F_Johto_TeleportGuyScript_No:
	message IndigoPlateauPokecenter1F_Johto_TeleportGuyNoText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IndigoPlateauPokecenter1F_Johto_AbraScript:
	message IndigoPlateauPokecenter1F_Johto_AbraText
	waitmessage
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FPrepareElite4Callback_Cb:
	setvar VAR_JOHTO_SCENE_WILLS_ROOM, 0
	setvar VAR_JOHTO_SCENE_KOGAS_ROOM, 0
	setvar VAR_JOHTO_SCENE_BRUNOS_ROOM, 0
	setvar VAR_JOHTO_SCENE_KARENS_ROOM, 0
	setvar VAR_JOHTO_SCENE_LANCES_ROOM, 0
	setvar VAR_JOHTO_SCENE_HALL_OF_FAME, 0
	clearflag FLAG_JOHTO_WILLS_ROOM_ENTRANCE_CLOSED
	clearflag FLAG_JOHTO_WILLS_ROOM_EXIT_OPEN
	clearflag FLAG_JOHTO_KOGAS_ROOM_ENTRANCE_CLOSED
	clearflag FLAG_JOHTO_KOGAS_ROOM_EXIT_OPEN
	clearflag FLAG_JOHTO_BRUNOS_ROOM_ENTRANCE_CLOSED
	clearflag FLAG_JOHTO_BRUNOS_ROOM_EXIT_OPEN
	clearflag FLAG_JOHTO_KARENS_ROOM_ENTRANCE_CLOSED
	clearflag FLAG_JOHTO_KARENS_ROOM_EXIT_OPEN
	clearflag FLAG_JOHTO_LANCES_ROOM_ENTRANCE_CLOSED
	clearflag FLAG_JOHTO_LANCES_ROOM_EXIT_OPEN
	clearflag FLAG_JOHTO_BEAT_ELITE_4_WILL
	clearflag FLAG_JOHTO_BEAT_ELITE_4_KOGA
	clearflag FLAG_JOHTO_BEAT_ELITE_4_BRUNO
	clearflag FLAG_JOHTO_BEAT_ELITE_4_KAREN
	clearflag FLAG_JOHTO_BEAT_CHAMPION_LANCE
	setflag FLAG_JOHTO_LANCES_ROOM_OAK_AND_MARY
	return

IndigoPlateauPokecenter1F_Johto_PlateauRivalMovement1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_left
	step_end

IndigoPlateauPokecenter1F_Johto_PlateauRivalMovement2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

IndigoPlateauPokecenter1F_Johto_PlateauRivalLeavesMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

IndigoPlateauPokecenter1F_Johto_IndigoPlateauPokecenter1FCooltrainerMText:
	.string "At the POKéMON\n"
	.string "LEAGUE, you'll get"
	.string "\ptested by the\n"
	.string "ELITE FOUR."
	.string "\pYou have to beat\n"
	.string "them all. If you"
	.string "\plose, you have to\n"
	.string "start all over!$"

IndigoPlateauPokecenter1F_Johto_PlateauRivalText1:
	.string "Hold it."
	.string "\pYou're going to\n"
	.string "take the POKéMON"
	.string "\pLEAGUE challenge\n"
	.string "now?"
	.string "\pThat's not going\n"
	.string "to happen."
	.string "\pMy super-well-\n"
	.string "trained POKéMON"
	.string "\pare going to pound\n"
	.string "you."
	.string "\p{PLAYER}!\n"
	.string "I challenge you!$"

IndigoPlateauPokecenter1F_Johto_PlateauRivalWinText:
	.string "…"
	.string "\pOK--I lost…$"

IndigoPlateauPokecenter1F_Johto_PlateauRivalText2:
	.string "…Darn… I still\n"
	.string "can't win…"
	.string "\pI… I have to think\n"
	.string "more about my\l"
	.string "POKéMON…"
	.string "\pHumph! Try not to\n"
	.string "lose!$"

IndigoPlateauPokecenter1F_Johto_TeleportGuyText1:
	.string "Ah! You're chal-\n"
	.string "lenging the ELITE"
	.string "\pFOUR? Are you sure\n"
	.string "you're ready?"
	.string "\pIf you need to\n"
	.string "train some more,"
	.string "\pmy ABRA can help\n"
	.string "you."
	.string "\pIt can TELEPORT\n"
	.string "you home."
	.string "\pWould you like to\n"
	.string "go home now?$"

IndigoPlateauPokecenter1F_Johto_TeleportGuyYesText:
	.string "OK, OK. Picture\n"
	.string "your house in your\l"
	.string "mind…$"

IndigoPlateauPokecenter1F_Johto_TeleportGuyNoText:
	.string "OK, OK. The best\n"
	.string "of luck to you!$"

IndigoPlateauPokecenter1F_Johto_AbraText:
	.string "ABRA: Aabra…$"
