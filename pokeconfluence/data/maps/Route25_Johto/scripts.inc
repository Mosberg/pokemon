Route25_Johto_MapScripts::
		map_script MAP_SCRIPT_ON_LOAD, Route25_Johto_OnLoad
	.byte 0

Route25_Johto_TrainerCooltrainermKevin_Entry::
	lockall
	goto Route25_Johto_TrainerCooltrainermKevin

Route25_Johto_Route25Protein_Entry::
	lockall
	goto Route25_Johto_Route25Protein

Route25_Johto_BillsHouseSign_Entry::
	lockall
	goto Route25_Johto_BillsHouseSign

Route25_Johto_Route25MistyDate1Script_Entry::
	lockall
	goto Route25_Johto_Route25MistyDate1Script

Route25_Johto_Route25MistyDate2Script_Entry::
	lockall
	goto Route25_Johto_Route25MistyDate2Script


Route25_Johto_Route25MistyDate1Script:
	applymovement 1, Johto_Movement_Emote_heart
	waitmovement 1
	delay 30
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	applymovement 2, Route25_Johto_Route25MistysDateLeavesMovement1
	waitmovement 2
	removeobject 2
	delay 15
	playbgm MUS_DUMMY, FALSE
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	delay 10
	applymovement 1, Route25_Johto_Route25MistyApproachesPlayerMovement1
	waitmovement 1
	message Route25_Johto_Route25MistyDateText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Route25_Johto_Route25MistyLeavesPlayerMovement1
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Route25_Johto_Route25MistyLeavesMovement
	waitmovement 1
	removeobject 1
	clearflag FLAG_JOHTO_TRAINERS_IN_CERULEAN_GYM
	setvar VAR_JOHTO_SCENE_ROUTE_25, 0
	fadedefaultbgm
	releaseall
	end

Route25_Johto_Route25MistyDate2Script:
	applymovement 1, Johto_Movement_Emote_heart
	waitmovement 1
	delay 30
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	applymovement 2, Route25_Johto_Route25MistysDateLeavesMovement2
	waitmovement 2
	removeobject 2
	delay 15
	playbgm MUS_DUMMY, FALSE
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	delay 10
	applymovement 1, Route25_Johto_Route25MistyApproachesPlayerMovement2
	waitmovement 1
	message Route25_Johto_Route25MistyDateText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Route25_Johto_Route25MistyLeavesPlayerMovement2
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Route25_Johto_Route25MistyLeavesMovement
	waitmovement 1
	removeobject 1
	clearflag FLAG_JOHTO_TRAINERS_IN_CERULEAN_GYM
	setvar VAR_JOHTO_SCENE_ROUTE_25, 0
	fadedefaultbgm
	releaseall
	end

Route25_Johto_TrainerSchoolboyDudley::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_DUDLEY, Route25_Johto_SchoolboyDudleySeenText, Route25_Johto_SchoolboyDudleyBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_DUDLEY
	lock
	faceplayer
	goto Route25_Johto_TrainerSchoolboyDudley_Script

Route25_Johto_TrainerSchoolboyDudley_Script:
	message Route25_Johto_SchoolboyDudleyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerLassEllen::
	trainerbattle_single TRAINER_JOHTO_LASS_ELLEN, Route25_Johto_LassEllenSeenText, Route25_Johto_LassEllenBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_ELLEN
	lock
	faceplayer
	goto Route25_Johto_TrainerLassEllen_Script

Route25_Johto_TrainerLassEllen_Script:
	message Route25_Johto_LassEllenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerSchoolboyJoe::
	trainerbattle_single TRAINER_JOHTO_SCHOOLBOY_JOE, Route25_Johto_SchoolboyJoeSeenText, Route25_Johto_SchoolboyJoeBeatenText
	setflag FLAG_JOHTO_BEAT_SCHOOLBOY_JOE
	lock
	faceplayer
	goto Route25_Johto_TrainerSchoolboyJoe_Script

Route25_Johto_TrainerSchoolboyJoe_Script:
	message Route25_Johto_SchoolboyJoeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerLassLaura::
	trainerbattle_single TRAINER_JOHTO_LASS_LAURA, Route25_Johto_LassLauraSeenText, Route25_Johto_LassLauraBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_LAURA
	lock
	faceplayer
	goto Route25_Johto_TrainerLassLaura_Script

Route25_Johto_TrainerLassLaura_Script:
	message Route25_Johto_LassLauraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerCamperLloyd::
	trainerbattle_single TRAINER_JOHTO_CAMPER_LLOYD, Route25_Johto_CamperLloydSeenText, Route25_Johto_CamperLloydBeatenText
	setflag FLAG_JOHTO_BEAT_CAMPER_LLOYD
	lock
	faceplayer
	goto Route25_Johto_TrainerCamperLloyd_Script

Route25_Johto_TrainerCamperLloyd_Script:
	message Route25_Johto_CamperLloydAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerLassShannon::
	trainerbattle_single TRAINER_JOHTO_LASS_SHANNON, Route25_Johto_LassShannonSeenText, Route25_Johto_LassShannonBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_SHANNON
	lock
	faceplayer
	goto Route25_Johto_TrainerLassShannon_Script

Route25_Johto_TrainerLassShannon_Script:
	message Route25_Johto_LassShannonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerSupernerdPat::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_PAT, Route25_Johto_SupernerdPatSeenText, Route25_Johto_SupernerdPatBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_PAT
	lock
	faceplayer
	goto Route25_Johto_TrainerSupernerdPat_Script

Route25_Johto_TrainerSupernerdPat_Script:
	message Route25_Johto_SupernerdPatAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_TrainerCooltrainermKevin:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_COOLTRAINERM_KEVIN, Route25_Johto_TrainerCooltrainermKevin_AfterBattle
	goto_if_set FLAG_JOHTO_CLEARED_NUGGET_BRIDGE, Route25_Johto_TrainerCooltrainermKevin_AfterNuggetBridge
	message Route25_Johto_CooltrainermKevinNuggetText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, 0, Route25_Johto_TrainerCooltrainermKevin_NoRoomForNugget
	setflag FLAG_JOHTO_CLEARED_NUGGET_BRIDGE

Route25_Johto_TrainerCooltrainermKevin_AfterNuggetBridge:
	message Route25_Johto_CooltrainermKevinSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_COOLTRAINERM_KEVIN, Route25_Johto_CooltrainermKevinBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_KEVIN

Route25_Johto_TrainerCooltrainermKevin_AfterBattle:
	message Route25_Johto_CooltrainermKevinAfterBattleText
	waitmessage
	waitbuttonpress

Route25_Johto_TrainerCooltrainermKevin_NoRoomForNugget:
	closemessage
	releaseall
	end

Route25_Johto_BillsHouseSign:
	message Route25_Johto_BillsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route25_Johto_Route25Protein:
	finditem ITEM_PROTEIN
	releaseall
	end

Route25_Johto_Route25MistysDateLeavesMovement1:
	walk_fast_down
	step_end

Route25_Johto_Route25MistysDateLeavesMovement2:
	walk_fast_down
	walk_fast_down
	step_end

Route25_Johto_Route25MistyApproachesPlayerMovement1:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Route25_Johto_Route25MistyApproachesPlayerMovement2:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Route25_Johto_Route25MistyLeavesPlayerMovement1:
	walk_down
	walk_left
	step_end

Route25_Johto_Route25MistyLeavesPlayerMovement2:
	walk_up
	walk_left
	step_end

Route25_Johto_Route25MistyLeavesMovement:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route25_Johto_Route25MistyDateText:
	.string "MISTY: Aww! Why\n"
	.string "did you have to"
	.string "\pshow up and bug us\n"
	.string "now?"
	.string "\pDo you know what\n"
	.string "they call people\l"
	.string "like you?"
	.string "\pPests! You heard\n"
	.string "me right, pest!"
	.string "\p…"
	.string "\p…Oh? Those BADGES\n"
	.string "you have… Are they\l"
	.string "JOHTO GYM BADGES?"
	.string "\pIf you have eight,\n"
	.string "you must be good."
	.string "\pOK, then. Come to\n"
	.string "CERULEAN GYM."
	.string "\pI'll be happy to\n"
	.string "take you on."
	.string "\pI'm MISTY, the\n"
	.string "GYM LEADER in\l"
	.string "CERULEAN.$"

Route25_Johto_SchoolboyDudleySeenText:
	.string "Beat the six of us\n"
	.string "trainers to win a\l"
	.string "fabulous prize!"
	.string "\pThink you've got\n"
	.string "what it takes?$"

Route25_Johto_SchoolboyDudleyBeatenText:
	.string "Whoo! Good stuff.$"

Route25_Johto_SchoolboyDudleyAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_LassEllenSeenText:
	.string "I'm second.\n"
	.string "Now it's serious!$"

Route25_Johto_LassEllenBeatenText:
	.string "How could I lose?$"

Route25_Johto_LassEllenAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_SchoolboyJoeSeenText:
	.string "Here's No. 3!\n"
	.string "I won't be easy.$"

Route25_Johto_SchoolboyJoeBeatenText:
	.string "Ow! Stomped flat!$"

Route25_Johto_SchoolboyJoeAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_LassLauraSeenText:
	.string "I'm No. 4!\n"
	.string "Getting tired?$"

Route25_Johto_LassLauraBeatenText:
	.string "I lost too…$"

Route25_Johto_LassLauraAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_CamperLloydSeenText:
	.string "OK! I'm No. 5.\n"
	.string "I'll stomp you!$"

Route25_Johto_CamperLloydBeatenText:
	.string "Whoa! Too much.$"

Route25_Johto_CamperLloydAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_LassShannonSeenText:
	.string "I'm the last in\n"
	.string "line, but I tell\l"
	.string "you, I'm tough!$"

Route25_Johto_LassShannonBeatenText:
	.string "You're kidding.$"

Route25_Johto_LassShannonAfterBattleText:
	.string "I did my best.\n"
	.string "I have no regrets.$"

Route25_Johto_SupernerdPatSeenText:
	.string "Mufufufu…"
	.string "\pI have nothing to\n"
	.string "do with the six-\l"
	.string "pack trainers."
	.string "\pI waited here to\n"
	.string "beat you when you"
	.string "\pwere tired out by\n"
	.string "all the battles.$"

Route25_Johto_SupernerdPatBeatenText:
	.string "Aren't you tired\n"
	.string "at all?$"

Route25_Johto_SupernerdPatAfterBattleText:
	.string "I'm sorry… I won't\n"
	.string "cheat anymore…$"

Route25_Johto_CooltrainermKevinNuggetText:
	.string "You took on one\n"
	.string "more battle than"
	.string "\pyou expected, but\n"
	.string "you won anyway."
	.string "\pAs promised, you\n"
	.string "win a prize.$"

Route25_Johto_CooltrainermKevinSeenText:
	.string "But after seeing\n"
	.string "how you battle, I"
	.string "\pwant to see how\n"
	.string "I'll fare."
	.string "\pHow about it? Let\n"
	.string "me take you on.$"

Route25_Johto_CooltrainermKevinBeatenText:
	.string "I've never had a\n"
	.string "battle this good!$"

Route25_Johto_CooltrainermKevinAfterBattleText:
	.string "That was a great\n"
	.string "battle!"
	.string "\pYou and your POKé-\n"
	.string "MON are truly out-\l"
	.string "standing!$"

Route25_Johto_BillsHouseSignText:
	.string "SEA COTTAGE\n"
	.string "BILL'S HOUSE$"

Route25_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_ROUTE_25_0, Route25_Johto_CutTree0_Keep
	setmetatile 34, 6, 533, 0
	setmetatile 35, 6, 533, 0
	setmetatile 34, 7, 541, 1
	setmetatile 35, 7, 541, 1
Route25_Johto_CutTree0_Keep:
	end

Route25_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, Route25_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_ROUTE_25_0
	setmetatile 34, 6, 533, 0
	setmetatile 35, 6, 533, 0
	setmetatile 34, 7, 541, 1
	setmetatile 35, 7, 541, 1
	special DrawWholeMapView
Route25_Johto_CutTree0_Done:
	releaseall
	end
