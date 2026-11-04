OlivineLighthouse6F_Johto_MapScripts::
	.byte 0

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_Entry::
	lockall
	goto OlivineLighthouse6F_Johto_OlivineLighthouseJasmine

OlivineLighthouse6F_Johto_OlivineLighthouseAmphy_Entry::
	lockall
	goto OlivineLighthouse6F_Johto_OlivineLighthouseAmphy

OlivineLighthouse6F_Johto_OlivineLighthouse6FSuperPotion_Entry::
	lockall
	goto OlivineLighthouse6F_Johto_OlivineLighthouse6FSuperPotion


OlivineLighthouse6F_Johto_OlivineLighthouseJasmine:
	faceplayer
	checkitem ITEM_SECRETPOTION, 1
	goto_if_ne VAR_RESULT, 0, OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_BroughtSecretpotion
	goto_if_set FLAG_JOHTO_JASMINE_EXPLAINED_AMPHYS_SICKNESS, OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_ExplainedSickness
	message OlivineLighthouse6F_Johto_JasmineCianwoodPharmacyText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_JASMINE_EXPLAINED_AMPHYS_SICKNESS

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_ExplainedSickness:
	message OlivineLighthouse6F_Johto_JasmineGetSomeMedicineText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_BroughtSecretpotion:
	message OlivineLighthouse6F_Johto_JasmineCureAmphyText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_Refused
	message OlivineLighthouse6F_Johto_PlayerHandedSecretpotionText
	waitmessage
	waitbuttonpress
	removeitem ITEM_SECRETPOTION
	message OlivineLighthouse6F_Johto_JasmineDontBeOffendedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	delay 15
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	playbgm MUS_HEAL, FALSE
	message OlivineLighthouse6F_Johto_JasmineAmphyHowAreYouFeelingText
	waitmessage
	delay 60
	waitbuttonpress
	closemessage
	fadedefaultbgm
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_TO_WHITE
	delay 10
	fadescreen FADE_FROM_WHITE
	message OlivineLighthouse6F_Johto_AmphyPaluPaluluText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Right
	waitmovement 2
	delay 10
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	delay 10
	applymovement 2, Johto_Movement_Face_Right
	waitmovement 2
	delay 10
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	delay 10
	faceplayer
	message OlivineLighthouse6F_Johto_JasmineThankYouText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_JASMINE_RETURNED_TO_GYM
	clearflag FLAG_JOHTO_OLIVINE_GYM_JASMINE
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_FacingDown
	goto_if_eq VAR_RESULT, DIR_EAST, OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_FacingRight
	applymovement 1, OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesUpMovement
	waitmovement 1
	removeobject 1
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_FacingDown:
	applymovement 1, OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesDownMovement
	waitmovement 1
	removeobject 1
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_FacingRight:
	applymovement 1, OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesRightMovement
	waitmovement 1
	removeobject 1
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmine_Refused:
	message OlivineLighthouse6F_Johto_JasmineISeeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	delay 15
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	message OlivineLighthouse6F_Johto_JasmineAmphyHangOnText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseAmphy:
	faceplayer
	goto_if_set FLAG_JOHTO_JASMINE_RETURNED_TO_GYM, OlivineLighthouse6F_Johto_OlivineLighthouseAmphy_HealthyNow
	message OlivineLighthouse6F_Johto_AmphyPalPalooText
	waitmessage
	setvar VAR_0x8004, SPECIES_AMPHAROS
	@ TODO unsupported: special PlaySlowCry
	goto Johto_EventScript_Unimplemented

OlivineLighthouse6F_Johto_OlivineLighthouseAmphy_HealthyNow:
	message OlivineLighthouse6F_Johto_AmphyPaluPaluluText
	waitmessage
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouse6FSuperPotion:
	finditem ITEM_SUPER_POTION
	releaseall
	end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesUpMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	delay_8
	delay_8
	step_end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesDownMovement:
	walk_slow_down
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_up
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end

OlivineLighthouse6F_Johto_OlivineLighthouseJasmineLeavesRightMovement:
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	delay_8
	step_end

OlivineLighthouse6F_Johto_JasmineCianwoodPharmacyText:
	.string "JASMINE: … This\n"
	.string "POKéMON always"
	.string "\pkept the sea lit\n"
	.string "at night."
	.string "\p…But it suddenly\n"
	.string "got sick… It's\l"
	.string "gasping for air…"
	.string "\p…I understand\n"
	.string "that there is a"
	.string "\pwonderful PHARMACY\n"
	.string "in CIANWOOD…"
	.string "\pBut that's across\n"
	.string "the sea…"
	.string "\pAnd I can't leave\n"
	.string "AMPHY unattended…$"

OlivineLighthouse6F_Johto_JasmineGetSomeMedicineText:
	.string "…May I ask you to\n"
	.string "get some medicine\l"
	.string "for me? Please?$"

OlivineLighthouse6F_Johto_JasmineCureAmphyText:
	.string "JASMINE: …Will\n"
	.string "that medicine cure\l"
	.string "AMPHY?$"

OlivineLighthouse6F_Johto_PlayerHandedSecretpotionText:
	.string "{PLAYER} handed the\n"
	.string "SECRETPOTION to\l"
	.string "JASMINE.$"

OlivineLighthouse6F_Johto_JasmineDontBeOffendedText:
	.string "JASMINE: …Um,\n"
	.string "please don't be\l"
	.string "offended…"
	.string "\p…AMPHY will not\n"
	.string "take anything from\l"
	.string "anyone but me…$"

OlivineLighthouse6F_Johto_JasmineAmphyHowAreYouFeelingText:
	.string "JASMINE: …"
	.string "\pAMPHY, how are you\n"
	.string "feeling?$"

OlivineLighthouse6F_Johto_JasmineThankYouText:
	.string "JASMINE: …Oh, I'm\n"
	.string "so relieved…"
	.string "\pThis is just so\n"
	.string "wonderful…"
	.string "\pThank you so very,\n"
	.string "very much."
	.string "\p…I will return to\n"
	.string "the GYM…$"

OlivineLighthouse6F_Johto_JasmineISeeText:
	.string "JASMINE: …I see…$"

OlivineLighthouse6F_Johto_JasmineAmphyHangOnText:
	.string "…AMPHY, hang on!$"

OlivineLighthouse6F_Johto_AmphyPalPalooText:
	.string "AMPHY: …\n"
	.string "…Pa… paloo…$"

OlivineLighthouse6F_Johto_AmphyPaluPaluluText:
	.string "AMPHY: Palu!\n"
	.string "Palulu!$"
