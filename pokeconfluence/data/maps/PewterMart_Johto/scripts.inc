PewterMart_Johto_MapScripts::
	.byte 0

PewterMart_Johto_PewterMartClerkScript_Entry::
	lockall
	goto PewterMart_Johto_PewterMartClerkScript

PewterMart_Johto_PewterMartYoungsterScript_Entry::
	lockall
	goto PewterMart_Johto_PewterMartYoungsterScript

PewterMart_Johto_PewterMartSuperNerdScript_Entry::
	lockall
	goto PewterMart_Johto_PewterMartSuperNerdScript


PewterMart_Johto_PewterMartClerkScript:
	pokemart Johto_Mart_PEWTER
	closemessage
	releaseall
	end

PewterMart_Johto_PewterMartYoungsterScript:
	faceplayer
	message PewterMart_Johto_PewterMartYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterMart_Johto_PewterMartSuperNerdScript:
	faceplayer
	message PewterMart_Johto_PewterMartSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PewterMart_Johto_PewterMartYoungsterText:
	.string "Hi! Check out my\n"
	.string "GYARADOS!"
	.string "\pI raised it from a\n"
	.string "MAGIKARP. I can't"
	.string "\pbelieve how strong\n"
	.string "it has become.$"

PewterMart_Johto_PewterMartSuperNerdText:
	.string "There once was a\n"
	.string "weird old man who\l"
	.string "sold MAGIKARP."
	.string "\pHe was saying the\n"
	.string "MAGIKARP from the"
	.string "\pLAKE OF RAGE were\n"
	.string "excellent.$"
