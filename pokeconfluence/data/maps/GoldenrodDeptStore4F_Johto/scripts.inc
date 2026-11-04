GoldenrodDeptStore4F_Johto_MapScripts::
	.byte 0

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FClerkScript_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FClerkScript

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FCooltrainerMScript_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FCooltrainerMScript

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FBugCatcherScript_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FBugCatcherScript

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FGameboyKidScript_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FGameboyKidScript

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FDirectory_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FDirectory

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FElevatorButton_Entry::
	lockall
	goto GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FElevatorButton


GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FClerkScript:
	faceplayer
	pokemart Johto_Mart_GOLDENROD_4F
	closemessage
	releaseall
	end

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FCooltrainerMScript:
	faceplayer
	message GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FBugCatcherScript:
	faceplayer
	message GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FGameboyKidScript:
	faceplayer
	message GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Down
	waitmovement 4
	releaseall
	end

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FDirectory:
	message GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FCooltrainerMText:
	.string "Hey. I love strong\n"
	.string "POKéMON."
	.string "\pI feed them PRO-\n"
	.string "TEIN to crank up\l"
	.string "their ATTACK.$"

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FBugCatcherText:
	.string "IRON adds to your\n"
	.string "POKéMON's DEFENSE.$"

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FGameboyKidText:
	.string "Some POKéMON\n"
	.string "evolve only by"
	.string "\pbeing traded via a\n"
	.string "Game Link cable."
	.string "\pI know of four:\n"
	.string "MACHOKE, KADABRA,"
	.string "\pHAUNTER and, um,\n"
	.string "GRAVELER."
	.string "\pI heard there are\n"
	.string "others too.$"

GoldenrodDeptStore4F_Johto_GoldenrodDeptStore4FDirectoryText:
	.string "Let Us Pump Up\n"
	.string "Your POKéMON!"
	.string "\p4F MEDICINE BOX$"
