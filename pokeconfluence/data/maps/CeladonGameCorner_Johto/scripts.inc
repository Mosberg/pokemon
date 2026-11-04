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
	@ TODO unsupported: writetext CeladonGameCornerTeacherText
	goto Johto_EventScript_Unimplemented

CeladonGameCorner_Johto_CeladonGameCornerFishingGuruScript:
	faceplayer
	@ TODO unsupported: writetext CeladonGameCornerFishingGuruText
	goto Johto_EventScript_Unimplemented

CeladonGameCorner_Johto_CeladonGameCornerFisherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_COINS_FROM_GAMBLER_AT_CELADON, CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GotCoins
	@ TODO unsupported: writetext CeladonGameCornerFisherText1
	goto Johto_EventScript_Unimplemented

CeladonGameCorner_Johto_CeladonGameCornerFisherScript_GotCoins:
	message CeladonGameCorner_Johto_CeladonGameCornerFisherText2
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
	@ TODO unsupported: writetext CeladonGameCornerGrampsText
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special SlotMachine
	goto Johto_EventScript_Unimplemented

CeladonGameCorner_Johto_CeladonGameCornerSlotMachineScript:
	setvar VAR_RESULT, TRUE
	@ TODO unsupported: special SlotMachine
	goto Johto_EventScript_Unimplemented

CeladonGameCorner_Johto_CeladonGameCornerCardFlipScript:
	@ TODO unsupported: special CardFlip
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: special CardFlip
	goto Johto_EventScript_Unimplemented

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

CeladonGameCorner_Johto_CeladonGameCornerFisherText2:
	.string "Gahahaha!"
	.string "\pIt makes me feel\n"
	.string "good to do nice"
	.string "\pthings for other\n"
	.string "people!$"

CeladonGameCorner_Johto_CeladonGymGuideText:
	.string "(text not converted)$"

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
