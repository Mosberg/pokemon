Colosseum_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Colosseum_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Colosseum_Johto_OnFrame
	.byte 0

Colosseum_Johto_OnTransition:
	call Colosseum_Johto_ColosseumSetWhichChrisCallback_Cb
	call Colosseum_Johto_ColosseumPreparePokecenter2FCallback_Cb
	end

Colosseum_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_COLOSSEUM, 0, Colosseum_Johto_ColosseumInitializeAndPreparePokecenter2FScript_Entry
	.2byte 0

Colosseum_Johto_CableClubFriendScript_Entry::
	lockall
	goto Colosseum_Johto_CableClubFriendScript

Colosseum_Johto_ColosseumConsoleScript_Entry::
	lockall
	goto Colosseum_Johto_ColosseumConsoleScript

Colosseum_Johto_ColosseumInitializeAndPreparePokecenter2FScript_Entry::
	lockall
	goto Colosseum_Johto_ColosseumInitializeAndPreparePokecenter2FScript


Colosseum_Johto_ColosseumInitializeAndPreparePokecenter2FScript:
	setvar VAR_JOHTO_SCENE_COLOSSEUM, 1
	setvar VAR_JOHTO_SCENE_POKECENTER_2F, 2
	releaseall
	end

Colosseum_Johto_ColosseumConsoleScript:
	message Colosseum_Johto_Text_LinkCableNotConnected
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Colosseum_Johto_CableClubFriendScript:
	message Colosseum_Johto_Text_FriendReady
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Colosseum_Johto_ColosseumSetWhichChrisCallback_Cb:
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	return

Colosseum_Johto_Text_LinkCableNotConnected:
	.string "The Game Link cable\n"
	.string "is not connected.$"

Colosseum_Johto_Text_FriendReady:
	.string "Your friend is\n"
	.string "ready.$"


Colosseum_Johto_ColosseumPreparePokecenter2FCallback_Cb:
	setvar VAR_JOHTO_SCENE_POKECENTER_2F, 2
	return
