MrPsychicsHouse_Johto_MapScripts::
	.byte 0

MrPsychicsHouse_Johto_MrPsychic_Entry::
	lockall
	goto MrPsychicsHouse_Johto_MrPsychic

MrPsychicsHouse_Johto_MrPsychicsHouseBookshelf_Entry::
	lockall
	goto MrPsychicsHouse_Johto_MrPsychicsHouseBookshelf


MrPsychicsHouse_Johto_MrPsychic:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM29_PSYCHIC, MrPsychicsHouse_Johto_MrPsychic_AlreadyGotItem
	message MrPsychicsHouse_Johto_MrPsychicText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_PSYCHIC
	goto_if_eq VAR_RESULT, 0, MrPsychicsHouse_Johto_MrPsychic_Done
	setflag FLAG_JOHTO_GOT_TM29_PSYCHIC

MrPsychicsHouse_Johto_MrPsychic_AlreadyGotItem:
	message MrPsychicsHouse_Johto_MrPsychicText2
	waitmessage
	waitbuttonpress

MrPsychicsHouse_Johto_MrPsychic_Done:
	closemessage
	releaseall
	end

MrPsychicsHouse_Johto_MrPsychicsHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

MrPsychicsHouse_Johto_MrPsychicText1:
	.string "…"
	.string "\p…"
	.string "\p…"
	.string "\p…I got it!"
	.string "\pYou wanted this!$"

MrPsychicsHouse_Johto_MrPsychicText2:
	.string "TM29 is PSYCHIC."
	.string "\pIt may lower the\n"
	.string "target's SPCL.DEF.$"
