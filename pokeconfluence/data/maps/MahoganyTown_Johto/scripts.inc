MahoganyTown_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MahoganyTown_Johto_OnTransition
	.byte 0

MahoganyTown_Johto_OnTransition:
	call MahoganyTown_Johto_MahoganyTownFlypointCallback_Cb
	end

MahoganyTown_Johto_MahoganyTownPokefanMScript_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownPokefanMScript

MahoganyTown_Johto_MahoganyTownGrampsScript_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownGrampsScript

MahoganyTown_Johto_MahoganyTownFisherScript_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownFisherScript

MahoganyTown_Johto_MahoganyTownLassScript_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownLassScript

MahoganyTown_Johto_MahoganyTownSign_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownSign

MahoganyTown_Johto_MahoganyTownRagecandybarSign_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownRagecandybarSign

MahoganyTown_Johto_MahoganyGymSign_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyGymSign

MahoganyTown_Johto_MahoganyTownPokecenterSign_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownPokecenterSign

MahoganyTown_Johto_MahoganyTownTryARageCandyBarScript_Entry::
	lockall
	goto MahoganyTown_Johto_MahoganyTownTryARageCandyBarScript


MahoganyTown_Johto_MahoganyTownTryARageCandyBarScript:
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	applymovement 1, MahoganyTown_Johto_MahoganyTownRageCandyBarMerchantBlocksYouMovement
	waitmovement 1
	applymovement 1, MahoganyTown_Johto_MahoganyTownPlayerStepLeftMovement
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Johto_MahoganyTownPlayerStepLeftMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	call MahoganyTown_Johto_RageCandyBarMerchantScript_Sub
	applymovement 1, MahoganyTown_Johto_MahoganyTownRageCandyBarMerchantReturnsMovement
	waitmovement 1
	releaseall
	end

MahoganyTown_Johto_MahoganyTownPokefanMScript:
	faceplayer

MahoganyTown_Johto_RageCandyBarMerchantScript:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, MahoganyTown_Johto_RageCandyBarMerchantScript_ClearedRocketHideout
	call MahoganyTown_Johto_RageCandyBarMerchantScript_SellRageCandyBars_Sub
	releaseall
	end

MahoganyTown_Johto_RageCandyBarMerchantScript_ClearedRocketHideout:
	message MahoganyTown_Johto_RageCandyBarMerchantSoldOutText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownGrampsScript:
	faceplayer
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, MahoganyTown_Johto_MahoganyTownGrampsScript_ClearedRocketHideout
	message MahoganyTown_Johto_MahoganyTownGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownGrampsScript_ClearedRocketHideout:
	message MahoganyTown_Johto_MahoganyTownGrampsText_ClearedRocketHideout
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownFisherScript:
	faceplayer
	message MahoganyTown_Johto_MahoganyTownFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownLassScript:
	faceplayer
	message MahoganyTown_Johto_MahoganyTownLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownSign:
	message MahoganyTown_Johto_MahoganyTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownRagecandybarSign:
	message MahoganyTown_Johto_MahoganyTownRagecandybarSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyGymSign:
	message MahoganyTown_Johto_MahoganyGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MahoganyTown_Johto_MahoganyTownPokecenterSign:
	goto Johto_Std_PokecenterSignScript

MahoganyTown_Johto_RageCandyBarMerchantScript_Sub:
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, MahoganyTown_Johto_RageCandyBarMerchantScript_ClearedRocketHideout_Sub
	call MahoganyTown_Johto_RageCandyBarMerchantScript_SellRageCandyBars_Sub
	return

MahoganyTown_Johto_RageCandyBarMerchantScript_ClearedRocketHideout_Sub:
	message MahoganyTown_Johto_RageCandyBarMerchantSoldOutText
	waitmessage
	waitbuttonpress
	closemessage
	return

MahoganyTown_Johto_RageCandyBarMerchantScript_SellRageCandyBars_Sub:
	message MahoganyTown_Johto_RageCandyBarMerchantTryOneText
	waitmessage
	@ TODO unsupported: special PlaceMoneyTopRight
	return

MahoganyTown_Johto_MahoganyTownFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_MAHOGANY
	return

MahoganyTown_Johto_MahoganyTownPlayerStepLeftMovement:
	walk_left
	step_end

MahoganyTown_Johto_MahoganyTownRageCandyBarMerchantBlocksYouMovement:
	walk_right
	walk_down
	face_left
	step_end

MahoganyTown_Johto_MahoganyTownRageCandyBarMerchantReturnsMovement:
	walk_up
	face_down
	step_end

MahoganyTown_Johto_RageCandyBarMerchantTryOneText:
	.string "(text not converted)$"

MahoganyTown_Johto_RageCandyBarMerchantSoldOutText:
	.string "RAGECANDYBAR's\n"
	.string "sold out."
	.string "\pI'm packing up.\n"
	.string "Don't bother me,\l"
	.string "kiddo.$"

MahoganyTown_Johto_MahoganyTownGrampsText:
	.string "Are you off to see\n"
	.string "the GYARADOS ram-\l"
	.string "page at the LAKE?$"

MahoganyTown_Johto_MahoganyTownGrampsText_ClearedRocketHideout:
	.string "MAGIKARP have\n"
	.string "returned to LAKE\l"
	.string "OF RAGE."
	.string "\pThat should be\n"
	.string "good news for the\l"
	.string "anglers there.$"

MahoganyTown_Johto_MahoganyTownFisherText:
	.string "Since you came\n"
	.string "this far, take the"
	.string "\ptime to do some\n"
	.string "sightseeing."
	.string "\pYou should head\n"
	.string "north and check"
	.string "\pout LAKE OF RAGE\n"
	.string "right now.$"

MahoganyTown_Johto_MahoganyTownLassText:
	.string "Visit Grandma's\n"
	.string "shop. She sells"
	.string "\pstuff that nobody\n"
	.string "else has.$"

MahoganyTown_Johto_MahoganyTownSignText:
	.string "MAHOGANY TOWN"
	.string "\pWelcome to the\n"
	.string "Home of the Ninja$"

MahoganyTown_Johto_MahoganyTownRagecandybarSignText:
	.string "While visiting\n"
	.string "MAHOGANY TOWN, try\l"
	.string "a RAGECANDYBAR!$"

MahoganyTown_Johto_MahoganyGymSignText:
	.string "MAHOGANY TOWN\n"
	.string "POKéMON GYM\l"
	.string "LEADER: PRYCE"
	.string "\pThe Teacher of\n"
	.string "Winter's Harshness$"
