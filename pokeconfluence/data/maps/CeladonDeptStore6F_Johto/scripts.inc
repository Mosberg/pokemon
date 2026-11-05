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
	@ TODO unsupported: loadmenu .MenuHeader
	goto Johto_EventScript_Unimplemented

CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectory:
	message CeladonDeptStore6F_Johto_CeladonDeptStore6FDirectoryText
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
