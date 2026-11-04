Route32Pokecenter1F_Johto_MapScripts::
	.byte 0

Route32Pokecenter1F_Johto_Route32Pokecenter1FNurseScript_Entry::
	lockall
	goto Route32Pokecenter1F_Johto_Route32Pokecenter1FNurseScript

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript_Entry::
	lockall
	goto Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript

Route32Pokecenter1F_Johto_Route32Pokecenter1FCooltrainerFScript_Entry::
	lockall
	goto Route32Pokecenter1F_Johto_Route32Pokecenter1FCooltrainerFScript


Route32Pokecenter1F_Johto_Route32Pokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_ROUTE_32
	goto Johto_Std_PokecenterNurseScript

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_OLD_ROD, Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript_GotOldRod
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_Question
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript_Refused
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_Yes
	waitmessage
	waitbuttonpress
	giveitem ITEM_OLD_ROD
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_GiveOldRod
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_GOT_OLD_ROD
	releaseall
	end

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript_Refused:
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_No
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruScript_GotOldRod:
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_After
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32Pokecenter1F_Johto_Route32Pokecenter1FCooltrainerFScript:
	faceplayer
	message Route32Pokecenter1F_Johto_Route32Pokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_Question:
	.string "This is a great\n"
	.string "fishing spot."
	.string "\pYou saw people\n"
	.string "fishing? How\l"
	.string "about you?"
	.string "\pWould you like one\n"
	.string "of my RODS?$"

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_Yes:
	.string "Heh, that's good\n"
	.string "to hear."
	.string "\pNow you're an\n"
	.string "angler too!$"

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_GiveOldRod:
	.string "Fishing is great!"
	.string "\pIf there's water,\n"
	.string "be it the sea or a"
	.string "\pstream, try out\n"
	.string "your ROD.$"

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_No:
	.string "Oh. That's rather\n"
	.string "disappointing…$"

Route32Pokecenter1F_Johto_Route32Pokecenter1FFishingGuruText_After:
	.string "Yo, kid. How are\n"
	.string "they biting?$"

Route32Pokecenter1F_Johto_Route32Pokecenter1FCooltrainerFText:
	.string "What should I make\n"
	.string "my POKéMON hold?"
	.string "\pMaybe an item that\n"
	.string "increases ATTACK\l"
	.string "power…$"
