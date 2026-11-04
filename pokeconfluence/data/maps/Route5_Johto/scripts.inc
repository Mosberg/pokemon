Route5_Johto_MapScripts::
	.byte 0

Route5_Johto_Route5PokefanMScript_Entry::
	lockall
	goto Route5_Johto_Route5PokefanMScript

Route5_Johto_Route5UndergroundPathSign_Entry::
	lockall
	goto Route5_Johto_Route5UndergroundPathSign

Route5_Johto_HouseForSaleSign_Entry::
	lockall
	goto Route5_Johto_HouseForSaleSign


Route5_Johto_Route5PokefanMScript:
	faceplayer
	message Route5_Johto_Route5PokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5_Johto_Route5UndergroundPathSign:
	message Route5_Johto_Route5UndergroundPathSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5_Johto_HouseForSaleSign:
	message Route5_Johto_HouseForSaleSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5_Johto_Route5PokefanMText:
	.string "The road is closed\n"
	.string "until the problem"
	.string "\pat the POWER PLANT\n"
	.string "is solved.$"

Route5_Johto_Route5UndergroundPathSignText:
	.string "UNDERGROUND PATH"
	.string "\pCERULEAN CITY -\n"
	.string "VERMILION CITY$"

Route5_Johto_HouseForSaleSignText:
	.string "What's this?"
	.string "\pHouse for Sale…\n"
	.string "Nobody lives here.$"
