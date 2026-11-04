CeruleanPoliceStation_Johto_MapScripts::
	.byte 0

CeruleanPoliceStation_Johto_CeruleanPoliceStationFishingGuruScript_Entry::
	lockall
	goto CeruleanPoliceStation_Johto_CeruleanPoliceStationFishingGuruScript

CeruleanPoliceStation_Johto_CeruleanPoliceStationPokefanFScript_Entry::
	lockall
	goto CeruleanPoliceStation_Johto_CeruleanPoliceStationPokefanFScript

CeruleanPoliceStation_Johto_CeruleanDiglett_Entry::
	lockall
	goto CeruleanPoliceStation_Johto_CeruleanDiglett


CeruleanPoliceStation_Johto_CeruleanPoliceStationFishingGuruScript:
	faceplayer
	message CeruleanPoliceStation_Johto_CeruleanPoliceStationFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPoliceStation_Johto_CeruleanPoliceStationPokefanFScript:
	faceplayer
	message CeruleanPoliceStation_Johto_CeruleanPoliceStationPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPoliceStation_Johto_CeruleanDiglett:
	message CeruleanPoliceStation_Johto_CeruleanDiglettText
	waitmessage
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeruleanPoliceStation_Johto_CeruleanPoliceStationFishingGuruText:
	.string "I heard that some\n"
	.string "shady character is\l"
	.string "skulking about."
	.string "\pI won't stand for\n"
	.string "it if he turns out\l"
	.string "to be a thief.$"

CeruleanPoliceStation_Johto_CeruleanPoliceStationPokefanFText:
	.string "We were held up by\n"
	.string "robbers before.$"

CeruleanPoliceStation_Johto_CeruleanDiglettText:
	.string "DIGLETT: Dug dug.$"
