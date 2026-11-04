DayOfWeekSiblingsHouse_Johto_MapScripts::
	.byte 0

DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript_Entry::
	lockall
	goto DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript


DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript:
	message DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText1
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript_End
	message DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText2
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript_End
	message DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText3
	waitmessage
	waitbuttonpress

DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexScript_End:
	closemessage
	releaseall
	end

DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText1:
	.string "There's something\n"
	.string "written here."
	.string "\pRead it?$"

DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText2:
	.string "To my brothers and\n"
	.string "sisters:"
	.string "\pWe take pride in\n"
	.string "serving POKéMON\l"
	.string "trainers."
	.string "\pWhen trainers talk\n"
	.string "to you, give them\l"
	.string "something useful."
	.string "\pLove,\n"
	.string "MONICA"
	.string "\pKeep reading?$"

DayOfWeekSiblingsHouse_Johto_DayOfWeekSiblingsHousePokedexText3:
	.string "Monday, MONICA\n"
	.string "ROUTE 40"
	.string "\pTuesday, TUSCANY\n"
	.string "ROUTE 29"
	.string "\pWednesday, WESLEY\n"
	.string "LAKE OF RAGE"
	.string "\pThursday, ARTHUR\n"
	.string "ROUTE 36"
	.string "\pFriday, FRIEDA\n"
	.string "ROUTE 32"
	.string "\pSaturday, SANTOS\n"
	.string "BLACKTHORN CITY"
	.string "\pSunday, SUNNY\n"
	.string "ROUTE 37$"
