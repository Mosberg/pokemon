CianwoodPharmacy_Johto_MapScripts::
	.byte 0

CianwoodPharmacy_Johto_CianwoodPharmacist_Entry::
	lockall
	goto CianwoodPharmacy_Johto_CianwoodPharmacist

CianwoodPharmacy_Johto_CianwoodPharmacyBookshelf_Entry::
	lockall
	goto CianwoodPharmacy_Johto_CianwoodPharmacyBookshelf


CianwoodPharmacy_Johto_CianwoodPharmacist:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_SECRETPOTION_FROM_PHARMACY, CianwoodPharmacy_Johto_CianwoodPharmacist_Mart
	goto_if_unset FLAG_JOHTO_JASMINE_EXPLAINED_AMPHYS_SICKNESS, CianwoodPharmacy_Johto_CianwoodPharmacist_Mart
	message CianwoodPharmacy_Johto_PharmacistGiveSecretpotionText
	waitmessage
	waitbuttonpress
	additem ITEM_SECRETPOTION
	message CianwoodPharmacy_Johto_ReceivedSecretpotionText
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	setflag FLAG_JOHTO_GOT_SECRETPOTION_FROM_PHARMACY
	message CianwoodPharmacy_Johto_PharmacistDescribeSecretpotionText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPharmacy_Johto_CianwoodPharmacist_Mart:
	pokemart Johto_Mart_CIANWOOD
	closemessage
	releaseall
	end

CianwoodPharmacy_Johto_CianwoodPharmacyBookshelf:
	goto Johto_Std_DifficultBookshelfScript

CianwoodPharmacy_Johto_PharmacistGiveSecretpotionText:
	.string "Your POKéMON ap-\n"
	.string "pear to be fine."
	.string "\pIs something wor- \n"
	.string "rying you?"
	.string "\p…"
	.string "\pThe LIGHTHOUSE\n"
	.string "POKéMON is in\l"
	.string "trouble?"
	.string "\pI got it!"
	.string "\pThis ought to do\n"
	.string "the trick.$"

CianwoodPharmacy_Johto_ReceivedSecretpotionText:
	.string "{PLAYER} received\n"
	.string "SECRETPOTION.$"

CianwoodPharmacy_Johto_PharmacistDescribeSecretpotionText:
	.string "My SECRETPOTION is\n"
	.string "a tad too strong."
	.string "\pI only offer it in\n"
	.string "an emergency.$"
