SilverCaveRoom3_Johto_MapScripts::
	.byte 0

SilverCaveRoom3_Johto_Red_Entry::
	lockall
	goto SilverCaveRoom3_Johto_Red


SilverCaveRoom3_Johto_Red:
	fadeoutbgm 4
	faceplayer
	message SilverCaveRoom3_Johto_RedSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_RED_RED1, SilverCaveRoom3_Johto_RedWinLossText
	fadeoutbgm 4
	message SilverCaveRoom3_Johto_RedLeavesText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	delay 15
	fadescreen FADE_FROM_BLACK
	delay 30
	special HealPlayerParty
	@ TODO unsupported: credits 
	goto Johto_EventScript_Unimplemented

SilverCaveRoom3_Johto_RedSeenText:
	.string "<……>\n"
	.string "<……>$"

SilverCaveRoom3_Johto_RedWinLossText:
	.string "…$"

SilverCaveRoom3_Johto_RedLeavesText:
	.string "<……>\n"
	.string "<……>$"
