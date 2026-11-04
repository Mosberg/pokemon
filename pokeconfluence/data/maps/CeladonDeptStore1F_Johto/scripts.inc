CeladonDeptStore1F_Johto_MapScripts::
	.byte 0

CeladonDeptStore1F_Johto_CeladonDeptStore1FReceptionistScript_Entry::
	lockall
	goto CeladonDeptStore1F_Johto_CeladonDeptStore1FReceptionistScript

CeladonDeptStore1F_Johto_CeladonDeptStore1FGentlemanScript_Entry::
	lockall
	goto CeladonDeptStore1F_Johto_CeladonDeptStore1FGentlemanScript

CeladonDeptStore1F_Johto_CeladonDeptStore1FTeacherScript_Entry::
	lockall
	goto CeladonDeptStore1F_Johto_CeladonDeptStore1FTeacherScript

CeladonDeptStore1F_Johto_CeladonDeptStore1FDirectory_Entry::
	lockall
	goto CeladonDeptStore1F_Johto_CeladonDeptStore1FDirectory

CeladonDeptStore1F_Johto_CeladonDeptStore1FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore1F_Johto_CeladonDeptStore1FElevatorButton


CeladonDeptStore1F_Johto_CeladonDeptStore1FReceptionistScript:
	faceplayer
	message CeladonDeptStore1F_Johto_CeladonDeptStore1FReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore1F_Johto_CeladonDeptStore1FGentlemanScript:
	faceplayer
	message CeladonDeptStore1F_Johto_CeladonDeptStore1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore1F_Johto_CeladonDeptStore1FTeacherScript:
	faceplayer
	message CeladonDeptStore1F_Johto_CeladonDeptStore1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore1F_Johto_CeladonDeptStore1FDirectory:
	message CeladonDeptStore1F_Johto_CeladonDeptStore1FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore1F_Johto_CeladonDeptStore1FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

CeladonDeptStore1F_Johto_CeladonDeptStore1FReceptionistText:
	.string "Hello! Welcome to\n"
	.string "CELADON DEPT.\l"
	.string "STORE!"
	.string "\pThe directory is\n"
	.string "on the wall.$"

CeladonDeptStore1F_Johto_CeladonDeptStore1FGentlemanText:
	.string "This DEPT.STORE is\n"
	.string "part of the same"
	.string "\pchain as the one\n"
	.string "in GOLDENROD CITY."
	.string "\pThey were both\n"
	.string "renovated at the\l"
	.string "same time.$"

CeladonDeptStore1F_Johto_CeladonDeptStore1FTeacherText:
	.string "This is my first\n"
	.string "time here."
	.string "\pIt's so big…"
	.string "\pI'm afraid I'll\n"
	.string "get lost.$"

CeladonDeptStore1F_Johto_CeladonDeptStore1FDirectoryText:
	.string "1F: SERVICE\n"
	.string "    COUNTER"
	.string "\p2F: TRAINER'S\n"
	.string "    MARKET"
	.string "\p3F: TM SHOP"
	.string "\p4F: WISEMAN GIFTS"
	.string "\p5F: DRUG STORE"
	.string "\p6F: ROOFTOP\n"
	.string "    SQUARE$"
