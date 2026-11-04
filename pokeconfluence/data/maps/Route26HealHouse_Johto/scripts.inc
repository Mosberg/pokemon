Route26HealHouse_Johto_MapScripts::
	.byte 0

Route26HealHouse_Johto_Route26HealHouseTeacherScript_Entry::
	lockall
	goto Route26HealHouse_Johto_Route26HealHouseTeacherScript

Route26HealHouse_Johto_Route26HealHouseBookshelf_Entry::
	lockall
	goto Route26HealHouse_Johto_Route26HealHouseBookshelf


Route26HealHouse_Johto_Route26HealHouseTeacherScript:
	faceplayer
	message Route26HealHouse_Johto_Route26HealHouseRestAWhileText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	playbgm MUS_HEAL, FALSE
	special HealPlayerParty
	delay 60
	fadescreen FADE_FROM_BLACK
	fadedefaultbgm
	message Route26HealHouse_Johto_Route26HealHouseKeepAtItText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route26HealHouse_Johto_Route26HealHouseBookshelf:
	goto Johto_Std_PictureBookshelfScript

Route26HealHouse_Johto_Route26HealHouseRestAWhileText:
	.string "Your POKéMON look\n"
	.string "a little tired."
	.string "\pYou should rest\n"
	.string "them a while.$"

Route26HealHouse_Johto_Route26HealHouseKeepAtItText:
	.string "There!"
	.string "\pYour POKéMON are\n"
	.string "looking good!"
	.string "\pKeep at it!$"
