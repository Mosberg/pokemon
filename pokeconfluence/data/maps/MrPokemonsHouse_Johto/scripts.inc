MrPokemonsHouse_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonsHouse_Johto_OnFrame
	.byte 0

MrPokemonsHouse_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_MR_POKEMONS_HOUSE, 0, MrPokemonsHouse_Johto_MrPokemonsHouseMrPokemonEventScript_Entry
	.2byte 0

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_Entry::
	lockall
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript

MrPokemonsHouse_Johto_MrPokemonsHouse_ForeignMagazines_Entry::
	lockall
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_ForeignMagazines

MrPokemonsHouse_Johto_MrPokemonsHouse_BrokenComputer_Entry::
	lockall
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_BrokenComputer

MrPokemonsHouse_Johto_MrPokemonsHouse_StrangeCoins_Entry::
	lockall
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_StrangeCoins

MrPokemonsHouse_Johto_MrPokemonsHouseMrPokemonEventScript_Entry::
	lockall
	goto MrPokemonsHouse_Johto_MrPokemonsHouseMrPokemonEventScript


MrPokemonsHouse_Johto_MrPokemonsHouseMrPokemonEventScript:
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	message MrPokemonsHouse_Johto_MrPokemonIntroText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonsHouse_Johto_MrPokemonsHouse_PlayerWalksToMrPokemon
	waitmovement OBJ_EVENT_ID_PLAYER
	message MrPokemonsHouse_Johto_MrPokemonIntroText2
	waitmessage
	waitbuttonpress
	waitse
	additem ITEM_MYSTERY_EGG
	message MrPokemonsHouse_Johto_MrPokemonsHouse_GotEggText
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	setflag FLAG_JOHTO_GOT_MYSTERY_EGG_FROM_MR_POKEMON
	setrespawn HEAL_LOCATION_JOHTO_CHERRYGROVE_CITY
	message MrPokemonsHouse_Johto_MrPokemonIntroText3
	waitmessage
	waitbuttonpress
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	message MrPokemonsHouse_Johto_MrPokemonIntroText4
	waitmessage
	waitbuttonpress
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	message MrPokemonsHouse_Johto_MrPokemonIntroText5
	waitmessage
	waitbuttonpress
	closemessage
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript:
	faceplayer
	checkitem ITEM_RED_SCALE, 1
	goto_if_ne VAR_RESULT, 0, MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_RedScale
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries
	message MrPokemonsHouse_Johto_MrPokemonText_ImDependingOnYou
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries:
	message MrPokemonsHouse_Johto_MrPokemonText_AlwaysNewDiscoveries
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_RedScale:
	message MrPokemonsHouse_Johto_MrPokemonText_GimmeTheScale
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_refused
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, 0, MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_full
	setflag FLAG_EXP_SHARE_ENABLED
	removeitem ITEM_RED_SCALE
	goto MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_refused:
	message MrPokemonsHouse_Johto_MrPokemonText_Disappointed
	waitmessage
	waitbuttonpress

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonScript_full:
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript:
	playbgm MUS_DUMMY, FALSE
	applymovement 2, MrPokemonsHouse_Johto_MrPokemonsHouse_OakWalksToPlayer
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message MrPokemonsHouse_Johto_MrPokemonsHouse_OakText1
	waitmessage
	waitbuttonpress
	waitse
	message MrPokemonsHouse_Johto_MrPokemonsHouse_GetDexText
	waitmessage
	playse SE_PIN
	waitse
	setflag FLAG_JOHTO_ENGINE_POKEDEX
	message MrPokemonsHouse_Johto_MrPokemonsHouse_OakText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 2, MrPokemonsHouse_Johto_MrPokemonsHouse_OakExits
	waitmovement 2
	playse SE_EXIT
	removeobject 2
	waitse
	fadedefaultbgm
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonHealText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	playbgm MUS_HEAL, FALSE
	special HealPlayerParty
	delay 60
	fadescreen FADE_FROM_BLACK
	fadedefaultbgm
	message MrPokemonsHouse_Johto_MrPokemonText_ImDependingOnYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_RIVAL_NEW_BARK_TOWN
	setflag FLAG_JOHTO_PLAYERS_HOUSE_1F_NEIGHBOR
	clearflag FLAG_JOHTO_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR
	setvar VAR_JOHTO_SCENE_MR_POKEMONS_HOUSE, 1
	setvar VAR_JOHTO_SCENE_CHERRYGROVE_CITY, 1
	setvar VAR_JOHTO_SCENE_ELMS_LAB, 3
	clearflag FLAG_JOHTO_COP_IN_ELMS_LAB
	goto_if_set FLAG_JOHTO_GOT_TOTODILE_FROM_ELM, MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript_RivalTakesChikorita
	goto_if_set FLAG_JOHTO_GOT_CHIKORITA_FROM_ELM, MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript_RivalTakesCyndaquil
	setflag FLAG_JOHTO_TOTODILE_POKEBALL_IN_ELMS_LAB
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript_RivalTakesChikorita:
	setflag FLAG_JOHTO_CHIKORITA_POKEBALL_IN_ELMS_LAB
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_OakScript_RivalTakesCyndaquil:
	setflag FLAG_JOHTO_CYNDAQUIL_POKEBALL_IN_ELMS_LAB
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_ForeignMagazines:
	message MrPokemonsHouse_Johto_MrPokemonsHouse_ForeignMagazinesText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_BrokenComputer:
	message MrPokemonsHouse_Johto_MrPokemonsHouse_BrokenComputerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_StrangeCoins:
	message MrPokemonsHouse_Johto_MrPokemonsHouse_StrangeCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrPokemonsHouse_Johto_MrPokemonsHouse_PlayerWalksToMrPokemon:
	walk_right
	walk_up
	step_end

MrPokemonsHouse_Johto_MrPokemonsHouse_OakWalksToPlayer:
	walk_down
	walk_left
	walk_left
	step_end

MrPokemonsHouse_Johto_MrPokemonsHouse_OakExits:
	walk_down
	walk_left
	face_down
	delay_8
	step_end

MrPokemonsHouse_Johto_MrPokemonIntroText1:
	.string "Hello, hello! You\n"
	.string "must be {PLAYER}."
	.string "\pPROF.ELM said that\n"
	.string "you would visit.$"

MrPokemonsHouse_Johto_MrPokemonIntroText2:
	.string "This is what I\n"
	.string "want PROF.ELM to\l"
	.string "examine.$"

MrPokemonsHouse_Johto_MrPokemonsHouse_GotEggText:
	.string "{PLAYER} received\n"
	.string "MYSTERY EGG.$"

MrPokemonsHouse_Johto_MrPokemonIntroText3:
	.string "I know a couple\n"
	.string "who run a POKéMON\l"
	.string "DAY-CARE service."
	.string "\pThey gave me that\n"
	.string "EGG."
	.string "\pI was intrigued,\n"
	.string "so I sent mail to\l"
	.string "PROF.ELM."
	.string "\pFor POKéMON evolu-\n"
	.string "tion, PROF.ELM is\l"
	.string "the authority.$"

MrPokemonsHouse_Johto_MrPokemonIntroText4:
	.string "Even PROF.OAK here\n"
	.string "recognizes that.$"

MrPokemonsHouse_Johto_MrPokemonIntroText5:
	.string "If my assumption\n"
	.string "is correct, PROF.\l"
	.string "ELM will know it.$"

MrPokemonsHouse_Johto_MrPokemonsHouse_MrPokemonHealText:
	.string "You are returning\n"
	.string "to PROF.ELM?"
	.string "\pHere. Your POKéMON\n"
	.string "should have some\l"
	.string "rest.$"

MrPokemonsHouse_Johto_MrPokemonText_ImDependingOnYou:
	.string "I'm depending on\n"
	.string "you!$"

MrPokemonsHouse_Johto_MrPokemonText_AlwaysNewDiscoveries:
	.string "Life is delight-\n"
	.string "ful! Always, new"
	.string "\pdiscoveries to be\n"
	.string "made!$"

MrPokemonsHouse_Johto_MrPokemonsHouse_OakText1:
	.string "OAK: Aha! So\n"
	.string "you're {PLAYER}!"
	.string "\pI'm OAK! A POKéMON\n"
	.string "researcher."
	.string "\pI was just visit-\n"
	.string "ing my old friend\l"
	.string "MR.POKéMON."
	.string "\pI heard you were\n"
	.string "running an errand"
	.string "\pfor PROF.ELM, so I\n"
	.string "waited here."
	.string "\pOh! What's this?\n"
	.string "A rare POKéMON!"
	.string "\pLet's see…"
	.string "\pHm, I see!"
	.string "\pI understand why\n"
	.string "PROF.ELM gave you"
	.string "\pa POKéMON for this\n"
	.string "errand."
	.string "\pTo researchers\n"
	.string "like PROF.ELM and"
	.string "\pI, POKéMON are our\n"
	.string "friends."
	.string "\pHe saw that you\n"
	.string "would treat your"
	.string "\pPOKéMON with love\n"
	.string "and care."
	.string "\p…Ah!"
	.string "\pYou seem to be\n"
	.string "dependable."
	.string "\pHow would you like\n"
	.string "to help me out?"
	.string "\pSee? This is the\n"
	.string "latest version of\l"
	.string "POKéDEX."
	.string "\pIt automatically\n"
	.string "records data on"
	.string "\pPOKéMON you've\n"
	.string "seen or caught."
	.string "\pIt's a hi-tech\n"
	.string "encyclopedia!$"

MrPokemonsHouse_Johto_MrPokemonsHouse_GetDexText:
	.string "{PLAYER} received\n"
	.string "POKéDEX!$"

MrPokemonsHouse_Johto_MrPokemonsHouse_OakText2:
	.string "Go meet many kinds\n"
	.string "of POKéMON and"
	.string "\pcomplete that\n"
	.string "POKéDEX!"
	.string "\pBut I've stayed\n"
	.string "too long."
	.string "\pI have to get to\n"
	.string "GOLDENROD for my\l"
	.string "usual radio show."
	.string "\p{PLAYER}, I'm\n"
	.string "counting on you!$"

MrPokemonsHouse_Johto_MrPokemonText_GimmeTheScale:
	.string "Hm? That SCALE!\n"
	.string "What's that?\l"
	.string "A red GYARADOS?"
	.string "\pThat's rare! \n"
	.string "I, I want it…"
	.string "\p{PLAYER}, would you\n"
	.string "care to trade it?"
	.string "\pI can offer this\n"
	.string "EXP.SHARE I got\l"
	.string "from PROF.OAK.$"

MrPokemonsHouse_Johto_MrPokemonText_Disappointed:
	.string "That's disappoint-\n"
	.string "ing. That happens\l"
	.string "to be very rare.$"

MrPokemonsHouse_Johto_MrPokemonsHouse_ForeignMagazinesText:
	.string "It's packed with\n"
	.string "foreign magazines."
	.string "\pCan't even read\n"
	.string "their titles…$"

MrPokemonsHouse_Johto_MrPokemonsHouse_BrokenComputerText:
	.string "It's a big com-\n"
	.string "puter. Hmm. It's\l"
	.string "broken.$"

MrPokemonsHouse_Johto_MrPokemonsHouse_StrangeCoinsText:
	.string "A whole pile of\n"
	.string "strange coins!"
	.string "\pMaybe they're from\n"
	.string "another country…$"
