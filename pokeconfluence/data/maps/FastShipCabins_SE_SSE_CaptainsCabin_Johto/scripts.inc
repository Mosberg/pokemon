FastShipCabins_SE_SSE_CaptainsCabin_Johto_MapScripts::
	.byte 0

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptain_Entry::
	lockall
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptain

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpa_Entry::
	lockall
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpa

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterAfter_Entry::
	lockall
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterAfter

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore_Entry::
	lockall
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore

FastShipCabins_SE_SSE_CaptainsCabin_Johto_FastShipCaptainsCabinTrashcan_Entry::
	lockall
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_FastShipCaptainsCabinTrashcan


FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptain:
	faceplayer
	goto_if_set FLAG_JOHTO_FAST_SHIP_FIRST_TIME, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptain_LaterTrip
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainExhaustingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptain_LaterTrip:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainHowDoYouLikeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore:
	applymovement 4, Johto_Movement_Face_Right
	waitmovement 4
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterCaptainPlayWithMeText
	waitmessage
	waitbuttonpress
	closemessage
	faceplayer
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterHasToFindGrandpaText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 4
	applymovement OBJ_EVENT_ID_PLAYER, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainsCabinWarpsToGrandpasCabinMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setobjectxyperm 3, 3, 19
	clearflag FLAG_JOHTO_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_1
	addobject 3
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Up
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, Johto_Movement_Face_Up
	waitmovement 3
	fadescreen FADE_FROM_BLACK
	applymovement 2, Johto_Movement_Face_Down
	waitmovement 2
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	applymovement 3, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterEntersCabinMovement
	waitmovement 3
	applymovement 2, Johto_Movement_Face_Right
	waitmovement 2
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore_PlayerIsFemale
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterWasPlayingMText
	waitmessage
	waitbuttonpress
	closemessage
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore_cont

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore_PlayerIsFemale:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterWasPlayingFText
	waitmessage
	waitbuttonpress
	closemessage

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterBefore_cont:
	applymovement 4, Johto_Movement_Face_Down
	waitmovement 4
	applymovement 2, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaApproachesPlayerMovement
	waitmovement 2
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaEntertainedGranddaughterText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_VERMILION_PORT_SAILOR_AT_GANGWAY
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 0
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaMetalCoatAndDocking

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpa:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGotMetalCoat
	goto_if_set FLAG_JOHTO_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_2, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaFoundGranddaughter
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCantFindGranddaughterText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_FAST_SHIP_1F, 0
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaMetalCoatAndDocking:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaHaveThisText
	waitmessage
	waitbuttonpress
	giveitem ITEM_METAL_COAT
	goto_if_eq VAR_RESULT, 0, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaMetalCoatAndDocking_NoRoom
	setflag FLAG_JOHTO_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaMetalCoatAndDocking_NoRoom:
	closemessage
	waitse
	playse SE_PIN
	delay 30
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaHasArrivedVermilionText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_FAST_SHIP_HAS_ARRIVED
	setflag FLAG_JOHTO_FAST_SHIP_FOUND_GIRL
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaFoundGranddaughter:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaHaveThisText
	waitmessage
	waitbuttonpress
	giveitem ITEM_METAL_COAT
	goto_if_eq VAR_RESULT, 0, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaFoundGranddaughter_NoRoom
	setflag FLAG_JOHTO_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaFoundGranddaughter_NoRoom:
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGotMetalCoat:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaTravellingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterAfter:
	faceplayer
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterHadFunText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmColin::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_COLIN, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinSeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_COLIN
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmColin_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmColin_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg1::
	trainerbattle_single TRAINER_JOHTO_TWINS_MEGANDPEG1, FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1SeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_MEG_AND_PEG
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg1_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg1_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg2::
	trainerbattle_single TRAINER_JOHTO_TWINS_MEGANDPEG2, FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2SeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2BeatenText
	setflag FLAG_JOHTO_BEAT_TWINS_MEG_AND_PEG
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg2_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerTwinsMegandpeg2_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPsychicRodney::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_RODNEY, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneySeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneyBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_RODNEY
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPsychicRodney_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPsychicRodney_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmJeremy::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_JEREMY, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremySeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremyBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_JEREMY
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmJeremy_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanmJeremy_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanfGeorgia::
	trainerbattle_single TRAINER_JOHTO_POKEFANF_GEORGIA, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaSeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANF_GEORGIA
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanfGeorgia_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerPokefanfGeorgia_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerSupernerdShawn::
	trainerbattle_single TRAINER_JOHTO_SUPER_NERD_SHAWN, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnSeenText, FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnBeatenText
	setflag FLAG_JOHTO_BEAT_SUPER_NERD_SHAWN
	lock
	faceplayer
	goto FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerSupernerdShawn_Script

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TrainerSupernerdShawn_Script:
	message FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_FastShipCaptainsCabinTrashcan:
	goto Johto_Std_TrashCanScript

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainsCabinWarpsToGrandpasCabinMovement:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterEntersCabinMovement:
	walk_up
	walk_up
	face_left
	step_end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaApproachesPlayerMovement:
	walk_down
	step_end

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainExhaustingText:
	.string "Whew! Thanks for\n"
	.string "coming along."
	.string "\pKeeping that lit-\n"
	.string "tle girl amused\l"
	.string "was exhausting.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCaptainHowDoYouLikeText:
	.string "How do you like\n"
	.string "S.S.AQUA's ride?"
	.string "\pShe practically\n"
	.string "skates across the\l"
	.string "waves.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaCantFindGranddaughterText:
	.string "Oh, hello…"
	.string "\pI still can't find\n"
	.string "my granddaughter."
	.string "\pIf she's on the\n"
	.string "ship, that's OK."
	.string "\pShe's an energetic\n"
	.string "child, so she may"
	.string "\pbe bugging some-\n"
	.string "one. I'm worried…$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaEntertainedGranddaughterText:
	.string "{PLAYER}, was it?\n"
	.string "I heard you enter-\l"
	.string "tained my grand-\l"
	.string "daughter."
	.string "\pI want to thank\n"
	.string "you for that.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaHaveThisText:
	.string "I know! I'd like\n"
	.string "you to have this!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGrandpaTravellingText:
	.string "We're traveling\n"
	.string "around the world.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterCaptainPlayWithMeText:
	.string "CAPTAIN, play with\n"
	.string "me, please?"
	.string "\pI'm bored! I want\n"
	.string "to play more!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterHasToFindGrandpaText:
	.string "Hi! Will you play\n"
	.string "with me?"
	.string "\p…Oh!"
	.string "\pGrandpa's worried\n"
	.string "about me?"
	.string "\pI have to go!"
	.string "\pI have to go find\n"
	.string "Grandpa!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterWasPlayingMText:
	.string "Grandpa, here I\n"
	.string "am! I was playing"
	.string "\pwith the CAPTAIN\n"
	.string "and this guy!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterWasPlayingFText:
	.string "Grandpa, here I\n"
	.string "am! I was playing"
	.string "\pwith the CAPTAIN\n"
	.string "and this big girl!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaGranddaughterHadFunText:
	.string "I had lots of fun\n"
	.string "playing!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinSeenText:
	.string "Hey, kid! Want to\n"
	.string "battle with me?$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinBeatenText:
	.string "You're strong!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmColinAfterBattleText:
	.string "You're traveling\n"
	.string "all alone?"
	.string "\pIsn't your mom\n"
	.string "worried?$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1SeenText:
	.string "You think I'm a\n"
	.string "baby?\l"
	.string "That's not fair!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1BeatenText:
	.string "Oh! We lost!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg1AfterBattleText:
	.string "Baby is a rude\n"
	.string "name to call us\l"
	.string "girls!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2SeenText:
	.string "I'm not a baby!"
	.string "\pThat's not nice to\n"
	.string "say to a lady!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2BeatenText:
	.string "Oh! We lost!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_TwinsMegandpeg2AfterBattleText:
	.string "Sometimes, kids\n"
	.string "are smarter than\l"
	.string "grown-ups!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneySeenText:
	.string "Ssh! My brain is\n"
	.string "picking up radio\l"
	.string "signals!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneyBeatenText:
	.string "…I hear some-\n"
	.string "thing!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PsychicRodneyAfterBattleText:
	.string "I get it. You can\n"
	.string "hear JOHTO's radio\l"
	.string "on the FAST SHIP.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremySeenText:
	.string "What do you think?\n"
	.string "My POKéMON are\l"
	.string "beautiful, yes?$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremyBeatenText:
	.string "Oh, no! My beauti-\n"
	.string "ful POKéMON!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanmJeremyAfterBattleText:
	.string "I must go to the\n"
	.string "POKéMON SALON and\l"
	.string "fix them up nice!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaSeenText:
	.string "I'm going to shop\n"
	.string "at the DEPT.STORE\l"
	.string "and then…$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaBeatenText:
	.string "What was I going\n"
	.string "to do?$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_PokefanfGeorgiaAfterBattleText:
	.string "Oh, yes! I have to\n"
	.string "get my POKéMON out\l"
	.string "of DAY-CARE!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnSeenText:
	.string "What kinds of POKé\n"
	.string "BALLS do you have\l"
	.string "with you?$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnBeatenText:
	.string "Wait! Stop! Don't!\n"
	.string "Please!$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SupernerdShawnAfterBattleText:
	.string "You should use the\n"
	.string "right BALLS to fit\l"
	.string "the situation.$"

FastShipCabins_SE_SSE_CaptainsCabin_Johto_SSAquaHasArrivedVermilionText:
	.string "FAST SHIP S.S.AQUA\n"
	.string "has arrived in\l"
	.string "VERMILION CITY.$"
