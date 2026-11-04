GoldenrodPPSpeechHouse_Johto_MapScripts::
	.byte 0

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseFisherScript_Entry::
	lockall
	goto GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseFisherScript

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseLassScript_Entry::
	lockall
	goto GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseLassScript

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf1_Entry::
	lockall
	goto GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf1

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf2_Entry::
	lockall
	goto GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf2

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseRadio_Entry::
	lockall
	goto GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseRadio


GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseFisherScript:
	faceplayer
	message GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseLassScript:
	faceplayer
	message GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf2:
	goto Johto_Std_DifficultBookshelfScript

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseBookshelf1:
	goto Johto_Std_MagazineBookshelfScript

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseRadio:
	goto Johto_Std_Radio2Script

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseFisherText:
	.string "Once while I was\n"
	.string "battling, my"
	.string "\pPOKéMON couldn't\n"
	.string "make any moves."
	.string "\pThe POWER POINTS,\n"
	.string "or PP, of its"
	.string "\pmoves were all\n"
	.string "gone.$"

GoldenrodPPSpeechHouse_Johto_GoldenrodPPSpeechHouseLassText:
	.string "Sometimes, a\n"
	.string "healthy POKéMON"
	.string "\pmay be unable to\n"
	.string "use its moves."
	.string "\pIf that happens,\n"
	.string "heal it at a POKé-\l"
	.string "MON CENTER or use\l"
	.string "an item.$"
