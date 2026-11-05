VictoryRoadGate_Johto_MapScripts::
	.byte 0

VictoryRoadGate_Johto_VictoryRoadGateOfficerScript_Entry::
	lockall
	goto VictoryRoadGate_Johto_VictoryRoadGateOfficerScript

VictoryRoadGate_Johto_VictoryRoadGateLeftBlackBeltScript_Entry::
	lockall
	goto VictoryRoadGate_Johto_VictoryRoadGateLeftBlackBeltScript

VictoryRoadGate_Johto_VictoryRoadGateRightBlackBeltScript_Entry::
	lockall
	goto VictoryRoadGate_Johto_VictoryRoadGateRightBlackBeltScript

VictoryRoadGate_Johto_VictoryRoadGateBadgeCheckScript_Entry::
	lockall
	goto VictoryRoadGate_Johto_VictoryRoadGateBadgeCheckScript


VictoryRoadGate_Johto_VictoryRoadGateBadgeCheckScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VictoryRoadGate_Johto__VictoryRoadGateBadgeCheckScript

VictoryRoadGate_Johto_VictoryRoadGateOfficerScript:
	faceplayer

VictoryRoadGate_Johto__VictoryRoadGateBadgeCheckScript:
	message VictoryRoadGate_Johto_VictoryRoadGateOfficerText
	waitmessage
	waitbuttonpress
	special JohtoCountBadges
	goto_if_gt VAR_RESULT, 7, VictoryRoadGate_Johto__VictoryRoadGateBadgeCheckScript_AllEightBadges
	message VictoryRoadGate_Johto_VictoryRoadGateNotEnoughBadgesText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, VictoryRoadGate_Johto_VictoryRoadGateStepDownMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	releaseall
	end

VictoryRoadGate_Johto__VictoryRoadGateBadgeCheckScript_AllEightBadges:
	message VictoryRoadGate_Johto_VictoryRoadGateEightBadgesText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_VICTORY_ROAD_GATE, 1
	releaseall
	end

VictoryRoadGate_Johto_VictoryRoadGateLeftBlackBeltScript:
	faceplayer
	message VictoryRoadGate_Johto_VictoryRoadGateLeftBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VictoryRoadGate_Johto_VictoryRoadGateRightBlackBeltScript:
	faceplayer
	message VictoryRoadGate_Johto_VictoryRoadGateRightBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VictoryRoadGate_Johto_VictoryRoadGateStepDownMovement:
	walk_down
	step_end

VictoryRoadGate_Johto_VictoryRoadGateOfficerText:
	.string "Only trainers who\n"
	.string "have proven them-\l"
	.string "selves may pass.$"

VictoryRoadGate_Johto_VictoryRoadGateNotEnoughBadgesText:
	.string "You don't have all\n"
	.string "the GYM BADGES of\l"
	.string "JOHTO."
	.string "\pI'm sorry, but I\n"
	.string "can't let you go\l"
	.string "through.$"

VictoryRoadGate_Johto_VictoryRoadGateEightBadgesText:
	.string "Oh! The eight\n"
	.string "BADGES of JOHTO!"
	.string "\pPlease, go right\n"
	.string "on through!$"

VictoryRoadGate_Johto_VictoryRoadGateLeftBlackBeltText:
	.string "This way leads to\n"
	.string "MT.SILVER."
	.string "\pYou'll see scary-\n"
	.string "strong POKéMON out\l"
	.string "there.$"

VictoryRoadGate_Johto_VictoryRoadGateRightBlackBeltText:
	.string "Off to the POKéMON\n"
	.string "LEAGUE, are you?"
	.string "\pThe ELITE FOUR are\n"
	.string "so strong it's"
	.string "\pscary, and they're\n"
	.string "ready for you!$"
