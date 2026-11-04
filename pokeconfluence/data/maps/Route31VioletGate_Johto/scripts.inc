Route31VioletGate_Johto_MapScripts::
	.byte 0

Route31VioletGate_Johto_Route31VioletGateOfficerScript_Entry::
	lockall
	goto Route31VioletGate_Johto_Route31VioletGateOfficerScript

Route31VioletGate_Johto_Route31VioletGateCooltrainerFScript_Entry::
	lockall
	goto Route31VioletGate_Johto_Route31VioletGateCooltrainerFScript


Route31VioletGate_Johto_Route31VioletGateOfficerScript:
	faceplayer
	message Route31VioletGate_Johto_Route31VioletGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31VioletGate_Johto_Route31VioletGateCooltrainerFScript:
	faceplayer
	message Route31VioletGate_Johto_Route31VioletGateCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route31VioletGate_Johto_Route31VioletGateOfficerText:
	.string "Hi there!\n"
	.string "Did you visit\l"
	.string "SPROUT TOWER?$"

Route31VioletGate_Johto_Route31VioletGateCooltrainerFText:
	.string "I came too far\n"
	.string "out. I'd better\l"
	.string "phone home!$"
