PlayersHouse2F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PlayersHouse2F_Johto_OnTransition
	.byte 0

PlayersHouse2F_Johto_OnTransition:
	call PlayersHouse2F_Johto_PlayersHouse2FInitializeRoomCallback_Cb
	end

PlayersHouse2F_Johto_PlayersHouseGameConsoleScript_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseGameConsoleScript

PlayersHouse2F_Johto_PlayersHouseDoll1Script_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseDoll1Script

PlayersHouse2F_Johto_PlayersHouseDoll2Script_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseDoll2Script

PlayersHouse2F_Johto_PlayersHouseBigDollScript_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseBigDollScript

PlayersHouse2F_Johto_PlayersHousePCScript_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHousePCScript

PlayersHouse2F_Johto_PlayersHouseRadioScript_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseRadioScript

PlayersHouse2F_Johto_PlayersHouseBookshelfScript_Entry::
	lockall
	goto PlayersHouse2F_Johto_PlayersHouseBookshelfScript


PlayersHouse2F_Johto_PlayersHouseDoll1Script:
	@ TODO unsupported: describedecoration DECODESC_LEFT_DOLL
	goto Johto_EventScript_Unimplemented

PlayersHouse2F_Johto_PlayersHouseDoll2Script:
	@ TODO unsupported: describedecoration DECODESC_RIGHT_DOLL
	goto Johto_EventScript_Unimplemented

PlayersHouse2F_Johto_PlayersHouseBigDollScript:
	@ TODO unsupported: describedecoration DECODESC_BIG_DOLL
	goto Johto_EventScript_Unimplemented

PlayersHouse2F_Johto_PlayersHouseGameConsoleScript:
	@ TODO unsupported: describedecoration DECODESC_CONSOLE
	goto Johto_EventScript_Unimplemented

PlayersHouse2F_Johto_PlayersHouseRadioScript:
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, PlayersHouse2F_Johto_PlayersHouseRadioScript_NormalRadio
	goto_if_set FLAG_JOHTO_LISTENED_TO_INITIAL_RADIO, PlayersHouse2F_Johto_PlayersHouseRadioScript_AbbreviatedRadio
	playbgm MUS_RG_POKE_CENTER, FALSE
	message PlayersHouse2F_Johto_PlayersRadioText1
	waitmessage
	delay 45
	message PlayersHouse2F_Johto_PlayersRadioText2
	waitmessage
	delay 45
	message PlayersHouse2F_Johto_PlayersRadioText3
	waitmessage
	delay 45
	fadeoutbgm 4
	message PlayersHouse2F_Johto_PlayersRadioText4
	waitmessage
	delay 45
	closemessage
	setflag FLAG_JOHTO_LISTENED_TO_INITIAL_RADIO
	releaseall
	end

PlayersHouse2F_Johto_PlayersHouseRadioScript_NormalRadio:
	goto Johto_Std_Radio1Script

PlayersHouse2F_Johto_PlayersHouseRadioScript_AbbreviatedRadio:
	message PlayersHouse2F_Johto_PlayersRadioText4
	waitmessage
	delay 45
	closemessage
	releaseall
	end

PlayersHouse2F_Johto_PlayersHouseBookshelfScript:
	goto Johto_Std_PictureBookshelfScript

PlayersHouse2F_Johto_PlayersHousePCScript:
	goto_if_ne VAR_RESULT, 0, PlayersHouse2F_Johto_PlayersHousePCScript_Warp
	closemessage
	releaseall
	end

PlayersHouse2F_Johto_PlayersHousePCScript_Warp:
	@ TODO unsupported: warp NONE, 0, 0
	goto Johto_EventScript_Unimplemented

PlayersHouse2F_Johto_PlayersHouse2FInitializeRoomCallback_Cb:
	setflag FLAG_TEMP_18
	goto_if_set FLAG_JOHTO_INITIALIZED_EVENTS, PlayersHouse2F_Johto_PlayersHouse2FInitializeRoomCallback_SkipInitialization_Cb
	goto Johto_Std_InitializeEventsScript_Cb

PlayersHouse2F_Johto_PlayersHouse2FInitializeRoomCallback_SkipInitialization_Cb:
	return

PlayersHouse2F_Johto_PlayersRadioText1:
	.string "PROF.OAK'S POKéMON\n"
	.string "TALK! Please tune\l"
	.string "in next time!$"

PlayersHouse2F_Johto_PlayersRadioText2:
	.string "POKéMON CHANNEL!$"

PlayersHouse2F_Johto_PlayersRadioText3:
	.string "This is DJ MARY,\n"
	.string "your co-host!$"

PlayersHouse2F_Johto_PlayersRadioText4:
	.string "POKéMON!\n"
	.string "POKéMON CHANNEL…$"
