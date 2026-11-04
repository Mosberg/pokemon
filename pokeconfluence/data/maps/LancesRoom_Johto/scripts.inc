LancesRoom_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LancesRoom_Johto_OnFrame
	.byte 0

LancesRoom_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_LANCES_ROOM, 0, LancesRoom_Johto_LancesRoomDoorLocksBehindYouScript_Entry
	.2byte 0

LancesRoom_Johto_LancesRoomLanceScript_Entry::
	lockall
	goto LancesRoom_Johto_LancesRoomLanceScript

LancesRoom_Johto_Script_ApproachLanceFromLeft_Entry::
	lockall
	goto LancesRoom_Johto_Script_ApproachLanceFromLeft

LancesRoom_Johto_Script_ApproachLanceFromRight_Entry::
	lockall
	goto LancesRoom_Johto_Script_ApproachLanceFromRight

LancesRoom_Johto_LancesRoomDoorLocksBehindYouScript_Entry::
	lockall
	goto LancesRoom_Johto_LancesRoomDoorLocksBehindYouScript


LancesRoom_Johto_LancesRoomDoorLocksBehindYouScript:
	applymovement OBJ_EVENT_ID_PLAYER, LancesRoom_Johto_LancesRoom_EnterMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_STRENGTH
	setmetatile 4, 22, 582, 0
	setmetatile 5, 22, 583, 0
	setmetatile 4, 23, 543, 1
	setmetatile 5, 23, 544, 1
	special DrawWholeMapView
	closemessage
	setvar VAR_JOHTO_SCENE_LANCES_ROOM, 1
	setflag FLAG_JOHTO_LANCES_ROOM_ENTRANCE_CLOSED
	releaseall
	end

LancesRoom_Johto_Script_ApproachLanceFromLeft:
	fadeoutbgm 4
	applymovement OBJ_EVENT_ID_PLAYER, LancesRoom_Johto_MovementData_ApproachLanceFromLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	goto LancesRoom_Johto_LancesRoomLanceScript

LancesRoom_Johto_Script_ApproachLanceFromRight:
	fadeoutbgm 4
	applymovement OBJ_EVENT_ID_PLAYER, LancesRoom_Johto_MovementData_ApproachLanceFromRight
	waitmovement OBJ_EVENT_ID_PLAYER

LancesRoom_Johto_LancesRoomLanceScript:
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message LancesRoom_Johto_LanceBattleIntroText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_JOHTO_CHAMPION_LANCE, LancesRoom_Johto_LanceBattleWinText
	setflag FLAG_JOHTO_BEAT_CHAMPION_LANCE
	message LancesRoom_Johto_LanceBattleAfterText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_DOOR
	setmetatile 4, 0, 535, 1
	setmetatile 5, 0, 536, 1
	setmetatile 4, 1, 537, 0
	setmetatile 5, 1, 537, 0
	special DrawWholeMapView
	closemessage
	setflag FLAG_JOHTO_LANCES_ROOM_ENTRANCE_CLOSED
	fadeoutbgm 4
	delay 30
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	clearflag FLAG_JOHTO_LANCES_ROOM_OAK_AND_MARY
	addobject 2
	applymovement 2, LancesRoom_Johto_LancesRoomMovementData_MaryRushesIn
	waitmovement 2
	message LancesRoom_Johto_LancesRoomMaryOhNoOakText
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_JOHTO_LANCES_ROOM_OAK_AND_MARY
	addobject 3
	applymovement 3, LancesRoom_Johto_LancesRoomMovementData_OakWalksIn
	waitmovement 3
	applymovement 3, LancesRoom_Johto_LancesRoomMovementData_MaryYieldsToOak
	applymovement 2, LancesRoom_Johto_LancesRoomMovementData_MaryYieldsToOak
	waitmovement 2
	applymovement 3, Johto_Movement_Face_Up
	waitmovement 3
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message LancesRoom_Johto_LancesRoomOakCongratulationsText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, LancesRoom_Johto_LancesRoomMovementData_MaryInterviewChampion
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	message LancesRoom_Johto_LancesRoomMaryInterviewText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, LancesRoom_Johto_LancesRoomMovementData_LancePositionsSelfToGuidePlayerAway
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	message LancesRoom_Johto_LancesRoomNoisyText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Up
	waitmovement 2
	applymovement 3, Johto_Movement_Face_Up
	waitmovement 3
	applymovement OBJ_EVENT_ID_PLAYER, LancesRoom_Johto_LancesRoomMovementData_LanceLeadsPlayerToHallOfFame
	applymovement 1, LancesRoom_Johto_LancesRoomMovementData_LanceLeadsPlayerToHallOfFame
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	applymovement OBJ_EVENT_ID_PLAYER, LancesRoom_Johto_LancesRoomMovementData_PlayerExits
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_EXIT
	removeobject OBJ_EVENT_ID_PLAYER
	applymovement 2, LancesRoom_Johto_LancesRoomMovementData_MaryTriesToFollow
	waitmovement 2
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	message LancesRoom_Johto_LancesRoomMaryNoInterviewText
	waitmessage
	delay 30
	closemessage
	applymovement 2, LancesRoom_Johto_LancesRoomMovementData_MaryRunsBackAndForth
	waitmovement 2
	fadescreen FADE_TO_WHITE
	delay 15
	@ TODO unsupported: warpfacing UP, HALL_OF_FAME, 4, 13
	goto Johto_EventScript_Unimplemented

LancesRoom_Johto_LancesRoom_EnterMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LancesRoom_Johto_MovementData_ApproachLanceFromLeft:
	walk_up
	walk_up
	face_right
	step_end

LancesRoom_Johto_MovementData_ApproachLanceFromRight:
	walk_up
	walk_left
	walk_up
	face_right
	step_end

LancesRoom_Johto_LancesRoomMovementData_MaryRushesIn:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_down
	step_end

LancesRoom_Johto_LancesRoomMovementData_OakWalksIn:
	walk_up
	walk_up
	step_end

LancesRoom_Johto_LancesRoomMovementData_MaryYieldsToOak:
	walk_left
	face_right
	step_end

LancesRoom_Johto_LancesRoomMovementData_MaryInterviewChampion:
	walk_fast_up
	face_right
	step_end

LancesRoom_Johto_LancesRoomMovementData_LancePositionsSelfToGuidePlayerAway:
	walk_up
	walk_left
	face_down
	step_end

LancesRoom_Johto_LancesRoomMovementData_LanceLeadsPlayerToHallOfFame:
	walk_up
	step_end

LancesRoom_Johto_LancesRoomMovementData_PlayerExits:
	walk_up
	step_end

LancesRoom_Johto_LancesRoomMovementData_MaryTriesToFollow:
	walk_up
	walk_right
	face_up
	step_end

LancesRoom_Johto_LancesRoomMovementData_MaryRunsBackAndForth:
	walk_fast_right
	walk_fast_right
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_left
	walk_fast_left
	face_up
	step_end

LancesRoom_Johto_LanceBattleIntroText:
	.string "LANCE: I've been\n"
	.string "waiting for you."
	.string "\p{PLAYER}!"
	.string "\pI knew that you,\n"
	.string "with your skills,"
	.string "\pwould eventually\n"
	.string "reach me here."
	.string "\pThere's no need\n"
	.string "for words now."
	.string "\pWe will battle to\n"
	.string "determine who is"
	.string "\pthe stronger of\n"
	.string "the two of us."
	.string "\pAs the most power-\n"
	.string "ful trainer and as"
	.string "\pthe POKéMON LEAGUE\n"
	.string "CHAMPION…"
	.string "\pI, LANCE the drag-\n"
	.string "on master, accept\l"
	.string "your challenge!$"

LancesRoom_Johto_LanceBattleWinText:
	.string "…It's over."
	.string "\pBut it's an odd\n"
	.string "feeling."
	.string "\pI'm not angry that\n"
	.string "I lost. In fact, I\l"
	.string "feel happy."
	.string "\pHappy that I\n"
	.string "witnessed the rise"
	.string "\pof a great new\n"
	.string "CHAMPION!$"

LancesRoom_Johto_LanceBattleAfterText:
	.string "…Whew."
	.string "\pYou have become\n"
	.string "truly powerful,\l"
	.string "{PLAYER}."
	.string "\pYour POKéMON have\n"
	.string "responded to your"
	.string "\pstrong and up-\n"
	.string "standing nature."
	.string "\pAs a trainer, you\n"
	.string "will continue to"
	.string "\pgrow strong with\n"
	.string "your POKéMON.$"

LancesRoom_Johto_LancesRoomMaryOhNoOakText:
	.string "MARY: Oh, no!\n"
	.string "It's all over!"
	.string "\pPROF.OAK, if you\n"
	.string "weren't so slow…$"

LancesRoom_Johto_LancesRoomOakCongratulationsText:
	.string "PROF.OAK: Ah,\n"
	.string "{PLAYER}!"
	.string "\pIt's been a long\n"
	.string "while."
	.string "\pYou certainly look\n"
	.string "more impressive."
	.string "\pYour conquest of\n"
	.string "the LEAGUE is just\l"
	.string "fantastic!"
	.string "\pYour dedication,\n"
	.string "trust and love for"
	.string "\pyour POKéMON made\n"
	.string "this happen."
	.string "\pYour POKéMON were\n"
	.string "outstanding too."
	.string "\pBecause they be-\n"
	.string "lieved in you as a"
	.string "\ptrainer, they per-\n"
	.string "severed."
	.string "\pCongratulations,\n"
	.string "{PLAYER}!$"

LancesRoom_Johto_LancesRoomMaryInterviewText:
	.string "MARY: Let's inter-\n"
	.string "view the brand new\l"
	.string "CHAMPION!$"

LancesRoom_Johto_LancesRoomNoisyText:
	.string "LANCE: This is\n"
	.string "getting to be a\l"
	.string "bit too noisy…"
	.string "\p{PLAYER}, could you\n"
	.string "come with me?$"

LancesRoom_Johto_LancesRoomMaryNoInterviewText:
	.string "MARY: Oh, wait!\n"
	.string "We haven't done\l"
	.string "the interview!$"
