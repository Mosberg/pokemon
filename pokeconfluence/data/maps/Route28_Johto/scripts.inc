Route28_Johto_MapScripts::
	.byte 0

Route28_Johto_Route28Sign_Entry::
	lockall
	goto Route28_Johto_Route28Sign


Route28_Johto_Route28Sign:
	message Route28_Johto_Route28SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route28_Johto_Route28SignText:
	.string "ROUTE 28$"
