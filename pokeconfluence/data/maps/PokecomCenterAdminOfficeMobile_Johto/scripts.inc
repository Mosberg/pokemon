PokecomCenterAdminOfficeMobile_Johto_MapScripts::
	.byte 0

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist1Script_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist1Script

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist2Script_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist2Script

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist3Script_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist3Script

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3_Entry::
	lockall
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3


PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist1Script:
	faceplayer
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist2Script:
	faceplayer
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist3Script:
	faceplayer
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text
	waitmessage
	waitbuttonpress

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_loop:
	@ TODO unsupported: loadmenu .Computer1MenuHeader
	goto Johto_EventScript_Unimplemented

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text
	waitmessage
	waitbuttonpress

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_loop:
	@ TODO unsupported: loadmenu .Computer2MenuHeader
	goto Johto_EventScript_Unimplemented

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist1Text:
	.string "POKéCOM CENTER and\n"
	.string "MOBILE CENTER were"
	.string "\pbuilt to satisfy\n"
	.string "demands for trades"
	.string "\pand battles with\n"
	.string "trainers far away"
	.string "\pand with total\n"
	.string "strangers.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist2Text:
	.string "When you linked\n"
	.string "with someone by"
	.string "\pmobile phone for\n"
	.string "the first time,"
	.string "\pweren't you\n"
	.string "impressed?"
	.string "\pWhen my first try\n"
	.string "worked, I was so"
	.string "\pimpressed that I\n"
	.string "got the shakes!$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileScientist3Text:
	.string "They were able to\n"
	.string "build this huge"
	.string "\pfacility thanks to\n"
	.string "advances in wire-\l"
	.string "less technology.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text:
	.string "It's a notice\n"
	.string "about where MOBILE"
	.string "\pADAPTERS are to be\n"
	.string "used…$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text:
	.string "It's a notice\n"
	.string "about using the\l"
	.string "phone…$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3Text:
	.string "The ADMINISTRATION\n"
	.string "OFFICE received an\l"
	.string "e-mail. It says…"
	.string "\p<……> <……> <……>"
	.string "\pTo the POKéCOM\n"
	.string "CENTER staff…"
	.string "\pWireless communi-\n"
	.string "cation has enabled"
	.string "\pPOKéMON trainers\n"
	.string "to interact across"
	.string "\pthe nation. Let's\n"
	.string "keep working for"
	.string "\pthe day when all\n"
	.string "the trainers in"
	.string "\pthe world can link\n"
	.string "without barriers!"
	.string "\p<……> <……> <……>$"
