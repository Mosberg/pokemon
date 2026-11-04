CeladonGym_Johto_MapScripts::
	.byte 0

CeladonGym_Johto_CeladonGymErikaScript_Entry::
	lockall
	goto CeladonGym_Johto_CeladonGymErikaScript

CeladonGym_Johto_CeladonGymStatue_Entry::
	lockall
	goto CeladonGym_Johto_CeladonGymStatue


CeladonGym_Johto_CeladonGymErikaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_RAINBOWBADGE, CeladonGym_Johto_CeladonGymErikaScript_FightDone
	message CeladonGym_Johto_ErikaBeforeBattleText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_ERIKA_ERIKA1, CeladonGym_Johto_ErikaBeatenText
	setflag FLAG_JOHTO_BEAT_ERIKA
	setflag FLAG_JOHTO_BEAT_LASS_MICHELLE
	setflag FLAG_JOHTO_BEAT_PICNICKER_TANYA
	setflag FLAG_JOHTO_BEAT_BEAUTY_JULIA
	setflag FLAG_JOHTO_BEAT_TWINS_JO_AND_ZOE
	message CeladonGym_Johto_PlayerReceivedRainbowBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_RAINBOWBADGE

CeladonGym_Johto_CeladonGymErikaScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM19_GIGA_DRAIN, CeladonGym_Johto_CeladonGymErikaScript_GotGigaDrain
	message CeladonGym_Johto_ErikaExplainTMText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_GIGA_DRAIN
	goto_if_eq VAR_RESULT, 0, CeladonGym_Johto_CeladonGymErikaScript_GotGigaDrain
	setflag FLAG_JOHTO_GOT_TM19_GIGA_DRAIN

CeladonGym_Johto_CeladonGymErikaScript_GotGigaDrain:
	message CeladonGym_Johto_ErikaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_TrainerLassMichelle::
	trainerbattle_single TRAINER_JOHTO_LASS_MICHELLE, CeladonGym_Johto_LassMichelleSeenText, CeladonGym_Johto_LassMichelleBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_MICHELLE
	lock
	faceplayer
	goto CeladonGym_Johto_TrainerLassMichelle_Script

CeladonGym_Johto_TrainerLassMichelle_Script:
	message CeladonGym_Johto_LassMichelleAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_TrainerPicnickerTanya::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_TANYA, CeladonGym_Johto_PicnickerTanyaSeenText, CeladonGym_Johto_PicnickerTanyaBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_TANYA
	lock
	faceplayer
	goto CeladonGym_Johto_TrainerPicnickerTanya_Script

CeladonGym_Johto_TrainerPicnickerTanya_Script:
	message CeladonGym_Johto_PicnickerTanyaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_TrainerBeautyJulia::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_JULIA, CeladonGym_Johto_BeautyJuliaSeenText, CeladonGym_Johto_BeautyJuliaBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_JULIA
	lock
	faceplayer
	goto CeladonGym_Johto_TrainerBeautyJulia_Script

CeladonGym_Johto_TrainerBeautyJulia_Script:
	message CeladonGym_Johto_BeautyJuliaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_TrainerTwinsJoAndZoe1::
	trainerbattle_single TRAINER_JOHTO_TWINS_JOANDZOE1, CeladonGym_Johto_TwinsJoAndZoe1SeenText, CeladonGym_Johto_TwinsJoAndZoe1BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_JO_AND_ZOE
	lock
	faceplayer
	goto CeladonGym_Johto_TrainerTwinsJoAndZoe1_Script

CeladonGym_Johto_TrainerTwinsJoAndZoe1_Script:
	message CeladonGym_Johto_TwinsJoAndZoe1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_TrainerTwinsJoAndZoe2::
	trainerbattle_single TRAINER_JOHTO_TWINS_JOANDZOE2, CeladonGym_Johto_TwinsJoAndZoe2SeenText, CeladonGym_Johto_TwinsJoAndZoe2BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_JO_AND_ZOE
	lock
	faceplayer
	goto CeladonGym_Johto_TrainerTwinsJoAndZoe2_Script

CeladonGym_Johto_TrainerTwinsJoAndZoe2_Script:
	message CeladonGym_Johto_TwinsJoAndZoe2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonGym_Johto_CeladonGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_RAINBOWBADGE, CeladonGym_Johto_CeladonGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

CeladonGym_Johto_CeladonGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

CeladonGym_Johto_ErikaBeforeBattleText:
	.string "ERIKA: Hello…\n"
	.string "Lovely weather,"
	.string "\pisn't it?\n"
	.string "It's so pleasant…"
	.string "\p…I'm afraid I may\n"
	.string "doze off…"
	.string "\pMy name is ERIKA.\n"
	.string "I am the LEADER of\l"
	.string "CELADON GYM."
	.string "\p…Oh? All the way\n"
	.string "from JOHTO, you\l"
	.string "say? How nice…"
	.string "\pOh. I'm sorry, I\n"
	.string "didn't realize"
	.string "\pthat you wished to\n"
	.string "challenge me."
	.string "\pVery well, but I\n"
	.string "shall not lose.$"

CeladonGym_Johto_ErikaBeatenText:
	.string "ERIKA: Oh!\n"
	.string "I concede defeat…"
	.string "\pYou are remarkably\n"
	.string "strong…"
	.string "\pI shall give you\n"
	.string "RAINBOWBADGE…$"

CeladonGym_Johto_PlayerReceivedRainbowBadgeText:
	.string "{PLAYER} received\n"
	.string "RAINBOWBADGE.$"

CeladonGym_Johto_ErikaExplainTMText:
	.string "ERIKA: That was a\n"
	.string "delightful match."
	.string "\pI felt inspired.\n"
	.string "Please, I wish you\l"
	.string "to have this TM."
	.string "\pIt is GIGA DRAIN."
	.string "\pIt is a wonderful\n"
	.string "move that drains"
	.string "\phalf the damage it\n"
	.string "inflicts to heal\l"
	.string "your POKéMON."
	.string "\pPlease use it if\n"
	.string "it pleases you…$"

CeladonGym_Johto_ErikaAfterBattleText:
	.string "ERIKA: Losing\n"
	.string "leaves a bitter\l"
	.string "aftertaste…"
	.string "\pBut knowing that\n"
	.string "there are strong"
	.string "\ptrainers spurs me\n"
	.string "to do better…$"

CeladonGym_Johto_LassMichelleSeenText:
	.string "Do you think a\n"
	.string "girls-only GYM\l"
	.string "is rare?$"

CeladonGym_Johto_LassMichelleBeatenText:
	.string "Oh, bleah!$"

CeladonGym_Johto_LassMichelleAfterBattleText:
	.string "I just got care-\n"
	.string "less, that's all!$"

CeladonGym_Johto_PicnickerTanyaSeenText:
	.string "Oh, a battle?\n"
	.string "That's kind of\l"
	.string "scary, but OK!$"

CeladonGym_Johto_PicnickerTanyaBeatenText:
	.string "Oh, that's it?$"

CeladonGym_Johto_PicnickerTanyaAfterBattleText:
	.string "Oh, look at all\n"
	.string "your BADGES. No"
	.string "\pwonder I couldn't\n"
	.string "win!$"

CeladonGym_Johto_BeautyJuliaSeenText:
	.string "Were you looking\n"
	.string "at these flowers\l"
	.string "or at me?$"

CeladonGym_Johto_BeautyJuliaBeatenText:
	.string "How annoying!$"

CeladonGym_Johto_BeautyJuliaAfterBattleText:
	.string "How do I go about\n"
	.string "becoming ladylike\l"
	.string "like ERIKA?$"

CeladonGym_Johto_TwinsJoAndZoe1SeenText:
	.string "We'll show you\n"
	.string "POKéMON moves that\l"
	.string "ERIKA taught us!$"

CeladonGym_Johto_TwinsJoAndZoe1BeatenText:
	.string "Oh… We lost…$"

CeladonGym_Johto_TwinsJoAndZoe1AfterBattleText:
	.string "ERIKA will get you\n"
	.string "back for us!$"

CeladonGym_Johto_TwinsJoAndZoe2SeenText:
	.string "We're going to\n"
	.string "protect ERIKA!$"

CeladonGym_Johto_TwinsJoAndZoe2BeatenText:
	.string "We couldn't win…$"

CeladonGym_Johto_TwinsJoAndZoe2AfterBattleText:
	.string "ERIKA is much,\n"
	.string "much stronger!$"
