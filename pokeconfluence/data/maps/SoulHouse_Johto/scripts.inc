SoulHouse_Johto_MapScripts::
	.byte 0

SoulHouse_Johto_MrFuji_Entry::
	lockall
	goto SoulHouse_Johto_MrFuji

SoulHouse_Johto_SoulHouseTeacherScript_Entry::
	lockall
	goto SoulHouse_Johto_SoulHouseTeacherScript

SoulHouse_Johto_SoulHouseLassScript_Entry::
	lockall
	goto SoulHouse_Johto_SoulHouseLassScript

SoulHouse_Johto_SoulHouseGrannyScript_Entry::
	lockall
	goto SoulHouse_Johto_SoulHouseGrannyScript


SoulHouse_Johto_MrFuji:
	faceplayer
	message SoulHouse_Johto_MrFujiText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SoulHouse_Johto_SoulHouseTeacherScript:
	faceplayer
	message SoulHouse_Johto_SoulHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SoulHouse_Johto_SoulHouseLassScript:
	faceplayer
	message SoulHouse_Johto_SoulHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SoulHouse_Johto_SoulHouseGrannyScript:
	faceplayer
	message SoulHouse_Johto_SoulHouseGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SoulHouse_Johto_MrFujiText:
	.string "MR.FUJI: Welcome."
	.string "\pHmm… You appear to\n"
	.string "be raising your"
	.string "\pPOKéMON in a kind\n"
	.string "and loving manner."
	.string "\pPOKéMON lovers\n"
	.string "come here to pay"
	.string "\ptheir respects to\n"
	.string "departed POKéMON."
	.string "\pPlease offer con-\n"
	.string "dolences for the"
	.string "\psouls of the de-\n"
	.string "parted POKéMON."
	.string "\pI'm sure that will\n"
	.string "make them happy.$"

SoulHouse_Johto_SoulHouseTeacherText:
	.string "There are other\n"
	.string "graves of POKéMON\l"
	.string "here, I think."
	.string "\pThere are many\n"
	.string "chambers that only\l"
	.string "MR.FUJI may enter.$"

SoulHouse_Johto_SoulHouseLassText:
	.string "I came with my mom\n"
	.string "to visit POKéMON\l"
	.string "graves…$"

SoulHouse_Johto_SoulHouseGrannyText:
	.string "The POKéMON that\n"
	.string "lived with me…"
	.string "\pI loved them like\n"
	.string "my grandchildren…$"
