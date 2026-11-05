NewBarkTown_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Johto_OnTransition
	.byte 0

NewBarkTown_Johto_OnTransition:
	call NewBarkTown_Johto_NewBarkTownFlypointCallback_Cb
	end

NewBarkTown_Johto_NewBarkTownTeacherScript_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownTeacherScript

NewBarkTown_Johto_NewBarkTownFisherScript_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownFisherScript

NewBarkTown_Johto_NewBarkTownRivalScript_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownRivalScript

NewBarkTown_Johto_NewBarkTownSign_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownSign

NewBarkTown_Johto_NewBarkTownPlayersHouseSign_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownPlayersHouseSign

NewBarkTown_Johto_NewBarkTownElmsLabSign_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownElmsLabSign

NewBarkTown_Johto_NewBarkTownElmsHouseSign_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTownElmsHouseSign

NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene1_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene1

NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene2_Entry::
	lockall
	goto NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene2


NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene1:
	playbgm MUS_ENCOUNTER_FEMALE, FALSE
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message NewBarkTown_Johto_Text_WaitPlayer
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, NewBarkTown_Johto_NewBarkTown_TeacherRunsToYouMovement1
	waitmovement 1
	message NewBarkTown_Johto_Text_WhatDoYouThinkYoureDoing
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement1
	applymovement 1, NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement1
	waitmovement 1
	message NewBarkTown_Johto_Text_ItsDangerousToGoAlone
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	releaseall
	end

NewBarkTown_Johto_NewBarkTown_TeacherStopsYouScene2:
	playbgm MUS_ENCOUNTER_FEMALE, FALSE
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message NewBarkTown_Johto_Text_WaitPlayer
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, NewBarkTown_Johto_NewBarkTown_TeacherRunsToYouMovement2
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message NewBarkTown_Johto_Text_WhatDoYouThinkYoureDoing
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement2
	applymovement 1, NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement2
	waitmovement 1
	message NewBarkTown_Johto_Text_ItsDangerousToGoAlone
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	releaseall
	end

NewBarkTown_Johto_NewBarkTownTeacherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, NewBarkTown_Johto_NewBarkTownTeacherScript_CallMom
	goto_if_set FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, NewBarkTown_Johto_NewBarkTownTeacherScript_TellMomYoureLeaving
	goto_if_set FLAG_JOHTO_GOT_A_POKEMON_FROM_ELM, NewBarkTown_Johto_NewBarkTownTeacherScript_MonIsAdorable
	message NewBarkTown_Johto_Text_GearIsImpressive
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownTeacherScript_MonIsAdorable:
	message NewBarkTown_Johto_Text_YourMonIsAdorable
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownTeacherScript_TellMomYoureLeaving:
	message NewBarkTown_Johto_Text_TellMomIfLeaving
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownTeacherScript_CallMom:
	message NewBarkTown_Johto_Text_CallMomOnGear
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownFisherScript:
	faceplayer
	message NewBarkTown_Johto_Text_ElmDiscoveredNewMon
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownRivalScript:
	message NewBarkTown_Johto_NewBarkTownRivalText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Left
	waitmovement 3
	message NewBarkTown_Johto_NewBarkTownRivalText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, NewBarkTown_Johto_NewBarkTown_RivalPushesYouAwayMovement
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Johto_NewBarkTown_RivalPushesYouAwayMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	delay 5
	playse SE_M_TAIL_WHIP
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Johto_NewBarkTown_RivalShovesYouOutMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, NewBarkTown_Johto_NewBarkTown_RivalReturnsToTheShadowsMovement
	waitmovement 3
	releaseall
	end

NewBarkTown_Johto_NewBarkTownSign:
	message NewBarkTown_Johto_NewBarkTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownPlayersHouseSign:
	message NewBarkTown_Johto_NewBarkTownPlayersHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownElmsLabSign:
	message NewBarkTown_Johto_NewBarkTownElmsLabSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownElmsHouseSign:
	message NewBarkTown_Johto_NewBarkTownElmsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

NewBarkTown_Johto_NewBarkTownFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_NEW_BARK
	clearflag FLAG_JOHTO_FIRST_TIME_BANKING_WITH_MOM
	return

NewBarkTown_Johto_NewBarkTown_TeacherRunsToYouMovement1:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_Johto_NewBarkTown_TeacherRunsToYouMovement2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement1:
	walk_right
	walk_right
	walk_right
	walk_right
	face_left
	step_end

NewBarkTown_Johto_NewBarkTown_TeacherBringsYouBackMovement2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_left
	step_end

NewBarkTown_Johto_NewBarkTown_RivalPushesYouAwayMovement:
	face_up
	walk_down
	step_end

NewBarkTown_Johto_NewBarkTown_RivalShovesYouOutMovement:
	face_up
	lock_facing_direction
	jump_down
	unlock_facing_direction
	step_end

NewBarkTown_Johto_NewBarkTown_RivalReturnsToTheShadowsMovement:
	walk_right
	step_end

NewBarkTown_Johto_Text_GearIsImpressive:
	.string "Wow, your POKéGEAR\n"
	.string "is impressive!"
	.string "\pDid your mom get\n"
	.string "it for you?$"

NewBarkTown_Johto_Text_WaitPlayer:
	.string "Wait, {PLAYER}!$"

NewBarkTown_Johto_Text_WhatDoYouThinkYoureDoing:
	.string "What do you think\n"
	.string "you're doing?$"

NewBarkTown_Johto_Text_ItsDangerousToGoAlone:
	.string "It's dangerous to\n"
	.string "go out without a\l"
	.string "POKéMON!"
	.string "\pWild POKéMON\n"
	.string "jump out of the"
	.string "\pgrass on the way\n"
	.string "to the next town.$"

NewBarkTown_Johto_Text_YourMonIsAdorable:
	.string "Oh! Your POKéMON\n"
	.string "is adorable!\l"
	.string "I wish I had one!$"

NewBarkTown_Johto_Text_TellMomIfLeaving:
	.string "Hi, {PLAYER}!\n"
	.string "Leaving again?"
	.string "\pYou should tell\n"
	.string "your mom if you\l"
	.string "are leaving.$"

NewBarkTown_Johto_Text_CallMomOnGear:
	.string "Call your mom on\n"
	.string "your POKéGEAR to"
	.string "\plet her know how\n"
	.string "you're doing.$"

NewBarkTown_Johto_Text_ElmDiscoveredNewMon:
	.string "Yo, {PLAYER}!"
	.string "\pI hear PROF.ELM\n"
	.string "discovered some\l"
	.string "new POKéMON.$"

NewBarkTown_Johto_NewBarkTownRivalText1:
	.string "…"
	.string "\pSo this is the\n"
	.string "famous ELM POKéMON\l"
	.string "LAB…$"

NewBarkTown_Johto_NewBarkTownRivalText2:
	.string "…What are you\n"
	.string "staring at?$"

NewBarkTown_Johto_NewBarkTownSignText:
	.string "NEW BARK TOWN"
	.string "\pThe Town Where the\n"
	.string "Winds of a New\l"
	.string "Beginning Blow$"

NewBarkTown_Johto_NewBarkTownPlayersHouseSignText:
	.string "{PLAYER}'s House$"

NewBarkTown_Johto_NewBarkTownElmsLabSignText:
	.string "ELM POKéMON LAB$"

NewBarkTown_Johto_NewBarkTownElmsHouseSignText:
	.string "ELM'S HOUSE$"
