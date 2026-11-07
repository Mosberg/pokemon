GoldenrodGameCorner_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodGameCorner_Johto_OnTransition
	.byte 0

GoldenrodGameCorner_Johto_OnTransition:
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_Cb
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerCoinVendorScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerCoinVendorScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendorScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendorScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPharmacistScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPharmacistScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM1Script_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM1Script

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerMScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerMScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanFScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanFScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerFScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerFScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerGentlemanScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerGentlemanScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM2Script_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM2Script

GoldenrodGameCorner_Johto_MoveTutorInsideScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_MoveTutorInsideScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerSlotsMachineScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerSlotsMachineScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerLuckySlotsMachineScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerLuckySlotsMachineScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerCardFlipMachineScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerCardFlipMachineScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerLeftTheirDrinkScript_Entry::
	lockall
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerLeftTheirDrinkScript


GoldenrodGameCorner_Johto_MoveTutorInsideScript:
	faceplayer
	message GoldenrodGameCorner_Johto_MoveTutorInsideText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 11, Johto_Movement_Face_Right
	waitmovement 11
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerCoinVendorScript:
	goto Johto_Std_GameCornerCoinVendorScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendorScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorWhichPrizeText
	waitmessage

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript:
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerTMVendorMenuHeader_Opt1, 1
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerTMVendorMenuHeader_Opt2, 2
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerTMVendorMenuHeader_Opt3, 3
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerTMVendorMenuHeader_Opt4, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_Thunder
	goto_if_eq VAR_RESULT, 2, GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_Blizzard
	goto_if_eq VAR_RESULT, 3, GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_FireBlast
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_Thunder:
	setvar VAR_0x8004, 5500
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_TM_THUNDER
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM_THUNDER
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 5500
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_FinishScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_Blizzard:
	setvar VAR_0x8004, 5500
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_TM_BLIZZARD
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM_BLIZZARD
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 5500
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_FinishScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript_FireBlast:
	setvar VAR_0x8004, 5500
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_TM_FIRE_BLAST
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM_FIRE_BLAST
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 5500
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_FinishScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_FinishScript:
	waitse
	playse SE_PIN
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerTMVendor_LoopScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNeedMoreCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNoMoreRoomText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorQuitText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNoCoinCaseText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_loop:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorWhichPrizeText
	waitmessage
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerPrizeMonVendorScript_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerPrizeMonVendorScript_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerPrizeMonVendorScript_MenuHeader_Opt3, 3
	dynmultipush Johto_Menu_GoldenrodGameCorner_GoldenrodGameCornerPrizeMonVendorScript_MenuHeader_Opt4, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Abra
	goto_if_eq VAR_RESULT, 2, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Cubone
	goto_if_eq VAR_RESULT, 3, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Wobbuffet
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Abra:
	setvar VAR_0x8004, 100
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	getpartysize
	goto_if_eq VAR_RESULT, 6, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	bufferspeciesname STR_VAR_1, SPECIES_ABRA
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_PIN
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, SPECIES_ABRA
	givemon SPECIES_ABRA, 5
	removecoins 100
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_loop

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Cubone:
	setvar VAR_0x8004, 800
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	getpartysize
	goto_if_eq VAR_RESULT, 6, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	bufferspeciesname STR_VAR_1, SPECIES_CUBONE
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_PIN
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, SPECIES_CUBONE
	givemon SPECIES_CUBONE, 15
	removecoins 800
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_loop

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_Wobbuffet:
	setvar VAR_0x8004, 1500
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	getpartysize
	goto_if_eq VAR_RESULT, 6, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	bufferspeciesname STR_VAR_1, SPECIES_WOBBUFFET
	call GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_PIN
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, SPECIES_WOBBUFFET
	givemon SPECIES_WOBBUFFET, 15
	removecoins 1500
	goto GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeMonVendorScript_loop

GoldenrodGameCorner_Johto_GoldenrodGameCornerPharmacistScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPharmacistText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement VAR_LAST_TALKED, Johto_Movement_Face_Left
	waitmovement VAR_LAST_TALKED
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM1Script:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM1Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerMScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, Johto_Movement_Face_Left
	waitmovement 6
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanFScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, Johto_Movement_Face_Right
	waitmovement 7
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerFScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerGentlemanScript:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 9, Johto_Movement_Face_Right
	waitmovement 9
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM2Script:
	faceplayer
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerLeftTheirDrinkScript:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerLeftTheirDrinkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerSlotsMachineScript:
	random 6
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerLuckySlotsMachineScript
	setvar VAR_RESULT, FALSE
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerLuckySlotsMachineScript:
	setvar VAR_RESULT, TRUE
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerCardFlipMachineScript:
	lockall
	special Special_CardFlipInit
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_CardFlip_NoCoinCase
	goto_if_eq VAR_RESULT, 1, GoldenrodGameCorner_Johto_CardFlip_NotEnoughCoins

	special Special_CardFlipShowCoins
	message GoldenrodGameCorner_Johto_Text_CardFlipPlayWithThreeCoins
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, NO, GoldenrodGameCorner_Johto_CardFlip_Quit

GoldenrodGameCorner_Johto_CardFlip_RoundLoop:
	special Special_CardFlipDeal
	goto_if_eq VAR_RESULT, 2, GoldenrodGameCorner_Johto_CardFlip_NotEnoughCoinsMidGame
	goto_if_ne VAR_RESULT, 1, GoldenrodGameCorner_Johto_CardFlip_SkipShuffledMessage

	playse SE_RG_CARD_FLIP
	message GoldenrodGameCorner_Johto_Text_CardFlipShuffled
	waitmessage
	waitbuttonpress

GoldenrodGameCorner_Johto_CardFlip_SkipShuffledMessage:
	playse SE_RG_CARD_FLIPPING
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseACard
	waitmessage

	dynmultipush GoldenrodGameCorner_Johto_Text_Card1, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_Card2, 2
	dynmultistack 20, 8, FALSE, 2, FALSE, 0, NULL
	copyvar VAR_0x8004, VAR_RESULT
	special Special_CardFlipSelectCard

	message GoldenrodGameCorner_Johto_Text_CardFlipPlaceYourBet
	waitmessage

	dynmultipush GoldenrodGameCorner_Johto_Text_BetSingleCard, 0
	dynmultipush GoldenrodGameCorner_Johto_Text_BetRank, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_BetSuit, 2
	dynmultipush GoldenrodGameCorner_Johto_Text_BetRankPair, 3
	dynmultipush GoldenrodGameCorner_Johto_Text_BetSuitPair, 4
	dynmultistack 14, 4, FALSE, 5, FALSE, 0, NULL

	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_0x8004, 0, GoldenrodGameCorner_Johto_CardFlip_ChooseSingleCard
	goto_if_eq VAR_0x8004, 1, GoldenrodGameCorner_Johto_CardFlip_ChooseRank
	goto_if_eq VAR_0x8004, 2, GoldenrodGameCorner_Johto_CardFlip_ChooseSuit
	goto_if_eq VAR_0x8004, 3, GoldenrodGameCorner_Johto_CardFlip_ChooseRankPair
	goto_if_eq VAR_0x8004, 4, GoldenrodGameCorner_Johto_CardFlip_ChooseSuitPair
	goto GoldenrodGameCorner_Johto_CardFlip_Quit

GoldenrodGameCorner_Johto_CardFlip_ChooseSingleCard:
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseSuit
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPikachu, 0
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitJigglypuff, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPoliwag, 2
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitOddish, 3
	dynmultistack 16, 4, FALSE, 4, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT

	message GoldenrodGameCorner_Johto_Text_CardFlipChooseRank
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank1, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank2, 2
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank3, 3
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank4, 4
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank5, 5
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank6, 6
	dynmultistack 20, 2, FALSE, 6, FALSE, 0, NULL
	copyvar VAR_0x8006, VAR_RESULT

	setvar VAR_0x8004, 0
	special Special_CardFlipSetBet
	goto GoldenrodGameCorner_Johto_CardFlip_RevealCard

GoldenrodGameCorner_Johto_CardFlip_ChooseRank:
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseRank
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank1, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank2, 2
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank3, 3
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank4, 4
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank5, 5
	dynmultipush GoldenrodGameCorner_Johto_Text_Rank6, 6
	dynmultistack 20, 2, FALSE, 6, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_0x8006, 0

	setvar VAR_0x8004, 1
	special Special_CardFlipSetBet
	goto GoldenrodGameCorner_Johto_CardFlip_RevealCard

GoldenrodGameCorner_Johto_CardFlip_ChooseSuit:
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseSuit
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPikachu, 0
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitJigglypuff, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPoliwag, 2
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitOddish, 3
	dynmultistack 16, 4, FALSE, 4, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_0x8006, 0

	setvar VAR_0x8004, 2
	special Special_CardFlipSetBet
	goto GoldenrodGameCorner_Johto_CardFlip_RevealCard

GoldenrodGameCorner_Johto_CardFlip_ChooseRankPair:
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseRankPair
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_RankPair12, 0
	dynmultipush GoldenrodGameCorner_Johto_Text_RankPair34, 1
	dynmultipush GoldenrodGameCorner_Johto_Text_RankPair56, 2
	dynmultistack 18, 6, FALSE, 3, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_0x8006, 0

	setvar VAR_0x8004, 3
	special Special_CardFlipSetBet
	goto GoldenrodGameCorner_Johto_CardFlip_RevealCard

GoldenrodGameCorner_Johto_CardFlip_ChooseSuitPair:
	message GoldenrodGameCorner_Johto_Text_CardFlipChooseSuitPair
	waitmessage
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPairPikaJiggly, 0
	dynmultipush GoldenrodGameCorner_Johto_Text_SuitPairPoliOdd, 1
	dynmultistack 12, 6, FALSE, 2, FALSE, 0, NULL
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_0x8006, 0

	setvar VAR_0x8004, 4
	special Special_CardFlipSetBet
	goto GoldenrodGameCorner_Johto_CardFlip_RevealCard

GoldenrodGameCorner_Johto_CardFlip_RevealCard:
	playse SE_RG_CARD_OPEN
	special Special_CardFlipBufferResult
	message GoldenrodGameCorner_Johto_Text_CardFlipRevealedCard
	waitmessage
	waitbuttonpress

	special Special_CardFlipEvaluate
	goto_if_eq VAR_RESULT, TRUE, GoldenrodGameCorner_Johto_CardFlip_Won

GoldenrodGameCorner_Johto_CardFlip_Lost:
	playse SE_BOO
	message GoldenrodGameCorner_Johto_Text_CardFlipDarn
	waitmessage
	waitbuttonpress
	goto GoldenrodGameCorner_Johto_CardFlip_AskPlayAgain

GoldenrodGameCorner_Johto_CardFlip_Won:
	playse SE_SHOP
	buffernumberstring STR_VAR_1, VAR_0x8005
	message GoldenrodGameCorner_Johto_Text_CardFlipYeah
	waitmessage
	waitbuttonpress

GoldenrodGameCorner_Johto_CardFlip_AskPlayAgain:
	special Special_CardFlipShowCoins
	message GoldenrodGameCorner_Johto_Text_CardFlipPlayAgain
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, GoldenrodGameCorner_Johto_CardFlip_RoundLoop

GoldenrodGameCorner_Johto_CardFlip_Quit:
	special Special_CardFlipHideCoins
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_CardFlip_NoCoinCase:
	message GoldenrodGameCorner_Johto_Text_CardFlipNoCoinCase
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_CardFlip_NotEnoughCoins:
	message GoldenrodGameCorner_Johto_Text_CardFlipNotEnoughCoins
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_CardFlip_NotEnoughCoinsMidGame:
	special Special_CardFlipHideCoins
	message GoldenrodGameCorner_Johto_Text_CardFlipNotEnoughCoins
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript_Sub:
	message GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorConfirmPrizeText
	waitmessage
	yesnobox 20, 8
	return

GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_Cb:
	goto_if_unset FLAG_JOHTO_BEAT_ELITE_FOUR, GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_finish_Cb
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_move_tutor_inside_Cb
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 3, GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside_Cb
	goto_if_eq VAR_RESULT, 6, GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside_Cb

GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_move_tutor_inside_Cb:
	clearflag FLAG_JOHTO_GOLDENROD_GAME_CORNER_MOVE_TUTOR
	return

GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_DAILY_MOVE_TUTOR, GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_finish_Cb
	setflag FLAG_JOHTO_GOLDENROD_GAME_CORNER_MOVE_TUTOR

GoldenrodGameCorner_Johto_GoldenrodGameCornerMoveTutorCallback_finish_Cb:
	return

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorIntroText:
	.string "Welcome!"
	.string "\pWe exchange your\n"
	.string "game coins for\l"
	.string "fabulous prizes!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorWhichPrizeText:
	.string "Which prize would\n"
	.string "you like?$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorConfirmPrizeText:
	.string "{STR_VAR_1}.\n"
	.string "Is that right?$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorHereYouGoText:
	.string "Here you go!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNeedMoreCoinsText:
	.string "Sorry! You need\n"
	.string "more coins.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNoMoreRoomText:
	.string "Sorry. You can't\n"
	.string "carry any more.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorQuitText:
	.string "OK. Please save\n"
	.string "your coins and\l"
	.string "come again!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPrizeVendorNoCoinCaseText:
	.string "Oh? You don't have\n"
	.string "a COIN CASE.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPharmacistText:
	.string "I always play this\n"
	.string "slot machine. It"
	.string "\ppays out more than\n"
	.string "others, I think.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM1Text:
	.string "I just love this\n"
	.string "new slot machine."
	.string "\pIt's more of a\n"
	.string "challenge than the\l"
	.string "ones in CELADON.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerMText:
	.string "Life is a gamble.\n"
	.string "I'm going to flip\l"
	.string "cards till I drop!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanFText:
	.string "Card flip…"
	.string "\pI prefer it over\n"
	.string "the slots because"
	.string "\pit's easier to\n"
	.string "figure the odds."
	.string "\pBut the payout is\n"
	.string "much lower.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerCooltrainerFText:
	.string "I won't quit until\n"
	.string "I win!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerGentlemanText:
	.string "I taught BLIZZARD\n"
	.string "to my POKéMON."
	.string "\pIt was hard to get\n"
	.string "enough coins for"
	.string "\pit, but it was\n"
	.string "worth it.$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerPokefanM2Text:
	.string "I couldn't win at\n"
	.string "the slots, and I"
	.string "\pblew it on card\n"
	.string "flipping…"
	.string "\pI got so furious,\n"
	.string "I tossed out my"
	.string "\pCOIN CASE in the\n"
	.string "UNDERGROUND.$"

GoldenrodGameCorner_Johto_MoveTutorInsideText:
	.string "Wahahah! The coins\n"
	.string "keep rolling in!$"

GoldenrodGameCorner_Johto_GoldenrodGameCornerLeftTheirDrinkText:
	.string "Someone left their\n"
	.string "drink."
	.string "\pIt smells sweet.$"

GoldenrodGameCorner_Johto_Text_CardFlipNoCoinCase:
	.string "You don't have a COIN CASE.$"

GoldenrodGameCorner_Johto_Text_CardFlipNotEnoughCoins:
	.string "Not enough coins…$"

GoldenrodGameCorner_Johto_Text_CardFlipPlayWithThreeCoins:
	.string "Play with three coins?$"

GoldenrodGameCorner_Johto_Text_CardFlipShuffled:
	.string "The cards have been shuffled.$"

GoldenrodGameCorner_Johto_Text_CardFlipChooseACard:
	.string "Choose a card.$"

GoldenrodGameCorner_Johto_Text_Card1:
	.string "CARD 1$"

GoldenrodGameCorner_Johto_Text_Card2:
	.string "CARD 2$"

GoldenrodGameCorner_Johto_Text_CardFlipPlaceYourBet:
	.string "Place your bet.$"

GoldenrodGameCorner_Johto_Text_BetSingleCard:
	.string "SINGLE CARD (24x)$"

GoldenrodGameCorner_Johto_Text_BetRank:
	.string "SINGLE RANK (6x)$"

GoldenrodGameCorner_Johto_Text_BetSuit:
	.string "SINGLE SUIT (4x)$"

GoldenrodGameCorner_Johto_Text_BetRankPair:
	.string "RANK PAIR (3x)$"

GoldenrodGameCorner_Johto_Text_BetSuitPair:
	.string "SUIT PAIR (2x)$"

GoldenrodGameCorner_Johto_Text_CardFlipChooseSuit:
	.string "Choose a Pokémon suit.$"

GoldenrodGameCorner_Johto_Text_SuitPikachu:
	.string "PIKACHU$"

GoldenrodGameCorner_Johto_Text_SuitJigglypuff:
	.string "JIGGLYPUFF$"

GoldenrodGameCorner_Johto_Text_SuitPoliwag:
	.string "POLIWAG$"

GoldenrodGameCorner_Johto_Text_SuitOddish:
	.string "ODDISH$"

GoldenrodGameCorner_Johto_Text_CardFlipChooseRank:
	.string "Choose a number rank.$"

GoldenrodGameCorner_Johto_Text_Rank1:
	.string "RANK 1$"

GoldenrodGameCorner_Johto_Text_Rank2:
	.string "RANK 2$"

GoldenrodGameCorner_Johto_Text_Rank3:
	.string "RANK 3$"

GoldenrodGameCorner_Johto_Text_Rank4:
	.string "RANK 4$"

GoldenrodGameCorner_Johto_Text_Rank5:
	.string "RANK 5$"

GoldenrodGameCorner_Johto_Text_Rank6:
	.string "RANK 6$"

GoldenrodGameCorner_Johto_Text_CardFlipChooseRankPair:
	.string "Choose a number pair.$"

GoldenrodGameCorner_Johto_Text_RankPair12:
	.string "RANKS 1 & 2$"

GoldenrodGameCorner_Johto_Text_RankPair34:
	.string "RANKS 3 & 4$"

GoldenrodGameCorner_Johto_Text_RankPair56:
	.string "RANKS 5 & 6$"

GoldenrodGameCorner_Johto_Text_CardFlipChooseSuitPair:
	.string "Choose a Pokémon pair.$"

GoldenrodGameCorner_Johto_Text_SuitPairPikaJiggly:
	.string "PIKACHU & JIGGLYPUFF$"

GoldenrodGameCorner_Johto_Text_SuitPairPoliOdd:
	.string "POLIWAG & ODDISH$"

GoldenrodGameCorner_Johto_Text_CardFlipRevealedCard:
	.string "The card is {STR_VAR_3}!$"

GoldenrodGameCorner_Johto_Text_CardFlipYeah:
	.string "Yeah!\n"
	.string "You won {STR_VAR_1} coins!$"

GoldenrodGameCorner_Johto_Text_CardFlipDarn:
	.string "Darn…$"

GoldenrodGameCorner_Johto_Text_CardFlipPlayAgain:
	.string "Want to play again?$"

