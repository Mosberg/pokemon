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
	call_if_unset FLAG_CONFLUENCE_GOT_FIELD_KIT, Confluence_EventScript_GiveFieldKit
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestKanto, CONFLUENCE_DEST_KANTO
	dynmultipush Confluence_Text_DestJohto, CONFLUENCE_DEST_JOHTO
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Briefing, 5
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianFromKanto::
	lock
	faceplayer
	msgbox Confluence_Text_MeridianWelcome, MSGBOX_DEFAULT
	special ConfluenceCheckMeridianAccess
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_MeridianLocked
	call_if_unset FLAG_CONFLUENCE_GOT_FIELD_KIT, Confluence_EventScript_GiveFieldKit
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestJohto, CONFLUENCE_DEST_JOHTO
	dynmultipush Confluence_Text_DestHoenn, CONFLUENCE_DEST_HOENN
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Briefing, 5
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianFromJohto::
	lock
	faceplayer
	msgbox Confluence_Text_MeridianWelcome, MSGBOX_DEFAULT
	special ConfluenceCheckMeridianAccess
	goto_if_eq VAR_RESULT, FALSE, Confluence_EventScript_MeridianLocked
	call_if_unset FLAG_CONFLUENCE_GOT_FIELD_KIT, Confluence_EventScript_GiveFieldKit
	msgbox Confluence_Text_MeridianWhere, MSGBOX_DEFAULT
	dynmultipush Confluence_Text_DestKanto, CONFLUENCE_DEST_KANTO
	dynmultipush Confluence_Text_DestHoenn, CONFLUENCE_DEST_HOENN
	dynmultipush Confluence_Text_Report, 3
	dynmultipush Confluence_Text_Briefing, 5
	dynmultipush Confluence_Text_Cancel, 4
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto Confluence_EventScript_MeridianHandleChoice

Confluence_EventScript_MeridianHandleChoice::
	switch VAR_RESULT
	case CONFLUENCE_DEST_KANTO, Confluence_EventScript_RideToKanto
	case CONFLUENCE_DEST_JOHTO, Confluence_EventScript_RideToJohto
	case CONFLUENCE_DEST_HOENN, Confluence_EventScript_RideToHoenn
	case 3, Confluence_EventScript_ShowReport
	case 5, Confluence_EventScript_CrisisBriefing
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
	call Confluence_EventScript_TransitRide
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	setflag FLAG_WORLD_MAP_VERMILION_CITY
	warp MAP_VERMILION_CITY, 23, 33
	waitstate
	end

Confluence_EventScript_RideToJohto::
	call Confluence_EventScript_TransitRide
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	warp MAP_JOHTO_OLIVINE_CITY, 15, 22
	waitstate
	end

Confluence_EventScript_RideToHoenn::
	call Confluence_EventScript_TransitRide
	setflag FLAG_CONFLUENCE_MERIDIAN_USED
	setflag FLAG_VISITED_SLATEPORT_CITY
	warp MAP_SLATEPORT_CITY_HARBOR, 12, 13
	waitstate
	end

Confluence_EventScript_TransitRide::
	msgbox Confluence_Text_AllAboard, MSGBOX_DEFAULT
	closemessage
	playse SE_TRUCK_MOVE
	fadescreenspeed FADE_TO_BLACK, 4
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 0  @ horizontal pan
	setvar VAR_0x8006, 6  @ num shakes
	setvar VAR_0x8007, 6  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	playse SE_TRUCK_STOP
	return

Confluence_EventScript_GiveFieldKit::
	msgbox Confluence_Text_FieldKitIntro, MSGBOX_DEFAULT
	giveitem ITEM_FIELD_KIT
	setflag FLAG_CONFLUENCE_GOT_FIELD_KIT
	return

@ ---- The Convergence Crisis ---------------------------------------------------------------------------------------
@ Briefing from the conductor, three syndicate enforcers (one per terminal) and the chairman.

Confluence_EventScript_CrisisBriefing::
	goto_if_set FLAG_CONFLUENCE_CRISIS_RESOLVED, Confluence_EventScript_CrisisResolved
	special ConfluenceCountBadges
	goto_if_lt VAR_RESULT, CONFLUENCE_SYNDICATE_MIN_BADGES, Confluence_EventScript_CrisisStart
	goto_if_defeated TRAINER_SYNDICATE_KANTO, Confluence_EventScript_CrisisCheckJohto
	goto Confluence_EventScript_CrisisEnforcers

Confluence_EventScript_CrisisCheckJohto::
	goto_if_defeated TRAINER_SYNDICATE_JOHTO, Confluence_EventScript_CrisisCheckHoenn
	goto Confluence_EventScript_CrisisEnforcers

Confluence_EventScript_CrisisCheckHoenn::
	goto_if_defeated TRAINER_SYNDICATE_HOENN, Confluence_EventScript_CrisisChairman
	goto Confluence_EventScript_CrisisEnforcers

Confluence_EventScript_CrisisStart::
	msgbox Confluence_Text_CrisisStart, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_CrisisEnforcers::
	msgbox Confluence_Text_CrisisEnforcers, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_CrisisResolved::
	msgbox Confluence_Text_CrisisResolved, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_CrisisChairman::
	special ConfluenceCountBadges
	goto_if_lt VAR_RESULT, CONFLUENCE_CHAIRMAN_MIN_BADGES, Confluence_EventScript_CrisisChairmanLater
	msgbox Confluence_Text_CrisisChairmanAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Confluence_EventScript_ApexDecline
	closemessage
	special HealPlayerParty
	trainerbattle_no_intro TRAINER_SYNDICATE_CHAIRMAN, Confluence_Text_ChairmanDefeat
	setflag FLAG_CONFLUENCE_CRISIS_RESOLVED
	msgbox Confluence_Text_ChairmanAfter, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 5
	release
	end

Confluence_EventScript_CrisisChairmanLater::
	msgbox Confluence_Text_CrisisChairmanLater, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerKanto::
	lock
	faceplayer
	goto_if_defeated TRAINER_SYNDICATE_KANTO, Confluence_EventScript_EnforcerKantoDone
	special ConfluenceCountBadges
	goto_if_lt VAR_RESULT, CONFLUENCE_SYNDICATE_MIN_BADGES, Confluence_EventScript_EnforcerTooEarly
	msgbox Confluence_Text_EnforcerKantoIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SYNDICATE_KANTO, Confluence_Text_EnforcerKantoDefeat
	msgbox Confluence_Text_EnforcerKantoDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerKantoDone::
	msgbox Confluence_Text_EnforcerKantoDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerJohto::
	lock
	faceplayer
	goto_if_defeated TRAINER_SYNDICATE_JOHTO, Confluence_EventScript_EnforcerJohtoDone
	special ConfluenceCountBadges
	goto_if_lt VAR_RESULT, CONFLUENCE_SYNDICATE_MIN_BADGES, Confluence_EventScript_EnforcerTooEarly
	msgbox Confluence_Text_EnforcerJohtoIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SYNDICATE_JOHTO, Confluence_Text_EnforcerJohtoDefeat
	msgbox Confluence_Text_EnforcerJohtoDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerJohtoDone::
	msgbox Confluence_Text_EnforcerJohtoDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerHoenn::
	lock
	faceplayer
	goto_if_defeated TRAINER_SYNDICATE_HOENN, Confluence_EventScript_EnforcerHoennDone
	special ConfluenceCountBadges
	goto_if_lt VAR_RESULT, CONFLUENCE_SYNDICATE_MIN_BADGES, Confluence_EventScript_EnforcerTooEarly
	msgbox Confluence_Text_EnforcerHoennIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SYNDICATE_HOENN, Confluence_Text_EnforcerHoennDefeat
	msgbox Confluence_Text_EnforcerHoennDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerHoennDone::
	msgbox Confluence_Text_EnforcerHoennDone, MSGBOX_DEFAULT
	release
	end

Confluence_EventScript_EnforcerTooEarly::
	msgbox Confluence_Text_EnforcerTooEarly, MSGBOX_DEFAULT
	release
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
	closemessage
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
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

Confluence_Text_Briefing:
	.string "Crisis briefing$"

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

Confluence_Text_FieldKitIntro:
	.string "Before you go: MERIDIAN HOLDINGS asks\n"
	.string "all travellers to take this FIELD KIT.\p"
	.string "With it, your team can use CUT, SURF,\n"
	.string "STRENGTH and the other field moves\l"
	.string "without knowing the HM moves.$"

Confluence_Text_CrisisStart:
	.string "Since the line opened, the sky has been\n"
	.string "wrong everywhere: storms over KANTO,\l"
	.string "fog over JOHTO, downpours over HOENN.\p"
	.string "The legends are restless. Calm and\n"
	.string "catch them and the weather will clear.\p"
	.string "And I hear MERIDIAN HOLDINGS has people\n"
	.string "at every terminal. Come back with more\l"
	.string "BADGES and ask again.$"

Confluence_Text_CrisisEnforcers:
	.string "MERIDIAN HOLDINGS is drawing power out\n"
	.string "of the leylines, and the old gangs run\l"
	.string "its security.\p"
	.string "Their enforcers wait at the terminals:\n"
	.string "one at VERMILION, one at OLIVINE and\l"
	.string "one at SLATEPORT.\p"
	.string "Beat all three to reach the CHAIRMAN.$"

Confluence_Text_CrisisChairmanAsk:
	.string "All three enforcers are down.\p"
	.string "The CHAIRMAN of MERIDIAN HOLDINGS is\n"
	.string "on the line, and he wants you.\p"
	.string "Take the call?$"

Confluence_Text_CrisisChairmanLater:
	.string "The CHAIRMAN wants to meet you, but he\n"
	.string "only receives trainers with at least\l"
	.string "12 BADGES.$"

Confluence_Text_CrisisResolved:
	.string "The leylines are steady again and the\n"
	.string "sky has cleared across all three\l"
	.string "regions.\p"
	.string "Thanks to you, the MERIDIAN LINE runs\n"
	.string "for travellers again.$"

Confluence_Text_ChairmanDefeat:
	.string "The leylines... were never ours.$"

Confluence_Text_ChairmanAfter:
	.string "CHAIRMAN: Without the siphons, the\n"
	.string "legends will settle.\p"
	.string "Take this. It's the least the company\n"
	.string "owes you.$"

Confluence_Text_EnforcerTooEarly:
	.string "Move along, kid. MERIDIAN HOLDINGS\n"
	.string "has no business with you yet.$"

Confluence_Text_EnforcerKantoIntro:
	.string "You're the one asking about the\n"
	.string "leylines? TEAM ROCKET never really\l"
	.string "disbanded, we just changed employers.$"

Confluence_Text_EnforcerKantoDefeat:
	.string "The boss won't like this.$"

Confluence_Text_EnforcerKantoDone:
	.string "VESPER: Fine, you win. Go bother the\n"
	.string "others.$"

Confluence_Text_EnforcerJohtoIntro:
	.string "TEAM MAGMA's furnaces need power, and\n"
	.string "the leylines of JOHTO burn hot.\p"
	.string "I'm not letting a kid shut that off!$"

Confluence_Text_EnforcerJohtoDefeat:
	.string "Burned out...$"

Confluence_Text_EnforcerJohtoDone:
	.string "CINDER: The fire's gone out of me.$"

Confluence_Text_EnforcerHoennIntro:
	.string "TEAM AQUA bankrolled this line to wake\n"
	.string "the deep. Do you know what's down\l"
	.string "there? Neither do we, so let's find\l"
	.string "out by beating you first.$"

Confluence_Text_EnforcerHoennDefeat:
	.string "Washed out...$"

Confluence_Text_EnforcerHoennDone:
	.string "TIDE: The CHAIRMAN is waiting for you.\n"
	.string "Ask the conductor.$"
