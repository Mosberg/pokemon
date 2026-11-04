CherrygroveMart_Johto_MapScripts::
	.byte 0

CherrygroveMart_Johto_CherrygroveMartClerkScript_Entry::
	lockall
	goto CherrygroveMart_Johto_CherrygroveMartClerkScript

CherrygroveMart_Johto_CherrygroveMartCooltrainerMScript_Entry::
	lockall
	goto CherrygroveMart_Johto_CherrygroveMartCooltrainerMScript

CherrygroveMart_Johto_CherrygroveMartYoungsterScript_Entry::
	lockall
	goto CherrygroveMart_Johto_CherrygroveMartYoungsterScript


CherrygroveMart_Johto_CherrygroveMartClerkScript:
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, CherrygroveMart_Johto_CherrygroveMartClerkScript_PokeBallsInStock
	pokemart Johto_Mart_CHERRYGROVE
	closemessage
	releaseall
	end

CherrygroveMart_Johto_CherrygroveMartClerkScript_PokeBallsInStock:
	pokemart Johto_Mart_CHERRYGROVE_DEX
	closemessage
	releaseall
	end

CherrygroveMart_Johto_CherrygroveMartCooltrainerMScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, CherrygroveMart_Johto_CherrygroveMartCooltrainerMScript_PokeBallsInStock
	message CherrygroveMart_Johto_CherrygroveMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygroveMart_Johto_CherrygroveMartCooltrainerMScript_PokeBallsInStock:
	message CherrygroveMart_Johto_CherrygroveMartCooltrainerMText_PokeBallsInStock
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygroveMart_Johto_CherrygroveMartYoungsterScript:
	faceplayer
	message CherrygroveMart_Johto_CherrygroveMartYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CherrygroveMart_Johto_CherrygroveMartCooltrainerMText:
	.string "They're fresh out\n"
	.string "of POKé BALLS!"
	.string "\pWhen will they get\n"
	.string "more of them?$"

CherrygroveMart_Johto_CherrygroveMartCooltrainerMText_PokeBallsInStock:
	.string "POKé BALLS are in\n"
	.string "stock! Now I can\l"
	.string "catch POKéMON!$"

CherrygroveMart_Johto_CherrygroveMartYoungsterText:
	.string "When I was walking\n"
	.string "in the grass, a"
	.string "\pbug POKéMON poi-\n"
	.string "soned my POKéMON!"
	.string "\pI just kept going,\n"
	.string "but then my\l"
	.string "POKéMON fainted."
	.string "\pYou should keep an\n"
	.string "ANTIDOTE with you.$"
