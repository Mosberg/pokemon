VioletMart_Johto_MapScripts::
	.byte 0

VioletMart_Johto_VioletMartClerkScript_Entry::
	lockall
	goto VioletMart_Johto_VioletMartClerkScript

VioletMart_Johto_VioletMartGrannyScript_Entry::
	lockall
	goto VioletMart_Johto_VioletMartGrannyScript

VioletMart_Johto_VioletMartCooltrainerMScript_Entry::
	lockall
	goto VioletMart_Johto_VioletMartCooltrainerMScript


VioletMart_Johto_VioletMartClerkScript:
	pokemart Johto_Mart_VIOLET
	closemessage
	releaseall
	end

VioletMart_Johto_VioletMartGrannyScript:
	faceplayer
	message VioletMart_Johto_VioletMartGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletMart_Johto_VioletMartCooltrainerMScript:
	faceplayer
	message VioletMart_Johto_VioletMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletMart_Johto_VioletMartGrannyText:
	.string "When you first\n"
	.string "catch a POKéMON,\l"
	.string "it may be weak."
	.string "\pBut it will even-\n"
	.string "tually grow to be\l"
	.string "strong."
	.string "\pIt's important to\n"
	.string "treat POKéMON with\l"
	.string "love.$"

VioletMart_Johto_VioletMartCooltrainerMText:
	.string "POKéMON can hold\n"
	.string "items like POTION\l"
	.string "and ANTIDOTE."
	.string "\pBut they don't\n"
	.string "appear to know how"
	.string "\pto use manmade\n"
	.string "items.$"
