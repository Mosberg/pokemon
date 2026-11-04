Route45_Johto_MapScripts::
	.byte 0

Route45_Johto_Route45FruitTree_Entry::
	lockall
	goto Route45_Johto_Route45FruitTree

Route45_Johto_Route45Nugget_Entry::
	lockall
	goto Route45_Johto_Route45Nugget

Route45_Johto_Route45Revive_Entry::
	lockall
	goto Route45_Johto_Route45Revive

Route45_Johto_Route45Elixer_Entry::
	lockall
	goto Route45_Johto_Route45Elixer

Route45_Johto_Route45MaxPotion_Entry::
	lockall
	goto Route45_Johto_Route45MaxPotion

Route45_Johto_TrainerCamperQuentin_Entry::
	lockall
	goto Route45_Johto_TrainerCamperQuentin

Route45_Johto_Route45Sign_Entry::
	lockall
	goto Route45_Johto_Route45Sign


Route45_Johto_TrainerBlackbeltKenji::
	trainerbattle_single TRAINER_JOHTO_BLACKBELT_T_KENJI3, Route45_Johto_BlackbeltKenji3SeenText, Route45_Johto_BlackbeltKenji3BeatenText
	setflag FLAG_JOHTO_BEAT_BLACKBELT_KENJI
	lock
	faceplayer
	goto Route45_Johto_TrainerBlackbeltKenji_Script

Route45_Johto_TrainerBlackbeltKenji_Script:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route45_Johto_TrainerBlackbeltKenji_Registered
	goto_if_set FLAG_JOHTO_KENJI_ASKED_FOR_PHONE_NUMBER, Route45_Johto_TrainerBlackbeltKenji_AskedAlready
	@ TODO unsupported: special SampleKenjiBreakCountdown
	goto Johto_EventScript_Unimplemented

Route45_Johto_TrainerBlackbeltKenji_AskedAlready:
	call Route45_Johto_Route45AskNumber2M_Sub

Route45_Johto_TrainerBlackbeltKenji_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route45_Johto_Route45PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route45_Johto_Route45NumberDeclinedM
	call Route45_Johto_Route45RegisteredNumberM_Sub
	goto Route45_Johto_Route45NumberAcceptedM

Route45_Johto_TrainerBlackbeltKenji_Registered:
	@ TODO unsupported: readvar VAR_KENJI_BREAK
	goto Johto_EventScript_Unimplemented

Route45_Johto_Route45NumberAcceptedM:
	goto Johto_Std_NumberAcceptedMScript

Route45_Johto_Route45NumberDeclinedM:
	goto Johto_Std_NumberDeclinedMScript

Route45_Johto_Route45PhoneFullM:
	goto Johto_Std_PhoneFullMScript

Route45_Johto_TrainerHikerErik::
	trainerbattle_single TRAINER_JOHTO_HIKER_ERIK, Route45_Johto_HikerErikSeenText, Route45_Johto_HikerErikBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_ERIK
	lock
	faceplayer
	goto Route45_Johto_TrainerHikerErik_Script

Route45_Johto_TrainerHikerErik_Script:
	message Route45_Johto_HikerErikAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_TrainerHikerMichael::
	trainerbattle_single TRAINER_JOHTO_HIKER_MICHAEL, Route45_Johto_HikerMichaelSeenText, Route45_Johto_HikerMichaelBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_MICHAEL
	lock
	faceplayer
	goto Route45_Johto_TrainerHikerMichael_Script

Route45_Johto_TrainerHikerMichael_Script:
	message Route45_Johto_HikerMichaelAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_TrainerHikerParry::
	trainerbattle_single TRAINER_JOHTO_HIKER_PARRY3, Route45_Johto_HikerParry3SeenText, Route45_Johto_HikerParry3BeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_PARRY
	lock
	faceplayer
	goto Route45_Johto_TrainerHikerParry_Script

Route45_Johto_TrainerHikerParry_Script:
	goto_if_set FLAG_JOHTO_ENGINE_PARRY_READY_FOR_REMATCH, Route45_Johto_TrainerHikerParry_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route45_Johto_Route45NumberAcceptedM
	goto_if_set FLAG_JOHTO_PARRY_ASKED_FOR_PHONE_NUMBER, Route45_Johto_TrainerHikerParry_AskedAlready
	message Route45_Johto_HikerParryAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_PARRY_ASKED_FOR_PHONE_NUMBER
	call Route45_Johto_Route45AskNumber1M_Sub
	goto Route45_Johto_TrainerHikerParry_AskForNumber

Route45_Johto_TrainerHikerParry_AskedAlready:
	call Route45_Johto_Route45AskNumber2M_Sub

Route45_Johto_TrainerHikerParry_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route45_Johto_Route45PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route45_Johto_Route45NumberDeclinedM
	call Route45_Johto_Route45RegisteredNumberM_Sub
	goto Route45_Johto_Route45NumberAcceptedM

Route45_Johto_TrainerHikerParry_WantsBattle:
	call Route45_Johto_Route45RematchM_Sub
	@ TODO unsupported: readmem wParryFightCount
	goto Johto_EventScript_Unimplemented

Route45_Johto_TrainerHikerTimothy::
	trainerbattle_single TRAINER_JOHTO_HIKER_TIMOTHY, Route45_Johto_HikerTimothySeenText, Route45_Johto_HikerTimothyBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_TIMOTHY
	lock
	faceplayer
	goto Route45_Johto_TrainerHikerTimothy_Script

Route45_Johto_TrainerHikerTimothy_Script:
	message Route45_Johto_HikerTimothyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_TrainerCooltrainermRyan::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_RYAN, Route45_Johto_CooltrainermRyanSeenText, Route45_Johto_CooltrainermRyanBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_RYAN
	lock
	faceplayer
	goto Route45_Johto_TrainerCooltrainermRyan_Script

Route45_Johto_TrainerCooltrainermRyan_Script:
	message Route45_Johto_CooltrainermRyanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_TrainerCooltrainerfKelly::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_KELLY, Route45_Johto_CooltrainerfKellySeenText, Route45_Johto_CooltrainerfKellyBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_KELLY
	lock
	faceplayer
	goto Route45_Johto_TrainerCooltrainerfKelly_Script

Route45_Johto_TrainerCooltrainerfKelly_Script:
	message Route45_Johto_CooltrainerfKellyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_TrainerCamperQuentin:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_CAMPER_QUENTIN, Route45_Johto_TrainerCamperQuentin_Defeated
	message Route45_Johto_CamperQuentinSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_QUENTIN, Route45_Johto_CamperQuentinBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_QUENTIN
	closemessage
	releaseall
	end

Route45_Johto_TrainerCamperQuentin_Defeated:
	message Route45_Johto_CamperQuentinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_Route45Sign:
	message Route45_Johto_Route45SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route45_Johto_Route45FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_45, Johto_Std_FruitTreeEmpty
	giveitem ITEM_LEPPA_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_45
	releaseall
	end

Route45_Johto_Route45Nugget:
	finditem ITEM_NUGGET
	releaseall
	end

Route45_Johto_Route45Revive:
	finditem ITEM_REVIVE
	releaseall
	end

Route45_Johto_Route45Elixer:
	finditem ITEM_ELIXER
	releaseall
	end

Route45_Johto_Route45MaxPotion:
	finditem ITEM_MAX_POTION
	releaseall
	end

Route45_Johto_Route45AskNumber1M_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route45_Johto_Route45AskNumber2M_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route45_Johto_Route45RegisteredNumberM_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route45_Johto_Route45RematchM_Sub:
	goto Johto_Std_RematchMScript_Sub

Route45_Johto_HikerErikSeenText:
	.string "Be prepared for\n"
	.string "anything!"
	.string "\pLet me see if your\n"
	.string "POKéMON have been\l"
	.string "raised properly!$"

Route45_Johto_HikerErikBeatenText:
	.string "Oh, I lost that!$"

Route45_Johto_HikerErikAfterBattleText:
	.string "I'll head back to\n"
	.string "BLACKTHORN's ICE"
	.string "\pPATH and train\n"
	.string "some more.$"

Route45_Johto_HikerMichaelSeenText:
	.string "Yo! You're spunky!\n"
	.string "But you know what?"
	.string "\pWhen it comes to\n"
	.string "sheer spunkiness,\l"
	.string "I'm the man!$"

Route45_Johto_HikerMichaelBeatenText:
	.string "My POKéMON weren't\n"
	.string "spunky enough!$"

Route45_Johto_HikerMichaelAfterBattleText:
	.string "Boy, do I love\n"
	.string "HP UP! Mmmm, yum!"
	.string "\pI keep drinking my\n"
	.string "POKéMON's!"
	.string "\pI can't help it!$"

Route45_Johto_HikerParry3SeenText:
	.string "My POKéMON are\n"
	.string "power packed!$"

Route45_Johto_HikerParry3BeatenText:
	.string "Wahahah! I'm the\n"
	.string "big loser!$"

Route45_Johto_HikerParryAfterBattleText:
	.string "I'm not much good\n"
	.string "at thinking, see?"
	.string "\pSo, I just plow\n"
	.string "ahead with power!$"

Route45_Johto_HikerTimothySeenText:
	.string "Why do I climb\n"
	.string "mountains?"
	.string "\pBecause they're\n"
	.string "there."
	.string "\pWhy do I train\n"
	.string "POKéMON?"
	.string "\pBecause they're\n"
	.string "there!$"

Route45_Johto_HikerTimothyBeatenText:
	.string "Losses…\n"
	.string "They're there too!$"

Route45_Johto_HikerTimothyAfterBattleText:
	.string "The best thing to\n"
	.string "ever happen to me"
	.string "\pwas discovering\n"
	.string "POKéMON.$"

Route45_Johto_BlackbeltKenji3SeenText:
	.string "I was training\n"
	.string "here alone."
	.string "\pBehold the fruits\n"
	.string "of my labor!$"

Route45_Johto_BlackbeltKenji3BeatenText:
	.string "Waaaargh!$"

Route45_Johto_CooltrainermRyanSeenText:
	.string "What are your\n"
	.string "thoughts on rais-\l"
	.string "ing POKéMON?$"

Route45_Johto_CooltrainermRyanBeatenText:
	.string "You've won my\n"
	.string "respect.$"

Route45_Johto_CooltrainermRyanAfterBattleText:
	.string "I see you're rais-\n"
	.string "ing your POKéMON\l"
	.string "with care."
	.string "\pThe bond you build\n"
	.string "will save you in\l"
	.string "tough situations.$"

Route45_Johto_CooltrainerfKellySeenText:
	.string "What is your\n"
	.string "battle strategy?"
	.string "\pIt is foolish to\n"
	.string "use strong moves\l"
	.string "indiscriminately.$"

Route45_Johto_CooltrainerfKellyBeatenText:
	.string "Fine. I lost.$"

Route45_Johto_CooltrainerfKellyAfterBattleText:
	.string "I'm not in favor\n"
	.string "of overly power-\l"
	.string "ful moves."
	.string "\pI want to win, but\n"
	.string "I also don't want\l"
	.string "to harm POKéMON.$"

Route45_Johto_CamperQuentinSeenText:
	.string "I'm really, really\n"
	.string "tough!$"

Route45_Johto_CamperQuentinBeatenText:
	.string "I was tough at the\n"
	.string "BATTLE TOWER…$"

Route45_Johto_CamperQuentinAfterBattleText:
	.string "Have you been to\n"
	.string "the BATTLE TOWER?"
	.string "\pI never, ever lose\n"
	.string "there, but…$"

Route45_Johto_Route45SignText:
	.string "ROUTE 45\n"
	.string "MOUNTAIN RD. AHEAD$"
