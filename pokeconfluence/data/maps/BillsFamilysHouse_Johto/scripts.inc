BillsFamilysHouse_Johto_MapScripts::
	.byte 0

BillsFamilysHouse_Johto_BillScript_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillScript

BillsFamilysHouse_Johto_BillsMomScript_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillsMomScript

BillsFamilysHouse_Johto_BillsYoungerSisterScript_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillsYoungerSisterScript

BillsFamilysHouse_Johto_BillsHouseBookshelf2_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillsHouseBookshelf2

BillsFamilysHouse_Johto_BillsHouseBookshelf1_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillsHouseBookshelf1

BillsFamilysHouse_Johto_BillsHouseRadio_Entry::
	lockall
	goto BillsFamilysHouse_Johto_BillsHouseRadio


BillsFamilysHouse_Johto_BillScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_EEVEE, BillsFamilysHouse_Johto_BillScript_GotEevee
	message BillsFamilysHouse_Johto_BillTakeThisEeveeText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, BillsFamilysHouse_Johto_BillScript_Refused
	message BillsFamilysHouse_Johto_BillImCountingOnYouText
	waitmessage
	waitbuttonpress
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 6, BillsFamilysHouse_Johto_BillScript_NoRoom
	message BillsFamilysHouse_Johto_ReceivedEeveeText
	waitmessage
	playse SE_PIN
	waitse
	givemon SPECIES_EEVEE, 20
	setflag FLAG_JOHTO_GOT_EEVEE
	message BillsFamilysHouse_Johto_BillEeveeMayEvolveText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillScript_NoRoom:
	message BillsFamilysHouse_Johto_BillPartyFullText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillScript_Refused:
	message BillsFamilysHouse_Johto_BillNoEeveeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillScript_GotEevee:
	message BillsFamilysHouse_Johto_BillPopWontWorkText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillsMomScript:
	faceplayer
	goto_if_unset FLAG_JOHTO_MET_BILL, BillsFamilysHouse_Johto_BillsMomScript_HaventMetBill
	message BillsFamilysHouse_Johto_BillsMomText_BeforeEcruteak
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillsMomScript_HaventMetBill:
	message BillsFamilysHouse_Johto_BillsMomText_AfterEcruteak
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillsYoungerSisterScript:
	faceplayer
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BILL_REGISTERED
	setvar VAR_0x8005, 0
	special JohtoPhoneIsRegistered
	goto_if_ne VAR_RESULT, 0, BillsFamilysHouse_Johto_BillsYoungerSisterScript_GotBillsNumber
	message BillsFamilysHouse_Johto_BillsYoungerSisterUsefulNumberText
	waitmessage
	setvar VAR_0x8004, FLAG_JOHTO_PHONE_BILL_REGISTERED
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, 0
	call Johto_Std_AskPhone
	goto_if_eq VAR_RESULT, 1, BillsFamilysHouse_Johto_BillsYoungerSisterScript_NoRoom
	goto_if_eq VAR_RESULT, 2, BillsFamilysHouse_Johto_BillsYoungerSisterScript_Refused
	waitse
	setflag FLAG_JOHTO_PHONE_BILL_REGISTERED
	message BillsFamilysHouse_Johto_RecordedBillsNumberText
	waitmessage
	playse SE_PIN
	waitse
	waitbuttonpress

BillsFamilysHouse_Johto_BillsYoungerSisterScript_GotBillsNumber:
	message BillsFamilysHouse_Johto_BillsYoungerSisterStorageSystemText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillsYoungerSisterScript_Refused:
	message BillsFamilysHouse_Johto_BillsYoungerSisterRefusedNumberText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BillsFamilysHouse_Johto_BillsYoungerSisterScript_NoRoom:
	message BillsFamilysHouse_Johto_BillsYoungerSisterPhoneFullText
	waitmessage
	waitbuttonpress
	goto BillsFamilysHouse_Johto_BillsYoungerSisterScript_Refused

BillsFamilysHouse_Johto_BillsHouseBookshelf1:
	goto Johto_Std_PictureBookshelfScript

BillsFamilysHouse_Johto_BillsHouseBookshelf2:
	goto Johto_Std_MagazineBookshelfScript

BillsFamilysHouse_Johto_BillsHouseRadio:
	goto Johto_Std_Radio2Script

BillsFamilysHouse_Johto_BillTakeThisEeveeText:
	.string "BILL: Hi, {PLAYER}!\n"
	.string "Do us a favor and\l"
	.string "take this EEVEE."
	.string "\pIt came over when\n"
	.string "I was adjusting\l"
	.string "the TIME CAPSULE."
	.string "\pSomeone has to\n"
	.string "take care of it,"
	.string "\pbut I don't like\n"
	.string "being outside."
	.string "\pCan I count on you\n"
	.string "to play with it,\l"
	.string "{PLAYER}?$"

BillsFamilysHouse_Johto_BillImCountingOnYouText:
	.string "BILL: I knew you'd\n"
	.string "come through!"
	.string "\pWay to go! You're\n"
	.string "the real deal!"
	.string "\pOK, I'm counting\n"
	.string "on you."
	.string "\pTake good care of\n"
	.string "it!$"

BillsFamilysHouse_Johto_ReceivedEeveeText:
	.string "{PLAYER} received\n"
	.string "EEVEE!$"

BillsFamilysHouse_Johto_BillEeveeMayEvolveText:
	.string "BILL: PROF.ELM\n"
	.string "claims EEVEE may"
	.string "\pevolve in new and\n"
	.string "unknown ways.$"

BillsFamilysHouse_Johto_BillPartyFullText:
	.string "Whoa, wait. You\n"
	.string "can't carry any\l"
	.string "more POKéMON.$"

BillsFamilysHouse_Johto_BillNoEeveeText:
	.string "Oh… Now what to\n"
	.string "do?$"

BillsFamilysHouse_Johto_BillPopWontWorkText:
	.string "BILL: My pop, he\n"
	.string "won't work. All he"
	.string "\pdoes is goof off\n"
	.string "all day long."
	.string "\pHe's getting to be\n"
	.string "a real headache…$"

BillsFamilysHouse_Johto_BillsMomText_BeforeEcruteak:
	.string "Oh, you collect\n"
	.string "POKéMON? My son\l"
	.string "BILL is an expert."
	.string "\pHe just got called\n"
	.string "to the POKéMON"
	.string "\pCENTER in ECRUTEAK\n"
	.string "CITY."
	.string "\pMy husband went\n"
	.string "off to the GAME"
	.string "\pCORNER without\n"
	.string "being called…$"

BillsFamilysHouse_Johto_BillsMomText_AfterEcruteak:
	.string "My husband was\n"
	.string "once known as a"
	.string "\pPOKéMANIAC.\n"
	.string "BILL must have"
	.string "\ptaken after his\n"
	.string "father.$"

BillsFamilysHouse_Johto_BillsYoungerSisterUsefulNumberText:
	.string "Are you a trainer?"
	.string "\pI've got a useful\n"
	.string "phone number for\l"
	.string "you.$"

BillsFamilysHouse_Johto_RecordedBillsNumberText:
	.string "{PLAYER} recorded\n"
	.string "BILL's number.$"

BillsFamilysHouse_Johto_BillsYoungerSisterRefusedNumberText:
	.string "My brother made\n"
	.string "the PC POKéMON\l"
	.string "storage system."
	.string "\pI was going to\n"
	.string "give you BILL's\l"
	.string "number…$"

BillsFamilysHouse_Johto_BillsYoungerSisterPhoneFullText:
	.string "You can't record\n"
	.string "any more numbers.$"

BillsFamilysHouse_Johto_BillsYoungerSisterStorageSystemText:
	.string "My big brother\n"
	.string "BILL made the PC"
	.string "\pPOKéMON storage\n"
	.string "system.$"
