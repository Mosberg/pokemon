Route15_Johto_MapScripts::
	.byte 0

Route15_Johto_Route15PPUp_Entry::
	lockall
	goto Route15_Johto_Route15PPUp

Route15_Johto_Route15Sign_Entry::
	lockall
	goto Route15_Johto_Route15Sign


Route15_Johto_TrainerTeacherColette::
	trainerbattle_single TRAINER_JOHTO_TEACHER_COLETTE, Route15_Johto_TeacherColetteSeenText, Route15_Johto_TeacherColetteBeatenText
	setflag FLAG_JOHTO_BEAT_TEACHER_COLETTE
	lock
	faceplayer
	goto Route15_Johto_TrainerTeacherColette_Script

Route15_Johto_TrainerTeacherColette_Script:
	message Route15_Johto_TeacherColetteAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_TrainerTeacherHillary::
	trainerbattle_single TRAINER_JOHTO_TEACHER_HILLARY, Route15_Johto_TeacherHillarySeenText, Route15_Johto_TeacherHillaryBeatenText
	setflag FLAG_JOHTO_BEAT_TEACHER_HILLARY
	lock
	faceplayer
	goto Route15_Johto_TrainerTeacherHillary_Script

Route15_Johto_TrainerTeacherHillary_Script:
	message Route15_Johto_TeacherHillaryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_TrainerSchoolboyKipp::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_KIPP, Route15_Johto_SchoolboyKippSeenText, Route15_Johto_SchoolboyKippBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_KIP
	lock
	faceplayer
	goto Route15_Johto_TrainerSchoolboyKipp_Script

Route15_Johto_TrainerSchoolboyKipp_Script:
	message Route15_Johto_SchoolboyKippAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_TrainerSchoolboyTommy::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_TOMMY, Route15_Johto_SchoolboyTommySeenText, Route15_Johto_SchoolboyTommyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_TOMMY
	lock
	faceplayer
	goto Route15_Johto_TrainerSchoolboyTommy_Script

Route15_Johto_TrainerSchoolboyTommy_Script:
	message Route15_Johto_SchoolboyTommyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_TrainerSchoolboyJohnny::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_JOHNNY, Route15_Johto_SchoolboyJohnnySeenText, Route15_Johto_SchoolboyJohnnyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_JOHNNY
	lock
	faceplayer
	goto Route15_Johto_TrainerSchoolboyJohnny_Script

Route15_Johto_TrainerSchoolboyJohnny_Script:
	message Route15_Johto_SchoolboyJohnnyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_TrainerSchoolboyBilly::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_BILLY, Route15_Johto_SchoolboyBillySeenText, Route15_Johto_SchoolboyBillyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_BILLY
	lock
	faceplayer
	goto Route15_Johto_TrainerSchoolboyBilly_Script

Route15_Johto_TrainerSchoolboyBilly_Script:
	message Route15_Johto_SchoolboyBillyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_Route15Sign:
	message Route15_Johto_Route15SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15_Johto_Route15PPUp:
	finditem ITEM_PP_UP
	releaseall
	end

Route15_Johto_TeacherColetteSeenText:
	.string "Have you forgotten\n"
	.string "anything?$"

Route15_Johto_TeacherColetteBeatenText:
	.string "Kyaaah!$"

Route15_Johto_TeacherColetteAfterBattleText:
	.string "Before I became a\n"
	.string "teacher, I used to"
	.string "\pforget a lot of\n"
	.string "things.$"

Route15_Johto_TeacherHillarySeenText:
	.string "On sunny days, I\n"
	.string "think that the"
	.string "\pkids would rather\n"
	.string "be playing in the"
	.string "\pschoolyard than\n"
	.string "studying in class.$"

Route15_Johto_TeacherHillaryBeatenText:
	.string "I didn't want to\n"
	.string "lose…$"

Route15_Johto_TeacherHillaryAfterBattleText:
	.string "Studying is impor-\n"
	.string "tant, but exercise\l"
	.string "is just as vital.$"

Route15_Johto_SchoolboyKippSeenText:
	.string "Hang on. I have to\n"
	.string "phone my mom.$"

Route15_Johto_SchoolboyKippBeatenText:
	.string "Sorry, Mom!\n"
	.string "I was beaten!$"

Route15_Johto_SchoolboyKippAfterBattleText:
	.string "My mom worries so\n"
	.string "much about me, I"
	.string "\phave to phone her\n"
	.string "all the time.$"

Route15_Johto_SchoolboyTommySeenText:
	.string "Let's battle.\n"
	.string "I won't lose!$"

Route15_Johto_SchoolboyTommyBeatenText:
	.string "I forgot to do my\n"
	.string "homework!$"

Route15_Johto_SchoolboyTommyAfterBattleText:
	.string "Sayonara! I just\n"
	.string "learned that in my\l"
	.string "Japanese class.$"

Route15_Johto_SchoolboyJohnnySeenText:
	.string "We're on a field\n"
	.string "trip to LAVENDER"
	.string "\pRADIO TOWER for\n"
	.string "social studies.$"

Route15_Johto_SchoolboyJohnnyBeatenText:
	.string "You're wickedly\n"
	.string "tough!$"

Route15_Johto_SchoolboyJohnnyAfterBattleText:
	.string "I'm tired of walk-\n"
	.string "ing. I need to\l"
	.string "take a break.$"

Route15_Johto_SchoolboyBillySeenText:
	.string "My favorite class\n"
	.string "is gym!$"

Route15_Johto_SchoolboyBillyBeatenText:
	.string "Oh, no!\n"
	.string "How could I lose?$"

Route15_Johto_SchoolboyBillyAfterBattleText:
	.string "If POKéMON were a\n"
	.string "subject at school,\l"
	.string "I'd be the best!$"

Route15_Johto_Route15SignText:
	.string "ROUTE 15"
	.string "\pFUCHSIA CITY -\n"
	.string "LAVENDER TOWN$"
