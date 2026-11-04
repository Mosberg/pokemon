Route38EcruteakGate_Johto_MapScripts::
	.byte 0

Route38EcruteakGate_Johto_Route38EcruteakGateOfficerScript_Entry::
	lockall
	goto Route38EcruteakGate_Johto_Route38EcruteakGateOfficerScript


Route38EcruteakGate_Johto_Route38EcruteakGateOfficerScript:
	faceplayer
	message Route38EcruteakGate_Johto_Route38EcruteakGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route38EcruteakGate_Johto_Route38EcruteakGateOfficerText:
	.string "Where did you say\n"
	.string "you're from?"
	.string "\pNEW BARK TOWN?"
	.string "\pPROF.ELM lives\n"
	.string "over there, right?"
	.string "\pYou've come a long\n"
	.string "way to get here.$"
