Route36_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route36_Johto_OnTransition
	.byte 0

Route36_Johto_OnTransition:
	call Route36_Johto_Route36ArthurCallback_Cb
	end

Route36_Johto_SudowoodoScript_Entry::
	lockall
	goto Route36_Johto_SudowoodoScript

Route36_Johto_Route36LassScript_Entry::
	lockall
	goto Route36_Johto_Route36LassScript

Route36_Johto_Route36RockSmashGuyScript_Entry::
	lockall
	goto Route36_Johto_Route36RockSmashGuyScript

Route36_Johto_Route36FruitTree_Entry::
	lockall
	goto Route36_Johto_Route36FruitTree

Route36_Johto_ArthurScript_Entry::
	lockall
	goto Route36_Johto_ArthurScript

Route36_Johto_Route36FloriaScript_Entry::
	lockall
	goto Route36_Johto_Route36FloriaScript

Route36_Johto_Route36TrainerTips2_Entry::
	lockall
	goto Route36_Johto_Route36TrainerTips2

Route36_Johto_RuinsOfAlphNorthSign_Entry::
	lockall
	goto Route36_Johto_RuinsOfAlphNorthSign

Route36_Johto_Route36Sign_Entry::
	lockall
	goto Route36_Johto_Route36Sign

Route36_Johto_Route36TrainerTips1_Entry::
	lockall
	goto Route36_Johto_Route36TrainerTips1

Route36_Johto_Route36SuicuneScript_Entry::
	lockall
	goto Route36_Johto_Route36SuicuneScript


Route36_Johto_Route36SuicuneScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	playse SE_WARP_OUT
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 9, Route36_Johto_Route36SuicuneMovement
	waitmovement 9
	removeobject 9
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	setvar VAR_JOHTO_SCENE_ROUTE_36, 0
	clearflag FLAG_JOHTO_SAW_SUICUNE_AT_CIANWOOD_CITY
	setvar VAR_JOHTO_SCENE_CIANWOOD_CITY, 1
	releaseall
	end

Route36_Johto_SudowoodoScript:
	checkitem ITEM_SQUIRTBOTTLE, 1
	goto_if_ne VAR_RESULT, 0, Route36_Johto_SudowoodoScript_Fight
	waitse
	playse SE_PIN
	applymovement 3, Route36_Johto_SudowoodoShakeMovement
	waitmovement 3
	releaseall
	end

Route36_Johto_SudowoodoScript_Fight:
	message Route36_Johto_UseSquirtbottleText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route36_Johto_DidntUseSquirtbottleScript
	closemessage

Route36_Johto_WateredWeirdTreeScript:
	message Route36_Johto_UsedSquirtbottleText
	waitmessage
	waitbuttonpress
	closemessage
	waitse
	playse SE_PIN
	applymovement 3, Route36_Johto_SudowoodoShakeMovement
	waitmovement 3
	message Route36_Johto_SudowoodoAttackedText
	waitmessage
	waitbuttonpress
	closemessage
	setwildbattle SPECIES_SUDOWOODO, 20
	dowildbattle
	setflag FLAG_JOHTO_FOUGHT_SUDOWOODO
	goto_if_eq VAR_RESULT, 2, Route36_Johto_DidntCatchSudowoodo
	removeobject 3
	releaseall
	end

Route36_Johto_DidntUseSquirtbottleScript:
	closemessage
	releaseall
	end

Route36_Johto_DidntCatchSudowoodo:
	applymovement 3, Route36_Johto_WeirdTreeMovement_Flee
	waitmovement 3
	removeobject 3
	releaseall
	end

Route36_Johto_Route36FloriaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_TALKED_TO_FLORIA_AT_FLOWER_SHOP, Route36_Johto_Route36FloriaScript_SecondTimeTalking
	setflag FLAG_JOHTO_MET_FLORIA
	message Route36_Johto_FloriaText1
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_JOHTO_FLORIA_AT_FLOWER_SHOP
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, Route36_Johto_Route36FloriaScript_Up
	applymovement 8, Route36_Johto_FloriaMovement1
	waitmovement 8
	removeobject 8
	releaseall
	end

Route36_Johto_Route36FloriaScript_Up:
	applymovement 8, Route36_Johto_FloriaMovement2
	waitmovement 8
	removeobject 8
	releaseall
	end

Route36_Johto_Route36FloriaScript_SecondTimeTalking:
	message Route36_Johto_FloriaText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36RockSmashGuyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM08_ROCK_SMASH, Route36_Johto_Route36RockSmashGuyScript_AlreadyGotRockSmash
	goto_if_set FLAG_JOHTO_FOUGHT_SUDOWOODO, Route36_Johto_Route36RockSmashGuyScript_ClearedSudowoodo
	message Route36_Johto_RockSmashGuyText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36RockSmashGuyScript_ClearedSudowoodo:
	message Route36_Johto_RockSmashGuyText2
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, Route36_Johto_Route36RockSmashGuyScript_NoRoomForTM
	setflag FLAG_JOHTO_GOT_TM08_ROCK_SMASH

Route36_Johto_Route36RockSmashGuyScript_AlreadyGotRockSmash:
	message Route36_Johto_RockSmashGuyText3
	waitmessage
	waitbuttonpress

Route36_Johto_Route36RockSmashGuyScript_NoRoomForTM:
	closemessage
	releaseall
	end

Route36_Johto_Route36LassScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FOUGHT_SUDOWOODO, Route36_Johto_Route36LassScript_ClearedSudowoodo
	message Route36_Johto_Route36LassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36LassScript_ClearedSudowoodo:
	message Route36_Johto_Route36LassText_ClearedSudowoodo
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_ALAN1, Route36_Johto_SchoolboyAlan1SeenText, Route36_Johto_SchoolboyAlan1BeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_ALAN
	lock
	faceplayer
	goto Route36_Johto_TrainerSchoolboyAlan1_Script

Route36_Johto_TrainerSchoolboyAlan1_Script:
	setvar VAR_0x8007, 294
	goto_if_set FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH, Route36_Johto_TrainerSchoolboyAlan1_ChooseRematch
	goto_if_set FLAG_JOHTO_ENGINE_ALAN_HAS_FIRE_STONE, Route36_Johto_TrainerSchoolboyAlan1_GiveFireStone
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_SCHOOLBOY_ALAN_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, Route36_Johto_TrainerSchoolboyAlan1_NumberAccepted
	goto_if_set FLAG_JOHTO_ALAN_ASKED_FOR_PHONE_NUMBER, Route36_Johto_TrainerSchoolboyAlan1_AskAgainForPhoneNumber
	message Route36_Johto_SchoolboyAlanBooksText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_ALAN_ASKED_FOR_PHONE_NUMBER
	call Route36_Johto_TrainerSchoolboyAlan1_AskNumber1_Sub
	goto Route36_Johto_TrainerSchoolboyAlan1_ContinueAskForPhoneNumber

Route36_Johto_TrainerSchoolboyAlan1_AskAgainForPhoneNumber:
	call Route36_Johto_TrainerSchoolboyAlan1_AskNumber2_Sub

Route36_Johto_TrainerSchoolboyAlan1_ContinueAskForPhoneNumber:
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_SCHOOLBOY_ALAN_REGISTERED
	setvar VAR_0x8005, FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	setvar VAR_0x8006, FLAG_JOHTO_ENGINE_ALAN_HAS_FIRE_STONE
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, Route36_Johto_TrainerSchoolboyAlan1_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route36_Johto_TrainerSchoolboyAlan1_NumberDeclined
	buffertrainername STR_VAR_1, TRAINER_JOHTO_SCHOOLBOY_ALAN1
	call Route36_Johto_TrainerSchoolboyAlan1_RegisteredNumber_Sub
	goto Route36_Johto_TrainerSchoolboyAlan1_NumberAccepted

Route36_Johto_TrainerSchoolboyAlan1_ChooseRematch:
	call Route36_Johto_TrainerSchoolboyAlan1_Rematch_Sub
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WALANFIGHTCOUNT
	goto_if_eq VAR_RESULT, 4, Route36_Johto_TrainerSchoolboyAlan1_Fight4
	goto_if_eq VAR_RESULT, 3, Route36_Johto_TrainerSchoolboyAlan1_Fight3
	goto_if_eq VAR_RESULT, 2, Route36_Johto_TrainerSchoolboyAlan1_Fight2
	goto_if_eq VAR_RESULT, 1, Route36_Johto_TrainerSchoolboyAlan1_Fight1
	goto_if_eq VAR_RESULT, 0, Route36_Johto_TrainerSchoolboyAlan1_LoadFight0

Route36_Johto_TrainerSchoolboyAlan1_Fight4:
	goto_if_set FLAG_JOHTO_RESTORED_POWER_TO_KANTO, Route36_Johto_TrainerSchoolboyAlan1_LoadFight4

Route36_Johto_TrainerSchoolboyAlan1_Fight3:
	goto_if_set FLAG_JOHTO_BEAT_ELITE_FOUR, Route36_Johto_TrainerSchoolboyAlan1_LoadFight3

Route36_Johto_TrainerSchoolboyAlan1_Fight2:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_BLACKTHORN, Route36_Johto_TrainerSchoolboyAlan1_LoadFight2

Route36_Johto_TrainerSchoolboyAlan1_Fight1:
	goto_if_set FLAG_JOHTO_ENGINE_FLYPOINT_OLIVINE, Route36_Johto_TrainerSchoolboyAlan1_LoadFight1

Route36_Johto_TrainerSchoolboyAlan1_LoadFight0:
	trainerbattle_no_intro TRAINER_JOHTO_SCHOOLBOY_ALAN1, Route36_Johto_SchoolboyAlan1BeatenText
	setvar VAR_JOHTO_MEM_WALANFIGHTCOUNT, 1
	clearflag FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_LoadFight1:
	trainerbattle_no_intro TRAINER_JOHTO_SCHOOLBOY_ALAN2, Route36_Johto_SchoolboyAlan1BeatenText
	setvar VAR_JOHTO_MEM_WALANFIGHTCOUNT, 2
	clearflag FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_LoadFight2:
	trainerbattle_no_intro TRAINER_JOHTO_SCHOOLBOY_ALAN3, Route36_Johto_SchoolboyAlan1BeatenText
	setvar VAR_JOHTO_MEM_WALANFIGHTCOUNT, 3
	clearflag FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_LoadFight3:
	trainerbattle_no_intro TRAINER_JOHTO_SCHOOLBOY_ALAN4, Route36_Johto_SchoolboyAlan1BeatenText
	setvar VAR_JOHTO_MEM_WALANFIGHTCOUNT, 4
	clearflag FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_LoadFight4:
	trainerbattle_no_intro TRAINER_JOHTO_SCHOOLBOY_ALAN5, Route36_Johto_SchoolboyAlan1BeatenText
	clearflag FLAG_JOHTO_ENGINE_ALAN_READY_FOR_REMATCH
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_GiveFireStone:
	call Route36_Johto_TrainerSchoolboyAlan1_Gift_Sub
	giveitem ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, 0, Route36_Johto_TrainerSchoolboyAlan1_BagFull
	clearflag FLAG_JOHTO_ENGINE_ALAN_HAS_FIRE_STONE
	setflag FLAG_JOHTO_ALAN_GAVE_FIRE_STONE
	goto Route36_Johto_TrainerSchoolboyAlan1_NumberAccepted

Route36_Johto_TrainerSchoolboyAlan1_BagFull:
	goto Route36_Johto_TrainerSchoolboyAlan1_PackFull

Route36_Johto_TrainerSchoolboyAlan1_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route36_Johto_TrainerSchoolboyAlan1_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route36_Johto_TrainerSchoolboyAlan1_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route36_Johto_TrainerSchoolboyAlan1_PackFull:
	goto Johto_Std_PackFullMScript

Route36_Johto_TrainerPsychicMark::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_MARK, Route36_Johto_PsychicMarkSeenText, Route36_Johto_PsychicMarkBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_MARK
	lock
	faceplayer
	goto Route36_Johto_TrainerPsychicMark_Script

Route36_Johto_TrainerPsychicMark_Script:
	message Route36_Johto_PsychicMarkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_ArthurScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HARD_STONE_FROM_ARTHUR, Route36_Johto_ArthurScript_AlreadyGotStone
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 4, Route36_Johto_ArthurNotThursdayScript
	goto_if_set FLAG_JOHTO_MET_ARTHUR_OF_THURSDAY, Route36_Johto_ArthurScript_MetArthur
	message Route36_Johto_MeetArthurText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_ARTHUR_OF_THURSDAY

Route36_Johto_ArthurScript_MetArthur:
	message Route36_Johto_ArthurGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HARD_STONE
	goto_if_eq VAR_RESULT, 0, Route36_Johto_ArthurScript_BagFull
	setflag FLAG_JOHTO_GOT_HARD_STONE_FROM_ARTHUR
	message Route36_Johto_ArthurGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_ArthurScript_AlreadyGotStone:
	message Route36_Johto_ArthurThursdayText
	waitmessage
	waitbuttonpress

Route36_Johto_ArthurScript_BagFull:
	closemessage
	releaseall
	end

Route36_Johto_ArthurNotThursdayScript:
	message Route36_Johto_ArthurNotThursdayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36Sign:
	message Route36_Johto_Route36SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_RuinsOfAlphNorthSign:
	message Route36_Johto_RuinsOfAlphNorthSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36TrainerTips1:
	message Route36_Johto_Route36TrainerTips1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36TrainerTips2:
	message Route36_Johto_Route36TrainerTips2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36_Johto_Route36FruitTree:
	goto_if_set FLAG_JOHTO_FRUITTREE_ROUTE_36, Johto_Std_FruitTreeEmpty
	giveitem ITEM_ASPEAR_BERRY
	setflag FLAG_JOHTO_FRUITTREE_ROUTE_36
	releaseall
	end

Route36_Johto_TrainerSchoolboyAlan1_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route36_Johto_TrainerSchoolboyAlan1_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route36_Johto_TrainerSchoolboyAlan1_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route36_Johto_TrainerSchoolboyAlan1_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route36_Johto_TrainerSchoolboyAlan1_Gift_Sub:
	goto Johto_Std_GiftMScript_Sub

Route36_Johto_Route36ArthurCallback_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 4, Route36_Johto_Route36ArthurCallback_ArthurAppears_Cb
	setflag FLAG_JOHTO_ROUTE_36_ARTHUR_OF_THURSDAY
	return

Route36_Johto_Route36ArthurCallback_ArthurAppears_Cb:
	clearflag FLAG_JOHTO_ROUTE_36_ARTHUR_OF_THURSDAY
	return

Route36_Johto_SudowoodoShakeMovement:
	step_end

Route36_Johto_WeirdTreeMovement_Flee:
	jump_up
	jump_up
	step_end

Route36_Johto_FloriaMovement1:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route36_Johto_FloriaMovement2:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route36_Johto_Route36SuicuneMovement:
	jump_down
	jump_down
	jump_down
	jump_right
	jump_right
	jump_right
	step_end

Route36_Johto_UseSquirtbottleText:
	.string "It's a weird tree.\n"
	.string "Use SQUIRTBOTTLE?$"

Route36_Johto_UsedSquirtbottleText:
	.string "{PLAYER} used the\n"
	.string "SQUIRTBOTTLE.$"

Route36_Johto_SudowoodoAttackedText:
	.string "The weird tree\n"
	.string "doesn't like the\l"
	.string "SQUIRTBOTTLE!"
	.string "\pThe weird tree\n"
	.string "attacked!$"

Route36_Johto_FloriaText1:
	.string "I'm the FLOWER\n"
	.string "SHOP's FLORIA!"
	.string "\pListen, listen!"
	.string "\pWhen I sprinkled\n"
	.string "water on that"
	.string "\pwiggly tree, it\n"
	.string "jumped right up!"
	.string "\pIt just has to be\n"
	.string "a POKéMON."
	.string "\pI bet it would be\n"
	.string "shocked out of its"
	.string "\pdisguise if you\n"
	.string "soaked it!"
	.string "\pI know! I'll tell\n"
	.string "my sis and borrow\l"
	.string "her water bottle!$"

Route36_Johto_FloriaText2:
	.string "When I told my sis\n"
	.string "about the jiggly"
	.string "\ptree, she said\n"
	.string "it's dangerous."
	.string "\pIf I beat WHITNEY,\n"
	.string "I wonder if she'll"
	.string "\plend me her water\n"
	.string "bottle…$"

Route36_Johto_RockSmashGuyText1:
	.string "Wa-hey!"
	.string "\pI was going to\n"
	.string "snap that tree"
	.string "\pwith my straight-\n"
	.string "arm punch."
	.string "\pBut I couldn't!\n"
	.string "I'm a failure!$"

Route36_Johto_RockSmashGuyText2:
	.string "Did you clear that\n"
	.string "wretched tree?"
	.string "\pI'm impressed!\n"
	.string "I want you to\l"
	.string "have this.$"

Route36_Johto_RockSmashGuyText3:
	.string "That happens to be\n"
	.string "ROCK SMASH."
	.string "\pYou can shatter\n"
	.string "rocks with just a"
	.string "\psingle well-aimed\n"
	.string "smack."
	.string "\pIf any rocks are\n"
	.string "in your way, just\l"
	.string "smash 'em up!$"

Route36_Johto_Route36LassText:
	.string "An odd tree is\n"
	.string "blocking the way\l"
	.string "to GOLDENROD CITY."
	.string "\pIt's preventing\n"
	.string "me from shopping."
	.string "\pSomething should\n"
	.string "be done about it.$"

Route36_Johto_Route36LassText_ClearedSudowoodo:
	.string "That odd tree dis-\n"
	.string "appeared without a\l"
	.string "trace."
	.string "\pOh! That tree was\n"
	.string "really a POKéMON?$"

Route36_Johto_PsychicMarkSeenText:
	.string "I'm going to read\n"
	.string "your thoughts!$"

Route36_Johto_PsychicMarkBeatenText:
	.string "I misread you!$"

Route36_Johto_PsychicMarkAfterBattleText:
	.string "I'd be strong if\n"
	.string "only I could tell"
	.string "\pwhat my opponent\n"
	.string "was thinking.$"

Route36_Johto_SchoolboyAlan1SeenText:
	.string "Thanks to my stud-\n"
	.string "ies, I'm ready for\l"
	.string "any POKéMON!$"

Route36_Johto_SchoolboyAlan1BeatenText:
	.string "Oops! Computation\n"
	.string "error?$"

Route36_Johto_SchoolboyAlanBooksText:
	.string "Darn. I study five\n"
	.string "hours a day too."
	.string "\pThere's more to\n"
	.string "learning than just\l"
	.string "reading books.$"

Route36_Johto_MeetArthurText:
	.string "ARTHUR: Who are\n"
	.string "you?"
	.string "\pI'm ARTHUR of\n"
	.string "Thursday.$"

Route36_Johto_ArthurGivesGiftText:
	.string "Here. You can have\n"
	.string "this.$"

Route36_Johto_ArthurGaveGiftText:
	.string "ARTHUR: A POKéMON\n"
	.string "that uses rock-"
	.string "\ptype moves should\n"
	.string "hold on to that."
	.string "\pIt pumps up rock-\n"
	.string "type attacks.$"

Route36_Johto_ArthurThursdayText:
	.string "ARTHUR: I'm ARTHUR\n"
	.string "of Thursday. I'm"
	.string "\pthe second son out\n"
	.string "of seven children.$"

Route36_Johto_ArthurNotThursdayText:
	.string "ARTHUR: Today's\n"
	.string "not Thursday. How\l"
	.string "disappointing.$"

Route36_Johto_Route36SignText:
	.string "ROUTE 36$"

Route36_Johto_RuinsOfAlphNorthSignText:
	.string "RUINS OF ALPH\n"
	.string "NORTH ENTRANCE$"

Route36_Johto_Route36TrainerTips1Text:
	.string "TRAINER TIPS"
	.string "\pPOKéMON stats\n"
	.string "vary--even within\l"
	.string "the same species."
	.string "\pTheir stats may be\n"
	.string "similar at first."
	.string "\pHowever, differ-\n"
	.string "ences will become"
	.string "\ppronounced as the\n"
	.string "POKéMON grow.$"

Route36_Johto_Route36TrainerTips2Text:
	.string "TRAINER TIPS"
	.string "\pUse DIG to return\n"
	.string "to the entrance of\l"
	.string "any place."
	.string "\pIt is convenient\n"
	.string "for exploring"
	.string "\pcaves and other\n"
	.string "landmarks.$"
