Route42EcruteakGate_Johto_MapScripts::
	.byte 0

Route42EcruteakGate_Johto_Route42EcruteakGateOfficerScript_Entry::
	lockall
	goto Route42EcruteakGate_Johto_Route42EcruteakGateOfficerScript


Route42EcruteakGate_Johto_Route42EcruteakGateOfficerScript:
	faceplayer
	message Route42EcruteakGate_Johto_Route42EcruteakGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route42EcruteakGate_Johto_Route42EcruteakGateOfficerText:
	.string "MT.MORTAR is like\n"
	.string "a maze inside."
	.string "\pBe careful. Don't\n"
	.string "get lost in there.$"
