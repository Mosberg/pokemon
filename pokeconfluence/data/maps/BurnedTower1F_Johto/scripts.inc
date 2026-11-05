BurnedTower1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BurnedTower1F_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BurnedTower1F_Johto_OnFrame
	.byte 0

BurnedTower1F_Johto_OnLoad:
	call BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_Cb
	end

BurnedTower1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_BURNED_TOWER_1F, 0, BurnedTower1F_Johto_BurnedTower1FMeetEusineScript_Entry
	.2byte 0

BurnedTower1F_Johto_BurnedTower1FRock_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTower1FRock

BurnedTower1F_Johto_BurnedTower1FEusineScript_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTower1FEusineScript

BurnedTower1F_Johto_BurnedTower1FMortyScript_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTower1FMortyScript

BurnedTower1F_Johto_BurnedTower1FHPUp_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTower1FHPUp

BurnedTower1F_Johto_BurnedTowerRivalBattleScript_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTowerRivalBattleScript

BurnedTower1F_Johto_BurnedTower1FMeetEusineScript_Entry::
	lockall
	goto BurnedTower1F_Johto_BurnedTower1FMeetEusineScript


BurnedTower1F_Johto_BurnedTower1FMeetEusineScript:
	applymovement 2, Johto_Movement_Face_Down
	waitmovement 2
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 2, BurnedTower1F_Johto_BurnedTower1FEusineMovement
	waitmovement 2
	message BurnedTower1F_Johto_BurnedTower1FEusineIntroText
	waitmessage
	waitbuttonpress
	closemessage
	setobjectxyperm 2, 9, 14
	setvar VAR_JOHTO_SCENE_BURNED_TOWER_1F, 1
	releaseall
	end

BurnedTower1F_Johto_BurnedTowerRivalBattleScript:
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	fadeoutbgm 4
	delay 15
	applymovement 3, Johto_Movement_Face_Right
	waitmovement 3
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, BurnedTower1F_Johto_BurnedTowerMovement_PlayerWalksToRival
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, BurnedTower1F_Johto_BurnedTowerMovement_RivalWalksToPlayer
	waitmovement 3
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message BurnedTower1F_Johto_BurnedTowerRival_BeforeText
	waitmessage
	waitbuttonpress
	closemessage
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, BurnedTower1F_Johto_BurnedTowerRivalBattleScript_totodile
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, BurnedTower1F_Johto_BurnedTowerRivalBattleScript_chikorita
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_3_TOTODILE, BurnedTower1F_Johto_BurnedTowerRival_WinText
	goto BurnedTower1F_Johto_BurnedTowerRivalBattleScript_returnfrombattle

BurnedTower1F_Johto_BurnedTowerRivalBattleScript_totodile:
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_3_CHIKORITA, BurnedTower1F_Johto_BurnedTowerRival_WinText
	goto BurnedTower1F_Johto_BurnedTowerRivalBattleScript_returnfrombattle

BurnedTower1F_Johto_BurnedTowerRivalBattleScript_chikorita:
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_3_CYNDAQUIL, BurnedTower1F_Johto_BurnedTowerRival_WinText
	goto BurnedTower1F_Johto_BurnedTowerRivalBattleScript_returnfrombattle

BurnedTower1F_Johto_BurnedTowerRivalBattleScript_returnfrombattle:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message BurnedTower1F_Johto_BurnedTowerRival_AfterText1
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_BURNED_TOWER_1F, 2
	setflag FLAG_JOHTO_RIVAL_BURNED_TOWER
	fadeoutbgm 4
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_DOOR
	waitse
	setmetatile 10, 8, 543, 1
	setmetatile 11, 8, 543, 1
	setmetatile 10, 9, 544, 1
	setmetatile 11, 9, 513, 0
	special DrawWholeMapView
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, BurnedTower1F_Johto_BurnedTower1FMovement_PlayerStartsToFall
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_PIN
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	message BurnedTower1F_Johto_BurnedTowerRival_AfterText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_HOLE_IN_BURNED_TOWER
	delay 15
	@ TODO unsupported: warpcheck 
	goto Johto_EventScript_Unimplemented

BurnedTower1F_Johto_BurnedTower1FEusineScript:
	faceplayer
	message BurnedTower1F_Johto_BurnedTower1FEusineText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BurnedTower1F_Johto_BurnedTower1FMortyScript:
	faceplayer
	message BurnedTower1F_Johto_BurnedTower1FMortyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BurnedTower1F_Johto_BurnedTower1FRock:
	goto Johto_Std_SmashRockScript

BurnedTower1F_Johto_BurnedTower1FHPUp:
	finditem ITEM_HP_UP
	releaseall
	end

BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_Cb:
	goto_if_set FLAG_JOHTO_HOLE_IN_BURNED_TOWER, BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_KeepHoleOpen_Cb
	setmetatile 10, 8, 543, 1
	setmetatile 11, 8, 543, 1
	setmetatile 10, 9, 513, 0
	setmetatile 11, 9, 513, 0
	special DrawWholeMapView

BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_KeepHoleOpen_Cb:
	goto_if_set FLAG_JOHTO_RELEASED_THE_BEASTS, BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_HideBasement_Cb
	setmetatile 6, 14, 513, 0
	setmetatile 7, 14, 513, 0
	setmetatile 6, 15, 513, 0
	setmetatile 7, 15, 513, 0
	special DrawWholeMapView

BurnedTower1F_Johto_BurnedTower1FHoleAndLadderCallback_HideBasement_Cb:
	return

BurnedTower1F_Johto_BurnedTowerMovement_PlayerWalksToRival:
	walk_left
	step_end

BurnedTower1F_Johto_BurnedTowerMovement_RivalWalksToPlayer:
	walk_right
	step_end

BurnedTower1F_Johto_BurnedTower1FMovement_PlayerStartsToFall:
	step_end

BurnedTower1F_Johto_BurnedTower1FEusineMovement:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

BurnedTower1F_Johto_BurnedTowerRival_BeforeText:
	.string "<……> <……> <……>"
	.string "\p…Oh, it's you."
	.string "\pI came looking for\n"
	.string "some legendary"
	.string "\pPOKéMON that they\n"
	.string "say roosts here."
	.string "\pBut there's\n"
	.string "nothing here!"
	.string "\pNothing after all\n"
	.string "the trouble of"
	.string "\pcoming to this\n"
	.string "dump? No way!"
	.string "\pIt's all your\n"
	.string "fault!$"

BurnedTower1F_Johto_BurnedTowerRival_WinText:
	.string "…Humph!"
	.string "\pThis is why I hate\n"
	.string "battling wimps."
	.string "\pThere's no\n"
	.string "challenge in it.$"

BurnedTower1F_Johto_BurnedTowerRival_AfterText1:
	.string "…Aw, whatever."
	.string "\pYou would never be\n"
	.string "able to catch a"
	.string "\plegendary POKéMON\n"
	.string "anyway.$"

BurnedTower1F_Johto_BurnedTowerRival_AfterText2:
	.string "Humph!"
	.string "\pWhat are you doing\n"
	.string "falling into a"
	.string "\phole? Some genius\n"
	.string "you are!"
	.string "\pServes you right!$"

BurnedTower1F_Johto_BurnedTower1FEusineIntroText:
	.string "EUSINE: My name's\n"
	.string "EUSINE."
	.string "\pI'm on the trail\n"
	.string "of a POKéMON named\l"
	.string "SUICUNE."
	.string "\pAnd you are…?"
	.string "\p{PLAYER}? Glad to\n"
	.string "meet you!"
	.string "\pI heard rumors\n"
	.string "that SUICUNE is in"
	.string "\pthis BURNED TOWER,\n"
	.string "so I came to look."
	.string "\pBut where exactly\n"
	.string "could it be?$"

BurnedTower1F_Johto_BurnedTower1FEusineText:
	.string "EUSINE: I heard\n"
	.string "that SUICUNE is in"
	.string "\pthis BURNED TOWER,\n"
	.string "so I came to look."
	.string "\pBut where exactly\n"
	.string "could it be?$"

BurnedTower1F_Johto_BurnedTower1FMortyText:
	.string "MORTY: ECRUTEAK's\n"
	.string "GYM LEADER has to"
	.string "\pstudy what are\n"
	.string "said to be the"
	.string "\plegendary POKéMON\n"
	.string "--SUICUNE, ENTEI\l"
	.string "and RAIKOU."
	.string "\pEUSINE is here, so\n"
	.string "I've decided to"
	.string "\pinvestigate the\n"
	.string "TOWER with him.$"
