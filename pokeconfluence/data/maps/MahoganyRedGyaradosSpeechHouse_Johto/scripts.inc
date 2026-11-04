MahoganyRedGyaradosSpeechHouse_Johto_MapScripts::
	.byte 0

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseBlackBeltScript_Entry::
	lockall
	goto MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseBlackBeltScript

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherScript_Entry::
	lockall
	goto MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherScript


MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseBlackBeltScript:
	faceplayer
	message MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_ROCKETS_IN_RADIO_TOWER, MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherScript_RocketsInRadioTower
	message MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherScript_RocketsInRadioTower:
	message MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseBlackBeltText:
	.string "I heard that a red\n"
	.string "GYARADOS appeared\l"
	.string "at the LAKE."
	.string "\pThat's odd, since\n"
	.string "even ordinary"
	.string "\pGYARADOS are rare\n"
	.string "in that lake…$"

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherText:
	.string "My favorite radio\n"
	.string "program? I'd say\l"
	.string "POKéMON MUSIC.$"

MahoganyRedGyaradosSpeechHouse_Johto_MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower:
	.string "I've been hearing\n"
	.string "laughter on the"
	.string "\pradio…\n"
	.string "It's creepy.$"
