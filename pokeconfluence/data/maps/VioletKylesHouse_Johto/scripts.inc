VioletKylesHouse_Johto_MapScripts::
	.byte 0

VioletKylesHouse_Johto_VioletKylesHousePokefanMScript_Entry::
	lockall
	goto VioletKylesHouse_Johto_VioletKylesHousePokefanMScript

VioletKylesHouse_Johto_Kyle_Entry::
	lockall
	goto VioletKylesHouse_Johto_Kyle


VioletKylesHouse_Johto_VioletKylesHousePokefanMScript:
	faceplayer
	message VioletKylesHouse_Johto_VioletKylesHousePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VioletKylesHouse_Johto_Kyle:
	faceplayer
	goto Johto_Std_Trade_KYLE

VioletKylesHouse_Johto_VioletKylesHousePokefanMText:
	.string "A POKéMON you get\n"
	.string "in a trade grows\l"
	.string "quickly."
	.string "\pBut if you don't\n"
	.string "have the right GYM"
	.string "\pBADGE, they may\n"
	.string "disobey you.$"
