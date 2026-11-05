TradeCenter_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TradeCenter_Johto_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TradeCenter_Johto_OnFrame
	.byte 0

TradeCenter_Johto_OnTransition:
	call TradeCenter_Johto_TradeCenterSetWhichChrisCallback_Cb
	end

TradeCenter_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_TRADE_CENTER, 0, TradeCenter_Johto_TradeCenterInitializeAndPreparePokecenter2FScript_Entry
	.2byte 0

TradeCenter_Johto_TradeCenterConsoleScript_Entry::
	lockall
	goto TradeCenter_Johto_TradeCenterConsoleScript

TradeCenter_Johto_TradeCenterInitializeAndPreparePokecenter2FScript_Entry::
	lockall
	goto TradeCenter_Johto_TradeCenterInitializeAndPreparePokecenter2FScript


TradeCenter_Johto_TradeCenterInitializeAndPreparePokecenter2FScript:
	setvar VAR_JOHTO_SCENE_TRADE_CENTER, 1
	setvar VAR_JOHTO_SCENE_POKECENTER_2F, 1
	releaseall
	end

TradeCenter_Johto_TradeCenterConsoleScript:
	message TradeCenter_Johto_Text_LinkCableNotConnected
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TradeCenter_Johto_TradeCenterSetWhichChrisCallback_Cb:
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	return

TradeCenter_Johto_Text_LinkCableNotConnected:
	.string "The Game Link cable\n"
	.string "is not connected.$"

