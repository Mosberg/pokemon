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
	@ TODO unsupported: loadmenu .MenuHeader
	goto Johto_EventScript_Unimplemented

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
