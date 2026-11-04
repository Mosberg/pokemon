BattleTower1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleTower1F_Johto_OnFrame
	.byte 0

BattleTower1F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_BATTLE_TOWER_1F, 0, BattleTower1F_Johto_BattleTower1FCheckStateScene_Entry
	.2byte 0

BattleTower1F_Johto_BattleTower1FReceptionistScript_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FReceptionistScript

BattleTower1F_Johto_BattleTower1FYoungsterScript_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FYoungsterScript

BattleTower1F_Johto_BattleTower1FCooltrainerFScript_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FCooltrainerFScript

BattleTower1F_Johto_BattleTower1FBugCatcherScript_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FBugCatcherScript

BattleTower1F_Johto_BattleTower1FGrannyScript_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FGrannyScript

BattleTower1F_Johto_BattleTower1FRulesSign_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FRulesSign

BattleTower1F_Johto_BattleTower1FCheckStateScene_Entry::
	lockall
	goto BattleTower1F_Johto_BattleTower1FCheckStateScene


BattleTower1F_Johto_BattleTower1FCheckStateScene:
	setvar VAR_RESULT, 0
	@ TODO unsupported: special BattleTowerAction
	goto Johto_EventScript_Unimplemented

BattleTower1F_Johto_BattleTower1FRulesSign:
	message BattleTower1F_Johto_Text_ReadBattleTowerRules
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BattleTower1F_Johto_BattleTower1FRulesSign_skip
	message BattleTower1F_Johto_Text_BattleTowerRules
	waitmessage
	waitbuttonpress

BattleTower1F_Johto_BattleTower1FRulesSign_skip:
	closemessage
	releaseall
	end

BattleTower1F_Johto_BattleTower1FReceptionistScript:
	setvar VAR_RESULT, 0
	@ TODO unsupported: special BattleTowerAction
	goto Johto_EventScript_Unimplemented

BattleTower1F_Johto_BattleTower1FYoungsterScript:
	faceplayer
	message BattleTower1F_Johto_Text_BattleTowerYoungster
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Right
	waitmovement 2
	releaseall
	end

BattleTower1F_Johto_BattleTower1FCooltrainerFScript:
	faceplayer
	message BattleTower1F_Johto_Text_BattleTowerCooltrainerF
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTower1F_Johto_BattleTower1FBugCatcherScript:
	faceplayer
	message BattleTower1F_Johto_Text_BattleTowerBugCatcher
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTower1F_Johto_BattleTower1FGrannyScript:
	faceplayer
	message BattleTower1F_Johto_Text_BattleTowerGranny
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTower1F_Johto_Text_ReadBattleTowerRules:
	.string "BATTLE TOWER rules\n"
	.string "are written here."
	.string "\pRead the rules?$"

BattleTower1F_Johto_Text_BattleTowerRules:
	.string "Three POKéMON may\n"
	.string "enter battles."
	.string "\pAll three must be\n"
	.string "different."
	.string "\pThe items they\n"
	.string "hold must also be\l"
	.string "different."
	.string "\pCertain POKéMON\n"
	.string "may also have"
	.string "\plevel restrictions\n"
	.string "placed on them.$"

BattleTower1F_Johto_Text_BattleTowerYoungster:
	.string "Destroyed by the\n"
	.string "first opponent in"
	.string "\pno time at all…\n"
	.string "I'm no good…$"

BattleTower1F_Johto_Text_BattleTowerCooltrainerF:
	.string "There are lots of\n"
	.string "BATTLE ROOMS, but"
	.string "\pI'm going to win\n"
	.string "them all!$"

BattleTower1F_Johto_Text_BattleTowerGranny:
	.string "It's a grueling\n"
	.string "task, not being"
	.string "\pable to use items\n"
	.string "in battle."
	.string "\pMaking your\n"
	.string "POKéMON hold items"
	.string "\pis the key to\n"
	.string "winning battles.$"

BattleTower1F_Johto_Text_BattleTowerBugCatcher:
	.string "I'm trying to see\n"
	.string "how far I can go"
	.string "\pusing just bug\n"
	.string "POKéMON."
	.string "\pDon't let there be\n"
	.string "any fire POKéMON…$"
