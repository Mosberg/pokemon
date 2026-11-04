BillsOlderSistersHouse_Johto_MapScripts::
	.byte 0

BillsOlderSistersHouse_Johto_BillsOlderSisterScript_Entry::
	lockall
	goto BillsOlderSistersHouse_Johto_BillsOlderSisterScript

BillsOlderSistersHouse_Johto_BillsOlderSistersHouseYoungsterScript_Entry::
	lockall
	goto BillsOlderSistersHouse_Johto_BillsOlderSistersHouseYoungsterScript


BillsOlderSistersHouse_Johto_BillsOlderSisterScript:
	faceplayer
	message BillsOlderSistersHouse_Johto_BillsOlderSisterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsOlderSistersHouse_Johto_BillsOlderSistersHouseYoungsterScript:
	faceplayer
	message BillsOlderSistersHouse_Johto_BillsOlderSistersHouseYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsOlderSistersHouse_Johto_BillsOlderSisterText:
	.string "My grandpa is at \n"
	.string "my brother BILL's\l"
	.string "on CERULEAN CAPE.$"

BillsOlderSistersHouse_Johto_BillsOlderSistersHouseYoungsterText:
	.string "I saw these weird,\n"
	.string "slow POKéMON on\l"
	.string "CYCLING ROAD.$"
