PokeSeersHouse_Johto_MapScripts::
	.byte 0

PokeSeersHouse_Johto_SeerScript_Entry::
	lockall
	goto PokeSeersHouse_Johto_SeerScript


PokeSeersHouse_Johto_SeerScript:
	faceplayer
	waitbuttonpress
	closemessage
	releaseall
	end
