VermilionPortPassage_Johto_MapScripts::
	.byte 0

VermilionPortPassage_Johto_VermilionPortPassageTeacherScript_Entry::
	lockall
	goto VermilionPortPassage_Johto_VermilionPortPassageTeacherScript


VermilionPortPassage_Johto_VermilionPortPassageTeacherScript:
	faceplayer
	message VermilionPortPassage_Johto_VermilionPortPassageTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionPortPassage_Johto_VermilionPortPassageTeacherText:
	.string "The FAST SHIP\n"
	.string "sails on Wednes-\l"
	.string "days and Sundays\l"
	.string "every week.$"
