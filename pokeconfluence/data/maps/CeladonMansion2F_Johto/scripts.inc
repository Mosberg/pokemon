CeladonMansion2F_Johto_MapScripts::
	.byte 0

CeladonMansion2F_Johto_CeladonMansion2FComputer_Entry::
	lockall
	goto CeladonMansion2F_Johto_CeladonMansion2FComputer

CeladonMansion2F_Johto_CeladonMansion2FMeetingRoomSign_Entry::
	lockall
	goto CeladonMansion2F_Johto_CeladonMansion2FMeetingRoomSign

CeladonMansion2F_Johto_CeladonMansion2FBookshelf_Entry::
	lockall
	goto CeladonMansion2F_Johto_CeladonMansion2FBookshelf


CeladonMansion2F_Johto_CeladonMansion2FComputer:
	message CeladonMansion2F_Johto_CeladonMansion2FComputerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion2F_Johto_CeladonMansion2FMeetingRoomSign:
	message CeladonMansion2F_Johto_CeladonMansion2FMeetingRoomSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion2F_Johto_CeladonMansion2FBookshelf:
	goto Johto_Std_DifficultBookshelfScript

CeladonMansion2F_Johto_CeladonMansion2FComputerText:
	.string "{PLAYER} turned on\n"
	.string "the PC."
	.string "\p…"
	.string "\pSomeone was in the\n"
	.string "middle of compos-\l"
	.string "ing an e-mail."
	.string "\p…I hope you'll\n"
	.string "come visit KANTO."
	.string "\pI think you'll be\n"
	.string "surprised at how"
	.string "\pmuch things have\n"
	.string "changed here."
	.string "\pYou'll also see\n"
	.string "many POKéMON that"
	.string "\paren't native to\n"
	.string "JOHTO."
	.string "\pTo the PRODUCER"
	.string "\p…$"

CeladonMansion2F_Johto_CeladonMansion2FMeetingRoomSignText:
	.string "GAME FREAK\n"
	.string "MEETING ROOM$"
