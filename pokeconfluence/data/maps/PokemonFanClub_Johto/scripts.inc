PokemonFanClub_Johto_MapScripts::
	.byte 0

PokemonFanClub_Johto_PokemonFanClubChairmanScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubChairmanScript

PokemonFanClub_Johto_PokemonFanClubReceptionistScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubReceptionistScript

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript

PokemonFanClub_Johto_PokemonFanClubTeacherScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubTeacherScript

PokemonFanClub_Johto_PokemonFanClubClefairyDollScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubClefairyDollScript

PokemonFanClub_Johto_PokemonFanClubBayleefScript_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubBayleefScript

PokemonFanClub_Johto_PokemonFanClubListenSign_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubListenSign

PokemonFanClub_Johto_PokemonFanClubBraggingSign_Entry::
	lockall
	goto PokemonFanClub_Johto_PokemonFanClubBraggingSign


PokemonFanClub_Johto_PokemonFanClubChairmanScript:
	faceplayer
	goto_if_set FLAG_JOHTO_LISTENED_TO_FAN_CLUB_PRESIDENT, PokemonFanClub_Johto_PokemonFanClubChairmanScript_HeardSpeech
	goto_if_set FLAG_JOHTO_LISTENED_TO_FAN_CLUB_PRESIDENT_BUT_BAG_WAS_FULL, PokemonFanClub_Johto_PokemonFanClubChairmanScript_HeardSpeechButBagFull
	message PokemonFanClub_Johto_PokemonFanClubChairmanDidYouVisitToHearAboutMyMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, PokemonFanClub_Johto_PokemonFanClubChairmanScript_NotListening
	message PokemonFanClub_Johto_PokemonFanClubChairmanRapidashText
	waitmessage
	waitbuttonpress

PokemonFanClub_Johto_PokemonFanClubChairmanScript_HeardSpeechButBagFull:
	message PokemonFanClub_Johto_PokemonFanClubChairmanIWantYouToHaveThisText
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, 0, PokemonFanClub_Johto_PokemonFanClubChairmanScript_BagFull
	setflag FLAG_JOHTO_LISTENED_TO_FAN_CLUB_PRESIDENT
	message PokemonFanClub_Johto_PokemonFanClubChairmanItsARareCandyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubChairmanScript_HeardSpeech:
	message PokemonFanClub_Johto_PokemonFanClubChairmanMoreTalesToTellText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubChairmanScript_NotListening:
	message PokemonFanClub_Johto_PokemonFanClubChairmanHowDisappointingText
	waitmessage
	waitbuttonpress

PokemonFanClub_Johto_PokemonFanClubChairmanScript_BagFull:
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubReceptionistScript:
	faceplayer
	message PokemonFanClub_Johto_PokemonFanClubReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_LOST_ITEM_FROM_FAN_CLUB, PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_GotLostItem
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_FoundClefairyDoll
	message PokemonFanClub_Johto_PokemonFanClubClefairyGuyClefairyIsSoAdorableText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_FoundClefairyDoll:
	message PokemonFanClub_Johto_PokemonFanClubClefairyGuyMakingDoWithADollIFoundText
	waitmessage
	goto_if_set FLAG_JOHTO_MET_COPYCAT_FOUND_OUT_ABOUT_LOST_ITEM, PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_MetCopycat
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_MetCopycat:
	waitbuttonpress
	message PokemonFanClub_Johto_PokemonFanClubClefairyGuyTakeThisDollBackToGirlText
	waitmessage
	waitbuttonpress
	waitse
	additem ITEM_LOST_ITEM
	goto_if_eq VAR_RESULT, 0, PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_NoRoom
	removeobject 5
	message PokemonFanClub_Johto_PokemonFanClubPlayerReceivedDollText
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	setflag FLAG_JOHTO_GOT_LOST_ITEM_FROM_FAN_CLUB
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_GotLostItem:
	message PokemonFanClub_Johto_PokemonFanClubClefairyGuyGoingToGetARealClefairyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyGuyScript_NoRoom:
	message PokemonFanClub_Johto_PokemonFanClubClefairyGuyPackIsJammedFullText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubTeacherScript:
	faceplayer
	message PokemonFanClub_Johto_PokemonFanClubTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubClefairyDollScript:
	message PokemonFanClub_Johto_PokemonFanClubClefairyDollText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubBayleefScript:
	message PokemonFanClub_Johto_PokemonFanClubBayleefText
	waitmessage
	playmoncry SPECIES_BAYLEEF, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubListenSign:
	message PokemonFanClub_Johto_PokemonFanClubListenSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubBraggingSign:
	message PokemonFanClub_Johto_PokemonFanClubBraggingSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PokemonFanClub_Johto_PokemonFanClubChairmanDidYouVisitToHearAboutMyMonText:
	.string "I'm the CHAIRMAN\n"
	.string "of the POKéMON FAN\l"
	.string "CLUB."
	.string "\pI've raised over\n"
	.string "150 POKéMON."
	.string "\pI'm very fussy\n"
	.string "when it comes to\l"
	.string "POKéMON."
	.string "\pDid you visit just\n"
	.string "to hear about my\l"
	.string "POKéMON?$"

PokemonFanClub_Johto_PokemonFanClubChairmanRapidashText:
	.string "Good!\n"
	.string "Then listen up!"
	.string "\pSo… my favorite\n"
	.string "RAPIDASH…"
	.string "\pIt… cute… lovely…\n"
	.string "smart… unbearably…\l"
	.string "plus… amazing… oh…\l"
	.string "you think so?…\l"
	.string "Too much… wild…\l"
	.string "beautiful… kindly…\l"
	.string "love it!"
	.string "\pHug it… when…\n"
	.string "sleeping… warm and\l"
	.string "cuddly… Oh, and…\l"
	.string "spectacular…\l"
	.string "ravishing… simply\l"
	.string "divine…\l"
	.string "Oops! Look at the\l"
	.string "time! I've kept\l"
	.string "you too long!$"

PokemonFanClub_Johto_PokemonFanClubChairmanIWantYouToHaveThisText:
	.string "Thanks for hearing\n"
	.string "me out. I want you\l"
	.string "to have this!$"

PokemonFanClub_Johto_PokemonFanClubChairmanItsARareCandyText:
	.string "It's a RARE CANDY\n"
	.string "that makes POKéMON\l"
	.string "stronger."
	.string "\pI prefer making my\n"
	.string "POKéMON stronger"
	.string "\pby battling, so\n"
	.string "you can have it.$"

PokemonFanClub_Johto_PokemonFanClubChairmanMoreTalesToTellText:
	.string "Hello, {PLAYER}!"
	.string "\pDid you come see\n"
	.string "me about my POKé-\l"
	.string "MON again?"
	.string "\pNo? Oh… I had more\n"
	.string "tales to tell…$"

PokemonFanClub_Johto_PokemonFanClubChairmanHowDisappointingText:
	.string "How disappointing…"
	.string "\pCome back if you\n"
	.string "want to listen.$"

PokemonFanClub_Johto_PokemonFanClubReceptionistText:
	.string "Our CHAIRMAN is\n"
	.string "very vocal when it\l"
	.string "comes to POKéMON…$"

PokemonFanClub_Johto_PokemonFanClubClefairyGuyClefairyIsSoAdorableText:
	.string "I love the way\n"
	.string "CLEFAIRY waggles"
	.string "\pits finger when\n"
	.string "it's trying to use"
	.string "\pMETRONOME.\n"
	.string "It's so adorable!$"

PokemonFanClub_Johto_PokemonFanClubClefairyGuyMakingDoWithADollIFoundText:
	.string "I love CLEFAIRY,\n"
	.string "but I could never"
	.string "\pcatch one. So I'm\n"
	.string "making do with a"
	.string "\pPOKé DOLL that I\n"
	.string "found.$"

PokemonFanClub_Johto_PokemonFanClubClefairyGuyTakeThisDollBackToGirlText:
	.string "Oh, I see now. The\n"
	.string "girl who lost this"
	.string "\pPOKé DOLL is sad…"
	.string "\pOK. Could you take\n"
	.string "this POKé DOLL"
	.string "\pback to that poor\n"
	.string "little girl?"
	.string "\pI'll befriend a\n"
	.string "real CLEFAIRY on"
	.string "\pmy own one day.\n"
	.string "No worries!$"

PokemonFanClub_Johto_PokemonFanClubPlayerReceivedDollText:
	.string "{PLAYER} received\n"
	.string "POKé DOLL.$"

PokemonFanClub_Johto_PokemonFanClubClefairyGuyGoingToGetARealClefairyText:
	.string "You watch. I'm\n"
	.string "going to get a"
	.string "\preal CLEFAIRY as\n"
	.string "my friend.$"

PokemonFanClub_Johto_PokemonFanClubClefairyGuyPackIsJammedFullText:
	.string "Your PACK is\n"
	.string "jammed full.$"

PokemonFanClub_Johto_PokemonFanClubTeacherText:
	.string "Look at my darling\n"
	.string "BAYLEEF!"
	.string "\pThe leaf on its\n"
	.string "head is so cute!$"

PokemonFanClub_Johto_PokemonFanClubClefairyDollText:
	.string "It's a CLEFAIRY!\n"
	.string "Huh?"
	.string "\pOh, right. It's a\n"
	.string "CLEFAIRY POKé\l"
	.string "DOLL.$"

PokemonFanClub_Johto_PokemonFanClubBayleefText:
	.string "BAYLEEF: Li liif!$"

PokemonFanClub_Johto_PokemonFanClubListenSignText:
	.string "Let's all listen\n"
	.string "politely to other\l"
	.string "trainers.$"

PokemonFanClub_Johto_PokemonFanClubBraggingSignText:
	.string "If someone brags,\n"
	.string "brag right back!$"
