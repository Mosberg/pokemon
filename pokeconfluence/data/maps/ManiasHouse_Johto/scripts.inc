ManiasHouse_Johto_MapScripts::
	.byte 0

ManiasHouse_Johto_ManiaScript_Entry::
	lockall
	goto ManiasHouse_Johto_ManiaScript


ManiasHouse_Johto_ManiaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM, ManiasHouse_Johto_ManiaScript_default_postevent
	goto_if_set FLAG_JOHTO_GOT_SHUCKIE, ManiasHouse_Johto_ManiaScript_alreadyhaveshuckie
	message ManiasHouse_Johto_ManiaText_AskLookAfterShuckle
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ManiasHouse_Johto_ManiaScript_refusetotakeshuckie
	@ TODO unsupported: special GiveShuckle
	goto Johto_EventScript_Unimplemented

ManiasHouse_Johto_ManiaScript_alreadyhaveshuckie:
	goto_if_unset FLAG_JOHTO_ENGINE_GOT_SHUCKIE_TODAY, ManiasHouse_Johto_ManiaScript_returnshuckie
	message ManiasHouse_Johto_ManiaText_TakeCareOfShuckle
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaScript_refusetotakeshuckie:
	message ManiasHouse_Johto_ManiaText_IfHeComesBack
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaScript_returnshuckie:
	message ManiasHouse_Johto_ManiaText_CanIHaveMyMonBack
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, ManiasHouse_Johto_ManiaScript_refused
	@ TODO unsupported: special ReturnShuckie
	goto Johto_EventScript_Unimplemented

ManiasHouse_Johto_ManiaScript_refused:
	message ManiasHouse_Johto_ManiaText_SameAsBeingRobbed
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaScript_default_postevent:
	message ManiasHouse_Johto_ManiaText_HappinessSpeech
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaText_AskLookAfterShuckle:
	.string "I, I'm in shock!"
	.string "\pA guy about your\n"
	.string "age with piercing"
	.string "\peyes and long hair\n"
	.string "came in."
	.string "\pHe scared me into\n"
	.string "giving him my\l"
	.string "prized POKéMON!"
	.string "\pI still have one\n"
	.string "left, but what if\l"
	.string "he comes back?"
	.string "\pYou look strong.\n"
	.string "Could you look"
	.string "\pafter my POKéMON\n"
	.string "for a while?$"

ManiasHouse_Johto_ManiaText_TakeCareOfShuckle:
	.string "Oh, thank you!"
	.string "\pTake good care of\n"
	.string "it, please!$"

ManiasHouse_Johto_ManiaText_IfHeComesBack:
	.string "Oh, no… What'll\n"
	.string "I do if he comes\l"
	.string "back?$"

ManiasHouse_Johto_ManiaText_CanIHaveMyMonBack:
	.string "Hi! How's my POKé-\n"
	.string "MON?"
	.string "\pI think I'm safe\n"
	.string "now, so may I have\l"
	.string "it back?$"

ManiasHouse_Johto_ManiaText_SameAsBeingRobbed:
	.string "Oh, no, no… That's\n"
	.string "the same as being\l"
	.string "robbed.$"

ManiasHouse_Johto_ManiaText_HappinessSpeech:
	.string "For POKéMON, hap-\n"
	.string "piness is being"
	.string "\pwith a person who\n"
	.string "treats them well.$"
