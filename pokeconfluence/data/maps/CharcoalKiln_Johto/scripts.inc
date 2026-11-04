CharcoalKiln_Johto_MapScripts::
	.byte 0

CharcoalKiln_Johto_CharcoalKilnBoss_Entry::
	lockall
	goto CharcoalKiln_Johto_CharcoalKilnBoss

CharcoalKiln_Johto_CharcoalKilnApprentice_Entry::
	lockall
	goto CharcoalKiln_Johto_CharcoalKilnApprentice

CharcoalKiln_Johto_CharcoalKilnFarfetchd_Entry::
	lockall
	goto CharcoalKiln_Johto_CharcoalKilnFarfetchd

CharcoalKiln_Johto_CharcoalKilnBookshelf_Entry::
	lockall
	goto CharcoalKiln_Johto_CharcoalKilnBookshelf

CharcoalKiln_Johto_CharcoalKilnRadio_Entry::
	lockall
	goto CharcoalKiln_Johto_CharcoalKilnRadio


CharcoalKiln_Johto_CharcoalKilnBoss:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HM01_CUT, CharcoalKiln_Johto_CharcoalKilnBoss_GotCut
	goto_if_set FLAG_JOHTO_CLEARED_SLOWPOKE_WELL, CharcoalKiln_Johto_CharcoalKilnBoss_SavedSlowpoke
	message CharcoalKiln_Johto_CharcoalKilnBossText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnBoss_SavedSlowpoke:
	message CharcoalKiln_Johto_CharcoalKilnBossText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnBoss_GotCut:
	message CharcoalKiln_Johto_CharcoalKilnBossText3
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnApprentice:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_CHARCOAL_IN_CHARCOAL_KILN, CharcoalKiln_Johto_CharcoalKilnApprentice_YoureTheCoolest
	goto_if_set FLAG_JOHTO_GOT_HM01_CUT, CharcoalKiln_Johto_CharcoalKilnApprentice_Thanks
	message CharcoalKiln_Johto_CharcoalKilnApprenticeText1
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnApprentice_Thanks:
	message CharcoalKiln_Johto_CharcoalKilnApprenticeText2
	waitmessage
	waitbuttonpress
	giveitem ITEM_CHARCOAL
	goto_if_eq VAR_RESULT, 0, CharcoalKiln_Johto_CharcoalKilnApprentice_Done
	setflag FLAG_JOHTO_GOT_CHARCOAL_IN_CHARCOAL_KILN
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnApprentice_YoureTheCoolest:
	message CharcoalKiln_Johto_CharcoalKilnApprenticeText3
	waitmessage
	waitbuttonpress

CharcoalKiln_Johto_CharcoalKilnApprentice_Done:
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnFarfetchd:
	faceplayer
	message CharcoalKiln_Johto_FarfetchdText
	waitmessage
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CharcoalKiln_Johto_CharcoalKilnBookshelf:
	goto Johto_Std_MagazineBookshelfScript

CharcoalKiln_Johto_CharcoalKilnRadio:
	goto Johto_Std_Radio2Script

CharcoalKiln_Johto_CharcoalKilnBossText1:
	.string "All the SLOWPOKE\n"
	.string "have disappeared\l"
	.string "from the town."
	.string "\pThe forest's pro-\n"
	.string "tector may be\l"
	.string "angry with us…"
	.string "\pIt may be a bad\n"
	.string "omen. We should\l"
	.string "stay in.$"

CharcoalKiln_Johto_CharcoalKilnBossText2:
	.string "The SLOWPOKE have\n"
	.string "returned…"
	.string "\pBut my APPRENTICE\n"
	.string "hasn't come back\l"
	.string "from ILEX FOREST."
	.string "\pWhere in the world\n"
	.string "is that lazy guy?$"

CharcoalKiln_Johto_CharcoalKilnBossText3:
	.string "You chased off\n"
	.string "TEAM ROCKET and"
	.string "\pwent to ILEX\n"
	.string "FOREST alone?"
	.string "\pThat takes guts!\n"
	.string "I like that. Come\l"
	.string "train with us.$"

CharcoalKiln_Johto_CharcoalKilnApprenticeText1:
	.string "Where have all the\n"
	.string "SLOWPOKE gone?"
	.string "\pAre they out play-\n"
	.string "ing somewhere?$"

CharcoalKiln_Johto_CharcoalKilnApprenticeText2:
	.string "I'm sorry--I for-\n"
	.string "got to thank you."
	.string "\pThis is CHARCOAL\n"
	.string "that I made."
	.string "\pFire-type POKéMON\n"
	.string "would be happy to\l"
	.string "hold that.$"

CharcoalKiln_Johto_CharcoalKilnApprenticeText3:
	.string "The SLOWPOKE came\n"
	.string "back, and you even\l"
	.string "found FARFETCH'D."
	.string "\pYou're the cool-\n"
	.string "est, man!$"

CharcoalKiln_Johto_FarfetchdText:
	.string "FARFETCH'D: Kwaa!$"
