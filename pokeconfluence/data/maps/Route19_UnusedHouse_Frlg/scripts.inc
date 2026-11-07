@ POKE-CONFLUENCE: Authentic Yellow Route 19 Beach House & Surfing Pikachu Scripts
Route19_UnusedHouse_Frlg_MapScripts::
	.byte 0

Route19_UnusedHouse_EventScript_SurfinDude::
	lock
	faceplayer
	special CheckSurfingPikachuInParty
	goto_if_eq VAR_RESULT, FALSE, Route19_UnusedHouse_EventScript_SurfinDudeNoSurfPika
	goto_if_set FLAG_MET_SURFIN_DUDE, Route19_UnusedHouse_EventScript_SurfinDudeSubsequent
	setflag FLAG_MET_SURFIN_DUDE
	msgbox Route19_UnusedHouse_Text_SurfinDudeFirstTime, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route19_UnusedHouse_EventScript_LaunchMinigame
	msgbox Route19_UnusedHouse_Text_SurfinDudeRefused, MSGBOX_DEFAULT
	release
	end

Route19_UnusedHouse_EventScript_SurfinDudeSubsequent::
	msgbox Route19_UnusedHouse_Text_SurfinDudeWannaSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route19_UnusedHouse_EventScript_LaunchMinigame
	msgbox Route19_UnusedHouse_Text_SurfinDudeRefused, MSGBOX_DEFAULT
	release
	end

Route19_UnusedHouse_EventScript_SurfinDudeNoSurfPika::
	msgbox Route19_UnusedHouse_Text_SurfinDudeDogsBurgers, MSGBOX_DEFAULT
	release
	end

Route19_UnusedHouse_EventScript_LaunchMinigame::
	msgbox Route19_UnusedHouse_Text_SurfsUp, MSGBOX_DEFAULT
	closemessage
	special StartSurfingPikachuMinigameSpecial
	release
	end

Route19_UnusedHouse_EventScript_Pikachu::
	lock
	faceplayer
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox Route19_UnusedHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route19_UnusedHouse_EventScript_Poster1::
	msgbox Route19_UnusedHouse_Text_Poster1, MSGBOX_SIGN
	end

Route19_UnusedHouse_EventScript_Poster2::
	msgbox Route19_UnusedHouse_Text_Poster2, MSGBOX_SIGN
	end

Route19_UnusedHouse_EventScript_Poster3::
	msgbox Route19_UnusedHouse_Text_Poster3, MSGBOX_SIGN
	end

Route19_UnusedHouse_EventScript_Printer::
	lockall
	special GetSurfingPikachuScores
	goto_if_eq VAR_RESULT, FALSE, Route19_UnusedHouse_EventScript_PrinterNoScore
	buffernumberstring STR_VAR_1, VAR_SURFING_PIKACHU_HIGH_SCORE
	buffernumberstring STR_VAR_2, VAR_SURFING_PIKACHU_RADNESS
	msgbox Route19_UnusedHouse_Text_PrinterHighScore, MSGBOX_DEFAULT
	releaseall
	end

Route19_UnusedHouse_EventScript_PrinterNoScore::
	msgbox Route19_UnusedHouse_Text_PrinterNoScore, MSGBOX_DEFAULT
	releaseall
	end

Route19_UnusedHouse_Text_SurfinDudeDogsBurgers:
	.string "SURFIN' DUDE: Dogs and burgers\n"
	.string "on special today!\p"
	.string "If you had a PIKACHU that knew\n"
	.string "how to SURF, we could hit the waves\l"
	.string "together!$"

Route19_UnusedHouse_Text_SurfinDudeFirstTime:
	.string "SURFIN' DUDE: Whoa!\p"
	.string "Your PIKACHU knows how to SURF!\n"
	.string "So, I'm not alone…\p"
	.string "Great! You earned the right to SURF\n"
	.string "with the DUDE!\p"
	.string "Give it a go?$"

Route19_UnusedHouse_Text_SurfinDudeWannaSurf:
	.string "SURFIN' DUDE: Wanna go SURF?$"

Route19_UnusedHouse_Text_SurfinDudeRefused:
	.string "SURFIN' DUDE: Come SURF anytime,\n"
	.string "my friend!$"

Route19_UnusedHouse_Text_SurfsUp:
	.string "SURFIN' DUDE: All right!\n"
	.string "Surf's up! Let's hit the big waves!$"

Route19_UnusedHouse_Text_Pikachu:
	.string "PIKACHU: Pika-pikaa!\p"
	.string "It's balancing skillfully on a miniature\n"
	.string "surfboard!$"

Route19_UnusedHouse_Text_Poster1:
	.string "SURFIN' DUDE's scribbles…\p"
	.string "“When I shoot the tube,\n"
	.string "the tunes hit the groove!”\l"
	.string "-- 30 years of waves! SURFIN' DUDE$"

Route19_UnusedHouse_Text_Poster2:
	.string "SURFING TIP 1!\p"
	.string "After flips in the air, line the board\n"
	.string "up with the wave slope for a clean\l"
	.string "landing and maximum speed!$"

Route19_UnusedHouse_Text_Poster3:
	.string "SURFING TIP 2!\p"
	.string "Pulling flips in a jump is totally rad!\n"
	.string "The sea unites all in surfdom!$"

Route19_UnusedHouse_Text_PrinterHighScore:
	.string "SUMMER BEACH HOUSE PRINTER\p"
	.string "SURFING PIKACHU HIGH SCORE:\n"
	.string "{STR_VAR_1} PTS!\p"
	.string "RADNESS RECORD:\n"
	.string "{STR_VAR_2} PTS!\p"
	.string "RADICAL SURFING!$"

Route19_UnusedHouse_Text_PrinterNoScore:
	.string "SUMMER BEACH HOUSE PRINTER\p"
	.string "No high score recorded yet!\p"
	.string "Hit the waves with a SURFING PIKACHU\n"
	.string "to set a new beach record!$"
