OlivineCafe_Johto_MapScripts::
	.byte 0

OlivineCafe_Johto_OlivineCafeStrengthSailorScript_Entry::
	lockall
	goto OlivineCafe_Johto_OlivineCafeStrengthSailorScript

OlivineCafe_Johto_OlivineCafeFishingGuruScript_Entry::
	lockall
	goto OlivineCafe_Johto_OlivineCafeFishingGuruScript

OlivineCafe_Johto_OlivineCafeSailorScript_Entry::
	lockall
	goto OlivineCafe_Johto_OlivineCafeSailorScript


OlivineCafe_Johto_OlivineCafeStrengthSailorScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HM04_STRENGTH, OlivineCafe_Johto_OlivineCafeStrengthSailorScript_GotStrength
	message OlivineCafe_Johto_OlivineCafeStrengthSailorText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_JOHTO_GOT_HM04_STRENGTH

OlivineCafe_Johto_OlivineCafeStrengthSailorScript_GotStrength:
	message OlivineCafe_Johto_OlivineCafeStrengthSailorText_GotStrength
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCafe_Johto_OlivineCafeFishingGuruScript:
	faceplayer
	message OlivineCafe_Johto_OlivineCafeFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCafe_Johto_OlivineCafeSailorScript:
	faceplayer
	message OlivineCafe_Johto_OlivineCafeSailorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineCafe_Johto_OlivineCafeStrengthSailorText:
	.string "Hah! Your POKéMON\n"
	.string "sure look like\l"
	.string "lightweights!"
	.string "\pThey don't have\n"
	.string "the power to move\l"
	.string "boulders aside."
	.string "\pHere, use this\n"
	.string "and teach them\l"
	.string "STRENGTH!$"

OlivineCafe_Johto_OlivineCafeStrengthSailorText_GotStrength:
	.string "On the sea, the\n"
	.string "only thing you can"
	.string "\pcount on is your\n"
	.string "own good self!"
	.string "\pI'm so proud of my\n"
	.string "buff bod!$"

OlivineCafe_Johto_OlivineCafeFishingGuruText:
	.string "OLIVINE CAFE's\n"
	.string "menu is chock full"
	.string "\pof hearty fare for\n"
	.string "beefy SAILORS!$"

OlivineCafe_Johto_OlivineCafeSailorText:
	.string "Whenever I roll\n"
	.string "into this town, I"
	.string "\palways visit the\n"
	.string "OLIVINE CAFE."
	.string "\pEverything on the\n"
	.string "menu makes me feel"
	.string "\pstronger. I can't\n"
	.string "stop eating!$"
