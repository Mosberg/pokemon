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
	@ TODO unsupported: special MonCheck
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special BeastsCheck
	return

TinTower1F_Johto_TinTower1FNPCsCallback_GotRainbowWing_Cb:
	goto_if_unset FLAG_JOHTO_FOUGHT_HO_OH, TinTower1F_Johto_TinTower1FNPCsCallback_Done_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_EUSINE

TinTower1F_Johto_TinTower1FNPCsCallback_Done_Cb:
	return

TinTower1F_Johto_TinTower1FNPCsCallback_FaceBeasts_Cb:
	goto_if_set FLAG_JOHTO_FOUGHT_SUICUNE, TinTower1F_Johto_TinTower1FNPCsCallback_FoughtSuicune_Cb
	clearflag FLAG_JOHTO_TIN_TOWER_1F_SUICUNE
	setvar VAR_0x8004, SPECIES_RAIKOU
	@ TODO unsupported: special MonCheck
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
