EcruteakMart_Johto_MapScripts::
	.byte 0

EcruteakMart_Johto_EcruteakMartClerkScript_Entry::
	lockall
	goto EcruteakMart_Johto_EcruteakMartClerkScript

EcruteakMart_Johto_EcruteakMartSuperNerdScript_Entry::
	lockall
	goto EcruteakMart_Johto_EcruteakMartSuperNerdScript

EcruteakMart_Johto_EcruteakMartGrannyScript_Entry::
	lockall
	goto EcruteakMart_Johto_EcruteakMartGrannyScript


EcruteakMart_Johto_EcruteakMartClerkScript:
	pokemart Johto_Mart_ECRUTEAK
	closemessage
	releaseall
	end

EcruteakMart_Johto_EcruteakMartSuperNerdScript:
	faceplayer
	message EcruteakMart_Johto_EcruteakMartSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakMart_Johto_EcruteakMartGrannyScript:
	faceplayer
	message EcruteakMart_Johto_EcruteakMartGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakMart_Johto_EcruteakMartSuperNerdText:
	.string "My EEVEE evolved\n"
	.string "into an ESPEON."
	.string "\pBut my friend's\n"
	.string "EEVEE turned into\l"
	.string "an UMBREON."
	.string "\pI wonder why? We\n"
	.string "both were raising"
	.string "\pour EEVEE in the\n"
	.string "same way…$"

EcruteakMart_Johto_EcruteakMartGrannyText:
	.string "If you use REVIVE,\n"
	.string "a POKéMON that's"
	.string "\pfainted will wake\n"
	.string "right up.$"
