Route40BattleTowerGate_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route40BattleTowerGate_Johto_OnTransition
	.byte 0

Route40BattleTowerGate_Johto_OnTransition:
	call Route40BattleTowerGate_Johto_RouteBattleTowerGateShowSailorCallback_Cb
	end

Route40BattleTowerGate_Johto_Route40BattleTowerGateRockerScript_Entry::
	lockall
	goto Route40BattleTowerGate_Johto_Route40BattleTowerGateRockerScript

Route40BattleTowerGate_Johto_Route40BattleTowerGateTwinScript_Entry::
	lockall
	goto Route40BattleTowerGate_Johto_Route40BattleTowerGateTwinScript


Route40BattleTowerGate_Johto_Route40BattleTowerGateRockerScript:
	faceplayer
	message Route40BattleTowerGate_Johto_Route40BattleTowerGateRockerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40BattleTowerGate_Johto_Route40BattleTowerGateTwinScript:
	faceplayer
	message Route40BattleTowerGate_Johto_Route40BattleTowerGateTwinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route40BattleTowerGate_Johto_RouteBattleTowerGateShowSailorCallback_Cb:
	clearflag FLAG_JOHTO_BATTLE_TOWER_OPEN_CIVILIANS
	return

Route40BattleTowerGate_Johto_Route40BattleTowerGateRockerText:
	.string "Are you going to\n"
	.string "the BATTLE TOWER?"
	.string "\pThis is a secret,\n"
	.string "but if you win a"
	.string "\pwhole lot, you can\n"
	.string "win special gifts.$"

Route40BattleTowerGate_Johto_Route40BattleTowerGateTwinText:
	.string "The levels of the\n"
	.string "POKéMON I want to"
	.string "\puse are all\n"
	.string "different."
	.string "\pI have to go train\n"
	.string "them now!$"
