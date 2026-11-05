Route34_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route34_Johto_OnTransition
	.byte 0

Route34_Johto_OnTransition:
	call Route34_Johto_Route34EggCheckCallback_Cb
	end

Route34_Johto_OfficerKeithScript_Entry::
	lockall
	goto Route34_Johto_OfficerKeithScript

Route34_Johto_DayCareMon1Script_Entry::
	lockall
	goto Route34_Johto_DayCareMon1Script

Route34_Johto_DayCareMon2Script_Entry::
	lockall
	goto Route34_Johto_DayCareMon2Script

Route34_Johto_Route34Nugget_Entry::
	lockall
	goto Route34_Johto_Route34Nugget

Route34_Johto_Route34Sign_Entry::
	lockall
	goto Route34_Johto_Route34Sign

Route34_Johto_Route34TrainerTips_Entry::
	lockall
	goto Route34_Johto_Route34TrainerTips

Route34_Johto_DayCareSign_Entry::
	lockall
	goto Route34_Johto_DayCareSign


Route34_Johto_DayCareMon1Script:
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	releaseall
	end

Route34_Johto_DayCareMon2Script:
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	releaseall
	end

Route34_Johto_TrainerCamperTodd1::
	trainerbattle_single TRAINER_JOHTO_CAMPER_TODD1, Route34_Johto_CamperTodd1SeenText, Route34_Johto_CamperTodd1BeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_TODD
	lock
	faceplayer
	goto Route34_Johto_TrainerCamperTodd1_Script

Route34_Johto_TrainerCamperTodd1_Script:
	setvar VAR_0x8007, 503
	goto_if_set FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH, Route34_Johto_TrainerCamperTodd1_Rematch
	goto_if_set FLAG_JOHTO_ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON, Route34_Johto_TrainerCamperTodd1_SaleIsOn
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_CAMPER_TODD_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route34_Johto_TrainerCamperTodd1_NumberAccepted
	goto_if_set FLAG_JOHTO_TODD_ASKED_FOR_PHONE_NUMBER, Route34_Johto_TrainerCamperTodd1_AskAgain
	message Route34_Johto_CamperTodd1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_TODD_ASKED_FOR_PHONE_NUMBER
	call Route34_Johto_TrainerCamperTodd1_AskNumber_Sub
	goto Route34_Johto_TrainerCamperTodd1_FinishAsk

Route34_Johto_TrainerCamperTodd1_AskAgain:
	call Route34_Johto_TrainerCamperTodd1_AskNumber2_Sub

Route34_Johto_TrainerCamperTodd1_FinishAsk:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_CAMPER_TODD_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route34_Johto_TrainerCamperTodd1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route34_Johto_TrainerCamperTodd1_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_CAMPER_TODD1
	call Route34_Johto_TrainerCamperTodd1_RegisteredNumber_Sub
	goto Route34_Johto_TrainerCamperTodd1_NumberAccepted

Route34_Johto_TrainerCamperTodd1_Rematch:
	call Route34_Johto_TrainerCamperTodd1_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WTODDFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route34_Johto_TrainerCamperTodd1_Fight4
	goto_if_eq VAR_RESULT, 3, Route34_Johto_TrainerCamperTodd1_Fight3
	goto_if_eq VAR_RESULT, 2, Route34_Johto_TrainerCamperTodd1_Fight2
	goto_if_eq VAR_RESULT, 1, Route34_Johto_TrainerCamperTodd1_Fight1
	goto_if_eq VAR_RESULT, 0, Route34_Johto_TrainerCamperTodd1_LoadFight0

Route34_Johto_TrainerCamperTodd1_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route34_Johto_TrainerCamperTodd1_LoadFight4

Route34_Johto_TrainerCamperTodd1_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route34_Johto_TrainerCamperTodd1_LoadFight3

Route34_Johto_TrainerCamperTodd1_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_BLACKTHORN, Route34_Johto_TrainerCamperTodd1_LoadFight2

Route34_Johto_TrainerCamperTodd1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_CIANWOOD, Route34_Johto_TrainerCamperTodd1_LoadFight1

Route34_Johto_TrainerCamperTodd1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_TODD1, Route34_Johto_CamperTodd1BeatenText
	setvar VAR_JOHTO_MEM_WTODDFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_TODD2, Route34_Johto_CamperTodd1BeatenText
	setvar VAR_JOHTO_MEM_WTODDFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_TODD3, Route34_Johto_CamperTodd1BeatenText
	setvar VAR_JOHTO_MEM_WTODDFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_TODD4, Route34_Johto_CamperTodd1BeatenText
	setvar VAR_JOHTO_MEM_WTODDFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_TODD5, Route34_Johto_CamperTodd1BeatenText
	clearflag FLAG_JOHTO_ENGINE_TODD_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_SaleIsOn:
	message Route34_Johto_CamperToddSaleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route34_Johto_TrainerCamperTodd1_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route34_Johto_TrainerCamperTodd1_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route34_Johto_TrainerPicnickerGina1::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_GINA1, Route34_Johto_PicnickerGina1SeenText, Route34_Johto_PicnickerGina1BeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_GINA
	lock
	faceplayer
	goto Route34_Johto_TrainerPicnickerGina1_Script

Route34_Johto_TrainerPicnickerGina1_Script:
	setvar VAR_0x8007, 428
	goto_if_set FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH, Route34_Johto_TrainerPicnickerGina1_Rematch
	goto_if_set FLAG_JOHTO_ENGINE_GINA_HAS_LEAF_STONE, Route34_Johto_TrainerPicnickerGina1_LeafStone
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_GINA_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route34_Johto_TrainerPicnickerGina1_NumberAccepted
	goto_if_set FLAG_JOHTO_GINA_ASKED_FOR_PHONE_NUMBER, Route34_Johto_TrainerPicnickerGina1_AskAgain
	message Route34_Johto_PicnickerGina1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_GINA_ASKED_FOR_PHONE_NUMBER
	call Route34_Johto_TrainerPicnickerGina1_AskNumber1_Sub
	goto Route34_Johto_TrainerPicnickerGina1_FinishAsk

Route34_Johto_TrainerPicnickerGina1_AskAgain:
	call Route34_Johto_TrainerPicnickerGina1_AskNumber2_Sub

Route34_Johto_TrainerPicnickerGina1_FinishAsk:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_GINA_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_GINA_HAS_LEAF_STONE
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route34_Johto_TrainerPicnickerGina1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route34_Johto_TrainerPicnickerGina1_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_PICNICKER_GINA1
	call Route34_Johto_TrainerPicnickerGina1_RegisteredNumber_Sub
	goto Route34_Johto_TrainerPicnickerGina1_NumberAccepted

Route34_Johto_TrainerPicnickerGina1_Rematch:
	call Route34_Johto_TrainerPicnickerGina1_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WGINAFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route34_Johto_TrainerPicnickerGina1_Fight4
	goto_if_eq VAR_RESULT, 3, Route34_Johto_TrainerPicnickerGina1_Fight3
	goto_if_eq VAR_RESULT, 2, Route34_Johto_TrainerPicnickerGina1_Fight2
	goto_if_eq VAR_RESULT, 1, Route34_Johto_TrainerPicnickerGina1_Fight1
	goto_if_eq VAR_RESULT, 0, Route34_Johto_TrainerPicnickerGina1_LoadFight0

Route34_Johto_TrainerPicnickerGina1_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route34_Johto_TrainerPicnickerGina1_LoadFight4

Route34_Johto_TrainerPicnickerGina1_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route34_Johto_TrainerPicnickerGina1_LoadFight3

Route34_Johto_TrainerPicnickerGina1_Fight2:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route34_Johto_TrainerPicnickerGina1_LoadFight2

Route34_Johto_TrainerPicnickerGina1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_MAHOGANY, Route34_Johto_TrainerPicnickerGina1_LoadFight1

Route34_Johto_TrainerPicnickerGina1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_GINA1, Route34_Johto_PicnickerGina1BeatenText
	setvar VAR_JOHTO_MEM_WGINAFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerPicnickerGina1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_GINA2, Route34_Johto_PicnickerGina1BeatenText
	setvar VAR_JOHTO_MEM_WGINAFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerPicnickerGina1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_GINA3, Route34_Johto_PicnickerGina1BeatenText
	setvar VAR_JOHTO_MEM_WGINAFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerPicnickerGina1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_GINA4, Route34_Johto_PicnickerGina1BeatenText
	setvar VAR_JOHTO_MEM_WGINAFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerPicnickerGina1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_GINA5, Route34_Johto_PicnickerGina1BeatenText
	clearflag FLAG_JOHTO_ENGINE_GINA_READY_FOR_REMATCH
	releaseall
	end

Route34_Johto_TrainerPicnickerGina1_LeafStone:
	call Route34_Johto_TrainerPicnickerGina1_Gift_Sub
	giveitem ITEM_LEAF_STONE
	goto_if_eq VAR_RESULT, 0, Route34_Johto_TrainerPicnickerGina1_BagFull
	clearflag FLAG_JOHTO_ENGINE_GINA_HAS_LEAF_STONE
	setflag FLAG_JOHTO_GINA_GAVE_LEAF_STONE
	goto Route34_Johto_TrainerPicnickerGina1_NumberAccepted

Route34_Johto_TrainerPicnickerGina1_BagFull:
	goto Route34_Johto_TrainerPicnickerGina1_PackFull

Route34_Johto_TrainerPicnickerGina1_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route34_Johto_TrainerPicnickerGina1_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

Route34_Johto_TrainerPicnickerGina1_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route34_Johto_TrainerPicnickerGina1_PackFull:
	goto Johto_Std_PackFullFScript

Route34_Johto_OfficerKeithScript:
	faceplayer
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_eq VAR_RESULT, 0, Route34_Johto_OfficerKeithScript_NoFight
	goto_if_set FLAG_JOHTO_BEAT_OFFICER_KEITH, Route34_Johto_OfficerKeithScript_AfterScript
	playbgm MUS_DUMMY, FALSE
	message Route34_Johto_OfficerKeithSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_OFFICER_KEITH, Route34_Johto_OfficerKeithWinText
	setflag FLAG_JOHTO_BEAT_OFFICER_KEITH
	closemessage
	releaseall
	end

Route34_Johto_OfficerKeithScript_AfterScript:
	message Route34_Johto_OfficerKeithAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_OfficerKeithScript_NoFight:
	message Route34_Johto_OfficerKeithDaytimeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerYoungsterSamuel::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_SAMUEL, Route34_Johto_YoungsterSamuelSeenText, Route34_Johto_YoungsterSamuelBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_SAMUEL
	lock
	faceplayer
	goto Route34_Johto_TrainerYoungsterSamuel_Script

Route34_Johto_TrainerYoungsterSamuel_Script:
	message Route34_Johto_YoungsterSamuelAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerYoungsterIan::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_IAN, Route34_Johto_YoungsterIanSeenText, Route34_Johto_YoungsterIanBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_IAN
	lock
	faceplayer
	goto Route34_Johto_TrainerYoungsterIan_Script

Route34_Johto_TrainerYoungsterIan_Script:
	message Route34_Johto_YoungsterIanAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerPokefanmBrandon::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_BRANDON, Route34_Johto_PokefanmBrandonSeenText, Route34_Johto_PokefanmBrandonBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_BRANDON
	lock
	faceplayer
	goto Route34_Johto_TrainerPokefanmBrandon_Script

Route34_Johto_TrainerPokefanmBrandon_Script:
	message Route34_Johto_PokefanmBrandonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCooltrainerfIrene::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_IRENE, Route34_Johto_CooltrainerfIreneSeenText, Route34_Johto_CooltrainerfIreneBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_IRENE
	lock
	faceplayer
	goto Route34_Johto_TrainerCooltrainerfIrene_Script

Route34_Johto_TrainerCooltrainerfIrene_Script:
	goto_if_set FLAG_JOHTO_GOT_SOFT_SAND_FROM_KATE, Route34_Johto_TrainerCooltrainerfIrene_GotSoftSand
	message Route34_Johto_CooltrainerfIreneAfterText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCooltrainerfIrene_GotSoftSand:
	message Route34_Johto_CooltrainerfIreneAfterText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCooltrainerfJenn::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_JENN, Route34_Johto_CooltrainerfJennSeenText, Route34_Johto_CooltrainerfJennBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_JENN
	lock
	faceplayer
	goto Route34_Johto_TrainerCooltrainerfJenn_Script

Route34_Johto_TrainerCooltrainerfJenn_Script:
	goto_if_set FLAG_JOHTO_GOT_SOFT_SAND_FROM_KATE, Route34_Johto_TrainerCooltrainerfJenn_GotSoftSand
	message Route34_Johto_CooltrainerfJennAfterText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCooltrainerfJenn_GotSoftSand:
	message Route34_Johto_CooltrainerfJennAfterText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_TrainerCooltrainerfKate::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_KATE, Route34_Johto_CooltrainerfKateSeenText, Route34_Johto_CooltrainerfKateBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_KATE
	lock
	faceplayer
	goto Route34_Johto_TrainerCooltrainerfKate_Script

Route34_Johto_TrainerCooltrainerfKate_Script:
	goto_if_set FLAG_JOHTO_GOT_SOFT_SAND_FROM_KATE, Route34_Johto_TrainerCooltrainerfKate_GotSoftSand
	message Route34_Johto_CooltrainerfKateOfferSoftSandText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SOFT_SAND
	goto_if_eq VAR_RESULT, 0, Route34_Johto_TrainerCooltrainerfKate_BagFull
	setflag FLAG_JOHTO_GOT_SOFT_SAND_FROM_KATE

Route34_Johto_TrainerCooltrainerfKate_GotSoftSand:
	message Route34_Johto_CooltrainerfKateAfterText
	waitmessage
	waitbuttonpress

Route34_Johto_TrainerCooltrainerfKate_BagFull:
	closemessage
	releaseall
	end

Route34_Johto_Route34Sign:
	message Route34_Johto_Route34SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_Route34TrainerTips:
	message Route34_Johto_Route34TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_DayCareSign:
	message Route34_Johto_DayCareSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route34_Johto_Route34Nugget:
	finditem ITEM_NUGGET
	releaseall
	end

Route34_Johto_TrainerCamperTodd1_AskNumber_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route34_Johto_TrainerCamperTodd1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route34_Johto_TrainerCamperTodd1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route34_Johto_TrainerCamperTodd1_RematchStd_Sub:
	goto Johto_Std_RematchMScript_Sub

Route34_Johto_TrainerPicnickerGina1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route34_Johto_TrainerPicnickerGina1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route34_Johto_TrainerPicnickerGina1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route34_Johto_TrainerPicnickerGina1_RematchStd_Sub:
	goto Johto_Std_RematchFScript_Sub

Route34_Johto_TrainerPicnickerGina1_Gift_Sub:
	goto Johto_Std_GiftFScript_Sub

Route34_Johto_Route34EggCheckCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_DAY_CARE_MAN_HAS_EGG, Route34_Johto_Route34EggCheckCallback_PutDayCareManOutside_Cb
	clearflag FLAG_JOHTO_DAY_CARE_MAN_IN_DAY_CARE
	setflag FLAG_JOHTO_DAY_CARE_MAN_ON_ROUTE_34
	goto Route34_Johto_Route34EggCheckCallback_CheckMon1_Cb

Route34_Johto_Route34EggCheckCallback_PutDayCareManOutside_Cb:
	setflag FLAG_JOHTO_DAY_CARE_MAN_IN_DAY_CARE
	clearflag FLAG_JOHTO_DAY_CARE_MAN_ON_ROUTE_34
	goto Route34_Johto_Route34EggCheckCallback_CheckMon1_Cb

Route34_Johto_Route34EggCheckCallback_CheckMon1_Cb:
	goto_if_unset FLAG_JOHTO_ENGINE_DAY_CARE_MAN_HAS_MON, Route34_Johto_Route34EggCheckCallback_HideMon1_Cb
	clearflag FLAG_JOHTO_DAY_CARE_MON_1
	goto Route34_Johto_Route34EggCheckCallback_CheckMon2_Cb

Route34_Johto_Route34EggCheckCallback_HideMon1_Cb:
	setflag FLAG_JOHTO_DAY_CARE_MON_1
	goto Route34_Johto_Route34EggCheckCallback_CheckMon2_Cb

Route34_Johto_Route34EggCheckCallback_CheckMon2_Cb:
	goto_if_unset FLAG_JOHTO_ENGINE_DAY_CARE_LADY_HAS_MON, Route34_Johto_Route34EggCheckCallback_HideMon2_Cb
	clearflag FLAG_JOHTO_DAY_CARE_MON_2
	return

Route34_Johto_Route34EggCheckCallback_HideMon2_Cb:
	setflag FLAG_JOHTO_DAY_CARE_MON_2
	return

Route34_Johto_YoungsterSamuelSeenText:
	.string "This is where I do\n"
	.string "my training!$"

Route34_Johto_YoungsterSamuelBeatenText:
	.string "Beaten by a\n"
	.string "passing stranger!$"

Route34_Johto_YoungsterSamuelAfterText:
	.string "I'm going to train\n"
	.string "even harder."
	.string "\pAfter all, I'm\n"
	.string "trying to become\l"
	.string "a GYM LEADER.$"

Route34_Johto_YoungsterIanSeenText:
	.string "I'm the best in my\n"
	.string "class at POKéMON.$"

Route34_Johto_YoungsterIanBeatenText:
	.string "No! There are bet-\n"
	.string "ter trainers…$"

Route34_Johto_YoungsterIanAfterText:
	.string "I'm trying hard so\n"
	.string "I can be the star\l"
	.string "in my class.$"

Route34_Johto_CamperTodd1SeenText:
	.string "I'm confident in\n"
	.string "my ability to\l"
	.string "raise POKéMON."
	.string "\pWant to see?$"

Route34_Johto_CamperTodd1BeatenText:
	.string "Did I screw up my\n"
	.string "training?$"

Route34_Johto_CamperTodd1AfterText:
	.string "Maybe I should\n"
	.string "take one to a DAY-"
	.string "\pCARE. Or maybe use\n"
	.string "some items…$"

Route34_Johto_CamperToddSaleText:
	.string "Shopping under the\n"
	.string "sky!"
	.string "\pIt feels so nice\n"
	.string "up on a rooftop.$"

Route34_Johto_PicnickerGina1SeenText:
	.string "Are you a trainer?"
	.string "\pLet's have a\n"
	.string "practice battle.$"

Route34_Johto_PicnickerGina1BeatenText:
	.string "Oh, no! I just\n"
	.string "can't win…$"

Route34_Johto_PicnickerGina1AfterText:
	.string "You're too strong\n"
	.string "to be a practice\l"
	.string "partner.$"

Route34_Johto_OfficerKeithSeenText:
	.string "Who goes there?\n"
	.string "What are you up\l"
	.string "to?$"

Route34_Johto_OfficerKeithWinText:
	.string "You're a tough\n"
	.string "little kid.$"

Route34_Johto_OfficerKeithAfterText:
	.string "Yep, I see nothing\n"
	.string "wrong today. You"
	.string "\pbe good and stay\n"
	.string "out of trouble.$"

Route34_Johto_OfficerKeithDaytimeText:
	.string "I'm on patrol for\n"
	.string "suspicious indi-\l"
	.string "viduals.$"

Route34_Johto_PokefanmBrandonSeenText:
	.string "I just got my\n"
	.string "POKéMON back from\l"
	.string "DAY-CARE."
	.string "\pLet's see how much\n"
	.string "stronger it got!$"

Route34_Johto_PokefanmBrandonBeatenText:
	.string "Why does it end\n"
	.string "this way?$"

Route34_Johto_PokefanmBrandonAfterText:
	.string "My POKéMON knew\n"
	.string "moves I didn't\l"
	.string "know it had."
	.string "\pThat confounded me\n"
	.string "to no end!$"

Route34_Johto_CooltrainerfIreneSeenText:
	.string "IRENE: Kyaaah!\n"
	.string "Someone found us!$"

Route34_Johto_CooltrainerfIreneBeatenText:
	.string "IRENE: Ohhh!\n"
	.string "Too strong!$"

Route34_Johto_CooltrainerfIreneAfterText1:
	.string "IRENE: My sister\n"
	.string "KATE will get you\l"
	.string "for this!$"

Route34_Johto_CooltrainerfIreneAfterText2:
	.string "IRENE: Isn't this\n"
	.string "beach great?"
	.string "\pIt's our secret\n"
	.string "little getaway!$"

Route34_Johto_CooltrainerfJennSeenText:
	.string "JENN: You can't\n"
	.string "beat IRENE and go\l"
	.string "unpunished!$"

Route34_Johto_CooltrainerfJennBeatenText:
	.string "JENN: So sorry,\n"
	.string "IRENE! Sis!$"

Route34_Johto_CooltrainerfJennAfterText1:
	.string "JENN: Don't get\n"
	.string "cocky! My sister\l"
	.string "KATE is tough!$"

Route34_Johto_CooltrainerfJennAfterText2:
	.string "JENN: Sunlight\n"
	.string "makes your body\l"
	.string "stronger.$"

Route34_Johto_CooltrainerfKateSeenText:
	.string "KATE: You sure\n"
	.string "were mean to my\l"
	.string "little sisters!$"

Route34_Johto_CooltrainerfKateBeatenText:
	.string "KATE: No! I can't\n"
	.string "believe I lost.$"

Route34_Johto_CooltrainerfKateOfferSoftSandText:
	.string "KATE: You're too\n"
	.string "strong. I didn't\l"
	.string "stand a chance."
	.string "\pHere. You deserve\n"
	.string "this.$"

Route34_Johto_CooltrainerfKateAfterText:
	.string "KATE: I'm sorry we\n"
	.string "jumped you."
	.string "\pWe never expected\n"
	.string "anyone to find us"
	.string "\phere. You sure\n"
	.string "startled us.$"

Route34_Johto_Route34SignText:
	.string "ROUTE 34"
	.string "\pGOLDENROD CITY -\n"
	.string "AZALEA TOWN"
	.string "\pILEX FOREST\n"
	.string "SOMEWHERE BETWEEN$"

Route34_Johto_Route34TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pBERRY trees grow\n"
	.string "new BERRIES\l"
	.string "every day."
	.string "\pMake a note of\n"
	.string "which trees bear\l"
	.string "which BERRIES.$"

Route34_Johto_DayCareSignText:
	.string "DAY-CARE"
	.string "\pLET US RAISE YOUR\n"
	.string "POKéMON FOR YOU!$"
