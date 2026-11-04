CeladonDeptStore4F_Johto_MapScripts::
	.byte 0

CeladonDeptStore4F_Johto_CeladonDeptStore4FClerkScript_Entry::
	lockall
	goto CeladonDeptStore4F_Johto_CeladonDeptStore4FClerkScript

CeladonDeptStore4F_Johto_CeladonDeptStore4FSuperNerdScript_Entry::
	lockall
	goto CeladonDeptStore4F_Johto_CeladonDeptStore4FSuperNerdScript

CeladonDeptStore4F_Johto_CeladonDeptStore4FYoungsterScript_Entry::
	lockall
	goto CeladonDeptStore4F_Johto_CeladonDeptStore4FYoungsterScript

CeladonDeptStore4F_Johto_CeladonDeptStore4FDirectory_Entry::
	lockall
	goto CeladonDeptStore4F_Johto_CeladonDeptStore4FDirectory

CeladonDeptStore4F_Johto_CeladonDeptStore4FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore4F_Johto_CeladonDeptStore4FElevatorButton


CeladonDeptStore4F_Johto_CeladonDeptStore4FClerkScript:
	faceplayer
	pokemart Johto_Mart_CELADON_4F
	closemessage
	releaseall
	end

CeladonDeptStore4F_Johto_CeladonDeptStore4FSuperNerdScript:
	faceplayer
	message CeladonDeptStore4F_Johto_CeladonDeptStore4FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore4F_Johto_CeladonDeptStore4FYoungsterScript:
	faceplayer
	message CeladonDeptStore4F_Johto_CeladonDeptStore4FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore4F_Johto_CeladonDeptStore4FDirectory:
	message CeladonDeptStore4F_Johto_CeladonDeptStore4FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore4F_Johto_CeladonDeptStore4FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

CeladonDeptStore4F_Johto_CeladonDeptStore4FSuperNerdText:
	.string "I'm here to buy\n"
	.string "SURF MAIL to send\l"
	.string "to my girlfriend.$"

CeladonDeptStore4F_Johto_CeladonDeptStore4FYoungsterText:
	.string "This is the only\n"
	.string "place where you"
	.string "\pcan buy LOVELY\n"
	.string "MAIL.$"

CeladonDeptStore4F_Johto_CeladonDeptStore4FDirectoryText:
	.string "Express Yourself\n"
	.string "With Gifts!"
	.string "\p4F: WISEMAN GIFTS$"
