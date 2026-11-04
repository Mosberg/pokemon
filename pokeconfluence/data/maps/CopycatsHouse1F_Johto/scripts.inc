CopycatsHouse1F_Johto_MapScripts::
	.byte 0

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanMScript_Entry::
	lockall
	goto CopycatsHouse1F_Johto_CopycatsHouse1FPokefanMScript

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFScript_Entry::
	lockall
	goto CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFScript

CopycatsHouse1F_Johto_CopycatsHouse1FBlisseyScript_Entry::
	lockall
	goto CopycatsHouse1F_Johto_CopycatsHouse1FBlisseyScript


CopycatsHouse1F_Johto_CopycatsHouse1FPokefanMScript:
	faceplayer
	message CopycatsHouse1F_Johto_CopycatsHouse1FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFScript_ReturnedMachinePart
	message CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFScript_ReturnedMachinePart:
	message CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse1F_Johto_CopycatsHouse1FBlisseyScript:
	message CopycatsHouse1F_Johto_CopycatsHouse1FBlisseyText
	waitmessage
	playmoncry SPECIES_BLISSEY, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanMText:
	.string "My daughter likes\n"
	.string "to mimic people."
	.string "\pHer mimicry has\n"
	.string "earned her the"
	.string "\pnickname COPYCAT\n"
	.string "around here.$"

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFText:
	.string "My daughter is so\n"
	.string "self-centered…"
	.string "\pShe only has a few\n"
	.string "friends.$"

CopycatsHouse1F_Johto_CopycatsHouse1FPokefanFText_ReturnedMachinePart:
	.string "She recently lost\n"
	.string "the POKé DOLL that"
	.string "\pa boy gave her\n"
	.string "three years ago."
	.string "\pEver since then,\n"
	.string "she's gotten even\l"
	.string "better at mimicry…$"

CopycatsHouse1F_Johto_CopycatsHouse1FBlisseyText:
	.string "BLISSEY: Bliisii!$"
