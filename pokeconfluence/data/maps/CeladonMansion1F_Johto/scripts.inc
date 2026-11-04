CeladonMansion1F_Johto_MapScripts::
	.byte 0

CeladonMansion1F_Johto_CeladonMansionManager_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansionManager

CeladonMansion1F_Johto_CeladonMansion1FMeowth_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansion1FMeowth

CeladonMansion1F_Johto_CeladonMansion1FClefairy_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansion1FClefairy

CeladonMansion1F_Johto_CeladonMansion1FNidoranF_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansion1FNidoranF

CeladonMansion1F_Johto_CeladonMansionManagersSuiteSign_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansionManagersSuiteSign

CeladonMansion1F_Johto_CeladonMansion1FBookshelf_Entry::
	lockall
	goto CeladonMansion1F_Johto_CeladonMansion1FBookshelf


CeladonMansion1F_Johto_CeladonMansionManager:
	faceplayer
	message CeladonMansion1F_Johto_CeladonMansionManagerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion1F_Johto_CeladonMansion1FMeowth:
	message CeladonMansion1F_Johto_CeladonMansion1FMeowthText
	waitmessage
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion1F_Johto_CeladonMansion1FClefairy:
	message CeladonMansion1F_Johto_CeladonMansion1FClefairyText
	waitmessage
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion1F_Johto_CeladonMansion1FNidoranF:
	message CeladonMansion1F_Johto_CeladonMansion1FNidoranFText
	waitmessage
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion1F_Johto_CeladonMansionManagersSuiteSign:
	message CeladonMansion1F_Johto_CeladonMansionManagersSuiteSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion1F_Johto_CeladonMansion1FBookshelf:
	goto Johto_Std_PictureBookshelfScript

CeladonMansion1F_Johto_CeladonMansionManagerText:
	.string "My dear POKéMON\n"
	.string "keep me company,"
	.string "\pso I don't ever\n"
	.string "feel lonely."
	.string "\pMEOWTH even brings\n"
	.string "money home.$"

CeladonMansion1F_Johto_CeladonMansion1FMeowthText:
	.string "MEOWTH: Meow!$"

CeladonMansion1F_Johto_CeladonMansion1FClefairyText:
	.string "CLEFAIRY: Clef\n"
	.string "cleff!$"

CeladonMansion1F_Johto_CeladonMansion1FNidoranFText:
	.string "NIDORAN: Kya\n"
	.string "kyaoo!$"

CeladonMansion1F_Johto_CeladonMansionManagersSuiteSignText:
	.string "CELADON MANSION\n"
	.string "MANAGER'S SUITE$"
