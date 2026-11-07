GoldenrodCity_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_Johto_OnTransition
	.byte 0

GoldenrodCity_Johto_OnTransition:
	call GoldenrodCity_Johto_GoldenrodCityFlypointAndFloriaCallback_Cb
	call GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_Cb
	end

GoldenrodCity_Johto_GoldenrodCityPokefanMScript_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityPokefanMScript

GoldenrodCity_Johto_GoldenrodCityYoungster1Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityYoungster1Script

GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Script

GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Script

GoldenrodCity_Johto_GoldenrodCityYoungster2Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityYoungster2Script

GoldenrodCity_Johto_GoldenrodCityLassScript_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityLassScript

GoldenrodCity_Johto_GoldenrodCityGrampsScript_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityGrampsScript

GoldenrodCity_Johto_GoldenrodCityRocketScoutScript_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocketScoutScript

GoldenrodCity_Johto_GoldenrodCityRocket1Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket1Script

GoldenrodCity_Johto_GoldenrodCityRocket2Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket2Script

GoldenrodCity_Johto_GoldenrodCityRocket3Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket3Script

GoldenrodCity_Johto_GoldenrodCityRocket4Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket4Script

GoldenrodCity_Johto_GoldenrodCityRocket5Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket5Script

GoldenrodCity_Johto_GoldenrodCityRocket6Script_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRocket6Script

GoldenrodCity_Johto_MoveTutorScript_Entry::
	lockall
	goto GoldenrodCity_Johto_MoveTutorScript

GoldenrodCity_Johto_GoldenrodCityStationSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityStationSign

GoldenrodCity_Johto_GoldenrodCityRadioTowerSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityRadioTowerSign

GoldenrodCity_Johto_GoldenrodDeptStoreSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodDeptStoreSign

GoldenrodCity_Johto_GoldenrodGymSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodGymSign

GoldenrodCity_Johto_GoldenrodCitySign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCitySign

GoldenrodCity_Johto_GoldenrodCityBikeShopSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityBikeShopSign

GoldenrodCity_Johto_GoldenrodCityGameCornerSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityGameCornerSign

GoldenrodCity_Johto_GoldenrodCityNameRaterSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityNameRaterSign

GoldenrodCity_Johto_GoldenrodCityUndergroundSignNorth_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityUndergroundSignNorth

GoldenrodCity_Johto_GoldenrodCityUndergroundSignSouth_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityUndergroundSignSouth

GoldenrodCity_Johto_GoldenrodCityPokecenterSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityPokecenterSign

GoldenrodCity_Johto_GoldenrodCityFlowerShopSign_Entry::
	lockall
	goto GoldenrodCity_Johto_GoldenrodCityFlowerShopSign


GoldenrodCity_Johto_MoveTutorScript:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorAskTeachAMoveText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_Johto_MoveTutorScript_Refused
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorAsk4000CoinsOkayText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_Johto_MoveTutorScript_Refused2
	setvar VAR_0x8004, 4000
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_Johto_MoveTutorScript_NotEnoughMoney
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorWhichMoveShouldITeachText
	waitmessage
	dynmultipush Johto_Menu_GoldenrodCity_MoveTutorScript_MoveMenuHeader_Opt1, 1
	dynmultipush Johto_Menu_GoldenrodCity_MoveTutorScript_MoveMenuHeader_Opt2, 2
	dynmultipush Johto_Menu_GoldenrodCity_MoveTutorScript_MoveMenuHeader_Opt3, 3
	dynmultipush Johto_Menu_GoldenrodCity_MoveTutorScript_MoveMenuHeader_Opt4, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_Johto_MoveTutorScript_Flamethrower
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_Johto_MoveTutorScript_Thunderbolt
	goto_if_eq VAR_RESULT, 3, GoldenrodCity_Johto_MoveTutorScript_IceBeam
	goto GoldenrodCity_Johto_MoveTutorScript_Incompatible

GoldenrodCity_Johto_MoveTutorScript_Flamethrower:
	setvar VAR_0x8005, MOVE_FLAMETHROWER
	setvar VAR_RESULT, 1
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorMoveText
	waitmessage
	special ChooseMonForMoveTutor
	special JohtoInvertResult
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_MoveTutorScript_TeachMove
	goto GoldenrodCity_Johto_MoveTutorScript_Incompatible

GoldenrodCity_Johto_MoveTutorScript_Thunderbolt:
	setvar VAR_0x8005, MOVE_THUNDERBOLT
	setvar VAR_RESULT, 2
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorMoveText
	waitmessage
	special ChooseMonForMoveTutor
	special JohtoInvertResult
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_MoveTutorScript_TeachMove
	goto GoldenrodCity_Johto_MoveTutorScript_Incompatible

GoldenrodCity_Johto_MoveTutorScript_IceBeam:
	setvar VAR_0x8005, MOVE_ICE_BEAM
	setvar VAR_RESULT, 3
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorMoveText
	waitmessage
	special ChooseMonForMoveTutor
	special JohtoInvertResult
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_MoveTutorScript_TeachMove
	goto GoldenrodCity_Johto_MoveTutorScript_Incompatible

GoldenrodCity_Johto_MoveTutorScript_Refused:
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorAwwButTheyreAmazingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_MoveTutorScript_Refused2:
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorHmTooBadText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_MoveTutorScript_TeachMove:
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText
	waitmessage
	waitbuttonpress
	removecoins 4000
	waitse
	playse SE_PIN
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorFarewellKidText
	waitmessage
	waitbuttonpress
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_WEST, GoldenrodCity_Johto_MoveTutorScript_WalkAroundPlayer
	applymovement 15, GoldenrodCity_Johto_GoldenrodCityMoveTutorEnterGameCornerMovement
	waitmovement 15
	goto GoldenrodCity_Johto_MoveTutorScript_GoInside

GoldenrodCity_Johto_MoveTutorScript_WalkAroundPlayer:
	applymovement 15, GoldenrodCity_Johto_GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement
	waitmovement 15

GoldenrodCity_Johto_MoveTutorScript_GoInside:
	playse SE_DOOR
	removeobject 15
	clearflag FLAG_JOHTO_GOLDENROD_GAME_CORNER_MOVE_TUTOR
	setflag FLAG_JOHTO_ENGINE_DAILY_MOVE_TUTOR
	waitse
	releaseall
	end

GoldenrodCity_Johto_MoveTutorScript_Incompatible:
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorBButText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_MoveTutorScript_NotEnoughMoney:
	message GoldenrodCity_Johto_GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityPokefanMScript:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityYoungster1Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Script_ClearedRadioTower
	message GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Script_ClearedRadioTower:
	message GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Text_ClearedRadioTower
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_RADIO_CARD, GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Script_GotRadioCard
	message GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Script_GotRadioCard:
	message GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Text_GotRadioCard
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityYoungster2Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityLassScript:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityGrampsScript:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocketScoutScript:
	message GoldenrodCity_Johto_GoldenrodCityRocketScoutText1
	waitmessage
	waitbuttonpress
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocketScoutText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 8, Johto_Movement_Face_Up
	waitmovement 8
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket1Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket2Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket3Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket4Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket4Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket5Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket5Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRocket6Script:
	faceplayer
	message GoldenrodCity_Johto_GoldenrodCityRocket6Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityStationSign:
	message GoldenrodCity_Johto_GoldenrodCityStationSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityRadioTowerSign:
	lockall
	message GoldenrodCity_Johto_Text_RadioTowerLobbyIntro
	waitmessage
GoldenrodCity_Johto_RadioTowerMenu:
	dynmultipush GoldenrodCity_Johto_Text_MenuBuenasShow, 0
	dynmultipush GoldenrodCity_Johto_Text_MenuBlueCardPrizes, 1
	dynmultipush GoldenrodCity_Johto_Text_MenuDirectory, 2
	dynmultipush GoldenrodCity_Johto_Text_MenuExit, 3
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, GoldenrodCity_Johto_RadioTower_BuenasShow
	case 1, GoldenrodCity_Johto_RadioTower_BlueCardPrizes
	case 2, GoldenrodCity_Johto_RadioTower_Directory
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_BuenasShow:
	checkitem ITEM_BLUE_CARD, 1
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_RadioTower_GiveBlueCard
	goto_if_set FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY, GoldenrodCity_Johto_RadioTower_AlreadyGotPointToday
	special JohtoCheckBuenaTime
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_RadioTower_BuenaOffAir
	message GoldenrodCity_Johto_Text_BuenaGreeting
	waitmessage
	special JohtoGetBuenaPasswordChoices
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultistack 0, 0, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq GoldenrodCity_Johto_RadioTower_BuenaCancel
	special JohtoCheckBuenaAnswer
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_RadioTower_BuenaWrongAnswer
	playse SE_EXP
	special JohtoGetBlueCardBalance
	buffernumberstring STR_VAR_1, VAR_RESULT
	message GoldenrodCity_Johto_Text_BuenaCorrect
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_GiveBlueCard:
	message GoldenrodCity_Johto_Text_BuenaIntroduceBlueCard
	waitmessage
	giveitem ITEM_BLUE_CARD
	setvar VAR_JOHTO_BLUE_CARD_BALANCE, 0
	message GoldenrodCity_Johto_Text_BuenaExplainRules
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_AlreadyGotPointToday:
	message GoldenrodCity_Johto_Text_BuenaAlreadyGotPoint
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_BuenaOffAir:
	message GoldenrodCity_Johto_Text_BuenaOffAir
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_BuenaWrongAnswer:
	playse SE_BOO
	message GoldenrodCity_Johto_Text_BuenaWrong
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_BuenaCancel:
	message GoldenrodCity_Johto_Text_BuenaComeBack
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_BlueCardPrizes:
	checkitem ITEM_BLUE_CARD, 1
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_Johto_RadioTower_NeedBlueCard
GoldenrodCity_Johto_RadioTower_PrizeLoop:
	special JohtoGetBlueCardBalance
	buffernumberstring STR_VAR_1, VAR_RESULT
	message GoldenrodCity_Johto_Text_PrizeExchangeIntro
	waitmessage
	dynmultipush GoldenrodCity_Johto_Text_PrizeUltraBall, 0
	dynmultipush GoldenrodCity_Johto_Text_PrizeFullRestore, 1
	dynmultipush GoldenrodCity_Johto_Text_PrizeNugget, 2
	dynmultipush GoldenrodCity_Johto_Text_PrizeRareCandy, 3
	dynmultipush GoldenrodCity_Johto_Text_PrizeProtein, 4
	dynmultipush GoldenrodCity_Johto_Text_PrizeIron, 5
	dynmultipush GoldenrodCity_Johto_Text_PrizeCarbos, 6
	dynmultipush GoldenrodCity_Johto_Text_PrizeCalcium, 7
	dynmultipush GoldenrodCity_Johto_Text_PrizeHPUp, 8
	dynmultipush GoldenrodCity_Johto_Text_PrizeCancel, 9
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	compare VAR_RESULT, 9
	goto_if_ge GoldenrodCity_Johto_RadioTower_Exit
	copyvar VAR_0x8004, VAR_RESULT
	special JohtoRedeemBuenaPrize
	compare VAR_RESULT, 0
	goto_if_eq GoldenrodCity_Johto_RadioTower_PrizeSuccess
	compare VAR_RESULT, 1
	goto_if_eq GoldenrodCity_Johto_RadioTower_PrizeNotEnoughPoints
	message GoldenrodCity_Johto_Text_PrizeBagFull
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_PrizeSuccess:
	playse SE_SHOP
	copyvar VAR_0x8004, VAR_0x8005
	bufferitemname STR_VAR_2, VAR_0x8004
	message GoldenrodCity_Johto_Text_PrizeClaimed
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_PrizeLoop

GoldenrodCity_Johto_RadioTower_PrizeNotEnoughPoints:
	message GoldenrodCity_Johto_Text_PrizeNotEnough
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_PrizeLoop

GoldenrodCity_Johto_RadioTower_NeedBlueCard:
	message GoldenrodCity_Johto_Text_PrizeNeedCard
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTower_Exit

GoldenrodCity_Johto_RadioTower_Directory:
	message GoldenrodCity_Johto_GoldenrodCityRadioTowerSignText
	waitmessage
	waitbuttonpress
	goto GoldenrodCity_Johto_RadioTowerMenu

GoldenrodCity_Johto_RadioTower_Exit:
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodDeptStoreSign:
	message GoldenrodCity_Johto_GoldenrodDeptStoreSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodGymSign:
	message GoldenrodCity_Johto_GoldenrodGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCitySign:
	message GoldenrodCity_Johto_GoldenrodCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityBikeShopSign:
	message GoldenrodCity_Johto_GoldenrodCityBikeShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityGameCornerSign:
	message GoldenrodCity_Johto_GoldenrodCityGameCornerSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityNameRaterSign:
	message GoldenrodCity_Johto_GoldenrodCityNameRaterSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityUndergroundSignNorth:
	message GoldenrodCity_Johto_GoldenrodCityUndergroundSignNorthText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityUndergroundSignSouth:
	message GoldenrodCity_Johto_GoldenrodCityUndergroundSignSouthText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityPokecenterSign:
	goto Johto_Std_PokecenterSignScript

GoldenrodCity_Johto_GoldenrodCityFlowerShopSign:
	message GoldenrodCity_Johto_GoldenrodCityFlowerShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodCity_Johto_GoldenrodCityFlypointAndFloriaCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_GOLDENROD
	setflag FLAG_JOHTO_ENGINE_REACHED_GOLDENROD
	goto_if_set FLAG_JOHTO_MET_FLORIA, GoldenrodCity_Johto_GoldenrodCityFlypointAndFloriaCallback_FloriaDone_Cb
	clearflag FLAG_JOHTO_FLORIA_AT_SUDOWOODO

GoldenrodCity_Johto_GoldenrodCityFlypointAndFloriaCallback_FloriaDone_Cb:
	return

GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_Cb:
	goto_if_unset FLAG_JOHTO_BEAT_ELITE_FOUR, GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorDone_Cb
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorDisappear_Cb
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 3, GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorAppear_Cb
	goto_if_eq VAR_RESULT, 6, GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorAppear_Cb

GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorDisappear_Cb:
	setflag FLAG_JOHTO_GOLDENROD_CITY_MOVE_TUTOR
	return

GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorAppear_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_MOVE_TUTOR, GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorDone_Cb
	clearflag FLAG_JOHTO_GOLDENROD_CITY_MOVE_TUTOR

GoldenrodCity_Johto_GoldenrodCityMoveTutorCallback_MoveTutorDone_Cb:
	return

GoldenrodCity_Johto_GoldenrodCityMoveTutorEnterGameCornerMovement:
	walk_right
	walk_right
	walk_up
	step_end

GoldenrodCity_Johto_GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement:
	walk_down
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

GoldenrodCity_Johto_GoldenrodCityPokefanMText:
	.string "They built the new\n"
	.string "RADIO TOWER to"
	.string "\preplace the old,\n"
	.string "creaky one.$"

GoldenrodCity_Johto_GoldenrodCityYoungster1Text:
	.string "I know there's a\n"
	.string "new BIKE SHOP, but"
	.string "\pI can't find it\n"
	.string "anywhere.$"

GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Text:
	.string "Is that man in\n"
	.string "black dressed up"
	.string "\plike a TEAM ROCKET\n"
	.string "member? How silly!$"

GoldenrodCity_Johto_GoldenrodCityCooltrainerF1Text_ClearedRadioTower:
	.string "Was that man in\n"
	.string "black really part"
	.string "\pof TEAM ROCKET? I\n"
	.string "can't believe it!$"

GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Text:
	.string "The RADIO TOWER in\n"
	.string "GOLDENROD CITY is\l"
	.string "a landmark."
	.string "\pThey're running a\n"
	.string "promotional cam- \l"
	.string "paign right now."
	.string "\pThey'll modify\n"
	.string "your POKéGEAR,"
	.string "\pso it can also\n"
	.string "serve as a radio.$"

GoldenrodCity_Johto_GoldenrodCityCooltrainerF2Text_GotRadioCard:
	.string "Oh, your POKéGEAR\n"
	.string "works as a radio!$"

GoldenrodCity_Johto_GoldenrodCityYoungster2Text:
	.string "E-he-he-he…"
	.string "\pI got in trouble\n"
	.string "for playing in the"
	.string "\pbasement of the\n"
	.string "DEPT.STORE.$"

GoldenrodCity_Johto_GoldenrodCityLassText:
	.string "The man at that\n"
	.string "house rates your\l"
	.string "POKéMON names."
	.string "\pHe can even rename\n"
	.string "your POKéMON.$"

GoldenrodCity_Johto_GoldenrodCityGrampsText:
	.string "Whew! This is one\n"
	.string "big town. I don't"
	.string "\pknow where any-\n"
	.string "thing is.$"

GoldenrodCity_Johto_GoldenrodCityRocketScoutText1:
	.string "So this is the\n"
	.string "RADIO TOWER…$"

GoldenrodCity_Johto_GoldenrodCityRocketScoutText2:
	.string "What do you want,\n"
	.string "you pest? Scram!$"

GoldenrodCity_Johto_GoldenrodCityRocket1Text:
	.string "Stay out of the\n"
	.string "way! Beat it!$"

GoldenrodCity_Johto_GoldenrodCityRocket2Text:
	.string "Take over the\n"
	.string "RADIO TOWER…"
	.string "\pWhat? It's none of\n"
	.string "your business!$"

GoldenrodCity_Johto_GoldenrodCityRocket3Text:
	.string "POKéMON? They're\n"
	.string "nothing more than"
	.string "\ptools for making\n"
	.string "money!$"

GoldenrodCity_Johto_GoldenrodCityRocket4Text:
	.string "Our dream will\n"
	.string "soon come true…"
	.string "\pIt was such a long\n"
	.string "struggle…$"

GoldenrodCity_Johto_GoldenrodCityRocket5Text:
	.string "Hey, brat! You\n"
	.string "don't belong here!\l"
	.string "Get lost!$"

GoldenrodCity_Johto_GoldenrodCityRocket6Text:
	.string "Come taste the\n"
	.string "true terror of\l"
	.string "TEAM ROCKET!$"

GoldenrodCity_Johto_GoldenrodCityStationSignText:
	.string "GOLDENROD CITY\n"
	.string "STATION$"

GoldenrodCity_Johto_GoldenrodCityRadioTowerSignText:
	.string "GOLDENROD CITY RADIO TOWER\n"
	.string "1F: Reception & Studio Desk\l"
	.string "2F: Sales & Buena's Studio\l"
	.string "3F: Personnel & Sound Lab\l"
	.string "4F: Production Office\l"
	.string "5F: Director's Office$"

GoldenrodCity_Johto_Text_RadioTowerLobbyIntro:
	.string "GOLDENROD RADIO TOWER\n"
	.string "Broadcast Central & Studio Desk.\l"
	.string "How may we help you?$"

GoldenrodCity_Johto_Text_MenuBuenasShow:
	.string "BUENA'S SHOW$"

GoldenrodCity_Johto_Text_MenuBlueCardPrizes:
	.string "BLUE CARD PRIZES$"

GoldenrodCity_Johto_Text_MenuDirectory:
	.string "STATION DIRECTORY$"

GoldenrodCity_Johto_Text_MenuExit:
	.string "EXIT$"

GoldenrodCity_Johto_Text_BuenaGreeting:
	.string "BUENA: Hi! Did you tune in to\n"
	.string "BUENA'S PASSWORD on the radio tonight?\p"
	.string "Tell me, what was tonight's password?$"

GoldenrodCity_Johto_Text_BuenaCorrect:
	.string "BUENA: Bingo! That's correct!\n"
	.string "Here is 1 point on your BLUE CARD!\p"
	.string "Your BLUE CARD now has {STR_VAR_1} points!\n"
	.string "Keep listening tomorrow night!$"

GoldenrodCity_Johto_Text_BuenaWrong:
	.string "BUENA: Aw, that's incorrect!\p"
	.string "Tune in to BUENA'S PASSWORD on your\n"
	.string "Pokégear radio between 6 PM and midnight\l"
	.string "to find out the real password!$"

GoldenrodCity_Johto_Text_BuenaComeBack:
	.string "BUENA: Tune in to my password show on\n"
	.string "the radio and come back anytime!$"

GoldenrodCity_Johto_Text_BuenaIntroduceBlueCard:
	.string "BUENA: Hi, I'm BUENA! The host of\n"
	.string "BUENA'S PASSWORD on the radio!\p"
	.string "Oh? You don't have a BLUE CARD?\n"
	.string "Here, take this one!$"

GoldenrodCity_Johto_Text_BuenaExplainRules:
	.string "BUENA: Tune in to BUENA'S PASSWORD on\n"
	.string "the radio every evening from 6:00 PM\l"
	.string "to midnight.\p"
	.string "Come back here, tell me the password,\n"
	.string "and earn 1 point every day!\p"
	.string "Save up your points and redeem them for\n"
	.string "terrific prizes at our Prize Counter!$"

GoldenrodCity_Johto_Text_BuenaAlreadyGotPoint:
	.string "BUENA: You already earned your\n"
	.string "point for today!\p"
	.string "Tune in again tomorrow evening from\n"
	.string "6:00 PM for a brand-new password!$"

GoldenrodCity_Johto_Text_BuenaOffAir:
	.string "BUENA: Hi! My password show is only\n"
	.string "on the air in the evening from\l"
	.string "6:00 PM to midnight!\p"
	.string "Please tune in then!$"

GoldenrodCity_Johto_Text_PrizeExchangeIntro:
	.string "Welcome to the BLUE CARD Point Exchange!\n"
	.string "Your BLUE CARD currently has {STR_VAR_1} points.\p"
	.string "Which prize would you like?$"

GoldenrodCity_Johto_Text_PrizeUltraBall:
	.string "ULTRA BALL    2 pts$"

GoldenrodCity_Johto_Text_PrizeFullRestore:
	.string "FULL RESTORE  2 pts$"

GoldenrodCity_Johto_Text_PrizeNugget:
	.string "NUGGET        3 pts$"

GoldenrodCity_Johto_Text_PrizeRareCandy:
	.string "RARE CANDY    3 pts$"

GoldenrodCity_Johto_Text_PrizeProtein:
	.string "PROTEIN       5 pts$"

GoldenrodCity_Johto_Text_PrizeIron:
	.string "IRON          5 pts$"

GoldenrodCity_Johto_Text_PrizeCarbos:
	.string "CARBOS        5 pts$"

GoldenrodCity_Johto_Text_PrizeCalcium:
	.string "CALCIUM       5 pts$"

GoldenrodCity_Johto_Text_PrizeHPUp:
	.string "HP UP         5 pts$"

GoldenrodCity_Johto_Text_PrizeCancel:
	.string "CANCEL$"

GoldenrodCity_Johto_Text_PrizeClaimed:
	.string "Here is your prize: {STR_VAR_2}!\n"
	.string "Thank you for listening!$"

GoldenrodCity_Johto_Text_PrizeNotEnough:
	.string "You don't have enough points on your\n"
	.string "BLUE CARD for that item!$"

GoldenrodCity_Johto_Text_PrizeBagFull:
	.string "Your Bag is full!\n"
	.string "Please make room before redeeming prizes.$"

GoldenrodCity_Johto_Text_PrizeNeedCard:
	.string "You need a BLUE CARD to exchange points!\n"
	.string "Talk to BUENA at the show desk first.$"

GoldenrodCity_Johto_GoldenrodDeptStoreSignText:
	.string "Full Selection of\n"
	.string "POKéMON Goods!"
	.string "\pGOLDENROD CITY\n"
	.string "DEPT.STORE$"

GoldenrodCity_Johto_GoldenrodGymSignText:
	.string "GOLDENROD CITY\n"
	.string "POKéMON GYM\l"
	.string "LEADER: WHITNEY"
	.string "\pThe Incredibly\n"
	.string "Pretty Girl!$"

GoldenrodCity_Johto_GoldenrodCitySignText:
	.string "GOLDENROD CITY"
	.string "\pThe Festive City\n"
	.string "of Opulent Charm$"

GoldenrodCity_Johto_GoldenrodCityBikeShopSignText:
	.string "The World is a\n"
	.string "Cycle Path!\l"
	.string "BIKE SHOP$"

GoldenrodCity_Johto_GoldenrodCityGameCornerSignText:
	.string "Your Playground!"
	.string "\pGOLDENROD CITY\n"
	.string "GAME CORNER$"

GoldenrodCity_Johto_GoldenrodCityNameRaterSignText:
	.string "NAME RATER"
	.string "\pGet Your POKéMON\n"
	.string "Nicknames Rated$"

GoldenrodCity_Johto_GoldenrodCityUndergroundSignNorthText:
	.string "UNDERGROUND\n"
	.string "ENTRANCE$"

GoldenrodCity_Johto_GoldenrodCityUndergroundSignSouthText:
	.string "UNDERGROUND\n"
	.string "ENTRANCE$"

GoldenrodCity_Johto_GoldenrodCityFlowerShopSignText:
	.string "Blooming Beautiful\n"
	.string "FLOWER SHOP$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorAskTeachAMoveText:
	.string "I can teach your\n"
	.string "POKéMON amazing"
	.string "\pmoves if you'd\n"
	.string "like."
	.string "\pShould I teach a\n"
	.string "new move?$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorAsk4000CoinsOkayText:
	.string "It will cost you\n"
	.string "4000 coins. Okay?$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorAwwButTheyreAmazingText:
	.string "Aww… But they're\n"
	.string "amazing…$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorWhichMoveShouldITeachText:
	.string "Wahahah! You won't\n"
	.string "regret it!"
	.string "\pWhich move should\n"
	.string "I teach?$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorHmTooBadText:
	.string "Hm, too bad. I'll\n"
	.string "have to get some\l"
	.string "cash from home…$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText:
	.string "If you understand\n"
	.string "what's so amazing"
	.string "\pabout this move,\n"
	.string "you've made it as\l"
	.string "a trainer.$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorFarewellKidText:
	.string "Wahahah!\n"
	.string "Farewell, kid!$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorBButText:
	.string "B-but…$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText:
	.string "…You don't have\n"
	.string "enough coins here…$"

GoldenrodCity_Johto_GoldenrodCityMoveTutorMoveText:
	.string "$"
