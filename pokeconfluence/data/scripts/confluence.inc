@ POKE-CONFLUENCE: the Meridian Transit line, the 24-badge circuit report and the Apex Summit on Mt. Silver.
@ Specials live in src/confluence.c, constants in include/constants/confluence.h.

@ ---- Meridian Transit ----------------------------------------------------------------------------------------------
@ One conductor per region. Each entry offers the other two regions; the line only opens after the second badge.

Confluence_EventScript_MeridianFromHoenn::
	lock
	faceplayer
	msgbox Confluence_Text_MeridianWelcome, MSGBOX_DEFAULT
	special ConfluenceCheckMeridianAccess
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_MeridianLocked
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestKanto, CONFLUENCE_DEST_KANTO
	dynmultipush Confluence_Text_DestJohto, CONFLUENCE_DEST_JOHTO
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianFromKanto::
	lock
	faceplayer
	msgbox Confluence_Text_MeridianWelcome, MSGBOX_DEFAULT
	special ConfluenceCheckMeridianAccess
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_MeridianLocked
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestJohto, CONFLUENCE_DEST_JOHTO
	dynmultipush Confluence_Text_DestHoenn, CONFLUENCE_DEST_HOENN
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianFromJohto::
	lock
	faceplayer
	msgbox Confluence_Text_MeridianWelcome, MSGBOX_DEFAULT
	special ConfluenceCheckMeridianAccess
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_MeridianLocked
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestKanto, CONFLUENCE_DEST_KANTO
	dynmultipush Confluence_Text_DestHoenn, CONFLUENCE_DEST_HOENN
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianHandleChoice::
	switch VAR_RESULT
	case CONFLUENCE_DEST_KANTO, Confluence_EventScript_RideToKanto
	case CONFLUENCE_DEST_JOHTO, Confluence_EventScript_RideToJohto
	case CONFLUENCE_DEST_HOENN, Confluence_EventScript_RideToHoenn
	case 3, Confluence_EventScript_ShowReport
	msgbox Confluence_Text_ComeBackAnytime, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_MeridianLocked::
	msgbox Confluence_Text_MeridianLocked, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_ShowReport::
	special ConfluenceBufferProgress
	msgbox Confluence_Text_ReportBody, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_RideToKanto::
	msgbox Confluence_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	setflag FLAG_WORLD_MAP_VERMILION_CITY
	warp MAP_VERMILION_CITY, 23, 33
	waitstate
	end

Confluence_EventScript_RideToJohto::
	msgbox Confluence_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	warp MAP_JOHTO_OLIVINE_CITY, 15, 22
	waitstate
	end

Confluence_EventScript_RideToHoenn::
	msgbox Confluence_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	setflag FLAG_VISITED_SLATEPORT_CITY
	warp MAP_SLATEPORT_CITY_HARBOR, 12, 13
	waitstate
	end

@ ---- Apex Summit ---------------------------------------------------------------------------------------------------
@ Four rounds in a row, healing between them. Progress is kept in the trainers' defeated flags.

Confluence_EventScript_ApexWarden::
	lock
	faceplayer
	goto_if_set FLAG_CONFLUENCE_APEX_CHAMPION, Confluence_EventScript_ApexAlreadyChampion
	special ConfluenceCheckApexEligible
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_ApexNotEligible
	goto_if_set FLAG_CONFLUENCE_APEX_UNLOCKED, Confluence_EventScript_ApexAskStart
	msgbox Confluence_Text_ApexQualified, MSGBOX_DEFAULT
	setflag FLAG_CONFLUENCE_APEX_UNLOCKED
	goto Confluence_EventScript_ApexAskStart

Confluence_EventScript_ApexNotEligible::
	special ConfluenceBufferProgress
	msgbox Confluence_Text_ApexNotEligible, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_ApexAlreadyChampion::
	msgbox Confluence_Text_ApexAlreadyChampion, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_ApexAskStart::
	msgbox Confluence_Text_ApexBegin, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Confluence_EventScript_ApexDecline
	closemessage
	goto Confluence_EventScript_ApexRound1

Confluence_EventScript_ApexDecline::
	msgbox Confluence_Text_ComeBackAnytime, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_ApexRound1::
	goto_if_defeated TRAINER_APEX_KANTO, Confluence_EventScript_ApexRound2
	msgbox Confluence_Text_ApexRound1, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_APEX_KANTO, Confluence_Text_ApexKantoDefeat
	goto Confluence_EventScript_ApexRound2

Confluence_EventScript_ApexRound2::
	goto_if_defeated TRAINER_APEX_JOHTO, Confluence_EventScript_ApexRound3
	msgbox Confluence_Text_ApexRound2, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_APEX_JOHTO, Confluence_Text_ApexJohtoDefeat
	goto Confluence_EventScript_ApexRound3

Confluence_EventScript_ApexRound3::
	goto_if_defeated TRAINER_APEX_HOENN, Confluence_EventScript_ApexRound4
	msgbox Confluence_Text_ApexRound3, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_APEX_HOENN, Confluence_Text_ApexHoennDefeat
	goto Confluence_EventScript_ApexRound4

Confluence_EventScript_ApexRound4::
	goto_if_defeated TRAINER_APEX_CHAMPION, Confluence_EventScript_ApexVictory
	msgbox Confluence_Text_ApexRound4, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_APEX_CHAMPION, Confluence_Text_ApexChampionDefeat
	goto Confluence_EventScript_ApexVictory

Confluence_EventScript_ApexVictory::
	special HealPlayerParty
	setflag FLAG_CONFLUENCE_APEX_CHAMPION
	setflag FLAG_IS_CHAMPION
	msgbox Confluence_Text_ApexVictory, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	release
	end

@ ---- Text -----------------------------------------------------------------------------------------------------------

Confluence_Text_MeridianWelcome:
	.string "Welcome to the MERIDIAN TRANSIT.\n"
	.string "The line links KANTO, JOHTO and HOENN\l"
	.string "under the sea.$"

Confluence_Text_MeridianLocked:
	.string "League rules say only trainers with at\n"
	.string "least 2 GYM BADGES may travel between\l"
	.string "regions.\p"
	.string "Come back once you've earned your\n"
	.string "second BADGE.$"

Confluence_Text_MeridianWhere:
	.string "Where would you like to go?$"

Confluence_Text_DestKanto:
	.string "Kanto$"

Confluence_Text_DestJohto:
	.string "Johto$"

Confluence_Text_DestHoenn:
	.string "Hoenn$"

Confluence_Text_Report:
	.string "Circuit report$"

Confluence_Text_Cancel:
	.string "Cancel$"

Confluence_Text_AllAboard:
	.string "All aboard the MERIDIAN LINE!$"

Confluence_Text_ComeBackAnytime:
	.string "Come back anytime!$"

Confluence_Text_ReportBody:
	.string "Circuit report:\n"
	.string "BADGES: {STR_VAR_1} of 24\l"
	.string "LEVEL CAP: {STR_VAR_2}\p"
	.string "The RESONANCE legends you've calmed:\n"
	.string "{STR_VAR_3} of 9.$"

Confluence_Text_ApexNotEligible:
	.string "This is the path to the APEX SUMMIT.\p"
	.string "Only trainers holding all 24 BADGES\n"
	.string "of the circuit may climb it.\p"
	.string "You hold {STR_VAR_1} of 24.$"

Confluence_Text_ApexQualified:
	.string "Twenty-four BADGES... You've crossed\n"
	.string "all three regions.\p"
	.string "The APEX SUMMIT is open to you.$"

Confluence_Text_ApexBegin:
	.string "Four rounds await atop MT. SILVER:\n"
	.string "three REGIONAL WARDENS and the\l"
	.string "SUMMIT CHAMPION.\p"
	.string "Your team is healed between rounds.\n"
	.string "Are you ready to begin?$"

Confluence_Text_ApexRound1:
	.string "Round 1: KESTREL, WARDEN OF KANTO!$"

Confluence_Text_ApexRound2:
	.string "Round 2: MAREN, WARDEN OF JOHTO!$"

Confluence_Text_ApexRound3:
	.string "Round 3: ORVILLE, WARDEN OF HOENN!$"

Confluence_Text_ApexRound4:
	.string "Final round: the SUMMIT CHAMPION!$"

Confluence_Text_ApexKantoDefeat:
	.string "Kanto's winds bow to you.$"

Confluence_Text_ApexJohtoDefeat:
	.string "Johto's towers ring for you.$"

Confluence_Text_ApexHoennDefeat:
	.string "Hoenn's seas part for you.$"

Confluence_Text_ApexChampionDefeat:
	.string "...$"

Confluence_Text_ApexVictory:
	.string "You stand above three regions.\p"
	.string "The APEX SUMMIT is yours, and the\n"
	.string "level limits no longer bind you.\p"
	.string "Take this as a token of the circuit.$"

Confluence_Text_ApexAlreadyChampion:
	.string "The APEX SUMMIT CHAMPION!\n"
	.string "The mountain remembers you.$"
