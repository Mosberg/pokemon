SafariZoneWardensHome_Johto_MapScripts::
	.byte 0

SafariZoneWardensHome_Johto_WardensGranddaughter_Entry::
	lockall
	goto SafariZoneWardensHome_Johto_WardensGranddaughter

SafariZoneWardensHome_Johto_WardensHomeBookshelf_Entry::
	lockall
	goto SafariZoneWardensHome_Johto_WardensHomeBookshelf

SafariZoneWardensHome_Johto_WardenPhoto_Entry::
	lockall
	goto SafariZoneWardensHome_Johto_WardenPhoto

SafariZoneWardensHome_Johto_SafariZonePhoto_Entry::
	lockall
	goto SafariZoneWardensHome_Johto_SafariZonePhoto


SafariZoneWardensHome_Johto_WardensGranddaughter:
	faceplayer
	goto_if_set FLAG_JOHTO_TALKED_TO_WARDENS_GRANDDAUGHTER, SafariZoneWardensHome_Johto_WardensGranddaughter_AlreadyMet
	message SafariZoneWardensHome_Johto_WardensGranddaughterText1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_TALKED_TO_WARDENS_GRANDDAUGHTER
	releaseall
	end

SafariZoneWardensHome_Johto_WardensGranddaughter_AlreadyMet:
	message SafariZoneWardensHome_Johto_WardensGranddaughterText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SafariZoneWardensHome_Johto_WardenPhoto:
	message SafariZoneWardensHome_Johto_WardenPhotoText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SafariZoneWardensHome_Johto_SafariZonePhoto:
	message SafariZoneWardensHome_Johto_SafariZonePhotoText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SafariZoneWardensHome_Johto_WardensHomeBookshelf:
	goto Johto_Std_PictureBookshelfScript

SafariZoneWardensHome_Johto_WardensGranddaughterText1:
	.string "My grandpa is the\n"
	.string "SAFARI ZONE WAR-\l"
	.string "DEN."
	.string "\pAt least he was…"
	.string "\pHe decided to go\n"
	.string "on a vacation and"
	.string "\ptook off overseas\n"
	.string "all by himself."
	.string "\pHe quit running\n"
	.string "SAFARI ZONE just\l"
	.string "like that.$"

SafariZoneWardensHome_Johto_WardensGranddaughterText2:
	.string "Many people were\n"
	.string "disappointed that"
	.string "\pSAFARI ZONE closed\n"
	.string "down, but Grandpa\l"
	.string "is so stubborn…$"

SafariZoneWardensHome_Johto_WardenPhotoText:
	.string "It's a photo of a\n"
	.string "grinning old man"
	.string "\pwho's surrounded\n"
	.string "by POKéMON.$"

SafariZoneWardensHome_Johto_SafariZonePhotoText:
	.string "It's a photo of a\n"
	.string "huge grassy plain"
	.string "\pwith rare POKéMON\n"
	.string "frolicking in it.$"
