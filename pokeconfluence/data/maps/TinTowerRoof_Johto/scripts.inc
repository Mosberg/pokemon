TinTowerRoof_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTowerRoof_Johto_OnTransition
	.byte 0

TinTowerRoof_Johto_OnTransition:
	call TinTowerRoof_Johto_TinTowerRoofHoOhCallback_Cb
	end

TinTowerRoof_Johto_TinTowerHoOh_Entry::
	lockall
	goto TinTowerRoof_Johto_TinTowerHoOh


TinTowerRoof_Johto_TinTowerHoOh:
	faceplayer
	message TinTowerRoof_Johto_HoOhText
	waitmessage
	playmoncry SPECIES_HO_OH, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	closemessage
	setflag FLAG_JOHTO_FOUGHT_HO_OH
	setwildbattle SPECIES_HO_OH, 60
	dowildbattle
	removeobject 1
	setflag FLAG_JOHTO_SET_WHEN_FOUGHT_HO_OH
	releaseall
	end

TinTowerRoof_Johto_TinTowerRoofHoOhCallback_Cb:
	goto_if_set FLAG_JOHTO_FOUGHT_HO_OH, TinTowerRoof_Johto_TinTowerRoofHoOhCallback_NoAppear_Cb
	checkitem ITEM_RAINBOW_WING, 1
	goto_if_ne VAR_RESULT, 0, TinTowerRoof_Johto_TinTowerRoofHoOhCallback_Appear_Cb
	goto TinTowerRoof_Johto_TinTowerRoofHoOhCallback_NoAppear_Cb

TinTowerRoof_Johto_TinTowerRoofHoOhCallback_Appear_Cb:
	clearflag FLAG_JOHTO_TIN_TOWER_ROOF_HO_OH
	return

TinTowerRoof_Johto_TinTowerRoofHoOhCallback_NoAppear_Cb:
	setflag FLAG_JOHTO_TIN_TOWER_ROOF_HO_OH
	return

TinTowerRoof_Johto_HoOhText:
	.string "Shaoooh!$"
