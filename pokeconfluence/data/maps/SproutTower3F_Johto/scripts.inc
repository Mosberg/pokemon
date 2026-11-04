SproutTower3F_Johto_MapScripts::
	.byte 0

SproutTower3F_Johto_SageLiScript_Entry::
	lockall
	goto SproutTower3F_Johto_SageLiScript

SproutTower3F_Johto_SproutTower3FPotion_Entry::
	lockall
	goto SproutTower3F_Johto_SproutTower3FPotion

SproutTower3F_Johto_SproutTower3FEscapeRope_Entry::
	lockall
	goto SproutTower3F_Johto_SproutTower3FEscapeRope

SproutTower3F_Johto_SproutTower3FStatue_Entry::
	lockall
	goto SproutTower3F_Johto_SproutTower3FStatue

SproutTower3F_Johto_SproutTower3FPainting_Entry::
	lockall
	goto SproutTower3F_Johto_SproutTower3FPainting

SproutTower3F_Johto_SproutTower3FRivalScene_Entry::
	lockall
	goto SproutTower3F_Johto_SproutTower3FRivalScene


SproutTower3F_Johto_SproutTower3FRivalScene:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	playse SE_M_TAIL_WHIP
	playse SE_PIN
	delay 15
	playse SE_M_TAIL_WHIP
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, SproutTower3F_Johto_SproutTower3FPlayerApproachesRivalMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 7, SproutTower3F_Johto_SproutTower3FRivalApproachesElderMovement
	waitmovement 7
	message SproutTower3F_Johto_SproutTowerElderLecturesRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, Johto_Movement_Emote_exclamation_mark
	waitmovement 7
	applymovement 7, Johto_Movement_Face_Down
	waitmovement 7
	delay 15
	applymovement 7, SproutTower3F_Johto_SproutTower3FRivalLeavesElderMovement
	waitmovement 7
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message SproutTower3F_Johto_SproutTowerRivalOnlyCareAboutStrongText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, Johto_Movement_Face_Up
	waitmovement 7
	message SproutTower3F_Johto_SproutTowerRivalUsedEscapeRopeText
	waitmessage
	delay 15
	closemessage
	playse SE_WARP_IN
	fadescreen FADE_TO_BLACK
	removeobject 7
	waitse
	fadescreen FADE_FROM_BLACK
	setvar VAR_JOHTO_SCENE_SPROUT_TOWER_3F, 1
	fadedefaultbgm
	releaseall
	end

SproutTower3F_Johto_SageLiScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HM05_FLASH, SproutTower3F_Johto_SageLiScript_GotFlash
	message SproutTower3F_Johto_SageLiSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_SAGE_LI, SproutTower3F_Johto_SageLiBeatenText
	message SproutTower3F_Johto_SageLiTakeThisFlashText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM_FLASH
	setflag FLAG_JOHTO_GOT_HM05_FLASH
	setflag FLAG_JOHTO_BEAT_SAGE_LI
	message SproutTower3F_Johto_SageLiFlashExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_SageLiScript_GotFlash:
	message SproutTower3F_Johto_SageLiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_TrainerSageJin::
	trainerbattle_single TRAINER_JOHTO_SAGE_JIN, SproutTower3F_Johto_SageJinSeenText, SproutTower3F_Johto_SageJinBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_JIN
	lock
	faceplayer
	goto SproutTower3F_Johto_TrainerSageJin_Script

SproutTower3F_Johto_TrainerSageJin_Script:
	message SproutTower3F_Johto_SageJinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_TrainerSageTroy::
	trainerbattle_single TRAINER_JOHTO_SAGE_TROY, SproutTower3F_Johto_SageTroySeenText, SproutTower3F_Johto_SageTroyBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_TROY
	lock
	faceplayer
	goto SproutTower3F_Johto_TrainerSageTroy_Script

SproutTower3F_Johto_TrainerSageTroy_Script:
	message SproutTower3F_Johto_SageTroyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_TrainerSageNeal::
	trainerbattle_single TRAINER_JOHTO_SAGE_NEAL, SproutTower3F_Johto_SageNealSeenText, SproutTower3F_Johto_SageNealBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_NEAL
	lock
	faceplayer
	goto SproutTower3F_Johto_TrainerSageNeal_Script

SproutTower3F_Johto_TrainerSageNeal_Script:
	message SproutTower3F_Johto_SageNealAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_SproutTower3FPainting:
	message SproutTower3F_Johto_SproutTower3FPaintingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_SproutTower3FStatue:
	message SproutTower3F_Johto_SproutTower3FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower3F_Johto_SproutTower3FPotion:
	finditem ITEM_POTION
	releaseall
	end

SproutTower3F_Johto_SproutTower3FEscapeRope:
	finditem ITEM_ESCAPE_ROPE
	releaseall
	end

SproutTower3F_Johto_SproutTower3FPlayerApproachesRivalMovement:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SproutTower3F_Johto_SproutTower3FRivalApproachesElderMovement:
	walk_up
	step_end

SproutTower3F_Johto_SproutTower3FRivalLeavesElderMovement:
	walk_right
	walk_down
	step_end

SproutTower3F_Johto_SproutTowerElderLecturesRivalText:
	.string "ELDER: You are in-\n"
	.string "deed skilled as a\l"
	.string "trainer."
	.string "\pAs promised, here\n"
	.string "is your HM."
	.string "\pBut let me say\n"
	.string "this: You should"
	.string "\ptreat your\n"
	.string "POKéMON better."
	.string "\pThe way you battle\n"
	.string "is far too harsh."
	.string "\pPOKéMON are not\n"
	.string "tools of war…$"

SproutTower3F_Johto_SproutTowerRivalOnlyCareAboutStrongText:
	.string "…\n"
	.string "…Humph!"
	.string "\pHe claims to be\n"
	.string "the ELDER but\l"
	.string "he's weak."
	.string "\pIt stands to\n"
	.string "reason."
	.string "\pI'd never lose to\n"
	.string "fools who babble"
	.string "\pabout being nice\n"
	.string "to POKéMON."
	.string "\pI only care about\n"
	.string "strong POKéMON\l"
	.string "that can win."
	.string "\pI really couldn't\n"
	.string "care less about\l"
	.string "weak POKéMON.$"

SproutTower3F_Johto_SproutTowerRivalUsedEscapeRopeText:
	.string "SILVER used an\n"
	.string "ESCAPE ROPE!$"

SproutTower3F_Johto_SageLiSeenText:
	.string "So good of you to\n"
	.string "come here!"
	.string "\pSPROUT TOWER is a\n"
	.string "place of training."
	.string "\pPeople and POKéMON\n"
	.string "test their bonds"
	.string "\pto build a bright\n"
	.string "future together."
	.string "\pI am the final\n"
	.string "test."
	.string "\pAllow me to check\n"
	.string "the ties between"
	.string "\pyour POKéMON and\n"
	.string "you!$"

SproutTower3F_Johto_SageLiBeatenText:
	.string "Ah, excellent!$"

SproutTower3F_Johto_SageLiTakeThisFlashText:
	.string "You and your POKé-\n"
	.string "MON should have"
	.string "\pno problem using\n"
	.string "this move."
	.string "\pTake this FLASH\n"
	.string "HM.$"

SproutTower3F_Johto_SageLiFlashExplanationText:
	.string "FLASH illuminates\n"
	.string "even the darkest\l"
	.string "of all places."
	.string "\pBut to use it out\n"
	.string "of battle, you"
	.string "\pneed the BADGE\n"
	.string "from VIOLET's GYM.$"

SproutTower3F_Johto_SageLiAfterBattleText:
	.string "I hope you learn\n"
	.string "and grow from your\l"
	.string "journey.$"

SproutTower3F_Johto_SageJinSeenText:
	.string "I train to find\n"
	.string "enlightenment in\l"
	.string "POKéMON!$"

SproutTower3F_Johto_SageJinBeatenText:
	.string "My training is\n"
	.string "incomplete…$"

SproutTower3F_Johto_SageJinAfterBattleText:
	.string "As POKéMON grow\n"
	.string "stronger, so does\l"
	.string "the trainer."
	.string "\pNo, wait. As the\n"
	.string "trainer grows"
	.string "\pstronger, so do\n"
	.string "the POKéMON.$"

SproutTower3F_Johto_SageTroySeenText:
	.string "Let me see how\n"
	.string "much you trust\l"
	.string "your POKéMON.$"

SproutTower3F_Johto_SageTroyBeatenText:
	.string "Yes, your trust is\n"
	.string "real!$"

SproutTower3F_Johto_SageTroyAfterBattleText:
	.string "It is not far to\n"
	.string "the ELDER.$"

SproutTower3F_Johto_SageNealSeenText:
	.string "The ELDER's HM\n"
	.string "lights even pitch-\l"
	.string "black darkness.$"

SproutTower3F_Johto_SageNealBeatenText:
	.string "It is my head that\n"
	.string "is bright!$"

SproutTower3F_Johto_SageNealAfterBattleText:
	.string "Let there be light\n"
	.string "on your journey.$"

SproutTower3F_Johto_SproutTower3FPaintingText:
	.string "It's a powerful\n"
	.string "painting of a\l"
	.string "BELLSPROUT.$"

SproutTower3F_Johto_SproutTower3FStatueText:
	.string "A POKéMON statue…"
	.string "\pIt looks very\n"
	.string "distinguished.$"
