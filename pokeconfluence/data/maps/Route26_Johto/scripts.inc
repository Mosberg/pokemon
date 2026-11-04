Route26_Johto_MapScripts::
	.byte 0

Route26_Johto_Route26FruitTree_Entry::
	lockall
	goto Route26_Johto_Route26FruitTree

Route26_Johto_Route26MaxElixer_Entry::
	lockall
	goto Route26_Johto_Route26MaxElixer

Route26_Johto_Route26Sign_Entry::
	lockall
	goto Route26_Johto_Route26Sign


Route26_Johto_TrainerCooltrainermJake::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_JAKE, Route26_Johto_CooltrainermJakeSeenText, Route26_Johto_CooltrainermJakeBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_JAKE
	lock
	faceplayer
	goto Route26_Johto_TrainerCooltrainermJake_Script

Route26_Johto_TrainerCooltrainermJake_Script:
	message Route26_Johto_CooltrainermJakeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26_Johto_TrainerCooltrainermGaven3::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_GAVEN3, Route26_Johto_CooltrainermGaven3SeenText, Route26_Johto_CooltrainermGaven3BeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_GAVEN
	lock
	faceplayer
	goto Route26_Johto_TrainerCooltrainermGaven3_Script

Route26_Johto_TrainerCooltrainermGaven3_Script:
	goto_if_set FLAG_JOHTO_ENGINE_GAVEN_READY_FOR_REMATCH, Route26_Johto_TrainerCooltrainermGaven3_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route26_Johto_TrainerCooltrainermGaven3_NumberAccepted
	goto_if_set FLAG_JOHTO_GAVEN_ASKED_FOR_PHONE_NUMBER, Route26_Johto_TrainerCooltrainermGaven3_AskedAlready
	message Route26_Johto_CooltrainermGavenAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_GAVEN_ASKED_FOR_PHONE_NUMBER
	call Route26_Johto_TrainerCooltrainermGaven3_AskNumber1_Sub
	goto Route26_Johto_TrainerCooltrainermGaven3_AskForNumber

Route26_Johto_TrainerCooltrainermGaven3_AskedAlready:
	call Route26_Johto_TrainerCooltrainermGaven3_AskNumber2_Sub

Route26_Johto_TrainerCooltrainermGaven3_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route26_Johto_TrainerCooltrainermGaven3_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route26_Johto_TrainerCooltrainermGaven3_NumberDeclined
	call Route26_Johto_TrainerCooltrainermGaven3_RegisteredNumber_Sub
	goto Route26_Johto_TrainerCooltrainermGaven3_NumberAccepted

Route26_Johto_TrainerCooltrainermGaven3_WantsBattle:
	call Route26_Johto_TrainerCooltrainermGaven3_Rematch_Sub
	@ TODO unsupported: readmem wGavenFightCount
	goto Johto_EventScript_Unimplemented

Route26_Johto_TrainerCooltrainermGaven3_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route26_Johto_TrainerCooltrainermGaven3_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route26_Johto_TrainerCooltrainermGaven3_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route26_Johto_TrainerCooltrainerfJoyce::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_JOYCE, Route26_Johto_CooltrainerfJoyceSeenText, Route26_Johto_CooltrainerfJoyceBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_JOYCE
	lock
	faceplayer
	goto Route26_Johto_TrainerCooltrainerfJoyce_Script

Route26_Johto_TrainerCooltrainerfJoyce_Script:
	message Route26_Johto_CooltrainerfJoyceAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26_Johto_TrainerCooltrainerfBeth1::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_BETH1, Route26_Johto_CooltrainerfBeth1SeenText, Route26_Johto_CooltrainerfBeth1BeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_BETH
	lock
	faceplayer
	goto Route26_Johto_TrainerCooltrainerfBeth1_Script

Route26_Johto_TrainerCooltrainerfBeth1_Script:
	goto_if_set FLAG_JOHTO_ENGINE_BETH_READY_FOR_REMATCH, Route26_Johto_TrainerCooltrainerfBeth1_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route26_Johto_TrainerCooltrainerfBeth1_NumberAccepted
	goto_if_set FLAG_JOHTO_BETH_ASKED_FOR_PHONE_NUMBER, Route26_Johto_TrainerCooltrainerfBeth1_AskedAlready
	message Route26_Johto_CooltrainerfBethAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_BETH_ASKED_FOR_PHONE_NUMBER
	call Route26_Johto_TrainerCooltrainerfBeth1_AskNumber1_Sub
	goto Route26_Johto_TrainerCooltrainerfBeth1_AskForNumber

Route26_Johto_TrainerCooltrainerfBeth1_AskedAlready:
	call Route26_Johto_TrainerCooltrainerfBeth1_AskNumber2_Sub

Route26_Johto_TrainerCooltrainerfBeth1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route26_Johto_TrainerCooltrainerfBeth1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route26_Johto_TrainerCooltrainerfBeth1_NumberDeclined
	call Route26_Johto_TrainerCooltrainerfBeth1_RegisteredNumber_Sub
	goto Route26_Johto_TrainerCooltrainerfBeth1_NumberAccepted

Route26_Johto_TrainerCooltrainerfBeth1_WantsBattle:
	call Route26_Johto_TrainerCooltrainerfBeth1_Rematch_Sub
	@ TODO unsupported: readmem wBethFightCount
	goto Johto_EventScript_Unimplemented

Route26_Johto_TrainerCooltrainerfBeth1_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route26_Johto_TrainerCooltrainerfBeth1_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

Route26_Johto_TrainerCooltrainerfBeth1_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route26_Johto_TrainerPsychicRichard::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_RICHARD, Route26_Johto_PsychicRichardSeenText, Route26_Johto_PsychicRichardBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_RICHARD
	lock
	faceplayer
	goto Route26_Johto_TrainerPsychicRichard_Script

Route26_Johto_TrainerPsychicRichard_Script:
	message Route26_Johto_PsychicRichardAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26_Johto_TrainerFisherScott::
	trainerbattle_single TRAINER_JOHTO_FISHER_SCOTT, Route26_Johto_FisherScottSeenText, Route26_Johto_FisherScottBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_SCOTT
	lock
	faceplayer
	goto Route26_Johto_TrainerFisherScott_Script

Route26_Johto_TrainerFisherScott_Script:
	message Route26_Johto_FisherScottAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26_Johto_Route26Sign:
	message Route26_Johto_Route26SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26_Johto_Route26FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_26, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ASPEAR_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_26
	releaseall
	end

Route26_Johto_Route26MaxElixer:
	finditem ITEM_MAX_ELIXER
	releaseall
	end

Route26_Johto_TrainerCooltrainermGaven3_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route26_Johto_TrainerCooltrainermGaven3_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route26_Johto_TrainerCooltrainermGaven3_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route26_Johto_TrainerCooltrainermGaven3_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route26_Johto_TrainerCooltrainerfBeth1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route26_Johto_TrainerCooltrainerfBeth1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route26_Johto_TrainerCooltrainerfBeth1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route26_Johto_TrainerCooltrainerfBeth1_Rematch_Sub:
	goto Johto_Std_RematchFScript_Sub

Route26_Johto_CooltrainermJakeSeenText:
	.string "I'm making my\n"
	.string "final preparations"
	.string "\pfor the POKéMON\n"
	.string "LEAGUE.$"

Route26_Johto_CooltrainermJakeBeatenText:
	.string "I blew it!$"

Route26_Johto_CooltrainermJakeAfterBattleText:
	.string "It's going to be\n"
	.string "tough to win at\l"
	.string "the LEAGUE."
	.string "\pI need to do some\n"
	.string "more training."
	.string "\pI hear that the\n"
	.string "LEAGUE's ELITE"
	.string "\pFOUR are tougher\n"
	.string "than GYM LEADERS.$"

Route26_Johto_CooltrainermGaven3SeenText:
	.string "By experiencing\n"
	.string "tough battles, you\l"
	.string "gain power.$"

Route26_Johto_CooltrainermGaven3BeatenText:
	.string "Gaah! Life is even\n"
	.string "tougher!$"

Route26_Johto_CooltrainermGavenAfterText:
	.string "To get to POKéMON\n"
	.string "LEAGUE, you have"
	.string "\pto get through\n"
	.string "VICTORY ROAD."
	.string "\pBut VICTORY ROAD\n"
	.string "is tough."
	.string "\pPractically nobody\n"
	.string "goes there!$"

Route26_Johto_CooltrainerfJoyceSeenText:
	.string "Since you've come\n"
	.string "this far, you must\l"
	.string "be good."
	.string "\pI'm going to give\n"
	.string "this battle every-\l"
	.string "thing I've got!$"

Route26_Johto_CooltrainerfJoyceBeatenText:
	.string "No! I don't\n"
	.string "believe this!$"

Route26_Johto_CooltrainerfJoyceAfterBattleText:
	.string "I've defeated\n"
	.string "eight GYM LEADERS,"
	.string "\pso I was feeling\n"
	.string "confident."
	.string "\pI'll have to try\n"
	.string "harder next time.$"

Route26_Johto_CooltrainerfBeth1SeenText:
	.string "I lost to a train-\n"
	.string "er named SILVER."
	.string "\pHe was really\n"
	.string "strong, but…"
	.string "\pIt was as if he\n"
	.string "absolutely had to\l"
	.string "win at any cost."
	.string "\pI felt sorry for\n"
	.string "his POKéMON.$"

Route26_Johto_CooltrainerfBeth1BeatenText:
	.string "POKéMON aren't\n"
	.string "tools of war.$"

Route26_Johto_CooltrainerfBethAfterText:
	.string "POKéMON are in-\n"
	.string "valuable, lifelong\l"
	.string "partners.$"

Route26_Johto_PsychicRichardSeenText:
	.string "Wow, look at all\n"
	.string "those BADGES!\l"
	.string "I'm impressed."
	.string "\pBut you're not\n"
	.string "satisfied by just"
	.string "\pcollecting them,\n"
	.string "right?$"

Route26_Johto_PsychicRichardBeatenText:
	.string "Good battle!$"

Route26_Johto_PsychicRichardAfterBattleText:
	.string "People and POKéMON\n"
	.string "grow from their\l"
	.string "experiences."
	.string "\pDon't get lazy and\n"
	.string "complacent.$"

Route26_Johto_FisherScottSeenText:
	.string "I'm feeling great\n"
	.string "today!"
	.string "\pI feel like I\n"
	.string "could boot even\l"
	.string "the LEAGUE CHAMP!$"

Route26_Johto_FisherScottBeatenText:
	.string "No! Not in this\n"
	.string "battle!$"

Route26_Johto_FisherScottAfterBattleText:
	.string "Just like in fish-\n"
	.string "ing, it's all over"
	.string "\pin POKéMON if you\n"
	.string "give up.$"

Route26_Johto_Route26SignText:
	.string "ROUTE 26"
	.string "\pPOKéMON LEAGUE\n"
	.string "RECEPTION GATE$"
