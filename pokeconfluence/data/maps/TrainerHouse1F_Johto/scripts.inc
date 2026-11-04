TrainerHouse1F_Johto_MapScripts::
	.byte 0

TrainerHouse1F_Johto_TrainerHouse1FReceptionistScript_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouse1FReceptionistScript

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerMScript_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouse1FCooltrainerMScript

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerFScript_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouse1FCooltrainerFScript

TrainerHouse1F_Johto_TrainerHouse1FYoungsterScript_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouse1FYoungsterScript

TrainerHouse1F_Johto_TrainerHouse1FGentlemanScript_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouse1FGentlemanScript

TrainerHouse1F_Johto_TrainerHouseSign1_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouseSign1

TrainerHouse1F_Johto_TrainerHouseSign2_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouseSign2

TrainerHouse1F_Johto_TrainerHouseIllegibleBook_Entry::
	lockall
	goto TrainerHouse1F_Johto_TrainerHouseIllegibleBook


TrainerHouse1F_Johto_TrainerHouse1FReceptionistScript:
	faceplayer
	message TrainerHouse1F_Johto_TrainerHouse1FReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerMScript:
	faceplayer
	message TrainerHouse1F_Johto_TrainerHouse1FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerFScript:
	faceplayer
	message TrainerHouse1F_Johto_TrainerHouse1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouse1FYoungsterScript:
	faceplayer
	message TrainerHouse1F_Johto_TrainerHouse1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouse1FGentlemanScript:
	faceplayer
	message TrainerHouse1F_Johto_TrainerHouse1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouseSign1:
	message TrainerHouse1F_Johto_TrainerHouseSign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouseSign2:
	message TrainerHouse1F_Johto_TrainerHouseSign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouseIllegibleBook:
	message TrainerHouse1F_Johto_TrainerHouseIllegibleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TrainerHouse1F_Johto_TrainerHouse1FReceptionistText:
	.string "Welcome to TRAINER\n"
	.string "HOUSE, the newest"
	.string "\pand most happening\n"
	.string "place in VIRIDIAN."
	.string "\pWe're open to\n"
	.string "trainers only."
	.string "\pYou can battle\n"
	.string "against the best"
	.string "\pof the best right\n"
	.string "downstairs.$"

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerMText:
	.string "VIRIDIAN is the\n"
	.string "town closest to\l"
	.string "INDIGO PLATEAU."
	.string "\pThey built this\n"
	.string "place because so"
	.string "\pmany trainers pass\n"
	.string "through on their"
	.string "\pway up to INDIGO\n"
	.string "PLATEAU.$"

TrainerHouse1F_Johto_TrainerHouse1FCooltrainerFText:
	.string "They hold practice\n"
	.string "battles downstairs\l"
	.string "here."
	.string "\pI would love to\n"
	.string "see how well a"
	.string "\ptrainer from JOHTO\n"
	.string "battles.$"

TrainerHouse1F_Johto_TrainerHouse1FYoungsterText:
	.string "I guess you can't\n"
	.string "become the CHAMP"
	.string "\punless you go all\n"
	.string "over the place and"
	.string "\pbattle all kinds\n"
	.string "of people."
	.string "\pThe CHAMPION from\n"
	.string "PALLET traveled to"
	.string "\pall the cities and\n"
	.string "towns in KANTO.$"

TrainerHouse1F_Johto_TrainerHouse1FGentlemanText:
	.string "Whew… I'm taking a\n"
	.string "rest from POKéMON\l"
	.string "battles.$"

TrainerHouse1F_Johto_TrainerHouseSign1Text:
	.string "Practice battles\n"
	.string "are held in the"
	.string "\pTRAINING HALL\n"
	.string "downstairs."
	.string "\pSkilled trainers\n"
	.string "are invited to\l"
	.string "participate.$"

TrainerHouse1F_Johto_TrainerHouseSign2Text:
	.string "There are no rules\n"
	.string "or regulations for"
	.string "\ppractice matches.\n"
	.string "Just like in field"
	.string "\pbattles, anything\n"
	.string "goes!$"

TrainerHouse1F_Johto_TrainerHouseIllegibleText:
	.string "…What's this?\n"
	.string "A strategy memo?"
	.string "\pThis writing looks\n"
	.string "like ONIX tracks…"
	.string "\pIt's completely\n"
	.string "illegible…$"
