Route15FuchsiaGate_Johto_MapScripts::
	.byte 0

Route15FuchsiaGate_Johto_Route15FuchsiaGateOfficerScript_Entry::
	lockall
	goto Route15FuchsiaGate_Johto_Route15FuchsiaGateOfficerScript


Route15FuchsiaGate_Johto_Route15FuchsiaGateOfficerScript:
	faceplayer
	message Route15FuchsiaGate_Johto_Route15FuchsiaGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route15FuchsiaGate_Johto_Route15FuchsiaGateOfficerText:
	.string "You're working on\n"
	.string "a POKéDEX? That's"
	.string "\preally something.\n"
	.string "Don't give up!$"
