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
	@ TODO unsupported: special MonCheck
	goto Johto_EventScript_Unimplemented

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
