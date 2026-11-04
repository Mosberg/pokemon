FastShipB1F_Johto_MapScripts::
	.byte 0

FastShipB1F_Johto_FastShipB1FSailorScript_Entry::
	lockall
	goto FastShipB1F_Johto_FastShipB1FSailorScript

FastShipB1F_Johto_FastShipB1FTrashcan_Entry::
	lockall
	goto FastShipB1F_Johto_FastShipB1FTrashcan

FastShipB1F_Johto_FastShipB1FSailorBlocksLeft_Entry::
	lockall
	goto FastShipB1F_Johto_FastShipB1FSailorBlocksLeft

FastShipB1F_Johto_FastShipB1FSailorBlocksRight_Entry::
	lockall
	goto FastShipB1F_Johto_FastShipB1FSailorBlocksRight


FastShipB1F_Johto_FastShipB1FSailorBlocksLeft:
	goto_if_set FLAG_JOHTO_FAST_SHIP_B1F_SAILOR_RIGHT, FastShipB1F_Johto_FastShipB1FAlreadyBlocked
	applymovement 2, FastShipB1F_Johto_FastShipB1FSailorBlocksLeftMovement
	waitmovement 2
	setobjectxyperm 1, 30, 6
	clearflag FLAG_JOHTO_FAST_SHIP_B1F_SAILOR_LEFT
	addobject 1
	delay 5
	removeobject 2
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorBlocksRight:
	goto_if_set FLAG_JOHTO_FAST_SHIP_B1F_SAILOR_LEFT, FastShipB1F_Johto_FastShipB1FAlreadyBlocked
	applymovement 1, FastShipB1F_Johto_FastShipB1FSailorBlocksRightMovement
	waitmovement 1
	setobjectxyperm 2, 31, 6
	clearflag FLAG_JOHTO_FAST_SHIP_B1F_SAILOR_RIGHT
	addobject 2
	delay 5
	removeobject 1
	releaseall
	end

FastShipB1F_Johto_FastShipB1FAlreadyBlocked:
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, FastShipB1F_Johto_FastShipB1FSailorScript_FirstTime
	goto_if_set FLAG_JOHTO_FAST_SHIP_LAZY_SAILOR, FastShipB1F_Johto_FastShipB1FSailorScript_LazySailor
	goto_if_set FLAG_JOHTO_FAST_SHIP_INFORMED_ABOUT_LAZY_SAILOR, FastShipB1F_Johto_FastShipB1FSailorScript_AlreadyInformed
	message FastShipB1F_Johto_FastShipB1FOnDutySailorText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_FAST_SHIP_INFORMED_ABOUT_LAZY_SAILOR
	clearflag FLAG_JOHTO_FAST_SHIP_CABINS_NNW_NNE_NE_SAILOR
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorScript_AlreadyInformed:
	message FastShipB1F_Johto_FastShipB1FOnDutySailorRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorScript_LazySailor:
	message FastShipB1F_Johto_FastShipB1FOnDutySailorThanksText
	waitmessage
	goto_if_unset FLAG_JOHTO_FAST_SHIP_FOUND_GIRL, FastShipB1F_Johto_FastShipB1FSailorScript_NotFoundGirl
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorScript_NotFoundGirl:
	waitbuttonpress
	message FastShipB1F_Johto_FastShipB1FOnDutySailorSawLittleGirlText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_FastShipB1FSailorScript_FirstTime:
	message FastShipB1F_Johto_FastShipB1FOnDutySailorDirectionsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerSailorJeff::
	trainerbattle_single TRAINER_JOHTO_SAILOR_JEFF, FastShipB1F_Johto_SailorJeffSeenText, FastShipB1F_Johto_SailorJeffBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_JEFF
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerSailorJeff_Script

FastShipB1F_Johto_TrainerSailorJeff_Script:
	message FastShipB1F_Johto_SailorJeffAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerPicnickerDebra::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_DEBRA, FastShipB1F_Johto_PicnickerDebraSeenText, FastShipB1F_Johto_PicnickerDebraBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_DEBRA
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerPicnickerDebra_Script

FastShipB1F_Johto_TrainerPicnickerDebra_Script:
	message FastShipB1F_Johto_PicnickerDebraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerJugglerFritz::
	trainerbattle_single TRAINER_JOHTO_JUGGLER_FRITZ, FastShipB1F_Johto_JugglerFritzSeenText, FastShipB1F_Johto_JugglerFritzBeatenText
	setflag FLAG_JOHTO_BEAT_JUGGLER_FRITZ
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerJugglerFritz_Script

FastShipB1F_Johto_TrainerJugglerFritz_Script:
	message FastShipB1F_Johto_JugglerFritzAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerSailorGarrett::
	trainerbattle_single TRAINER_JOHTO_SAILOR_GARRETT, FastShipB1F_Johto_SailorGarrettSeenText, FastShipB1F_Johto_SailorGarrettBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_GARRETT
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerSailorGarrett_Script

FastShipB1F_Johto_TrainerSailorGarrett_Script:
	message FastShipB1F_Johto_SailorGarrettAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerFisherJonah::
	trainerbattle_single TRAINER_JOHTO_FISHER_JONAH, FastShipB1F_Johto_FisherJonahSeenText, FastShipB1F_Johto_FisherJonahBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_JONAH
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerFisherJonah_Script

FastShipB1F_Johto_TrainerFisherJonah_Script:
	message FastShipB1F_Johto_FisherJonahAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerBlackbeltWai::
	trainerbattle_single TRAINER_JOHTO_BLACKBELT_T_WAI, FastShipB1F_Johto_BlackbeltWaiSeenText, FastShipB1F_Johto_BlackbeltWaiBeatenText
	setflag FLAG_JOHTO_BEAT_BLACKBELT_WAI
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerBlackbeltWai_Script

FastShipB1F_Johto_TrainerBlackbeltWai_Script:
	message FastShipB1F_Johto_BlackbeltWaiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerSailorKenneth::
	trainerbattle_single TRAINER_JOHTO_SAILOR_KENNETH, FastShipB1F_Johto_SailorKennethSeenText, FastShipB1F_Johto_SailorKennethBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_KENNETH
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerSailorKenneth_Script

FastShipB1F_Johto_TrainerSailorKenneth_Script:
	message FastShipB1F_Johto_SailorKennethAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerTeacherShirley::
	trainerbattle_single TRAINER_JOHTO_TEACHER_SHIRLEY, FastShipB1F_Johto_TeacherShirleySeenText, FastShipB1F_Johto_TeacherShirleyBeatenText
	setflag FLAG_JOHTO_BEAT_TEACHER_SHIRLEY
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerTeacherShirley_Script

FastShipB1F_Johto_TrainerTeacherShirley_Script:
	message FastShipB1F_Johto_TeacherShirleyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerSchoolboyNate::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_NATE, FastShipB1F_Johto_SchoolboyNateSeenText, FastShipB1F_Johto_SchoolboyNateBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_NATE
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerSchoolboyNate_Script

FastShipB1F_Johto_TrainerSchoolboyNate_Script:
	message FastShipB1F_Johto_SchoolboyNateAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_TrainerSchoolboyRicky::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_RICKY, FastShipB1F_Johto_SchoolboyRickySeenText, FastShipB1F_Johto_SchoolboyRickyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_RICKY
	lock
	faceplayer
	goto FastShipB1F_Johto_TrainerSchoolboyRicky_Script

FastShipB1F_Johto_TrainerSchoolboyRicky_Script:
	message FastShipB1F_Johto_SchoolboyRickyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipB1F_Johto_FastShipB1FTrashcan:
	goto Johto_Std_TrashCanScript

FastShipB1F_Johto_FastShipB1FSailorBlocksRightMovement:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	face_down
	step_end

FastShipB1F_Johto_FastShipB1FSailorBlocksLeftMovement:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_down
	step_end

FastShipB1F_Johto_FastShipB1FOnDutySailorText:
	.string "Hey, kid. Could I\n"
	.string "get you to look\l"
	.string "for my buddy?"
	.string "\pHe's goofing off\n"
	.string "somewhere, that\l"
	.string "lazy bum!"
	.string "\pI want to go find\n"
	.string "him, but I'm on\l"
	.string "duty right now.$"

FastShipB1F_Johto_FastShipB1FOnDutySailorRefusedText:
	.string "Oh, gee…"
	.string "\pThe CAPTAIN will\n"
	.string "be furious…$"

FastShipB1F_Johto_FastShipB1FOnDutySailorThanksText:
	.string "Thanks, kid!\n"
	.string "I chewed him out"
	.string "\pgood so he'll quit\n"
	.string "slacking off!$"

FastShipB1F_Johto_FastShipB1FOnDutySailorSawLittleGirlText:
	.string "A little girl?"
	.string "\pI may have seen\n"
	.string "her go by here.$"

FastShipB1F_Johto_FastShipB1FOnDutySailorDirectionsText:
	.string "The dining room is\n"
	.string "up ahead."
	.string "\pThe stairs at the\n"
	.string "end lead to the\l"
	.string "CAPTAIN's cabin.$"

FastShipB1F_Johto_SailorJeffSeenText:
	.string "Nothing beats a\n"
	.string "battle when I'm\l"
	.string "on my break.$"

FastShipB1F_Johto_SailorJeffBeatenText:
	.string "Win or lose, my\n"
	.string "break's over!$"

FastShipB1F_Johto_SailorJeffAfterBattleText:
	.string "I guess I can't\n"
	.string "win if I don't get\l"
	.string "serious.$"

FastShipB1F_Johto_PicnickerDebraSeenText:
	.string "I'm so bored.\n"
	.string "Want to battle?$"

FastShipB1F_Johto_PicnickerDebraBeatenText:
	.string "Yow! You're too\n"
	.string "strong!$"

FastShipB1F_Johto_PicnickerDebraAfterBattleText:
	.string "SAFFRON, CELADON…\n"
	.string "I hear there are"
	.string "\pmany big cities\n"
	.string "in KANTO.$"

FastShipB1F_Johto_JugglerFritzSeenText:
	.string "Urrf…\n"
	.string "I'm seasick!$"

FastShipB1F_Johto_JugglerFritzBeatenText:
	.string "I can't move any-\n"
	.string "more…$"

FastShipB1F_Johto_JugglerFritzAfterBattleText:
	.string "No more ships for\n"
	.string "me. Next time,"
	.string "\pI'm taking the\n"
	.string "MAGNET TRAIN.$"

FastShipB1F_Johto_SailorGarrettSeenText:
	.string "This is where we\n"
	.string "sailors work!$"

FastShipB1F_Johto_SailorGarrettBeatenText:
	.string "I lost on my home\n"
	.string "field…$"

FastShipB1F_Johto_SailorGarrettAfterBattleText:
	.string "We get different\n"
	.string "passengers from"
	.string "\pVERMILION CITY to\n"
	.string "OLIVINE CITY.$"

FastShipB1F_Johto_FisherJonahSeenText:
	.string "Even though we're\n"
	.string "out on the sea, I\l"
	.string "can't fish!"
	.string "\pThis is boring!\n"
	.string "Let's battle!$"

FastShipB1F_Johto_FisherJonahBeatenText:
	.string "I… I'm not bored\n"
	.string "anymore…$"

FastShipB1F_Johto_FisherJonahAfterBattleText:
	.string "I plan to fish off\n"
	.string "VERMILION's pier.$"

FastShipB1F_Johto_BlackbeltWaiSeenText:
	.string "I'm building up my\n"
	.string "legs by bracing"
	.string "\pagainst the ship's\n"
	.string "rocking!$"

FastShipB1F_Johto_BlackbeltWaiBeatenText:
	.string "Rocked and rolled\n"
	.string "over!$"

FastShipB1F_Johto_BlackbeltWaiAfterBattleText:
	.string "I couldn't find\n"
	.string "the KARATE KING in\l"
	.string "JOHTO."
	.string "\pHe's supposed to\n"
	.string "be training in a\l"
	.string "cave somewhere.$"

FastShipB1F_Johto_SailorKennethSeenText:
	.string "I'm a sailor man!"
	.string "\pBut I'm training\n"
	.string "POKéMON, so I can\l"
	.string "become the CHAMP!$"

FastShipB1F_Johto_SailorKennethBeatenText:
	.string "My lack of train-\n"
	.string "ing is obvious…$"

FastShipB1F_Johto_SailorKennethAfterBattleText:
	.string "Eight BADGES!\n"
	.string "They must prove"
	.string "\pthat you've beaten\n"
	.string "GYM LEADERS."
	.string "\pNo wonder you're\n"
	.string "so good!$"

FastShipB1F_Johto_TeacherShirleySeenText:
	.string "Don't lay a finger\n"
	.string "on my students!$"

FastShipB1F_Johto_TeacherShirleyBeatenText:
	.string "Aaack!$"

FastShipB1F_Johto_TeacherShirleyAfterBattleText:
	.string "We're on a field\n"
	.string "trip to the RUINS\l"
	.string "outside VIOLET.$"

FastShipB1F_Johto_SchoolboyNateSeenText:
	.string "Do you know the\n"
	.string "RUINS OF ALPH?$"

FastShipB1F_Johto_SchoolboyNateBeatenText:
	.string "Yaargh!$"

FastShipB1F_Johto_SchoolboyNateAfterBattleText:
	.string "Radios pick up\n"
	.string "strange signals\l"
	.string "inside the RUINS.$"

FastShipB1F_Johto_SchoolboyRickySeenText:
	.string "There are some odd\n"
	.string "stone panels in\l"
	.string "the RUINS OF ALPH.$"

FastShipB1F_Johto_SchoolboyRickyBeatenText:
	.string "I was done in!$"

FastShipB1F_Johto_SchoolboyRickyAfterBattleText:
	.string "I read that there\n"
	.string "are four of those\l"
	.string "stone panels.$"
