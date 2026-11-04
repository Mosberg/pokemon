SlowpokeWellB1F_Johto_MapScripts::
	.byte 0

SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailScript_Entry::
	lockall
	goto SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailScript

SlowpokeWellB1F_Johto_SlowpokeWellB1FTaillessSlowpokeScript_Entry::
	lockall
	goto SlowpokeWellB1F_Johto_SlowpokeWellB1FTaillessSlowpokeScript

SlowpokeWellB1F_Johto_SlowpokeWellB1FKurtScript_Entry::
	lockall
	goto SlowpokeWellB1F_Johto_SlowpokeWellB1FKurtScript

SlowpokeWellB1F_Johto_SlowpokeWellB1FBoulder_Entry::
	lockall
	goto SlowpokeWellB1F_Johto_SlowpokeWellB1FBoulder

SlowpokeWellB1F_Johto_SlowpokeWellB1FSuperPotion_Entry::
	lockall
	goto SlowpokeWellB1F_Johto_SlowpokeWellB1FSuperPotion


SlowpokeWellB1F_Johto_SlowpokeWellB1FKurtScript:
	faceplayer
	message SlowpokeWellB1F_Johto_SlowpokeWellB1FKurtText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_TrainerGruntM29::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_29, SlowpokeWellB1F_Johto_GruntM29SeenText, SlowpokeWellB1F_Johto_GruntM29BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_29
	lock
	faceplayer
	goto SlowpokeWellB1F_Johto_TrainerGruntM29_Script

SlowpokeWellB1F_Johto_TrainerGruntM29_Script:
	message SlowpokeWellB1F_Johto_GruntM29AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_TrainerGruntM1::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_1, SlowpokeWellB1F_Johto_GruntM1SeenText, SlowpokeWellB1F_Johto_GruntM1BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_1
	lock
	faceplayer
	goto SlowpokeWellB1F_Johto_TrainerGruntM1_Script

SlowpokeWellB1F_Johto_TrainerGruntM1_Script:
	message SlowpokeWellB1F_Johto_TrainerGruntM1WhenTalkText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	removeobject 2
	removeobject 3
	removeobject 4
	delay 15
	fadescreen FADE_FROM_BLACK
	removeobject 7
	setobjectxyperm 7, 11, 6
	clearflag FLAG_JOHTO_SLOWPOKE_WELL_KURT
	addobject 7
	applymovement 7, SlowpokeWellB1F_Johto_KurtSlowpokeWellVictoryMovementData
	waitmovement 7
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message SlowpokeWellB1F_Johto_KurtLeaveSlowpokeWellText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_CLEARED_SLOWPOKE_WELL
	setvar VAR_JOHTO_SCENE_AZALEA_TOWN, 1
	clearflag FLAG_JOHTO_ILEX_FOREST_APPRENTICE
	clearflag FLAG_JOHTO_ILEX_FOREST_FARFETCHD
	setflag FLAG_JOHTO_CHARCOAL_KILN_FARFETCH_D
	setflag FLAG_JOHTO_CHARCOAL_KILN_APPRENTICE
	setflag FLAG_JOHTO_SLOWPOKE_WELL_SLOWPOKES
	setflag FLAG_JOHTO_SLOWPOKE_WELL_KURT
	clearflag FLAG_JOHTO_AZALEA_TOWN_SLOWPOKES
	clearflag FLAG_JOHTO_KURTS_HOUSE_SLOWPOKE
	clearflag FLAG_JOHTO_KURTS_HOUSE_KURT_1
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	delay 15
	warp MAP_JOHTO_KURTS_HOUSE, 3, 3
	waitstate

SlowpokeWellB1F_Johto_TrainerGruntM2::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_2, SlowpokeWellB1F_Johto_GruntM2SeenText, SlowpokeWellB1F_Johto_GruntM2BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_2
	lock
	faceplayer
	goto SlowpokeWellB1F_Johto_TrainerGruntM2_Script

SlowpokeWellB1F_Johto_TrainerGruntM2_Script:
	message SlowpokeWellB1F_Johto_GruntM2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_TrainerGruntF1::
	trainerbattle_single TRAINER_JOHTO_GRUNTF_GRUNTF_1, SlowpokeWellB1F_Johto_GruntF1SeenText, SlowpokeWellB1F_Johto_GruntF1BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTF_1
	lock
	faceplayer
	goto SlowpokeWellB1F_Johto_TrainerGruntF1_Script

SlowpokeWellB1F_Johto_TrainerGruntF1_Script:
	message SlowpokeWellB1F_Johto_GruntF1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailScript:
	faceplayer
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	message SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailScript_ReadMail
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailScript_ReadMail:
	message SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeMailText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_SlowpokeWellB1FTaillessSlowpokeScript:
	faceplayer
	message SlowpokeWellB1F_Johto_SlowpokeWellB1FTaillessSlowpokeText
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

SlowpokeWellB1F_Johto_SlowpokeWellB1FBoulder:
	goto Johto_Std_StrengthBoulderScript

SlowpokeWellB1F_Johto_SlowpokeWellB1FSuperPotion:
	finditem ITEM_SUPER_POTION
	releaseall
	end

SlowpokeWellB1F_Johto_KurtSlowpokeWellVictoryMovementData:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	delay_8
	delay_8
	delay_8
	walk_left
	walk_up
	walk_up
	delay_8
	delay_8
	delay_8
	face_left
	step_end

SlowpokeWellB1F_Johto_SlowpokeWellB1FKurtText:
	.string "KURT: Hey there,\n"
	.string "{PLAYER}!"
	.string "\pThe guard up top\n"
	.string "took off when I\l"
	.string "shouted at him."
	.string "\pBut then I took a\n"
	.string "tumble down the\l"
	.string "WELL."
	.string "\pI slammed down\n"
	.string "hard on my back,\l"
	.string "so I can't move."
	.string "\pRats! If I were\n"
	.string "fit, my POKéMON"
	.string "\pwould've punished\n"
	.string "them…"
	.string "\pAh, it can't be\n"
	.string "helped."
	.string "\p{PLAYER}, show them\n"
	.string "how gutsy you are\l"
	.string "in my place!$"

SlowpokeWellB1F_Johto_KurtLeaveSlowpokeWellText:
	.string "KURT: Way to go,\n"
	.string "{PLAYER}!"
	.string "\pTEAM ROCKET has\n"
	.string "taken off."
	.string "\pMy back's better\n"
	.string "too. Let's get out\l"
	.string "of here.$"

SlowpokeWellB1F_Johto_GruntM29SeenText:
	.string "Darn! I was stand-\n"
	.string "ing guard up top"
	.string "\pwhen some old coot\n"
	.string "yelled at me."
	.string "\pHe startled me so\n"
	.string "much that I fell\l"
	.string "down here."
	.string "\pI think I'll vent\n"
	.string "my anger by taking\l"
	.string "it out on you!$"

SlowpokeWellB1F_Johto_GruntM29BeatenText:
	.string "Arrgh! This is NOT\n"
	.string "my day!$"

SlowpokeWellB1F_Johto_GruntM29AfterBattleText:
	.string "Sure, we've been\n"
	.string "hacking the tails"
	.string "\poff SLOWPOKE and\n"
	.string "selling them."
	.string "\pEverything we do\n"
	.string "is for profit."
	.string "\pThat's right!\n"
	.string "We're TEAM ROCKET,"
	.string "\pand we'll do any-\n"
	.string "thing for money!$"

SlowpokeWellB1F_Johto_GruntM1SeenText:
	.string "What do you want?"
	.string "\pIf you interrupt\n"
	.string "our work, don't\l"
	.string "expect any mercy!$"

SlowpokeWellB1F_Johto_GruntM1BeatenText:
	.string "You did OK today,\n"
	.string "but wait till next\l"
	.string "time!$"

SlowpokeWellB1F_Johto_TrainerGruntM1WhenTalkText:
	.string "Yeah, TEAM ROCKET\n"
	.string "was broken up\l"
	.string "three years ago."
	.string "\pBut we continued\n"
	.string "our activities\l"
	.string "underground."
	.string "\pNow you can have\n"
	.string "fun watching us\l"
	.string "stir up trouble!$"

SlowpokeWellB1F_Johto_GruntM2SeenText:
	.string "Quit taking SLOW-\n"
	.string "POKETAILS?"
	.string "\pIf we obeyed you,\n"
	.string "TEAM ROCKET's rep\l"
	.string "would be ruined!$"

SlowpokeWellB1F_Johto_GruntM2BeatenText:
	.string "Just…\n"
	.string "Too strong…$"

SlowpokeWellB1F_Johto_GruntM2AfterBattleText:
	.string "We need the money,\n"
	.string "but selling SLOW-\l"
	.string "POKETAILS?"
	.string "\pIt's tough being a\n"
	.string "ROCKET GRUNT!$"

SlowpokeWellB1F_Johto_GruntF1SeenText:
	.string "Stop taking TAILS?"
	.string "\pYeah, just try to\n"
	.string "defeat all of us!$"

SlowpokeWellB1F_Johto_GruntF1BeatenText:
	.string "You rotten brat!$"

SlowpokeWellB1F_Johto_GruntF1AfterBattleText:
	.string "SLOWPOKETAILS\n"
	.string "grow back fast!"
	.string "\pWhat's wrong with\n"
	.string "selling them?$"

SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeWithMailText:
	.string "A SLOWPOKE with\n"
	.string "its TAIL cut off…"
	.string "\pHuh? It has MAIL.\n"
	.string "Read it?$"

SlowpokeWellB1F_Johto_SlowpokeWellB1FSlowpokeMailText:
	.string "{PLAYER} read the\n"
	.string "MAIL."
	.string "\pBe good and look\n"
	.string "after the house"
	.string "\pwith Grandpa and\n"
	.string "SLOWPOKE."
	.string "\pLove, Dad$"

SlowpokeWellB1F_Johto_SlowpokeWellB1FTaillessSlowpokeText:
	.string "A SLOWPOKE with\n"
	.string "its TAIL cut off…$"
