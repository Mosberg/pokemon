GuideGentsHouse_Johto_MapScripts::
	.byte 0

GuideGentsHouse_Johto_GuideGentsHouseGuideGent_Entry::
	lockall
	goto GuideGentsHouse_Johto_GuideGentsHouseGuideGent

GuideGentsHouse_Johto_GuideGentsHouseBookshelf_Entry::
	lockall
	goto GuideGentsHouse_Johto_GuideGentsHouseBookshelf


GuideGentsHouse_Johto_GuideGentsHouseGuideGent:
	faceplayer
	message GuideGentsHouse_Johto_GuideGentsHouseGuideGentText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GuideGentsHouse_Johto_GuideGentsHouseBookshelf:
	goto Johto_Std_MagazineBookshelfScript

GuideGentsHouse_Johto_GuideGentsHouseGuideGentText:
	.string "When I was a wee\n"
	.string "lad, I was a hot-\l"
	.string "shot trainer!"
	.string "\pHere's a word of\n"
	.string "advice: Catch lots\l"
	.string "of POKéMON!"
	.string "\pTreat them all\n"
	.string "with kindness!$"
