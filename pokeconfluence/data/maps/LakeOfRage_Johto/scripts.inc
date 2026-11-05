LakeOfRage_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_Johto_OnTransition
		map_script MAP_SCRIPT_ON_LOAD, LakeOfRage_Johto_OnLoad
	.byte 0

LakeOfRage_Johto_OnTransition:
	call LakeOfRage_Johto_LakeOfRageFlypointCallback_Cb
	call LakeOfRage_Johto_LakeOfRageWesleyCallback_Cb
	end

LakeOfRage_Johto_LakeOfRageLanceScript_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageLanceScript

LakeOfRage_Johto_LakeOfRageGrampsScript_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageGrampsScript

LakeOfRage_Johto_LakeOfRageSuperNerdScript_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageSuperNerdScript

LakeOfRage_Johto_LakeOfRageCooltrainerFScript_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageCooltrainerFScript

LakeOfRage_Johto_RedGyarados_Entry::
	lockall
	goto LakeOfRage_Johto_RedGyarados

LakeOfRage_Johto_WesleyScript_Entry::
	lockall
	goto LakeOfRage_Johto_WesleyScript

LakeOfRage_Johto_LakeOfRageElixer_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageElixer

LakeOfRage_Johto_LakeOfRageTMDetect_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageTMDetect

LakeOfRage_Johto_LakeOfRageSign_Entry::
	lockall
	goto LakeOfRage_Johto_LakeOfRageSign

LakeOfRage_Johto_MagikarpHouseSignScript_Entry::
	lockall
	goto LakeOfRage_Johto_MagikarpHouseSignScript


LakeOfRage_Johto_LakeOfRageLanceScript:
	goto_if_set FLAG_JOHTO_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE, LakeOfRage_Johto_LakeOfRageLanceScript_AskAgainForHelp
	message LakeOfRage_Johto_LakeOfRageLanceForcedToEvolveText
	waitmessage
	waitbuttonpress
	faceplayer
	message LakeOfRage_Johto_LakeOfRageLanceIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, LakeOfRage_Johto_LakeOfRageLanceScript_RefusedToHelp

LakeOfRage_Johto_LakeOfRageLanceScript_AgreedToHelp:
	message LakeOfRage_Johto_LakeOfRageLanceRadioSignalText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_WARP_IN
	applymovement 1, LakeOfRage_Johto_LakeOfRageLanceTeleportIntoSkyMovement
	waitmovement 1
	removeobject 1
	clearflag FLAG_JOHTO_MAHOGANY_MART_LANCE_AND_DRAGONITE
	setflag FLAG_JOHTO_DECIDED_TO_HELP_LANCE
	setvar VAR_JOHTO_SCENE_MAHOGANY_MART_1F, 1
	releaseall
	end

LakeOfRage_Johto_LakeOfRageLanceScript_RefusedToHelp:
	message LakeOfRage_Johto_LakeOfRageLanceRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE
	releaseall
	end

LakeOfRage_Johto_LakeOfRageLanceScript_AskAgainForHelp:
	faceplayer
	message LakeOfRage_Johto_LakeOfRageLanceAskHelpText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, LakeOfRage_Johto_LakeOfRageLanceScript_RefusedToHelp
	goto LakeOfRage_Johto_LakeOfRageLanceScript_AgreedToHelp

LakeOfRage_Johto_RedGyarados:
	message LakeOfRage_Johto_LakeOfRageGyaradosCryText
	waitmessage
	delay 15
	playmoncry SPECIES_GYARADOS, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	setwildbattle SPECIES_GYARADOS, 30
	dowildbattle
	goto_if_eq VAR_RESULT, 0, LakeOfRage_Johto_RedGyarados_NotBeaten
	removeobject 9

LakeOfRage_Johto_RedGyarados_NotBeaten:
	additem ITEM_RED_SCALE
	waitse
	message LakeOfRage_Johto_LakeOfRageGotRedScaleText
	waitmessage
	playse SE_PIN
	waitse
	closemessage
	setvar VAR_JOHTO_SCENE_LAKE_OF_RAGE, 0
	clearflag FLAG_JOHTO_LAKE_OF_RAGE_LANCE
	addobject 1
	releaseall
	end

LakeOfRage_Johto_LakeOfRageGrampsScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, LakeOfRage_Johto_LakeOfRageGrampsScript_ClearedRocketHideout
	message LakeOfRage_Johto_LakeOfRageGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_LakeOfRageGrampsScript_ClearedRocketHideout:
	message LakeOfRage_Johto_LakeOfRageGrampsText_ClearedRocketHideout
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_LakeOfRageSuperNerdScript:
	faceplayer
	message LakeOfRage_Johto_LakeOfRageSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_LakeOfRageCooltrainerFScript:
	faceplayer
	message LakeOfRage_Johto_LakeOfRageCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_LakeOfRageSign:
	message LakeOfRage_Johto_LakeOfRageSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_MagikarpHouseSignScript:
	message LakeOfRage_Johto_FishingGurusHouseSignText
	waitmessage
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, LakeOfRage_Johto_MagikarpHouseSignScript_MagikarpLengthRecord
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_MagikarpHouseSignScript_MagikarpLengthRecord:
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_TrainerFisherAndre::
	trainerbattle_single TRAINER_JOHTO_FISHER_ANDRE, LakeOfRage_Johto_FisherAndreSeenText, LakeOfRage_Johto_FisherAndreBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_ANDRE
	lock
	faceplayer
	goto LakeOfRage_Johto_TrainerFisherAndre_Script

LakeOfRage_Johto_TrainerFisherAndre_Script:
	message LakeOfRage_Johto_FisherAndreAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_TrainerFisherRaymond::
	trainerbattle_single TRAINER_JOHTO_FISHER_RAYMOND, LakeOfRage_Johto_FisherRaymondSeenText, LakeOfRage_Johto_FisherRaymondBeatenText
	setflag FLAG_JOHTO_BEAT_FISHER_RAYMOND
	lock
	faceplayer
	goto LakeOfRage_Johto_TrainerFisherRaymond_Script

LakeOfRage_Johto_TrainerFisherRaymond_Script:
	message LakeOfRage_Johto_FisherRaymondAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_TrainerCooltrainermAaron::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_AARON, LakeOfRage_Johto_CooltrainermAaronSeenText, LakeOfRage_Johto_CooltrainermAaronBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_AARON
	lock
	faceplayer
	goto LakeOfRage_Johto_TrainerCooltrainermAaron_Script

LakeOfRage_Johto_TrainerCooltrainermAaron_Script:
	message LakeOfRage_Johto_CooltrainermAaronAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_TrainerCooltrainerfLois::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_LOIS, LakeOfRage_Johto_CooltrainerfLoisSeenText, LakeOfRage_Johto_CooltrainerfLoisBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_LOIS
	lock
	faceplayer
	goto LakeOfRage_Johto_TrainerCooltrainerfLois_Script

LakeOfRage_Johto_TrainerCooltrainerfLois_Script:
	message LakeOfRage_Johto_CooltrainerfLoisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_WesleyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_BLACKBELT_FROM_WESLEY, LakeOfRage_Johto_WesleyWednesdayScript
	special JohtoGetWeekday
	goto_if_ne VAR_RESULT, 3, LakeOfRage_Johto_WesleyNotWednesdayScript
	goto_if_set FLAG_JOHTO_MET_WESLEY_OF_WEDNESDAY, LakeOfRage_Johto_WesleyScript_MetWesley
	message LakeOfRage_Johto_MeetWesleyText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_MET_WESLEY_OF_WEDNESDAY

LakeOfRage_Johto_WesleyScript_MetWesley:
	message LakeOfRage_Johto_WesleyGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_BLACKBELT_I
	goto_if_eq VAR_RESULT, 0, LakeOfRage_Johto_WesleyDoneScript
	setflag FLAG_JOHTO_GOT_BLACKBELT_FROM_WESLEY
	message LakeOfRage_Johto_WesleyGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_WesleyWednesdayScript:
	message LakeOfRage_Johto_WesleyWednesdayText
	waitmessage
	waitbuttonpress

LakeOfRage_Johto_WesleyDoneScript:
	closemessage
	releaseall
	end

LakeOfRage_Johto_WesleyNotWednesdayScript:
	message LakeOfRage_Johto_WesleyNotWednesdayText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRage_Johto_LakeOfRageElixer:
	finditem ITEM_ELIXER
	releaseall
	end

LakeOfRage_Johto_LakeOfRageTMDetect:
	finditem ITEM_TM_PROTECT
	releaseall
	end

LakeOfRage_Johto_LakeOfRageFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_LAKE_OF_RAGE
	return

LakeOfRage_Johto_LakeOfRageWesleyCallback_Cb:
	special JohtoGetWeekday
	goto_if_eq VAR_RESULT, 3, LakeOfRage_Johto_LakeOfRageWesleyCallback_WesleyAppears_Cb
	setflag FLAG_JOHTO_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY
	return

LakeOfRage_Johto_LakeOfRageWesleyCallback_WesleyAppears_Cb:
	clearflag FLAG_JOHTO_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY
	return

LakeOfRage_Johto_LakeOfRageLanceTeleportIntoSkyMovement:
	set_invisible
	step_end

LakeOfRage_Johto_LakeOfRageLanceForcedToEvolveText:
	.string "This lake is full\n"
	.string "of GYARADOS but\l"
	.string "nothing else…"
	.string "\pSo the MAGIKARP\n"
	.string "are being forced\l"
	.string "to evolve…$"

LakeOfRage_Johto_LakeOfRageLanceIntroText:
	.string "Did you come here\n"
	.string "because of the\l"
	.string "rumors?"
	.string "\pYou're {PLAYER}?\n"
	.string "I'm LANCE, a\l"
	.string "trainer like you."
	.string "\pI heard some ru-\n"
	.string "mors, so I came to\l"
	.string "investigate…"
	.string "\pI saw the way you\n"
	.string "battled earlier,\l"
	.string "{PLAYER}."
	.string "\pI can tell that\n"
	.string "you're a trainer"
	.string "\pwith considerable\n"
	.string "skill."
	.string "\pIf you don't mind,\n"
	.string "could you help me\l"
	.string "investigate?$"

LakeOfRage_Johto_LakeOfRageLanceRadioSignalText:
	.string "LANCE: Excellent!"
	.string "\pIt seems that the\n"
	.string "LAKE's MAGIKARP"
	.string "\pare being forced\n"
	.string "to evolve."
	.string "\pA mysterious radio\n"
	.string "broadcast coming"
	.string "\pfrom MAHOGANY is\n"
	.string "the cause."
	.string "\pI'll be waiting\n"
	.string "for you, {PLAYER}.$"

LakeOfRage_Johto_LakeOfRageLanceRefusedText:
	.string "Oh… Well, if you\n"
	.string "change your mind,\l"
	.string "please help me.$"

LakeOfRage_Johto_LakeOfRageLanceAskHelpText:
	.string "LANCE: Hm? Are you\n"
	.string "going to help me?$"

LakeOfRage_Johto_LakeOfRageGyaradosCryText:
	.string "GYARADOS: Gyashaa!$"

LakeOfRage_Johto_LakeOfRageGotRedScaleText:
	.string "{PLAYER} obtained a\n"
	.string "RED SCALE.$"

LakeOfRage_Johto_LakeOfRageGrampsText:
	.string "The GYARADOS are\n"
	.string "angry!"
	.string "\pIt's a bad omen!$"

LakeOfRage_Johto_LakeOfRageGrampsText_ClearedRocketHideout:
	.string "Hahah! The MAGI-\n"
	.string "KARP are biting!$"

LakeOfRage_Johto_LakeOfRageSuperNerdText:
	.string "I heard this lake\n"
	.string "was made by ram-\l"
	.string "paging GYARADOS."
	.string "\pI wonder if there\n"
	.string "is any connection"
	.string "\pto their mass out-\n"
	.string "break now?$"

LakeOfRage_Johto_LakeOfRageCooltrainerFText:
	.string "Did my eyes de-\n"
	.string "ceive me? I saw a"
	.string "\pred GYARADOS in\n"
	.string "the LAKE…"
	.string "\pBut I thought\n"
	.string "GYARADOS were\l"
	.string "usually blue?$"

LakeOfRage_Johto_FisherAndreSeenText:
	.string "Let me battle with\n"
	.string "the POKéMON I just\l"
	.string "caught!$"

LakeOfRage_Johto_FisherAndreBeatenText:
	.string "I might be an ex-\n"
	.string "pert angler, but"
	.string "\pI stink as a POKé-\n"
	.string "MON trainer…$"

LakeOfRage_Johto_FisherAndreAfterBattleText:
	.string "I won't lose as an\n"
	.string "angler! I catch\l"
	.string "POKéMON all day.$"

LakeOfRage_Johto_FisherRaymondSeenText:
	.string "No matter what I\n"
	.string "do, all I catch"
	.string "\pare the same POKé-\n"
	.string "MON…$"

LakeOfRage_Johto_FisherRaymondBeatenText:
	.string "My line's all\n"
	.string "tangled up…$"

LakeOfRage_Johto_FisherRaymondAfterBattleText:
	.string "Why can't I catch\n"
	.string "any good POKéMON?$"

LakeOfRage_Johto_CooltrainermAaronSeenText:
	.string "If a trainer spots\n"
	.string "another trainer,"
	.string "\phe has to make a\n"
	.string "challenge."
	.string "\pThat is our\n"
	.string "destiny.$"

LakeOfRage_Johto_CooltrainermAaronBeatenText:
	.string "Whew…\n"
	.string "Good battle.$"

LakeOfRage_Johto_CooltrainermAaronAfterBattleText:
	.string "POKéMON and their\n"
	.string "trainer become"
	.string "\ppowerful through\n"
	.string "constant battling.$"

LakeOfRage_Johto_CooltrainerfLoisSeenText:
	.string "What happened to\n"
	.string "the red GYARADOS?"
	.string "\pIt's gone?"
	.string "\pOh, darn. I came\n"
	.string "here for nothing?"
	.string "\pI know--let's\n"
	.string "battle!$"

LakeOfRage_Johto_CooltrainerfLoisBeatenText:
	.string "Good going!$"

LakeOfRage_Johto_CooltrainerfLoisAfterBattleText:
	.string "Come to think of\n"
	.string "it, I've seen a\l"
	.string "pink BUTTERFREE.$"

LakeOfRage_Johto_MeetWesleyText:
	.string "WESLEY: Well, how\n"
	.string "do you do?"
	.string "\pSeeing as how it's\n"
	.string "Wednesday today,"
	.string "\pI'm WESLEY of\n"
	.string "Wednesday.$"

LakeOfRage_Johto_WesleyGivesGiftText:
	.string "Pleased to meet\n"
	.string "you. Please take a\l"
	.string "souvenir.$"

LakeOfRage_Johto_WesleyGaveGiftText:
	.string "WESLEY: BLACKBELT\n"
	.string "beefs up the power\l"
	.string "of fighting moves.$"

LakeOfRage_Johto_WesleyWednesdayText:
	.string "WESLEY: Since you\n"
	.string "found me, you must"
	.string "\phave met my broth-\n"
	.string "ers and sisters."
	.string "\pOr did you just\n"
	.string "get lucky?$"

LakeOfRage_Johto_WesleyNotWednesdayText:
	.string "WESLEY: Today's\n"
	.string "not Wednesday.\l"
	.string "That's too bad.$"

LakeOfRage_Johto_LakeOfRageSignText:
	.string "LAKE OF RAGE,\n"
	.string "also known as\l"
	.string "GYARADOS LAKE.$"

LakeOfRage_Johto_FishingGurusHouseSignText:
	.string "FISHING GURU'S\n"
	.string "HOUSE$"

LakeOfRage_Johto_OnLoad:
	goto_if_unset FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_0, LakeOfRage_Johto_CutTree0_Keep
	setmetatile 22, 4, 591, 0
	setmetatile 23, 4, 514, 0
	setmetatile 22, 5, 514, 0
	setmetatile 23, 5, 514, 0
LakeOfRage_Johto_CutTree0_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_1, LakeOfRage_Johto_CutTree1_Keep
	setmetatile 18, 8, 514, 0
	setmetatile 19, 8, 514, 0
	setmetatile 18, 9, 514, 0
	setmetatile 19, 9, 591, 0
LakeOfRage_Johto_CutTree1_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_2, LakeOfRage_Johto_CutTree2_Keep
	setmetatile 10, 12, 591, 0
	setmetatile 11, 12, 514, 0
	setmetatile 10, 13, 514, 0
	setmetatile 11, 13, 514, 0
LakeOfRage_Johto_CutTree2_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_3, LakeOfRage_Johto_CutTree3_Keep
	setmetatile 4, 14, 591, 0
	setmetatile 5, 14, 514, 0
	setmetatile 4, 15, 514, 0
	setmetatile 5, 15, 514, 0
LakeOfRage_Johto_CutTree3_Keep:
	goto_if_unset FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_4, LakeOfRage_Johto_CutTree4_Keep
	setmetatile 6, 20, 514, 0
	setmetatile 7, 20, 514, 0
	setmetatile 6, 21, 514, 0
	setmetatile 7, 21, 591, 0
LakeOfRage_Johto_CutTree4_Keep:
	end

LakeOfRage_Johto_CutTree0::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_Johto_CutTree0_Done
	setflag FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_0
	setmetatile 22, 4, 591, 0
	setmetatile 23, 4, 514, 0
	setmetatile 22, 5, 514, 0
	setmetatile 23, 5, 514, 0
	special DrawWholeMapView
LakeOfRage_Johto_CutTree0_Done:
	releaseall
	end

LakeOfRage_Johto_CutTree1::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_Johto_CutTree1_Done
	setflag FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_1
	setmetatile 18, 8, 514, 0
	setmetatile 19, 8, 514, 0
	setmetatile 18, 9, 514, 0
	setmetatile 19, 9, 591, 0
	special DrawWholeMapView
LakeOfRage_Johto_CutTree1_Done:
	releaseall
	end

LakeOfRage_Johto_CutTree2::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_Johto_CutTree2_Done
	setflag FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_2
	setmetatile 10, 12, 591, 0
	setmetatile 11, 12, 514, 0
	setmetatile 10, 13, 514, 0
	setmetatile 11, 13, 514, 0
	special DrawWholeMapView
LakeOfRage_Johto_CutTree2_Done:
	releaseall
	end

LakeOfRage_Johto_CutTree3::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_Johto_CutTree3_Done
	setflag FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_3
	setmetatile 4, 14, 591, 0
	setmetatile 5, 14, 514, 0
	setmetatile 4, 15, 514, 0
	setmetatile 5, 15, 514, 0
	special DrawWholeMapView
LakeOfRage_Johto_CutTree3_Done:
	releaseall
	end

LakeOfRage_Johto_CutTree4::
	lockall
	call Johto_Std_TryCutTree
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_Johto_CutTree4_Done
	setflag FLAG_JOHTO_CUTTREE_LAKE_OF_RAGE_4
	setmetatile 6, 20, 514, 0
	setmetatile 7, 20, 514, 0
	setmetatile 6, 21, 514, 0
	setmetatile 7, 21, 591, 0
	special DrawWholeMapView
LakeOfRage_Johto_CutTree4_Done:
	releaseall
	end
