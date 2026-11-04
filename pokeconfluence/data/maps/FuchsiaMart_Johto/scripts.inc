FuchsiaMart_Johto_MapScripts::
	.byte 0

FuchsiaMart_Johto_FuchsiaMartClerkScript_Entry::
	lockall
	goto FuchsiaMart_Johto_FuchsiaMartClerkScript

FuchsiaMart_Johto_FuchsiaMartFisherScript_Entry::
	lockall
	goto FuchsiaMart_Johto_FuchsiaMartFisherScript

FuchsiaMart_Johto_FuchsiaMartCooltrainerFScript_Entry::
	lockall
	goto FuchsiaMart_Johto_FuchsiaMartCooltrainerFScript


FuchsiaMart_Johto_FuchsiaMartClerkScript:
	pokemart Johto_Mart_FUCHSIA
	closemessage
	releaseall
	end

FuchsiaMart_Johto_FuchsiaMartFisherScript:
	faceplayer
	message FuchsiaMart_Johto_FuchsiaMartFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaMart_Johto_FuchsiaMartCooltrainerFScript:
	faceplayer
	message FuchsiaMart_Johto_FuchsiaMartCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaMart_Johto_FuchsiaMartFisherText:
	.string "I was hoping to\n"
	.string "buy some SAFARI"
	.string "\pZONE souvenirs,\n"
	.string "but it's closed…$"

FuchsiaMart_Johto_FuchsiaMartCooltrainerFText:
	.string "The SAFARI ZONE\n"
	.string "WARDEN's grand-\l"
	.string "daughter lives in\l"
	.string "town.$"
