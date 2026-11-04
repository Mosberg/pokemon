CeruleanMart_Johto_MapScripts::
	.byte 0

CeruleanMart_Johto_CeruleanMart_Clerk_Entry::
	lockall
	goto CeruleanMart_Johto_CeruleanMart_Clerk

CeruleanMart_Johto_CeruleanMart_CooltrainerM_Entry::
	lockall
	goto CeruleanMart_Johto_CeruleanMart_CooltrainerM

CeruleanMart_Johto_CeruleanMart_CooltrainerF_Entry::
	lockall
	goto CeruleanMart_Johto_CeruleanMart_CooltrainerF


CeruleanMart_Johto_CeruleanMart_Clerk:
	pokemart Johto_Mart_CERULEAN
	closemessage
	releaseall
	end

CeruleanMart_Johto_CeruleanMart_CooltrainerM:
	faceplayer
	message CeruleanMart_Johto_CeruleanMart_CooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanMart_Johto_CeruleanMart_CooltrainerF:
	faceplayer
	message CeruleanMart_Johto_CeruleanMart_CooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanMart_Johto_CeruleanMart_CooltrainerMText:
	.string "You'll run into\n"
	.string "many trainers on"
	.string "\pthe way to CERU-\n"
	.string "LEAN's CAPE."
	.string "\pThey want to see\n"
	.string "how they stack"
	.string "\pup against other\n"
	.string "trainers.$"

CeruleanMart_Johto_CeruleanMart_CooltrainerFText:
	.string "MISTY is about the\n"
	.string "only person in"
	.string "\ptown who can beat\n"
	.string "the trainers at\l"
	.string "CERULEAN's CAPE.$"
