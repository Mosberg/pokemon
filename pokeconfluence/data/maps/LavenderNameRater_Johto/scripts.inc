LavenderNameRater_Johto_MapScripts::
	.byte 0

LavenderNameRater_Johto_LavenderNameRater_Entry::
	lockall
	goto LavenderNameRater_Johto_LavenderNameRater


LavenderNameRater_Johto_LavenderNameRater:
	faceplayer
	goto SlateportCity_NameRatersHouse_EventScript_NameRater
	waitbuttonpress
	closemessage
	releaseall
	end
