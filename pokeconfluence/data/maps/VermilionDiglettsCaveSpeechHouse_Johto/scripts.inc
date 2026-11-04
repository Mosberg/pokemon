VermilionDiglettsCaveSpeechHouse_Johto_MapScripts::
	.byte 0

VermilionDiglettsCaveSpeechHouse_Johto_VermilionDiglettsCaveSpeechHouseGentlemanScript_Entry::
	lockall
	goto VermilionDiglettsCaveSpeechHouse_Johto_VermilionDiglettsCaveSpeechHouseGentlemanScript


VermilionDiglettsCaveSpeechHouse_Johto_VermilionDiglettsCaveSpeechHouseGentlemanScript:
	faceplayer
	message VermilionDiglettsCaveSpeechHouse_Johto_VermilionDiglettsCaveSpeechHouseGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionDiglettsCaveSpeechHouse_Johto_VermilionDiglettsCaveSpeechHouseGentlemanText:
	.string "Over many years,\n"
	.string "DIGLETT dug a\l"
	.string "large tunnel."
	.string "\pThat tunnel goes\n"
	.string "to a distant town.$"
