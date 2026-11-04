Route32RuinsOfAlphGate_Johto_MapScripts::
	.byte 0

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateOfficerScript_Entry::
	lockall
	goto Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateOfficerScript

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGatePokefanMScript_Entry::
	lockall
	goto Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGatePokefanMScript

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateYoungsterScript_Entry::
	lockall
	goto Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateYoungsterScript


Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateOfficerScript:
	faceplayer
	message Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGatePokefanMScript:
	faceplayer
	message Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGatePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateYoungsterScript:
	faceplayer
	message Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateOfficerText:
	.string "RUINS OF ALPH"
	.string "\pA Look-and-Touch\n"
	.string "Tourist Site"
	.string "\pTry the sliding\n"
	.string "stone panels!$"

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGatePokefanMText:
	.string "You're studying\n"
	.string "the RUINS?"
	.string "\pI see a scientist\n"
	.string "in the making.$"

Route32RuinsOfAlphGate_Johto_Route32RuinsOfAlphGateYoungsterText:
	.string "There are drawings\n"
	.string "on stone panels."
	.string "\pI tried moving\n"
	.string "them. I wonder\l"
	.string "what they are.$"
