BattleTowerOutside_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BattleTowerOutside_Johto_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BattleTowerOutside_Johto_OnTransition
	.byte 0

BattleTowerOutside_Johto_OnLoad:
	call BattleTowerOutside_Johto_BattleTowerOutsideNoopCallback_Cb
	end

BattleTowerOutside_Johto_OnTransition:
	call BattleTowerOutside_Johto_BattleTowerOutsideShowCiviliansCallback_Cb
	end

BattleTowerOutside_Johto_BattleTowerOutsideYoungsterScript_Entry::
	lockall
	goto BattleTowerOutside_Johto_BattleTowerOutsideYoungsterScript

BattleTowerOutside_Johto_BattleTowerOutsideBeautyScript_Entry::
	lockall
	goto BattleTowerOutside_Johto_BattleTowerOutsideBeautyScript

BattleTowerOutside_Johto_BattleTowerOutsideSailorScript_Entry::
	lockall
	goto BattleTowerOutside_Johto_BattleTowerOutsideSailorScript

BattleTowerOutside_Johto_BattleTowerOutsideSign_Entry::
	lockall
	goto BattleTowerOutside_Johto_BattleTowerOutsideSign


BattleTowerOutside_Johto_BattleTowerOutsideYoungsterScript:
	faceplayer
	message BattleTowerOutside_Johto_BattleTowerOutsideYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTowerOutside_Johto_BattleTowerOutsideBeautyScript:
	faceplayer
	message BattleTowerOutside_Johto_BattleTowerOutsideBeautyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTowerOutside_Johto_BattleTowerOutsideSailorScript:
	faceplayer
	message BattleTowerOutside_Johto_BattleTowerOutsideSailorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTowerOutside_Johto_BattleTowerOutsideSign:
	message BattleTowerOutside_Johto_BattleTowerOutsideSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattleTowerOutside_Johto_BattleTowerOutsideNoopCallback_Cb:
	return

BattleTowerOutside_Johto_BattleTowerOutsideShowCiviliansCallback_Cb:
	clearflag FLAG_JOHTO_BATTLE_TOWER_OPEN_CIVILIANS
	return

BattleTowerOutside_Johto_BattleTowerOutsideYoungsterText:
	.string "Wow, the BATTLE\n"
	.string "TOWER is huge!"
	.string "\pThere must be many\n"
	.string "kinds of POKéMON\l"
	.string "in there!$"

BattleTowerOutside_Johto_BattleTowerOutsideBeautyText:
	.string "You can use only\n"
	.string "three POKéMON."
	.string "\pIt's so hard to\n"
	.string "decide which three"
	.string "\pshould go into\n"
	.string "battle…$"

BattleTowerOutside_Johto_BattleTowerOutsideSailorText:
	.string "Hehehe, I snuck\n"
	.string "out from work."
	.string "\pI can't bail out\n"
	.string "until I've won!"
	.string "\pI have to win it\n"
	.string "all. That I must!$"

BattleTowerOutside_Johto_BattleTowerOutsideSignText:
	.string "BATTLE TOWER"
	.string "\pTake the Ultimate\n"
	.string "Trainer Challenge!$"
