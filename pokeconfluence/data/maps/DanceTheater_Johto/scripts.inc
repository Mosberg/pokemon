DanceTheater_Johto_MapScripts::
	.byte 0

DanceTheater_Johto_DanceTheaterSurfGuy_Entry::
	lockall
	goto DanceTheater_Johto_DanceTheaterSurfGuy

DanceTheater_Johto_DanceTheaterRhydon_Entry::
	lockall
	goto DanceTheater_Johto_DanceTheaterRhydon

DanceTheater_Johto_DanceTheaterCooltrainerMScript_Entry::
	lockall
	goto DanceTheater_Johto_DanceTheaterCooltrainerMScript

DanceTheater_Johto_DanceTheaterGrannyScript_Entry::
	lockall
	goto DanceTheater_Johto_DanceTheaterGrannyScript

DanceTheater_Johto_DanceTheaterFancyPanel_Entry::
	lockall
	goto DanceTheater_Johto_DanceTheaterFancyPanel


DanceTheater_Johto_TrainerKimonoGirlNaoko::
	trainerbattle_single TRAINER_JOHTO_KIMONO_GIRL_NAOKO, DanceTheater_Johto_KimonoGirlNaokoSeenText, DanceTheater_Johto_KimonoGirlNaokoBeatenText
	setflag FLAG_JOHTO_BEAT_KIMONO_GIRL_NAOKO
	lock
	faceplayer
	goto DanceTheater_Johto_TrainerKimonoGirlNaoko_Script

DanceTheater_Johto_TrainerKimonoGirlNaoko_Script:
	message DanceTheater_Johto_KimonoGirlNaokoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_TrainerKimonoGirlSayo::
	trainerbattle_single TRAINER_JOHTO_KIMONO_GIRL_SAYO, DanceTheater_Johto_KimonoGirlSayoSeenText, DanceTheater_Johto_KimonoGirlSayoBeatenText
	setflag FLAG_JOHTO_BEAT_KIMONO_GIRL_SAYO
	lock
	faceplayer
	goto DanceTheater_Johto_TrainerKimonoGirlSayo_Script

DanceTheater_Johto_TrainerKimonoGirlSayo_Script:
	message DanceTheater_Johto_KimonoGirlSayoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_TrainerKimonoGirlZuki::
	trainerbattle_single TRAINER_JOHTO_KIMONO_GIRL_ZUKI, DanceTheater_Johto_KimonoGirlZukiSeenText, DanceTheater_Johto_KimonoGirlZukiBeatenText
	setflag FLAG_JOHTO_BEAT_KIMONO_GIRL_ZUKI
	lock
	faceplayer
	goto DanceTheater_Johto_TrainerKimonoGirlZuki_Script

DanceTheater_Johto_TrainerKimonoGirlZuki_Script:
	message DanceTheater_Johto_KimonoGirlZukiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_TrainerKimonoGirlKuni::
	trainerbattle_single TRAINER_JOHTO_KIMONO_GIRL_KUNI, DanceTheater_Johto_KimonoGirlKuniSeenText, DanceTheater_Johto_KimonoGirlKuniBeatenText
	setflag FLAG_JOHTO_BEAT_KIMONO_GIRL_KUNI
	lock
	faceplayer
	goto DanceTheater_Johto_TrainerKimonoGirlKuni_Script

DanceTheater_Johto_TrainerKimonoGirlKuni_Script:
	message DanceTheater_Johto_KimonoGirlKuniAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_TrainerKimonoGirlMiki::
	trainerbattle_single TRAINER_JOHTO_KIMONO_GIRL_MIKI, DanceTheater_Johto_KimonoGirlMikiSeenText, DanceTheater_Johto_KimonoGirlMikiBeatenText
	setflag FLAG_JOHTO_BEAT_KIMONO_GIRL_MIKI
	lock
	faceplayer
	goto DanceTheater_Johto_TrainerKimonoGirlMiki_Script

DanceTheater_Johto_TrainerKimonoGirlMiki_Script:
	message DanceTheater_Johto_KimonoGirlMikiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterSurfGuy:
	faceplayer
	message DanceTheater_Johto_SurfGuyNeverLeftAScratchText
	waitmessage
	waitbuttonpress
	goto_if_set FLAG_JOHTO_GOT_HM03_SURF, DanceTheater_Johto_SurfGuyAlreadyGaveSurf
	goto_if_unset FLAG_JOHTO_BEAT_KIMONO_GIRL_NAOKO, DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto_if_unset FLAG_JOHTO_BEAT_KIMONO_GIRL_SAYO, DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto_if_unset FLAG_JOHTO_BEAT_KIMONO_GIRL_ZUKI, DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto_if_unset FLAG_JOHTO_BEAT_KIMONO_GIRL_KUNI, DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto_if_unset FLAG_JOHTO_BEAT_KIMONO_GIRL_MIKI, DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto DanceTheater_Johto_DanceTheaterSurfGuy_GetSurf

DanceTheater_Johto_DanceTheaterSurfGuy_KimonoGirlsUndefeated:
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, DanceTheater_Johto_DanceTheaterSurfGuy_PlayerIsFemale
	message DanceTheater_Johto_SurfGuyLadGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterSurfGuy_PlayerIsFemale:
	message DanceTheater_Johto_SurfGuyLassieGiftText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterSurfGuy_GetSurf:
	message DanceTheater_Johto_SurfGuyLikeADanceText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM_SURF
	setflag FLAG_JOHTO_GOT_HM03_SURF
	message DanceTheater_Johto_SurfGuySurfExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_SurfGuyAlreadyGaveSurf:
	message DanceTheater_Johto_SurfGuyElegantKimonoGirlsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterRhydon:
	message DanceTheater_Johto_RhydonText
	waitmessage
	playmoncry SPECIES_RHYDON, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterCooltrainerMScript:
	faceplayer
	message DanceTheater_Johto_DanceTheaterCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterGrannyScript:
	faceplayer
	message DanceTheater_Johto_DanceTheaterGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_DanceTheaterFancyPanel:
	message DanceTheater_Johto_DanceTheaterFancyPanelText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DanceTheater_Johto_KimonoGirlNaokoSeenText:
	.string "You have lovely\n"
	.string "POKéMON. May I see\l"
	.string "them in battle?$"

DanceTheater_Johto_KimonoGirlNaokoBeatenText:
	.string "Oh, you are very\n"
	.string "strong.$"

DanceTheater_Johto_KimonoGirlNaokoAfterBattleText:
	.string "I enjoyed that\n"
	.string "bout. I would like\l"
	.string "to see you again.$"

DanceTheater_Johto_KimonoGirlSayoSeenText:
	.string "I always dance\n"
	.string "with my POKéMON."
	.string "\pOf course, I also\n"
	.string "train them.$"

DanceTheater_Johto_KimonoGirlSayoBeatenText:
	.string "Oh, so close!\n"
	.string "I almost had you.$"

DanceTheater_Johto_KimonoGirlSayoAfterBattleText:
	.string "Rhythm is impor-\n"
	.string "tant for both"
	.string "\pdancing and POKé-\n"
	.string "MON.$"

DanceTheater_Johto_KimonoGirlZukiSeenText:
	.string "Isn't my barrette\n"
	.string "pretty?"
	.string "\pOh. A POKéMON\n"
	.string "battle?$"

DanceTheater_Johto_KimonoGirlZukiBeatenText:
	.string "I don't have any\n"
	.string "POKéMON left…$"

DanceTheater_Johto_KimonoGirlZukiAfterBattleText:
	.string "I put a different\n"
	.string "flower in my bar-\l"
	.string "rette every month.$"

DanceTheater_Johto_KimonoGirlKuniSeenText:
	.string "Oh, you're a cute\n"
	.string "trainer. Would you\l"
	.string "like to battle?$"

DanceTheater_Johto_KimonoGirlKuniBeatenText:
	.string "You're stronger\n"
	.string "than you look.$"

DanceTheater_Johto_KimonoGirlKuniAfterBattleText:
	.string "I trained a lot,\n"
	.string "so I thought I was"
	.string "\pa capable trainer.\n"
	.string "I guess I'm not.$"

DanceTheater_Johto_KimonoGirlMikiSeenText:
	.string "Do you like my\n"
	.string "dancing? I'm good\l"
	.string "at POKéMON too.$"

DanceTheater_Johto_KimonoGirlMikiBeatenText:
	.string "Ooh, you're good\n"
	.string "at POKéMON too.$"

DanceTheater_Johto_KimonoGirlMikiAfterBattleText:
	.string "I can keep dancing\n"
	.string "because there are"
	.string "\ppeople who enjoy\n"
	.string "what I do."
	.string "\pMy POKéMON keep my\n"
	.string "spirits up too.$"

DanceTheater_Johto_SurfGuyNeverLeftAScratchText:
	.string "Not only are the\n"
	.string "KIMONO GIRLS great"
	.string "\pdancers, they're\n"
	.string "also skilled at\l"
	.string "POKéMON."
	.string "\pI always challenge\n"
	.string "them, but I've"
	.string "\pnever even left a\n"
	.string "scratch…$"

DanceTheater_Johto_SurfGuyLadGiftText:
	.string "Lad! If you can\n"
	.string "defeat all the"
	.string "\pKIMONO GIRLS, I'll\n"
	.string "give you a gift.$"

DanceTheater_Johto_SurfGuyLassieGiftText:
	.string "Lassie, if you can\n"
	.string "defeat all the"
	.string "\pKIMONO GIRLS, I'll\n"
	.string "give you a gift.$"

DanceTheater_Johto_SurfGuyLikeADanceText:
	.string "The way you bat-\n"
	.string "tled, it was like\l"
	.string "watching a dance."
	.string "\pIt was a rare\n"
	.string "treat to see!"
	.string "\pI want you to have\n"
	.string "this. Don't worry\l"
	.string "--take it!$"

DanceTheater_Johto_SurfGuySurfExplanationText:
	.string "That's SURF."
	.string "\pIt's a move that\n"
	.string "lets POKéMON swim\l"
	.string "across water.$"

DanceTheater_Johto_SurfGuyElegantKimonoGirlsText:
	.string "I wish my POKéMON\n"
	.string "were as elegant as\l"
	.string "the KIMONO GIRLS…$"

DanceTheater_Johto_RhydonText:
	.string "RHYDON: Gugooh\n"
	.string "gugogooh!$"

DanceTheater_Johto_DanceTheaterCooltrainerMText:
	.string "That man's always\n"
	.string "with his RHYDON."
	.string "\pSays he wants a\n"
	.string "POKéMON that can\l"
	.string "SURF and dance."
	.string "\pIs he trying to\n"
	.string "make a synchro-\l"
	.string "nized swimming\l"
	.string "POKéMON?$"

DanceTheater_Johto_DanceTheaterGrannyText:
	.string "The KIMONO GIRLS\n"
	.string "are so beautiful…"
	.string "\pBut they have to\n"
	.string "go through rigor-\l"
	.string "ous training."
	.string "\pAnd they have to\n"
	.string "learn to follow"
	.string "\pcustoms before ap-\n"
	.string "pearing in public."
	.string "\pBut if you love\n"
	.string "something, any-\l"
	.string "thing is possible.$"

DanceTheater_Johto_DanceTheaterFancyPanelText:
	.string "It's a fancy panel\n"
	.string "that's decorated\l"
	.string "with flowers.$"
