CeladonGameCornerPrizeRoom_Johto_MapScripts::
	.byte 0

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomGentlemanScript_Entry::
	lockall
	goto CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomGentlemanScript

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPharmacistScript_Entry::
	lockall
	goto CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPharmacistScript

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomTMVendor_Entry::
	lockall
	goto CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomTMVendor

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPokemonVendor_Entry::
	lockall
	goto CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPokemonVendor


CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomGentlemanScript:
	faceplayer
	message CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPharmacistScript:
	faceplayer
	message CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPharmacistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomTMVendor:
	faceplayer
	message CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_PrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_NoCoinCase
	message CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_AskWhichPrizeText
	waitmessage

CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_tmcounterloop:
	@ TODO unsupported: loadmenu CeladonPrizeRoom_TMMenuHeader
	goto Johto_EventScript_Unimplemented

CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_NoCoinCase:
	message CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_NoCoinCaseText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPokemonVendor:
	faceplayer
	message CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_PrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_NoCoinCase

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPokemonVendor_loop:
	message CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_AskWhichPrizeText
	waitmessage
	@ TODO unsupported: loadmenu .MenuHeader
	goto Johto_EventScript_Unimplemented

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomGentlemanText:
	.string "I wanted PORYGON,\n"
	.string "but I was short by\l"
	.string "100 coins…$"

CeladonGameCornerPrizeRoom_Johto_CeladonGameCornerPrizeRoomPharmacistText:
	.string "Whew…"
	.string "\pI've got to stay\n"
	.string "calm and cool…"
	.string "\pI can't lose my\n"
	.string "cool, or I'll lose\l"
	.string "all my money…$"

CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_PrizeVendorIntroText:
	.string "Welcome!"
	.string "\pWe exchange your\n"
	.string "coins for fabulous\l"
	.string "prizes!$"

CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_AskWhichPrizeText:
	.string "Which prize would\n"
	.string "you like?$"

CeladonGameCornerPrizeRoom_Johto_CeladonPrizeRoom_NoCoinCaseText:
	.string "Oh? You don't have\n"
	.string "a COIN CASE.$"
