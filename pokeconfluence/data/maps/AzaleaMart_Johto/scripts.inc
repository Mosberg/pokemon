AzaleaMart_Johto_MapScripts::
	.byte 0

AzaleaMart_Johto_AzaleaMartClerkScript_Entry::
	lockall
	goto AzaleaMart_Johto_AzaleaMartClerkScript

AzaleaMart_Johto_AzaleaMartCooltrainerMScript_Entry::
	lockall
	goto AzaleaMart_Johto_AzaleaMartCooltrainerMScript

AzaleaMart_Johto_AzaleaMartBugCatcherScript_Entry::
	lockall
	goto AzaleaMart_Johto_AzaleaMartBugCatcherScript


AzaleaMart_Johto_AzaleaMartClerkScript:
	pokemart Johto_Mart_AZALEA
	closemessage
	releaseall
	end

AzaleaMart_Johto_AzaleaMartCooltrainerMScript:
	faceplayer
	message AzaleaMart_Johto_AzaleaMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaMart_Johto_AzaleaMartBugCatcherScript:
	faceplayer
	message AzaleaMart_Johto_AzaleaMartBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

AzaleaMart_Johto_AzaleaMartCooltrainerMText:
	.string "There's no GREAT\n"
	.string "BALL here. POKé"
	.string "\pBALLS will have\n"
	.string "to do."
	.string "\pI wish KURT would\n"
	.string "make me some of\l"
	.string "his custom BALLS.$"

AzaleaMart_Johto_AzaleaMartBugCatcherText:
	.string "A GREAT BALL is\n"
	.string "better for catch-\l"
	.string "ing POKéMON than a\l"
	.string "POKé BALL."
	.string "\pBut KURT's might\n"
	.string "be better some-\l"
	.string "times.$"
