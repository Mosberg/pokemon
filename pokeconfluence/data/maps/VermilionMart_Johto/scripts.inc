VermilionMart_Johto_MapScripts::
	.byte 0

VermilionMart_Johto_VermilionMartClerkScript_Entry::
	lockall
	goto VermilionMart_Johto_VermilionMartClerkScript

VermilionMart_Johto_VermilionMartSuperNerdScript_Entry::
	lockall
	goto VermilionMart_Johto_VermilionMartSuperNerdScript

VermilionMart_Johto_VermilionMartBeautyScript_Entry::
	lockall
	goto VermilionMart_Johto_VermilionMartBeautyScript


VermilionMart_Johto_VermilionMartClerkScript:
	pokemart Johto_Mart_VERMILION
	closemessage
	releaseall
	end

VermilionMart_Johto_VermilionMartSuperNerdScript:
	faceplayer
	message VermilionMart_Johto_VermilionMartSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionMart_Johto_VermilionMartBeautyScript:
	faceplayer
	message VermilionMart_Johto_VermilionMartBeautyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionMart_Johto_VermilionMartSuperNerdText:
	.string "TEAM ROCKET is no\n"
	.string "longer in KANTO."
	.string "\pThat alone makes\n"
	.string "me happy.$"

VermilionMart_Johto_VermilionMartBeautyText:
	.string "I'm thinking about\n"
	.string "going shopping in\l"
	.string "SAFFRON.$"
