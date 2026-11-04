OaksLab_Johto_MapScripts::
	.byte 0

OaksLab_Johto_Oak_Entry::
	lockall
	goto OaksLab_Johto_Oak

OaksLab_Johto_OaksAssistant1Script_Entry::
	lockall
	goto OaksLab_Johto_OaksAssistant1Script

OaksLab_Johto_OaksAssistant2Script_Entry::
	lockall
	goto OaksLab_Johto_OaksAssistant2Script

OaksLab_Johto_OaksAssistant3Script_Entry::
	lockall
	goto OaksLab_Johto_OaksAssistant3Script

OaksLab_Johto_OaksLabBookshelf_Entry::
	lockall
	goto OaksLab_Johto_OaksLabBookshelf

OaksLab_Johto_OaksLabPoster1_Entry::
	lockall
	goto OaksLab_Johto_OaksLabPoster1

OaksLab_Johto_OaksLabPoster2_Entry::
	lockall
	goto OaksLab_Johto_OaksLabPoster2

OaksLab_Johto_OaksLabTrashcan_Entry::
	lockall
	goto OaksLab_Johto_OaksLabTrashcan

OaksLab_Johto_OaksLabPC_Entry::
	lockall
	goto OaksLab_Johto_OaksLabPC


OaksLab_Johto_Oak:
	faceplayer
	goto_if_set FLAG_JOHTO_OPENED_MT_SILVER, OaksLab_Johto_Oak_CheckPokedex
	goto_if_set FLAG_JOHTO_TALKED_TO_OAK_IN_KANTO, OaksLab_Johto_Oak_CheckBadges
	message OaksLab_Johto_OakWelcomeKantoText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_TALKED_TO_OAK_IN_KANTO

OaksLab_Johto_Oak_CheckBadges:
	special JohtoCountBadges
	@ TODO unsupported: ifequal NUM_BADGES, .OpenMtSilver
	goto Johto_EventScript_Unimplemented

OaksLab_Johto_Oak_CheckPokedex:
	message OaksLab_Johto_OakLabDexCheckText
	waitmessage
	waitbuttonpress
	@ TODO unsupported: special ProfOaksPCBoot
	goto Johto_EventScript_Unimplemented

OaksLab_Johto_OaksAssistant1Script:
	faceplayer
	message OaksLab_Johto_OaksAssistant1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksAssistant2Script:
	faceplayer
	message OaksLab_Johto_OaksAssistant2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksAssistant3Script:
	faceplayer
	message OaksLab_Johto_OaksAssistant3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksLabBookshelf:
	goto Johto_Std_DifficultBookshelfScript

OaksLab_Johto_OaksLabPoster1:
	message OaksLab_Johto_OaksLabPoster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksLabPoster2:
	message OaksLab_Johto_OaksLabPoster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksLabTrashcan:
	message OaksLab_Johto_OaksLabTrashcanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OaksLabPC:
	message OaksLab_Johto_OaksLabPCText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OaksLab_Johto_OakWelcomeKantoText:
	.string "OAK: Ah, {PLAYER}!\n"
	.string "It's good of you"
	.string "\pto come all this\n"
	.string "way to KANTO."
	.string "\pWhat do you think\n"
	.string "of the trainers"
	.string "\pout here?\n"
	.string "Pretty tough, huh?$"

OaksLab_Johto_OakLabDexCheckText:
	.string "How is your POKé-\n"
	.string "DEX coming?"
	.string "\pLet's see…$"

OaksLab_Johto_OaksAssistant1Text:
	.string "The PROF's POKéMON\n"
	.string "TALK radio program"
	.string "\pisn't aired here\n"
	.string "in KANTO."
	.string "\pIt's a shame--I'd\n"
	.string "like to hear it.$"

OaksLab_Johto_OaksAssistant2Text:
	.string "Thanks to your\n"
	.string "work on the POKé-\l"
	.string "DEX, the PROF's"
	.string "\presearch is coming\n"
	.string "along great.$"

OaksLab_Johto_OaksAssistant3Text:
	.string "Don't tell anyone,\n"
	.string "but PROF.OAK'S"
	.string "\pPOKéMON TALK isn't\n"
	.string "a live broadcast.$"

OaksLab_Johto_OaksLabPoster1Text:
	.string "Press START to\n"
	.string "open the MENU.$"

OaksLab_Johto_OaksLabPoster2Text:
	.string "The SAVE option is\n"
	.string "on the MENU."
	.string "\pUse it in a timely\n"
	.string "manner.$"

OaksLab_Johto_OaksLabTrashcanText:
	.string "There's nothing in\n"
	.string "here…$"

OaksLab_Johto_OaksLabPCText:
	.string "There's an e-mail\n"
	.string "message on the PC."
	.string "\p…"
	.string "\pPROF.OAK, how is\n"
	.string "your research\l"
	.string "coming along?"
	.string "\pI'm still plugging\n"
	.string "away."
	.string "\pI heard rumors\n"
	.string "that {PLAYER} is"
	.string "\pgetting quite a\n"
	.string "reputation."
	.string "\pI'm delighted to\n"
	.string "hear that."
	.string "\pELM in NEW BARK\n"
	.string "TOWN 8-)$"
