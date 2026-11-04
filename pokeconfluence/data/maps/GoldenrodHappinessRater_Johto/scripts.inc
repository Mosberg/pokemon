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
	@ TODO unsupported: ifgreater 250 - 1, .LovesYouALot
	goto Johto_EventScript_Unimplemented

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
