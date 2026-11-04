OlivinePunishmentSpeechHouse_Johto_MapScripts::
	.byte 0

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDad_Entry::
	lockall
	goto OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDad

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDaughter_Entry::
	lockall
	goto OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDaughter

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf1_Entry::
	lockall
	goto OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf1

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf2_Entry::
	lockall
	goto OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf2


OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDad:
	faceplayer
	message OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDadText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDaughter:
	faceplayer
	message OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDaughterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf2:
	goto Johto_Std_PictureBookshelfScript

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseBookshelf1:
	goto Johto_Std_MagazineBookshelfScript

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDadText:
	.string "Along the way to\n"
	.string "CIANWOOD, there"
	.string "\pare four deserted\n"
	.string "islands."
	.string "\pBad kids are taken\n"
	.string "to the islands as\l"
	.string "punishment!$"

OlivinePunishmentSpeechHouse_Johto_OlivinePunishmentSpeechHouseDaughterText:
	.string "Whenever I get in\n"
	.string "trouble, Daddy\l"
	.string "always scares me.$"
