MrFujisHouse_Johto_MapScripts::
	.byte 0

MrFujisHouse_Johto_MrFujisHouseSuperNerdScript_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisHouseSuperNerdScript

MrFujisHouse_Johto_MrFujisHouseLassScript_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisHouseLassScript

MrFujisHouse_Johto_MrFujisPsyduck_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisPsyduck

MrFujisHouse_Johto_MrFujisNidorino_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisNidorino

MrFujisHouse_Johto_MrFujisPidgey_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisPidgey

MrFujisHouse_Johto_MrFujisHouseBookshelf_Entry::
	lockall
	goto MrFujisHouse_Johto_MrFujisHouseBookshelf


MrFujisHouse_Johto_MrFujisHouseSuperNerdScript:
	faceplayer
	message MrFujisHouse_Johto_MrFujisHouseSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrFujisHouse_Johto_MrFujisHouseLassScript:
	faceplayer
	message MrFujisHouse_Johto_MrFujisHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MrFujisHouse_Johto_MrFujisPsyduck:
	message MrFujisHouse_Johto_MrFujisPsyduckText
	waitmessage
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

MrFujisHouse_Johto_MrFujisNidorino:
	message MrFujisHouse_Johto_MrFujisNidorinoText
	waitmessage
	playmoncry SPECIES_NIDORINO, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

MrFujisHouse_Johto_MrFujisPidgey:
	message MrFujisHouse_Johto_MrFujisPidgeyText
	waitmessage
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

MrFujisHouse_Johto_MrFujisHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

MrFujisHouse_Johto_MrFujisHouseSuperNerdText:
	.string "MR.FUJI does live\n"
	.string "here, but he's not"
	.string "\phome now."
	.string "\pHe should be at\n"
	.string "the SOUL HOUSE.$"

MrFujisHouse_Johto_MrFujisHouseLassText:
	.string "Some cold-hearted\n"
	.string "people stop caring\l"
	.string "for their POKéMON."
	.string "\pGrandpa takes in\n"
	.string "the poor homeless"
	.string "\pPOKéMON and takes\n"
	.string "care of them.$"

MrFujisHouse_Johto_MrFujisPsyduckText:
	.string "PSYDUCK: Gu-guwa?$"

MrFujisHouse_Johto_MrFujisNidorinoText:
	.string "NIDORINO: Gyun!$"

MrFujisHouse_Johto_MrFujisPidgeyText:
	.string "PIDGEY: Pijji!$"
