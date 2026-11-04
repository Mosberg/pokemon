CeladonDeptStore5F_Johto_MapScripts::
	.byte 0

CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk1Script_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk1Script

CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk2Script_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk2Script

CeladonDeptStore5F_Johto_CeladonDeptStore5FGentlemanScript_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FGentlemanScript

CeladonDeptStore5F_Johto_CeladonDeptStore5FSailorScript_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FSailorScript

CeladonDeptStore5F_Johto_CeladonDeptStore5FTeacherScript_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FTeacherScript

CeladonDeptStore5F_Johto_CeladonDeptStore5FDirectory_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FDirectory

CeladonDeptStore5F_Johto_CeladonDeptStore5FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore5F_Johto_CeladonDeptStore5FElevatorButton


CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk1Script:
	faceplayer
	pokemart Johto_Mart_CELADON_5F_1
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FClerk2Script:
	faceplayer
	pokemart Johto_Mart_CELADON_5F_2
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FGentlemanScript:
	faceplayer
	message CeladonDeptStore5F_Johto_CeladonDeptStore5FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FSailorScript:
	faceplayer
	message CeladonDeptStore5F_Johto_CeladonDeptStore5FSailorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FTeacherScript:
	faceplayer
	message CeladonDeptStore5F_Johto_CeladonDeptStore5FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FDirectory:
	message CeladonDeptStore5F_Johto_CeladonDeptStore5FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore5F_Johto_CeladonDeptStore5FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

CeladonDeptStore5F_Johto_CeladonDeptStore5FGentlemanText:
	.string "I want to buy some\n"
	.string "items that raise"
	.string "\pPOKéMON stats, but\n"
	.string "I don't have\l"
	.string "enough money…$"

CeladonDeptStore5F_Johto_CeladonDeptStore5FSailorText:
	.string "I want PP UP, so I\n"
	.string "can raise the PP"
	.string "\pof moves. But you\n"
	.string "can't buy it…$"

CeladonDeptStore5F_Johto_CeladonDeptStore5FTeacherText:
	.string "Using items on\n"
	.string "them makes POKé-\l"
	.string "MON happy."
	.string "\pThey hate certain\n"
	.string "items, though…$"

CeladonDeptStore5F_Johto_CeladonDeptStore5FDirectoryText:
	.string "5F: DRUG STORE$"
