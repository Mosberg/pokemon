OlivineLighthouse1F_Johto_MapScripts::
	.byte 0

OlivineLighthouse1F_Johto_OlivineLighthouse1FSailorScript_Entry::
	lockall
	goto OlivineLighthouse1F_Johto_OlivineLighthouse1FSailorScript

OlivineLighthouse1F_Johto_OlivineLighthouse1FPokefanFScript_Entry::
	lockall
	goto OlivineLighthouse1F_Johto_OlivineLighthouse1FPokefanFScript


OlivineLighthouse1F_Johto_OlivineLighthouse1FSailorScript:
	faceplayer
	message OlivineLighthouse1F_Johto_OlivineLighthouse1FSailorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse1F_Johto_OlivineLighthouse1FPokefanFScript:
	faceplayer
	message OlivineLighthouse1F_Johto_OlivineLighthouse1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivineLighthouse1F_Johto_OlivineLighthouse1FSailorText:
	.string "People train at\n"
	.string "this LIGHTHOUSE."
	.string "\pIt's not easy to\n"
	.string "climb because of\l"
	.string "all the trainers.$"

OlivineLighthouse1F_Johto_OlivineLighthouse1FPokefanFText:
	.string "In the past, POKé-\n"
	.string "MON used to light"
	.string "\pthe sea around\n"
	.string "OLIVINE at night."
	.string "\pThe LIGHTHOUSE was\n"
	.string "made in honor of\l"
	.string "those POKéMON.$"
