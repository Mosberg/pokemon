CeladonDeptStore2F_Johto_MapScripts::
	.byte 0

CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk1Script_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk1Script

CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk2Script_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk2Script

CeladonDeptStore2F_Johto_CeladonDeptStore2FPokefanMScript_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FPokefanMScript

CeladonDeptStore2F_Johto_CeladonDeptStore2FYoungsterScript_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FYoungsterScript

CeladonDeptStore2F_Johto_CeladonDeptStore2FDirectory_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FDirectory

CeladonDeptStore2F_Johto_CeladonDeptStore2FElevatorButton_Entry::
	lockall
	goto CeladonDeptStore2F_Johto_CeladonDeptStore2FElevatorButton


CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk1Script:
	faceplayer
	pokemart Johto_Mart_CELADON_2F_1
	closemessage
	releaseall
	end

CeladonDeptStore2F_Johto_CeladonDeptStore2FClerk2Script:
	faceplayer
	pokemart Johto_Mart_CELADON_2F_2
	closemessage
	releaseall
	end

CeladonDeptStore2F_Johto_CeladonDeptStore2FPokefanMScript:
	faceplayer
	message CeladonDeptStore2F_Johto_CeladonDeptStore2FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore2F_Johto_CeladonDeptStore2FYoungsterScript:
	faceplayer
	message CeladonDeptStore2F_Johto_CeladonDeptStore2FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore2F_Johto_CeladonDeptStore2FDirectory:
	message CeladonDeptStore2F_Johto_CeladonDeptStore2FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonDeptStore2F_Johto_CeladonDeptStore2FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

CeladonDeptStore2F_Johto_CeladonDeptStore2FPokefanMText:
	.string "I just recently\n"
	.string "became a trainer."
	.string "\pMy son encouraged\n"
	.string "me to do it."
	.string "\pI'm impressed by\n"
	.string "the selection of\l"
	.string "convenient items.$"

CeladonDeptStore2F_Johto_CeladonDeptStore2FYoungsterText:
	.string "My dad's having a\n"
	.string "hard time learning"
	.string "\pthe names of items\n"
	.string "and how they are"
	.string "\psupposed to be\n"
	.string "used…$"

CeladonDeptStore2F_Johto_CeladonDeptStore2FDirectoryText:
	.string "Top Grade Items\n"
	.string "for Trainers!"
	.string "\p2F: TRAINER'S\n"
	.string "    MARKET$"
