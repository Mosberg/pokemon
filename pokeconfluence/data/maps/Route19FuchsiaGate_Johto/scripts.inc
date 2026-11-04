Route19FuchsiaGate_Johto_MapScripts::
	.byte 0

Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerScript_Entry::
	lockall
	goto Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerScript


Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CINNABAR_ROCKS_CLEARED, Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerScript_RocksCleared
	message Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerScript_RocksCleared:
	message Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerText_RocksCleared
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerText:
	.string "CINNABAR's volcano\n"
	.string "erupted."
	.string "\pIt hurled boulders\n"
	.string "that cut off ROUTE\l"
	.string "19 indefinitely."
	.string "\pI wonder if the\n"
	.string "people of CINNABAR\l"
	.string "are safe…$"

Route19FuchsiaGate_Johto_Route19FuchsiaGateOfficerText_RocksCleared:
	.string "No CINNABAR citi-\n"
	.string "zens were injured"
	.string "\pby the eruption.\n"
	.string "That's great!$"
