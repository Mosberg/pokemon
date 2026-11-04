OlivineMart_Johto_MapScripts::
	.byte 0

OlivineMart_Johto_OlivineMartClerkScript_Entry::
	lockall
	goto OlivineMart_Johto_OlivineMartClerkScript

OlivineMart_Johto_OlivineMartCooltrainerFScript_Entry::
	lockall
	goto OlivineMart_Johto_OlivineMartCooltrainerFScript

OlivineMart_Johto_OlivineMartLassScript_Entry::
	lockall
	goto OlivineMart_Johto_OlivineMartLassScript


OlivineMart_Johto_OlivineMartClerkScript:
	pokemart Johto_Mart_OLIVINE
	closemessage
	releaseall
	end

OlivineMart_Johto_OlivineMartCooltrainerFScript:
	faceplayer
	message OlivineMart_Johto_OlivineMartCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineMart_Johto_OlivineMartLassScript:
	faceplayer
	message OlivineMart_Johto_OlivineMartLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineMart_Johto_OlivineMartCooltrainerFText:
	.string "Do your POKéMON\n"
	.string "already know the"
	.string "\pmove for carrying\n"
	.string "people on water?$"

OlivineMart_Johto_OlivineMartLassText:
	.string "My BUTTERFREE came\n"
	.string "from my boyfriend\l"
	.string "overseas."
	.string "\pIt carried some\n"
	.string "MAIL from him."
	.string "\pWant to know what\n"
	.string "it says?"
	.string "\pLet's see… Nope!\n"
	.string "It's a secret!$"
