TinTower1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TinTower1F_Johto_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower1F_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TinTower1F_Johto_OnFrame
	.byte 0

TinTower1F_Johto_OnLoad:
	call TinTower1F_Johto_TinTower1FStairsCallback_Cb
	end

TinTower1F_Johto_OnTransition:
	call TinTower1F_Johto_TinTower1FNPCsCallback_Cb
	end

TinTower1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_TIN_TOWER_1F, 0, TinTower1F_Johto_TinTower1FSuicuneBattleScript_Entry
	.2byte 0

TinTower1F_Johto_TinTower1FEusine_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FEusine

TinTower1F_Johto_TinTower1FSage1Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage1Script

TinTower1F_Johto_TinTower1FSage2Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage2Script

TinTower1F_Johto_TinTower1FSage3Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage3Script

TinTower1F_Johto_TinTower1FSage4Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage4Script

TinTower1F_Johto_TinTower1FSage5Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage5Script

TinTower1F_Johto_TinTower1FSage6Script_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSage6Script

TinTower1F_Johto_TinTower1FSuicuneBattleScript_Entry::
	lockall
	goto TinTower1F_Johto_TinTower1FSuicuneBattleScript


TinTower1F_Johto_TinTower1FSuicuneBattleScript:
	applymovement OBJ_EVENT_ID_PLAYER, TinTower1F_Johto_TinTower1FPlayerEntersMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	setvar VAR_0x8004, SPECIES_RAIKOU
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_ne VAR_RESULT, 0, TinTower1F_Johto_TinTower1FSuicuneBattleScript_Next1
	applymovement 2, TinTower1F_Johto_TinTower1FRaikouApproachesMovement
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	waitmoncry
	delay 10
	playse SE_WARP_OUT
	applymovement 2, TinTower1F_Johto_TinTower1FRaikouLeavesMovement
	waitmovement 2
	removeobject 2
	playse SE_EXIT
	waitse

TinTower1F_Johto_TinTower1FSuicuneBattleScript_Next1:
	setvar VAR_0x8004, SPECIES_ENTEI
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_ne VAR_RESULT, 0, TinTower1F_Johto_TinTower1FSuicuneBattleScript_Next2
	applymovement 3, TinTower1F_Johto_TinTower1FEnteiApproachesMovement
	waitmovement 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	waitmoncry
	delay 10
	playse SE_WARP_OUT
	applymovement 3, TinTower1F_Johto_TinTower1FEnteiLeavesMovement
	waitmovement 3
	removeobject 3
	playse SE_EXIT
	waitse

TinTower1F_Johto_TinTower1FSuicuneBattleScript_Next2:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, TinTower1F_Johto_TinTower1FPlayerBacksUpMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, TinTower1F_Johto_TinTower1FSuicuneApproachesMovement
	waitmovement 1
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 20
	setwildbattle SPECIES_SUICUNE, 40
	dowildbattle
	removeobject 1
	setflag FLAG_JOHTO_FOUGHT_SUICUNE
	setflag FLAG_JOHTO_SAW_SUICUNE_ON_ROUTE_42
	setvar VAR_JOHTO_SCENE_ROUTE_42, 0
	setflag FLAG_JOHTO_SAW_SUICUNE_ON_ROUTE_36
	setvar VAR_JOHTO_SCENE_ROUTE_36, 0
	setflag FLAG_JOHTO_SAW_SUICUNE_AT_CIANWOOD_CITY
	setvar VAR_JOHTO_SCENE_CIANWOOD_CITY, 0
	setvar VAR_JOHTO_SCENE_TIN_TOWER_1F, 1
	clearflag FLAG_JOHTO_SET_WHEN_FOUGHT_HO_OH
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_DUMMY, FALSE
	playse SE_DOOR
	setobjectxyperm 4, 10, 15
	clearflag FLAG_JOHTO_TIN_TOWER_1F_EUSINE
	addobject 4
	applymovement 4, TinTower1F_Johto_TinTower1FEusineEntersMovement
	waitmovement 4
	playse SE_DOOR
	setobjectxyperm 5, 9, 15
	clearflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_1
	addobject 5
	applymovement 5, TinTower1F_Johto_TinTower1FSage1EntersMovement
	waitmovement 5
	playse SE_DOOR
	setobjectxyperm 6, 9, 15
	clearflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_1
	addobject 6
	applymovement 6, TinTower1F_Johto_TinTower1FSage2EntersMovement
	waitmovement 6
	playse SE_DOOR
	setobjectxyperm 7, 9, 15
	clearflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_1
	addobject 7
	applymovement 7, TinTower1F_Johto_TinTower1FSage3EntersMovement
	waitmovement 7
	setobjectxyperm 5, 7, 13
	setobjectxyperm 6, 9, 13
	setobjectxyperm 7, 11, 13
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message TinTower1F_Johto_TinTower1FEusineSuicuneText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, TinTower1F_Johto_TinTower1FEusineLeavesMovement
	waitmovement 4
	playse SE_EXIT
	removeobject 4
	waitse
	fadeoutbgm 4
	delay 20
	fadedefaultbgm
	releaseall
	end

TinTower1F_Johto_TinTower1FSage1Script:
	faceplayer
	message TinTower1F_Johto_TinTower1FSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage2Script:
	faceplayer
	message TinTower1F_Johto_TinTower1FSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage3Script:
	faceplayer
	message TinTower1F_Johto_TinTower1FSage3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage4Script:
	goto_if_set FLAG_JOHTO_FOUGHT_HO_OH, TinTower1F_Johto_TinTower1FSage4Script_FoughtHoOh
	faceplayer
	message TinTower1F_Johto_TinTower1FSage4Text1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage4Script_FoughtHoOh:
	faceplayer
	message TinTower1F_Johto_TinTower1FSage4Text2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage5Script:
	faceplayer
	goto_if_set FLAG_JOHTO_FOUGHT_HO_OH, TinTower1F_Johto_TinTower1FSage5Script_FoughtHoOh
	goto_if_set FLAG_JOHTO_GOT_RAINBOW_WING, TinTower1F_Johto_TinTower1FSage5Script_GotRainbowWing
	message TinTower1F_Johto_TinTower1FSage5Text1
	waitmessage
	waitbuttonpress
	giveitem ITEM_RAINBOW_WING
	closemessage
	waitse
	playse SE_M_STRENGTH
	setmetatile 10, 2, 515, 0
	setmetatile 11, 2, 513, 0
	setmetatile 10, 3, 513, 0
	setmetatile 11, 3, 513, 0
	special DrawWholeMapView
	setflag FLAG_JOHTO_GOT_RAINBOW_WING
	closemessage

TinTower1F_Johto_TinTower1FSage5Script_GotRainbowWing:
	message TinTower1F_Johto_TinTower1FSage5Text2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage5Script_FoughtHoOh:
	message TinTower1F_Johto_TinTower1FSage5Text3
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage6Script:
	goto_if_set FLAG_JOHTO_FOUGHT_HO_OH, TinTower1F_Johto_TinTower1FSage6Script_FoughtHoOh
	faceplayer
	message TinTower1F_Johto_TinTower1FSage6Text1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FSage6Script_FoughtHoOh:
	faceplayer
	message TinTower1F_Johto_TinTower1FSage6Text2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FEusine:
	faceplayer
	message TinTower1F_Johto_TinTower1FEusineHoOhText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TinTower1F_Johto_TinTower1FNPCsCallback_Cb:
	goto_if_set FLAG_JOHTO_GOT_RAINBOW_WING, TinTower1F_Johto_TinTower1FNPCsCallback_GotRainbowWing_Cb
	goto_if_unset FLAG_JOHTO_BEAT_ELITE_FOUR, TinTower1F_Johto_TinTower1FNPCsCallback_FaceBeasts_Cb
	goto_if_unset FLAG_JOHTO_FOUGHT_SUICUNE, TinTower1F_Johto_TinTower1FNPCsCallback_FaceBeasts_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_2
	setflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_1

TinTower1F_Johto_TinTower1FNPCsCallback_GotRainbowWing_Cb:
	goto_if_unset FLAG_JOHTO_FOUGHT_HO_OH, TinTower1F_Johto_TinTower1FNPCsCallback_Done_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_EUSINE

TinTower1F_Johto_TinTower1FNPCsCallback_Done_Cb:
	return

TinTower1F_Johto_TinTower1FNPCsCallback_FaceBeasts_Cb:
	goto_if_set FLAG_JOHTO_FOUGHT_SUICUNE, TinTower1F_Johto_TinTower1FNPCsCallback_FoughtSuicune_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_SUICUNE
	setvar VAR_0x8004, SPECIES_RAIKOU
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_ne VAR_RESULT, 0, TinTower1F_Johto_TinTower1FNPCsCallback_NoRaikou_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_RAIKOU
	goto TinTower1F_Johto_TinTower1FNPCsCallback_CheckEntei_Cb

TinTower1F_Johto_TinTower1FNPCsCallback_NoRaikou_Cb:
	setflag FLAG_JOHTO_TIN_TOWER_1F_RAIKOU

TinTower1F_Johto_TinTower1FNPCsCallback_CheckEntei_Cb:
	setvar VAR_0x8004, SPECIES_ENTEI
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_ne VAR_RESULT, 0, TinTower1F_Johto_TinTower1FNPCsCallback_NoEntei_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_ENTEI
	goto TinTower1F_Johto_TinTower1FNPCsCallback_BeastsDone_Cb

TinTower1F_Johto_TinTower1FNPCsCallback_NoEntei_Cb:
	setflag FLAG_JOHTO_TIN_TOWER_1F_ENTEI

TinTower1F_Johto_TinTower1FNPCsCallback_BeastsDone_Cb:
	return

TinTower1F_Johto_TinTower1FNPCsCallback_FoughtSuicune_Cb:
	setflag FLAG_JOHTO_TIN_TOWER_1F_SUICUNE
	setflag FLAG_JOHTO_TIN_TOWER_1F_RAIKOU
	setflag FLAG_JOHTO_TIN_TOWER_1F_ENTEI
	clearflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_1
	setflag FLAG_JOHTO_TIN_TOWER_1F_WISE_TRIO_2
	return

TinTower1F_Johto_TinTower1FStairsCallback_Cb:
	goto_if_set FLAG_JOHTO_GOT_RAINBOW_WING, TinTower1F_Johto_TinTower1FStairsCallback_DontHideStairs_Cb
	setmetatile 10, 2, 513, 0
	setmetatile 11, 2, 513, 0
	setmetatile 10, 3, 513, 0
	setmetatile 11, 3, 513, 0
	special DrawWholeMapView

TinTower1F_Johto_TinTower1FStairsCallback_DontHideStairs_Cb:
	return

TinTower1F_Johto_TinTower1FPlayerEntersMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

TinTower1F_Johto_TinTower1FRaikouApproachesMovement:
	jump_down
	step_end

TinTower1F_Johto_TinTower1FRaikouLeavesMovement:
	jump_down
	jump_right
	jump_down
	step_end

TinTower1F_Johto_TinTower1FEnteiApproachesMovement:
	jump_down
	step_end

TinTower1F_Johto_TinTower1FEnteiLeavesMovement:
	jump_down
	jump_left
	jump_down
	step_end

TinTower1F_Johto_TinTower1FSuicuneApproachesMovement:
	jump_down
	step_end

TinTower1F_Johto_TinTower1FPlayerBacksUpMovement:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end

TinTower1F_Johto_TinTower1FEusineEntersMovement:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

TinTower1F_Johto_TinTower1FEusineLeavesMovement:
	walk_down
	walk_down
	walk_down
	step_end

TinTower1F_Johto_TinTower1FSage1EntersMovement:
	walk_up
	walk_up
	walk_left
	walk_left
	face_up
	step_end

TinTower1F_Johto_TinTower1FSage2EntersMovement:
	walk_up
	walk_up
	step_end

TinTower1F_Johto_TinTower1FSage3EntersMovement:
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

TinTower1F_Johto_TinTower1FEusineSuicuneText:
	.string "EUSINE: Awesome!\n"
	.string "Too awesome, even!"
	.string "\pI've never seen a\n"
	.string "battle that great."
	.string "\pThat was truly\n"
	.string "inspiring to see."
	.string "\pSUICUNE was tough,\n"
	.string "but you were even"
	.string "\pmore incredible,\n"
	.string "{PLAYER}."
	.string "\pI heard SUICUNE's\n"
	.string "mystic power"
	.string "\psummons a rainbow-\n"
	.string "colored POKéMON."
	.string "\pMaybe, just maybe,\n"
	.string "what went on today"
	.string "\pwill cause that\n"
	.string "POKéMON to appear."
	.string "\pI'm going to study\n"
	.string "the legends more."
	.string "\pThanks for showing\n"
	.string "me that fantastic\l"
	.string "battle."
	.string "\pLater, {PLAYER}!$"

TinTower1F_Johto_TinTower1FSage1Text:
	.string "According to\n"
	.string "legend…"
	.string "\pWhen the souls of\n"
	.string "POKéMON and humans"
	.string "\pcommune, from the\n"
	.string "heavens descends a"
	.string "\pPOKéMON of rainbow\n"
	.string "colors…"
	.string "\pCould it mean the\n"
	.string "legendary POKéMON"
	.string "\pare testing us\n"
	.string "humans?$"

TinTower1F_Johto_TinTower1FSage2Text:
	.string "When the BRASS\n"
	.string "TOWER burned down,"
	.string "\pthree nameless\n"
	.string "POKéMON were said"
	.string "\pto have perished.\n"
	.string "It was tragic."
	.string "\pHowever…"
	.string "\pA rainbow-colored\n"
	.string "POKéMON…"
	.string "\pIn other words…"
	.string "\pHO-OH descended\n"
	.string "from the sky and"
	.string "\pgave new life to\n"
	.string "the three POKéMON."
	.string "\pThey are…"
	.string "\pSUICUNE, ENTEI and\n"
	.string "RAIKOU."
	.string "\pThat is what they\n"
	.string "say.$"

TinTower1F_Johto_TinTower1FSage3Text:
	.string "The two TOWERS are\n"
	.string "said to have been"
	.string "\pbuilt to foster\n"
	.string "friendship and"
	.string "\phope between POKé-\n"
	.string "MON and people."
	.string "\pThat was 700 years\n"
	.string "ago, but the ideal"
	.string "\pstill remains\n"
	.string "important today.$"

TinTower1F_Johto_TinTower1FSage4Text1:
	.string "HO-OH appears to\n"
	.string "have descended"
	.string "\pupon this, the TIN\n"
	.string "TOWER!$"

TinTower1F_Johto_TinTower1FSage5Text1:
	.string "This will protect\n"
	.string "you. Take it.$"

TinTower1F_Johto_TinTower1FSage5Text2:
	.string "Now, go.$"

TinTower1F_Johto_TinTower1FSage6Text1:
	.string "I believe you are\n"
	.string "being tested."
	.string "\pFree your mind\n"
	.string "from uncertainty,\l"
	.string "and advance.$"

TinTower1F_Johto_TinTower1FEusineHoOhText:
	.string "I knew it."
	.string "\pI knew you'd get\n"
	.string "to see the POKéMON"
	.string "\pof rainbow colors,\n"
	.string "{PLAYER}."
	.string "\pIt happened just\n"
	.string "as I envisioned."
	.string "\pMy research isn't\n"
	.string "bad, I might say."
	.string "\pI'm going to keep\n"
	.string "studying POKéMON"
	.string "\pto become a famous\n"
	.string "POKéMANIAC!$"

TinTower1F_Johto_TinTower1FSage4Text2:
	.string "The legendary\n"
	.string "POKéMON are said"
	.string "\pto embody three\n"
	.string "powers…"
	.string "\pThe lightning that\n"
	.string "struck the TOWER."
	.string "\pThe fire that\n"
	.string "burned the TOWER."
	.string "\pAnd the rain that\n"
	.string "put out the fire…$"

TinTower1F_Johto_TinTower1FSage5Text3:
	.string "When the legendary\n"
	.string "POKéMON appeared…"
	.string "\pThey struck terror\n"
	.string "in those who saw\l"
	.string "their rise."
	.string "\pAnd…"
	.string "\pSome even took to\n"
	.string "futile attacks."
	.string "\pThe legendary\n"
	.string "POKéMON, knowing"
	.string "\ptheir own power,\n"
	.string "fled, ignoring the\l"
	.string "frightened people.$"

TinTower1F_Johto_TinTower1FSage6Text2:
	.string "Of the legendary\n"
	.string "POKéMON, SUICUNE"
	.string "\pis said to be the\n"
	.string "closest to HO-OH."
	.string "\pI hear there may\n"
	.string "also be a link to"
	.string "\pPOKéMON known as\n"
	.string "UNOWN."
	.string "\pThe POKéMON UNOWN\n"
	.string "must be sharing a"
	.string "\pcooperative bond\n"
	.string "with SUICUNE.$"
