GoldenrodGym_Johto_MapScripts::
	.byte 0

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_Entry::
	lockall
	goto GoldenrodGym_Johto_GoldenrodGymWhitneyScript

GoldenrodGym_Johto_GoldenrodGymGuideScript_Entry::
	lockall
	goto GoldenrodGym_Johto_GoldenrodGymGuideScript

GoldenrodGym_Johto_GoldenrodGymStatue_Entry::
	lockall
	goto GoldenrodGym_Johto_GoldenrodGymStatue

GoldenrodGym_Johto_WhitneyCriesScript_Entry::
	lockall
	goto GoldenrodGym_Johto_WhitneyCriesScript


GoldenrodGym_Johto_GoldenrodGymWhitneyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_WHITNEY, GoldenrodGym_Johto_GoldenrodGymWhitneyScript_FightDone
	message GoldenrodGym_Johto_WhitneyBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_WHITNEY_WHITNEY1, GoldenrodGym_Johto_WhitneyShouldntBeSoSeriousText
	setflag FLAG_JOHTO_BEAT_WHITNEY
	setflag FLAG_JOHTO_MADE_WHITNEY_CRY
	setvar VAR_JOHTO_SCENE_GOLDENROD_GYM, 1
	setflag FLAG_JOHTO_BEAT_BEAUTY_VICTORIA
	setflag FLAG_JOHTO_BEAT_BEAUTY_SAMANTHA
	setflag FLAG_JOHTO_BEAT_LASS_CARRIE
	setflag FLAG_JOHTO_BEAT_LASS_BRIDGET

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_FightDone:
	goto_if_unset FLAG_JOHTO_MADE_WHITNEY_CRY, GoldenrodGym_Johto_GoldenrodGymWhitneyScript_StoppedCrying
	message GoldenrodGym_Johto_WhitneyYouMeanieText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_StoppedCrying:
	goto_if_set FLAG_JOHTO_GOT_TM45_ATTRACT, GoldenrodGym_Johto_GoldenrodGymWhitneyScript_GotAttract
	goto_if_set FLAG_JOHTO_ENGINE_PLAINBADGE, GoldenrodGym_Johto_GoldenrodGymWhitneyScript_GotPlainBadge
	message GoldenrodGym_Johto_WhitneyWhatDoYouWantText
	waitmessage
	waitbuttonpress
	waitse
	message GoldenrodGym_Johto_PlayerReceivedPlainBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_PLAINBADGE
	special JohtoCountBadges
	call GoldenrodGym_Johto_GoldenrodGymActivateRockets_Sub

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_GotPlainBadge:
	message GoldenrodGym_Johto_WhitneyPlainBadgeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_ATTRACT
	goto_if_eq VAR_RESULT, 0, GoldenrodGym_Johto_GoldenrodGymWhitneyScript_NoRoomForAttract
	setflag FLAG_JOHTO_GOT_TM45_ATTRACT
	message GoldenrodGym_Johto_WhitneyAttractText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_GotAttract:
	message GoldenrodGym_Johto_WhitneyGoodCryText
	waitmessage
	waitbuttonpress

GoldenrodGym_Johto_GoldenrodGymWhitneyScript_NoRoomForAttract:
	closemessage
	releaseall
	end

GoldenrodGym_Johto_TrainerLassCarrie::
	trainerbattle_single TRAINER_JOHTO_LASS_CARRIE, GoldenrodGym_Johto_LassCarrieSeenText, GoldenrodGym_Johto_LassCarrieBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_CARRIE
	lock
	faceplayer
	goto GoldenrodGym_Johto_TrainerLassCarrie_Script

GoldenrodGym_Johto_TrainerLassCarrie_Script:
	message GoldenrodGym_Johto_LassCarrieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_WhitneyCriesScript:
	applymovement 3, Johto_Movement_Emote_exclamation_mark
	waitmovement 3
	applymovement 3, GoldenrodGym_Johto_BridgetWalksUpMovement
	waitmovement 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	message GoldenrodGym_Johto_BridgetWhitneyCriesText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, GoldenrodGym_Johto_BridgetWalksAwayMovement
	waitmovement 3
	setvar VAR_JOHTO_SCENE_GOLDENROD_GYM, 0
	clearflag FLAG_JOHTO_MADE_WHITNEY_CRY
	releaseall
	end

GoldenrodGym_Johto_TrainerLassBridget::
	trainerbattle_single TRAINER_JOHTO_LASS_BRIDGET, GoldenrodGym_Johto_LassBridgetSeenText, GoldenrodGym_Johto_LassBridgetBeatenText
	setflag FLAG_JOHTO_BEAT_LASS_BRIDGET
	lock
	faceplayer
	goto GoldenrodGym_Johto_TrainerLassBridget_Script

GoldenrodGym_Johto_TrainerLassBridget_Script:
	message GoldenrodGym_Johto_LassBridgetAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_TrainerBeautyVictoria::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_VICTORIA, GoldenrodGym_Johto_BeautyVictoriaSeenText, GoldenrodGym_Johto_BeautyVictoriaBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_VICTORIA
	lock
	faceplayer
	goto GoldenrodGym_Johto_TrainerBeautyVictoria_Script

GoldenrodGym_Johto_TrainerBeautyVictoria_Script:
	message GoldenrodGym_Johto_BeautyVictoriaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_TrainerBeautySamantha::
	trainerbattle_single TRAINER_JOHTO_BEAUTY_SAMANTHA, GoldenrodGym_Johto_BeautySamanthaSeenText, GoldenrodGym_Johto_BeautySamanthaBeatenText
	setflag FLAG_JOHTO_BEAT_BEAUTY_SAMANTHA
	lock
	faceplayer
	goto GoldenrodGym_Johto_TrainerBeautySamantha_Script

GoldenrodGym_Johto_TrainerBeautySamantha_Script:
	message GoldenrodGym_Johto_BeautySamanthaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_GoldenrodGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_WHITNEY, GoldenrodGym_Johto_GoldenrodGymGuideScript_GoldenrodGymGuideWinScript
	message GoldenrodGym_Johto_GoldenrodGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_GoldenrodGymGuideScript_GoldenrodGymGuideWinScript:
	message GoldenrodGym_Johto_GoldenrodGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodGym_Johto_GoldenrodGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_PLAINBADGE, GoldenrodGym_Johto_GoldenrodGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

GoldenrodGym_Johto_GoldenrodGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

GoldenrodGym_Johto_GoldenrodGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, GoldenrodGym_Johto_GoldenrodGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, GoldenrodGym_Johto_GoldenrodGymActivateRockets_GoldenrodRockets_Sub
	return

GoldenrodGym_Johto_GoldenrodGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

GoldenrodGym_Johto_GoldenrodGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

GoldenrodGym_Johto_BridgetWalksUpMovement:
	walk_left
	face_up
	step_end

GoldenrodGym_Johto_BridgetWalksAwayMovement:
	walk_right
	face_left
	step_end

GoldenrodGym_Johto_WhitneyBeforeText:
	.string "Hi! I'm WHITNEY!"
	.string "\pEveryone was into\n"
	.string "POKéMON, so I got\l"
	.string "into it too!"
	.string "\pPOKéMON are\n"
	.string "super-cute!"
	.string "\pYou want to bat-\n"
	.string "tle? I'm warning\l"
	.string "you--I'm good!$"

GoldenrodGym_Johto_WhitneyShouldntBeSoSeriousText:
	.string "Sob…"
	.string "\p…Waaaaaaah!\n"
	.string "You're mean!"
	.string "\pYou shouldn't be\n"
	.string "so serious! You…\l"
	.string "you child, you!$"

GoldenrodGym_Johto_WhitneyYouMeanieText:
	.string "Waaaaah!"
	.string "\pWaaaaah!"
	.string "\p…Snivel, hic…\n"
	.string "…You meanie!$"

GoldenrodGym_Johto_WhitneyWhatDoYouWantText:
	.string "…Sniff…"
	.string "\pWhat? What do you\n"
	.string "want? A BADGE?"
	.string "\pOh, right.\n"
	.string "I forgot. Here's\l"
	.string "PLAINBADGE.$"

GoldenrodGym_Johto_PlayerReceivedPlainBadgeText:
	.string "{PLAYER} received\n"
	.string "PLAINBADGE.$"

GoldenrodGym_Johto_WhitneyPlainBadgeText:
	.string "PLAINBADGE lets\n"
	.string "your POKéMON use"
	.string "\pSTRENGTH outside\n"
	.string "of battle."
	.string "\pIt also boosts\n"
	.string "your POKéMON's\l"
	.string "SPEED."
	.string "\pOh, you can have\n"
	.string "this too!$"

GoldenrodGym_Johto_WhitneyAttractText:
	.string "It's ATTRACT!\n"
	.string "It makes full use"
	.string "\pof a POKéMON's\n"
	.string "charm."
	.string "\pIsn't it just per-\n"
	.string "fect for a cutie\l"
	.string "like me?$"

GoldenrodGym_Johto_WhitneyGoodCryText:
	.string "Ah, that was a\n"
	.string "good cry!"
	.string "\pCome for a visit\n"
	.string "again! Bye-bye!$"

GoldenrodGym_Johto_LassCarrieSeenText:
	.string "Don't let my\n"
	.string "POKéMON's cute"
	.string "\plooks fool you.\n"
	.string "They can whip you!$"

GoldenrodGym_Johto_LassCarrieBeatenText:
	.string "Darn… I thought\n"
	.string "you were weak…$"

GoldenrodGym_Johto_LassCarrieAfterBattleText:
	.string "Do my POKéMON\n"
	.string "think I'm cute?$"

GoldenrodGym_Johto_LassBridgetSeenText:
	.string "I like cute POKé-\n"
	.string "MON better than\l"
	.string "strong POKéMON."
	.string "\pBut I have strong\n"
	.string "and cute POKéMON!$"

GoldenrodGym_Johto_LassBridgetBeatenText:
	.string "Oh, no, no, no!$"

GoldenrodGym_Johto_LassBridgetAfterBattleText:
	.string "I'm trying to beat\n"
	.string "WHITNEY, but…\l"
	.string "It's depressing."
	.string "\pI'm okay! If I\n"
	.string "lose, I'll just"
	.string "\ptry harder next\n"
	.string "time!$"

GoldenrodGym_Johto_BridgetWhitneyCriesText:
	.string "Oh, no. You made\n"
	.string "WHITNEY cry."
	.string "\pIt's OK. She'll\n"
	.string "stop soon. She"
	.string "\palways cries when\n"
	.string "she loses.$"

GoldenrodGym_Johto_BeautyVictoriaSeenText:
	.string "Oh, you are a cute\n"
	.string "little trainer! "
	.string "\pI like you, but I\n"
	.string "won't hold back!$"

GoldenrodGym_Johto_BeautyVictoriaBeatenText:
	.string "Let's see… Oops,\n"
	.string "it's over?$"

GoldenrodGym_Johto_BeautyVictoriaAfterBattleText:
	.string "Wow, you must be\n"
	.string "good to beat me!\l"
	.string "Keep it up!$"

GoldenrodGym_Johto_BeautySamanthaSeenText:
	.string "Give it your best\n"
	.string "shot, or I'll take\l"
	.string "you down!$"

GoldenrodGym_Johto_BeautySamanthaBeatenText:
	.string "No! Oh, MEOWTH,\n"
	.string "I'm so sorry!$"

GoldenrodGym_Johto_BeautySamanthaAfterBattleText:
	.string "I taught MEOWTH\n"
	.string "moves for taking\l"
	.string "on any type…$"

GoldenrodGym_Johto_GoldenrodGymGuideText:
	.string "Yo! CHAMP in\n"
	.string "making!"
	.string "\pThis GYM is home\n"
	.string "to normal-type\l"
	.string "POKéMON trainers."
	.string "\pI recommend you\n"
	.string "use fighting-type\l"
	.string "POKéMON.$"

GoldenrodGym_Johto_GoldenrodGymGuideWinText:
	.string "You won? Great! I\n"
	.string "was busy admiring\l"
	.string "the ladies here.$"
