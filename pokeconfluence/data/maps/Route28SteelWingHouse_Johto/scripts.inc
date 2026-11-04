Route28SteelWingHouse_Johto_MapScripts::
	.byte 0

Route28SteelWingHouse_Johto_Celebrity_Entry::
	lockall
	goto Route28SteelWingHouse_Johto_Celebrity

Route28SteelWingHouse_Johto_CelebritysFearow_Entry::
	lockall
	goto Route28SteelWingHouse_Johto_CelebritysFearow

Route28SteelWingHouse_Johto_CelebrityHouseBookshelf_Entry::
	lockall
	goto Route28SteelWingHouse_Johto_CelebrityHouseBookshelf


Route28SteelWingHouse_Johto_Celebrity:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM47_STEEL_WING, Route28SteelWingHouse_Johto_Celebrity_AlreadyGotItem
	message Route28SteelWingHouse_Johto_CelebrityText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_STEEL_WING
	goto_if_eq VAR_RESULT, 0, Route28SteelWingHouse_Johto_Celebrity_Done
	setflag FLAG_JOHTO_GOT_TM47_STEEL_WING

Route28SteelWingHouse_Johto_Celebrity_Done:
	closemessage
	releaseall
	end

Route28SteelWingHouse_Johto_Celebrity_AlreadyGotItem:
	message Route28SteelWingHouse_Johto_CelebrityText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route28SteelWingHouse_Johto_CelebritysFearow:
	message Route28SteelWingHouse_Johto_CelebritysFearowText
	waitmessage
	playmoncry SPECIES_FEAROW, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

Route28SteelWingHouse_Johto_CelebrityHouseBookshelf:
	goto Johto_Std_MagazineBookshelfScript

Route28SteelWingHouse_Johto_CelebrityText1:
	.string "Oh, dear.\n"
	.string "You've found me."
	.string "\pPlease don't tell\n"
	.string "anyone about me."
	.string "\pI'll give you this\n"
	.string "for keeping my\l"
	.string "secret. Please?$"

Route28SteelWingHouse_Johto_CelebrityText2:
	.string "It's tough being a\n"
	.string "top celebrity."
	.string "\pEverywhere I go,\n"
	.string "people chase me."
	.string "\pI just want to be\n"
	.string "left alone…$"

Route28SteelWingHouse_Johto_CelebritysFearowText:
	.string "FEAROW: Feero!$"
