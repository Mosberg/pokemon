Route10North_Johto_MapScripts::
	.byte 0

Route10North_Johto_PowerPlantSign_Entry::
	lockall
	goto Route10North_Johto_PowerPlantSign

Route10North_Johto_Route10PokecenterSign_Entry::
	lockall
	goto Route10North_Johto_Route10PokecenterSign


Route10North_Johto_PowerPlantSign:
	message Route10North_Johto_PowerPlantSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10North_Johto_Route10PokecenterSign:
	goto Johto_Std_PokecenterSignScript

Route10North_Johto_PowerPlantSignText:
	.string "KANTO POWER PLANT$"
