BluesHouse_Johto_MapScripts::
	.byte 0

BluesHouse_Johto_DaisyScript_Entry::
	lockall
	goto BluesHouse_Johto_DaisyScript


BluesHouse_Johto_DaisyScript:
	faceplayer
	special JohtoGetHour
	goto_if_eq VAR_RESULT, 15, BluesHouse_Johto_DaisyScript_ThreePM
	message BluesHouse_Johto_DaisyHelloText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BluesHouse_Johto_DaisyScript_ThreePM:
	goto_if_set FLAG_JOHTO_ENGINE_DAISYS_GROOMING, BluesHouse_Johto_DaisyScript_AlreadyGroomedMon
	message BluesHouse_Johto_DaisyOfferGroomingText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BluesHouse_Johto_DaisyScript_Refused
	message BluesHouse_Johto_DaisyWhichMonText
	waitmessage
	waitbuttonpress
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BluesHouse_Johto_DaisyScript_Refused
	special JohtoDaisyGrooming
	goto_if_eq VAR_RESULT, 0x0, BluesHouse_Johto_DaisyScript_Refused
	goto_if_eq VAR_RESULT, 0x1, BluesHouse_Johto_DaisyScript_CantGroomEgg
	setflag FLAG_JOHTO_ENGINE_DAISYS_GROOMING
	message BluesHouse_Johto_DaisyAlrightText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	playbgm MUS_HEAL, FALSE
	delay 60
	fadescreen FADE_FROM_WHITE
	fadedefaultbgm
	message BluesHouse_Johto_GroomedMonLooksContentText
	waitmessage
	playmoncry VAR_0x8004, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	message BluesHouse_Johto_DaisyAllDoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BluesHouse_Johto_DaisyScript_AlreadyGroomedMon:
	message BluesHouse_Johto_DaisyAlreadyGroomedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BluesHouse_Johto_DaisyScript_Refused:
	message BluesHouse_Johto_DaisyRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BluesHouse_Johto_DaisyScript_CantGroomEgg:
	message BluesHouse_Johto_DaisyCantGroomEggText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BluesHouse_Johto_DaisyHelloText:
	.string "DAISY: Hi! My kid\n"
	.string "brother is the GYM"
	.string "\pLEADER in VIRIDIAN\n"
	.string "CITY."
	.string "\pBut he goes out\n"
	.string "of town so often,"
	.string "\pit causes problems\n"
	.string "for the trainers.$"

BluesHouse_Johto_DaisyOfferGroomingText:
	.string "DAISY: Hi! Good\n"
	.string "timing. I'm about\l"
	.string "to have some tea."
	.string "\pWould you like to\n"
	.string "join me?"
	.string "\pOh, your POKéMON\n"
	.string "are a bit dirty."
	.string "\pWould you like me\n"
	.string "to groom one?$"

BluesHouse_Johto_DaisyWhichMonText:
	.string "DAISY: Which one\n"
	.string "should I groom?$"

BluesHouse_Johto_DaisyAlrightText:
	.string "DAISY: OK, I'll\n"
	.string "get it looking\l"
	.string "nice in no time.$"

BluesHouse_Johto_GroomedMonLooksContentText:
	.string "{STR_VAR_1} looks\n"
	.string "content.$"

BluesHouse_Johto_DaisyAllDoneText:
	.string "DAISY: There you\n"
	.string "go! All done."
	.string "\pSee? Doesn't it\n"
	.string "look nice?"
	.string "\pIt's such a cute\n"
	.string "POKéMON.$"

BluesHouse_Johto_DaisyAlreadyGroomedText:
	.string "DAISY: I always\n"
	.string "have tea around"
	.string "\pthis time. Come\n"
	.string "join me.$"

BluesHouse_Johto_DaisyRefusedText:
	.string "DAISY: You don't\n"
	.string "want to have one"
	.string "\pgroomed? OK, we'll\n"
	.string "just have tea.$"

BluesHouse_Johto_DaisyCantGroomEggText:
	.string "DAISY: Oh, sorry.\n"
	.string "I honestly can't\l"
	.string "groom an EGG.$"
