PlayersNeighborsHouse_Johto_MapScripts::
	.byte 0

PlayersNeighborsHouse_Johto_PlayersNeighborsDaughterScript_Entry::
	lockall
	goto PlayersNeighborsHouse_Johto_PlayersNeighborsDaughterScript

PlayersNeighborsHouse_Johto_PlayersNeighborScript_Entry::
	lockall
	goto PlayersNeighborsHouse_Johto_PlayersNeighborScript

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseBookshelfScript_Entry::
	lockall
	goto PlayersNeighborsHouse_Johto_PlayersNeighborsHouseBookshelfScript

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript_Entry::
	lockall
	goto PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript


PlayersNeighborsHouse_Johto_PlayersNeighborsDaughterScript:
	faceplayer
	message PlayersNeighborsHouse_Johto_PlayersNeighborsDaughterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersNeighborsHouse_Johto_PlayersNeighborScript:
	faceplayer
	message PlayersNeighborsHouse_Johto_PlayersNeighborText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseBookshelfScript:
	goto Johto_Std_MagazineBookshelfScript

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript_NormalRadio
	goto_if_set FLAG_JOHTO_LISTENED_TO_INITIAL_RADIO, PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript_AbbreviatedRadio
	playbgm MUS_RG_POKE_CENTER, FALSE
	message PlayersNeighborsHouse_Johto_PlayerNeighborRadioText1
	waitmessage
	delay 45
	message PlayersNeighborsHouse_Johto_PlayerNeighborRadioText2
	waitmessage
	delay 45
	message PlayersNeighborsHouse_Johto_PlayerNeighborRadioText3
	waitmessage
	delay 45
	fadeoutbgm 4
	message PlayersNeighborsHouse_Johto_PlayerNeighborRadioText4
	waitmessage
	delay 45
	closemessage
	setflag FLAG_JOHTO_LISTENED_TO_INITIAL_RADIO
	releaseall
	end

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript_NormalRadio:
	goto Johto_Std_Radio1Script

PlayersNeighborsHouse_Johto_PlayersNeighborsHouseRadioScript_AbbreviatedRadio:
	message PlayersNeighborsHouse_Johto_PlayerNeighborRadioText4
	waitmessage
	delay 45
	closemessage
	releaseall
	end

PlayersNeighborsHouse_Johto_PlayersNeighborsDaughterText:
	.string "PIKACHU is an\n"
	.string "evolved POKéMON."
	.string "\pI was amazed by\n"
	.string "PROF.ELM's find-\l"
	.string "ings."
	.string "\pHe's so famous for\n"
	.string "his research on\l"
	.string "POKéMON evolution."
	.string "\p…sigh…"
	.string "\pI wish I could be\n"
	.string "a researcher like\l"
	.string "him…$"

PlayersNeighborsHouse_Johto_PlayersNeighborText:
	.string "My daughter is\n"
	.string "adamant about"
	.string "\pbecoming PROF.\n"
	.string "ELM's assistant."
	.string "\pShe really loves\n"
	.string "POKéMON!"
	.string "\pBut then, so do I!$"

PlayersNeighborsHouse_Johto_PlayerNeighborRadioText1:
	.string "PROF.OAK'S POKéMON\n"
	.string "TALK! Please tune\l"
	.string "in next time!$"

PlayersNeighborsHouse_Johto_PlayerNeighborRadioText2:
	.string "POKéMON CHANNEL!$"

PlayersNeighborsHouse_Johto_PlayerNeighborRadioText3:
	.string "This is DJ MARY,\n"
	.string "your co-host!$"

PlayersNeighborsHouse_Johto_PlayerNeighborRadioText4:
	.string "POKéMON!\n"
	.string "POKéMON CHANNEL…$"
