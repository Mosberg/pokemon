Route38_Johto_MapScripts::
	.byte 0

Route38_Johto_Route38FruitTree_Entry::
	lockall
	goto Route38_Johto_Route38FruitTree

Route38_Johto_Route38Sign_Entry::
	lockall
	goto Route38_Johto_Route38Sign

Route38_Johto_Route38TrainerTips_Entry::
	lockall
	goto Route38_Johto_Route38TrainerTips


Route38_Johto_TrainerBirdKeeperToby::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_TOBY, Route38_Johto_BirdKeeperTobySeenText, Route38_Johto_BirdKeeperTobyBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_TOBY
	lock
	faceplayer
	goto Route38_Johto_TrainerBirdKeeperToby_Script

Route38_Johto_TrainerBirdKeeperToby_Script:
	message Route38_Johto_BirdKeeperTobyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_TrainerSailorHarry::
	trainerbattle_single TRAINER_JOHTO_SAILOR_HARRY, Route38_Johto_SailorHarrySeenText, Route38_Johto_SailorHarryBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_HARRY
	lock
	faceplayer
	goto Route38_Johto_TrainerSailorHarry_Script

Route38_Johto_TrainerSailorHarry_Script:
	message Route38_Johto_SailorHarryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_TrainerLassDana1::
	trainerbattle_single TRAINER_JOHTO_LASS_DANA1, Route38_Johto_LassDana1SeenText, Route38_Johto_LassDana1BeatenText
	setflag FLAG_JOHTO_BEAT_LASS_DANA
	lock
	faceplayer
	goto Route38_Johto_TrainerLassDana1_Script

Route38_Johto_TrainerLassDana1_Script:
	goto_if_set FLAG_JOHTO_ENGINE_DANA_READY_FOR_REMATCH, Route38_Johto_TrainerLassDana1_DanaRematch
	goto_if_set FLAG_JOHTO_ENGINE_DANA_HAS_THUNDERSTONE, Route38_Johto_TrainerLassDana1_TryGiveThunderstone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route38_Johto_TrainerLassDana1_NumberAccepted
	goto_if_set FLAG_JOHTO_DANA_ASKED_FOR_PHONE_NUMBER, Route38_Johto_TrainerLassDana1_SecondTimeAsking
	message Route38_Johto_LassDanaMoomooMilkText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_DANA_ASKED_FOR_PHONE_NUMBER
	call Route38_Johto_TrainerLassDana1_AskNumber1F_Sub
	goto Route38_Johto_TrainerLassDana1_AskForPhoneNumber

Route38_Johto_TrainerLassDana1_SecondTimeAsking:
	call Route38_Johto_TrainerLassDana1_AskNumber2F_Sub

Route38_Johto_TrainerLassDana1_AskForPhoneNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route38_Johto_TrainerLassDana1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route38_Johto_TrainerLassDana1_DeclinedPhoneNumber
	call Route38_Johto_TrainerLassDana1_RegisteredPhoneNumber_Sub
	goto Route38_Johto_TrainerLassDana1_NumberAccepted

Route38_Johto_TrainerLassDana1_DanaRematch:
	call Route38_Johto_TrainerLassDana1_Rematch_Sub
	@ TODO unsupported: readmem wDanaFightCount
	goto Johto_EventScript_Unimplemented

Route38_Johto_TrainerLassDana1_TryGiveThunderstone:
	call Route38_Johto_TrainerLassDana1_Gift_Sub
	giveitem ITEM_THUNDERSTONE
	goto_if_eq VAR_RESULT, 0, Route38_Johto_TrainerLassDana1_NoRoomForThunderstone
	clearflag FLAG_JOHTO_ENGINE_DANA_HAS_THUNDERSTONE
	setflag FLAG_JOHTO_DANA_GAVE_THUNDERSTONE
	goto Route38_Johto_TrainerLassDana1_NumberAccepted

Route38_Johto_TrainerLassDana1_NoRoomForThunderstone:
	goto Route38_Johto_TrainerLassDana1_PackFull

Route38_Johto_TrainerLassDana1_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route38_Johto_TrainerLassDana1_DeclinedPhoneNumber:
	goto Johto_Std_NumberDeclinedFScript

Route38_Johto_TrainerLassDana1_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route38_Johto_TrainerLassDana1_PackFull:
	goto Johto_Std_PackFullFScript

Route38_Johto_TrainerSchoolboyChad1::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_CHAD1, Route38_Johto_SchoolboyChad1SeenText, Route38_Johto_SchoolboyChad1BeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_CHAD
	lock
	faceplayer
	goto Route38_Johto_TrainerSchoolboyChad1_Script

Route38_Johto_TrainerSchoolboyChad1_Script:
	goto_if_set FLAG_JOHTO_ENGINE_CHAD_READY_FOR_REMATCH, Route38_Johto_TrainerSchoolboyChad1_ChadRematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route38_Johto_TrainerSchoolboyChad1_HaveChadsNumber
	goto_if_set FLAG_JOHTO_CHAD_ASKED_FOR_PHONE_NUMBER, Route38_Johto_TrainerSchoolboyChad1_SecondTimeAsking
	message Route38_Johto_SchoolboyChadSoManyTestsText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_CHAD_ASKED_FOR_PHONE_NUMBER
	call Route38_Johto_TrainerSchoolboyChad1_AskPhoneNumber1_Sub
	goto Route38_Johto_TrainerSchoolboyChad1_AskToRegisterNumber

Route38_Johto_TrainerSchoolboyChad1_SecondTimeAsking:
	call Route38_Johto_TrainerSchoolboyChad1_AskPhoneNumber2_Sub

Route38_Johto_TrainerSchoolboyChad1_AskToRegisterNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route38_Johto_TrainerSchoolboyChad1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route38_Johto_TrainerSchoolboyChad1_SaidNo
	call Route38_Johto_TrainerSchoolboyChad1_RegisteredChad_Sub
	goto Route38_Johto_TrainerSchoolboyChad1_HaveChadsNumber

Route38_Johto_TrainerSchoolboyChad1_ChadRematch:
	call Route38_Johto_TrainerSchoolboyChad1_Rematch_Sub
	@ TODO unsupported: readmem wChadFightCount
	goto Johto_EventScript_Unimplemented

Route38_Johto_TrainerSchoolboyChad1_HaveChadsNumber:
	goto Johto_Std_NumberAcceptedMScript

Route38_Johto_TrainerSchoolboyChad1_SaidNo:
	goto Johto_Std_NumberDeclinedMScript

Route38_Johto_TrainerSchoolboyChad1_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route38_Johto_TrainerBeautyValerie::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_VALERIE, Route38_Johto_BeautyValerieSeenText, Route38_Johto_BeautyValerieBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_VALERIE
	lock
	faceplayer
	goto Route38_Johto_TrainerBeautyValerie_Script

Route38_Johto_TrainerBeautyValerie_Script:
	message Route38_Johto_BeautyValerieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_TrainerBeautyOlivia::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_OLIVIA, Route38_Johto_BeautyOliviaSeenText, Route38_Johto_BeautyOliviaBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_OLIVIA
	lock
	faceplayer
	goto Route38_Johto_TrainerBeautyOlivia_Script

Route38_Johto_TrainerBeautyOlivia_Script:
	message Route38_Johto_BeautyOliviaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_Route38Sign:
	message Route38_Johto_Route38SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_Route38TrainerTips:
	message Route38_Johto_Route38TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38_Johto_Route38FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_38, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ORAN_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_38
	releaseall
	end

Route38_Johto_TrainerLassDana1_AskNumber1F_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route38_Johto_TrainerLassDana1_AskNumber2F_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route38_Johto_TrainerLassDana1_RegisteredPhoneNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route38_Johto_TrainerLassDana1_Rematch_Sub:
	goto Johto_Std_RematchFScript_Sub

Route38_Johto_TrainerLassDana1_Gift_Sub:
	goto Johto_Std_GiftFScript_Sub

Route38_Johto_TrainerSchoolboyChad1_AskPhoneNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route38_Johto_TrainerSchoolboyChad1_AskPhoneNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route38_Johto_TrainerSchoolboyChad1_RegisteredChad_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route38_Johto_TrainerSchoolboyChad1_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route38_Johto_BirdKeeperTobySeenText:
	.string "Fly high into the\n"
	.string "sky, my beloved\l"
	.string "bird POKéMON!$"

Route38_Johto_BirdKeeperTobyBeatenText:
	.string "I feel like just\n"
	.string "flying away now.$"

Route38_Johto_BirdKeeperTobyAfterBattleText:
	.string "I plan to train in\n"
	.string "CIANWOOD CITY to"
	.string "\pteach my POKéMON\n"
	.string "how to FLY.$"

Route38_Johto_SchoolboyChad1SeenText:
	.string "Let me try some-\n"
	.string "thing I learned\l"
	.string "today.$"

Route38_Johto_SchoolboyChad1BeatenText:
	.string "I didn't study\n"
	.string "enough, I guess.$"

Route38_Johto_SchoolboyChadSoManyTestsText:
	.string "I have to take so\n"
	.string "many tests, I"
	.string "\pdon't have much\n"
	.string "time for POKéMON."
	.string "\pSo when I do get\n"
	.string "to play, I really\l"
	.string "concentrate.$"

Route38_Johto_LassDana1SeenText:
	.string "You seem to be\n"
	.string "good at POKéMON."
	.string "\pIf you are, how\n"
	.string "about giving me\l"
	.string "some advice?$"

Route38_Johto_LassDana1BeatenText:
	.string "I see. So you can\n"
	.string "battle that way.$"

Route38_Johto_LassDanaMoomooMilkText:
	.string "I know something\n"
	.string "good!"
	.string "\pMOOMOO FARM's milk\n"
	.string "is famous for its\l"
	.string "flavor.$"

Route38_Johto_BeautyValerieSeenText:
	.string "Hi! Aren't you a\n"
	.string "cute trainer!"
	.string "\pMay I see your\n"
	.string "POKéMON?$"

Route38_Johto_BeautyValerieBeatenText:
	.string "I'm glad I got to\n"
	.string "see your POKéMON!$"

Route38_Johto_BeautyValerieAfterBattleText:
	.string "When I see POKé-\n"
	.string "MON, it seems to\l"
	.string "soothe my nerves.$"

Route38_Johto_SailorHarrySeenText:
	.string "I've been over-\n"
	.string "seas, so I know"
	.string "\pabout all sorts of\n"
	.string "POKéMON!$"

Route38_Johto_SailorHarryBeatenText:
	.string "Your skill is\n"
	.string "world class!$"

Route38_Johto_SailorHarryAfterBattleText:
	.string "All kinds of peo-\n"
	.string "ple around the"
	.string "\pworld live happily\n"
	.string "with POKéMON.$"

Route38_Johto_BeautyOliviaSeenText:
	.string "Don't you think my\n"
	.string "POKéMON and I are\l"
	.string "beautiful?$"

Route38_Johto_BeautyOliviaBeatenText:
	.string "We drink MOOMOO\n"
	.string "MILK every day.$"

Route38_Johto_BeautyOliviaAfterBattleText:
	.string "MOOMOO MILK is\n"
	.string "good for beauty"
	.string "\pand health, but\n"
	.string "inconveniently,"
	.string "\pthey only sell a\n"
	.string "bottle at a time.$"

Route38_Johto_Route38SignText:
	.string "ROUTE 38"
	.string "\pOLIVINE CITY -\n"
	.string "ECRUTEAK CITY$"

Route38_Johto_Route38TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pIf a POKéMON is\n"
	.string "trying to evolve,\l"
	.string "you can stop it."
	.string "\pPress the B But-\n"
	.string "ton during evolu-\l"
	.string "tion."
	.string "\pThat startles the\n"
	.string "POKéMON and stops\l"
	.string "its evolution.$"
