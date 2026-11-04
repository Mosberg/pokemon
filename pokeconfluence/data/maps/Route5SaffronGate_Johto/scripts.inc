Route5SaffronGate_Johto_MapScripts::
	.byte 0

Route5SaffronGate_Johto_Route5SaffronGateOfficerScript_Entry::
	lockall
	goto Route5SaffronGate_Johto_Route5SaffronGateOfficerScript


Route5SaffronGate_Johto_Route5SaffronGateOfficerScript:
	faceplayer
	message Route5SaffronGate_Johto_Route5SaffronGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5SaffronGate_Johto_Route5SaffronGateOfficerText:
	.string "You're from JOHTO,\n"
	.string "aren't you?"
	.string "\pHow do you like\n"
	.string "KANTO? It's nice,\l"
	.string "don't you agree?$"
