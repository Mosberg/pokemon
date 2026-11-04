VictoryRoad_Johto_MapScripts::
	.byte 0

VictoryRoad_Johto_VictoryRoadTMEarthquake_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadTMEarthquake

VictoryRoad_Johto_VictoryRoadMaxRevive_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadMaxRevive

VictoryRoad_Johto_VictoryRoadFullRestore_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadFullRestore

VictoryRoad_Johto_VictoryRoadFullHeal_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadFullHeal

VictoryRoad_Johto_VictoryRoadHPUp_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadHPUp

VictoryRoad_Johto_VictoryRoadRivalLeft_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadRivalLeft

VictoryRoad_Johto_VictoryRoadRivalRight_Entry::
	lockall
	goto VictoryRoad_Johto_VictoryRoadRivalRight


VictoryRoad_Johto_VictoryRoadRivalLeft:
	setobjectxyperm 1, 18, 11
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	clearflag FLAG_JOHTO_RIVAL_VICTORY_ROAD
	addobject 1
	applymovement 1, VictoryRoad_Johto_VictoryRoadRivalBattleApproachMovement1
	waitmovement 1
	call VictoryRoad_Johto_VictoryRoadRivalNext_Sub
	applymovement 1, VictoryRoad_Johto_VictoryRoadRivalBattleExitMovement1
	waitmovement 1
	removeobject 1
	setvar VAR_JOHTO_SCENE_VICTORY_ROAD, 1
	fadedefaultbgm
	releaseall
	end

VictoryRoad_Johto_VictoryRoadRivalRight:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	clearflag FLAG_JOHTO_RIVAL_VICTORY_ROAD
	addobject 1
	applymovement 1, VictoryRoad_Johto_VictoryRoadRivalBattleApproachMovement2
	waitmovement 1
	call VictoryRoad_Johto_VictoryRoadRivalNext_Sub
	applymovement 1, VictoryRoad_Johto_VictoryRoadRivalBattleExitMovement2
	waitmovement 1
	removeobject 1
	setvar VAR_JOHTO_SCENE_VICTORY_ROAD, 1
	fadedefaultbgm
	releaseall
	end

VictoryRoad_Johto_VictoryRoadTMEarthquake:
	finditem ITEM_TM_EARTHQUAKE
	releaseall
	end

VictoryRoad_Johto_VictoryRoadMaxRevive:
	finditem ITEM_MAX_REVIVE
	releaseall
	end

VictoryRoad_Johto_VictoryRoadFullRestore:
	finditem ITEM_FULL_RESTORE
	releaseall
	end

VictoryRoad_Johto_VictoryRoadFullHeal:
	finditem ITEM_FULL_HEAL
	releaseall
	end

VictoryRoad_Johto_VictoryRoadHPUp:
	finditem ITEM_HP_UP
	releaseall
	end

VictoryRoad_Johto_VictoryRoadRivalNext_Sub:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message VictoryRoad_Johto_VictoryRoadRivalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_RIVAL_VICTORY_ROAD
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, VictoryRoad_Johto_VictoryRoadRivalNext_GotTotodile_Sub
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, VictoryRoad_Johto_VictoryRoadRivalNext_GotChikorita_Sub
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_5_TOTODILE, VictoryRoad_Johto_VictoryRoadRivalDefeatText
	goto VictoryRoad_Johto_VictoryRoadRivalNext_AfterBattle_Sub

VictoryRoad_Johto_VictoryRoadRivalNext_GotTotodile_Sub:
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_5_CHIKORITA, VictoryRoad_Johto_VictoryRoadRivalDefeatText
	goto VictoryRoad_Johto_VictoryRoadRivalNext_AfterBattle_Sub

VictoryRoad_Johto_VictoryRoadRivalNext_GotChikorita_Sub:
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_5_CYNDAQUIL, VictoryRoad_Johto_VictoryRoadRivalDefeatText
	goto VictoryRoad_Johto_VictoryRoadRivalNext_AfterBattle_Sub

VictoryRoad_Johto_VictoryRoadRivalNext_AfterBattle_Sub:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message VictoryRoad_Johto_VictoryRoadRivalAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return

VictoryRoad_Johto_VictoryRoadRivalBattleApproachMovement1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

VictoryRoad_Johto_VictoryRoadRivalBattleApproachMovement2:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

VictoryRoad_Johto_VictoryRoadRivalBattleExitMovement1:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VictoryRoad_Johto_VictoryRoadRivalBattleExitMovement2:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

VictoryRoad_Johto_VictoryRoadRivalBeforeText:
	.string "Hold it."
	.string "\p…Are you going to\n"
	.string "take the POKéMON\l"
	.string "LEAGUE challenge?"
	.string "\p…Don't make me\n"
	.string "laugh."
	.string "\pYou're so much\n"
	.string "weaker than I am."
	.string "\pI'm not like I was\n"
	.string "before."
	.string "\pI now have the\n"
	.string "best and strongest"
	.string "\pPOKéMON with me.\n"
	.string "I'm invincible!"
	.string "\p{PLAYER}!\n"
	.string "I challenge you!$"

VictoryRoad_Johto_VictoryRoadRivalDefeatText:
	.string "…I couldn't win…"
	.string "\pI gave it every-\n"
	.string "thing I had…"
	.string "\pWhat you possess,\n"
	.string "and what I lack…"
	.string "\pI'm beginning to\n"
	.string "understand what"
	.string "\pthat dragon master\n"
	.string "said to me…$"

VictoryRoad_Johto_VictoryRoadRivalAfterText:
	.string "…I haven't given up\n"
	.string "on becoming the\l"
	.string "greatest trainer…"
	.string "\pI'm going to find\n"
	.string "out why I can't"
	.string "\pwin and become\n"
	.string "stronger…"
	.string "\pWhen I do, I will\n"
	.string "challenge you."
	.string "\pAnd I'll beat you\n"
	.string "down with all my\l"
	.string "power."
	.string "\p…Humph! You keep\n"
	.string "at it until then.$"
