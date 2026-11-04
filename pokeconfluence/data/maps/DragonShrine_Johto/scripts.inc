DragonShrine_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonShrine_Johto_OnFrame
	.byte 0

DragonShrine_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_DRAGON_SHRINE, 0, DragonShrine_Johto_DragonShrineTakeTestScript_Entry
	.2byte 0

DragonShrine_Johto_DragonShrineElder1Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder1Script

DragonShrine_Johto_DragonShrineElder2Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder2Script

DragonShrine_Johto_DragonShrineElder3Script_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineElder3Script

DragonShrine_Johto_DragonShrineTakeTestScript_Entry::
	lockall
	goto DragonShrine_Johto_DragonShrineTakeTestScript


DragonShrine_Johto_DragonShrineTakeTestScript:
	applymovement OBJ_EVENT_ID_PLAYER, DragonShrine_Johto_DragonShrinePlayerWalkInMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, DragonShrine_Johto_DragonShrineElderStepDownMovement
	waitmovement 1
	message DragonShrine_Johto_DragonShrineElderGreetingText
	waitmessage
	waitbuttonpress

DragonShrine_Johto_DragonShrineTakeTestScript_Question1:
	setflag FLAG_TEMP_12
	message DragonShrine_Johto_DragonShrineQuestion1Text
	waitmessage
	waitbuttonpress
	@ TODO unsupported: loadmenu DragonShrineQuestion1_MenuHeader
	goto Johto_EventScript_Unimplemented

DragonShrine_Johto_DragonShrineElder1Script:
	faceplayer
	goto_if_set FLAG_TEMP_11, DragonShrine_Johto_DragonShrineElder1Script_DontGiveDratiniYet
	goto_if_set FLAG_TEMP_17, DragonShrine_Johto_DragonShrineElder1Script_ReceivedDratini
	goto_if_unset FLAG_JOHTO_GOT_DRATINI, DragonShrine_Johto_DragonShrineElder1Script_GiveDratini
	goto_if_set FLAG_JOHTO_BEAT_RIVAL_IN_MT_MOON, DragonShrine_Johto_DragonShrineElder1Script_BeatRivalInMtMoon
	message DragonShrine_Johto_DragonShrineClairsGrandfatherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_GiveDratini:
	message DragonShrine_Johto_DragonShrineTakeThisDratiniText
	waitmessage
	waitbuttonpress
	getpartysize
	goto_if_eq VAR_RESULT, 6, DragonShrine_Johto_DragonShrineElder1Script_PartyFull
	message DragonShrine_Johto_DragonShrinePlayerReceivedDratiniText
	waitmessage
	playse SE_PIN
	waitse
	givemon SPECIES_DRATINI, 15
	@ TODO unsupported: special GiveDratini
	goto Johto_EventScript_Unimplemented

DragonShrine_Johto_DragonShrineElder1Script_PartyFull:
	message DragonShrine_Johto_DragonShrinePartyFullText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_BeatRivalInMtMoon:
	message DragonShrine_Johto_DragonShrineRivalIsInTrainingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_DontGiveDratiniYet:
	message DragonShrine_Johto_DragonShrineComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder1Script_ReceivedDratini:
	message DragonShrine_Johto_DragonShrineSymbolicDragonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder2Script:
	faceplayer
	message DragonShrine_Johto_DragonShrineElder2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrineElder3Script:
	faceplayer
	message DragonShrine_Johto_DragonShrineElder3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DragonShrine_Johto_DragonShrinePlayerWalkInMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

DragonShrine_Johto_DragonShrineElderStepDownMovement:
	walk_slow_down
	step_end

DragonShrine_Johto_DragonShrineElderGreetingText:
	.string "Hm… Good to see\n"
	.string "you here."
	.string "\pNo need to explain\n"
	.string "why you came."
	.string "\pCLAIR sent you\n"
	.string "here, didn't she?"
	.string "\pThat girl is a\n"
	.string "handful…"
	.string "\pI am sorry, but I\n"
	.string "must test you."
	.string "\pNot to worry, you\n"
	.string "are to answer only\l"
	.string "a few questions."
	.string "\pReady?$"

DragonShrine_Johto_DragonShrineQuestion1Text:
	.string "What are POKéMON\n"
	.string "to you?$"

DragonShrine_Johto_DragonShrineComeAgainText:
	.string "Come again, if you\n"
	.string "so desire.$"

DragonShrine_Johto_DragonShrineTakeThisDratiniText:
	.string "Hm… Good to see\n"
	.string "you here."
	.string "\pYour arrival is\n"
	.string "most fortunate."
	.string "\pI have something\n"
	.string "for you."
	.string "\pTake this DRATINI\n"
	.string "as proof that I"
	.string "\phave recognized\n"
	.string "your worth.$"

DragonShrine_Johto_DragonShrinePlayerReceivedDratiniText:
	.string "{PLAYER} received\n"
	.string "DRATINI!$"

DragonShrine_Johto_DragonShrinePartyFullText:
	.string "Hm? Your POKéMON\n"
	.string "party is full.$"

DragonShrine_Johto_DragonShrineSymbolicDragonText:
	.string "Dragon POKéMON are\n"
	.string "symbolic of our\l"
	.string "clan."
	.string "\pYou have shown\n"
	.string "that you can be"
	.string "\pentrusted with\n"
	.string "one.$"

DragonShrine_Johto_DragonShrineClairsGrandfatherText:
	.string "CLAIR appears to\n"
	.string "have learned an"
	.string "\pinvaluable lesson\n"
	.string "from you."
	.string "\pI thank you as her\n"
	.string "grandfather.$"

DragonShrine_Johto_DragonShrineRivalIsInTrainingText:
	.string "A boy close to\n"
	.string "your age is in\l"
	.string "training here."
	.string "\pHe is much like\n"
	.string "CLAIR when she was"
	.string "\pyounger. It is a\n"
	.string "little worrisome…$"

DragonShrine_Johto_DragonShrineElder2Text:
	.string "It's been quite\n"
	.string "some time since a"
	.string "\ptrainer has gained\n"
	.string "our MASTER's rare\l"
	.string "approval."
	.string "\pIn fact, not since\n"
	.string "Master LANCE.$"

DragonShrine_Johto_DragonShrineElder3Text:
	.string "You know young\n"
	.string "Master LANCE?"
	.string "\pHe looks so much\n"
	.string "like our MASTER\l"
	.string "did in his youth."
	.string "\pIt's in their\n"
	.string "blood.$"
