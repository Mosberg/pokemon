Route43MahoganyGate_Johto_MapScripts::
	.byte 0

Route43MahoganyGate_Johto_Route43MahoganyGateOfficer_Entry::
	lockall
	goto Route43MahoganyGate_Johto_Route43MahoganyGateOfficer


Route43MahoganyGate_Johto_Route43MahoganyGateOfficer:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, Route43MahoganyGate_Johto_Route43MahoganyGateOfficer_RocketsCleared
	message Route43MahoganyGate_Johto_Route43MahoganyGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43MahoganyGate_Johto_Route43MahoganyGateOfficer_RocketsCleared:
	message Route43MahoganyGate_Johto_Route43MahoganyGateOfficerRocketsClearedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route43MahoganyGate_Johto_Route43MahoganyGateOfficerText:
	.string "Only people headed\n"
	.string "up to LAKE OF RAGE"
	.string "\phave been through\n"
	.string "here lately.$"

Route43MahoganyGate_Johto_Route43MahoganyGateOfficerRocketsClearedText:
	.string "Nobody goes up to\n"
	.string "LAKE OF RAGE these\l"
	.string "days.$"
