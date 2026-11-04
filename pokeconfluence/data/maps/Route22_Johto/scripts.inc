Route22_Johto_MapScripts::
	.byte 0

Route22_Johto_VictoryRoadEntranceSign_Entry::
	lockall
	goto Route22_Johto_VictoryRoadEntranceSign


Route22_Johto_VictoryRoadEntranceSign:
	message Route22_Johto_VictoryRoadEntranceSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route22_Johto_VictoryRoadEntranceSignText:
	.string "POKéMON LEAGUE"
	.string "\pVICTORY ROAD\n"
	.string "ENTRANCE$"
