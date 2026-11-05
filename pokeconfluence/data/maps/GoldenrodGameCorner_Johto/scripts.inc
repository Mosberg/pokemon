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
	@ TODO unsupported: loadmenu GoldenrodGameCornerTMVendorMenuHeader
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: loadmenu .MenuHeader
	goto Johto_EventScript_Unimplemented

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
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

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
