Route33_Johto_MapScripts::
	.byte 0

Route33_Johto_Route33LassScript_Entry::
	lockall
	goto Route33_Johto_Route33LassScript

Route33_Johto_Route33FruitTree_Entry::
	lockall
	goto Route33_Johto_Route33FruitTree

Route33_Johto_Route33Sign_Entry::
	lockall
	goto Route33_Johto_Route33Sign


Route33_Johto_Route33LassScript:
	faceplayer
	message Route33_Johto_Route33LassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route33_Johto_TrainerHikerAnthony::
	trainerbattle_single TRAINER_JOHTO_HIKER_ANTHONY2, Route33_Johto_HikerAnthony2SeenText, Route33_Johto_HikerAnthony2BeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_ANTHONY
	lock
	faceplayer
	goto Route33_Johto_TrainerHikerAnthony_Script

Route33_Johto_TrainerHikerAnthony_Script:
	setvar VAR_0x8007, 628
	goto_if_set FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH, Route33_Johto_TrainerHikerAnthony_Rematch
	goto_if_set FLAG_JOHTO_ENGINE_DUNSPARCE_SWARM, Route33_Johto_TrainerHikerAnthony_Swarm
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_HIKER_ANTHONY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route33_Johto_TrainerHikerAnthony_NumberAccepted
	goto_if_set FLAG_JOHTO_ANTHONY_ASKED_FOR_PHONE_NUMBER, Route33_Johto_TrainerHikerAnthony_AskAgain
	message Route33_Johto_HikerAnthony2AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_ANTHONY_ASKED_FOR_PHONE_NUMBER
	call Route33_Johto_TrainerHikerAnthony_AskNumber1_Sub
	goto Route33_Johto_TrainerHikerAnthony_AskForPhoneNumber

Route33_Johto_TrainerHikerAnthony_AskAgain:
	call Route33_Johto_TrainerHikerAnthony_AskNumber2_Sub

Route33_Johto_TrainerHikerAnthony_AskForPhoneNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_HIKER_ANTHONY_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route33_Johto_TrainerHikerAnthony_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route33_Johto_TrainerHikerAnthony_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_HIKER_ANTHONY2
	call Route33_Johto_TrainerHikerAnthony_RegisteredNumber_Sub
	goto Route33_Johto_TrainerHikerAnthony_NumberAccepted

Route33_Johto_TrainerHikerAnthony_Rematch:
	call Route33_Johto_TrainerHikerAnthony_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WANTHONYFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route33_Johto_TrainerHikerAnthony_Fight4
	goto_if_eq VAR_RESULT, 3, Route33_Johto_TrainerHikerAnthony_Fight3
	goto_if_eq VAR_RESULT, 2, Route33_Johto_TrainerHikerAnthony_Fight2
	goto_if_eq VAR_RESULT, 1, Route33_Johto_TrainerHikerAnthony_Fight1
	goto_if_eq VAR_RESULT, 0, Route33_Johto_TrainerHikerAnthony_LoadFight0

Route33_Johto_TrainerHikerAnthony_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route33_Johto_TrainerHikerAnthony_LoadFight4

Route33_Johto_TrainerHikerAnthony_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route33_Johto_TrainerHikerAnthony_LoadFight3

Route33_Johto_TrainerHikerAnthony_Fight2:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route33_Johto_TrainerHikerAnthony_LoadFight2

Route33_Johto_TrainerHikerAnthony_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_OLIVINE, Route33_Johto_TrainerHikerAnthony_LoadFight1

Route33_Johto_TrainerHikerAnthony_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_HIKER_ANTHONY2, Route33_Johto_HikerAnthony2BeatenText
	setvar VAR_JOHTO_MEM_WANTHONYFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_HIKER_ANTHONY1, Route33_Johto_HikerAnthony2BeatenText
	setvar VAR_JOHTO_MEM_WANTHONYFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_HIKER_ANTHONY3, Route33_Johto_HikerAnthony2BeatenText
	setvar VAR_JOHTO_MEM_WANTHONYFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_HIKER_ANTHONY4, Route33_Johto_HikerAnthony2BeatenText
	setvar VAR_JOHTO_MEM_WANTHONYFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_HIKER_ANTHONY5, Route33_Johto_HikerAnthony2BeatenText
	clearflag FLAG_JOHTO_ENGINE_ANTHONY_READY_FOR_REMATCH
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_Swarm:
	message Route33_Johto_HikerAnthonyDunsparceText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route33_Johto_TrainerHikerAnthony_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route33_Johto_TrainerHikerAnthony_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route33_Johto_Route33Sign:
	message Route33_Johto_Route33SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route33_Johto_Route33FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_33, Johto_Std_FruitTreeEmpty
	giveitem ITEM_PECHA_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_33
	releaseall
	end

Route33_Johto_TrainerHikerAnthony_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route33_Johto_TrainerHikerAnthony_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route33_Johto_TrainerHikerAnthony_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route33_Johto_TrainerHikerAnthony_RematchStd_Sub:
	goto Johto_Std_RematchMScript_Sub

Route33_Johto_HikerAnthony2SeenText:
	.string "I came through the\n"
	.string "tunnel, but I"
	.string "\pstill have plenty\n"
	.string "of energy left.$"

Route33_Johto_HikerAnthony2BeatenText:
	.string "Whoa! You've got\n"
	.string "more zip than me!$"

Route33_Johto_HikerAnthony2AfterText:
	.string "We HIKERS are at\n"
	.string "our best in the\l"
	.string "mountains.$"

Route33_Johto_HikerAnthonyDunsparceText:
	.string "Hey, did you get a\n"
	.string "DUNSPARCE?"
	.string "\pI caught one too."
	.string "\pTake a look at it\n"
	.string "in the light. It's\l"
	.string "got a funny face!$"

Route33_Johto_Route33LassText:
	.string "Pant, pant…"
	.string "\pI finally got\n"
	.string "through that cave."
	.string "\pIt was much bigger\n"
	.string "than I'd expected."
	.string "\pI got too tired to\n"
	.string "explore the whole"
	.string "\pthing, so I came\n"
	.string "outside.$"

Route33_Johto_Route33SignText:
	.string "ROUTE 33$"
