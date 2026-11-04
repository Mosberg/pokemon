Route7SaffronGate_Johto_MapScripts::
	.byte 0

Route7SaffronGate_Johto_Route7SaffronGuardScript_Entry::
	lockall
	goto Route7SaffronGate_Johto_Route7SaffronGuardScript


Route7SaffronGate_Johto_Route7SaffronGuardScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, Route7SaffronGate_Johto_Route7SaffronGuardScript_ReturnedPart
	message Route7SaffronGate_Johto_Route7SaffronGuardPowerPlantText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route7SaffronGate_Johto_Route7SaffronGuardScript_ReturnedPart:
	message Route7SaffronGate_Johto_Route7SaffronGuardSeriousText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route7SaffronGate_Johto_Route7SaffronGuardPowerPlantText:
	.string "Did you hear about\n"
	.string "the accident at\l"
	.string "the POWER PLANT?"
	.string "\pIt's located in\n"
	.string "the East, close to\l"
	.string "LAVENDER TOWN.$"

Route7SaffronGate_Johto_Route7SaffronGuardSeriousText:
	.string "I take my GUARD\n"
	.string "job seriously."
	.string "\pHey! You have a\n"
	.string "POKéDEX."
	.string "\pOK. You can go\n"
	.string "through.$"
