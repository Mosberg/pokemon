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
	setvar VAR_JOHTO_SCENE_BATTLE_TOWER_1F, 1
	releaseall
	end

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
	faceplayer
	message BattleTower1F_Johto_Text_BattleTowerWelcomesYou
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleTower1F_Johto_BattleTower1FReceptionist_Challenge
	case 1, BattleTower1F_Johto_BattleTower1FReceptionist_Explanation
	case 2, BattleTower1F_Johto_BattleTower1FReceptionist_Cancel
	case MULTI_B_PRESSED, BattleTower1F_Johto_BattleTower1FReceptionist_Cancel
	end

BattleTower1F_Johto_BattleTower1FReceptionist_Explanation:
	message BattleTower1F_Johto_Text_BattleTowerExplanation
	waitmessage
	waitbuttonpress
	goto BattleTower1F_Johto_BattleTower1FReceptionistScript

BattleTower1F_Johto_BattleTower1FReceptionist_Cancel:
	message BattleTower1F_Johto_Text_WeHopeToServeYouAgain
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTower1F_Johto_BattleTower1FReceptionist_Challenge:
	special JohtoCheckBattleTowerEligibility
	goto_if_eq VAR_RESULT, FALSE, BattleTower1F_Johto_BattleTower1FReceptionist_NotEligible
	message BattleTower1F_Johto_Text_RightThisWayToYourBattleRoom
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, BattleTower1F_Johto_Movement_ReceptionistWalkToElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleTower1F_Johto_Movement_PlayerWalkToElevator
	waitmovement OBJ_EVENT_ID_PLAYER
	warp MAP_JOHTO_BATTLE_TOWER_ELEVATOR, 1, 2
	waitstate
	end

BattleTower1F_Johto_BattleTower1FReceptionist_NotEligible:
	message BattleTower1F_Johto_Text_NeedThreeMons
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTower1F_Johto_Movement_ReceptionistWalkToElevator:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleTower1F_Johto_Movement_PlayerWalkToElevator:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleTower1F_Johto_Text_BattleTowerWelcomesYou:
	.string "BATTLE TOWER\n"
	.string "welcomes you!\pI could show you to\n"
	.string "a BATTLE ROOM.$"

BattleTower1F_Johto_Text_BattleTowerExplanation:
	.string "BATTLE TOWER is a\n"
	.string "facility made for\l"
	.string "POKéMON battles.\pCountless POKéMON\n"
	.string "TRAINERS gather\l"
	.string "from all over to\l"
	.string "hold battles in\l"
	.string "BATTLE ROOMS.\pIf you beat the\n"
	.string "seven TRAINERS in\l"
	.string "a ROOM, you may win\l"
	.string "a prize!$"

BattleTower1F_Johto_Text_WeHopeToServeYouAgain:
	.string "We hope to serve\n"
	.string "you again.$"

BattleTower1F_Johto_Text_RightThisWayToYourBattleRoom:
	.string "Right this way to\n"
	.string "your BATTLE ROOM.$"

BattleTower1F_Johto_Text_NeedThreeMons:
	.string "Excuse me!\pYou need at least\n"
	.string "three battle-ready\l"
	.string "POKéMON to enter.$"


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
