EcruteakPokecenter1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EcruteakPokecenter1F_Johto_OnFrame
	.byte 0

EcruteakPokecenter1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_ECRUTEAK_POKECENTER_1F, 0, EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_Entry
	.2byte 0

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FNurseScript_Entry::
	lockall
	goto EcruteakPokecenter1F_Johto_EcruteakPokecenter1FNurseScript

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FPokefanMScript_Entry::
	lockall
	goto EcruteakPokecenter1F_Johto_EcruteakPokecenter1FPokefanMScript

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto EcruteakPokecenter1F_Johto_EcruteakPokecenter1FCooltrainerFScript

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FGymGuideScript_Entry::
	lockall
	goto EcruteakPokecenter1F_Johto_EcruteakPokecenter1FGymGuideScript

EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_Entry::
	lockall
	goto EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript


EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript:
	delay 30
	playse SE_EXIT
	clearflag FLAG_JOHTO_ECRUTEAK_POKE_CENTER_BILL
	addobject 5
	waitse
	applymovement 5, EcruteakPokecenter1F_Johto_EcruteakPokecenter1FBillMovement1
	waitmovement 5
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakPokecenter1F_Johto_EcruteakPokecenter1FPlayerMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	delay 10
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 30
	applymovement 1, Johto_Movement_Face_Up
	waitmovement 1
	delay 10
	applymovement 1, Johto_Movement_Face_Down
	waitmovement 1
	delay 20
	applymovement 5, Johto_Movement_Face_Down
	waitmovement 5
	delay 10
	message EcruteakPokecenter1F_Johto_EcruteakPokecenter1F_BillText1
	waitmessage
	waitbuttonpress
	goto EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_PointlessJump

EcruteakPokecenter1F_Johto_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_PointlessJump:
	message EcruteakPokecenter1F_Johto_EcruteakPokecenter1F_BillText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 5, EcruteakPokecenter1F_Johto_EcruteakPokecenter1FBillMovement2
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	clearflag FLAG_JOHTO_MET_BILL
	setflag FLAG_JOHTO_ENGINE_TIME_CAPSULE
	setvar VAR_JOHTO_SCENE_ECRUTEAK_POKECENTER_1F, 1
	waitse
	releaseall
	end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_ECRUTEAK_CITY
	goto Johto_Std_PokecenterNurseScript

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FPokefanMScript:
	@ TODO unsupported: special CheckMobileAdapterStatusSpecial
	goto Johto_EventScript_Unimplemented

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FCooltrainerFScript:
	faceplayer
	message EcruteakPokecenter1F_Johto_EcruteakPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FGymGuideScript:
	faceplayer
	message EcruteakPokecenter1F_Johto_EcruteakPokecenter1FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FBillMovement1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	face_up
	step_end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FBillMovement2:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FPlayerMovement1:
	walk_up
	walk_up
	walk_up
	step_end

EcruteakPokecenter1F_Johto_EcruteakPokecenter1F_BillText1:
	.string "Hi, I'm BILL. And\n"
	.string "who are you?"
	.string "\pHmm, {PLAYER}, huh?\n"
	.string "You've come at the\l"
	.string "right time.$"

EcruteakPokecenter1F_Johto_EcruteakPokecenter1F_BillText2:
	.string "I just finished\n"
	.string "adjustments on my\l"
	.string "TIME CAPSULE."
	.string "\pYou know that\n"
	.string "POKéMON can be\l"
	.string "traded, right?"
	.string "\pMy TIME CAPSULE\n"
	.string "was developed to"
	.string "\penable trades with\n"
	.string "the past."
	.string "\pBut you can't send\n"
	.string "anything that"
	.string "\pdidn't exist in\n"
	.string "the past."
	.string "\pIf you did, the PC\n"
	.string "in the past would\l"
	.string "have a breakdown."
	.string "\pSo you have to\n"
	.string "remove anything"
	.string "\pthat wasn't around\n"
	.string "in the past."
	.string "\pPut simply, no\n"
	.string "sending new moves"
	.string "\por new POKéMON in\n"
	.string "the TIME CAPSULE."
	.string "\pDon't you worry.\n"
	.string "I'm done with the\l"
	.string "adjustments."
	.string "\pTomorrow, TIME\n"
	.string "CAPSULES will be"
	.string "\prunning at all\n"
	.string "POKéMON CENTERS."
	.string "\pI have to hurry on\n"
	.string "back to GOLDENROD\l"
	.string "and see my folks."
	.string "\pBuh-bye!$"

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FCooltrainerFText:
	.string "MORTY, the GYM\n"
	.string "LEADER, is soooo\l"
	.string "cool."
	.string "\pHis POKéMON are\n"
	.string "really tough too.$"

EcruteakPokecenter1F_Johto_EcruteakPokecenter1FGymGuideText:
	.string "LAKE OF RAGE…"
	.string "\pThe appearance of\n"
	.string "a GYARADOS swarm…"
	.string "\pI smell a conspir-\n"
	.string "acy. I know it!$"
