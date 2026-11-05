CeladonDeptStore6F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CeladonDeptStore6F_Johto_OnLoad
	.byte 0

CeladonDeptStore6F_Johto_OnLoad:
	call CeladonDeptStore6F_Johto_CeladonDeptStore6FHideRooftopStairsCallback_Cb
	end

CeladonDeptStore6F_Johto_CeladonDeptStore6FSuperNerdScript_Entry::
	lockall
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FSuperNerdScript

CeladonDeptStore6F_Johto_CeladonDeptStore6FYoungsterScript_Entry::
	lockall
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FYoungsterScript

CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectory_Entry::
	lockall
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectory

CeladonDeptStore6F_Johto_CeladonDeptStore1FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore6F_Johto_CeladonDeptStore1FElevatorButton

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Entry::
	lockall
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine


CeladonDeptStore6F_Johto_CeladonDeptStore6FSuperNerdScript:
	faceplayer
	message CeladonDeptStore6F_Johto_CeladonDeptStore6FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore6F_Johto_CeladonDeptStore6FYoungsterScript:
	faceplayer
	message CeladonDeptStore6F_Johto_CeladonDeptStore6FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine:
	message CeladonDeptStore6F_Johto_CeladonVendingText
	waitmessage

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Start:
	dynmultipush Johto_Menu_CeladonDeptStore6F_CeladonDeptStore6FVendingMachine_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_CeladonDeptStore6F_CeladonDeptStore6FVendingMachine_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_CeladonDeptStore6F_CeladonDeptStore6FVendingMachine_MenuHeader_Opt3, 3
	dynmultipush Johto_Menu_CeladonDeptStore6F_CeladonDeptStore6FVendingMachine_MenuHeader_Opt4, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_FreshWater
	goto_if_eq VAR_RESULT, 2, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_SodaPop
	goto_if_eq VAR_RESULT, 3, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Lemonade
	closemessage
	releaseall
	end

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_FreshWater:
	checkmoney 200
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughMoney
	additem ITEM_FRESH_WATER
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughSpace
	removemoney 200
	bufferitemname STR_VAR_1, ITEM_FRESH_WATER
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_VendItem

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_SodaPop:
	checkmoney 300
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughMoney
	additem ITEM_SODA_POP
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughSpace
	removemoney 300
	bufferitemname STR_VAR_1, ITEM_SODA_POP
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_VendItem

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Lemonade:
	checkmoney 350
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughMoney
	additem ITEM_LEMONADE
	goto_if_eq VAR_RESULT, 0, CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughSpace
	removemoney 350
	bufferitemname STR_VAR_1, ITEM_LEMONADE
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_VendItem

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_VendItem:
	delay 10
	playse SE_DOOR
	message CeladonDeptStore6F_Johto_CeladonClangText
	waitmessage
	waitbuttonpress
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Start

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughMoney:
	message CeladonDeptStore6F_Johto_CeladonVendingNoMoneyText
	waitmessage
	waitbuttonpress
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Start

CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_NotEnoughSpace:
	message CeladonDeptStore6F_Johto_CeladonVendingNoSpaceText
	waitmessage
	waitbuttonpress
	goto CeladonDeptStore6F_Johto_CeladonDeptStore6FVendingMachine_Start

CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectory:
	message CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore6F_Johto_CeladonDeptStore1FElevatorButton:
	message CeladonDeptStore6F_Johto_CeladonDeptStore6FElevatorButtonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore6F_Johto_CeladonDeptStore6FHideRooftopStairsCallback_Cb:
	setmetatile 12, 0, 514, 1
	setmetatile 13, 0, 514, 1
	setmetatile 12, 1, 515, 0
	setmetatile 13, 1, 515, 0
	special DrawWholeMapView
	return

CeladonDeptStore6F_Johto_CeladonVendingText:
	.string "A vending machine!\n"
	.string "Here's the menu.$"

CeladonDeptStore6F_Johto_CeladonClangText:
	.string "Clang!"
	.string "\p{STR_VAR_1}\n"
	.string "popped out.$"

CeladonDeptStore6F_Johto_CeladonVendingNoMoneyText:
	.string "Oops, not enough\n"
	.string "money…$"

CeladonDeptStore6F_Johto_CeladonVendingNoSpaceText:
	.string "There's no more\n"
	.string "room for stuff…$"

CeladonDeptStore6F_Johto_CeladonDeptStore6FSuperNerdText:
	.string "A vending machine\n"
	.string "with a prize rou-\l"
	.string "lette…"
	.string "\pYou never see\n"
	.string "those anymore.$"

CeladonDeptStore6F_Johto_CeladonDeptStore6FYoungsterText:
	.string "Aww! There's no\n"
	.string "games here!"
	.string "\pI wanted to play…$"

CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectoryText:
	.string "6F: ROOFTOP SQUARE\n"
	.string "VENDING MACHINES$"

CeladonDeptStore6F_Johto_CeladonDeptStore6FElevatorButtonText:
	.string "It's the elevator\n"
	.string "button.$"
