Route5CleanseTagHouse_Johto_MapScripts::
	.byte 0

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript_Entry::
	lockall
	goto Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseTeacherScript_Entry::
	lockall
	goto Route5CleanseTagHouse_Johto_Route5CleanseTagHouseTeacherScript

Route5CleanseTagHouse_Johto_HouseForSaleBookshelf_Entry::
	lockall
	goto Route5CleanseTagHouse_Johto_HouseForSaleBookshelf


Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_CLEANSE_TAG, Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript_GotCleanseTag
	message Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, 0, Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript_NoRoom
	setflag FLAG_JOHTO_GOT_CLEANSE_TAG

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript_GotCleanseTag:
	message Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyText2
	waitmessage
	waitbuttonpress

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyScript_NoRoom:
	closemessage
	releaseall
	end

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseTeacherScript:
	faceplayer
	message Route5CleanseTagHouse_Johto_Route5CleanseTagHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5CleanseTagHouse_Johto_HouseForSaleBookshelf:
	goto Johto_Std_DifficultBookshelfScript

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyText1:
	.string "Eeyaaaah!"
	.string "\pI sense a sinister\n"
	.string "shadow hovering\l"
	.string "over you."
	.string "\pTake this to ward\n"
	.string "it off!$"

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseGrannyText2:
	.string "You were in mortal\n"
	.string "danger, but you\l"
	.string "are protected now.$"

Route5CleanseTagHouse_Johto_Route5CleanseTagHouseTeacherText:
	.string "My grandma is into\n"
	.string "warding off what"
	.string "\pshe believes to be\n"
	.string "evil spirits."
	.string "\pI'm sorry that she\n"
	.string "startled you.$"
