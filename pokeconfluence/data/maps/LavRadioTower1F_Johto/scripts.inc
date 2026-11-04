LavRadioTower1F_Johto_MapScripts::
	.byte 0

LavRadioTower1F_Johto_LavRadioTower1FReceptionistScript_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FReceptionistScript

LavRadioTower1F_Johto_LavRadioTower1FOfficerScript_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FOfficerScript

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd1Script_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FSuperNerd1Script

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Script_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Script

LavRadioTower1F_Johto_LavRadioTower1FDirectory_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FDirectory

LavRadioTower1F_Johto_LavRadioTower1FPokeFluteSign_Entry::
	lockall
	goto LavRadioTower1F_Johto_LavRadioTower1FPokeFluteSign


LavRadioTower1F_Johto_LavRadioTower1FReceptionistScript:
	faceplayer
	message LavRadioTower1F_Johto_LavRadioTower1FReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FOfficerScript:
	faceplayer
	message LavRadioTower1F_Johto_LavRadioTower1FOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd1Script:
	faceplayer
	message LavRadioTower1F_Johto_LavRadioTower1FSuperNerd1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_EXPN_CARD, LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_GotExpnCard
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_ReturnedMachinePart
	message LavRadioTower1F_Johto_LavRadioTower1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_ReturnedMachinePart:
	message LavRadioTower1F_Johto_LavRadioTower1FGentlemanText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_expncardname
	call LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_receiveitem_Sub
	setflag FLAG_JOHTO_ENGINE_EXPN_CARD

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_GotExpnCard:
	message LavRadioTower1F_Johto_LavRadioTower1FGentlemanText_GotExpnCard
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_EXPN_CARD, LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Script_GotExpnCard
	message LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Script_GotExpnCard:
	message LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Text_GotExpnCard
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FDirectory:
	message LavRadioTower1F_Johto_LavRadioTower1FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FPokeFluteSign:
	message LavRadioTower1F_Johto_LavRadioTower1FPokeFluteSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_receiveitem_Sub:
	goto Johto_Std_ReceiveItemScript_Sub

LavRadioTower1F_Johto_LavRadioTower1FGentlemanScript_expncardname:
	.string "EXPN CARD$"

LavRadioTower1F_Johto_LavRadioTower1FReceptionistText:
	.string "Welcome!\n"
	.string "Feel free to look"
	.string "\paround anywhere on\n"
	.string "this floor.$"

LavRadioTower1F_Johto_LavRadioTower1FOfficerText:
	.string "Sorry, but you can\n"
	.string "only tour the\l"
	.string "ground floor."
	.string "\pEver since JOHTO's\n"
	.string "RADIO TOWER was"
	.string "\ptaken over by a\n"
	.string "criminal gang, we"
	.string "\phave had to step\n"
	.string "up our security.$"

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd1Text:
	.string "Many people are\n"
	.string "hard at work here"
	.string "\pin the RADIO\n"
	.string "TOWER."
	.string "\pThey must be doing\n"
	.string "their best to put\l"
	.string "on good shows.$"

LavRadioTower1F_Johto_LavRadioTower1FGentlemanText:
	.string "Oh, no, no, no!"
	.string "\pWe've been off the\n"
	.string "air ever since the"
	.string "\pPOWER PLANT shut\n"
	.string "down."
	.string "\pAll my efforts to\n"
	.string "start this station"
	.string "\pwould be wasted if\n"
	.string "I can't broadcast."
	.string "\pI'll be ruined!$"

LavRadioTower1F_Johto_LavRadioTower1FGentlemanText_ReturnedMachinePart:
	.string "Ah! So you're the\n"
	.string "{PLAYER} who solved"
	.string "\pthe POWER PLANT's\n"
	.string "problem?"
	.string "\pThanks to you, I\n"
	.string "never lost my job."
	.string "\pI tell you, you're\n"
	.string "a real lifesaver!"
	.string "\pPlease take this\n"
	.string "as my thanks.$"

LavRadioTower1F_Johto_LavRadioTower1FGentlemanText_GotExpnCard:
	.string "With that thing,\n"
	.string "you can tune into"
	.string "\pthe radio programs\n"
	.string "here in KANTO."
	.string "\pGahahahaha!$"

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Text:
	.string "Hey there!"
	.string "\pI am the super\n"
	.string "MUSIC DIRECTOR!"
	.string "\pHuh? Your POKéGEAR\n"
	.string "can't tune into my"
	.string "\pmusic programs.\n"
	.string "How unfortunate!"
	.string "\pIf you get an EXPN\n"
	.string "CARD upgrade, you"
	.string "\pcan tune in. You'd\n"
	.string "better get one!$"

LavRadioTower1F_Johto_LavRadioTower1FSuperNerd2Text_GotExpnCard:
	.string "Hey there!"
	.string "\pI am the super\n"
	.string "MUSIC DIRECTOR!"
	.string "\pI'm responsible\n"
	.string "for the gorgeous"
	.string "\pmelodies that go\n"
	.string "out over the air."
	.string "\pDon't be square.\n"
	.string "Grab your music\l"
	.string "off the air!$"

LavRadioTower1F_Johto_LavRadioTower1FDirectoryText:
	.string "1F RECEPTION\n"
	.string "2F SALES"
	.string "\p3F PERSONNEL\n"
	.string "4F PRODUCTION"
	.string "\p5F DIRECTOR'S\n"
	.string "   OFFICE$"

LavRadioTower1F_Johto_LavRadioTower1FPokeFluteSignText:
	.string "Perk Up POKéMON\n"
	.string "with Mellow Sounds"
	.string "\pof the POKé FLUTE\n"
	.string "on CHANNEL 20$"
