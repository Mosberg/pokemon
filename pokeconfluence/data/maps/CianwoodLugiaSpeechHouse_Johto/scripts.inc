CianwoodLugiaSpeechHouse_Johto_MapScripts::
	.byte 0

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTeacherScript_Entry::
	lockall
	goto CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTeacherScript

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseLassScript_Entry::
	lockall
	goto CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseLassScript

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTwinScript_Entry::
	lockall
	goto CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTwinScript

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseBookshelf_Entry::
	lockall
	goto CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseBookshelf


CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTeacherScript:
	faceplayer
	message CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseLassScript:
	faceplayer
	message CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTwinScript:
	faceplayer
	message CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTwinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTeacherText:
	.string "You came from\n"
	.string "OLIVINE?"
	.string "\pDo you remember\n"
	.string "the four islands\l"
	.string "along the way?"
	.string "\pI heard that a \n"
	.string "mythical sea crea-\l"
	.string "ture is hiding in\l"
	.string "them.$"

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseLassText:
	.string "I heard that you\n"
	.string "can only see it if"
	.string "\pyou have a SILVER\n"
	.string "WING."
	.string "\pIt must have the\n"
	.string "same scent as the\l"
	.string "creature.$"

CianwoodLugiaSpeechHouse_Johto_CianwoodLugiaSpeechHouseTwinText:
	.string "I've heard that\n"
	.string "the whirlpools"
	.string "\paround the islands\n"
	.string "are caused by the\l"
	.string "sea creature."
	.string "\pYou might need a\n"
	.string "special move to\l"
	.string "get past them.$"
