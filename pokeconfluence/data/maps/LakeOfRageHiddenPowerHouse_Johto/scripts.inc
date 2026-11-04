LakeOfRageHiddenPowerHouse_Johto_MapScripts::
	.byte 0

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy_Entry::
	lockall
	goto LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerHouseBookshelf_Entry::
	lockall
	goto LakeOfRageHiddenPowerHouse_Johto_HiddenPowerHouseBookshelf


LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM10_HIDDEN_POWER, LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy_AlreadyGotItem
	message LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy_Done
	setflag FLAG_JOHTO_GOT_TM10_HIDDEN_POWER
	message LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy_AlreadyGotItem:
	message LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText3
	waitmessage
	waitbuttonpress

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuy_Done:
	closemessage
	releaseall
	end

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText1:
	.string "…You have strayed\n"
	.string "far…"
	.string "\pHere I have medi-\n"
	.string "tated. Inside me,"
	.string "\pa new power has\n"
	.string "been awakened."
	.string "\pLet me share my\n"
	.string "power with your"
	.string "\pPOKéMON.\n"
	.string "Take this, child.$"

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText2:
	.string "Do you see it? It\n"
	.string "is HIDDEN POWER!"
	.string "\pIt draws out the\n"
	.string "power of POKéMON\l"
	.string "for attacking."
	.string "\pRemember this: its\n"
	.string "type and power de-\l"
	.string "pend on the POKé-\l"
	.string "MON using it.$"

LakeOfRageHiddenPowerHouse_Johto_HiddenPowerGuyText3:
	.string "I am meditating…$"
