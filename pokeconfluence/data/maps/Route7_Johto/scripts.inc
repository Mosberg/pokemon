Route7_Johto_MapScripts::
	.byte 0

Route7_Johto_Route7UndergroundPathSign_Entry::
	lockall
	goto Route7_Johto_Route7UndergroundPathSign

Route7_Johto_Route7LockedDoor_Entry::
	lockall
	goto Route7_Johto_Route7LockedDoor


Route7_Johto_Route7UndergroundPathSign:
	message Route7_Johto_Route7UndergroundPathSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route7_Johto_Route7LockedDoor:
	message Route7_Johto_Route7LockedDoorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route7_Johto_Route7UndergroundPathSignText:
	.string "What's this flyer?"
	.string "\p… Uncouth trainers\n"
	.string "have been holding"
	.string "\pbattles in the\n"
	.string "UNDERGROUND PATH."
	.string "\pBecause of rising\n"
	.string "complaints by lo-\l"
	.string "cal residents, the\l"
	.string "UNDERGROUND PATH\l"
	.string "has been sealed\l"
	.string "indefinitely."
	.string "\pCELADON POLICE$"

Route7_Johto_Route7LockedDoorText:
	.string "It's locked…$"
