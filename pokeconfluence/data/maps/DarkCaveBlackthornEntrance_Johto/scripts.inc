DarkCaveBlackthornEntrance_Johto_MapScripts::
	.byte 0

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript_Entry::
	lockall
	goto DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceRevive_Entry::
	lockall
	goto DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceRevive

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceTMSnore_Entry::
	lockall
	goto DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceTMSnore


DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_BLACKGLASSES_IN_DARK_CAVE, DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript_GotBlackglasses
	message DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_BLACKGLASSES
	goto_if_eq VAR_RESULT, 0, DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript_PackFull
	setflag FLAG_JOHTO_GOT_BLACKGLASSES_IN_DARK_CAVE

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript_GotBlackglasses:
	message DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistText2
	waitmessage
	waitbuttonpress

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistScript_PackFull:
	closemessage
	releaseall
	end

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceRevive:
	finditem ITEM_REVIVE
	releaseall
	end

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntranceTMSnore:
	finditem ITEM_NUGGET
	releaseall
	end

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistText1:
	.string "Whoa! You startled\n"
	.string "me there!"
	.string "\pI had my BLACK-\n"
	.string "GLASSES on, so I"
	.string "\pdidn't notice you\n"
	.string "at all."
	.string "\pWhat am I doing\n"
	.string "here?"
	.string "\pHey, don't you\n"
	.string "worry about it."
	.string "\pI'll give you a\n"
	.string "pair of BLACK-\l"
	.string "GLASSES, so forget\l"
	.string "you saw me, OK?$"

DarkCaveBlackthornEntrance_Johto_DarkCaveBlackthornEntrancePharmacistText2:
	.string "BLACKGLASSES ups\n"
	.string "the power of dark-\l"
	.string "type moves.$"
