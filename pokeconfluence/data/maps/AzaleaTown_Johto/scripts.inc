AzaleaTown_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_Johto_OnTransition
	.byte 0

AzaleaTown_Johto_OnTransition:
	call AzaleaTown_Johto_AzaleaTownFlypointCallback_Cb
	end

AzaleaTown_Johto_AzaleaTownRocket1Script_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownRocket1Script

AzaleaTown_Johto_AzaleaTownGrampsScript_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownGrampsScript

AzaleaTown_Johto_AzaleaTownTeacherScript_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownTeacherScript

AzaleaTown_Johto_AzaleaTownYoungsterScript_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownYoungsterScript

AzaleaTown_Johto_AzaleaTownSlowpokeScript_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownSlowpokeScript

AzaleaTown_Johto_WhiteApricornTree_Entry::
	lockall
	goto AzaleaTown_Johto_WhiteApricornTree

AzaleaTown_Johto_AzaleaTownRocket2Script_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownRocket2Script

AzaleaTown_Johto_AzaleaTownKurtScript_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownKurtScript

AzaleaTown_Johto_AzaleaTownSign_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownSign

AzaleaTown_Johto_KurtsHouseSign_Entry::
	lockall
	goto AzaleaTown_Johto_KurtsHouseSign

AzaleaTown_Johto_AzaleaGymSign_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaGymSign

AzaleaTown_Johto_SlowpokeWellSign_Entry::
	lockall
	goto AzaleaTown_Johto_SlowpokeWellSign

AzaleaTown_Johto_CharcoalKilnSign_Entry::
	lockall
	goto AzaleaTown_Johto_CharcoalKilnSign

AzaleaTown_Johto_AzaleaTownPokecenterSign_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownPokecenterSign

AzaleaTown_Johto_AzaleaTownMartSign_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownMartSign

AzaleaTown_Johto_AzaleaTownIlextForestSign_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownIlextForestSign

AzaleaTown_Johto_AzaleaTownRivalBattleScene1_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScene1

AzaleaTown_Johto_AzaleaTownRivalBattleScene2_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScene2

AzaleaTown_Johto_AzaleaTownCelebiScene_Entry::
	lockall
	goto AzaleaTown_Johto_AzaleaTownCelebiScene


AzaleaTown_Johto_AzaleaTownRivalBattleScene1:
	setobjectxyperm 10, 11, 11
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	clearflag FLAG_JOHTO_RIVAL_AZALEA_TOWN
	addobject 10
	applymovement 10, AzaleaTown_Johto_AzaleaTownRivalBattleApproachMovement1
	waitmovement 10
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScript

AzaleaTown_Johto_AzaleaTownRivalBattleScene2:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	delay 15
	clearflag FLAG_JOHTO_RIVAL_AZALEA_TOWN
	addobject 10
	applymovement 10, AzaleaTown_Johto_AzaleaTownRivalBattleApproachMovement2
	waitmovement 10
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER

AzaleaTown_Johto_AzaleaTownRivalBattleScript:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message AzaleaTown_Johto_AzaleaTownRivalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_RIVAL_AZALEA_TOWN
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, AzaleaTown_Johto_AzaleaTownRivalBattleScript_Totodile
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, AzaleaTown_Johto_AzaleaTownRivalBattleScript_Chikorita
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_2_TOTODILE, AzaleaTown_Johto_AzaleaTownRivalWinText
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScript_AfterBattle

AzaleaTown_Johto_AzaleaTownRivalBattleScript_Totodile:
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_2_CHIKORITA, AzaleaTown_Johto_AzaleaTownRivalWinText
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScript_AfterBattle

AzaleaTown_Johto_AzaleaTownRivalBattleScript_Chikorita:
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_JOHTO_RIVAL1_RIVAL1_2_CYNDAQUIL, AzaleaTown_Johto_AzaleaTownRivalWinText
	goto AzaleaTown_Johto_AzaleaTownRivalBattleScript_AfterBattle

AzaleaTown_Johto_AzaleaTownRivalBattleScript_AfterBattle:
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message AzaleaTown_Johto_AzaleaTownRivalAfterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 10, AzaleaTown_Johto_AzaleaTownRivalBattleExitMovement
	waitmovement 10
	playse SE_EXIT
	removeobject 10
	setvar VAR_JOHTO_SCENE_AZALEA_TOWN, 0
	waitse
	fadedefaultbgm
	releaseall
	end

AzaleaTown_Johto_AzaleaTownRocket1Script:
	faceplayer
	message AzaleaTown_Johto_AzaleaTownRocket1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownRocket2Script:
	faceplayer
	message AzaleaTown_Johto_AzaleaTownRocket2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownGrampsScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_SLOWPOKE_WELL, AzaleaTown_Johto_AzaleaTownGrampsScript_ClearedWell
	message AzaleaTown_Johto_AzaleaTownGrampsTextBefore
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownGrampsScript_ClearedWell:
	message AzaleaTown_Johto_AzaleaTownGrampsTextAfter
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownTeacherScript:
	faceplayer
	message AzaleaTown_Johto_AzaleaTownTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownYoungsterScript:
	faceplayer
	message AzaleaTown_Johto_AzaleaTownYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownSlowpokeScript:
	message AzaleaTown_Johto_AzaleaTownSlowpokeText1
	waitmessage
	delay 60
	message AzaleaTown_Johto_AzaleaTownSlowpokeText2
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownCelebiScene:
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Johto_AzaleaTownPlayerLeavesKurtsHouseMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	message AzaleaTown_Johto_AzaleaTownKurtText1
	waitmessage
	waitbuttonpress
	applymovement 12, Johto_Movement_Face_Right
	waitmovement 12
	message AzaleaTown_Johto_AzaleaTownKurtText2
	waitmessage
	waitbuttonpress
	message AzaleaTown_Johto_AzaleaTownKurtText3
	waitmessage
	waitbuttonpress
	giveitem ITEM_GS_BALL
	applymovement 12, Johto_Movement_Face_Left
	waitmovement 12
	setflag FLAG_JOHTO_ENGINE_FOREST_IS_RESTLESS
	clearflag FLAG_JOHTO_ILEX_FOREST_LASS
	setflag FLAG_JOHTO_ROUTE_34_ILEX_FOREST_GATE_LASS
	setvar VAR_JOHTO_SCENE_AZALEA_TOWN, 0
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownKurtScript:
	faceplayer
	message AzaleaTown_Johto_AzaleaTownKurtText3
	waitmessage
	waitbuttonpress
	applymovement 12, Johto_Movement_Face_Left
	waitmovement 12
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownSign:
	message AzaleaTown_Johto_AzaleaTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_KurtsHouseSign:
	message AzaleaTown_Johto_KurtsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaGymSign:
	message AzaleaTown_Johto_AzaleaGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_SlowpokeWellSign:
	message AzaleaTown_Johto_SlowpokeWellSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_CharcoalKilnSign:
	message AzaleaTown_Johto_CharcoalKilnSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownIlextForestSign:
	message AzaleaTown_Johto_AzaleaTownIlexForestSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaTown_Johto_AzaleaTownPokecenterSign:
	goto Johto_Std_PokecenterSignScript

AzaleaTown_Johto_AzaleaTownMartSign:
	goto Johto_Std_MartSignScript

AzaleaTown_Johto_WhiteApricornTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_AZALEA_TOWN, Johto_Std_FruitTreeEmpty
	giveitem ITEM_WHT_APRICORN
	setflag FLAG_JOHTO_FRUITTREE_AZALEA_TOWN
	releaseall
	end

AzaleaTown_Johto_AzaleaTownFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_AZALEA
	return

AzaleaTown_Johto_AzaleaTownRivalBattleApproachMovement1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

AzaleaTown_Johto_AzaleaTownRivalBattleApproachMovement2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

AzaleaTown_Johto_AzaleaTownRivalBattleExitMovement:
	walk_left
	walk_left
	walk_left
	step_end

AzaleaTown_Johto_AzaleaTownPlayerLeavesKurtsHouseMovement:
	walk_left
	walk_left
	walk_up
	face_left
	step_end

AzaleaTown_Johto_AzaleaTownRivalBeforeText:
	.string "…Tell me some-\n"
	.string "thing."
	.string "\pIs it true that\n"
	.string "TEAM ROCKET has\l"
	.string "returned?"
	.string "\pWhat? You beat\n"
	.string "them? Hah! Quit\l"
	.string "lying."
	.string "\pYou're not joking?\n"
	.string "Then let's see how\l"
	.string "good you are.$"

AzaleaTown_Johto_AzaleaTownRivalWinText:
	.string "… Humph! Useless\n"
	.string "POKéMON!"
	.string "\pListen, you. You\n"
	.string "only won because"
	.string "\pmy POKéMON were\n"
	.string "weak.$"

AzaleaTown_Johto_AzaleaTownRivalAfterText:
	.string "I hate the weak."
	.string "\pPOKéMON, trainers.\n"
	.string "It doesn't matter\l"
	.string "who or what."
	.string "\pI'm going to be\n"
	.string "strong and wipe\l"
	.string "out the weak."
	.string "\pThat goes for TEAM\n"
	.string "ROCKET too."
	.string "\pThey act big and\n"
	.string "tough in a group."
	.string "\pBut get them\n"
	.string "alone, and they're\l"
	.string "weak."
	.string "\pI hate them all."
	.string "\pYou stay out of my\n"
	.string "way. A weakling"
	.string "\plike you is only a\n"
	.string "distraction.$"

AzaleaTown_Johto_AzaleaTownRocket1Text:
	.string "It's unsafe to go\n"
	.string "in there, so I'm\l"
	.string "standing guard."
	.string "\pAren't I a good\n"
	.string "Samaritan?$"

AzaleaTown_Johto_AzaleaTownRocket2Text:
	.string "Do you know about\n"
	.string "SLOWPOKETAIL? I\l"
	.string "heard it's tasty!"
	.string "\pAren't you glad I\n"
	.string "told you that?$"

AzaleaTown_Johto_AzaleaTownGrampsTextBefore:
	.string "The SLOWPOKE have\n"
	.string "disappeared from\l"
	.string "town…"
	.string "\pI heard their\n"
	.string "TAILS are being\l"
	.string "sold somewhere.$"

AzaleaTown_Johto_AzaleaTownGrampsTextAfter:
	.string "The SLOWPOKE have\n"
	.string "returned."
	.string "\pKnowing them, they\n"
	.string "could've just been"
	.string "\pgoofing off some-\n"
	.string "where.$"

AzaleaTown_Johto_AzaleaTownTeacherText:
	.string "Did you come to\n"
	.string "get KURT to make\l"
	.string "some BALLS?"
	.string "\pA lot of people do\n"
	.string "just that.$"

AzaleaTown_Johto_AzaleaTownYoungsterText:
	.string "Cut through AZALEA\n"
	.string "and you'll be in\l"
	.string "ILEX FOREST."
	.string "\pBut these skinny\n"
	.string "trees make it"
	.string "\pimpossible to get\n"
	.string "through."
	.string "\pThe CHARCOAL MAN's\n"
	.string "POKéMON can CUT\l"
	.string "down trees.$"

AzaleaTown_Johto_AzaleaTownSlowpokeText1:
	.string "SLOWPOKE: …"
	.string "\p… … …$"

AzaleaTown_Johto_AzaleaTownSlowpokeText2:
	.string "… …Yawn?$"

AzaleaTown_Johto_AzaleaTownKurtText1:
	.string "ILEX FOREST is\n"
	.string "restless!"
	.string "\pWhat is going on?$"

AzaleaTown_Johto_AzaleaTownKurtText2:
	.string "{PLAYER}, here's\n"
	.string "your GS BALL back!$"

AzaleaTown_Johto_AzaleaTownKurtText3:
	.string "Could you go see\n"
	.string "why ILEX FOREST is\l"
	.string "so restless?$"

AzaleaTown_Johto_AzaleaTownSignText:
	.string "AZALEA TOWN\n"
	.string "Where People and"
	.string "\pPOKéMON Live in\n"
	.string "Happy Harmony$"

AzaleaTown_Johto_KurtsHouseSignText:
	.string "KURT'S HOUSE$"

AzaleaTown_Johto_AzaleaGymSignText:
	.string "AZALEA TOWN\n"
	.string "POKéMON GYM\l"
	.string "LEADER: BUGSY"
	.string "\pThe Walking\n"
	.string "Bug POKéMON\l"
	.string "Encyclopedia$"

AzaleaTown_Johto_SlowpokeWellSignText:
	.string "SLOWPOKE WELL"
	.string "\pAlso known as the\n"
	.string "RAINMAKER WELL."
	.string "\pLocals believe\n"
	.string "that a SLOWPOKE's\l"
	.string "yawn summons rain."
	.string "\pRecords show that\n"
	.string "a SLOWPOKE's yawn"
	.string "\pended a drought\n"
	.string "400 years ago.$"

AzaleaTown_Johto_CharcoalKilnSignText:
	.string "CHARCOAL KILN$"

AzaleaTown_Johto_AzaleaTownIlexForestSignText:
	.string "ILEX FOREST"
	.string "\pEnter through the\n"
	.string "gate.$"
