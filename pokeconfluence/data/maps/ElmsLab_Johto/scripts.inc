ElmsLab_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ElmsLab_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ElmsLab_Johto_OnFrame
	.byte 0

ElmsLab_Johto_OnTransition:
	call ElmsLab_Johto_ElmsLabMoveElmCallback_Cb
	end

ElmsLab_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ELMS_LAB, 0, ElmsLab_Johto_ElmsLabWalkUpToElmScript_Entry
	.2byte 0

ElmsLab_Johto_ProfElmScript_Entry::
	lockall
	goto ElmsLab_Johto_ProfElmScript

ElmsLab_Johto_ElmsAideScript_Entry::
	lockall
	goto ElmsLab_Johto_ElmsAideScript

ElmsLab_Johto_CyndaquilPokeBallScript_Entry::
	lockall
	goto ElmsLab_Johto_CyndaquilPokeBallScript

ElmsLab_Johto_TotodilePokeBallScript_Entry::
	lockall
	goto ElmsLab_Johto_TotodilePokeBallScript

ElmsLab_Johto_ChikoritaPokeBallScript_Entry::
	lockall
	goto ElmsLab_Johto_ChikoritaPokeBallScript

ElmsLab_Johto_CopScript_Entry::
	lockall
	goto ElmsLab_Johto_CopScript

ElmsLab_Johto_ElmsLabHealingMachine_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabHealingMachine

ElmsLab_Johto_ElmsLabBookshelf_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabBookshelf

ElmsLab_Johto_ElmsLabTravelTip1_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabTravelTip1

ElmsLab_Johto_ElmsLabTravelTip2_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabTravelTip2

ElmsLab_Johto_ElmsLabTravelTip3_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabTravelTip3

ElmsLab_Johto_ElmsLabTravelTip4_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabTravelTip4

ElmsLab_Johto_ElmsLabTrashcan_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabTrashcan

ElmsLab_Johto_ElmsLabWindow_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabWindow

ElmsLab_Johto_ElmsLabPC_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabPC

ElmsLab_Johto_LabTryToLeaveScript_Entry::
	lockall
	goto ElmsLab_Johto_LabTryToLeaveScript

ElmsLab_Johto_MeetCopScript_Entry::
	lockall
	goto ElmsLab_Johto_MeetCopScript

ElmsLab_Johto_MeetCopScript2_Entry::
	lockall
	goto ElmsLab_Johto_MeetCopScript2

ElmsLab_Johto_AideScript_WalkPotion1_Entry::
	lockall
	goto ElmsLab_Johto_AideScript_WalkPotion1

ElmsLab_Johto_AideScript_WalkPotion2_Entry::
	lockall
	goto ElmsLab_Johto_AideScript_WalkPotion2

ElmsLab_Johto_AideScript_WalkBalls1_Entry::
	lockall
	goto ElmsLab_Johto_AideScript_WalkBalls1

ElmsLab_Johto_AideScript_WalkBalls2_Entry::
	lockall
	goto ElmsLab_Johto_AideScript_WalkBalls2

ElmsLab_Johto_ElmsLabWalkUpToElmScript_Entry::
	lockall
	goto ElmsLab_Johto_ElmsLabWalkUpToElmScript


ElmsLab_Johto_ElmsLabWalkUpToElmScript:
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_ElmsLab_WalkUpToElmMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	message ElmsLab_Johto_ElmText_Intro
	waitmessage

ElmsLab_Johto_ElmsLabWalkUpToElmScript_MustSayYes:
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ElmsLabWalkUpToElmScript_ElmGetsEmail
	message ElmsLab_Johto_ElmText_Refused
	waitmessage
	goto ElmsLab_Johto_ElmsLabWalkUpToElmScript_MustSayYes

ElmsLab_Johto_ElmsLabWalkUpToElmScript_ElmGetsEmail:
	message ElmsLab_Johto_ElmText_Accepted
	waitmessage
	waitbuttonpress
	message ElmsLab_Johto_ElmText_ResearchAmbitions
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_PIN
	delay 30
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	message ElmsLab_Johto_ElmText_GotAnEmail
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	message ElmsLab_Johto_ElmText_MissionFromMrPokemon
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, ElmsLab_Johto_ElmsLab_ElmToDefaultPositionMovement1
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, ElmsLab_Johto_ElmsLab_ElmToDefaultPositionMovement2
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message ElmsLab_Johto_ElmText_ChooseAPokemon
	waitmessage
	waitbuttonpress
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 1
	closemessage
	releaseall
	end

ElmsLab_Johto_ProfElmScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SS_TICKET_FROM_ELM, ElmsLab_Johto_ElmCheckMasterBall
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, ElmsLab_Johto_ElmGiveTicketScript

ElmsLab_Johto_ElmCheckMasterBall:
	goto_if_set FLAG_JOHTO_GOT_MASTER_BALL_FROM_ELM, ElmsLab_Johto_ElmCheckEverstone
	goto_if_set FLAG_JOHTO_ENGINE_RISINGBADGE, ElmsLab_Johto_ElmGiveMasterBallScript

ElmsLab_Johto_ElmCheckEverstone:
	goto_if_set FLAG_JOHTO_GOT_EVERSTONE_FROM_ELM, ElmsLab_Johto_ElmScript_CallYou
	goto_if_set FLAG_JOHTO_SHOWED_TOGEPI_TO_ELM, ElmsLab_Johto_ElmGiveEverstoneScript
	goto_if_unset FLAG_JOHTO_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE, ElmsLab_Johto_ElmCheckTogepiEgg
	setvar VAR_0x8004, SPECIES_TOGEPI
	special JohtoFindPartyMonSpecies
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ShowElmTogepiScript
	setvar VAR_0x8004, SPECIES_TOGETIC
	special JohtoFindPartyMonSpecies
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ShowElmTogepiScript
	message ElmsLab_Johto_ElmThoughtEggHatchedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmEggHatchedScript:
	setvar VAR_0x8004, SPECIES_TOGEPI
	special JohtoFindPartyMonSpecies
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ShowElmTogepiScript
	setvar VAR_0x8004, SPECIES_TOGETIC
	special JohtoFindPartyMonSpecies
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ShowElmTogepiScript
	goto ElmsLab_Johto_ElmCheckGotEggAgain

ElmsLab_Johto_ElmCheckTogepiEgg:
	goto_if_unset FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, ElmsLab_Johto_ElmCheckGotEggAgain
	goto_if_set FLAG_JOHTO_TOGEPI_HATCHED, ElmsLab_Johto_ElmEggHatchedScript

ElmsLab_Johto_ElmCheckGotEggAgain:
	goto_if_set FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, ElmsLab_Johto_ElmWaitingEggHatchScript
	goto_if_set FLAG_JOHTO_ENGINE_ZEPHYRBADGE, ElmsLab_Johto_ElmAideHasEggScript
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, ElmsLab_Johto_ElmStudyingEggScript
	goto_if_set FLAG_JOHTO_GOT_MYSTERY_EGG_FROM_MR_POKEMON, ElmsLab_Johto_ElmAfterTheftScript
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, ElmsLab_Johto_ElmDescribesMrPokemonScript
	message ElmsLab_Johto_ElmText_LetYourMonBattleIt
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_LabTryToLeaveScript:
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	message ElmsLab_Johto_LabWhereGoingText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_ElmsLab_CantLeaveMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

ElmsLab_Johto_CyndaquilPokeBallScript:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, ElmsLab_Johto_LookAtElmPokeBallScript
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message ElmsLab_Johto_TakeCyndaquilText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_DidntChooseStarterScript
	removeobject 3
	setflag FLAG_JOHTO_GOT_CYNDAQUIL_FROM_ELM
	message ElmsLab_Johto_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	message ElmsLab_Johto_ReceivedStarterText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	givemon SPECIES_CYNDAQUIL, 5, ITEM_ORAN_BERRY
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, ElmsLab_Johto_ElmDirectionsScript
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_AfterCyndaquilMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto ElmsLab_Johto_ElmDirectionsScript

ElmsLab_Johto_TotodilePokeBallScript:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, ElmsLab_Johto_LookAtElmPokeBallScript
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	showmonpic SPECIES_TOTODILE, 10, 3
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message ElmsLab_Johto_TakeTotodileText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_DidntChooseStarterScript
	removeobject 4
	setflag FLAG_JOHTO_GOT_TOTODILE_FROM_ELM
	message ElmsLab_Johto_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	message ElmsLab_Johto_ReceivedStarterText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	givemon SPECIES_TOTODILE, 5, ITEM_ORAN_BERRY
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_AfterTotodileMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto ElmsLab_Johto_ElmDirectionsScript

ElmsLab_Johto_ChikoritaPokeBallScript:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, ElmsLab_Johto_LookAtElmPokeBallScript
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	showmonpic SPECIES_CHIKORITA, 10, 3
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message ElmsLab_Johto_TakeChikoritaText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_DidntChooseStarterScript
	removeobject 5
	setflag FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM
	message ElmsLab_Johto_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	message ElmsLab_Johto_ReceivedStarterText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	givemon SPECIES_CHIKORITA, 5, ITEM_ORAN_BERRY
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_AfterChikoritaMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto ElmsLab_Johto_ElmDirectionsScript

ElmsLab_Johto_DidntChooseStarterScript:
	message ElmsLab_Johto_DidntChooseStarterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmDirectionsScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message ElmsLab_Johto_ElmDirectionsText1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_PHONE_ELM_REGISTERED
	message ElmsLab_Johto_GotElmsNumberText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message ElmsLab_Johto_ElmDirectionsText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	message ElmsLab_Johto_ElmDirectionsText3
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM
	setflag FLAG_JOHTO_RIVAL_CHERRYGROVE_CITY
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 5
	setvar VAR_JOHTO_SCENE_NEW_BARK_TOWN, 1
	releaseall
	end

ElmsLab_Johto_ElmDescribesMrPokemonScript:
	message ElmsLab_Johto_ElmDescribesMrPokemonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_LookAtElmPokeBallScript:
	message ElmsLab_Johto_ElmPokeBallText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabHealingMachine:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, ElmsLab_Johto_ElmsLabHealingMachine_CanHeal
	message ElmsLab_Johto_ElmsLabHealingMachineText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabHealingMachine_CanHeal:
	message ElmsLab_Johto_ElmsLabHealingMachineText2
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ElmsLabHealingMachine_HealParty
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabHealingMachine_HealParty:
	special HealPlayerParty
	playbgm MUS_DUMMY, FALSE
	setvar VAR_RESULT, 0
	delay 30
	fadedefaultbgm
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmAfterTheftDoneScript:
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmAfterTheftScript:
	message ElmsLab_Johto_ElmAfterTheftText1
	waitmessage
	checkitem ITEM_MYSTERY_EGG, 1
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_ElmAfterTheftDoneScript
	waitbuttonpress
	message ElmsLab_Johto_ElmAfterTheftText2
	waitmessage
	waitbuttonpress
	removeitem ITEM_MYSTERY_EGG
	call ElmsLab_Johto_ElmJumpBackScript1_Sub
	message ElmsLab_Johto_ElmAfterTheftText3
	waitmessage
	waitbuttonpress
	call ElmsLab_Johto_ElmJumpBackScript2_Sub
	message ElmsLab_Johto_ElmAfterTheftText4
	waitmessage
	waitbuttonpress
	message ElmsLab_Johto_ElmAfterTheftText5
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM
	setflag FLAG_JOHTO_ENGINE_MOBILE_SYSTEM
	setvar VAR_JOHTO_SCENE_ROUTE_29, 1
	clearflag FLAG_JOHTO_ROUTE_30_YOUNGSTER_JOEY
	setflag FLAG_JOHTO_ROUTE_30_BATTLE
	message ElmsLab_Johto_ElmAfterTheftText6
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 6
	releaseall
	end

ElmsLab_Johto_ElmStudyingEggScript:
	message ElmsLab_Johto_ElmStudyingEggText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmAideHasEggScript:
	message ElmsLab_Johto_ElmAideHasEggText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmWaitingEggHatchScript:
	message ElmsLab_Johto_ElmWaitingEggHatchText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ShowElmTogepiScript:
	message ElmsLab_Johto_ShowElmTogepiText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	setflag FLAG_JOHTO_SHOWED_TOGEPI_TO_ELM
	message ElmsLab_Johto_ShowElmTogepiText2
	waitmessage
	waitbuttonpress
	message ElmsLab_Johto_ShowElmTogepiText3
	waitmessage
	waitbuttonpress

ElmsLab_Johto_ElmGiveEverstoneScript:
	message ElmsLab_Johto_ElmGiveEverstoneText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_ElmScript_NoRoomForEverstone
	message ElmsLab_Johto_ElmGiveEverstoneText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_GOT_EVERSTONE_FROM_ELM
	releaseall
	end

ElmsLab_Johto_ElmScript_CallYou:
	message ElmsLab_Johto_ElmText_CallYou
	waitmessage
	waitbuttonpress

ElmsLab_Johto_ElmScript_NoRoomForEverstone:
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmGiveMasterBallScript:
	message ElmsLab_Johto_ElmGiveMasterBallText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, 0, ElmsLab_Johto_ElmGiveMasterBallScript_notdone
	setflag FLAG_JOHTO_GOT_MASTER_BALL_FROM_ELM
	message ElmsLab_Johto_ElmGiveMasterBallText2
	waitmessage
	waitbuttonpress

ElmsLab_Johto_ElmGiveMasterBallScript_notdone:
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmGiveTicketScript:
	message ElmsLab_Johto_ElmGiveTicketText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_SS_TICKET
	setflag FLAG_JOHTO_GOT_SS_TICKET_FROM_ELM
	message ElmsLab_Johto_ElmGiveTicketText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_AideScript_WalkPotion1:
	applymovement 2, ElmsLab_Johto_AideWalksRight1
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	call ElmsLab_Johto_AideScript_GivePotion_Sub
	applymovement 2, ElmsLab_Johto_AideWalksLeft1
	waitmovement 2
	releaseall
	end

ElmsLab_Johto_AideScript_WalkPotion2:
	applymovement 2, ElmsLab_Johto_AideWalksRight2
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	call ElmsLab_Johto_AideScript_GivePotion_Sub
	applymovement 2, ElmsLab_Johto_AideWalksLeft2
	waitmovement 2
	releaseall
	end

ElmsLab_Johto_AideScript_WalkBalls1:
	applymovement 2, ElmsLab_Johto_AideWalksRight1
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	call ElmsLab_Johto_AideScript_GiveYouBalls_Sub
	applymovement 2, ElmsLab_Johto_AideWalksLeft1
	waitmovement 2
	releaseall
	end

ElmsLab_Johto_AideScript_WalkBalls2:
	applymovement 2, ElmsLab_Johto_AideWalksRight2
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	call ElmsLab_Johto_AideScript_GiveYouBalls_Sub
	applymovement 2, ElmsLab_Johto_AideWalksLeft2
	waitmovement 2
	releaseall
	end

ElmsLab_Johto_ElmsAideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, ElmsLab_Johto_AideScript_AfterTheft
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, ElmsLab_Johto_AideScript_ExplainBalls
	goto_if_set FLAG_JOHTO_GOT_MYSTERY_EGG_FROM_MR_POKEMON, ElmsLab_Johto_AideScript_TheftTestimony
	message ElmsLab_Johto_AideText_AlwaysBusy
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_AideScript_TheftTestimony:
	message ElmsLab_Johto_AideText_TheftTestimony
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_AideScript_ExplainBalls:
	message ElmsLab_Johto_AideText_ExplainBalls
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_AideScript_AfterTheft:
	message ElmsLab_Johto_AideText_AfterTheft
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_MeetCopScript2:
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_MeetCopScript2_StepLeft
	waitmovement OBJ_EVENT_ID_PLAYER

ElmsLab_Johto_MeetCopScript:
	applymovement OBJ_EVENT_ID_PLAYER, ElmsLab_Johto_MeetCopScript_WalkUp
	waitmovement OBJ_EVENT_ID_PLAYER

ElmsLab_Johto_CopScript:
	applymovement 6, Johto_Movement_Face_Left
	waitmovement 6
	message ElmsLab_Johto_ElmsLabOfficerText1
	waitmessage
	waitbuttonpress
	message ElmsLab_Johto_ElmsLabOfficerText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, ElmsLab_Johto_OfficerLeavesMovement
	waitmovement 6
	removeobject 6
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 2
	releaseall
	end

ElmsLab_Johto_ElmsLabWindow:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_VIOLET, ElmsLab_Johto_ElmsLabWindow_Normal
	goto_if_set FLAG_JOHTO_ELM_CALLED_ABOUT_STOLEN_POKEMON, ElmsLab_Johto_ElmsLabWindow_BreakIn
	goto ElmsLab_Johto_ElmsLabWindow_Normal

ElmsLab_Johto_ElmsLabWindow_BreakIn:
	message ElmsLab_Johto_ElmsLabWindowText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabWindow_Normal:
	message ElmsLab_Johto_ElmsLabWindowText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabTravelTip1:
	message ElmsLab_Johto_ElmsLabTravelTip1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabTravelTip2:
	message ElmsLab_Johto_ElmsLabTravelTip2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabTravelTip3:
	message ElmsLab_Johto_ElmsLabTravelTip3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabTravelTip4:
	message ElmsLab_Johto_ElmsLabTravelTip4Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabTrashcan:
	message ElmsLab_Johto_ElmsLabTrashcanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabPC:
	message ElmsLab_Johto_ElmsLabPCText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsLab_Johto_ElmsLabBookshelf:
	goto Johto_Std_DifficultBookshelfScript

ElmsLab_Johto_ElmJumpBackScript1_Sub:
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, ElmsLab_Johto_ElmJumpDownScript_Sub
	goto_if_eq VAR_RESULT, DIR_NORTH, ElmsLab_Johto_ElmJumpUpScript_Sub
	goto_if_eq VAR_RESULT, DIR_WEST, ElmsLab_Johto_ElmJumpLeftScript_Sub
	goto_if_eq VAR_RESULT, DIR_EAST, ElmsLab_Johto_ElmJumpRightScript_Sub
	return

ElmsLab_Johto_ElmJumpBackScript2_Sub:
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, ElmsLab_Johto_ElmJumpUpScript_Sub
	goto_if_eq VAR_RESULT, DIR_NORTH, ElmsLab_Johto_ElmJumpDownScript_Sub
	goto_if_eq VAR_RESULT, DIR_WEST, ElmsLab_Johto_ElmJumpRightScript_Sub
	goto_if_eq VAR_RESULT, DIR_EAST, ElmsLab_Johto_ElmJumpLeftScript_Sub
	return

ElmsLab_Johto_ElmJumpUpScript_Sub:
	applymovement 1, ElmsLab_Johto_ElmJumpUpMovement
	waitmovement 1
	return

ElmsLab_Johto_ElmJumpDownScript_Sub:
	applymovement 1, ElmsLab_Johto_ElmJumpDownMovement
	waitmovement 1
	return

ElmsLab_Johto_ElmJumpLeftScript_Sub:
	applymovement 1, ElmsLab_Johto_ElmJumpLeftMovement
	waitmovement 1
	return

ElmsLab_Johto_ElmJumpRightScript_Sub:
	applymovement 1, ElmsLab_Johto_ElmJumpRightMovement
	waitmovement 1
	return

ElmsLab_Johto_AideScript_GivePotion_Sub:
	message ElmsLab_Johto_AideText_GiveYouPotion
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	message ElmsLab_Johto_AideText_AlwaysBusy
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 2
	return

ElmsLab_Johto_AideScript_GiveYouBalls_Sub:
	message ElmsLab_Johto_AideText_GiveYouBalls
	waitmessage
	waitbuttonpress
	bufferitemname STR_VAR_2, ITEM_POKE_BALL
	call ElmsLab_Johto_AideScript_ReceiveTheBalls_Sub
	additem ITEM_POKE_BALL, 5
	message ElmsLab_Johto_AideText_ExplainBalls
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 2
	return

ElmsLab_Johto_AideScript_ReceiveTheBalls_Sub:
	goto Johto_Std_ReceiveItemScript_Sub

ElmsLab_Johto_ElmsLabMoveElmCallback_Cb:
	copyvar VAR_RESULT, VAR_JOHTO_SCENE_ELMS_LAB
	goto_if_ne VAR_RESULT, 0, ElmsLab_Johto_ElmsLabMoveElmCallback_Skip_Cb
	setobjectxyperm 1, 3, 4

ElmsLab_Johto_ElmsLabMoveElmCallback_Skip_Cb:
	return

ElmsLab_Johto_ElmsLab_WalkUpToElmMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_left
	step_end

ElmsLab_Johto_ElmsLab_CantLeaveMovement:
	walk_up
	step_end

ElmsLab_Johto_MeetCopScript2_StepLeft:
	walk_left
	step_end

ElmsLab_Johto_MeetCopScript_WalkUp:
	walk_up
	walk_up
	face_right
	step_end

ElmsLab_Johto_OfficerLeavesMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

ElmsLab_Johto_AideWalksRight1:
	walk_right
	walk_right
	face_up
	step_end

ElmsLab_Johto_AideWalksRight2:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

ElmsLab_Johto_AideWalksLeft1:
	walk_left
	walk_left
	face_down
	step_end

ElmsLab_Johto_AideWalksLeft2:
	walk_left
	walk_left
	walk_left
	face_down
	step_end

ElmsLab_Johto_ElmJumpUpMovement:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

ElmsLab_Johto_ElmJumpDownMovement:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end

ElmsLab_Johto_ElmJumpLeftMovement:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

ElmsLab_Johto_ElmJumpRightMovement:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

ElmsLab_Johto_ElmsLab_ElmToDefaultPositionMovement1:
	walk_up
	step_end

ElmsLab_Johto_ElmsLab_ElmToDefaultPositionMovement2:
	walk_right
	walk_right
	walk_up
	face_down
	step_end

ElmsLab_Johto_AfterCyndaquilMovement:
	walk_left
	walk_up
	face_up
	step_end

ElmsLab_Johto_AfterTotodileMovement:
	walk_left
	walk_left
	walk_up
	face_up
	step_end

ElmsLab_Johto_AfterChikoritaMovement:
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

ElmsLab_Johto_ElmText_Intro:
	.string "ELM: {PLAYER}!\n"
	.string "There you are!"
	.string "\pI needed to ask\n"
	.string "you a favor."
	.string "\pI'm conducting new\n"
	.string "POKéMON research"
	.string "\pright now. I was\n"
	.string "wondering if you"
	.string "\pcould help me with\n"
	.string "it, {PLAYER}."
	.string "\pYou see…"
	.string "\pI'm writing a\n"
	.string "paper that I want"
	.string "\pto present at a\n"
	.string "conference."
	.string "\pBut there are some\n"
	.string "things I don't"
	.string "\pquite understand\n"
	.string "yet."
	.string "\pSo!"
	.string "\pI'd like you to\n"
	.string "raise a POKéMON"
	.string "\pthat I recently\n"
	.string "caught.$"

ElmsLab_Johto_ElmText_Accepted:
	.string "Thanks, {PLAYER}!"
	.string "\pYou're a great\n"
	.string "help!$"

ElmsLab_Johto_ElmText_Refused:
	.string "But… Please, I\n"
	.string "need your help!$"

ElmsLab_Johto_ElmText_ResearchAmbitions:
	.string "When I announce my\n"
	.string "findings, I'm sure"
	.string "\pwe'll delve a bit\n"
	.string "deeper into the"
	.string "\pmany mysteries of\n"
	.string "POKéMON."
	.string "\pYou can count on\n"
	.string "it!$"

ElmsLab_Johto_ElmText_GotAnEmail:
	.string "Oh, hey! I got an\n"
	.string "e-mail!"
	.string "\p<……><……><……>\n"
	.string "Hm… Uh-huh…"
	.string "\pOkay…$"

ElmsLab_Johto_ElmText_MissionFromMrPokemon:
	.string "Hey, listen."
	.string "\pI have an acquain-\n"
	.string "tance called MR.\l"
	.string "POKéMON."
	.string "\pHe keeps finding\n"
	.string "weird things and"
	.string "\praving about his\n"
	.string "discoveries."
	.string "\pAnyway, I just got\n"
	.string "an e-mail from him"
	.string "\psaying that this\n"
	.string "time it's real."
	.string "\pIt is intriguing,\n"
	.string "but we're busy"
	.string "\pwith our POKéMON\n"
	.string "research…"
	.string "\pWait!"
	.string "\pI know!"
	.string "\p{PLAYER}, can you\n"
	.string "go in our place?$"

ElmsLab_Johto_ElmText_ChooseAPokemon:
	.string "I want you to\n"
	.string "raise one of the"
	.string "\pPOKéMON contained\n"
	.string "in these BALLS."
	.string "\pYou'll be that\n"
	.string "POKéMON's first\l"
	.string "partner, {PLAYER}!"
	.string "\pGo on. Pick one!$"

ElmsLab_Johto_ElmText_LetYourMonBattleIt:
	.string "If a wild POKéMON\n"
	.string "appears, let your\l"
	.string "POKéMON battle it!$"

ElmsLab_Johto_LabWhereGoingText:
	.string "ELM: Wait! Where\n"
	.string "are you going?$"

ElmsLab_Johto_TakeCyndaquilText:
	.string "ELM: You'll take\n"
	.string "CYNDAQUIL, the\l"
	.string "fire POKéMON?$"

ElmsLab_Johto_TakeTotodileText:
	.string "ELM: Do you want\n"
	.string "TOTODILE, the\l"
	.string "water POKéMON?$"

ElmsLab_Johto_TakeChikoritaText:
	.string "ELM: So, you like\n"
	.string "CHIKORITA, the\l"
	.string "grass POKéMON?$"

ElmsLab_Johto_DidntChooseStarterText:
	.string "ELM: Think it over\n"
	.string "carefully."
	.string "\pYour partner is\n"
	.string "important.$"

ElmsLab_Johto_ChoseStarterText:
	.string "ELM: I think\n"
	.string "that's a great\l"
	.string "POKéMON too!$"

ElmsLab_Johto_ReceivedStarterText:
	.string "{PLAYER} received\n"
	.string "{STR_VAR_1}!$"

ElmsLab_Johto_ElmDirectionsText1:
	.string "MR.POKéMON lives a\n"
	.string "little bit beyond"
	.string "\pCHERRYGROVE, the\n"
	.string "next city over."
	.string "\pIt's almost a\n"
	.string "direct route"
	.string "\pthere, so you\n"
	.string "can't miss it."
	.string "\pBut just in case,\n"
	.string "here's my phone"
	.string "\pnumber. Call me if\n"
	.string "anything comes up!$"

ElmsLab_Johto_ElmDirectionsText2:
	.string "If your POKéMON is\n"
	.string "hurt, you should"
	.string "\pheal it with this\n"
	.string "machine."
	.string "\pFeel free to use\n"
	.string "it anytime.$"

ElmsLab_Johto_ElmDirectionsText3:
	.string "{PLAYER}, I'm\n"
	.string "counting on you!$"

ElmsLab_Johto_GotElmsNumberText:
	.string "{PLAYER} got ELM's\n"
	.string "phone number.$"

ElmsLab_Johto_ElmDescribesMrPokemonText:
	.string "MR.POKéMON goes\n"
	.string "everywhere and\l"
	.string "finds rarities."
	.string "\pToo bad they're\n"
	.string "just rare and\l"
	.string "not very useful…$"

ElmsLab_Johto_ElmPokeBallText:
	.string "It contains a\n"
	.string "POKéMON caught by\l"
	.string "PROF.ELM.$"

ElmsLab_Johto_ElmsLabHealingMachineText1:
	.string "I wonder what this\n"
	.string "does?$"

ElmsLab_Johto_ElmsLabHealingMachineText2:
	.string "Would you like to\n"
	.string "heal your POKéMON?$"

ElmsLab_Johto_ElmAfterTheftText1:
	.string "ELM: {PLAYER}, this\n"
	.string "is terrible…"
	.string "\pOh, yes, what was\n"
	.string "MR.POKéMON's big\l"
	.string "discovery?$"

ElmsLab_Johto_ElmAfterTheftText2:
	.string "{PLAYER} handed\n"
	.string "the MYSTERY EGG to\l"
	.string "PROF.ELM.$"

ElmsLab_Johto_ElmAfterTheftText3:
	.string "ELM: This?$"

ElmsLab_Johto_ElmAfterTheftText4:
	.string "But… Is it a\n"
	.string "POKéMON EGG?"
	.string "\pIf it is, it is a\n"
	.string "great discovery!$"

ElmsLab_Johto_ElmAfterTheftText5:
	.string "ELM: What?!?"
	.string "\pPROF.OAK gave you\n"
	.string "a POKéDEX?"
	.string "\p{PLAYER}, is that\n"
	.string "true? Th-that's\l"
	.string "incredible!"
	.string "\pHe is superb at\n"
	.string "seeing the poten-\l"
	.string "tial of people as\l"
	.string "trainers."
	.string "\pWow, {PLAYER}. You\n"
	.string "may have what it"
	.string "\ptakes to become\n"
	.string "the CHAMPION."
	.string "\pYou seem to be\n"
	.string "getting on great\l"
	.string "with POKéMON too."
	.string "\pYou should take\n"
	.string "the POKéMON GYM\l"
	.string "challenge."
	.string "\pThe closest GYM\n"
	.string "would be the one\l"
	.string "in VIOLET CITY.$"

ElmsLab_Johto_ElmAfterTheftText6:
	.string "…{PLAYER}. The\n"
	.string "road to the"
	.string "\pchampionship will\n"
	.string "be a long one."
	.string "\pBefore you leave,\n"
	.string "make sure that you\l"
	.string "talk to your mom.$"

ElmsLab_Johto_ElmStudyingEggText:
	.string "ELM: Don't give\n"
	.string "up! I'll call if"
	.string "\pI learn anything\n"
	.string "about that EGG!$"

ElmsLab_Johto_ElmAideHasEggText:
	.string "ELM: {PLAYER}?\n"
	.string "Didn't you meet my\l"
	.string "assistant?"
	.string "\pHe should have met\n"
	.string "you with the EGG"
	.string "\pat VIOLET CITY's\n"
	.string "POKéMON CENTER."
	.string "\pYou must have just\n"
	.string "missed him. Try to\l"
	.string "catch him there.$"

ElmsLab_Johto_ElmWaitingEggHatchText:
	.string "ELM: Hey, has that\n"
	.string "EGG changed any?$"

ElmsLab_Johto_ElmThoughtEggHatchedText:
	.string "{PLAYER}? I thought\n"
	.string "the EGG hatched."
	.string "\pWhere is the\n"
	.string "POKéMON?$"

ElmsLab_Johto_ShowElmTogepiText1:
	.string "ELM: {PLAYER}, you\n"
	.string "look great!$"

ElmsLab_Johto_ShowElmTogepiText2:
	.string "What?\n"
	.string "That POKéMON!?!$"

ElmsLab_Johto_ShowElmTogepiText3:
	.string "The EGG hatched!\n"
	.string "So, POKéMON are\l"
	.string "born from EGGS…"
	.string "\pNo, perhaps not\n"
	.string "all POKéMON are."
	.string "\pWow, there's still\n"
	.string "a lot of research\l"
	.string "to be done.$"

ElmsLab_Johto_ElmGiveEverstoneText1:
	.string "Thanks, {PLAYER}!\n"
	.string "You're helping"
	.string "\punravel POKéMON\n"
	.string "mysteries for us!"
	.string "\pI want you to have\n"
	.string "this as a token of\l"
	.string "our appreciation.$"

ElmsLab_Johto_ElmGiveEverstoneText2:
	.string "That's an\n"
	.string "EVERSTONE."
	.string "\pSome species of\n"
	.string "POKéMON evolve"
	.string "\pwhen they grow to\n"
	.string "certain levels."
	.string "\pA POKéMON holding\n"
	.string "the EVERSTONE\l"
	.string "won't evolve."
	.string "\pGive it to a POKé-\n"
	.string "MON you don't want\l"
	.string "to evolve.$"

ElmsLab_Johto_ElmText_CallYou:
	.string "ELM: {PLAYER}, I'll\n"
	.string "call you if any-\l"
	.string "thing comes up.$"

ElmsLab_Johto_AideText_AfterTheft:
	.string "…sigh… That\n"
	.string "stolen POKéMON."
	.string "\pI wonder how it's\n"
	.string "doing."
	.string "\pThey say a POKéMON\n"
	.string "raised by a bad"
	.string "\pperson turns bad\n"
	.string "itself.$"

ElmsLab_Johto_ElmGiveMasterBallText1:
	.string "ELM: Hi, {PLAYER}!\n"
	.string "Thanks to you, my"
	.string "\presearch is going\n"
	.string "great!"
	.string "\pTake this as a\n"
	.string "token of my\l"
	.string "appreciation.$"

ElmsLab_Johto_ElmGiveMasterBallText2:
	.string "The MASTER BALL is\n"
	.string "the best!"
	.string "\pIt's the ultimate\n"
	.string "BALL! It'll catch"
	.string "\pany POKéMON with-\n"
	.string "out fail."
	.string "\pIt's given only to\n"
	.string "recognized POKéMON\l"
	.string "researchers."
	.string "\pI think you can\n"
	.string "make much better"
	.string "\puse of it than I\n"
	.string "can, {PLAYER}!$"

ElmsLab_Johto_ElmGiveTicketText1:
	.string "ELM: {PLAYER}!\n"
	.string "There you are!"
	.string "\pI called because I\n"
	.string "have something for\l"
	.string "you."
	.string "\pSee? It's an\n"
	.string "S.S.TICKET."
	.string "\pNow you can catch\n"
	.string "POKéMON in KANTO.$"

ElmsLab_Johto_ElmGiveTicketText2:
	.string "The ship departs\n"
	.string "from OLIVINE CITY."
	.string "\pBut you knew that\n"
	.string "already, {PLAYER}."
	.string "\pAfter all, you've\n"
	.string "traveled all over\l"
	.string "with your POKéMON."
	.string "\pGive my regards to\n"
	.string "PROF.OAK in KANTO!$"

ElmsLab_Johto_AideText_GiveYouPotion:
	.string "{PLAYER}, I want\n"
	.string "you to have this\l"
	.string "for your errand.$"

ElmsLab_Johto_AideText_AlwaysBusy:
	.string "There are only two\n"
	.string "of us, so we're\l"
	.string "always busy.$"

ElmsLab_Johto_AideText_TheftTestimony:
	.string "There was a loud\n"
	.string "noise outside…"
	.string "\pWhen we went to\n"
	.string "look, someone\l"
	.string "stole a POKéMON."
	.string "\pIt's unbelievable\n"
	.string "that anyone would\l"
	.string "do that!"
	.string "\p…sigh… That\n"
	.string "stolen POKéMON."
	.string "\pI wonder how it's\n"
	.string "doing."
	.string "\pThey say a POKéMON\n"
	.string "raised by a bad"
	.string "\pperson turns bad\n"
	.string "itself.$"

ElmsLab_Johto_AideText_GiveYouBalls:
	.string "{PLAYER}!"
	.string "\pUse these on your\n"
	.string "POKéDEX quest!$"

ElmsLab_Johto_AideText_ExplainBalls:
	.string "To add to your\n"
	.string "POKéDEX, you have\l"
	.string "to catch POKéMON."
	.string "\pThrow POKé BALLS\n"
	.string "at wild POKéMON\l"
	.string "to get them.$"

ElmsLab_Johto_ElmsLabOfficerText1:
	.string "I heard a POKéMON\n"
	.string "was stolen here…"
	.string "\pI was just getting\n"
	.string "some information\l"
	.string "from PROF.ELM."
	.string "\pApparently, it was\n"
	.string "a young male with\l"
	.string "long, red hair…"
	.string "\pWhat?"
	.string "\pYou battled a\n"
	.string "trainer like that?"
	.string "\pDid you happen to\n"
	.string "get his name?$"

ElmsLab_Johto_ElmsLabOfficerText2:
	.string "OK! So SILVER\n"
	.string "was his name."
	.string "\pThanks for helping\n"
	.string "my investigation!$"

ElmsLab_Johto_ElmsLabWindowText1:
	.string "The window's open."
	.string "\pA pleasant breeze\n"
	.string "is blowing in.$"

ElmsLab_Johto_ElmsLabWindowText2:
	.string "He broke in\n"
	.string "through here!$"

ElmsLab_Johto_ElmsLabTravelTip1Text:
	.string "{PLAYER} opened a\n"
	.string "book."
	.string "\pTravel Tip 1:"
	.string "\pPress START to\n"
	.string "open the MENU.$"

ElmsLab_Johto_ElmsLabTravelTip2Text:
	.string "{PLAYER} opened a\n"
	.string "book."
	.string "\pTravel Tip 2:"
	.string "\pRecord your trip\n"
	.string "with SAVE!$"

ElmsLab_Johto_ElmsLabTravelTip3Text:
	.string "{PLAYER} opened a\n"
	.string "book."
	.string "\pTravel Tip 3:"
	.string "\pOpen your PACK and\n"
	.string "press SELECT to\l"
	.string "move items.$"

ElmsLab_Johto_ElmsLabTravelTip4Text:
	.string "{PLAYER} opened a\n"
	.string "book."
	.string "\pTravel Tip 4:"
	.string "\pCheck your POKéMON\n"
	.string "moves. Press the"
	.string "\pA Button to switch\n"
	.string "moves.$"

ElmsLab_Johto_ElmsLabTrashcanText:
	.string "The wrapper from\n"
	.string "the snack PROF.ELM\l"
	.string "ate is in there…$"

ElmsLab_Johto_ElmsLabPCText:
	.string "OBSERVATIONS ON\n"
	.string "POKéMON EVOLUTION"
	.string "\p…It says on the\n"
	.string "screen…$"
