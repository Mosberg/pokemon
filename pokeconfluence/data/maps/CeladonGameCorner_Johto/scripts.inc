CeladonGameCorner_Johto_MapScripts::
	.byte 0

CeladonGameCorner_Johto_CeladonGameCornerClerkScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerClerkScript

CeladonGameCorner_Johto_CeladonGameCornerReceptionistScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerReceptionistScript

CeladonGameCorner_Johto_CeladonGameCornerPokefanMScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerPokefanMScript

CeladonGameCorner_Johto_CeladonGameCornerTeacherScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerTeacherScript

CeladonGameCorner_Johto_CeladonGameCornerFishingGuruScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerFishingGuruScript

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerFisherScript

CeladonGameCorner_Johto_CeladonGymGuideScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGymGuideScript

CeladonGameCorner_Johto_CeladonGameCornerGrampsScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerGrampsScript

CeladonGameCorner_Johto_CeladonGameCornerCardFlipScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerCardFlipScript

CeladonGameCorner_Johto_CeladonGameCornerSodaCanScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerSodaCanScript

CeladonGameCorner_Johto_CeladonGameCornerLuckySlotMachineScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerLuckySlotMachineScript

CeladonGameCorner_Johto_CeladonGameCornerSlotMachineScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerSlotMachineScript

CeladonGameCorner_Johto_CeladonGameCornerLighterScript_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerLighterScript

CeladonGameCorner_Johto_CeladonGameCornerPoster1Script_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerPoster1Script

CeladonGameCorner_Johto_CeladonGameCornerPoster2Script_Entry::
	lockall
	goto CeladonGameCorner_Johto_CeladonGameCornerPoster2Script


CeladonGameCorner_Johto_CeladonGameCornerClerkScript:
	goto Johto_Std_GameCornerCoinVendorScript

CeladonGameCorner_Johto_CeladonGameCornerReceptionistScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGameCornerReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerPokefanMScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGameCornerPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Left
	waitmovement 3
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerTeacherScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGameCornerTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Right
	waitmovement 4
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerFishingGuruScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGameCornerFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_COINS_FROM_GAMBLER_AT_CELADON, CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GotCoins
	message CeladonGameCorner_Johto_CeladonGameCornerFisherText1
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, CeladonGameCorner_Johto_CeladonGameCornerFisherScript_NoCoinCase
	setvar VAR_0x8004, 9998
	special JohtoCheckCoins
	goto_if_eq VAR_RESULT, 1, CeladonGameCorner_Johto_CeladonGameCornerFisherScript_FullCoinCase
	bufferstring STR_VAR_2, CeladonGameCorner_Johto_CeladonGameCornerFisherScript_coinname
	call CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GiveCoins_Sub
	addcoins 18
	setflag FLAG_JOHTO_GOT_COINS_FROM_GAMBLER_AT_CELADON

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GotCoins:
	message CeladonGameCorner_Johto_CeladonGameCornerFisherText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement VAR_LAST_TALKED, Johto_Movement_Face_Left
	waitmovement VAR_LAST_TALKED
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_NoCoinCase:
	message CeladonGameCorner_Johto_CeladonGameCornerFisherNoCoinCaseText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement VAR_LAST_TALKED, Johto_Movement_Face_Left
	waitmovement VAR_LAST_TALKED
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_FullCoinCase:
	message CeladonGameCorner_Johto_CeladonGameCornerFisherFullCoinCaseText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement VAR_LAST_TALKED, Johto_Movement_Face_Left
	waitmovement VAR_LAST_TALKED
	releaseall
	end

CeladonGameCorner_Johto_CeladonGymGuideScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerGrampsScript:
	faceplayer
	message CeladonGameCorner_Johto_CeladonGameCornerGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 8, Johto_Movement_Face_Left
	waitmovement 8
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerPoster1Script:
	message CeladonGameCorner_Johto_CeladonGameCornerPoster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerPoster2Script:
	message CeladonGameCorner_Johto_CeladonGameCornerPoster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerLuckySlotMachineScript:
	random 6
	goto_if_eq VAR_RESULT, 0, CeladonGameCorner_Johto_CeladonGameCornerSlotMachineScript
	setvar VAR_RESULT, FALSE
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerSlotMachineScript:
	setvar VAR_RESULT, TRUE
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerCardFlipScript:
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerLighterScript:
	message CeladonGameCorner_Johto_CeladonGameCornerLighterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerSodaCanScript:
	message CeladonGameCorner_Johto_CeladonGameCornerSodaCanText
	waitmessage
	waitbuttonpress
	goto MauvilleCity_GameCorner_EventScript_SlotMachine0
	closemessage
	releaseall
	end

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GiveCoins_Sub:
	goto Johto_Std_ReceiveItemScript_Sub

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_coinname:
	.string "COIN$"

CeladonGameCorner_Johto_CeladonGameCornerReceptionistText:
	.string "Welcome!"
	.string "\pYou may exchange\n"
	.string "your coins for"
	.string "\pfabulous prizes\n"
	.string "next door.$"

CeladonGameCorner_Johto_CeladonGameCornerPokefanMText:
	.string "The slot machines\n"
	.string "are all state of\l"
	.string "the art.$"

CeladonGameCorner_Johto_CeladonGameCornerTeacherText:
	.string "It's this machine\n"
	.string "I want."
	.string "\pIt cleaned me out\n"
	.string "yesterday, so it"
	.string "\pshould pay out\n"
	.string "today.$"

CeladonGameCorner_Johto_CeladonGameCornerFishingGuruText:
	.string "I think this slot\n"
	.string "machine will pay\l"
	.string "out…"
	.string "\pThe odds vary\n"
	.string "among machines.$"

CeladonGameCorner_Johto_CeladonGameCornerFisherText1:
	.string "Gahahaha!"
	.string "\pThe coins just\n"
	.string "keep popping out!"
	.string "\pHm? What, kid? You\n"
	.string "want to play?"
	.string "\pI'll share my luck\n"
	.string "with you!$"

CeladonGameCorner_Johto_CeladonGameCornerFisherText2:
	.string "Gahahaha!"
	.string "\pIt makes me feel\n"
	.string "good to do nice"
	.string "\pthings for other\n"
	.string "people!$"

CeladonGameCorner_Johto_CeladonGameCornerFisherNoCoinCaseText:
	.string "Hey, you don't\n"
	.string "have a COIN CASE."
	.string "\pHow am I supposed\n"
	.string "to give you any\l"
	.string "coins, kid?$"

CeladonGameCorner_Johto_CeladonGameCornerFisherFullCoinCaseText:
	.string "Hey, your COIN\n"
	.string "CASE is full, kid."
	.string "\pYou must be riding\n"
	.string "a winning streak\l"
	.string "too.$"

CeladonGameCorner_Johto_CeladonGymGuideText:
	.string "Hey! CHAMP in\n"
	.string "making!"
	.string "\pAre you playing\n"
	.string "the slots too?"
	.string "\pI'm trying to get\n"
	.string "enough coins for a\l"
	.string "prize POKéMON."
	.string "\pBut I don't have\n"
	.string "enough coins yet…$"

CeladonGameCorner_Johto_CeladonGameCornerGrampsText:
	.string "Hmmm… The odds are\n"
	.string "surely better for"
	.string "\pPIKACHU's line,\n"
	.string "but… What to do?$"

CeladonGameCorner_Johto_CeladonGameCornerPoster1Text:
	.string "Hey!"
	.string "\pUnderneath this\n"
	.string "poster…"
	.string "\pThere's nothing!$"

CeladonGameCorner_Johto_CeladonGameCornerPoster2Text:
	.string "Hey!"
	.string "\pUnderneath this\n"
	.string "poster…"
	.string "\pThere's nothing!$"

CeladonGameCorner_Johto_CeladonGameCornerLighterText:
	.string "There's a lighter\n"
	.string "here.$"

CeladonGameCorner_Johto_CeladonGameCornerSodaCanText:
	.string "A can of soda…"
	.string "\pSomeone must be\n"
	.string "coming back…"
	.string "\pHuh? It's empty!$"
