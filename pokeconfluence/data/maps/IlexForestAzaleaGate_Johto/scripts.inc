IlexForestAzaleaGate_Johto_MapScripts::
	.byte 0

IlexForestAzaleaGate_Johto_IlexForestAzaleaGateOfficerScript_Entry::
	lockall
	goto IlexForestAzaleaGate_Johto_IlexForestAzaleaGateOfficerScript

IlexForestAzaleaGate_Johto_IlexForestAzaleaGateGrannyScript_Entry::
	lockall
	goto IlexForestAzaleaGate_Johto_IlexForestAzaleaGateGrannyScript


IlexForestAzaleaGate_Johto_IlexForestAzaleaGateOfficerScript:
	faceplayer
	message IlexForestAzaleaGate_Johto_IlexForestAzaleaGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForestAzaleaGate_Johto_IlexForestAzaleaGateGrannyScript:
	faceplayer
	message IlexForestAzaleaGate_Johto_IlexForestAzaleaGateGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

IlexForestAzaleaGate_Johto_IlexForestAzaleaGateOfficerText:
	.string "ILEX FOREST is\n"
	.string "big. Be careful!\l"
	.string "Don't get lost.$"

IlexForestAzaleaGate_Johto_IlexForestAzaleaGateGrannyText:
	.string "The FOREST is\n"
	.string "watched over by\l"
	.string "its protector."
	.string "\pStay out of\n"
	.string "mischief!$"
