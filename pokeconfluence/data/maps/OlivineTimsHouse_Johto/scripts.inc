OlivineTimsHouse_Johto_MapScripts::
	.byte 0

OlivineTimsHouse_Johto_Tim_Entry::
	lockall
	goto OlivineTimsHouse_Johto_Tim

OlivineTimsHouse_Johto_TimsHouseBookshelf_Entry::
	lockall
	goto OlivineTimsHouse_Johto_TimsHouseBookshelf


OlivineTimsHouse_Johto_Tim:
	faceplayer
	goto Johto_Std_Trade_TIM

OlivineTimsHouse_Johto_TimsHouseBookshelf:
	goto Johto_Std_MagazineBookshelfScript
