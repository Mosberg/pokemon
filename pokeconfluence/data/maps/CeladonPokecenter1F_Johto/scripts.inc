CeladonPokecenter1F_Johto_MapScripts::
	.byte 0

CeladonPokecenter1F_Johto_CeladonPokecenter1FNurseScript_Entry::
	lockall
	goto CeladonPokecenter1F_Johto_CeladonPokecenter1FNurseScript

CeladonPokecenter1F_Johto_CeladonPokecenter1FGentlemanScript_Entry::
	lockall
	goto CeladonPokecenter1F_Johto_CeladonPokecenter1FGentlemanScript

CeladonPokecenter1F_Johto_CeladonPokecenter1FPharmacistScript_Entry::
	lockall
	goto CeladonPokecenter1F_Johto_CeladonPokecenter1FPharmacistScript

CeladonPokecenter1F_Johto_CeladonPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto CeladonPokecenter1F_Johto_CeladonPokecenter1FCooltrainerFScript

CeladonPokecenter1F_Johto_CeladonEusine_Entry::
	lockall
	goto CeladonPokecenter1F_Johto_CeladonEusine


CeladonPokecenter1F_Johto_CeladonPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_CELADON_CITY
	goto Johto_Std_PokecenterNurseScript

CeladonPokecenter1F_Johto_CeladonPokecenter1FGentlemanScript:
	goto Johto_Std_HappinessCheckScript

CeladonPokecenter1F_Johto_CeladonPokecenter1FCooltrainerFScript:
	faceplayer
	message CeladonPokecenter1F_Johto_CeladonPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonPokecenter1F_Johto_CeladonPokecenter1FPharmacistScript:
	faceplayer
	message CeladonPokecenter1F_Johto_CeladonPokecenter1FPharmacistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonPokecenter1F_Johto_CeladonEusine:
	faceplayer
	message CeladonPokecenter1F_Johto_CeladonEusineText1
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, SPECIES_SUICUNE
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, 0, CeladonPokecenter1F_Johto_CeladonEusine_NoSuicune
	goto_if_set FLAG_JOHTO_FOUGHT_SUICUNE, CeladonPokecenter1F_Johto_CeladonEusine_HoOh
	message CeladonPokecenter1F_Johto_NoBeastsText
	waitmessage
	waitbuttonpress

CeladonPokecenter1F_Johto_CeladonEusine_NoSuicune:
	closemessage
	releaseall
	end

CeladonPokecenter1F_Johto_CeladonEusine_HoOh:
	message CeladonPokecenter1F_Johto_EusineLeavesCeladonText
	waitmessage
	waitbuttonpress
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_NORTH, CeladonPokecenter1F_Johto_CeladonEusine_Location1
	applymovement 5, CeladonPokecenter1F_Johto_CeladonEusine_Movement1
	waitmovement 5
	goto CeladonPokecenter1F_Johto_CeladonEusine_Continue

CeladonPokecenter1F_Johto_CeladonEusine_Location1:
	applymovement 5, CeladonPokecenter1F_Johto_CeladonEusine_Movement2
	waitmovement 5

CeladonPokecenter1F_Johto_CeladonEusine_Continue:
	removeobject 5
	playse SE_EXIT
	waitse
	releaseall
	end

CeladonPokecenter1F_Johto_CeladonEusine_Movement2:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeladonPokecenter1F_Johto_CeladonEusine_Movement1:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeladonPokecenter1F_Johto_CeladonPokecenter1FCooltrainerFText:
	.string "ERIKA is a master\n"
	.string "of grass POKéMON."
	.string "\pShe'll make you\n"
	.string "pay if you don't\l"
	.string "watch yourself.$"

CeladonPokecenter1F_Johto_CeladonPokecenter1FPharmacistText:
	.string "TEAM ROCKET's\n"
	.string "hideout is in the"
	.string "\pbasement of the\n"
	.string "GAME CORNER."
	.string "\pOh, wait. That was\n"
	.string "three years ago.$"

CeladonPokecenter1F_Johto_CeladonEusineText1:
	.string "EUSINE: Hi!"
	.string "\pI'm back visiting\n"
	.string "my hometown."
	.string "\pIt's been quite a\n"
	.string "while.$"

CeladonPokecenter1F_Johto_EusineLeavesCeladonText:
	.string "{PLAYER}, have you\n"
	.string "heard?"
	.string "\pThere have been\n"
	.string "fresh rumors of a"
	.string "\prainbow-colored\n"
	.string "POKéMON appearing\l"
	.string "at TIN TOWER."
	.string "\pI've just had my\n"
	.string "party healed, so"
	.string "\pnow I'm headed to\n"
	.string "ECRUTEAK."
	.string "\pI'll be seeing\n"
	.string "you, {PLAYER}!$"

CeladonPokecenter1F_Johto_NoBeastsText:
	.string "Oh, by the way,\n"
	.string "{PLAYER}."
	.string "\pHave you caught\n"
	.string "the legendary"
	.string "\pPOKéMON RAIKOU and\n"
	.string "ENTEI?"
	.string "\p………"
	.string "\pOkay…"
	.string "\pIf you catch even\n"
	.string "one, I hope that\l"
	.string "you'll inform me."
	.string "\pI'm counting on\n"
	.string "you, {PLAYER}!$"
