SaffronMart_Johto_MapScripts::
	.byte 0

SaffronMart_Johto_SaffronMartClerkScript_Entry::
	lockall
	goto SaffronMart_Johto_SaffronMartClerkScript

SaffronMart_Johto_SaffronMartCooltrainerMScript_Entry::
	lockall
	goto SaffronMart_Johto_SaffronMartCooltrainerMScript

SaffronMart_Johto_SaffronMartCooltrainerFScript_Entry::
	lockall
	goto SaffronMart_Johto_SaffronMartCooltrainerFScript


SaffronMart_Johto_SaffronMartClerkScript:
	pokemart Johto_Mart_SAFFRON
	closemessage
	releaseall
	end

SaffronMart_Johto_SaffronMartCooltrainerMScript:
	faceplayer
	message SaffronMart_Johto_SaffronMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMart_Johto_SaffronMartCooltrainerFScript:
	faceplayer
	message SaffronMart_Johto_SaffronMartCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronMart_Johto_SaffronMartCooltrainerMText:
	.string "There's a big\n"
	.string "RADIO TOWER in\l"
	.string "LAVENDER.$"

SaffronMart_Johto_SaffronMartCooltrainerFText:
	.string "I want to become\n"
	.string "stronger, but I'm\l"
	.string "not good yet…"
	.string "\pCould you show me\n"
	.string "how sometime?$"
