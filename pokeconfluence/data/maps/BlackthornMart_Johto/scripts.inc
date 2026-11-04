BlackthornMart_Johto_MapScripts::
	.byte 0

BlackthornMart_Johto_BlackthornMartClerkScript_Entry::
	lockall
	goto BlackthornMart_Johto_BlackthornMartClerkScript

BlackthornMart_Johto_BlackthornMartCooltrainerMScript_Entry::
	lockall
	goto BlackthornMart_Johto_BlackthornMartCooltrainerMScript

BlackthornMart_Johto_BlackthornMartBlackBeltScript_Entry::
	lockall
	goto BlackthornMart_Johto_BlackthornMartBlackBeltScript


BlackthornMart_Johto_BlackthornMartClerkScript:
	pokemart Johto_Mart_BLACKTHORN
	closemessage
	releaseall
	end

BlackthornMart_Johto_BlackthornMartCooltrainerMScript:
	faceplayer
	message BlackthornMart_Johto_BlackthornMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornMart_Johto_BlackthornMartBlackBeltScript:
	faceplayer
	message BlackthornMart_Johto_BlackthornMartBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornMart_Johto_BlackthornMartCooltrainerMText:
	.string "You can't buy MAX\n"
	.string "REVIVE, but it"
	.string "\pfully restores a\n"
	.string "fainted POKéMON."
	.string "\pBeware--it won't\n"
	.string "restore PP, the"
	.string "\pPOWER POINTS\n"
	.string "needed for moves.$"

BlackthornMart_Johto_BlackthornMartBlackBeltText:
	.string "MAX REPEL keeps\n"
	.string "weak POKéMON away\l"
	.string "from you."
	.string "\pIt's the longest\n"
	.string "lasting of the\l"
	.string "REPEL sprays.$"
