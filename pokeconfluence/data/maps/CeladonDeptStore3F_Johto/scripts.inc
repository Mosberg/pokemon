CeladonDeptStore3F_Johto_MapScripts::
	.byte 0

CeladonDeptStore3F_Johto_CeladonDeptStore3FClerkScript_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FClerkScript

CeladonDeptStore3F_Johto_CeladonDeptStore3FYoungsterScript_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FYoungsterScript

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid1Script_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid1Script

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid2Script_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid2Script

CeladonDeptStore3F_Johto_CeladonDeptStore3FSuperNerdScript_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FSuperNerdScript

CeladonDeptStore3F_Johto_CeladonDeptStore3FDirectory_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FDirectory

CeladonDeptStore3F_Johto_CeladonDeptStore3FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore3F_Johto_CeladonDeptStore3FElevatorButton


CeladonDeptStore3F_Johto_CeladonDeptStore3FClerkScript:
	faceplayer
	pokemart Johto_Mart_CELADON_3F
	closemessage
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FYoungsterScript:
	faceplayer
	message CeladonDeptStore3F_Johto_CeladonDeptStore3FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid1Script:
	faceplayer
	message CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid1Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid2Script:
	faceplayer
	message CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid2Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Down
	waitmovement 4
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FSuperNerdScript:
	faceplayer
	message CeladonDeptStore3F_Johto_CeladonDeptStore3FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

CeladonDeptStore3F_Johto_CeladonDeptStore3FDirectory:
	message CeladonDeptStore3F_Johto_CeladonDeptStore3FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore3F_Johto_CeladonDeptStore3FYoungsterText:
	.string "I can't decide\n"
	.string "which POKéMON I"
	.string "\pshould use this TM\n"
	.string "on…$"

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid1Text:
	.string "Uh-oh! I traded my\n"
	.string "POKéMON without"
	.string "\premoving the UP-\n"
	.string "GRADE from it.$"

CeladonDeptStore3F_Johto_CeladonDeptStore3FGameboyKid2Text:
	.string "Yeah! I'm finally\n"
	.string "getting a PORYGON!"
	.string "\pI'm no good at the\n"
	.string "slots, so I could"
	.string "\pnever get enough\n"
	.string "coins…"
	.string "\p…Huh?"
	.string "\pThe traded PORYGON\n"
	.string "turned into a dif-\l"
	.string "ferent POKéMON!$"

CeladonDeptStore3F_Johto_CeladonDeptStore3FSuperNerdText:
	.string "The TM SHOP sells\n"
	.string "some rare moves.$"

CeladonDeptStore3F_Johto_CeladonDeptStore3FDirectoryText:
	.string "3F: TM SHOP"
	.string "\pMake Your POKéMON\n"
	.string "Stronger!$"
