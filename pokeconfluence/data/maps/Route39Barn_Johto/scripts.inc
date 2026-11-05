Route39Barn_Johto_MapScripts::
	.byte 0

Route39Barn_Johto_Route39BarnTwin1Script_Entry::
	lockall
	goto Route39Barn_Johto_Route39BarnTwin1Script

Route39Barn_Johto_Route39BarnTwin2Script_Entry::
	lockall
	goto Route39Barn_Johto_Route39BarnTwin2Script

Route39Barn_Johto_MoomooScript_Entry::
	lockall
	goto Route39Barn_Johto_MoomooScript


Route39Barn_Johto_Route39BarnTwin1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_Route39BarnTwin1Script_FeedingMooMoo
	message Route39Barn_Johto_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin1Script_FeedingMooMoo:
	message Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_Route39BarnTwin2Script_FeedingMooMoo
	message Route39Barn_Johto_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin2Script_FeedingMooMoo:
	message Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	releaseall
	end

Route39Barn_Johto_MoomooScript:
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_MoomooScript_HappyCow
	message Route39Barn_Johto_MoomooWeakMooText
	waitmessage
	setvar VAR_0x8004, SPECIES_MILTANK
	playmoncry VAR_0x8004, CRY_MODE_WEAK
	waitmoncry
	waitbuttonpress
	message Route39Barn_Johto_Route39BarnItsCryIsWeakText
	waitmessage
	goto_if_set FLAG_JOHTO_TALKED_TO_FARMER_ABOUT_MOOMOO, Route39Barn_Johto_MoomooScript_GiveBerry
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_GiveBerry:
	waitbuttonpress
	message Route39Barn_Johto_Route39BarnAskGiveBerryText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route39Barn_Johto_MoomooScript_Refused
	checkitem ITEM_ORAN_BERRY, 1
	goto_if_eq VAR_RESULT, 0, Route39Barn_Johto_MoomooScript_NoBerriesInBag
	removeitem ITEM_ORAN_BERRY
	copyvar VAR_RESULT, VAR_JOHTO_MEM_WMOOMOOBERRIES
	addvar VAR_RESULT, 1
	copyvar VAR_JOHTO_MEM_WMOOMOOBERRIES, VAR_RESULT
	goto_if_eq VAR_RESULT, 3, Route39Barn_Johto_MoomooScript_ThreeBerries
	goto_if_eq VAR_RESULT, 5, Route39Barn_Johto_MoomooScript_FiveBerries
	goto_if_eq VAR_RESULT, 7, Route39Barn_Johto_MoomooScript_SevenBerries
	message Route39Barn_Johto_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_ThreeBerries:
	message Route39Barn_Johto_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	message Route39Barn_Johto_Route39BarnLittleHealthierText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_FiveBerries:
	message Route39Barn_Johto_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	message Route39Barn_Johto_Route39BarnQuiteHealthyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_SevenBerries:
	playbgm MUS_HEAL, FALSE
	message Route39Barn_Johto_Route39BarnGaveBerryText
	waitmessage
	delay 60
	waitbuttonpress
	fadedefaultbgm
	message Route39Barn_Johto_Route39BarnTotallyHealthyText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_HEALED_MOOMOO
	releaseall
	end

Route39Barn_Johto_MoomooScript_NoBerriesInBag:
	message Route39Barn_Johto_Route39BarnNoBerriesText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_Refused:
	message Route39Barn_Johto_Route39BarnRefusedBerryText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_MoomooScript_HappyCow:
	message Route39Barn_Johto_MoomooHappyMooText
	waitmessage
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_Route39BarnTwinMoomooIsSickText:
	.string "MOOMOO is sick…"
	.string "\pShe needs lots of\n"
	.string "BERRIES.$"

Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText:
	.string "We're feeding\n"
	.string "MOOMOO!$"

Route39Barn_Johto_MoomooWeakMooText:
	.string "MILTANK: …Moo…$"

Route39Barn_Johto_Route39BarnItsCryIsWeakText:
	.string "Its cry is weak…$"

Route39Barn_Johto_MoomooHappyMooText:
	.string "MILTANK: Mooo!$"

Route39Barn_Johto_Route39BarnAskGiveBerryText:
	.string "Give a BERRY to\n"
	.string "MILTANK?$"

Route39Barn_Johto_Route39BarnGaveBerryText:
	.string "{PLAYER} gave a\n"
	.string "BERRY to MILTANK.$"

Route39Barn_Johto_Route39BarnLittleHealthierText:
	.string "MILTANK became a\n"
	.string "little healthier!$"

Route39Barn_Johto_Route39BarnQuiteHealthyText:
	.string "MILTANK became\n"
	.string "quite healthy!$"

Route39Barn_Johto_Route39BarnTotallyHealthyText:
	.string "MILTANK became\n"
	.string "totally healthy!$"

Route39Barn_Johto_Route39BarnNoBerriesText:
	.string "{PLAYER} has no\n"
	.string "BERRIES…$"

Route39Barn_Johto_Route39BarnRefusedBerryText:
	.string "{PLAYER} wouldn't\n"
	.string "give a BERRY."
	.string "\pMILTANK looks sad.$"
