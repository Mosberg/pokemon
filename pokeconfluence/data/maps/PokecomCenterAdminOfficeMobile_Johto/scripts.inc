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
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer1_Computer1MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer1_Computer1MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer1_Computer1MenuHeader_Opt3, 3
	dynmultistack 0, 0, FALSE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_PokeComClub
	goto_if_eq VAR_RESULT, 2, PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_MobileCenter
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_Quit

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_PokeComClub:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text_PokeComClub
	waitmessage
	waitbuttonpress
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_loop

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_MobileCenter:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text_MobileCenter
	waitmessage
	waitbuttonpress
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_loop

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1_Quit:
	closemessage
	releaseall
	end

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text
	waitmessage
	waitbuttonpress

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_loop:
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer2_Computer2MenuHeader_Opt1, 1
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer2_Computer2MenuHeader_Opt2, 2
	dynmultipush Johto_Menu_PokecomCenterAdminOfficeMobile_PokecomCenterAdminOfficeMobileComputer2_Computer2MenuHeader_Opt3, 3
	dynmultistack 0, 0, FALSE, 3, FALSE, 1, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_UsePhone
	goto_if_eq VAR_RESULT, 2, PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_DontUsePhone
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_Quit

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_UsePhone:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text_UsePhone
	waitmessage
	waitbuttonpress
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_loop

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_DontUsePhone:
	message PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text_DontUsePhone
	waitmessage
	waitbuttonpress
	goto PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_loop

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2_Quit:
	closemessage
	releaseall
	end

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

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text_PokeComClub:
	.string "There's a POKéCOM\n"
	.string "CLUB upstairs in"
	.string "\pany POKéMON\n"
	.string "CENTER."
	.string "\pThere, you can\n"
	.string "battle or trade"
	.string "\pwith a friend far\n"
	.string "away by using a\l"
	.string "MOBILE ADAPTER."
	.string "\pTo link up, your\n"
	.string "friend must have"
	.string "\pthe same kind of\n"
	.string "MOBILE ADAPTER as\l"
	.string "you.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer1Text_MobileCenter:
	.string "To use the TRADE\n"
	.string "CORNER or read the"
	.string "\pPOKéMON NEWS, you\n"
	.string "need to phone the\l"
	.string "MOBILE CENTER."
	.string "\pYou must register\n"
	.string "at the MOBILE"
	.string "\pCENTER before\n"
	.string "connecting there.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text:
	.string "It's a notice\n"
	.string "about using the\l"
	.string "phone…$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text_UsePhone:
	.string "Please ensure that\n"
	.string "your phone and"
	.string "\pMOBILE ADAPTER are\n"
	.string "properly linked."
	.string "\pPlease make sure\n"
	.string "the wireless phone\l"
	.string "signal is strong."
	.string "\pDon't touch or\n"
	.string "hang up the phone\l"
	.string "while linking.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer2Text_DontUsePhone:
	.string "If the server is\n"
	.string "busy, it may not"
	.string "\pbe possible to log\n"
	.string "on."
	.string "\pIf so, please call\n"
	.string "back later."
	.string "\pIf you are unable\n"
	.string "to log on or don't"
	.string "\punderstand the\n"
	.string "error messages,"
	.string "\pcall a support\n"
	.string "center or read the\l"
	.string "instructions.$"

PokecomCenterAdminOfficeMobile_Johto_PokecomCenterAdminOfficeMobileComputer3Text:
	.string "The ADMINISTRATION\n"
	.string "OFFICE received an\l"
	.string "e-mail. It says…"
	.string "\p… … …"
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
	.string "\p… … …$"
