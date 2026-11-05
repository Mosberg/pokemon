Route32_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, Route32_Johto_OnLoad
	.byte 0

Route32_Johto_OnTransition:
	call Route32_Johto_Route32FriedaCallback_Cb
	end

Route32_Johto_Route32CooltrainerMScript_Entry::
	lockall
	goto Route32_Johto_Route32CooltrainerMScript

Route32_Johto_SlowpokeTailSalesmanScript_Entry::
	lockall
	goto Route32_Johto_SlowpokeTailSalesmanScript

Route32_Johto_Route32GreatBall_Entry::
	lockall
	goto Route32_Johto_Route32GreatBall

Route32_Johto_Route32RoarTMGuyScript_Entry::
	lockall
	goto Route32_Johto_Route32RoarTMGuyScript

Route32_Johto_FriedaScript_Entry::
	lockall
	goto Route32_Johto_FriedaScript

Route32_Johto_Route32Repel_Entry::
	lockall
	goto Route32_Johto_Route32Repel

Route32_Johto_Route32Sign_Entry::
	lockall
	goto Route32_Johto_Route32Sign

Route32_Johto_Route32RuinsSign_Entry::
	lockall
	goto Route32_Johto_Route32RuinsSign

Route32_Johto_Route32UnionCaveSign_Entry::
	lockall
	goto Route32_Johto_Route32UnionCaveSign

Route32_Johto_Route32PokecenterSign_Entry::
	lockall
	goto Route32_Johto_Route32PokecenterSign

Route32_Johto_Route32CooltrainerMStopsYouScene_Entry::
	lockall
	goto Route32_Johto_Route32CooltrainerMStopsYouScene

Route32_Johto_Route32WannaBuyASlowpokeTailScript_Entry::
	lockall
	goto Route32_Johto_Route32WannaBuyASlowpokeTailScript


Route32_Johto_Route32CooltrainerMScript:
	faceplayer

Route32_Johto_Route32CooltrainerMContinueScene:
	goto_if_set FLAG_JOHTO_GOT_MIRACLE_SEED_IN_ROUTE_32, Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed
	goto_if_unset FLAG_JOHTO_ENGINE_ZEPHYRBADGE, Route32_Johto_Route32CooltrainerMContinueScene_DontHaveZephyrBadge
	goto_if_set FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, Route32_Johto_Route32CooltrainerMContinueScene_GiveMiracleSeed
	message Route32_Johto_Route32CooltrainerMText_AideIsWaiting
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32CooltrainerMContinueScene_GiveMiracleSeed:
	message Route32_Johto_Route32CooltrainerMText_HaveThisSeed
	waitmessage
	waitbuttonpress
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, 0, Route32_Johto_Route32CooltrainerMContinueScene_BagFull
	setflag FLAG_JOHTO_GOT_MIRACLE_SEED_IN_ROUTE_32
	goto Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed

Route32_Johto_Route32CooltrainerMContinueScene_DontHaveZephyrBadge:
	message Route32_Johto_Route32CooltrainerMText_VioletGym
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed:
	message Route32_Johto_Route32CooltrainerMText_ExperiencesShouldBeUseful
	waitmessage
	waitbuttonpress

Route32_Johto_Route32CooltrainerMContinueScene_BagFull:
	closemessage
	releaseall
	end

Route32_Johto_Route32CooltrainerMStopsYouScene:
	applymovement 8, Johto_Movement_Face_Left
	waitmovement 8
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message Route32_Johto_Route32CooltrainerMText_WhatsTheHurry
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 8, Route32_Johto_Movement_Route32CooltrainerMPushesYouBackToViolet
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Johto_Movement_Route32CooltrainerMPushesYouBackToViolet
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	call Route32_Johto_Route32CooltrainerMContinueScene_Sub
	applymovement 8, Route32_Johto_Movement_Route32CooltrainerMReset1
	waitmovement 8
	applymovement 8, Route32_Johto_Movement_Route32CooltrainerMReset2
	waitmovement 8
	releaseall
	end

Route32_Johto_Route32RoarTMGuyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM05_ROAR, Route32_Johto_Route32RoarTMGuyScript_AlreadyHaveRoar
	message Route32_Johto_Text_RoarIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_ROAR
	goto_if_eq VAR_RESULT, 0, Route32_Johto_Route32RoarTMGuyScript_Finish
	setflag FLAG_JOHTO_GOT_TM05_ROAR

Route32_Johto_Route32RoarTMGuyScript_AlreadyHaveRoar:
	message Route32_Johto_Text_RoarOutro
	waitmessage
	waitbuttonpress

Route32_Johto_Route32RoarTMGuyScript_Finish:
	closemessage
	releaseall
	end

Route32_Johto_Route32WannaBuyASlowpokeTailScript:
	applymovement 10, Johto_Movement_Face_Down
	waitmovement 10
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	goto Route32_Johto__OfferToSellSlowpokeTail

Route32_Johto_SlowpokeTailSalesmanScript:
	faceplayer

Route32_Johto__OfferToSellSlowpokeTail:
	setvar VAR_JOHTO_SCENE_ROUTE_32, 2
	message Route32_Johto_Text_MillionDollarSlowpokeTail
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route32_Johto__OfferToSellSlowpokeTail_refused
	message Route32_Johto_Text_ThoughtKidsWereLoaded
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto__OfferToSellSlowpokeTail_refused:
	message Route32_Johto_Text_RefusedToBuySlowpokeTail
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerCamperRoland::
	trainerbattle_single TRAINER_JOHTO_CAMPER_ROLAND, Route32_Johto_CamperRolandSeenText, Route32_Johto_CamperRolandBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_ROLAND
	lock
	faceplayer
	goto Route32_Johto_TrainerCamperRoland_Script

Route32_Johto_TrainerCamperRoland_Script:
	message Route32_Johto_CamperRolandAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerFisherJustin::
	trainerbattle_single TRAINER_JOHTO_FISHER_JUSTIN, Route32_Johto_FisherJustinSeenText, Route32_Johto_FisherJustinBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_JUSTIN
	lock
	faceplayer
	goto Route32_Johto_TrainerFisherJustin_Script

Route32_Johto_TrainerFisherJustin_Script:
	message Route32_Johto_FisherJustinAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerFisherRalph1::
	trainerbattle_single TRAINER_JOHTO_FISHER_RALPH1, Route32_Johto_FisherRalph1SeenText, Route32_Johto_FisherRalph1BeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_RALPH
	lock
	faceplayer
	goto Route32_Johto_TrainerFisherRalph1_Script

Route32_Johto_TrainerFisherRalph1_Script:
	setvar VAR_0x8007, 993
	goto_if_set FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH, Route32_Johto_TrainerFisherRalph1_Rematch
	goto_if_set FLAG_JOHTO_ENGINE_QWILFISH_SWARM, Route32_Johto_TrainerFisherRalph1_Swarm
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_FISHER_RALPH_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route32_Johto_TrainerFisherRalph1_NumberAccepted
	goto_if_set FLAG_JOHTO_RALPH_ASKED_FOR_PHONE_NUMBER, Route32_Johto_TrainerFisherRalph1_AskAgain
	message Route32_Johto_FisherRalphAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_RALPH_ASKED_FOR_PHONE_NUMBER
	call Route32_Johto_TrainerFisherRalph1_AskNumber1_Sub
	goto Route32_Johto_TrainerFisherRalph1_AskForNumber

Route32_Johto_TrainerFisherRalph1_AskAgain:
	call Route32_Johto_TrainerFisherRalph1_AskNumber2_Sub

Route32_Johto_TrainerFisherRalph1_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_FISHER_RALPH_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route32_Johto_TrainerFisherRalph1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route32_Johto_TrainerFisherRalph1_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_FISHER_RALPH1
	call Route32_Johto_TrainerFisherRalph1_RegisteredNumber_Sub
	goto Route32_Johto_TrainerFisherRalph1_NumberAccepted

Route32_Johto_TrainerFisherRalph1_Rematch:
	call Route32_Johto_TrainerFisherRalph1_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WRALPHFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route32_Johto_TrainerFisherRalph1_Fight4
	goto_if_eq VAR_RESULT, 3, Route32_Johto_TrainerFisherRalph1_Fight3
	goto_if_eq VAR_RESULT, 2, Route32_Johto_TrainerFisherRalph1_Fight2
	goto_if_eq VAR_RESULT, 1, Route32_Johto_TrainerFisherRalph1_Fight1
	goto_if_eq VAR_RESULT, 0, Route32_Johto_TrainerFisherRalph1_LoadFight0

Route32_Johto_TrainerFisherRalph1_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route32_Johto_TrainerFisherRalph1_LoadFight4

Route32_Johto_TrainerFisherRalph1_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route32_Johto_TrainerFisherRalph1_LoadFight3

Route32_Johto_TrainerFisherRalph1_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_LAKE_OF_RAGE, Route32_Johto_TrainerFisherRalph1_LoadFight2

Route32_Johto_TrainerFisherRalph1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_ECRUTEAK, Route32_Johto_TrainerFisherRalph1_LoadFight1

Route32_Johto_TrainerFisherRalph1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_RALPH1, Route32_Johto_FisherRalph1BeatenText
	setvar VAR_JOHTO_MEM_WRALPHFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_RALPH2, Route32_Johto_FisherRalph1BeatenText
	setvar VAR_JOHTO_MEM_WRALPHFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_RALPH3, Route32_Johto_FisherRalph1BeatenText
	setvar VAR_JOHTO_MEM_WRALPHFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_RALPH4, Route32_Johto_FisherRalph1BeatenText
	setvar VAR_JOHTO_MEM_WRALPHFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_RALPH5, Route32_Johto_FisherRalph1BeatenText
	clearflag FLAG_JOHTO_ENGINE_RALPH_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_Swarm:
	message Route32_Johto_FisherRalphSwarmText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerFisherRalph1_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route32_Johto_TrainerFisherRalph1_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route32_Johto_TrainerFisherRalph1_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route32_Johto_TrainerFisherHenry::
	trainerbattle_single TRAINER_JOHTO_FISHER_HENRY, Route32_Johto_FisherHenrySeenText, Route32_Johto_FisherHenryBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_HENRY
	lock
	faceplayer
	goto Route32_Johto_TrainerFisherHenry_Script

Route32_Johto_TrainerFisherHenry_Script:
	message Route32_Johto_FisherHenryAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_LIZ1, Route32_Johto_PicnickerLiz1SeenText, Route32_Johto_PicnickerLiz1BeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_LIZ
	lock
	faceplayer
	goto Route32_Johto_TrainerPicnickerLiz1_Script

Route32_Johto_TrainerPicnickerLiz1_Script:
	setvar VAR_0x8007, 718
	goto_if_set FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH, Route32_Johto_TrainerPicnickerLiz1_Rematch
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_LIZ_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route32_Johto_TrainerPicnickerLiz1_NumberAccepted
	goto_if_set FLAG_JOHTO_LIZ_ASKED_FOR_PHONE_NUMBER, Route32_Johto_TrainerPicnickerLiz1_AskAgain
	message Route32_Johto_PicnickerLiz1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_LIZ_ASKED_FOR_PHONE_NUMBER
	call Route32_Johto_TrainerPicnickerLiz1_AskNumber1_Sub
	goto Route32_Johto_TrainerPicnickerLiz1_AskForNumber

Route32_Johto_TrainerPicnickerLiz1_AskAgain:
	call Route32_Johto_TrainerPicnickerLiz1_AskNumber2_Sub

Route32_Johto_TrainerPicnickerLiz1_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_LIZ_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route32_Johto_TrainerPicnickerLiz1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route32_Johto_TrainerPicnickerLiz1_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_PICNICKER_LIZ1
	call Route32_Johto_TrainerPicnickerLiz1_RegisteredNumber_Sub
	goto Route32_Johto_TrainerPicnickerLiz1_NumberAccepted

Route32_Johto_TrainerPicnickerLiz1_Rematch:
	call Route32_Johto_TrainerPicnickerLiz1_RematchStd_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WLIZFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route32_Johto_TrainerPicnickerLiz1_Fight4
	goto_if_eq VAR_RESULT, 3, Route32_Johto_TrainerPicnickerLiz1_Fight3
	goto_if_eq VAR_RESULT, 2, Route32_Johto_TrainerPicnickerLiz1_Fight2
	goto_if_eq VAR_RESULT, 1, Route32_Johto_TrainerPicnickerLiz1_Fight1
	goto_if_eq VAR_RESULT, 0, Route32_Johto_TrainerPicnickerLiz1_LoadFight0

Route32_Johto_TrainerPicnickerLiz1_Fight4:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route32_Johto_TrainerPicnickerLiz1_LoadFight4

Route32_Johto_TrainerPicnickerLiz1_Fight3:
	goto_if_set FLAG_JOHTO_CLEARED_RADIO_TOWER, Route32_Johto_TrainerPicnickerLiz1_LoadFight3

Route32_Johto_TrainerPicnickerLiz1_Fight2:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, Route32_Johto_TrainerPicnickerLiz1_LoadFight2

Route32_Johto_TrainerPicnickerLiz1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_ECRUTEAK, Route32_Johto_TrainerPicnickerLiz1_LoadFight1

Route32_Johto_TrainerPicnickerLiz1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_LIZ1, Route32_Johto_PicnickerLiz1BeatenText
	setvar VAR_JOHTO_MEM_WLIZFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_LIZ2, Route32_Johto_PicnickerLiz1BeatenText
	setvar VAR_JOHTO_MEM_WLIZFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_LIZ3, Route32_Johto_PicnickerLiz1BeatenText
	setvar VAR_JOHTO_MEM_WLIZFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_LIZ4, Route32_Johto_PicnickerLiz1BeatenText
	setvar VAR_JOHTO_MEM_WLIZFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_LIZ5, Route32_Johto_PicnickerLiz1BeatenText
	clearflag FLAG_JOHTO_ENGINE_LIZ_READY_FOR_REMATCH
	releaseall
	end

Route32_Johto_TrainerPicnickerLiz1_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route32_Johto_TrainerPicnickerLiz1_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

Route32_Johto_TrainerPicnickerLiz1_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route32_Johto_TrainerYoungsterAlbert::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_ALBERT, Route32_Johto_YoungsterAlbertSeenText, Route32_Johto_YoungsterAlbertBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_ALBERT
	lock
	faceplayer
	goto Route32_Johto_TrainerYoungsterAlbert_Script

Route32_Johto_TrainerYoungsterAlbert_Script:
	message Route32_Johto_YoungsterAlbertAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerYoungsterGordon::
	trainerbattle_single TRAINER_JOHTO_YOUNGSTER_GORDON, Route32_Johto_YoungsterGordonSeenText, Route32_Johto_YoungsterGordonBeatenText
	setflag FLAG_JOHTO_BEAT_YOUNGSTER_GORDON
	lock
	faceplayer
	goto Route32_Johto_TrainerYoungsterGordon_Script

Route32_Johto_TrainerYoungsterGordon_Script:
	message Route32_Johto_YoungsterGordonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_TrainerBirdKeeperPeter::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_PETER, Route32_Johto_BirdKeeperPeterSeenText, Route32_Johto_BirdKeeperPeterBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_PETER
	lock
	faceplayer
	goto Route32_Johto_TrainerBirdKeeperPeter_Script

Route32_Johto_TrainerBirdKeeperPeter_Script:
	message Route32_Johto_BirdKeeperPeterAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_FriedaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_POISON_BARB_FROM_FRIEDA, Route32_Johto_FriedaScript_Friday
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 5, Route32_Johto_FriedaScript_NotFriday
	goto_if_set FLAG_JOHTO_MET_FRIEDA_OF_FRIDAY, Route32_Johto_FriedaScript_MetFrieda
	message Route32_Johto_MeetFriedaText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_FRIEDA_OF_FRIDAY

Route32_Johto_FriedaScript_MetFrieda:
	message Route32_Johto_FriedaGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_POISON_BARB
	goto_if_eq VAR_RESULT, 0, Route32_Johto_FriedaScript_Done
	setflag FLAG_JOHTO_GOT_POISON_BARB_FROM_FRIEDA
	message Route32_Johto_FriedaGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_FriedaScript_Friday:
	message Route32_Johto_FriedaFridayText
	waitmessage
	waitbuttonpress

Route32_Johto_FriedaScript_Done:
	closemessage
	releaseall
	end

Route32_Johto_FriedaScript_NotFriday:
	message Route32_Johto_FriedaNotFridayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32GreatBall:
	finditem ITEM_GREAT_BALL
	releaseall
	end

Route32_Johto_Route32Repel:
	finditem ITEM_REPEL
	releaseall
	end

Route32_Johto_Route32Sign:
	message Route32_Johto_Route32SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32RuinsSign:
	message Route32_Johto_Route32RuinsSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32UnionCaveSign:
	message Route32_Johto_Route32UnionCaveSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32_Johto_Route32PokecenterSign:
	goto Johto_Std_PokecenterSignScript

Route32_Johto_Route32CooltrainerMContinueScene_Sub:
	goto_if_set FLAG_JOHTO_GOT_MIRACLE_SEED_IN_ROUTE_32, Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed_Sub
	goto_if_unset FLAG_JOHTO_ENGINE_ZEPHYRBADGE, Route32_Johto_Route32CooltrainerMContinueScene_DontHaveZephyrBadge_Sub
	goto_if_set FLAG_JOHTO_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, Route32_Johto_Route32CooltrainerMContinueScene_GiveMiracleSeed_Sub
	message Route32_Johto_Route32CooltrainerMText_AideIsWaiting
	waitmessage
	waitbuttonpress
	closemessage
	return

Route32_Johto_Route32CooltrainerMContinueScene_GiveMiracleSeed_Sub:
	message Route32_Johto_Route32CooltrainerMText_HaveThisSeed
	waitmessage
	waitbuttonpress
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, 0, Route32_Johto_Route32CooltrainerMContinueScene_BagFull_Sub
	setflag FLAG_JOHTO_GOT_MIRACLE_SEED_IN_ROUTE_32
	goto Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed_Sub

Route32_Johto_Route32CooltrainerMContinueScene_DontHaveZephyrBadge_Sub:
	message Route32_Johto_Route32CooltrainerMText_VioletGym
	waitmessage
	waitbuttonpress
	closemessage
	return

Route32_Johto_Route32CooltrainerMContinueScene_GotMiracleSeed_Sub:
	message Route32_Johto_Route32CooltrainerMText_ExperiencesShouldBeUseful
	waitmessage
	waitbuttonpress

Route32_Johto_Route32CooltrainerMContinueScene_BagFull_Sub:
	closemessage
	return

Route32_Johto_TrainerFisherRalph1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route32_Johto_TrainerFisherRalph1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route32_Johto_TrainerFisherRalph1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route32_Johto_TrainerFisherRalph1_RematchStd_Sub:
	goto Johto_Std_RematchMScript_Sub

Route32_Johto_TrainerPicnickerLiz1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route32_Johto_TrainerPicnickerLiz1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route32_Johto_TrainerPicnickerLiz1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route32_Johto_TrainerPicnickerLiz1_RematchStd_Sub:
	goto Johto_Std_RematchFScript_Sub

Route32_Johto_Route32FriedaCallback_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 5, Route32_Johto_Route32FriedaCallback_FriedaAppears_Cb
	setflag FLAG_JOHTO_ROUTE_32_FRIEDA_OF_FRIDAY
	return

Route32_Johto_Route32FriedaCallback_FriedaAppears_Cb:
	clearflag FLAG_JOHTO_ROUTE_32_FRIEDA_OF_FRIDAY
	return

Route32_Johto_Movement_Route32CooltrainerMPushesYouBackToViolet:
	walk_up
	walk_up
	step_end

Route32_Johto_Movement_Route32CooltrainerMReset1:
	walk_down
	step_end

Route32_Johto_Movement_Route32CooltrainerMReset2:
	walk_right
	step_end

Route32_Johto_Route32CooltrainerMText_WhatsTheHurry:
	.string "Wait up!\n"
	.string "What's the hurry?$"

Route32_Johto_Route32CooltrainerMText_AideIsWaiting:
	.string "{PLAYER}, right?\n"
	.string "Some guy wearing"
	.string "\pglasses was look-\n"
	.string "ing for you."
	.string "\pSee for yourself.\n"
	.string "He's waiting for"
	.string "\pyou at the POKéMON\n"
	.string "CENTER.$"

Route32_Johto_Route32CooltrainerMText_VioletGym:
	.string "Have you gone to\n"
	.string "the POKéMON GYM?"
	.string "\pYou can test your\n"
	.string "POKéMON and your-\l"
	.string "self there."
	.string "\pIt's a rite of\n"
	.string "passage for all\l"
	.string "trainers!$"

Route32_Johto_Route32CooltrainerMText_HaveThisSeed:
	.string "You have some good\n"
	.string "POKéMON there."
	.string "\pIt must be from\n"
	.string "the training you"
	.string "\pgave them around\n"
	.string "VIOLET CITY."
	.string "\pThe training at\n"
	.string "the GYM must have"
	.string "\pbeen especially\n"
	.string "helpful."
	.string "\pAs a souvenir of\n"
	.string "VIOLET CITY, take\l"
	.string "this."
	.string "\pIt increases the\n"
	.string "power of grass-\l"
	.string "type moves.$"

Route32_Johto_Route32CooltrainerMText_ExperiencesShouldBeUseful:
	.string "Your experiences\n"
	.string "in VIOLET CITY"
	.string "\pshould be useful\n"
	.string "for your journey.$"

Route32_Johto_Text_MillionDollarSlowpokeTail:
	.string "How would you like\n"
	.string "to have this"
	.string "\ptasty, nutritious\n"
	.string "SLOWPOKETAIL?"
	.string "\pFor you right now,\n"
	.string "just ¥1,000,000!"
	.string "\pYou'll want this!$"

Route32_Johto_Text_ThoughtKidsWereLoaded:
	.string "Tch! I thought\n"
	.string "kids these days\l"
	.string "were loaded…$"

Route32_Johto_Text_RefusedToBuySlowpokeTail:
	.string "You don't want it?\n"
	.string "Then scram. Shoo!$"

Route32_Johto_FisherJustinSeenText:
	.string "Whoa!"
	.string "\pYou made me lose\n"
	.string "that fish!$"

Route32_Johto_FisherJustinBeatenText:
	.string "Sploosh!$"

Route32_Johto_FisherJustinAfterText:
	.string "Calm, collected…\n"
	.string "The essence of"
	.string "\pfishing and POKé-\n"
	.string "MON is the same.$"

Route32_Johto_FisherRalph1SeenText:
	.string "I'm really good at\n"
	.string "both fishing and\l"
	.string "POKéMON."
	.string "\pI'm not about to\n"
	.string "lose to any kid!$"

Route32_Johto_FisherRalph1BeatenText:
	.string "Tch! I tried to\n"
	.string "rush things…$"

Route32_Johto_FisherRalphAfterText:
	.string "Fishing is a life-\n"
	.string "long passion."
	.string "\pPOKéMON are life-\n"
	.string "long friends!$"

Route32_Johto_FisherRalphSwarmText:
	.string "One, two, three…\n"
	.string "Muahahaha, what a"
	.string "\pgreat haul!\n"
	.string "I'm done! Go ahead"
	.string "\pand catch as many\n"
	.string "as you can, kid!$"

Route32_Johto_FisherHenrySeenText:
	.string "My POKéMON?\n"
	.string "Freshly caught!$"

Route32_Johto_FisherHenryBeatenText:
	.string "SPLASH?$"

Route32_Johto_FisherHenryAfterText:
	.string "Freshly caught\n"
	.string "POKéMON are no"
	.string "\pmatch for properly\n"
	.string "raised ones.$"

Route32_Johto_YoungsterAlbertSeenText:
	.string "I haven't seen you\n"
	.string "around before."
	.string "\pSo you think you\n"
	.string "are pretty tough?$"

Route32_Johto_YoungsterAlbertBeatenText:
	.string "You're strong!$"

Route32_Johto_YoungsterAlbertAfterText:
	.string "I'm going to try\n"
	.string "to be the best\l"
	.string "with my favorites."
	.string "\pI'm not using the\n"
	.string "same tough POKéMON\l"
	.string "as everyone else.$"

Route32_Johto_YoungsterGordonSeenText:
	.string "I found some good\n"
	.string "POKéMON in the\l"
	.string "grass!"
	.string "\pI think they'll do\n"
	.string "it for me!$"

Route32_Johto_YoungsterGordonBeatenText:
	.string "Darn. I thought I\n"
	.string "could win.$"

Route32_Johto_YoungsterGordonAfterText:
	.string "The grass is full\n"
	.string "of clingy things.$"

Route32_Johto_CamperRolandSeenText:
	.string "That glance…\n"
	.string "It's intriguing.$"

Route32_Johto_CamperRolandBeatenText:
	.string "Hmmm. This is\n"
	.string "disappointing.$"

Route32_Johto_CamperRolandAfterText:
	.string "If you don't want\n"
	.string "to battle, just\l"
	.string "avoid eye contact.$"

Route32_Johto_PicnickerLiz1SeenText:
	.string "Uh-huh. Yeah, and\n"
	.string "you know…"
	.string "\pPardon? Battle?\n"
	.string "I'm on the phone."
	.string "\pOh, all right. But\n"
	.string "make it fast.$"

Route32_Johto_PicnickerLiz1BeatenText:
	.string "Oh! I've got to\n"
	.string "relieve my anger!$"

Route32_Johto_PicnickerLiz1AfterText:
	.string "I was having a\n"
	.string "nice chat too.$"

Route32_Johto_BirdKeeperPeterSeenText:
	.string "That BADGE! It's\n"
	.string "from VIOLET CITY!"
	.string "\pYou beat FALKNER?$"

Route32_Johto_BirdKeeperPeterBeatenText:
	.string "I know what my\n"
	.string "weaknesses are.$"

Route32_Johto_BirdKeeperPeterAfterText:
	.string "I should train\n"
	.string "again at the GYM\l"
	.string "in VIOLET CITY.$"

Route32_Johto_Text_RoarIntro:
	.string "WROOOOAR!\n"
	.string "PEOPLE RUN WHEN I"
	.string "\pROAR! BUT YOU\n"
	.string "CAME LOOKING!"
	.string "\pTHAT PLEASES ME!\n"
	.string "NOW TAKE THIS!$"

Route32_Johto_Text_RoarOutro:
	.string "WROOOAR!\n"
	.string "IT'S ROAR!"
	.string "\pEVEN POKéMON RUN\n"
	.string "FROM A GOOD ROAR!$"

Route32_Johto_MeetFriedaText:
	.string "FRIEDA: Yahoo!\n"
	.string "It's Friday!"
	.string "\pI'm FRIEDA of\n"
	.string "Friday!"
	.string "\pNice to meet you!$"

Route32_Johto_FriedaGivesGiftText:
	.string "Here's a POISON\n"
	.string "BARB for you!$"

Route32_Johto_FriedaGaveGiftText:
	.string "FRIEDA: Give it to\n"
	.string "a POKéMON that has\l"
	.string "poison-type moves."
	.string "\pOh!"
	.string "\pIt's wicked!"
	.string "\pYou'll be shocked\n"
	.string "how good it makes\l"
	.string "poison moves!$"

Route32_Johto_FriedaFridayText:
	.string "FRIEDA: Hiya! What\n"
	.string "day do you like?"
	.string "\pI love Friday. No\n"
	.string "doubt about it!"
	.string "\pDon't you think\n"
	.string "it's great too?$"

Route32_Johto_FriedaNotFridayText:
	.string "FRIEDA: Isn't it\n"
	.string "Friday today?"
	.string "\pIt's so boring\n"
	.string "when it's not!$"

Route32_Johto_Route32SignText:
	.string "ROUTE 32"
	.string "\pVIOLET CITY -\n"
	.string "AZALEA TOWN$"

Route32_Johto_Route32RuinsSignText:
	.string "RUINS OF ALPH\n"
	.string "EAST ENTRANCE$"

Route32_Johto_Route32UnionCaveSignText:
	.string "UNION CAVE\n"
	.string "AHEAD$"

Route32_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_32_0, Route32_Johto_CutTree0_Keep
	setmetatile 10, 18, 514, 0
	setmetatile 11, 18, 514, 0
	setmetatile 10, 19, 514, 0
	setmetatile 11, 19, 591, 0
Route32_Johto_CutTree0_Keep:
	end

Route32_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route32_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_32_0
	setmetatile 10, 18, 514, 0
	setmetatile 11, 18, 514, 0
	setmetatile 10, 19, 514, 0
	setmetatile 11, 19, 591, 0
	special DrawWholeMapView
Route32_Johto_CutTree0_Done:
	releaseall
	end
