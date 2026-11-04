Route35GoldenrodGate_Johto_MapScripts::
	.byte 0

Route35GoldenrodGate_Johto_RandyScript_Entry::
	lockall
	goto Route35GoldenrodGate_Johto_RandyScript

Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFScript_Entry::
	lockall
	goto Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFScript

Route35GoldenrodGate_Johto_Route35GoldenrodGateFisherScript_Entry::
	lockall
	goto Route35GoldenrodGate_Johto_Route35GoldenrodGateFisherScript


Route35GoldenrodGate_Johto_RandyScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_HP_UP_FROM_RANDY, Route35GoldenrodGate_Johto_RandyScript_gothpup
	goto_if_set FLAG_JOHTO_GAVE_KENYA, Route35GoldenrodGate_Johto_RandyScript_questcomplete
	goto_if_set FLAG_JOHTO_GOT_KENYA, Route35GoldenrodGate_Johto_RandyScript_alreadyhavekenya
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, Route35GoldenrodGate_Johto_RandyScript_refused
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyThanksText
	waitmessage
	waitbuttonpress
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 6, Route35GoldenrodGate_Johto_RandyScript_partyfull
	message Route35GoldenrodGate_Johto_Route35GoldenrodGatePlayerReceivedAMonWithMailText
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	@ TODO unsupported: givepoke SPEAROW, 10, NO_ITEM, GiftSpearowName, GiftSpearowOTName
	goto Johto_EventScript_Unimplemented

Route35GoldenrodGate_Johto_RandyScript_alreadyhavekenya:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyWeirdTreeBlockingRoadText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_RandyScript_partyfull:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyCantCarryAnotherMonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_RandyScript_refused:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyOhNeverMindThenText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_RandyScript_questcomplete:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandySomethingForYourTroubleText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, 0, Route35GoldenrodGate_Johto_RandyScript_bagfull
	setflag FLAG_JOHTO_GOT_HP_UP_FROM_RANDY

Route35GoldenrodGate_Johto_RandyScript_gothpup:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyMyPalWasSnoozingRightText
	waitmessage
	waitbuttonpress

Route35GoldenrodGate_Johto_RandyScript_bagfull:
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FOUGHT_SUDOWOODO, Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFScript_FoughtSudowoodo
	message Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFScript_FoughtSudowoodo:
	message Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFText_FoughtSudowoodo
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_Route35GoldenrodGateFisherScript:
	faceplayer
	message Route35GoldenrodGate_Johto_Route35GoldenrodGateFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText:
	.string "Excuse me, kid!\n"
	.string "Can you do a guy\l"
	.string "a favor?"
	.string "\pCan you take this\n"
	.string "POKéMON with MAIL\l"
	.string "to my friend?"
	.string "\pHe's on ROUTE 31.$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyThanksText:
	.string "You will? Perfect!\n"
	.string "Thanks, kid!"
	.string "\pMy pal's a chubby\n"
	.string "guy who snoozes\l"
	.string "all the time."
	.string "\pYou'll recognize\n"
	.string "him right away!$"

Route35GoldenrodGate_Johto_Route35GoldenrodGatePlayerReceivedAMonWithMailText:
	.string "{PLAYER} received a\n"
	.string "POKéMON with MAIL.$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyWeirdTreeBlockingRoadText:
	.string "You can read it,\n"
	.string "but don't lose it!\l"
	.string "ROUTE 31!"
	.string "\pOh, yeah. There\n"
	.string "was a weird tree\l"
	.string "blocking the road."
	.string "\pI wonder if it's\n"
	.string "been cleared?$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyCantCarryAnotherMonText:
	.string "You can't carry\n"
	.string "another POKéMON…$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyOhNeverMindThenText:
	.string "Oh… Never mind,\n"
	.string "then…$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandySomethingForYourTroubleText:
	.string "Thanks, kid! You\n"
	.string "made the delivery\l"
	.string "for me!"
	.string "\pHere's something\n"
	.string "for your trouble!$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateRandyMyPalWasSnoozingRightText:
	.string "My pal was snooz-\n"
	.string "ing, right? Heh,\l"
	.string "what'd I say?$"

Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFText:
	.string "A strange tree is\n"
	.string "blocking the road."
	.string "\pIt wriggles around\n"
	.string "if you talk to it."
	.string "\pI heard it became\n"
	.string "wild when someone"
	.string "\pwatered it with a\n"
	.string "SQUIRTBOTTLE.$"

Route35GoldenrodGate_Johto_Route35GoldenrodGatePokefanFText_FoughtSudowoodo:
	.string "I like the POKéMON\n"
	.string "Lullaby they play\l"
	.string "on the radio.$"

Route35GoldenrodGate_Johto_Route35GoldenrodGateFisherText:
	.string "I wonder how many\n"
	.string "kinds of POKéMON"
	.string "\pthere are in the\n"
	.string "world."
	.string "\pThree years ago,\n"
	.string "PROF.OAK said that"
	.string "\pthere were 150\n"
	.string "different kinds.$"
