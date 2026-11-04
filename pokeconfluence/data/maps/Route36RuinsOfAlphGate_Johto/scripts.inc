Route36RuinsOfAlphGate_Johto_MapScripts::
	.byte 0

Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateOfficerScript_Entry::
	lockall
	goto Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateOfficerScript

Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateGrampsScript_Entry::
	lockall
	goto Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateGrampsScript


Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateOfficerScript:
	faceplayer
	message Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateGrampsScript:
	faceplayer
	message Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateOfficerText:
	.string "Don't you wonder\n"
	.string "who'd make some-\l"
	.string "thing like this?\l"
	.string "And why?$"

Route36RuinsOfAlphGate_Johto_Route36RuinsOfAlphGateGrampsText:
	.string "Did you see that\n"
	.string "strange tree in\l"
	.string "the road?"
	.string "\pThat may explain\n"
	.string "why fewer people"
	.string "\pare visiting the\n"
	.string "RUINS OF ALPH.$"
