PalletTown_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_Johto_OnTransition
	.byte 0

PalletTown_Johto_OnTransition:
	call PalletTown_Johto_PalletTownFlypointCallback_Cb
	end

PalletTown_Johto_PalletTownTeacherScript_Entry::
	lockall
	goto PalletTown_Johto_PalletTownTeacherScript

PalletTown_Johto_PalletTownFisherScript_Entry::
	lockall
	goto PalletTown_Johto_PalletTownFisherScript

PalletTown_Johto_PalletTownSign_Entry::
	lockall
	goto PalletTown_Johto_PalletTownSign

PalletTown_Johto_RedsHouseSign_Entry::
	lockall
	goto PalletTown_Johto_RedsHouseSign

PalletTown_Johto_OaksLabSign_Entry::
	lockall
	goto PalletTown_Johto_OaksLabSign

PalletTown_Johto_BluesHouseSign_Entry::
	lockall
	goto PalletTown_Johto_BluesHouseSign


PalletTown_Johto_PalletTownTeacherScript:
	faceplayer
	message PalletTown_Johto_PalletTownTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_PalletTownFisherScript:
	faceplayer
	message PalletTown_Johto_PalletTownFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_PalletTownSign:
	message PalletTown_Johto_PalletTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_RedsHouseSign:
	message PalletTown_Johto_RedsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_OaksLabSign:
	message PalletTown_Johto_OaksLabSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_BluesHouseSign:
	message PalletTown_Johto_BluesHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PalletTown_Johto_PalletTownFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_PALLET
	return

PalletTown_Johto_PalletTownTeacherText:
	.string "I'm raising POKé-\n"
	.string "MON too."
	.string "\pThey serve as my\n"
	.string "private guards.$"

PalletTown_Johto_PalletTownFisherText:
	.string "Technology is\n"
	.string "incredible!"
	.string "\pYou can now trade\n"
	.string "POKéMON across\l"
	.string "time like e-mail.$"

PalletTown_Johto_PalletTownSignText:
	.string "PALLET TOWN"
	.string "\pA Tranquil Setting\n"
	.string "of Peace & Purity$"

PalletTown_Johto_RedsHouseSignText:
	.string "RED'S HOUSE$"

PalletTown_Johto_OaksLabSignText:
	.string "OAK POKéMON\n"
	.string "RESEARCH LAB$"

PalletTown_Johto_BluesHouseSignText:
	.string "BLUE'S HOUSE$"
