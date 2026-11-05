MahoganyGym_Johto_MapScripts::
	.byte 0

MahoganyGym_Johto_MahoganyGymPryceScript_Entry::
	lockall
	goto MahoganyGym_Johto_MahoganyGymPryceScript

MahoganyGym_Johto_MahoganyGymGuideScript_Entry::
	lockall
	goto MahoganyGym_Johto_MahoganyGymGuideScript

MahoganyGym_Johto_MahoganyGymStatue_Entry::
	lockall
	goto MahoganyGym_Johto_MahoganyGymStatue


MahoganyGym_Johto_MahoganyGymPryceScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_PRYCE, MahoganyGym_Johto_MahoganyGymPryceScript_FightDone
	message MahoganyGym_Johto_PryceText_Intro
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_PRYCE_PRYCE1, MahoganyGym_Johto_PryceText_Impressed
	setflag FLAG_JOHTO_BEAT_PRYCE
	message MahoganyGym_Johto_Text_ReceivedGlacierBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_GLACIERBADGE
	special JohtoCountBadges
	call MahoganyGym_Johto_MahoganyGymActivateRockets_Sub

MahoganyGym_Johto_MahoganyGymPryceScript_FightDone:
	goto_if_set FLAG_JOHTO_GOT_TM16_ICY_WIND, MahoganyGym_Johto_PryceScript_Defeat
	setflag FLAG_JOHTO_BEAT_SKIER_ROXANNE
	setflag FLAG_JOHTO_BEAT_SKIER_CLARISSA
	setflag FLAG_JOHTO_BEAT_BOARDER_RONALD
	setflag FLAG_JOHTO_BEAT_BOARDER_BRAD
	setflag FLAG_JOHTO_BEAT_BOARDER_DOUGLAS
	message MahoganyGym_Johto_PryceText_GlacierBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_HAIL
	goto_if_eq VAR_RESULT, 0, MahoganyGym_Johto_MahoganyGym_NoRoomForIcyWind
	setflag FLAG_JOHTO_GOT_TM16_ICY_WIND
	message MahoganyGym_Johto_PryceText_IcyWindSpeech
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_PryceScript_Defeat:
	message MahoganyGym_Johto_PryceText_CherishYourPokemon
	waitmessage
	waitbuttonpress

MahoganyGym_Johto_MahoganyGym_NoRoomForIcyWind:
	closemessage
	releaseall
	end

MahoganyGym_Johto_TrainerSkierRoxanne::
	trainerbattle_single TRAINER_JOHTO_SKIER_ROXANNE, MahoganyGym_Johto_SkierRoxanneSeenText, MahoganyGym_Johto_SkierRoxanneBeatenText
	setflag FLAG_JOHTO_BEAT_SKIER_ROXANNE
	lock
	faceplayer
	goto MahoganyGym_Johto_TrainerSkierRoxanne_Script

MahoganyGym_Johto_TrainerSkierRoxanne_Script:
	message MahoganyGym_Johto_SkierRoxanneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_TrainerSkierClarissa::
	trainerbattle_single TRAINER_JOHTO_SKIER_CLARISSA, MahoganyGym_Johto_SkierClarissaSeenText, MahoganyGym_Johto_SkierClarissaBeatenText
	setflag FLAG_JOHTO_BEAT_SKIER_CLARISSA
	lock
	faceplayer
	goto MahoganyGym_Johto_TrainerSkierClarissa_Script

MahoganyGym_Johto_TrainerSkierClarissa_Script:
	message MahoganyGym_Johto_SkierClarissaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_TrainerBoarderRonald::
	trainerbattle_single TRAINER_JOHTO_BOARDER_RONALD, MahoganyGym_Johto_BoarderRonaldSeenText, MahoganyGym_Johto_BoarderRonaldBeatenText
	setflag FLAG_JOHTO_BEAT_BOARDER_RONALD
	lock
	faceplayer
	goto MahoganyGym_Johto_TrainerBoarderRonald_Script

MahoganyGym_Johto_TrainerBoarderRonald_Script:
	message MahoganyGym_Johto_BoarderRonaldAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_TrainerBoarderBrad::
	trainerbattle_single TRAINER_JOHTO_BOARDER_BRAD, MahoganyGym_Johto_BoarderBradSeenText, MahoganyGym_Johto_BoarderBradBeatenText
	setflag FLAG_JOHTO_BEAT_BOARDER_BRAD
	lock
	faceplayer
	goto MahoganyGym_Johto_TrainerBoarderBrad_Script

MahoganyGym_Johto_TrainerBoarderBrad_Script:
	message MahoganyGym_Johto_BoarderBradAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_TrainerBoarderDouglas::
	trainerbattle_single TRAINER_JOHTO_BOARDER_DOUGLAS, MahoganyGym_Johto_BoarderDouglasSeenText, MahoganyGym_Johto_BoarderDouglasBeatenText
	setflag FLAG_JOHTO_BEAT_BOARDER_DOUGLAS
	lock
	faceplayer
	goto MahoganyGym_Johto_TrainerBoarderDouglas_Script

MahoganyGym_Johto_TrainerBoarderDouglas_Script:
	message MahoganyGym_Johto_BoarderDouglasAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_MahoganyGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_PRYCE, MahoganyGym_Johto_MahoganyGymGuideScript_MahoganyGymGuideWinScript
	message MahoganyGym_Johto_MahoganyGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_MahoganyGymGuideScript_MahoganyGymGuideWinScript:
	message MahoganyGym_Johto_MahoganyGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyGym_Johto_MahoganyGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_GLACIERBADGE, MahoganyGym_Johto_MahoganyGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

MahoganyGym_Johto_MahoganyGymStatue_Beaten:
	buffertrainername STR_VAR_2, TRAINER_JOHTO_PRYCE_PRYCE1
	goto Johto_Std_GymStatue2Script

MahoganyGym_Johto_MahoganyGymActivateRockets_Sub:
	goto_if_eq VAR_RESULT, 7, MahoganyGym_Johto_MahoganyGymActivateRockets_RadioTowerRockets_Sub
	goto_if_eq VAR_RESULT, 6, MahoganyGym_Johto_MahoganyGymActivateRockets_GoldenrodRockets_Sub
	return

MahoganyGym_Johto_MahoganyGymActivateRockets_GoldenrodRockets_Sub:
	goto Johto_Std_GoldenrodRocketsScript_Sub

MahoganyGym_Johto_MahoganyGymActivateRockets_RadioTowerRockets_Sub:
	goto Johto_Std_RadioTowerRocketsScript_Sub

MahoganyGym_Johto_PryceText_Intro:
	.string "POKéMON have many\n"
	.string "experiences in"
	.string "\ptheir lives, just \n"
	.string "like we do. "
	.string "\pI, too, have seen\n"
	.string "and suffered much\l"
	.string "in my life."
	.string "\pSince I am your\n"
	.string "elder, let me show\l"
	.string "you what I mean."
	.string "\pI have been with\n"
	.string "POKéMON since"
	.string "\pbefore you were\n"
	.string "born."
	.string "\pI do not lose\n"
	.string "easily."
	.string "\pI, PRYCE--the\n"
	.string "winter trainer--"
	.string "\pshall demonstrate\n"
	.string "my power!$"

MahoganyGym_Johto_PryceText_Impressed:
	.string "Ah, I am impressed\n"
	.string "by your prowess."
	.string "\pWith your strong\n"
	.string "will, I know you"
	.string "\pwill overcome all\n"
	.string "life's obstacles."
	.string "\pYou are worthy of\n"
	.string "this BADGE!$"

MahoganyGym_Johto_Text_ReceivedGlacierBadge:
	.string "{PLAYER} received\n"
	.string "GLACIERBADGE.$"

MahoganyGym_Johto_PryceText_GlacierBadgeSpeech:
	.string "That BADGE will\n"
	.string "raise the SPECIAL\l"
	.string "stats of POKéMON."
	.string "\pIt also lets your\n"
	.string "POKéMON use WHIRL-\l"
	.string "POOL to get across\l"
	.string "real whirlpools."
	.string "\pAnd this… This is\n"
	.string "a gift from me!$"

MahoganyGym_Johto_PryceText_IcyWindSpeech:
	.string "That TM contains\n"
	.string "ICY WIND."
	.string "\pIt inflicts damage\n"
	.string "and lowers speed."
	.string "\pIt demonstrates\n"
	.string "the harshness of\l"
	.string "winter.$"

MahoganyGym_Johto_PryceText_CherishYourPokemon:
	.string "When the ice and\n"
	.string "snow melt, spring\l"
	.string "arrives."
	.string "\pYou and your POKé-\n"
	.string "MON will be to-"
	.string "\pgether for many\n"
	.string "years to come."
	.string "\pCherish your time\n"
	.string "together!$"

MahoganyGym_Johto_BoarderRonaldSeenText:
	.string "I'll freeze your\n"
	.string "POKéMON, so you\l"
	.string "can't do a thing!$"

MahoganyGym_Johto_BoarderRonaldBeatenText:
	.string "Darn. I couldn't\n"
	.string "do a thing.$"

MahoganyGym_Johto_BoarderRonaldAfterBattleText:
	.string "I think there's a\n"
	.string "move a POKéMON"
	.string "\pcan use while it's\n"
	.string "frozen.$"

MahoganyGym_Johto_BoarderBradSeenText:
	.string "This GYM has a\n"
	.string "slippery floor."
	.string "\pIt's fun, isn't\n"
	.string "it?"
	.string "\pBut hey--we're\n"
	.string "not playing games\l"
	.string "here!$"

MahoganyGym_Johto_BoarderBradBeatenText:
	.string "Do you see how\n"
	.string "serious we are?$"

MahoganyGym_Johto_BoarderBradAfterBattleText:
	.string "This GYM is great.\n"
	.string "I love boarding\l"
	.string "with my POKéMON!$"

MahoganyGym_Johto_BoarderDouglasSeenText:
	.string "I know PRYCE's\n"
	.string "secret.$"

MahoganyGym_Johto_BoarderDouglasBeatenText:
	.string "OK. I'll tell you\n"
	.string "PRYCE's secret.$"

MahoganyGym_Johto_BoarderDouglasAfterBattleText:
	.string "The secret behind\n"
	.string "PRYCE's power…"
	.string "\pHe meditates under\n"
	.string "a waterfall daily"
	.string "\pto strengthen his\n"
	.string "mind and body.$"

MahoganyGym_Johto_SkierRoxanneSeenText:
	.string "To get to PRYCE,\n"
	.string "our GYM LEADER,"
	.string "\pyou need to think\n"
	.string "before you skate.$"

MahoganyGym_Johto_SkierRoxanneBeatenText:
	.string "I wouldn't lose to\n"
	.string "you in skiing!$"

MahoganyGym_Johto_SkierRoxanneAfterBattleText:
	.string "If you don't skate\n"
	.string "with precision,"
	.string "\pyou won't get far\n"
	.string "in this GYM.$"

MahoganyGym_Johto_SkierClarissaSeenText:
	.string "Check out my\n"
	.string "parallel turn!$"

MahoganyGym_Johto_SkierClarissaBeatenText:
	.string "No! You made me\n"
	.string "wipe out!$"

MahoganyGym_Johto_SkierClarissaAfterBattleText:
	.string "I shouldn't have\n"
	.string "been bragging\l"
	.string "about my skiing…$"

MahoganyGym_Johto_MahoganyGymGuideText:
	.string "PRYCE is a veteran\n"
	.string "who has trained"
	.string "\pPOKéMON for some\n"
	.string "50 years."
	.string "\pHe's said to be\n"
	.string "good at freezing"
	.string "\popponents with\n"
	.string "ice-type moves."
	.string "\pThat means you\n"
	.string "should melt him"
	.string "\pwith your burning\n"
	.string "ambition!$"

MahoganyGym_Johto_MahoganyGymGuideWinText:
	.string "PRYCE is some-\n"
	.string "thing, but you're\l"
	.string "something else!"
	.string "\pThat was a hot\n"
	.string "battle that"
	.string "\pbridged the gen-\n"
	.string "eration gap!$"
