Route44_Johto_MapScripts::
	.byte 0

Route44_Johto_Route44FruitTree_Entry::
	lockall
	goto Route44_Johto_Route44FruitTree

Route44_Johto_Route44MaxRevive_Entry::
	lockall
	goto Route44_Johto_Route44MaxRevive

Route44_Johto_Route44UltraBall_Entry::
	lockall
	goto Route44_Johto_Route44UltraBall

Route44_Johto_Route44MaxRepel_Entry::
	lockall
	goto Route44_Johto_Route44MaxRepel

Route44_Johto_Route44Sign1_Entry::
	lockall
	goto Route44_Johto_Route44Sign1

Route44_Johto_Route44Sign2_Entry::
	lockall
	goto Route44_Johto_Route44Sign2


Route44_Johto_TrainerBirdKeeperVance1::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_VANCE1, Route44_Johto_BirdKeeperVance1SeenText, Route44_Johto_BirdKeeperVance1BeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_VANCE
	lock
	faceplayer
	goto Route44_Johto_TrainerBirdKeeperVance1_Script

Route44_Johto_TrainerBirdKeeperVance1_Script:
	setvar VAR_0x8007, 917
	goto_if_set FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH, Route44_Johto_TrainerBirdKeeperVance1_WantsBattle
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BIRDKEEPER_VANCE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route44_Johto_Route44NumberAcceptedM
	goto_if_set FLAG_JOHTO_VANCE_ASKED_FOR_PHONE_NUMBER, Route44_Johto_TrainerBirdKeeperVance1_AskedAlready
	message Route44_Johto_BirdKeeperVanceLegendaryBirdsText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_VANCE_ASKED_FOR_PHONE_NUMBER
	call Route44_Johto_Route44AskNumber1M_Sub
	goto Route44_Johto_TrainerBirdKeeperVance1_AskForNumber

Route44_Johto_TrainerBirdKeeperVance1_AskedAlready:
	call Route44_Johto_Route44AskNumber2M_Sub

Route44_Johto_TrainerBirdKeeperVance1_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BIRDKEEPER_VANCE_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route44_Johto_Route44PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route44_Johto_Route44NumberDeclinedM
	buffertrainername STR_VAR_1, TRAINER_JOHTO_BIRD_KEEPER_VANCE1
	call Route44_Johto_Route44RegisteredNumberM_Sub
	goto Route44_Johto_Route44NumberAcceptedM

Route44_Johto_TrainerBirdKeeperVance1_WantsBattle:
	call Route44_Johto_Route44RematchM_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WVANCEFIGHTCOUNT
	goto_if_eq VAR_RESULT, 2, Route44_Johto_TrainerBirdKeeperVance1_Fight2
	goto_if_eq VAR_RESULT, 1, Route44_Johto_TrainerBirdKeeperVance1_Fight1
	goto_if_eq VAR_RESULT, 0, Route44_Johto_TrainerBirdKeeperVance1_LoadFight0

Route44_Johto_TrainerBirdKeeperVance1_Fight2:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route44_Johto_TrainerBirdKeeperVance1_LoadFight2

Route44_Johto_TrainerBirdKeeperVance1_Fight1:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route44_Johto_TrainerBirdKeeperVance1_LoadFight1

Route44_Johto_TrainerBirdKeeperVance1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_BIRD_KEEPER_VANCE1, Route44_Johto_BirdKeeperVance1BeatenText
	setvar VAR_JOHTO_MEM_WVANCEFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH
	releaseall
	end

Route44_Johto_TrainerBirdKeeperVance1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_BIRD_KEEPER_VANCE2, Route44_Johto_BirdKeeperVance1BeatenText
	setvar VAR_JOHTO_MEM_WVANCEFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH
	releaseall
	end

Route44_Johto_TrainerBirdKeeperVance1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_BIRD_KEEPER_VANCE3, Route44_Johto_BirdKeeperVance1BeatenText
	clearflag FLAG_JOHTO_ENGINE_VANCE_READY_FOR_REMATCH
	goto_if_set FLAG_JOHTO_VANCE_CARBOS, Route44_Johto_TrainerBirdKeeperVance1_Carbos
	goto_if_set FLAG_JOHTO_GOT_CARBOS_FROM_VANCE, Route44_Johto_TrainerBirdKeeperVance1_ReceivedCarbosBefore
	call Route44_Johto_Route44RematchGiftM_Sub
	giveitem ITEM_CARBOS
	goto_if_eq VAR_RESULT, 0, Route44_Johto_VancePackFull
	setflag FLAG_JOHTO_GOT_CARBOS_FROM_VANCE
	goto Route44_Johto_Route44NumberAcceptedM

Route44_Johto_TrainerBirdKeeperVance1_ReceivedCarbosBefore:
	releaseall
	end

Route44_Johto_TrainerBirdKeeperVance1_Carbos:
	message Route44_Johto_BirdKeeperVance2BeatenText
	waitmessage
	waitbuttonpress
	giveitem ITEM_CARBOS
	goto_if_eq VAR_RESULT, 0, Route44_Johto_VancePackFull
	clearflag FLAG_JOHTO_VANCE_CARBOS
	setflag FLAG_JOHTO_GOT_CARBOS_FROM_VANCE
	goto Route44_Johto_Route44NumberAcceptedM

Route44_Johto_Route44NumberAcceptedM:
	goto Johto_Std_NumberAcceptedMScript

Route44_Johto_Route44NumberDeclinedM:
	goto Johto_Std_NumberDeclinedMScript

Route44_Johto_Route44PhoneFullM:
	goto Johto_Std_PhoneFullMScript

Route44_Johto_Route44PackFullM:
	goto Johto_Std_PackFullMScript

Route44_Johto_VancePackFull:
	setflag FLAG_JOHTO_VANCE_CARBOS
	goto Johto_Std_PackFullMScript

Route44_Johto_TrainerPsychicPhil::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_PHIL, Route44_Johto_PsychicPhilSeenText, Route44_Johto_PsychicPhilBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_PHIL
	lock
	faceplayer
	goto Route44_Johto_TrainerPsychicPhil_Script

Route44_Johto_TrainerPsychicPhil_Script:
	message Route44_Johto_PsychicPhilAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_TrainerFisherWilton1::
	trainerbattle_single TRAINER_JOHTO_FISHER_WILTON1, Route44_Johto_FisherWilton1SeenText, Route44_Johto_FisherWilton1BeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_WILTON
	lock
	faceplayer
	goto Route44_Johto_TrainerFisherWilton1_Script

Route44_Johto_TrainerFisherWilton1_Script:
	setvar VAR_0x8007, 992
	goto_if_set FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH, Route44_Johto_TrainerFisherWilton1_WantsBattle
	goto_if_set FLAG_JOHTO_ENGINE_WILTON_HAS_ITEM, Route44_Johto_TrainerFisherWilton1_HasItem
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_FISHER_WILTON_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route44_Johto_Route44NumberAcceptedM
	goto_if_set FLAG_JOHTO_WILTON_ASKED_FOR_PHONE_NUMBER, Route44_Johto_TrainerFisherWilton1_AskedAlready
	message Route44_Johto_FisherWiltonHugePoliwagText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_WILTON_ASKED_FOR_PHONE_NUMBER
	call Route44_Johto_Route44AskNumber1M_Sub
	goto Route44_Johto_TrainerFisherWilton1_AskForNumber

Route44_Johto_TrainerFisherWilton1_AskedAlready:
	call Route44_Johto_Route44AskNumber2M_Sub

Route44_Johto_TrainerFisherWilton1_AskForNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_FISHER_WILTON_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_WILTON_HAS_ITEM
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route44_Johto_Route44PhoneFullM
	goto_if_eq VAR_RESULT, 2, Route44_Johto_Route44NumberDeclinedM
	buffertrainername STR_VAR_1, TRAINER_JOHTO_FISHER_WILTON1
	call Route44_Johto_Route44RegisteredNumberM_Sub
	goto Route44_Johto_Route44NumberAcceptedM

Route44_Johto_TrainerFisherWilton1_WantsBattle:
	call Route44_Johto_Route44RematchM_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WWILTONFIGHTCOUNT
	goto_if_eq VAR_RESULT, 2, Route44_Johto_TrainerFisherWilton1_Fight2
	goto_if_eq VAR_RESULT, 1, Route44_Johto_TrainerFisherWilton1_Fight1
	goto_if_eq VAR_RESULT, 0, Route44_Johto_TrainerFisherWilton1_LoadFight0

Route44_Johto_TrainerFisherWilton1_Fight2:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route44_Johto_TrainerFisherWilton1_LoadFight2

Route44_Johto_TrainerFisherWilton1_Fight1:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route44_Johto_TrainerFisherWilton1_LoadFight1

Route44_Johto_TrainerFisherWilton1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_WILTON1, Route44_Johto_FisherWilton1BeatenText
	setvar VAR_JOHTO_MEM_WWILTONFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH
	releaseall
	end

Route44_Johto_TrainerFisherWilton1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_WILTON2, Route44_Johto_FisherWilton1BeatenText
	setvar VAR_JOHTO_MEM_WWILTONFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH
	releaseall
	end

Route44_Johto_TrainerFisherWilton1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_FISHER_WILTON3, Route44_Johto_FisherWilton1BeatenText
	clearflag FLAG_JOHTO_ENGINE_WILTON_READY_FOR_REMATCH
	releaseall
	end

Route44_Johto_TrainerFisherWilton1_HasItem:
	call Route44_Johto_Route44GiftM_Sub
	goto_if_set FLAG_JOHTO_WILTON_HAS_ULTRA_BALL, Route44_Johto_TrainerFisherWilton1_UltraBall
	goto_if_set FLAG_JOHTO_WILTON_HAS_GREAT_BALL, Route44_Johto_TrainerFisherWilton1_GreatBall
	goto_if_set FLAG_JOHTO_WILTON_HAS_POKE_BALL, Route44_Johto_TrainerFisherWilton1_PokeBall

Route44_Johto_TrainerFisherWilton1_UltraBall:
	giveitem ITEM_ULTRA_BALL
	goto_if_eq VAR_RESULT, 0, Route44_Johto_TrainerFisherWilton1_Route44PackFullM
	goto Route44_Johto_TrainerFisherWilton1_ItemReceived

Route44_Johto_TrainerFisherWilton1_GreatBall:
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, 0, Route44_Johto_TrainerFisherWilton1_Route44PackFullM
	goto Route44_Johto_TrainerFisherWilton1_ItemReceived

Route44_Johto_TrainerFisherWilton1_PokeBall:
	giveitem ITEM_POKE_BALL
	goto_if_eq VAR_RESULT, 0, Route44_Johto_TrainerFisherWilton1_Route44PackFullM

Route44_Johto_TrainerFisherWilton1_ItemReceived:
	clearflag FLAG_JOHTO_ENGINE_WILTON_HAS_ITEM
	goto Route44_Johto_Route44NumberAcceptedM

Route44_Johto_TrainerFisherWilton1_Route44PackFullM:
	goto Route44_Johto_Route44PackFullM

Route44_Johto_TrainerFisherEdgar::
	trainerbattle_single TRAINER_JOHTO_FISHER_EDGAR, Route44_Johto_FisherEdgarSeenText, Route44_Johto_FisherEdgarBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_EDGAR
	lock
	faceplayer
	goto Route44_Johto_TrainerFisherEdgar_Script

Route44_Johto_TrainerFisherEdgar_Script:
	message Route44_Johto_FisherEdgarAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_TrainerCooltrainerfCybil::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_CYBIL, Route44_Johto_CooltrainerfCybilSeenText, Route44_Johto_CooltrainerfCybilBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_CYBIL
	lock
	faceplayer
	goto Route44_Johto_TrainerCooltrainerfCybil_Script

Route44_Johto_TrainerCooltrainerfCybil_Script:
	message Route44_Johto_CooltrainerfCybilAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_TrainerPokemaniacZach::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_ZACH, Route44_Johto_PokemaniacZachSeenText, Route44_Johto_PokemaniacZachBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_ZACH
	lock
	faceplayer
	goto Route44_Johto_TrainerPokemaniacZach_Script

Route44_Johto_TrainerPokemaniacZach_Script:
	message Route44_Johto_PokemaniacZachAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_TrainerCooltrainermAllen::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_ALLEN, Route44_Johto_CooltrainermAllenSeenText, Route44_Johto_CooltrainermAllenBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_ALLEN
	lock
	faceplayer
	goto Route44_Johto_TrainerCooltrainermAllen_Script

Route44_Johto_TrainerCooltrainermAllen_Script:
	message Route44_Johto_CooltrainermAllenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_Route44Sign1:
	message Route44_Johto_Route44Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_Route44Sign2:
	message Route44_Johto_Route44Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route44_Johto_Route44FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_44, Johto_Std_FruitTreeEmpty
	giveitem ITEM_RAWST_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_44
	releaseall
	end

Route44_Johto_Route44MaxRevive:
	finditem ITEM_MAX_REVIVE
	releaseall
	end

Route44_Johto_Route44UltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

Route44_Johto_Route44MaxRepel:
	finditem ITEM_MAX_REPEL
	releaseall
	end

Route44_Johto_Route44AskNumber1M_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route44_Johto_Route44AskNumber2M_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route44_Johto_Route44RegisteredNumberM_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route44_Johto_Route44RematchM_Sub:
	goto Johto_Std_RematchMScript_Sub

Route44_Johto_Route44GiftM_Sub:
	goto Johto_Std_GiftMScript_Sub

Route44_Johto_Route44RematchGiftM_Sub:
	goto Johto_Std_RematchGiftMScript_Sub

Route44_Johto_FisherWilton1SeenText:
	.string "Aack! You made me\n"
	.string "lose a POLIWAG!"
	.string "\pWhat are you going\n"
	.string "to do about it?$"

Route44_Johto_FisherWilton1BeatenText:
	.string "Just forget about\n"
	.string "it.$"

Route44_Johto_FisherWiltonHugePoliwagText:
	.string "That POLIWAG that\n"
	.string "got away…\l"
	.string "It was huge."
	.string "\pI swear it must've\n"
	.string "been 16 feet long!$"

Route44_Johto_FisherEdgarSeenText:
	.string "I fish until I\n"
	.string "can't anymore."
	.string "\pI also battle\n"
	.string "until I drop."
	.string "\pThat's my\n"
	.string "relationship\l"
	.string "with my POKéMON.$"

Route44_Johto_FisherEdgarBeatenText:
	.string "Hmmmm… \n"
	.string "This isn't right.$"

Route44_Johto_FisherEdgarAfterBattleText:
	.string "That's 100 wins\n"
	.string "to 101 losses."
	.string "\pI won't battle\n"
	.string "again for a while.$"

Route44_Johto_BirdKeeperVance1SeenText:
	.string "Do you know about\n"
	.string "the legendary bird\l"
	.string "POKéMON?$"

Route44_Johto_BirdKeeperVance1BeatenText:
	.string "Whew! You're hot\n"
	.string "stuff.$"

Route44_Johto_BirdKeeperVanceLegendaryBirdsText:
	.string "ARTICUNO, ZAPDOS\n"
	.string "and MOLTRES are"
	.string "\pthe three legend-\n"
	.string "ary bird POKéMON."
	.string "\pI heard there are\n"
	.string "other legendary\l"
	.string "birds, though.$"

Route44_Johto_BirdKeeperVance2BeatenText:
	.string "Why can't I ever\n"
	.string "beat you?"
	.string "\pOh yeah, here you\n"
	.string "go. It's that gift"
	.string "\pI couldn't give\n"
	.string "you last time.$"

Route44_Johto_PsychicPhilSeenText:
	.string "I'm gonna win,\n"
	.string "for sure!$"

Route44_Johto_PsychicPhilBeatenText:
	.string "Arrgh… That's a\n"
	.string "shocking loss…$"

Route44_Johto_PsychicPhilAfterBattleText:
	.string "It's important to\n"
	.string "have conviction\l"
	.string "on your side.$"

Route44_Johto_PokemaniacZachSeenText:
	.string "I'll do anything\n"
	.string "to get my hands on\l"
	.string "rare POKéMON!$"

Route44_Johto_PokemaniacZachBeatenText:
	.string "Oooh, your POKéMON\n"
	.string "are so appealing.$"

Route44_Johto_PokemaniacZachAfterBattleText:
	.string "If a POKéMON has\n"
	.string "different colors"
	.string "\pfrom usual, it's\n"
	.string "more valuable."
	.string "\pWhat? You mean\n"
	.string "that's not true?$"

Route44_Johto_CooltrainermAllenSeenText:
	.string "I can tell you're\n"
	.string "a good trainer by\l"
	.string "looking at you."
	.string "\pI'm good at POKé-\n"
	.string "MON, and I can see\l"
	.string "that you are too.$"

Route44_Johto_CooltrainermAllenBeatenText:
	.string "Tch! It's a total\n"
	.string "loss on my part.$"

Route44_Johto_CooltrainermAllenAfterBattleText:
	.string "Wow. You have a\n"
	.string "lot of BADGES."
	.string "\pNo wonder you're\n"
	.string "so tough."
	.string "\pI wonder if\n"
	.string "ECRUTEAK GYM's"
	.string "\pMORTY is still in\n"
	.string "training?"
	.string "\pHe really hammered\n"
	.string "me.$"

Route44_Johto_CooltrainerfCybilSeenText:
	.string "You look strong."
	.string "\pGood trainers seek\n"
	.string "tough opponents\l"
	.string "instinctively.$"

Route44_Johto_CooltrainerfCybilBeatenText:
	.string "Nope! This won't\n"
	.string "do at all.$"

Route44_Johto_CooltrainerfCybilAfterBattleText:
	.string "We all get better\n"
	.string "by experiencing\l"
	.string "many battles."
	.string "\pI battled a lot to\n"
	.string "become what I am\l"
	.string "today--an elite.$"

Route44_Johto_Route44Sign1Text:
	.string "ROUTE 44\n"
	.string "ICE PATH AHEAD$"

Route44_Johto_Route44Sign2Text:
	.string "ROUTE 44"
	.string "\pMAHOGANY TOWN -\n"
	.string "BLACKTHORN CITY$"
