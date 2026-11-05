GoldenrodHappinessRater_Johto_MapScripts::
	.byte 0

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_Entry::
	lockall
	goto GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterPokefanMScript_Entry::
	lockall
	goto GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterPokefanMScript

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTwinScript_Entry::
	lockall
	goto GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTwinScript

GoldenrodHappinessRater_Johto_HappinessRatersHouseBookshelf_Entry::
	lockall
	goto GoldenrodHappinessRater_Johto_HappinessRatersHouseBookshelf

GoldenrodHappinessRater_Johto_HappinessRatersHouseRadio_Entry::
	lockall
	goto GoldenrodHappinessRater_Johto_HappinessRatersHouseRadio


GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript:
	faceplayer
	special JohtoGetFirstMonHappiness
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherText
	waitmessage
	waitbuttonpress
	goto_if_gt VAR_RESULT, 249, GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_LovesYouALot
	goto_if_gt VAR_RESULT, 199, GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_ReallyTrustsYou
	goto_if_gt VAR_RESULT, 149, GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_SortOfHappy
	goto_if_gt VAR_RESULT, 99, GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_QuiteCute
	goto_if_gt VAR_RESULT, 49, GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_NotUsedToYou
	goto GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_LooksMean

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_LovesYouALot:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_LovesYouALot
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_ReallyTrustsYou:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_ReallyTrustsYou
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_SortOfHappy:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_SortOfHappy
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_QuiteCute:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_QuiteCute
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_NotUsedToYou:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_NotUsedToYou
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherScript_LooksMean:
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_LooksMean
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterPokefanMScript:
	faceplayer
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTwinScript:
	faceplayer
	message GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTwinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodHappinessRater_Johto_HappinessRatersHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

GoldenrodHappinessRater_Johto_HappinessRatersHouseRadio:
	goto Johto_Std_Radio2Script

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTeacherText:
	.string "If you treat your\n"
	.string "POKéMON nicely,"
	.string "\pthey will love you\n"
	.string "in return."
	.string "\pOh? Let me see\n"
	.string "your {STR_VAR_1}…$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_LovesYouALot:
	.string "It looks really\n"
	.string "happy! It must\l"
	.string "love you a lot.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_ReallyTrustsYou:
	.string "I get the feeling\n"
	.string "that it really\l"
	.string "trusts you.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_SortOfHappy:
	.string "It's friendly to-\n"
	.string "ward you. It looks\l"
	.string "sort of happy.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_QuiteCute:
	.string "It's quite cute.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_NotUsedToYou:
	.string "You should treat\n"
	.string "it better. It's\l"
	.string "not used to you.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRatingText_LooksMean:
	.string "It doesn't seem to\n"
	.string "like you at all.\l"
	.string "It looks mean.$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterPokefanMText:
	.string "I keep losing in\n"
	.string "battles, and my"
	.string "\pPOKéMON end up\n"
	.string "fainting…"
	.string "\pMaybe that's why\n"
	.string "my POKéMON don't\l"
	.string "like me much…$"

GoldenrodHappinessRater_Johto_GoldenrodHappinessRaterTwinText:
	.string "When I use an item\n"
	.string "on my POKéMON, it\l"
	.string "acts really glad!$"
