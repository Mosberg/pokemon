Route42_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route42_Johto_OnLoad
	.byte 0

Route42_Johto_Route42FruitTree1_Entry::
	lockall
	goto Route42_Johto_Route42FruitTree1

Route42_Johto_Route42FruitTree2_Entry::
	lockall
	goto Route42_Johto_Route42FruitTree2

Route42_Johto_Route42FruitTree3_Entry::
	lockall
	goto Route42_Johto_Route42FruitTree3

Route42_Johto_Route42UltraBall_Entry::
	lockall
	goto Route42_Johto_Route42UltraBall

Route42_Johto_Route42SuperPotion_Entry::
	lockall
	goto Route42_Johto_Route42SuperPotion

Route42_Johto_Route42Sign1_Entry::
	lockall
	goto Route42_Johto_Route42Sign1

Route42_Johto_MtMortarSign1_Entry::
	lockall
	goto Route42_Johto_MtMortarSign1

Route42_Johto_MtMortarSign2_Entry::
	lockall
	goto Route42_Johto_MtMortarSign2

Route42_Johto_Route42Sign2_Entry::
	lockall
	goto Route42_Johto_Route42Sign2

Route42_Johto_Route42SuicuneScript_Entry::
	lockall
	goto Route42_Johto_Route42SuicuneScript


Route42_Johto_Route42SuicuneScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	playse SE_WARP_OUT
	applymovement 9, Route42_Johto_Route42SuicuneMovement
	waitmovement 9
	removeobject 9
	delay 10
	setvar VAR_JOHTO_SCENE_ROUTE_42, 0
	clearflag FLAG_JOHTO_SAW_SUICUNE_ON_ROUTE_36
	setvar VAR_JOHTO_SCENE_ROUTE_36, 1
	releaseall
	end

Route42_Johto_TrainerFisherTully::
	trainerbattle_single TRAINER_JOHTO_FISHER_TULLY1, Route42_Johto_FisherTullySeenText, Route42_Johto_FisherTullyBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_TULLY
	lock
	faceplayer
	goto Route42_Johto_TrainerFisherTully_Script

Route42_Johto_TrainerFisherTully_Script:
	goto_if_set FLAG_JOHTO_ENGINE_TULLY_READY_FOR_REMATCH, Route42_Johto_TrainerFisherTully_WantsBattle
	goto_if_set FLAG_JOHTO_ENGINE_TULLY_HAS_WATER_STONE, Route42_Johto_TrainerFisherTully_HasWaterStone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route42_Johto_TrainerFisherTully_NumberAccepted
	goto_if_set FLAG_JOHTO_TULLY_ASKED_FOR_PHONE_NUMBER, Route42_Johto_TrainerFisherTully_AskedAlready
	message Route42_Johto_FisherTullyAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_TULLY_ASKED_FOR_PHONE_NUMBER
	call Route42_Johto_TrainerFisherTully_AskNumber1_Sub
	goto Route42_Johto_TrainerFisherTully_AskForNumber

Route42_Johto_TrainerFisherTully_AskedAlready:
	call Route42_Johto_TrainerFisherTully_AskNumber2_Sub

Route42_Johto_TrainerFisherTully_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route42_Johto_TrainerFisherTully_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route42_Johto_TrainerFisherTully_NumberDeclined
	call Route42_Johto_TrainerFisherTully_RegisteredNumber_Sub
	goto Route42_Johto_TrainerFisherTully_NumberAccepted

Route42_Johto_TrainerFisherTully_WantsBattle:
	call Route42_Johto_TrainerFisherTully_Rematch_Sub
	@ TODO unsupported: readmem wTullyFightCount
	goto Johto_EventScript_Unimplemented

Route42_Johto_TrainerFisherTully_HasWaterStone:
	call Route42_Johto_TrainerFisherTully_Gift_Sub
	giveitem ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, 0, Route42_Johto_TrainerFisherTully_NoRoom
	clearflag FLAG_JOHTO_ENGINE_TULLY_HAS_WATER_STONE
	setflag FLAG_JOHTO_TULLY_GAVE_WATER_STONE
	goto Route42_Johto_TrainerFisherTully_NumberAccepted

Route42_Johto_TrainerFisherTully_NoRoom:
	goto Route42_Johto_TrainerFisherTully_PackFull

Route42_Johto_TrainerFisherTully_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route42_Johto_TrainerFisherTully_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route42_Johto_TrainerFisherTully_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route42_Johto_TrainerFisherTully_PackFull:
	goto Johto_Std_PackFullMScript

Route42_Johto_TrainerPokemaniacShane::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_SHANE, Route42_Johto_PokemaniacShaneSeenText, Route42_Johto_PokemaniacShaneBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_SHANE
	lock
	faceplayer
	goto Route42_Johto_TrainerPokemaniacShane_Script

Route42_Johto_TrainerPokemaniacShane_Script:
	message Route42_Johto_PokemaniacShaneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_TrainerHikerBenjamin::
	trainerbattle_single TRAINER_JOHTO_HIKER_BENJAMIN, Route42_Johto_HikerBenjaminSeenText, Route42_Johto_HikerBenjaminBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_BENJAMIN
	lock
	faceplayer
	goto Route42_Johto_TrainerHikerBenjamin_Script

Route42_Johto_TrainerHikerBenjamin_Script:
	message Route42_Johto_HikerBenjaminAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_Route42Sign1:
	message Route42_Johto_Route42Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_MtMortarSign1:
	message Route42_Johto_MtMortarSign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_MtMortarSign2:
	message Route42_Johto_MtMortarSign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_Route42Sign2:
	message Route42_Johto_Route42Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42_Johto_Route42UltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

Route42_Johto_Route42SuperPotion:
	finditem ITEM_SUPER_POTION
	releaseall
	end

Route42_Johto_Route42FruitTree1:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_42_1, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PNK_APRICORN
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_42_1
	releaseall
	end

Route42_Johto_Route42FruitTree2:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_42_2, Johto_Std_FruitTreeEmpty
	giveitem ITEM_GRN_APRICORN
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_42_2
	releaseall
	end

Route42_Johto_Route42FruitTree3:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_42_3, Johto_Std_FruitTreeEmpty
	giveitem ITEM_YLW_APRICORN
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_42_3
	releaseall
	end

Route42_Johto_TrainerFisherTully_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route42_Johto_TrainerFisherTully_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route42_Johto_TrainerFisherTully_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route42_Johto_TrainerFisherTully_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route42_Johto_TrainerFisherTully_Gift_Sub:
	goto Johto_Std_GiftMScript_Sub

Route42_Johto_Route42SuicuneMovement:
	jump_up
	jump_up
	jump_up
	jump_right
	jump_right
	jump_right
	step_end

Route42_Johto_FisherTullySeenText:
	.string "Let me demonstrate\n"
	.string "the power of the\l"
	.string "POKéMON I caught!$"

Route42_Johto_FisherTullyBeatenText:
	.string "What? That's not\n"
	.string "right.$"

Route42_Johto_FisherTullyAfterBattleText:
	.string "I want to become\n"
	.string "the trainer CHAMP"
	.string "\pusing the POKéMON\n"
	.string "I caught."
	.string "\pThat's the best\n"
	.string "part of fishing!$"

Route42_Johto_HikerBenjaminSeenText:
	.string "Ah, it's good to\n"
	.string "be outside!\l"
	.string "I feel so free!$"

Route42_Johto_HikerBenjaminBeatenText:
	.string "Gahahah!$"

Route42_Johto_HikerBenjaminAfterBattleText:
	.string "Losing feels in-\n"
	.string "significant if you"
	.string "\plook up at the big\n"
	.string "sky!$"

Route42_Johto_PokemaniacShaneSeenText:
	.string "HEY!"
	.string "\pThis is my secret\n"
	.string "place! Get lost,\l"
	.string "you outsider!$"

Route42_Johto_PokemaniacShaneBeatenText:
	.string "I should have used\n"
	.string "my MOON STONE…$"

Route42_Johto_PokemaniacShaneAfterBattleText:
	.string "You're working on\n"
	.string "a POKéDEX?"
	.string "\pWow, you must know\n"
	.string "some pretty rare\l"
	.string "POKéMON!"
	.string "\pMay I please see\n"
	.string "it. Please?$"

Route42_Johto_Route42Sign1Text:
	.string "ROUTE 42"
	.string "\pECRUTEAK CITY -\n"
	.string "MAHOGANY TOWN$"

Route42_Johto_MtMortarSign1Text:
	.string "MT.MORTAR"
	.string "\pWATERFALL CAVE\n"
	.string "INSIDE$"

Route42_Johto_MtMortarSign2Text:
	.string "MT.MORTAR"
	.string "\pWATERFALL CAVE\n"
	.string "INSIDE$"

Route42_Johto_Route42Sign2Text:
	.string "ROUTE 42"
	.string "\pECRUTEAK CITY -\n"
	.string "MAHOGANY TOWN$"

Route42_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_42_0, Route42_Johto_CutTree0_Keep
	setmetatile 24, 12, 514, 0
	setmetatile 25, 12, 514, 0
	setmetatile 24, 13, 514, 0
	setmetatile 25, 13, 591, 0
Route42_Johto_CutTree0_Keep:
	end

Route42_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route42_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_42_0
	setmetatile 24, 12, 514, 0
	setmetatile 25, 12, 514, 0
	setmetatile 24, 13, 514, 0
	setmetatile 25, 13, 591, 0
	special DrawWholeMapView
Route42_Johto_CutTree0_Done:
	releaseall
	end
