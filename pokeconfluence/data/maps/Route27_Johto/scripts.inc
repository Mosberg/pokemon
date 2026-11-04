Route27_Johto_MapScripts::
	.byte 0

Route27_Johto_Route27TMSolarbeam_Entry::
	lockall
	goto Route27_Johto_Route27TMSolarbeam

Route27_Johto_Route27RareCandy_Entry::
	lockall
	goto Route27_Johto_Route27RareCandy

Route27_Johto_Route27FisherScript_Entry::
	lockall
	goto Route27_Johto_Route27FisherScript

Route27_Johto_TohjoFallsSign_Entry::
	lockall
	goto Route27_Johto_TohjoFallsSign

Route27_Johto_FirstStepIntoKantoLeftScene_Entry::
	lockall
	goto Route27_Johto_FirstStepIntoKantoLeftScene

Route27_Johto_FirstStepIntoKantoRightScene_Entry::
	lockall
	goto Route27_Johto_FirstStepIntoKantoRightScene


Route27_Johto_FirstStepIntoKantoLeftScene:
	applymovement 9, Johto_Movement_Face_Left
	waitmovement 9
	applymovement 9, Johto_Movement_Emote_exclamation_mark
	waitmovement 9
	applymovement 9, Route27_Johto_Route27FisherStepLeftTwiceMovement
	waitmovement 9
	goto Route27_Johto_FirstStepIntoKantoScene_Continue

Route27_Johto_FirstStepIntoKantoRightScene:
	applymovement 9, Johto_Movement_Face_Left
	waitmovement 9
	applymovement 9, Johto_Movement_Emote_exclamation_mark
	waitmovement 9
	applymovement 9, Route27_Johto_Route27FisherStepLeftOnceMovement
	waitmovement 9

Route27_Johto_FirstStepIntoKantoScene_Continue:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message Route27_Johto_Route27FisherHeyText
	waitmessage
	waitbuttonpress
	message Route27_Johto_Route27FisherText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_ROUTE_27, 1
	releaseall
	end

Route27_Johto_Route27FisherScript:
	faceplayer
	message Route27_Johto_Route27FisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_TrainerPsychicGilbert::
	trainerbattle_single TRAINER_JOHTO_PSYCHIC_T_GILBERT, Route27_Johto_PsychicGilbertSeenText, Route27_Johto_PsychicGilbertBeatenText
	setflag FLAG_JOHTO_BEAT_PSYCHIC_GILBERT
	lock
	faceplayer
	goto Route27_Johto_TrainerPsychicGilbert_Script

Route27_Johto_TrainerPsychicGilbert_Script:
	message Route27_Johto_PsychicGilbertAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_TrainerBirdKeeperJose2::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_JOSE2, Route27_Johto_BirdKeeperJose2SeenText, Route27_Johto_BirdKeeperJose2BeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_JOSE2
	lock
	faceplayer
	goto Route27_Johto_TrainerBirdKeeperJose2_Script

Route27_Johto_TrainerBirdKeeperJose2_Script:
	goto_if_set FLAG_JOHTO_ENGINE_JOSE_READY_FOR_REMATCH, Route27_Johto_TrainerBirdKeeperJose2_WantsBattle
	goto_if_set FLAG_JOHTO_ENGINE_JOSE_HAS_STAR_PIECE, Route27_Johto_TrainerBirdKeeperJose2_HasStarPiece
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route27_Johto_TrainerBirdKeeperJose2_NumberAccepted
	goto_if_set FLAG_JOHTO_JOSE_ASKED_FOR_PHONE_NUMBER, Route27_Johto_TrainerBirdKeeperJose2_AskedAlready
	message Route27_Johto_BirdKeeperJose2AfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_JOSE_ASKED_FOR_PHONE_NUMBER
	call Route27_Johto_TrainerBirdKeeperJose2_AskNumber1_Sub
	goto Route27_Johto_TrainerBirdKeeperJose2_AskForNumber

Route27_Johto_TrainerBirdKeeperJose2_AskedAlready:
	call Route27_Johto_TrainerBirdKeeperJose2_AskNumber2_Sub

Route27_Johto_TrainerBirdKeeperJose2_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route27_Johto_TrainerBirdKeeperJose2_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route27_Johto_TrainerBirdKeeperJose2_NumberDeclined
	call Route27_Johto_TrainerBirdKeeperJose2_RegisteredNumber_Sub
	goto Route27_Johto_TrainerBirdKeeperJose2_NumberAccepted

Route27_Johto_TrainerBirdKeeperJose2_WantsBattle:
	call Route27_Johto_TrainerBirdKeeperJose2_Rematch_Sub
	@ TODO unsupported: readmem wJoseFightCount
	goto Johto_EventScript_Unimplemented

Route27_Johto_TrainerBirdKeeperJose2_HasStarPiece:
	call Route27_Johto_TrainerBirdKeeperJose2_Gift_Sub
	giveitem ITEM_STAR_PIECE
	goto_if_eq VAR_RESULT, 0, Route27_Johto_TrainerBirdKeeperJose2_NoRoom
	clearflag FLAG_JOHTO_ENGINE_JOSE_HAS_STAR_PIECE
	goto Route27_Johto_TrainerBirdKeeperJose2_NumberAccepted

Route27_Johto_TrainerBirdKeeperJose2_NoRoom:
	goto Route27_Johto_TrainerBirdKeeperJose2_PackFull

Route27_Johto_TrainerBirdKeeperJose2_NumberAccepted:
	goto Johto_Std_NumberAcceptedMScript

Route27_Johto_TrainerBirdKeeperJose2_NumberDeclined:
	goto Johto_Std_NumberDeclinedMScript

Route27_Johto_TrainerBirdKeeperJose2_PhoneFull:
	goto Johto_Std_PhoneFullMScript

Route27_Johto_TrainerBirdKeeperJose2_PackFull:
	goto Johto_Std_PackFullMScript

Route27_Johto_TrainerCooltrainermBlake::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_BLAKE, Route27_Johto_CooltrainermBlakeSeenText, Route27_Johto_CooltrainermBlakeBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_BLAKE
	lock
	faceplayer
	goto Route27_Johto_TrainerCooltrainermBlake_Script

Route27_Johto_TrainerCooltrainermBlake_Script:
	message Route27_Johto_CooltrainermBlakeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_TrainerCooltrainermBrian::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_BRIAN, Route27_Johto_CooltrainermBrianSeenText, Route27_Johto_CooltrainermBrianBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_BRIAN
	lock
	faceplayer
	goto Route27_Johto_TrainerCooltrainermBrian_Script

Route27_Johto_TrainerCooltrainermBrian_Script:
	message Route27_Johto_CooltrainermBrianAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_TrainerCooltrainerfReena::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_REENA1, Route27_Johto_CooltrainerfReenaSeenText, Route27_Johto_CooltrainerfReenaBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_REENA
	lock
	faceplayer
	goto Route27_Johto_TrainerCooltrainerfReena_Script

Route27_Johto_TrainerCooltrainerfReena_Script:
	goto_if_set FLAG_JOHTO_ENGINE_REENA_READY_FOR_REMATCH, Route27_Johto_TrainerCooltrainerfReena_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, Route27_Johto_TrainerCooltrainerfReena_NumberAccepted
	goto_if_set FLAG_JOHTO_REENA_ASKED_FOR_PHONE_NUMBER, Route27_Johto_TrainerCooltrainerfReena_AskedAlready
	message Route27_Johto_CooltrainerfReenaAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_REENA_ASKED_FOR_PHONE_NUMBER
	call Route27_Johto_TrainerCooltrainerfReena_AskNumber1_Sub
	goto Route27_Johto_TrainerCooltrainerfReena_AskForNumber

Route27_Johto_TrainerCooltrainerfReena_AskedAlready:
	call Route27_Johto_TrainerCooltrainerfReena_AskNumber2_Sub

Route27_Johto_TrainerCooltrainerfReena_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, Route27_Johto_TrainerCooltrainerfReena_PhoneFull
	goto_if_eq VAR_RESULT, 2, Route27_Johto_TrainerCooltrainerfReena_NumberDeclined
	call Route27_Johto_TrainerCooltrainerfReena_RegisteredNumber_Sub
	goto Route27_Johto_TrainerCooltrainerfReena_NumberAccepted

Route27_Johto_TrainerCooltrainerfReena_WantsBattle:
	call Route27_Johto_TrainerCooltrainerfReena_Rematch_Sub
	@ TODO unsupported: readmem wReenaFightCount
	goto Johto_EventScript_Unimplemented

Route27_Johto_TrainerCooltrainerfReena_NumberAccepted:
	goto Johto_Std_NumberAcceptedFScript

Route27_Johto_TrainerCooltrainerfReena_NumberDeclined:
	goto Johto_Std_NumberDeclinedFScript

Route27_Johto_TrainerCooltrainerfReena_PhoneFull:
	goto Johto_Std_PhoneFullFScript

Route27_Johto_TrainerCooltrainerfMegan::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_MEGAN, Route27_Johto_CooltrainerfMeganSeenText, Route27_Johto_CooltrainerfMeganBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_MEGAN
	lock
	faceplayer
	goto Route27_Johto_TrainerCooltrainerfMegan_Script

Route27_Johto_TrainerCooltrainerfMegan_Script:
	message Route27_Johto_CooltrainerfMeganAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_TohjoFallsSign:
	message Route27_Johto_TohjoFallsSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route27_Johto_Route27TMSolarbeam:
	finditem ITEM_TM_SOLAR_BEAM
	releaseall
	end

Route27_Johto_Route27RareCandy:
	finditem ITEM_RARE_CANDY
	releaseall
	end

Route27_Johto_TrainerBirdKeeperJose2_AskNumber1_Sub:
	goto Johto_Std_AskNumber1MScript_Sub

Route27_Johto_TrainerBirdKeeperJose2_AskNumber2_Sub:
	goto Johto_Std_AskNumber2MScript_Sub

Route27_Johto_TrainerBirdKeeperJose2_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberMScript_Sub

Route27_Johto_TrainerBirdKeeperJose2_Rematch_Sub:
	goto Johto_Std_RematchMScript_Sub

Route27_Johto_TrainerBirdKeeperJose2_Gift_Sub:
	goto Johto_Std_GiftMScript_Sub

Route27_Johto_TrainerCooltrainerfReena_AskNumber1_Sub:
	goto Johto_Std_AskNumber1FScript_Sub

Route27_Johto_TrainerCooltrainerfReena_AskNumber2_Sub:
	goto Johto_Std_AskNumber2FScript_Sub

Route27_Johto_TrainerCooltrainerfReena_RegisteredNumber_Sub:
	goto Johto_Std_RegisteredNumberFScript_Sub

Route27_Johto_TrainerCooltrainerfReena_Rematch_Sub:
	goto Johto_Std_RematchFScript_Sub

Route27_Johto_Route27FisherStepLeftTwiceMovement:
	walk_left
	walk_left
	step_end

Route27_Johto_Route27FisherStepLeftOnceMovement:
	walk_left
	step_end

Route27_Johto_Route27FisherHeyText:
	.string "Hey!$"

Route27_Johto_Route27FisherText:
	.string "Do you know what\n"
	.string "you just did?"
	.string "\pYou've taken your\n"
	.string "first step into\l"
	.string "KANTO."
	.string "\pCheck your POKé-\n"
	.string "GEAR MAP and see.$"

Route27_Johto_CooltrainermBlakeSeenText:
	.string "You look pretty\n"
	.string "strong.\l"
	.string "Let me battle you!$"

Route27_Johto_CooltrainermBlakeBeatenText:
	.string "Yow!$"

Route27_Johto_CooltrainermBlakeAfterBattleText:
	.string "If you prevail on\n"
	.string "this harsh trek,"
	.string "\pthe truth will be\n"
	.string "revealed!"
	.string "\pHeh, sorry, I just\n"
	.string "wanted to say\l"
	.string "something cool.$"

Route27_Johto_CooltrainermBrianSeenText:
	.string "Hm? You're good,\n"
	.string "aren't you?$"

Route27_Johto_CooltrainermBrianBeatenText:
	.string "Just as I thought!$"

Route27_Johto_CooltrainermBrianAfterBattleText:
	.string "A good trainer can\n"
	.string "recognize other\l"
	.string "good trainers.$"

Route27_Johto_CooltrainerfReenaSeenText:
	.string "You shouldn't\n"
	.string "underestimate the"
	.string "\pwild POKéMON in\n"
	.string "these parts.$"

Route27_Johto_CooltrainerfReenaBeatenText:
	.string "Oh! You're much\n"
	.string "too strong!$"

Route27_Johto_CooltrainerfReenaAfterBattleText:
	.string "You're just a kid,\n"
	.string "but you're not to"
	.string "\pbe underestimated\n"
	.string "either.$"

Route27_Johto_CooltrainerfMeganSeenText:
	.string "It's rare to see\n"
	.string "anyone come here."
	.string "\pAre you training\n"
	.string "on your own?$"

Route27_Johto_CooltrainerfMeganBeatenText:
	.string "Oh! You're really\n"
	.string "strong!$"

Route27_Johto_CooltrainerfMeganAfterBattleText:
	.string "I'm checking out\n"
	.string "pre- and post-\l"
	.string "evolution POKéMON."
	.string "\pEvolution really\n"
	.string "does make POKéMON\l"
	.string "stronger."
	.string "\pBut evolved forms\n"
	.string "also learn moves\l"
	.string "later on.$"

Route27_Johto_PsychicGilbertSeenText:
	.string "Don't say a thing!"
	.string "\pLet me guess what\n"
	.string "you're thinking."
	.string "\pMmmmmmm…"
	.string "\pI got it! You're\n"
	.string "on the POKéMON\l"
	.string "LEAGUE challenge!$"

Route27_Johto_PsychicGilbertBeatenText:
	.string "You're too much!$"

Route27_Johto_PsychicGilbertAfterBattleText:
	.string "With your skills,\n"
	.string "you'll do well at\l"
	.string "the LEAGUE."
	.string "\pThat's what my\n"
	.string "premonition says.$"

Route27_Johto_BirdKeeperJose2SeenText:
	.string "Tweet! Tweet!\n"
	.string "Tetweet!$"

Route27_Johto_BirdKeeperJose2BeatenText:
	.string "Tweet!$"

Route27_Johto_BirdKeeperJose2AfterBattleText:
	.string "BIRD KEEPERS like\n"
	.string "me mimic bird"
	.string "\pwhistles to com-\n"
	.string "mand POKéMON.$"

Route27_Johto_TohjoFallsSignText:
	.string "TOHJO FALLS"
	.string "\pTHE LINK BETWEEN\n"
	.string "KANTO AND JOHTO$"
