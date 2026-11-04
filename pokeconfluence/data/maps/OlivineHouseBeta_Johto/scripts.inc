OlivineHouseBeta_Johto_MapScripts::
	.byte 0

OlivineHouseBeta_Johto_OlivineHouseBetaTeacherScript_Entry::
	lockall
	goto OlivineHouseBeta_Johto_OlivineHouseBetaTeacherScript

OlivineHouseBeta_Johto_OlivineHouseBetaRhydonScript_Entry::
	lockall
	goto OlivineHouseBeta_Johto_OlivineHouseBetaRhydonScript

OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf1_Entry::
	lockall
	goto OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf1

OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf2_Entry::
	lockall
	goto OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf2


OlivineHouseBeta_Johto_OlivineHouseBetaTeacherScript:
	faceplayer
	message OlivineHouseBeta_Johto_OlivineHouseBetaTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineHouseBeta_Johto_OlivineHouseBetaRhydonScript:
	message OlivineHouseBeta_Johto_OlivineHouseBetaRhydonText
	waitmessage
	playmoncry SPECIES_RHYDON, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf1:
	goto Johto_Std_PictureBookshelfScript

OlivineHouseBeta_Johto_OlivineHouseBetaBookshelf2:
	goto Johto_Std_MagazineBookshelfScript

OlivineHouseBeta_Johto_OlivineHouseBetaTeacherText:
	.string "When my POKéMON\n"
	.string "got sick, the"
	.string "\pPHARMACIST in\n"
	.string "ECRUTEAK made some\l"
	.string "medicine for me.$"

OlivineHouseBeta_Johto_OlivineHouseBetaRhydonText:
	.string "RHYDON: Gugooh!$"
