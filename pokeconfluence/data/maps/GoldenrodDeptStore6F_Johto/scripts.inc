GoldenrodDeptStore6F_Johto_MapScripts::
	.byte 0

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FLassScript_Entry::
	lockall
	goto GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FLassScript

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FSuperNerdScript_Entry::
	lockall
	goto GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FSuperNerdScript

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FDirectory_Entry::
	lockall
	goto GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FDirectory

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FElevatorButton_Entry::
	lockall
	goto GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FElevatorButton

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Entry::
	lockall
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine


GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine:
	message GoldenrodDeptStore6F_Johto_GoldenrodVendingText
	waitmessage

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Start:
	dynmultipush Johto_Menu_GoldenrodDeptStore6F_GoldenrodVendingMachine_MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_GoldenrodDeptStore6F_GoldenrodVendingMachine_MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_GoldenrodDeptStore6F_GoldenrodVendingMachine_MenuHeader_Opt3, 3
	dynmultipush Johto_Menu_GoldenrodDeptStore6F_GoldenrodVendingMachine_MenuHeader_Opt4, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_FreshWater
	goto_if_eq VAR_RESULT, 2, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_SodaPop
	goto_if_eq VAR_RESULT, 3, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Lemonade
	closemessage
	releaseall
	end

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_FreshWater:
	checkmoney 200
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_FRESH_WATER
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 200
	bufferitemname STR_VAR_1, ITEM_FRESH_WATER
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_VendItem

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_SodaPop:
	checkmoney 300
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_SODA_POP
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 300
	bufferitemname STR_VAR_1, ITEM_SODA_POP
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_VendItem

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Lemonade:
	checkmoney 350
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_LEMONADE
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 350
	bufferitemname STR_VAR_1, ITEM_LEMONADE
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_VendItem

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_VendItem:
	delay 10
	playse SE_DOOR
	message GoldenrodDeptStore6F_Johto_GoldenrodClangText
	waitmessage
	waitbuttonpress
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Start

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughMoney:
	message GoldenrodDeptStore6F_Johto_GoldenrodVendingNoMoneyText
	waitmessage
	waitbuttonpress
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Start

GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_NotEnoughSpace:
	message GoldenrodDeptStore6F_Johto_GoldenrodVendingNoSpaceText
	waitmessage
	waitbuttonpress
	goto GoldenrodDeptStore6F_Johto_GoldenrodVendingMachine_Start

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FLassScript:
	faceplayer
	message GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FSuperNerdScript:
	faceplayer
	message GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FDirectory:
	message GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

GoldenrodDeptStore6F_Johto_GoldenrodVendingText:
	.string "A vending machine!\n"
	.string "Here's the menu.$"

GoldenrodDeptStore6F_Johto_GoldenrodClangText:
	.string "Clang! A can of\n"
	.string "{STR_VAR_1}\l"
	.string "popped out!$"

GoldenrodDeptStore6F_Johto_GoldenrodVendingNoMoneyText:
	.string "Oops, not enough\n"
	.string "money.$"

GoldenrodDeptStore6F_Johto_GoldenrodVendingNoSpaceText:
	.string "There's no more\n"
	.string "room for stuff.$"

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FLassText:
	.string "Do you listen to\n"
	.string "LUCKY CHANNEL?"
	.string "\pIf you want to\n"
	.string "win, trade POKéMON"
	.string "\pwith as many peo-\n"
	.string "ple as possible to"
	.string "\pget different ID\n"
	.string "numbers.$"

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FSuperNerdText:
	.string "If you're tired,\n"
	.string "try the vending\l"
	.string "machine's drinks."
	.string "\pYour POKéMON will\n"
	.string "love them too.$"

GoldenrodDeptStore6F_Johto_GoldenrodDeptStore6FDirectoryText:
	.string "Take a Break from\n"
	.string "Shopping!"
	.string "\p6F TRANQUIL SQUARE$"
