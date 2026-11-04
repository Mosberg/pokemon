Pokecenter2F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Pokecenter2F_Johto_OnFrame
	.byte 0

Pokecenter2F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 0, Pokecenter2F_Johto_Pokecenter2FCheckMysteryGiftScene_Entry
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 1, Pokecenter2F_Johto_Script_LeftCableTradeCenter_Entry
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 2, Pokecenter2F_Johto_Script_LeftCableColosseum_Entry
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 3, Pokecenter2F_Johto_Script_LeftTimeCapsule_Entry
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 4, Pokecenter2F_Johto_Script_LeftMobileTradeRoom_Entry
	map_script_2 VAR_JOHTO_SCENE_POKECENTER_2F, 5, Pokecenter2F_Johto_Script_LeftMobileBattleRoom_Entry
	.2byte 0

Pokecenter2F_Johto_LinkReceptionistScript_Trade_Entry::
	lockall
	goto Pokecenter2F_Johto_LinkReceptionistScript_Trade

Pokecenter2F_Johto_LinkReceptionistScript_Battle_Entry::
	lockall
	goto Pokecenter2F_Johto_LinkReceptionistScript_Battle

Pokecenter2F_Johto_LinkReceptionistScript_TimeCapsule_Entry::
	lockall
	goto Pokecenter2F_Johto_LinkReceptionistScript_TimeCapsule

Pokecenter2F_Johto_Pokecenter2FOfficerScript_Entry::
	lockall
	goto Pokecenter2F_Johto_Pokecenter2FOfficerScript

Pokecenter2F_Johto_Pokecenter2FLinkRecordSign_Entry::
	lockall
	goto Pokecenter2F_Johto_Pokecenter2FLinkRecordSign

Pokecenter2F_Johto_Pokecenter2FCheckMysteryGiftScene_Entry::
	lockall
	goto Pokecenter2F_Johto_Pokecenter2FCheckMysteryGiftScene

Pokecenter2F_Johto_Script_LeftCableTradeCenter_Entry::
	lockall
	goto Pokecenter2F_Johto_Script_LeftCableTradeCenter

Pokecenter2F_Johto_Script_LeftCableColosseum_Entry::
	lockall
	goto Pokecenter2F_Johto_Script_LeftCableColosseum

Pokecenter2F_Johto_Script_LeftTimeCapsule_Entry::
	lockall
	goto Pokecenter2F_Johto_Script_LeftTimeCapsule

Pokecenter2F_Johto_Script_LeftMobileTradeRoom_Entry::
	lockall
	goto Pokecenter2F_Johto_Script_LeftMobileTradeRoom

Pokecenter2F_Johto_Script_LeftMobileBattleRoom_Entry::
	lockall
	goto Pokecenter2F_Johto_Script_LeftMobileBattleRoom


Pokecenter2F_Johto_Pokecenter2FCheckMysteryGiftScene:
	@ TODO unsupported: special CheckMysteryGift
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_TradeCenterClosed:
	faceplayer
	message Pokecenter2F_Johto_Text_TradeRoomClosed
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Pokecenter2F_Johto_Script_BattleRoomClosed:
	faceplayer
	message Pokecenter2F_Johto_Text_BattleRoomClosed
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Pokecenter2F_Johto_LinkReceptionistScript_Trade:
	goto_if_unset FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, Pokecenter2F_Johto_Script_TradeCenterClosed
	message Pokecenter2F_Johto_Text_TradeReceptionistIntro
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Pokecenter2F_Johto_LinkReceptionistScript_Trade_Cancel
	@ TODO unsupported: special CheckMobileAdapterStatusSpecial
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_LinkReceptionistScript_Trade_Cancel:
	closemessage
	releaseall
	end

Pokecenter2F_Johto_LinkReceptionistScript_Battle:
	goto_if_unset FLAG_JOHTO_GAVE_MYSTERY_EGG_TO_ELM, Pokecenter2F_Johto_Script_BattleRoomClosed
	message Pokecenter2F_Johto_Text_BattleReceptionistIntro
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Pokecenter2F_Johto_LinkReceptionistScript_Battle_Cancel
	@ TODO unsupported: special CheckMobileAdapterStatusSpecial
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_LinkReceptionistScript_Battle_Cancel:
	closemessage
	releaseall
	end

Pokecenter2F_Johto_Script_TimeCapsuleClosed:
	faceplayer
	message Pokecenter2F_Johto_Text_TimeCapsuleClosed
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Pokecenter2F_Johto_LinkReceptionistScript_TimeCapsule:
	goto_if_set FLAG_JOHTO_MET_BILL, Pokecenter2F_Johto_Script_TimeCapsuleClosed
	goto_if_set FLAG_JOHTO_ENGINE_TIME_CAPSULE, Pokecenter2F_Johto_Script_TimeCapsuleClosed
	@ TODO unsupported: special SetBitsForTimeCapsuleRequest
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_LeftCableTradeCenter:
	@ TODO unsupported: special WaitForOtherPlayerToExit
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_LeftMobileTradeRoom:
	@ TODO unsupported: special Function101220
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_LeftCableColosseum:
	@ TODO unsupported: special WaitForOtherPlayerToExit
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_LeftMobileBattleRoom:
	@ TODO unsupported: special Function101220
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Script_LeftTimeCapsule:
	@ TODO unsupported: special WaitForOtherPlayerToExit
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Pokecenter2FLinkRecordSign:
	@ TODO unsupported: special DisplayLinkRecord
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Pokecenter2FOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_MYSTERY_GIFT_DELIVERY_GUY, Pokecenter2F_Johto_Pokecenter2FOfficerScript_AlreadyGotGift
	message Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_Intro
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Pokecenter2F_Johto_Pokecenter2FOfficerScript_RefusedGift
	message Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_HereYouGo
	waitmessage
	waitbuttonpress
	waitse
	@ TODO unsupported: special GetMysteryGiftItem
	goto Johto_EventScript_Unimplemented

Pokecenter2F_Johto_Pokecenter2FOfficerScript_AlreadyGotGift:
	message Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_Outro
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Pokecenter2F_Johto_Pokecenter2FOfficerScript_RefusedGift:
	message Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_SaidNo
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Pokecenter2F_Johto_Text_BattleReceptionistIntro:
	.string "Welcome to CABLE\n"
	.string "CLUB COLOSSEUM."
	.string "\pYou may battle a\n"
	.string "friend here."
	.string "\pWould you like to\n"
	.string "battle?$"

Pokecenter2F_Johto_Text_TradeReceptionistIntro:
	.string "Welcome to CABLE\n"
	.string "TRADE CENTER."
	.string "\pYou may trade your\n"
	.string "POKéMON here with\l"
	.string "a friend."
	.string "\pWould you like to\n"
	.string "trade?$"

Pokecenter2F_Johto_Text_TimeCapsuleClosed:
	.string "I'm sorry--the\n"
	.string "TIME CAPSULE is\l"
	.string "being adjusted.$"

Pokecenter2F_Johto_Text_TradeRoomClosed:
	.string "I'm sorry--the\n"
	.string "TRADE MACHINE is\l"
	.string "being adjusted.$"

Pokecenter2F_Johto_Text_BattleRoomClosed:
	.string "I'm sorry--the\n"
	.string "BATTLE MACHINE is\l"
	.string "being adjusted.$"

Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_Intro:
	.string "Hello! You're\n"
	.string "{PLAYER}, right?"
	.string "\pI have some-\n"
	.string "thing for you.$"

Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_HereYouGo:
	.string "Here you go!$"

Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_Outro:
	.string "We hope to serve\n"
	.string "you again.$"

Pokecenter2F_Johto_Text_MysteryGiftDeliveryGuy_SaidNo:
	.string "No? That's very\n"
	.string "strange…$"
