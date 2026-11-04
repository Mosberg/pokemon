SaffronGym_Johto_MapScripts::
	.byte 0

SaffronGym_Johto_SaffronGymSabrinaScript_Entry::
	lockall
	goto SaffronGym_Johto_SaffronGymSabrinaScript

SaffronGym_Johto_SaffronGymGuideScript_Entry::
	lockall
	goto SaffronGym_Johto_SaffronGymGuideScript

SaffronGym_Johto_SaffronGymStatue_Entry::
	lockall
	goto SaffronGym_Johto_SaffronGymStatue


SaffronGym_Johto_SaffronGymSabrinaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENGINE_MARSHBADGE, SaffronGym_Johto_SaffronGymSabrinaScript_FightDone
	message SaffronGym_Johto_SabrinaIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_SABRINA_SABRINA1, SaffronGym_Johto_SabrinaWinLossText
	setflag FLAG_JOHTO_BEAT_SABRINA
	setflag FLAG_JOHTO_BEAT_MEDIUM_REBECCA
	setflag FLAG_JOHTO_BEAT_MEDIUM_DORIS
	setflag FLAG_JOHTO_BEAT_PSYCHIC_FRANKLIN
	setflag FLAG_JOHTO_BEAT_PSYCHIC_JARED
	message SaffronGym_Johto_ReceivedMarshBadgeText
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_MARSHBADGE
	message SaffronGym_Johto_SabrinaMarshBadgeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_SaffronGymSabrinaScript_FightDone:
	message SaffronGym_Johto_SabrinaFightDoneText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_TrainerMediumRebecca::
	trainerbattle_single TRAINER_JOHTO_MEDIUM_REBECCA, SaffronGym_Johto_MediumRebeccaSeenText, SaffronGym_Johto_MediumRebeccaBeatenText
	setflag FLAG_JOHTO_BEAT_MEDIUM_REBECCA
	lock
	faceplayer
	goto SaffronGym_Johto_TrainerMediumRebecca_Script

SaffronGym_Johto_TrainerMediumRebecca_Script:
	message SaffronGym_Johto_MediumRebeccaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_TrainerPsychicFranklin::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_FRANKLIN, SaffronGym_Johto_PsychicFranklinSeenText, SaffronGym_Johto_PsychicFranklinBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_FRANKLIN
	lock
	faceplayer
	goto SaffronGym_Johto_TrainerPsychicFranklin_Script

SaffronGym_Johto_TrainerPsychicFranklin_Script:
	message SaffronGym_Johto_PsychicFranklinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_TrainerMediumDoris::
	trainerbattle_single TRAINER_JOHTO_MEDIUM_DORIS, SaffronGym_Johto_MediumDorisSeenText, SaffronGym_Johto_MediumDorisBeatenText
	setflag FLAG_JOHTO_BEAT_MEDIUM_DORIS
	lock
	faceplayer
	goto SaffronGym_Johto_TrainerMediumDoris_Script

SaffronGym_Johto_TrainerMediumDoris_Script:
	message SaffronGym_Johto_MediumDorisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_TrainerPsychicJared::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_JARED, SaffronGym_Johto_PsychicJaredSeenText, SaffronGym_Johto_PsychicJaredBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_JARED
	lock
	faceplayer
	goto SaffronGym_Johto_TrainerPsychicJared_Script

SaffronGym_Johto_TrainerPsychicJared_Script:
	message SaffronGym_Johto_PsychicJaredAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_SaffronGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_SABRINA, SaffronGym_Johto_SaffronGymGuideScript_SaffronGymGuideWinScript
	message SaffronGym_Johto_SaffronGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_SaffronGymGuideScript_SaffronGymGuideWinScript:
	message SaffronGym_Johto_SaffronGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SaffronGym_Johto_SaffronGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_MARSHBADGE, SaffronGym_Johto_SaffronGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

SaffronGym_Johto_SaffronGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

SaffronGym_Johto_SabrinaIntroText:
	.string "SABRINA: I knew\n"
	.string "you were coming…"
	.string "\pThree years ago I\n"
	.string "had a vision of\l"
	.string "your arrival."
	.string "\pYou're after my\n"
	.string "BADGE."
	.string "\pI don't enjoy bat-\n"
	.string "tling, but it's my"
	.string "\pduty as a LEADER\n"
	.string "to confer BADGES"
	.string "\pon anyone who has\n"
	.string "proven him- or\l"
	.string "herself worthy."
	.string "\pSince you wish it,\n"
	.string "I will show you my\l"
	.string "psychic powers!$"

SaffronGym_Johto_SabrinaWinLossText:
	.string "SABRINA: Your\n"
	.string "power…"
	.string "\pIt far exceeds\n"
	.string "what I foresaw…"
	.string "\pMaybe it isn't\n"
	.string "possible to fully"
	.string "\ppredict what the\n"
	.string "future holds…"
	.string "\pOK, you win. You\n"
	.string "earned yourself\l"
	.string "MARSHBADGE.$"

SaffronGym_Johto_ReceivedMarshBadgeText:
	.string "{PLAYER} received\n"
	.string "MARSHBADGE.$"

SaffronGym_Johto_SabrinaMarshBadgeText:
	.string "SABRINA: MARSH-\n"
	.string "BADGE draws out"
	.string "\pyour subliminal\n"
	.string "powers…"
	.string "\pAlthough I failed\n"
	.string "to accurately pre-\l"
	.string "dict your power,\l"
	.string "this much I know\l"
	.string "to be true."
	.string "\pYou will become a\n"
	.string "celebrated and\l"
	.string "beloved CHAMPION!$"

SaffronGym_Johto_SabrinaFightDoneText:
	.string "SABRINA: Your love\n"
	.string "for your POKéMON"
	.string "\poverwhelmed my\n"
	.string "psychic power…"
	.string "\pThe power of love,\n"
	.string "I think, is also a"
	.string "\pkind of psychic\n"
	.string "power…$"

SaffronGym_Johto_MediumRebeccaSeenText:
	.string "The power of all\n"
	.string "those you defeated\l"
	.string "comes to me!$"

SaffronGym_Johto_MediumRebeccaBeatenText:
	.string "Strong…\n"
	.string "Far too strong…$"

SaffronGym_Johto_MediumRebeccaAfterBattleText:
	.string "What is the source\n"
	.string "of your power?$"

SaffronGym_Johto_PsychicFranklinSeenText:
	.string "Psychic power is\n"
	.string "the power of your\l"
	.string "soul.$"

SaffronGym_Johto_PsychicFranklinBeatenText:
	.string "Your soul has more\n"
	.string "power than mine!$"

SaffronGym_Johto_PsychicFranklinAfterBattleText:
	.string "You made your soul\n"
	.string "stronger, not just\l"
	.string "your abilities.$"

SaffronGym_Johto_MediumDorisSeenText:
	.string "Fufufufu…\n"
	.string "I see it clearly."
	.string "\pI can see into\n"
	.string "your soul!$"

SaffronGym_Johto_MediumDorisBeatenText:
	.string "Though I read you,\n"
	.string "I still lost…$"

SaffronGym_Johto_MediumDorisAfterBattleText:
	.string "Darn! I forgot\n"
	.string "that I predicted I\l"
	.string "would lose to you.$"

SaffronGym_Johto_PsychicJaredSeenText:
	.string "The FIGHTING DOJO\n"
	.string "next door was once\l"
	.string "this city's GYM.$"

SaffronGym_Johto_PsychicJaredBeatenText:
	.string "I was no match…$"

SaffronGym_Johto_PsychicJaredAfterBattleText:
	.string "KARATE KING, the\n"
	.string "master of the"
	.string "\pFIGHTING DOJO, was\n"
	.string "just destroyed by\l"
	.string "SABRINA.$"

SaffronGym_Johto_SaffronGymGuideText:
	.string "Yo, CHAMP in\n"
	.string "making!"
	.string "\pA trainer as\n"
	.string "skilled as you"
	.string "\pdoesn't need to be\n"
	.string "told how to deal"
	.string "\pwith psychic-type\n"
	.string "POKéMON, right?"
	.string "\pI expect great\n"
	.string "things from you!"
	.string "\pGood luck!$"

SaffronGym_Johto_SaffronGymGuideWinText:
	.string "That was another\n"
	.string "fantastic battle!$"
