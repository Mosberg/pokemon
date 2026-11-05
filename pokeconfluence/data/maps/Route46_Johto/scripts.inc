Route46_Johto_MapScripts::
	.byte 0

Route46_Johto_Route46FruitTree1_Entry::
	lockall
	goto Route46_Johto_Route46FruitTree1

Route46_Johto_Route46FruitTree2_Entry::
	lockall
	goto Route46_Johto_Route46FruitTree2

Route46_Johto_Route46XSpeed_Entry::
	lockall
	goto Route46_Johto_Route46XSpeed

Route46_Johto_Route46Sign_Entry::
	lockall
	goto Route46_Johto_Route46Sign


Route46_Johto_TrainerCamperTed::
	trainerbattle_single TRAINER_JOHTO_CAMPER_TED, Route46_Johto_CamperTedSeenText, Route46_Johto_CamperTedBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_TED
	lock
	faceplayer
	goto Route46_Johto_TrainerCamperTed_Script

Route46_Johto_TrainerCamperTed_Script:
	message Route46_Johto_CamperTedAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route46_Johto_TrainerPicnickerErin1::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_ERIN1, Route46_Johto_PicnickerErin1SeenText, Route46_Johto_PicnickerErin1BeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_ERIN
	lock
	faceplayer
	goto Route46_Johto_TrainerPicnickerErin1_Script

Route46_Johto_TrainerPicnickerErin1_Script:
	setvar VAR_0x8007, 552
	goto_if_set FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH, Route46_Johto_TrainerPicnickerErin1_WantsBattle
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_ERIN_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route46_Johto_Route46NumberAcceptedF
	goto_if_set FLAG_JOHTO_ERIN_ASKED_FOR_PHONE_NUMBER, Route46_Johto_TrainerPicnickerErin1_AskedAlready
	message Route46_Johto_PicnickerErinAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_ERIN_ASKED_FOR_PHONE_NUMBER
	call Route46_Johto_Route46AskNumber1F_Sub
	goto Route46_Johto_TrainerPicnickerErin1_AskForNumber

Route46_Johto_TrainerPicnickerErin1_AskedAlready:
	call Route46_Johto_Route46AskNumber2F_Sub

Route46_Johto_TrainerPicnickerErin1_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_PICNICKER_ERIN_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route46_Johto_Route46PhoneFullF
	goto_if_eq VAR_RESULT, 2, Route46_Johto_Route46NumberDeclinedF
	buffertrainername STR_VAR_1, TRAINER_JOHTO_PICNICKER_ERIN1
	call Route46_Johto_Route46RegisteredNumberF_Sub
	goto Route46_Johto_Route46NumberAcceptedF

Route46_Johto_TrainerPicnickerErin1_WantsBattle:
	call Route46_Johto_Route46RematchF_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WERINFIGHTCOUNT
	goto_if_eq VAR_RESULT, 2, Route46_Johto_TrainerPicnickerErin1_Fight2
	goto_if_eq VAR_RESULT, 1, Route46_Johto_TrainerPicnickerErin1_Fight1
	goto_if_eq VAR_RESULT, 0, Route46_Johto_TrainerPicnickerErin1_LoadFight0

Route46_Johto_TrainerPicnickerErin1_Fight2:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route46_Johto_TrainerPicnickerErin1_LoadFight2

Route46_Johto_TrainerPicnickerErin1_Fight1:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route46_Johto_TrainerPicnickerErin1_LoadFight1

Route46_Johto_TrainerPicnickerErin1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_ERIN1, Route46_Johto_PicnickerErin1BeatenText
	setvar VAR_JOHTO_MEM_WERINFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH
	releaseall
	end

Route46_Johto_TrainerPicnickerErin1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_ERIN2, Route46_Johto_PicnickerErin1BeatenText
	setvar VAR_JOHTO_MEM_WERINFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH
	releaseall
	end

Route46_Johto_TrainerPicnickerErin1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_ERIN3, Route46_Johto_PicnickerErin1BeatenText
	clearflag FLAG_JOHTO_ENGINE_ERIN_READY_FOR_REMATCH
	goto_if_set FLAG_JOHTO_ERIN_CALCIUM, Route46_Johto_TrainerPicnickerErin1_HasCalcium
	goto_if_set FLAG_JOHTO_GOT_CALCIUM_FROM_ERIN, Route46_Johto_TrainerPicnickerErin1_GotCalciumAlready
	call Route46_Johto_Route46RematchGiftF_Sub
	giveitem ITEM_CALCIUM
	goto_if_eq VAR_RESULT, 0, Route46_Johto_ErinNoRoomForCalcium
	setflag FLAG_JOHTO_GOT_CALCIUM_FROM_ERIN
	goto Route46_Johto_Route46NumberAcceptedF

Route46_Johto_TrainerPicnickerErin1_GotCalciumAlready:
	releaseall
	end

Route46_Johto_TrainerPicnickerErin1_HasCalcium:
	message Route46_Johto_PicnickerErin2BeatenText
	waitmessage
	waitbuttonpress
	giveitem ITEM_CALCIUM
	goto_if_eq VAR_RESULT, 0, Route46_Johto_ErinNoRoomForCalcium
	clearflag FLAG_JOHTO_ERIN_CALCIUM
	setflag FLAG_JOHTO_GOT_CALCIUM_FROM_ERIN
	goto Route46_Johto_Route46NumberAcceptedF

Route46_Johto_Route46NumberAcceptedF:
	goto Johto_Std_NumberAcceptedFScript

Route46_Johto_Route46NumberDeclinedF:
	goto Johto_Std_NumberDeclinedFScript

Route46_Johto_Route46PhoneFullF:
	goto Johto_Std_PhoneFullFScript

Route46_Johto_ErinNoRoomForCalcium:
	setflag FLAG_JOHTO_ERIN_CALCIUM
	goto Johto_Std_PackFullFScript

Route46_Johto_TrainerHikerBailey::
	trainerbattle_single TRAINER_JOHTO_HIKER_BAILEY, Route46_Johto_HikerBaileySeenText, Route46_Johto_HikerBaileyBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_BAILEY
	lock
	faceplayer
	goto Route46_Johto_TrainerHikerBailey_Script

Route46_Johto_TrainerHikerBailey_Script:
	message Route46_Johto_HikerBaileyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route46_Johto_Route46Sign:
	message Route46_Johto_Route46SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route46_Johto_Route46XSpeed:
	finditem ITEM_X_SPEED
	releaseall
	end

Route46_Johto_Route46FruitTree1:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_46_1, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ORAN_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_46_1
	releaseall
	end

Route46_Johto_Route46FruitTree2:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_46_2, Johto_Std_FruitTreeEmpty
	giveitem ITEM_CHERI_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_46_2
	releaseall
	end

Route46_Johto_Route46AskNumber1F_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route46_Johto_Route46AskNumber2F_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route46_Johto_Route46RegisteredNumberF_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route46_Johto_Route46RematchF_Sub:
	goto Johto_Std_RematchFScript_Sub

Route46_Johto_Route46RematchGiftF_Sub:
	goto Johto_Std_RematchGiftFScript_Sub

Route46_Johto_HikerBaileySeenText:
	.string "Awright! I'll show\n"
	.string "you the power of\l"
	.string "mountain POKéMON!$"

Route46_Johto_HikerBaileyBeatenText:
	.string "Mercy! You showed\n"
	.string "me your power!$"

Route46_Johto_HikerBaileyAfterBattleText:
	.string "It's over. I don't\n"
	.string "mind. We HIKERS\l"
	.string "are like that.$"

Route46_Johto_CamperTedSeenText:
	.string "I'm raising POKé-\n"
	.string "MON too!"
	.string "\pWill you battle\n"
	.string "with me?$"

Route46_Johto_CamperTedBeatenText:
	.string "Wha…?$"

Route46_Johto_CamperTedAfterBattleText:
	.string "I did my best but\n"
	.string "came up short."
	.string "\pNo excuses--I\n"
	.string "admit I lost.$"

Route46_Johto_PicnickerErin1SeenText:
	.string "I raise POKéMON\n"
	.string "too!"
	.string "\pWill you battle\n"
	.string "with me?$"

Route46_Johto_PicnickerErin1BeatenText:
	.string "Oh, rats!$"

Route46_Johto_PicnickerErinAfterBattleText:
	.string "I've been to many\n"
	.string "GYMS, but the GYM"
	.string "\pin GOLDENROD is my\n"
	.string "favorite."
	.string "\pIt's filled with\n"
	.string "pretty flowers!$"

Route46_Johto_PicnickerErin2BeatenText:
	.string "Aww… I keep losing\n"
	.string "all the time!"
	.string "\pI'll just have to\n"
	.string "try harder!"
	.string "\pAnyway, thanks for\n"
	.string "battling me again"
	.string "\pand again. Here's\n"
	.string "that present from\l"
	.string "the other time.$"

Route46_Johto_Route46SignText:
	.string "ROUTE 46\n"
	.string "MOUNTAIN RD. AHEAD$"
