SilphCo1F_Johto_MapScripts::
	.byte 0

SilphCo1F_Johto_SilphCoReceptionistScript_Entry::
	lockall
	goto SilphCo1F_Johto_SilphCoReceptionistScript

SilphCo1F_Johto_SilphCoOfficerScript_Entry::
	lockall
	goto SilphCo1F_Johto_SilphCoOfficerScript


SilphCo1F_Johto_SilphCoReceptionistScript:
	faceplayer
	message SilphCo1F_Johto_SilphCoReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SilphCo1F_Johto_SilphCoOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_UP_GRADE, SilphCo1F_Johto_SilphCoOfficerScript_GotUpGrade
	message SilphCo1F_Johto_SilphCoOfficerText
	waitmessage
	waitbuttonpress
	giveitem ITEM_UP_GRADE
	goto_if_eq VAR_RESULT, 0, SilphCo1F_Johto_SilphCoOfficerScript_NoRoom
	setflag FLAG_JOHTO_GOT_UP_GRADE

SilphCo1F_Johto_SilphCoOfficerScript_GotUpGrade:
	message SilphCo1F_Johto_SilphCoOfficerText_GotUpGrade
	waitmessage
	waitbuttonpress

SilphCo1F_Johto_SilphCoOfficerScript_NoRoom:
	closemessage
	releaseall
	end

SilphCo1F_Johto_SilphCoReceptionistText:
	.string "Welcome. This is\n"
	.string "SILPH CO.'s HEAD\l"
	.string "OFFICE BUILDING.$"

SilphCo1F_Johto_SilphCoOfficerText:
	.string "Only employees are\n"
	.string "permitted to go\l"
	.string "upstairs."
	.string "\pBut since you came\n"
	.string "such a long way,"
	.string "\phave this neat\n"
	.string "little souvenir.$"

SilphCo1F_Johto_SilphCoOfficerText_GotUpGrade:
	.string "It's SILPH CO.'s\n"
	.string "latest product."
	.string "\pIt's not for sale\n"
	.string "anywhere yet.$"
