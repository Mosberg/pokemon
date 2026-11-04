FastShipCabins_NNW_NNE_NE_Johto_MapScripts::
	.byte 0

FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorScript_Entry::
	lockall
	goto FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorScript

FastShipCabins_NNW_NNE_NE_Johto_FastShipCabins_NNW_NNE_NETrashcan_Entry::
	lockall
	goto FastShipCabins_NNW_NNE_NE_Johto_FastShipCabins_NNW_NNE_NETrashcan


FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainermSean::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_SEAN, FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanSeenText, FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_SEAN
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainermSean_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainermSean_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainerfCarol::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_CAROL, FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolSeenText, FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_CAROL
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainerfCarol_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerCooltrainerfCarol_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_TrainerPokemaniacEthan::
	trainerbattle_single TRAINER_JOHTO_POKEMANIAC_ETHAN, FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanSeenText, FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanBeatenText
	setflag FLAG_JOHTO_BEAT_POKEMANIAC_ETHAN
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerPokemaniacEthan_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerPokemaniacEthan_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_TrainerHikerNoland::
	trainerbattle_single TRAINER_JOHTO_HIKER_NOLAND, FastShipCabins_NNW_NNE_NE_Johto_HikerNolandSeenText, FastShipCabins_NNW_NNE_NE_Johto_HikerNolandBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_NOLAND
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerHikerNoland_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerHikerNoland_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_HikerNolandAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_TrainerGentlemanEdward::
	trainerbattle_single TRAINER_JOHTO_GENTLEMAN_EDWARD, FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardSeenText, FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardBeatenText
	setflag FLAG_JOHTO_BEAT_GENTLEMAN_EDWARD
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerGentlemanEdward_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerGentlemanEdward_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_TrainerBurglarCorey::
	trainerbattle_single TRAINER_JOHTO_BURGLAR_COREY, FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreySeenText, FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreyBeatenText
	setflag FLAG_JOHTO_BEAT_BURGLAR_COREY
	lock
	faceplayer
	goto FastShipCabins_NNW_NNE_NE_Johto_TrainerBurglarCorey_Script

FastShipCabins_NNW_NNE_NE_Johto_TrainerBurglarCorey_Script:
	message FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorScript:
	playbgm MUS_DUMMY, FALSE
	faceplayer
	message FastShipCabins_NNW_NNE_NE_Johto_SailorStanlySeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_SAILOR_STANLY, FastShipCabins_NNW_NNE_NE_Johto_SailorStanlyBeatenText
	special HealPlayerParty
	setflag FLAG_JOHTO_BEAT_SAILOR_STANLY
	message FastShipCabins_NNW_NNE_NE_Johto_SailorStanlyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_FAST_SHIP_LAZY_SAILOR
	setvar VAR_JOHTO_SCENE_FAST_SHIP_B1F, 1
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorScript_Movement2
	applymovement 5, FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorLeavesMovement1
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorScript_Movement2:
	applymovement 5, FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorLeavesMovement2
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	releaseall
	end

FastShipCabins_NNW_NNE_NE_Johto_FastShipCabins_NNW_NNE_NETrashcan:
	goto Johto_Std_TrashCanScript

FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorLeavesMovement1:
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

FastShipCabins_NNW_NNE_NE_Johto_FastShipLazySailorLeavesMovement2:
	walk_down
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanSeenText:
	.string "I'm going to KANTO\n"
	.string "to test my skills.$"

FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanBeatenText:
	.string "I wanted to win!$"

FastShipCabins_NNW_NNE_NE_Johto_CooltrainermSeanAfterBattleText:
	.string "Trainers from\n"
	.string "JOHTO can battle"
	.string "\pwith KANTO GYM\n"
	.string "LEADERS.$"

FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolSeenText:
	.string "I'm training to\n"
	.string "become the CHAMP!$"

FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolBeatenText:
	.string "What's so differ-\n"
	.string "ent between us?$"

FastShipCabins_NNW_NNE_NE_Johto_CooltrainerfCarolAfterBattleText:
	.string "I'm going to beat\n"
	.string "you someday!$"

FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanSeenText:
	.string "Do you know LILY?\n"
	.string "She's a hot DJ in\l"
	.string "KANTO.$"

FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanBeatenText:
	.string "Gyaaaah!$"

FastShipCabins_NNW_NNE_NE_Johto_PokemaniacEthanAfterBattleText:
	.string "LILY's nice, but\n"
	.string "MARY's the best!"
	.string "\pI want to check\n"
	.string "out JOHTO's radio\l"
	.string "programs!$"

FastShipCabins_NNW_NNE_NE_Johto_HikerNolandSeenText:
	.string "Are you alone?\n"
	.string "Then let's battle!$"

FastShipCabins_NNW_NNE_NE_Johto_HikerNolandBeatenText:
	.string "That's too much to\n"
	.string "handle!$"

FastShipCabins_NNW_NNE_NE_Johto_HikerNolandAfterBattleText:
	.string "I wonder if there\n"
	.string "are any mountains"
	.string "\pworth climbing in\n"
	.string "KANTO?$"

FastShipCabins_NNW_NNE_NE_Johto_SailorStanlySeenText:
	.string "Yeah, I'm a sail-\n"
	.string "or, all right."
	.string "\pI wasn't goofing\n"
	.string "off!"
	.string "\pThis cabin was\n"
	.string "vacant, so I just\l"
	.string "took a quick nap!"
	.string "\pAh, forget it!\n"
	.string "Let's battle!$"

FastShipCabins_NNW_NNE_NE_Johto_SailorStanlyBeatenText:
	.string "Sorry! It's all my\n"
	.string "fault!$"

FastShipCabins_NNW_NNE_NE_Johto_SailorStanlyAfterBattleText:
	.string "Being a sailor, I\n"
	.string "have to do phys-\l"
	.string "ical labor. It's\l"
	.string "exhausting!$"

FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardSeenText:
	.string "Oh, no. I've lost\n"
	.string "something that's\l"
	.string "very important.$"

FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardBeatenText:
	.string "I… I can't find\n"
	.string "it…$"

FastShipCabins_NNW_NNE_NE_Johto_GentlemanEdwardAfterBattleText:
	.string "I give up.\n"
	.string "You don't have to"
	.string "\plook. Just forget\n"
	.string "about it!$"

FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreySeenText:
	.string "Yeehaw!\n"
	.string "Lucky!$"

FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreyBeatenText:
	.string "How unlucky!\n"
	.string "I lost!$"

FastShipCabins_NNW_NNE_NE_Johto_BurglarCoreyAfterBattleText:
	.string "I found a pretty\n"
	.string "coin here."
	.string "\pSomeone must have\n"
	.string "lost it…$"
