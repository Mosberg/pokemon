ViridianMart_Johto_MapScripts::
	.byte 0

ViridianMart_Johto_ViridianMartClerkScript_Entry::
	lockall
	goto ViridianMart_Johto_ViridianMartClerkScript

ViridianMart_Johto_ViridianMartLassScript_Entry::
	lockall
	goto ViridianMart_Johto_ViridianMartLassScript

ViridianMart_Johto_ViridianMartCooltrainerMScript_Entry::
	lockall
	goto ViridianMart_Johto_ViridianMartCooltrainerMScript


ViridianMart_Johto_ViridianMartClerkScript:
	pokemart Johto_Mart_VIRIDIAN
	closemessage
	releaseall
	end

ViridianMart_Johto_ViridianMartLassScript:
	faceplayer
	message ViridianMart_Johto_ViridianMartLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianMart_Johto_ViridianMartCooltrainerMScript:
	faceplayer
	message ViridianMart_Johto_ViridianMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianMart_Johto_ViridianMartLassText:
	.string "The GYM LEADER\n"
	.string "here is totally\l"
	.string "cool.$"

ViridianMart_Johto_ViridianMartCooltrainerMText:
	.string "Have you been to\n"
	.string "CINNABAR?"
	.string "\pIt's an island way\n"
	.string "south of here.$"
