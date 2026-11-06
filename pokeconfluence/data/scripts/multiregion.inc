@ POKE-MULTIREGION: choosing a start region and sailing between Hoenn and Kanto.

Multiregion_EventScript_ChooseStartRegion::
	msgbox Multiregion_Text_ChooseStartRegion, MSGBOX_DEFAULT
	dynmultipush Multiregion_Text_RegionKanto, 0
	dynmultipush Multiregion_Text_RegionJohto, 1
	dynmultipush Multiregion_Text_RegionHoenn, 2
	dynmultistack 0, 0, TRUE, 3, FALSE, 2, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, Multiregion_EventScript_StartInKanto
	case 1, Multiregion_EventScript_StartInJohto
	return

Multiregion_EventScript_StartInKanto::
	setrespawn HEAL_LOCATION_PALLET_TOWN
	setvar VAR_LITTLEROOT_INTRO_STATE, 7
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_PALLET_TOWN_PLAYERS_HOUSE_2F, 6, 6
	waitstate
	end

Multiregion_EventScript_StartInJohto::
	setrespawn HEAL_LOCATION_JOHTO_NEW_BARK_TOWN
	setvar VAR_LITTLEROOT_INTRO_STATE, 7
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_JOHTO_PLAYERS_HOUSE_2F, 3, 3
	waitstate
	end

Multiregion_EventScript_SailToKanto::
	msgbox Multiregion_Text_SailToKantoQuestion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Multiregion_EventScript_DeclineSail
	msgbox Multiregion_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WORLD_MAP_VERMILION_CITY
	warp MAP_VERMILION_CITY, 23, 33
	waitstate
	end

Multiregion_EventScript_SailToHoenn::
	msgbox Multiregion_Text_SailToHoennQuestion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Multiregion_EventScript_DeclineSail
	msgbox Multiregion_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_VISITED_SLATEPORT_CITY
	warp MAP_SLATEPORT_CITY_HARBOR, 12, 13
	waitstate
	end

Multiregion_EventScript_DeclineSail::
	msgbox Multiregion_Text_ComeBackAnytime, MSGBOX_DEFAULT
	release
	end

Multiregion_Text_ChooseStartRegion:
	.string "Where will your adventure begin?$"

Multiregion_Text_RegionKanto:
	.string "Kanto$"

Multiregion_Text_RegionJohto:
	.string "Johto$"

Multiregion_Text_RegionHoenn:
	.string "Hoenn$"

Multiregion_Text_SailToKantoQuestion:
	.string "Ahoy! There's a ferry to VERMILION CITY\n"
	.string "in the KANTO region.\p"
	.string "Would you like to sail there?$"

Multiregion_Text_SailToHoennQuestion:
	.string "Ahoy! A ferry sails back to SLATEPORT\n"
	.string "CITY in the HOENN region.\p"
	.string "Would you like to sail there?$"

Multiregion_Text_AllAboard:
	.string "All aboard!$"

Multiregion_Text_ComeBackAnytime:
	.string "Come back anytime!$"
