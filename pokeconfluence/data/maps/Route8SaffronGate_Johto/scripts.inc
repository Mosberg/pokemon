Route8SaffronGate_Johto_MapScripts::
	.byte 0

Route8SaffronGate_Johto_Route8SaffronGateOfficerScript_Entry::
	lockall
	goto Route8SaffronGate_Johto_Route8SaffronGateOfficerScript


Route8SaffronGate_Johto_Route8SaffronGateOfficerScript:
	faceplayer
	message Route8SaffronGate_Johto_Route8SaffronGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route8SaffronGate_Johto_Route8SaffronGateOfficerText:
	.string "Have you been to\n"
	.string "LAVENDER TOWN?"
	.string "\pThere's a tall\n"
	.string "RADIO TOWER there.$"
