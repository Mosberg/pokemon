GoldenrodDeptStore3F_Johto_MapScripts::
	.byte 0

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FClerkScript_Entry::
	lockall
	goto GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FClerkScript

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FSuperNerdScript_Entry::
	lockall
	goto GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FSuperNerdScript

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FRockerScript_Entry::
	lockall
	goto GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FRockerScript

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FDirectory_Entry::
	lockall
	goto GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FDirectory

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FElevatorButton_Entry::
	lockall
	goto GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FElevatorButton


GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FClerkScript:
	faceplayer
	pokemart Johto_Mart_GOLDENROD_3F
	closemessage
	releaseall
	end

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FSuperNerdScript:
	faceplayer
	message GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FRockerScript:
	faceplayer
	message GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FRockerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FDirectory:
	message GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FSuperNerdText:
	.string "I, I, I'm really\n"
	.string "impatient!"
	.string "\pI use X SPEED in\n"
	.string "battle to speed up\l"
	.string "my POKéMON.$"

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FRockerText:
	.string "Hey! When you bat-\n"
	.string "tle, do you use X\l"
	.string "SPECIAL?"
	.string "\pIt's awesome. It\n"
	.string "really jacks up\l"
	.string "SPECIAL ATTACK!$"

GoldenrodDeptStore3F_Johto_GoldenrodDeptStore3FDirectoryText:
	.string "For Victory\n"
	.string "Seekers"
	.string "\p3F BATTLE\n"
	.string "   COLLECTION$"
