CeladonMansionRoofHouse_Johto_MapScripts::
	.byte 0

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_Entry::
	lockall
	goto CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript


CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM03_CURSE, CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_GotCurse
	message CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistIntroText
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_ne VAR_RESULT, 0, CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_Night
	message CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistNotNightText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_Night:
	message CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistStoryText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_NoRoom
	setflag FLAG_JOHTO_GOT_TM03_CURSE

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_GotCurse:
	message CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistCurseText
	waitmessage
	waitbuttonpress

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistScript_NoRoom:
	closemessage
	releaseall
	end

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistIntroText:
	.string "Let me recount a\n"
	.string "terrifying tale…$"

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistNotNightText:
	.string "Then again, it's\n"
	.string "not as scary while"
	.string "\pit's still light\n"
	.string "outside."
	.string "\pCome back after\n"
	.string "sunset, OK?$"

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistStoryText:
	.string "Once upon a time,\n"
	.string "there was a little"
	.string "\pboy who was given\n"
	.string "a new BICYCLE…"
	.string "\pHe wanted to try\n"
	.string "it right away…"
	.string "\pHe was having so\n"
	.string "much fun that he"
	.string "\pdidn't notice the\n"
	.string "sun had set…"
	.string "\pWhile riding home\n"
	.string "in the pitch-black"
	.string "\pnight, the bike\n"
	.string "suddenly slowed!"
	.string "\pThe pedals became\n"
	.string "heavy!"
	.string "\pWhen he stopped\n"
	.string "pedaling, the bike"
	.string "\pbegan slipping\n"
	.string "backwards!"
	.string "\pIt was as if the\n"
	.string "bike were cursed"
	.string "\pand trying to drag\n"
	.string "him into oblivion!"
	.string "\p…"
	.string "\p…"
	.string "\pSHRIEEEEK!"
	.string "\pThe boy had been\n"
	.string "riding uphill on\l"
	.string "CYCLING ROAD!"
	.string "\p…\n"
	.string "Ba-dum ba-dum!"
	.string "\pFor listening so\n"
	.string "patiently, you may\l"
	.string "take this--TM03!$"

CeladonMansionRoofHouse_Johto_CeladonMansionRoofHousePharmacistCurseText:
	.string "TM03 is CURSE."
	.string "\pIt's a terrifying\n"
	.string "move that slowly"
	.string "\pwhittles down the\n"
	.string "victim's HP.$"
