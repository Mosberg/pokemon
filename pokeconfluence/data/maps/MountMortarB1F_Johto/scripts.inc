MountMortarB1F_Johto_MapScripts::
	.byte 0

MountMortarB1F_Johto_MountMortarB1FHyperPotion_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FHyperPotion

MountMortarB1F_Johto_MountMortarB1FCarbos_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FCarbos

MountMortarB1F_Johto_MountMortarB1FBoulder_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FBoulder

MountMortarB1F_Johto_MountMortarB1FKiyoScript_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FKiyoScript

MountMortarB1F_Johto_MountMortarB1FFullRestore_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FFullRestore

MountMortarB1F_Johto_MountMortarB1FMaxEther_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FMaxEther

MountMortarB1F_Johto_MountMortarB1FPPUp_Entry::
	lockall
	goto MountMortarB1F_Johto_MountMortarB1FPPUp


MountMortarB1F_Johto_MountMortarB1FKiyoScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TYROGUE_FROM_KIYO, MountMortarB1F_Johto_MountMortarB1FKiyoScript_GotTyrogue
	goto_if_set FLAG_JOHTO_BEAT_BLACKBELT_KIYO, MountMortarB1F_Johto_MountMortarB1FKiyoScript_BeatKiyo
	message MountMortarB1F_Johto_MountMortarB1FKiyoIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_BLACKBELT_T_KIYO, MountMortarB1F_Johto_MountMortarB1FKiyoWinText
	setflag FLAG_JOHTO_BEAT_BLACKBELT_KIYO

MountMortarB1F_Johto_MountMortarB1FKiyoScript_BeatKiyo:
	message MountMortarB1F_Johto_MountMortarB1FTyrogueRewardText
	waitmessage
	waitbuttonpress
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 6, MountMortarB1F_Johto_MountMortarB1FKiyoScript_NoRoom
	message MountMortarB1F_Johto_MountMortarB1FReceiveMonText
	waitmessage
	playse SE_PIN
	waitse
	givemon SPECIES_TYROGUE, 10
	setflag FLAG_JOHTO_GOT_TYROGUE_FROM_KIYO

MountMortarB1F_Johto_MountMortarB1FKiyoScript_GotTyrogue:
	message MountMortarB1F_Johto_MountMortarB1FKiyoGotTyrogueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FKiyoScript_NoRoom:
	message MountMortarB1F_Johto_MountMortarB1FKiyoFullPartyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FBoulder:
	goto Johto_Std_StrengthBoulderScript

MountMortarB1F_Johto_MountMortarB1FHyperPotion:
	finditem ITEM_HYPER_POTION
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FCarbos:
	finditem ITEM_CARBOS
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FFullRestore:
	finditem ITEM_FULL_RESTORE
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FMaxEther:
	finditem ITEM_MAX_ETHER
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FPPUp:
	finditem ITEM_PP_UP
	releaseall
	end

MountMortarB1F_Johto_MountMortarB1FKiyoIntroText:
	.string "Hey!"
	.string "\pI am the KARATE\n"
	.string "KING!"
	.string "\pI train alone here\n"
	.string "in the dark!"
	.string "\pYou!\n"
	.string "Battle with me!"
	.string "\pHwaaarggh!$"

MountMortarB1F_Johto_MountMortarB1FKiyoWinText:
	.string "Waaaarggh!\n"
	.string "I'm beaten!$"

MountMortarB1F_Johto_MountMortarB1FTyrogueRewardText:
	.string "I… I'm crushed…"
	.string "\pMy training is\n"
	.string "still not enough…"
	.string "\pBut a loss is a\n"
	.string "loss. I admit it."
	.string "\pAs proof that you\n"
	.string "defeated me, I'll"
	.string "\pgive you a rare\n"
	.string "fighting POKéMON.$"

MountMortarB1F_Johto_MountMortarB1FReceiveMonText:
	.string "{PLAYER} received\n"
	.string "TYROGUE.$"

MountMortarB1F_Johto_MountMortarB1FKiyoGotTyrogueText:
	.string "TYROGUE is a\n"
	.string "fighting-type."
	.string "\pIt evolves into a\n"
	.string "tougher POKéMON."
	.string "\pKeep up the hard\n"
	.string "work. I'll keep\l"
	.string "training too."
	.string "\pFarewell!$"

MountMortarB1F_Johto_MountMortarB1FKiyoFullPartyText:
	.string "You have no room\n"
	.string "in your party!$"
