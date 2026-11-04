GoldenrodDeptStore1F_Johto_MapScripts::
	.byte 0

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FReceptionistScript_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FReceptionistScript

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FPokefanFScript_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FPokefanFScript

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FBugCatcherScript_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FBugCatcherScript

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FGentlemanScript_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FGentlemanScript

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FDirectory_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FDirectory

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FElevatorButton_Entry::
	lockall
	goto GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FElevatorButton


GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FReceptionistScript:
	faceplayer
	message GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FGentlemanScript:
	faceplayer
	message GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FPokefanFScript:
	faceplayer
	message GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FBugCatcherScript:
	faceplayer
	message GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FDirectory:
	message GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FElevatorButton:
	goto Johto_Std_ElevatorButtonScript

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FReceptionistText:
	.string "Welcome to GOLDEN-\n"
	.string "ROD DEPT.STORE.$"

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FGentlemanText:
	.string "The DEPT.STORE\n"
	.string "has a decent se-\l"
	.string "lection."
	.string "\pBut some items\n"
	.string "are only available"
	.string "\pas GAME CORNER\n"
	.string "prizes.$"

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FPokefanFText:
	.string "I'm raring to shop\n"
	.string "again today!$"

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FBugCatcherText:
	.string "Mom's good at\n"
	.string "bargain hunting."
	.string "\pShe always buys\n"
	.string "stuff at lower\l"
	.string "prices.$"

GoldenrodDeptStore1F_Johto_GoldenrodDeptStore1FDirectoryText:
	.string "1F SERVICE COUNTER"
	.string "\p2F TRAINER'S\n"
	.string "   MARKET"
	.string "\p3F BATTLE\n"
	.string "   COLLECTION"
	.string "\p4F MEDICINE BOX"
	.string "\p5F TM CORNER"
	.string "\p6F TRANQUIL SQUARE"
	.string "\pROOFTOP LOOKOUT$"
