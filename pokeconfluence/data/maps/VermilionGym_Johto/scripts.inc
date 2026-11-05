VermilionGym_Johto_MapScripts::
	.byte 0

VermilionGym_Johto_VermilionGymSurgeScript_Entry::
	lockall
	goto VermilionGym_Johto_VermilionGymSurgeScript

VermilionGym_Johto_VermilionGymGuideScript_Entry::
	lockall
	goto VermilionGym_Johto_VermilionGymGuideScript

VermilionGym_Johto_VermilionGymTrashCan_Entry::
	lockall
	goto VermilionGym_Johto_VermilionGymTrashCan

VermilionGym_Johto_VermilionGymStatue_Entry::
	lockall
	goto VermilionGym_Johto_VermilionGymStatue


VermilionGym_Johto_VermilionGymSurgeScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_THUNDERBADGE, VermilionGym_Johto_VermilionGymSurgeScript_FightDone
	message VermilionGym_Johto_LtSurgeIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_LT_SURGE_LT_SURGE1, VermilionGym_Johto_LtSurgeWinLossText
	setflag FLAG_JOHTO_BEAT_LTSURGE
	setflag FLAG_JOHTO_BEAT_GENTLEMAN_GREGORY
	setflag FLAG_JOHTO_BEAT_GUITARIST_VINCENT
	setflag FLAG_JOHTO_BEAT_JUGGLER_HORTON
	message VermilionGym_Johto_ReceivedThunderBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_THUNDERBADGE
	message VermilionGym_Johto_LtSurgeThunderBadgeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_VermilionGymSurgeScript_FightDone:
	message VermilionGym_Johto_LtSurgeFightDoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_TrainerGentlemanGregory::
	trainerbattle_single TRAINER_JOHTO_GENTLEMAN_GREGORY, VermilionGym_Johto_GentlemanGregorySeenText, VermilionGym_Johto_GentlemanGregoryBeatenText
	setflag FLAG_JOHTO_BEAT_GENTLEMAN_GREGORY
	lock
	faceplayer
	goto VermilionGym_Johto_TrainerGentlemanGregory_Script

VermilionGym_Johto_TrainerGentlemanGregory_Script:
	message VermilionGym_Johto_GentlemanGregoryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_TrainerGuitaristVincent::
	trainerbattle_single TRAINER_JOHTO_GUITARIST_VINCENT, VermilionGym_Johto_GuitaristVincentSeenText, VermilionGym_Johto_GuitaristVincentBeatenText
	setflag FLAG_JOHTO_BEAT_GUITARIST_VINCENT
	lock
	faceplayer
	goto VermilionGym_Johto_TrainerGuitaristVincent_Script

VermilionGym_Johto_TrainerGuitaristVincent_Script:
	message VermilionGym_Johto_GuitaristVincentAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_TrainerJugglerHorton::
	trainerbattle_single TRAINER_JOHTO_JUGGLER_HORTON, VermilionGym_Johto_JugglerHortonSeenText, VermilionGym_Johto_JugglerHortonBeatenText
	setflag FLAG_JOHTO_BEAT_JUGGLER_HORTON
	lock
	faceplayer
	goto VermilionGym_Johto_TrainerJugglerHorton_Script

VermilionGym_Johto_TrainerJugglerHorton_Script:
	message VermilionGym_Johto_JugglerHortonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_VermilionGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_LTSURGE, VermilionGym_Johto_VermilionGymGuideScript_VermilionGymGuideWinScript
	message VermilionGym_Johto_VermilionGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_VermilionGymGuideScript_VermilionGymGuideWinScript:
	message VermilionGym_Johto_VermilionGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_VermilionGymTrashCan:
	message VermilionGym_Johto_VermilionGymTrashCanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionGym_Johto_VermilionGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_THUNDERBADGE, VermilionGym_Johto_VermilionGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

VermilionGym_Johto_VermilionGymStatue_Beaten:
	buffertrainername STR_VAR_2, TRAINER_JOHTO_LT_SURGE_LT_SURGE1
	goto Johto_Std_GymStatue2Script

VermilionGym_Johto_LtSurgeIntroText:
	.string "SURGE: Hey, you\n"
	.string "little tyke!"
	.string "\pI have to hand it\n"
	.string "to you. It may not"
	.string "\pbe very smart to\n"
	.string "challenge me, but\l"
	.string "it takes guts!"
	.string "\pWhen it comes to\n"
	.string "electric POKéMON,\l"
	.string "I'm number one!"
	.string "\pI've never lost on\n"
	.string "the battlefield."
	.string "\pI'll zap you just\n"
	.string "like I did my\l"
	.string "enemies in war!$"

VermilionGym_Johto_LtSurgeWinLossText:
	.string "SURGE: Arrrgh!\n"
	.string "You are strong!"
	.string "\pOK, kid. You get\n"
	.string "THUNDERBADGE!$"

VermilionGym_Johto_ReceivedThunderBadgeText:
	.string "{PLAYER} received\n"
	.string "THUNDERBADGE.$"

VermilionGym_Johto_LtSurgeThunderBadgeText:
	.string "SURGE: THUNDER-\n"
	.string "BADGE increases\l"
	.string "POKéMON's speed. "
	.string "\pConsider it proof\n"
	.string "that you defeated"
	.string "\pme. You wear it\n"
	.string "proudly, hear?$"

VermilionGym_Johto_LtSurgeFightDoneText:
	.string "SURGE: Hey, kid!\n"
	.string "Still slugging and\l"
	.string "chugging away?"
	.string "\pMy POKéMON and I\n"
	.string "are still at it!$"

VermilionGym_Johto_GentlemanGregorySeenText:
	.string "You're here to\n"
	.string "defeat LT.SURGE?"
	.string "\pNot if I can help\n"
	.string "it!$"

VermilionGym_Johto_GentlemanGregoryBeatenText:
	.string "Sorry I failed\n"
	.string "you, LT.SURGE,\l"
	.string "sir!$"

VermilionGym_Johto_GentlemanGregoryAfterBattleText:
	.string "When I was still\n"
	.string "in the army, LT."
	.string "\pSURGE saved my\n"
	.string "life.$"

VermilionGym_Johto_GuitaristVincentSeenText:
	.string "LT.SURGE recog-\n"
	.string "nized my potential"
	.string "\pwith electric\n"
	.string "POKéMON."
	.string "\pThink you can beat\n"
	.string "me?$"

VermilionGym_Johto_GuitaristVincentBeatenText:
	.string "Ooh, how shocking!$"

VermilionGym_Johto_GuitaristVincentAfterBattleText:
	.string "If the GYM's traps\n"
	.string "were working, you"
	.string "\pwould have been\n"
	.string "toast…$"

VermilionGym_Johto_JugglerHortonSeenText:
	.string "I'm going to take\n"
	.string "you down! Prepare\l"
	.string "to be shocked!$"

VermilionGym_Johto_JugglerHortonBeatenText:
	.string "Gwaaah!\n"
	.string "I was overpowered…$"

VermilionGym_Johto_JugglerHortonAfterBattleText:
	.string "Don't get too com-\n"
	.string "fortable about"
	.string "\pbeating me…\n"
	.string "LT.SURGE is tough.$"

VermilionGym_Johto_VermilionGymGuideText:
	.string "Yo! CHAMP in\n"
	.string "making!"
	.string "\pYou lucked out\n"
	.string "this time."
	.string "\pLT.SURGE is very\n"
	.string "cautious. He has"
	.string "\ptraps set all over\n"
	.string "the GYM."
	.string "\pBut--he-heh--the\n"
	.string "traps aren't\l"
	.string "active right now."
	.string "\pYou'll have no\n"
	.string "problem getting to\l"
	.string "LT.SURGE.$"

VermilionGym_Johto_VermilionGymGuideWinText:
	.string "Whew! That was an\n"
	.string "electrifying bout!"
	.string "\pIt sure made me\n"
	.string "nervous.$"

VermilionGym_Johto_VermilionGymTrashCanText:
	.string "Nope! Nothing here\n"
	.string "but trash.$"
