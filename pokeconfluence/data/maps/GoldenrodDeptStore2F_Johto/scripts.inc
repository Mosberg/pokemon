GoldenrodDeptStore2F_Johto_MapScripts::
	.byte 0

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk1Script_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk1Script

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk2Script_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk2Script

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FYoungsterScript_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FYoungsterScript

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FCooltrainerFScript_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FCooltrainerFScript

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FGentlemanScript_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FGentlemanScript

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FDirectory_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FDirectory

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FElevatorButton_Entry::
	lockall
	goto GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FElevatorButton


GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk1Script:
	faceplayer
	pokemart Johto_Mart_GOLDENROD_2F_1
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FClerk2Script:
	faceplayer
	pokemart Johto_Mart_GOLDENROD_2F_2
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FYoungsterScript:
	faceplayer
	message GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FCooltrainerFScript:
	faceplayer
	message GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FGentlemanScript:
	faceplayer
	message GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FDirectory:
	message GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FYoungsterText:
	.string "POKéGEAR can store\n"
	.string "up to ten phone\l"
	.string "numbers."
	.string "\pIt's hard to de-\n"
	.string "cide which numbers\l"
	.string "to keep.$"

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FCooltrainerFText:
	.string "I got my ABRA at\n"
	.string "the GAME CORNER."
	.string "\pNow it's my best\n"
	.string "partner.$"

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FGentlemanText:
	.string "This DEPT.STORE\n"
	.string "makes me realize"
	.string "\pthat GOLDENROD is\n"
	.string "a big city."
	.string "\pThe selection here\n"
	.string "is unmatched any-\l"
	.string "where else.$"

GoldenrodDeptStore2F_Johto_GoldenrodDeptStore2FDirectoryText:
	.string "Your Travel\n"
	.string "Companion"
	.string "\p2F TRAINER'S\n"
	.string "   MARKET$"
