BillsHouse_Johto_MapScripts::
	.byte 0

BillsHouse_Johto_BillsGrandpa_Entry::
	lockall
	goto BillsHouse_Johto_BillsGrandpa


BillsHouse_Johto_BillsGrandpa:
	faceplayer
	goto_if_set FLAG_TEMP_11, BillsHouse_Johto_BillsGrandpa_JustShowedSomething
	goto_if_set FLAG_JOHTO_GOT_THUNDERSTONE_FROM_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_GotThunderstone
	goto_if_set FLAG_JOHTO_MET_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_MetGrandpa
	message BillsHouse_Johto_BillsGrandpaIntroText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_BILLS_GRANDPA

BillsHouse_Johto_BillsGrandpa_MetGrandpa:
	goto_if_set FLAG_JOHTO_SHOWED_PICHU_TO_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_ShowedPichu
	goto_if_set FLAG_JOHTO_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_ShowedGrowlitheVulpix
	goto_if_set FLAG_JOHTO_SHOWED_STARYU_TO_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_ShowedStaryu
	goto_if_set FLAG_JOHTO_SHOWED_ODDISH_TO_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_ShowedOddish
	goto_if_set FLAG_JOHTO_SHOWED_LICKITUNG_TO_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_ShowedLickitung
	message BillsHouse_Johto_BillsGrandpaLickitungText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_LICKITUNG
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_LICKITUNG, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_LICKITUNG_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedLickitung

BillsHouse_Johto_BillsGrandpa_GotEverstone:
	message BillsHouse_Johto_BillsGrandpaOddishText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_ODDISH
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_ODDISH, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_ODDISH_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedOddish

BillsHouse_Johto_BillsGrandpa_GotLeafStone:
	message BillsHouse_Johto_BillsGrandpaStaryuText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_STARYU
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_STARYU, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_STARYU_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedStaryu

BillsHouse_Johto_BillsGrandpa_GotWaterStone:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_AskVulpix
	message BillsHouse_Johto_BillsGrandpaGrowlitheText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_GROWLITHE
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_GROWLITHE, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedGrowlitheVulpix

BillsHouse_Johto_BillsGrandpa_AskVulpix:
	message BillsHouse_Johto_BillsGrandpaVulpixText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_VULPIX
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_VULPIX, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedGrowlitheVulpix

BillsHouse_Johto_BillsGrandpa_GotFireStone:
	message BillsHouse_Johto_BillsGrandpaPichuText
	waitmessage
	waitbuttonpress
	message BillsHouse_Johto_BillsGrandpaAskToSeeMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	call BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub
	setvar VAR_0x8004, SPECIES_PICHU
	special JohtoBillsGrandfather
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_SaidNo
	goto_if_ne VAR_RESULT, SPECIES_PICHU, BillsHouse_Johto_BillsGrandpa_WrongPokemon
	call BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub
	setflag FLAG_JOHTO_SHOWED_PICHU_TO_BILLS_GRANDPA
	goto BillsHouse_Johto_BillsGrandpa_ShowedPichu

BillsHouse_Johto_BillsGrandpa_ShowedLickitung:
	goto_if_set FLAG_JOHTO_GOT_EVERSTONE_FROM_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_GotEverstone
	call BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_BagFull
	setflag FLAG_JOHTO_GOT_EVERSTONE_FROM_BILLS_GRANDPA
	setflag FLAG_TEMP_11
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_ShowedOddish:
	goto_if_set FLAG_JOHTO_GOT_LEAF_STONE_FROM_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_GotLeafStone
	call BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub
	giveitem ITEM_LEAF_STONE
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_BagFull
	setflag FLAG_JOHTO_GOT_LEAF_STONE_FROM_BILLS_GRANDPA
	setflag FLAG_TEMP_11
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_ShowedStaryu:
	goto_if_set FLAG_JOHTO_GOT_WATER_STONE_FROM_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_GotWaterStone
	call BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub
	giveitem ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_BagFull
	setflag FLAG_JOHTO_GOT_WATER_STONE_FROM_BILLS_GRANDPA
	setflag FLAG_TEMP_11
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_ShowedGrowlitheVulpix:
	goto_if_set FLAG_JOHTO_GOT_FIRE_STONE_FROM_BILLS_GRANDPA, BillsHouse_Johto_BillsGrandpa_GotFireStone
	call BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub
	giveitem ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_BagFull
	setflag FLAG_JOHTO_GOT_FIRE_STONE_FROM_BILLS_GRANDPA
	setflag FLAG_TEMP_11
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_ShowedPichu:
	call BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub
	giveitem ITEM_THUNDERSTONE
	goto_if_eq VAR_RESULT, 0, BillsHouse_Johto_BillsGrandpa_BagFull
	setflag FLAG_JOHTO_GOT_THUNDERSTONE_FROM_BILLS_GRANDPA
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_SaidNo:
	message BillsHouse_Johto_BillsGrandpaYouDontHaveItTextText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_JustShowedSomething:
	message BillsHouse_Johto_BillsGrandpaComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_GotThunderstone:
	message BillsHouse_Johto_BillsGrandpaShownAllThePokemonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_WrongPokemon:
	message BillsHouse_Johto_BillsGrandpaWrongPokemonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_BagFull:
	closemessage
	releaseall
	end

BillsHouse_Johto_BillsGrandpa_ExcitedToSee_Sub:
	message BillsHouse_Johto_BillsGrandpaExcitedToSeeText
	waitmessage
	waitbuttonpress
	return

BillsHouse_Johto_BillsGrandpa_CorrectPokemon_Sub:
	message BillsHouse_Johto_BillsGrandpaShownPokemonText
	waitmessage
	waitbuttonpress
	return

BillsHouse_Johto_BillsGrandpa_ReceiveItem_Sub:
	message BillsHouse_Johto_BillsGrandpaTokenOfAppreciationText
	waitmessage
	waitbuttonpress
	return

BillsHouse_Johto_BillsGrandpaIntroText:
	.string "Hm? You know BILL?\n"
	.string "He's my grandson."
	.string "\pHe's in JOHTO. He\n"
	.string "does something"
	.string "\pwith PCs, so I'm\n"
	.string "house-sitting.$"

BillsHouse_Johto_BillsGrandpaAskToSeeMonText:
	.string "If you have that\n"
	.string "POKéMON, may I see\l"
	.string "it, please?$"

BillsHouse_Johto_BillsGrandpaExcitedToSeeText:
	.string "You will show me?\n"
	.string "How good of you!$"

BillsHouse_Johto_BillsGrandpaYouDontHaveItTextText:
	.string "You don't have it?\n"
	.string "That's too bad…$"

BillsHouse_Johto_BillsGrandpaShownPokemonText:
	.string "Ah, so that is\n"
	.string "{STR_VAR_1}?"
	.string "\pIsn't it cute!\n"
	.string "That's so kind of\l"
	.string "you.$"

BillsHouse_Johto_BillsGrandpaTokenOfAppreciationText:
	.string "Thanks!"
	.string "\pThis is a token of\n"
	.string "my appreciation.$"

BillsHouse_Johto_BillsGrandpaComeAgainText:
	.string "Come visit again\n"
	.string "sometime.$"

BillsHouse_Johto_BillsGrandpaShownAllThePokemonText:
	.string "Thanks for showing\n"
	.string "me so many cute\l"
	.string "POKéMON."
	.string "\pI really enjoyed\n"
	.string "myself. I'm glad"
	.string "\pI've lived such a\n"
	.string "long life.$"

BillsHouse_Johto_BillsGrandpaWrongPokemonText:
	.string "Hm?"
	.string "\pThat's not the\n"
	.string "POKéMON that I was\l"
	.string "told about.$"

BillsHouse_Johto_BillsGrandpaLickitungText:
	.string "My grandson BILL\n"
	.string "told me about a"
	.string "\pPOKéMON that has a\n"
	.string "long tongue.$"

BillsHouse_Johto_BillsGrandpaOddishText:
	.string "Ah, my grandson\n"
	.string "mentioned a round,"
	.string "\pgreen POKéMON that\n"
	.string "has leaves growing\l"
	.string "on its head.$"

BillsHouse_Johto_BillsGrandpaStaryuText:
	.string "Do you know of a\n"
	.string "sea POKéMON that"
	.string "\phas a red sphere\n"
	.string "in its body?"
	.string "\pYou know, the one\n"
	.string "that's shaped like\l"
	.string "a star?"
	.string "\pI heard that it\n"
	.string "appears at night."
	.string "\pI would surely\n"
	.string "like to see it.$"

BillsHouse_Johto_BillsGrandpaGrowlitheText:
	.string "BILL told me about\n"
	.string "a POKéMON that is"
	.string "\pvery loyal to its\n"
	.string "trainer."
	.string "\pIt's supposed to\n"
	.string "ROAR well.$"

BillsHouse_Johto_BillsGrandpaVulpixText:
	.string "I heard about a\n"
	.string "cute POKéMON that\l"
	.string "has six tails."
	.string "\pI would love to\n"
	.string "hug a cute POKéMON\l"
	.string "like that.$"

BillsHouse_Johto_BillsGrandpaPichuText:
	.string "Do you know that\n"
	.string "hugely popular\l"
	.string "POKéMON?"
	.string "\pThe POKéMON that\n"
	.string "has a yellow body\l"
	.string "and red cheeks."
	.string "\pI would love to\n"
	.string "see what it looks"
	.string "\plike before it\n"
	.string "evolves.$"
