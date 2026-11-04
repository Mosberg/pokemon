OlivineLighthouse2F_Johto_MapScripts::
	.byte 0



OlivineLighthouse2F_Johto_TrainerGentlemanAlfred::
	trainerbattle_single TRAINER_JOHTO_GENTLEMAN_ALFRED, OlivineLighthouse2F_Johto_GentlemanAlfredSeenText, OlivineLighthouse2F_Johto_GentlemanAlfredBeatenText
	setflag FLAG_JOHTO_BEAT_GENTLEMAN_ALFRED
	lock
	faceplayer
	goto OlivineLighthouse2F_Johto_TrainerGentlemanAlfred_Script

OlivineLighthouse2F_Johto_TrainerGentlemanAlfred_Script:
	message OlivineLighthouse2F_Johto_GentlemanAlfredAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse2F_Johto_TrainerSailorHuey::
	trainerbattle_single TRAINER_JOHTO_SAILOR_HUEY1, OlivineLighthouse2F_Johto_SailorHueySeenText, OlivineLighthouse2F_Johto_SailorHueyBeatenText
	setflag FLAG_JOHTO_BEAT_SAILOR_HUEY
	lock
	faceplayer
	goto OlivineLighthouse2F_Johto_TrainerSailorHuey_Script

OlivineLighthouse2F_Johto_TrainerSailorHuey_Script:
	goto_if_set FLAG_JOHTO_ENGINE_HUEY_READY_FOR_REMATCH, OlivineLighthouse2F_Johto_TrainerSailorHuey_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, OlivineLighthouse2F_Johto_TrainerSailorHuey_NumberAccepted
	goto_if_set FLAG_JOHTO_HUEY_ASKED_FOR_PHONE_NUMBER, OlivineLighthouse2F_Johto_TrainerSailorHuey_AskedBefore
	setflag FLAG_JOHTO_HUEY_ASKED_FOR_PHONE_NUMBER
	call OlivineLighthouse2F_Johto_TrainerSailorHuey_AskNumber1_Sub
	goto OlivineLighthouse2F_Johto_TrainerSailorHuey_AskForNumber

OlivineLighthouse2F_Johto_TrainerSailorHuey_AskedBefore:
	call OlivineLighthouse2F_Johto_TrainerSailorHuey_AskNumber2_Sub

OlivineLighthouse2F_Johto_TrainerSailorHuey_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, OlivineLighthouse2F_Johto_TrainerSailorHuey_PhoneFull
	goto_if_eq VAR_RESULT, 2, OlivineLighthouse2F_Johto_TrainerSailorHuey_NumberDeclined
	call OlivineLighthouse2F_Johto_TrainerSailorHuey_RegisteredNumber_Sub
	goto OlivineLighthouse2F_Johto_TrainerSailorHuey_NumberAccepted

OlivineLighthouse2F_Johto_TrainerSailorHuey_WantsBattle:
	call OlivineLighthouse2F_Johto_TrainerSailorHuey_Rematch_Sub
	@ TODO unsupported: readmem wHueyFightCount
	goto Johto_EventScript_Unimplemented

OlivineLighthouse2F_Johto_TrainerSailorHuey_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

OlivineLighthouse2F_Johto_TrainerSailorHuey_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

OlivineLighthouse2F_Johto_TrainerSailorHuey_PhoneFull:
	goto Johto_Std_PhoneFullMScript

OlivineLighthouse2F_Johto_TrainerSailorHuey_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

OlivineLighthouse2F_Johto_TrainerSailorHuey_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

OlivineLighthouse2F_Johto_TrainerSailorHuey_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

OlivineLighthouse2F_Johto_TrainerSailorHuey_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

OlivineLighthouse2F_Johto_SailorHueySeenText:
	.string "Men of the sea are\n"
	.string "always spoiling\l"
	.string "for a good fight!$"

OlivineLighthouse2F_Johto_SailorHueyBeatenText:
	.string "Urf!\n"
	.string "I lose!$"

OlivineLighthouse2F_Johto_GentlemanAlfredSeenText:
	.string "Hm? This is no\n"
	.string "place for playing.$"

OlivineLighthouse2F_Johto_GentlemanAlfredBeatenText:
	.string "Ah! I can see that\n"
	.string "you're serious.$"

OlivineLighthouse2F_Johto_GentlemanAlfredAfterBattleText:
	.string "Up top is a POKé-\n"
	.string "MON that keeps the\l"
	.string "LIGHTHOUSE lit."
	.string "\pBut I hear that\n"
	.string "it's sick now and"
	.string "\pcan't be cured by\n"
	.string "ordinary medicine.$"
