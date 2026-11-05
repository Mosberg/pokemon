Route39_Johto_MapScripts::
	.byte 0

Route39_Johto_Route39Miltank_Entry::
	lockall
	goto Route39_Johto_Route39Miltank

Route39_Johto_Route39FruitTree_Entry::
	lockall
	goto Route39_Johto_Route39FruitTree

Route39_Johto_TrainerPokefanfJaime_Entry::
	lockall
	goto Route39_Johto_TrainerPokefanfJaime

Route39_Johto_Route39TrainerTips_Entry::
	lockall
	goto Route39_Johto_Route39TrainerTips

Route39_Johto_MoomooFarmSign_Entry::
	lockall
	goto Route39_Johto_MoomooFarmSign

Route39_Johto_Route39Sign_Entry::
	lockall
	goto Route39_Johto_Route39Sign


Route39_Johto_Route39Miltank:
	message Route39_Johto_Route39MiltankText
	waitmessage
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerPokefanmDerek::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_DEREK1, Route39_Johto_PokefanmDerekSeenText, Route39_Johto_PokefanmDerekBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_DEREK
	lock
	faceplayer
	goto Route39_Johto_TrainerPokefanmDerek_Script

Route39_Johto_TrainerPokefanmDerek_Script:
	setvar VAR_0x8007, 1009
	goto_if_set FLAG_JOHTO_ENGINE_DEREK_HAS_NUGGET, Route39_Johto_TrainerPokefanmDerek_HasNugget
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_POKEFANM_DEREK_REGISTERED
	setvar VAR_0x8005, 0
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route39_Johto_TrainerPokefanmDerek_NumberAccepted
	setvar VAR_0x8004, SPECIES_PIKACHU
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, 0, Route39_Johto_TrainerPokefanmDerek_WantsPikachu
	goto_if_set FLAG_JOHTO_DEREK_ASKED_FOR_PHONE_NUMBER, Route39_Johto_TrainerPokefanmDerek_AskedAlready
	message Route39_Johto_PokefanMDerekText_NotBragging
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_DEREK_ASKED_FOR_PHONE_NUMBER
	call Route39_Johto_TrainerPokefanmDerek_AskNumber1_Sub
	goto Route39_Johto_TrainerPokefanmDerek_AskForNumber

Route39_Johto_TrainerPokefanmDerek_AskedAlready:
	call Route39_Johto_TrainerPokefanmDerek_AskNumber2_Sub

Route39_Johto_TrainerPokefanmDerek_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_POKEFANM_DEREK_REGISTERED
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_DEREK_HAS_NUGGET
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route39_Johto_TrainerPokefanmDerek_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route39_Johto_TrainerPokefanmDerek_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_POKEFANM_DEREK1
	call Route39_Johto_TrainerPokefanmDerek_RegisteredNumber_Sub
	goto Route39_Johto_TrainerPokefanmDerek_NumberAccepted

Route39_Johto_TrainerPokefanmDerek_HasNugget:
	call Route39_Johto_TrainerPokefanmDerek_Gift_Sub
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, Route39_Johto_TrainerPokefanmDerek_NoRoom
	clearflag FLAG_JOHTO_ENGINE_DEREK_HAS_NUGGET
	goto Route39_Johto_TrainerPokefanmDerek_NumberAccepted

Route39_Johto_TrainerPokefanmDerek_NoRoom:
	goto Route39_Johto_TrainerPokefanmDerek_PackFull

Route39_Johto_TrainerPokefanmDerek_WantsPikachu:
	message Route39_Johto_PokefanMDerekPikachuIsItText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerPokefanmDerek_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route39_Johto_TrainerPokefanmDerek_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route39_Johto_TrainerPokefanmDerek_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route39_Johto_TrainerPokefanmDerek_PackFull:
	goto Johto_Std_PackFullMScript

Route39_Johto_TrainerPokefanfRuth::
	trainerbattle_single TRAINER_JOHTO_POKEFANF_RUTH, Route39_Johto_PokefanfRuthSeenText, Route39_Johto_PokefanfRuthBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANF_RUTH
	lock
	faceplayer
	goto Route39_Johto_TrainerPokefanfRuth_Script

Route39_Johto_TrainerPokefanfRuth_Script:
	message Route39_Johto_PokefanfRuthAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerSailorEugene::
	trainerbattle_single TRAINER_JOHTO_SAILOR_EUGENE, Route39_Johto_SailorEugeneSeenText, Route39_Johto_SailorEugeneBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_EUGENE
	lock
	faceplayer
	goto Route39_Johto_TrainerSailorEugene_Script

Route39_Johto_TrainerSailorEugene_Script:
	message Route39_Johto_SailorEugeneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerPsychicNorman::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_NORMAN, Route39_Johto_PsychicNormanSeenText, Route39_Johto_PsychicNormanBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_NORMAN
	lock
	faceplayer
	goto Route39_Johto_TrainerPsychicNorman_Script

Route39_Johto_TrainerPsychicNorman_Script:
	message Route39_Johto_PsychicNormanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerPokefanfJaime:
	faceplayer
	setvar VAR_0x8004, 4
	special JohtoCheckTime
	goto_if_eq VAR_RESULT, 0, Route39_Johto_TrainerPokefanfJaime_NotNight
	goto_if_set FLAG_JOHTO_BEAT_POKEFANF_JAIME, Route39_Johto_TrainerPokefanfJaime_Beaten
	message Route39_Johto_PokefanfJaimeSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_POKEFANF_JAIME, Route39_Johto_PokefanfJaimeBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANF_JAIME
	closemessage
	releaseall
	end

Route39_Johto_TrainerPokefanfJaime_Beaten:
	message Route39_Johto_PokefanfJaimeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_TrainerPokefanfJaime_NotNight:
	message Route39_Johto_PokefanfJaimeHopeItGetsDarkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_Route39Sign:
	message Route39_Johto_Route39SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_MoomooFarmSign:
	message Route39_Johto_MoomooFarmSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_Route39TrainerTips:
	message Route39_Johto_Route39TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39_Johto_Route39FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_39, Johto_Std_FruitTreeEmpty
	giveitem ITEM_LUM_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_39
	releaseall
	end

Route39_Johto_TrainerPokefanmDerek_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route39_Johto_TrainerPokefanmDerek_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route39_Johto_TrainerPokefanmDerek_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route39_Johto_TrainerPokefanmDerek_Gift_Sub:
	goto Johto_Std_GiftMScript_Sub

Route39_Johto_Route39MiltankText:
	.string "MILTANK: Mooo!$"

Route39_Johto_SailorEugeneSeenText:
	.string "I just got back to\n"
	.string "OLIVINE."
	.string "\pSo how about a\n"
	.string "POKéMON battle?$"

Route39_Johto_SailorEugeneBeatenText:
	.string "Awaaargh!$"

Route39_Johto_SailorEugeneAfterBattleText:
	.string "My POKéMON were\n"
	.string "caught and raised\l"
	.string "overseas."
	.string "\pThey're my compan-\n"
	.string "ions on those long\l"
	.string "voyages.$"

Route39_Johto_PokefanmDerekSeenText:
	.string "This is a good\n"
	.string "time to brag about\l"
	.string "my PIKACHU!$"

Route39_Johto_PokefanmDerekBeatenText:
	.string "I had no time to\n"
	.string "show off PIKACHU…$"

Route39_Johto_PokefanMDerekText_NotBragging:
	.string "I'm not listening\n"
	.string "to your bragging!"
	.string "\pWe POKé FANS have\n"
	.string "a policy of not"
	.string "\plistening to other\n"
	.string "people brag!$"

Route39_Johto_PokefanfRuthSeenText:
	.string "Such darling\n"
	.string "POKéMON."
	.string "\pLet's show our\n"
	.string "POKéMON together\l"
	.string "at the same time.$"

Route39_Johto_PokefanfRuthBeatenText:
	.string "I don't mind\n"
	.string "losing.$"

Route39_Johto_PokefanfRuthAfterBattleText:
	.string "Do you know about\n"
	.string "baby POKéMON?"
	.string "\pI bet they're just\n"
	.string "adorable!$"

Route39_Johto_PokefanMDerekPikachuIsItText:
	.string "PIKACHU is it!\n"
	.string "Don't you agree?$"

Route39_Johto_PsychicNormanSeenText:
	.string "Let me see what\n"
	.string "your POKéMON are\l"
	.string "capable of.$"

Route39_Johto_PsychicNormanBeatenText:
	.string "Ooh, your POKéMON\n"
	.string "have potential.$"

Route39_Johto_PsychicNormanAfterBattleText:
	.string "You know how POKé-\n"
	.string "MON have different\l"
	.string "abilities?"
	.string "\pPeople are like\n"
	.string "that too. Every-\l"
	.string "one has different\l"
	.string "potential.$"

Route39_Johto_PokefanfJaimeHopeItGetsDarkText:
	.string "Ufufufu… I hope it\n"
	.string "gets dark soon.$"

Route39_Johto_PokefanfJaimeSeenText:
	.string "You came at just\n"
	.string "the right time."
	.string "\pLet's battle.$"

Route39_Johto_PokefanfJaimeBeatenText:
	.string "Oh, how disap-\n"
	.string "pointing…$"

Route39_Johto_PokefanfJaimeAfterBattleText:
	.string "I met my MEOWTH at\n"
	.string "night, right here\l"
	.string "on ROUTE 39."
	.string "\pI'm not sure why,\n"
	.string "but it seems to"
	.string "\plike it when I\n"
	.string "train here."
	.string "\pIt seems to become\n"
	.string "friendlier by"
	.string "\ptraining here than\n"
	.string "anywhere else.$"

Route39_Johto_Route39SignText:
	.string "ROUTE 39"
	.string "\pOLIVINE CITY -\n"
	.string "ECRUTEAK CITY$"

Route39_Johto_MoomooFarmSignText:
	.string "MOOMOO FARM"
	.string "\pEnjoy Our Fresh\n"
	.string "and Tasty Milk$"

Route39_Johto_Route39TrainerTipsText:
	.string "TRAINER TIPS"
	.string "\pUse HEADBUTT on\n"
	.string "trees to shake\l"
	.string "POKéMON out."
	.string "\pDifferent kinds of\n"
	.string "POKéMON drop out\l"
	.string "of trees."
	.string "\pUse HEADBUTT on\n"
	.string "any tree you see!$"
