NationalPark_Johto_MapScripts::
	.byte 0

NationalPark_Johto_NationalParkLassScript_Entry::
	lockall
	goto NationalPark_Johto_NationalParkLassScript

NationalPark_Johto_NationalParkPokefanFScript_Entry::
	lockall
	goto NationalPark_Johto_NationalParkPokefanFScript

NationalPark_Johto_NationalParkTeacher1Script_Entry::
	lockall
	goto NationalPark_Johto_NationalParkTeacher1Script

NationalPark_Johto_NationalParkYoungster1Script_Entry::
	lockall
	goto NationalPark_Johto_NationalParkYoungster1Script

NationalPark_Johto_NationalParkYoungster2Script_Entry::
	lockall
	goto NationalPark_Johto_NationalParkYoungster2Script

NationalPark_Johto_NationalParkTeacher2Script_Entry::
	lockall
	goto NationalPark_Johto_NationalParkTeacher2Script

NationalPark_Johto_NationalParkPersian_Entry::
	lockall
	goto NationalPark_Johto_NationalParkPersian

NationalPark_Johto_NationalParkParlyzHeal_Entry::
	lockall
	goto NationalPark_Johto_NationalParkParlyzHeal

NationalPark_Johto_NationalParkGameboyKidScript_Entry::
	lockall
	goto NationalPark_Johto_NationalParkGameboyKidScript

NationalPark_Johto_NationalParkTMDig_Entry::
	lockall
	goto NationalPark_Johto_NationalParkTMDig

NationalPark_Johto_NationalParkRelaxationSquareSign_Entry::
	lockall
	goto NationalPark_Johto_NationalParkRelaxationSquareSign

NationalPark_Johto_NationalParkBattleNoticeSign_Entry::
	lockall
	goto NationalPark_Johto_NationalParkBattleNoticeSign

NationalPark_Johto_NationalParkTrainerTipsSign_Entry::
	lockall
	goto NationalPark_Johto_NationalParkTrainerTipsSign


NationalPark_Johto_NationalParkLassScript:
	faceplayer
	message NationalPark_Johto_NationalParkLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkPokefanFScript:
	faceplayer
	message NationalPark_Johto_NationalParkPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkTeacher1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_QUICK_CLAW, NationalPark_Johto_NationalParkTeacher1Script_GotQuickClaw
	message NationalPark_Johto_NationalParkTeacher1Text
	waitmessage
	waitbuttonpress
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, NationalPark_Johto_NationalParkTeacher1Script_NoRoom
	setflag FLAG_JOHTO_GOT_QUICK_CLAW

NationalPark_Johto_NationalParkTeacher1Script_GotQuickClaw:
	message NationalPark_Johto_NationalParkTeacher1Text_GotQuickClaw
	waitmessage
	waitbuttonpress

NationalPark_Johto_NationalParkTeacher1Script_NoRoom:
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkYoungster1Script:
	faceplayer
	message NationalPark_Johto_NationalParkYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkYoungster2Script:
	faceplayer
	message NationalPark_Johto_NationalParkYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkTeacher2Script:
	faceplayer
	message NationalPark_Johto_NationalParkTeacher2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkPersian:
	faceplayer
	message NationalPark_Johto_NationalParkPersianText
	waitmessage
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkGameboyKidScript:
	faceplayer
	message NationalPark_Johto_NationalParkGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 13, Johto_Movement_Face_Down
	waitmovement 13
	releaseall
	end

NationalPark_Johto_TrainerSchoolboyJack1::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_JACK1, NationalPark_Johto_SchoolboyJack1SeenText, NationalPark_Johto_SchoolboyJack1BeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_JACK
	lock
	faceplayer
	goto NationalPark_Johto_TrainerSchoolboyJack1_Script

NationalPark_Johto_TrainerSchoolboyJack1_Script:
	goto_if_set FLAG_JOHTO_ENGINE_JACK_READY_FOR_REMATCH, NationalPark_Johto_TrainerSchoolboyJack1_Rematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, NationalPark_Johto_TrainerSchoolboyJack1_NumberAccepted
	goto_if_set FLAG_JOHTO_JACK_ASKED_FOR_PHONE_NUMBER, NationalPark_Johto_TrainerSchoolboyJack1_AskAgain
	message NationalPark_Johto_SchoolboyJackTradeMonText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_JACK_ASKED_FOR_PHONE_NUMBER
	call NationalPark_Johto_TrainerSchoolboyJack1_AskNumber1_Sub
	goto NationalPark_Johto_TrainerSchoolboyJack1_RequestNumber

NationalPark_Johto_TrainerSchoolboyJack1_AskAgain:
	call NationalPark_Johto_TrainerSchoolboyJack1_AskNumber2_Sub

NationalPark_Johto_TrainerSchoolboyJack1_RequestNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, NationalPark_Johto_TrainerSchoolboyJack1_PhoneFull
	goto_if_eq VAR_RESULT, 2, NationalPark_Johto_TrainerSchoolboyJack1_NumberDeclined
	call NationalPark_Johto_TrainerSchoolboyJack1_RegisteredNumber_Sub
	goto NationalPark_Johto_TrainerSchoolboyJack1_NumberAccepted

NationalPark_Johto_TrainerSchoolboyJack1_Rematch:
	call NationalPark_Johto_TrainerSchoolboyJack1_RematchStd_Sub
	@ TODO unsupported: readmem wJackFightCount
	goto Johto_EventScript_Unimplemented

NationalPark_Johto_TrainerSchoolboyJack1_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

NationalPark_Johto_TrainerSchoolboyJack1_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

NationalPark_Johto_TrainerSchoolboyJack1_PhoneFull:
	goto Johto_Std_PhoneFullMScript

NationalPark_Johto_TrainerPokefanmWilliam::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_WILLIAM, NationalPark_Johto_PokefanmWilliamSeenText, NationalPark_Johto_PokefanmWilliamBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_WILLIAM
	lock
	faceplayer
	goto NationalPark_Johto_TrainerPokefanmWilliam_Script

NationalPark_Johto_TrainerPokefanmWilliam_Script:
	message NationalPark_Johto_PokefanmWilliamAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_TrainerPokefanfBeverly1::
	trainerbattle_single TRAINER_JOHTO_POKEFANF_BEVERLY1, NationalPark_Johto_PokefanfBeverly1SeenText, NationalPark_Johto_PokefanfBeverly1BeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANF_BEVERLY
	lock
	faceplayer
	goto NationalPark_Johto_TrainerPokefanfBeverly1_Script

NationalPark_Johto_TrainerPokefanfBeverly1_Script:
	goto_if_set FLAG_JOHTO_ENGINE_BEVERLY_HAS_NUGGET, NationalPark_Johto_TrainerPokefanfBeverly1_GiveNugget
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, NationalPark_Johto_TrainerPokefanfBeverly1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, NationalPark_Johto_TrainerPokefanfBeverly1_NoMarill
	goto_if_set FLAG_JOHTO_BEVERLY_ASKED_FOR_PHONE_NUMBER, NationalPark_Johto_TrainerPokefanfBeverly1_AskAgain
	message NationalPark_Johto_PokefanBeverlyCuteMonText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_BEVERLY_ASKED_FOR_PHONE_NUMBER
	call NationalPark_Johto_TrainerPokefanfBeverly1_AskNumber1_Sub
	goto NationalPark_Johto_TrainerPokefanfBeverly1_RequestNumber

NationalPark_Johto_TrainerPokefanfBeverly1_AskAgain:
	call NationalPark_Johto_TrainerPokefanfBeverly1_AskNumber2_Sub

NationalPark_Johto_TrainerPokefanfBeverly1_RequestNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, NationalPark_Johto_TrainerPokefanfBeverly1_PhoneFull
	goto_if_eq VAR_RESULT, 2, NationalPark_Johto_TrainerPokefanfBeverly1_NumberDeclined
	call NationalPark_Johto_TrainerPokefanfBeverly1_RegisteredNumber_Sub
	goto NationalPark_Johto_TrainerPokefanfBeverly1_NumberAccepted

NationalPark_Johto_TrainerPokefanfBeverly1_GiveNugget:
	call NationalPark_Johto_TrainerPokefanfBeverly1_Gift_Sub
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, NationalPark_Johto_TrainerPokefanfBeverly1_NoRoom
	clearflag FLAG_JOHTO_ENGINE_BEVERLY_HAS_NUGGET
	goto NationalPark_Johto_TrainerPokefanfBeverly1_NumberAccepted

NationalPark_Johto_TrainerPokefanfBeverly1_NoRoom:
	goto NationalPark_Johto_TrainerPokefanfBeverly1_PackFull

NationalPark_Johto_TrainerPokefanfBeverly1_NoMarill:
	message NationalPark_Johto_PokefanFBeverlyMarillFriendText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_TrainerPokefanfBeverly1_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

NationalPark_Johto_TrainerPokefanfBeverly1_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

NationalPark_Johto_TrainerPokefanfBeverly1_PhoneFull:
	goto Johto_Std_PhoneFullFScript

NationalPark_Johto_TrainerPokefanfBeverly1_PackFull:
	goto Johto_Std_PackFullFScript

NationalPark_Johto_TrainerLassKrise::
	trainerbattle_single TRAINER_JOHTO_LASS_KRISE, NationalPark_Johto_LassKriseSeenText, NationalPark_Johto_LassKriseBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_KRISE
	lock
	faceplayer
	goto NationalPark_Johto_TrainerLassKrise_Script

NationalPark_Johto_TrainerLassKrise_Script:
	message NationalPark_Johto_LassKriseAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkRelaxationSquareSign:
	message NationalPark_Johto_NationalParkRelaxationSquareText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkBattleNoticeSign:
	message NationalPark_Johto_NationalParkBattleNoticeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkTrainerTipsSign:
	message NationalPark_Johto_NationalParkTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NationalPark_Johto_NationalParkParlyzHeal:
	finditem ITEM_PARLYZ_HEAL
	releaseall
	end

NationalPark_Johto_NationalParkTMDig:
	finditem ITEM_TM_DIG
	releaseall
	end

NationalPark_Johto_TrainerSchoolboyJack1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

NationalPark_Johto_TrainerSchoolboyJack1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

NationalPark_Johto_TrainerSchoolboyJack1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

NationalPark_Johto_TrainerSchoolboyJack1_RematchStd_Sub:
	goto Johto_Std_RematchMScript_Sub

NationalPark_Johto_TrainerPokefanfBeverly1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

NationalPark_Johto_TrainerPokefanfBeverly1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

NationalPark_Johto_TrainerPokefanfBeverly1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

NationalPark_Johto_TrainerPokefanfBeverly1_Gift_Sub:
	goto Johto_Std_GiftFScript_Sub

NationalPark_Johto_NationalParkLassText:
	.string "Look! Check out my\n"
	.string "bag!"
	.string "\pI printed out my\n"
	.string "favorites from my"
	.string "\pPOKéDEX and stuck\n"
	.string "them on my bag.$"

NationalPark_Johto_NationalParkPokefanFText:
	.string "This is MAIL I got\n"
	.string "from my daughter.\l"
	.string "It cheers me up.$"

NationalPark_Johto_NationalParkTeacher1Text:
	.string "Pay attention,\n"
	.string "please!"
	.string "\p…Oops, I have to\n"
	.string "quit thinking like"
	.string "\pa teacher all the\n"
	.string "time."
	.string "\pYou must be a\n"
	.string "POKéMON trainer."
	.string "\pSince you're work-\n"
	.string "ing so hard, I"
	.string "\pwant you to have\n"
	.string "this.$"

NationalPark_Johto_NationalParkTeacher1Text_GotQuickClaw:
	.string "Let a POKéMON hold\n"
	.string "that QUICK CLAW."
	.string "\pSometimes it will\n"
	.string "strike first\l"
	.string "during battle.$"

NationalPark_Johto_NationalParkYoungster1Text:
	.string "I'm playing with\n"
	.string "stickers I printed\l"
	.string "from my POKéDEX.$"

NationalPark_Johto_NationalParkYoungster2Text:
	.string "I get the other\n"
	.string "guy's POKéDEX\l"
	.string "sticker if I win.$"

NationalPark_Johto_NationalParkTeacher2Text:
	.string "I take walks in\n"
	.string "the PARK, but I"
	.string "\pnever go into the\n"
	.string "grass."
	.string "\pTrainers always\n"
	.string "want to battle…$"

NationalPark_Johto_NationalParkPersianText:
	.string "PERSIAN: Fufushaa!$"

NationalPark_Johto_NationalParkGameboyKidText:
	.string "I'm printing out\n"
	.string "my POKéDEX."
	.string "\pYou can also print\n"
	.string "out stuff like"
	.string "\pMAIL and your PC\n"
	.string "BOXES.$"

NationalPark_Johto_SchoolboyJack1SeenText:
	.string "The world of\n"
	.string "POKéMON is deep."
	.string "\pThere are still\n"
	.string "lots of things we\l"
	.string "don't know."
	.string "\pBut I know more\n"
	.string "than you do!$"

NationalPark_Johto_SchoolboyJack1BeatenText:
	.string "Wha-wha-what?$"

NationalPark_Johto_SchoolboyJackTradeMonText:
	.string "(text not converted)$"

NationalPark_Johto_PokefanfBeverly1SeenText:
	.string "My POKéMON are\n"
	.string "simply darling."
	.string "\pLet me tell you\n"
	.string "how proud my\l"
	.string "darlings make me.$"

NationalPark_Johto_PokefanfBeverly1BeatenText:
	.string "I can beat you in\n"
	.string "pride, but…$"

NationalPark_Johto_PokefanBeverlyCuteMonText:
	.string "I must say, your\n"
	.string "POKéMON are quite\l"
	.string "cute, too.$"

NationalPark_Johto_PokefanmWilliamSeenText:
	.string "We adore our POKé-\n"
	.string "MON, even if they\l"
	.string "dislike us."
	.string "\pThat's what being\n"
	.string "a FAN is about.$"

NationalPark_Johto_PokefanmWilliamBeatenText:
	.string "M-my POKéMON!$"

NationalPark_Johto_PokefanmWilliamAfterBattleText:
	.string "I lost the battle,\n"
	.string "but my POKéMON win"
	.string "\pthe prize for\n"
	.string "being most lovely.$"

NationalPark_Johto_PokefanFBeverlyMarillFriendText:
	.string "My friend keeps a\n"
	.string "MARILL!"
	.string "\pI find them very\n"
	.string "endearing."
	.string "\pOh, I wish for a\n"
	.string "MARILL of my own…$"

NationalPark_Johto_LassKriseSeenText:
	.string "Hello? Why are you\n"
	.string "staring at me?"
	.string "\pOh, a battle?$"

NationalPark_Johto_LassKriseBeatenText:
	.string "…Hmmm…$"

NationalPark_Johto_LassKriseAfterBattleText:
	.string "I thought you were\n"
	.string "staring at me\l"
	.string "because I'm cute!$"

NationalPark_Johto_NationalParkRelaxationSquareText:
	.string "RELAXATION SQUARE\n"
	.string "NATIONAL PARK$"

NationalPark_Johto_NationalParkBattleNoticeText:
	.string "What is this\n"
	.string "notice?"
	.string "\pPlease battle only\n"
	.string "in the grass."
	.string "\pNATIONAL PARK\n"
	.string "WARDEN'S OFFICE$"

NationalPark_Johto_NationalParkTrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pPrint out MAIL by\n"
	.string "opening it then\l"
	.string "pressing START.$"
