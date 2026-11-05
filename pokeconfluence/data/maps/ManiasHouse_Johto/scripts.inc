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
	givemon SPECIES_SHUCKLE, 15, ITEM_ORAN_BERRY
	goto_if_eq VAR_RESULT, 0, ManiasHouse_Johto_ManiaScript_partyfull
	message ManiasHouse_Johto_ManiaText_TakeCareOfShuckle
	waitmessage
	waitbuttonpress
	waitse
	message ManiasHouse_Johto_ManiaText_GotShuckle
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	closemessage
	setflag FLAG_JOHTO_GOT_SHUCKIE
	releaseall
	end

ManiasHouse_Johto_ManiaScript_alreadyhaveshuckie:
	goto_if_unset FLAG_JOHTO_ENGINE_GOT_SHUCKIE_TODAY, ManiasHouse_Johto_ManiaScript_returnshuckie
	message ManiasHouse_Johto_ManiaText_TakeCareOfShuckle
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaScript_partyfull:
	message ManiasHouse_Johto_ManiaText_PartyFull
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
	setvar VAR_0x8004, SPECIES_SHUCKLE
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, 0, ManiasHouse_Johto_ManiaScript_wrong
	goto_if_eq VAR_RESULT, 1, ManiasHouse_Johto_ManiaScript_refused
	goto_if_eq VAR_RESULT, 3, ManiasHouse_Johto_ManiaScript_superhappy
	goto_if_eq VAR_RESULT, 4, ManiasHouse_Johto_ManiaScript_default_postevent
	message ManiasHouse_Johto_ManiaText_ThankYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM
	releaseall
	end

ManiasHouse_Johto_ManiaScript_wrong:
	message ManiasHouse_Johto_ManiaText_ShuckleNotThere
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ManiasHouse_Johto_ManiaScript_superhappy:
	message ManiasHouse_Johto_ManiaText_ShuckleLikesYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM
	releaseall
	end

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

ManiasHouse_Johto_ManiaText_GotShuckle:
	.string "{PLAYER} received a\n"
	.string "POKéMON.$"

ManiasHouse_Johto_ManiaText_PartyFull:
	.string "Your POKéMON party\n"
	.string "is full.$"

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

ManiasHouse_Johto_ManiaText_ThankYou:
	.string "Thank you!$"

ManiasHouse_Johto_ManiaText_ShuckleNotThere:
	.string "Hey, you don't\n"
	.string "have my POKéMON\l"
	.string "with you.$"

ManiasHouse_Johto_ManiaText_ShuckleLikesYou:
	.string "My POKéMON has\n"
	.string "come to like you."
	.string "\pAll right, you\n"
	.string "should keep it."
	.string "\pBut promise to\n"
	.string "be good to it!$"

ManiasHouse_Johto_ManiaText_SameAsBeingRobbed:
	.string "Oh, no, no… That's\n"
	.string "the same as being\l"
	.string "robbed.$"

ManiasHouse_Johto_ManiaText_HappinessSpeech:
	.string "For POKéMON, hap-\n"
	.string "piness is being"
	.string "\pwith a person who\n"
	.string "treats them well.$"
