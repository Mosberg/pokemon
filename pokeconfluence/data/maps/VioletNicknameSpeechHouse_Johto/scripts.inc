VioletNicknameSpeechHouse_Johto_MapScripts::
	.byte 0

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseTeacherScript_Entry::
	lockall
	goto VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseTeacherScript

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseLassScript_Entry::
	lockall
	goto VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseLassScript

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseBirdScript_Entry::
	lockall
	goto VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseBirdScript


VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseTeacherScript:
	faceplayer
	message VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseLassScript:
	faceplayer
	message VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseBirdScript:
	faceplayer
	message VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseBirdText
	waitmessage
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseTeacherText:
	.string "She uses the names\n"
	.string "of her favorite\l"
	.string "things to eat."
	.string "\pFor the nicknames\n"
	.string "she gives to her\l"
	.string "POKéMON, I mean.$"

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseLassText:
	.string "I call my PIDGEY\n"
	.string "STRAWBERRY!$"

VioletNicknameSpeechHouse_Johto_VioletNicknameSpeechHouseBirdText:
	.string "STRAWBERRY: Pijji!$"
