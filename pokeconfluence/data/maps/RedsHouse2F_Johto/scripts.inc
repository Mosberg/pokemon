RedsHouse2F_Johto_MapScripts::
	.byte 0

RedsHouse2F_Johto_RedsHouse2FN64Script_Entry::
	lockall
	goto RedsHouse2F_Johto_RedsHouse2FN64Script

RedsHouse2F_Johto_RedsHouse2FPCScript_Entry::
	lockall
	goto RedsHouse2F_Johto_RedsHouse2FPCScript


RedsHouse2F_Johto_RedsHouse2FN64Script:
	message RedsHouse2F_Johto_RedsHouse2FN64Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RedsHouse2F_Johto_RedsHouse2FPCScript:
	message RedsHouse2F_Johto_RedsHouse2FPCText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RedsHouse2F_Johto_RedsHouse2FN64Text:
	.string "{PLAYER} played the\n"
	.string "N64."
	.string "\pBetter get going--\n"
	.string "no time to lose!$"

RedsHouse2F_Johto_RedsHouse2FPCText:
	.string "It looks like it\n"
	.string "hasn't been used\l"
	.string "in a long time…$"
