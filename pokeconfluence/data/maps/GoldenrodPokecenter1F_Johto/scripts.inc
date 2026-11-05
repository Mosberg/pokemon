GoldenrodPokecenter1F_Johto_MapScripts::
	.byte 0

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FNurseScript_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FNurseScript

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FGameboyKidScript_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FGameboyKidScript

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FLassScript_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FLassScript

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneLeft_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneLeft

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneRight_Entry::
	lockall
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneRight


GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_GOLDENROD_CITY
	goto Johto_Std_PokecenterNurseScript

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneLeft:
	goto_if_unset FLAG_SYS_GAME_CLEAR, GoldenrodPokecenter1F_Johto_GSBallEnd
	goto_if_set FLAG_JOHTO_CAN_GIVE_GS_BALL_TO_KURT, GoldenrodPokecenter1F_Johto_GSBallEnd
	goto_if_set FLAG_JOHTO_GAVE_GS_BALL_TO_KURT, GoldenrodPokecenter1F_Johto_GSBallEnd
	checkitem ITEM_GS_BALL, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodPokecenter1F_Johto_GSBallEnd
	message GoldenrodPokecenter1F_Johto_LinkReceptionistPleaseAcceptGSBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GS_BALL
	setflag FLAG_JOHTO_CAN_GIVE_GS_BALL_TO_KURT
	message GoldenrodPokecenter1F_Johto_LinkReceptionistPleaseDoComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
GoldenrodPokecenter1F_Johto_GSBallEnd:
	setvar VAR_JOHTO_SCENE_GOLDENROD_POKECENTER_1F, 1
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneRight:
	goto GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneLeft

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FGameboyKidScript:
	faceplayer
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FLassScript:
	faceplayer
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF:
	faceplayer
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText
	waitmessage
	waitbuttonpress
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FAskGiveAwayAnEonMailText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoEonMail
	removeitem ITEM_DREAM_MAIL
	goto_if_eq VAR_RESULT, 0, GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoEonMail
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText
	waitmessage
	waitbuttonpress
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFThisIsForYouText
	waitmessage
	waitbuttonpress
	giveitem ITEM_REVIVE
	goto_if_eq VAR_RESULT, 0, GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoRoom
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoEonMail:
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFTooBadText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoRoom:
	additem ITEM_DREAM_MAIL
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFAnotherTimeThenText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FGameboyKidText:
	.string "The COLOSSEUM\n"
	.string "upstairs is for\l"
	.string "link battles."
	.string "\pBattle records are\n"
	.string "posted on the"
	.string "\pwall, so I can't\n"
	.string "afford to lose.$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FLassText:
	.string "A higher level\n"
	.string "POKéMON doesn't\l"
	.string "always win."
	.string "\pAfter all, it may\n"
	.string "have a type dis-\l"
	.string "advantage."
	.string "\pI don't think\n"
	.string "there is a single"
	.string "\pPOKéMON that is\n"
	.string "the toughest.$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText:
	.string "Oh my, your pack\n"
	.string "looks so heavy!"
	.string "\pOh! Do you happen\n"
	.string "to have something\l"
	.string "named EON MAIL?"
	.string "\pMy daughter is\n"
	.string "after one."
	.string "\pYou can part with\n"
	.string "one, can't you?$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FAskGiveAwayAnEonMailText:
	.string "Give away an EON\n"
	.string "MAIL?$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFThisIsForYouText:
	.string "Oh, that's great!\n"
	.string "Thank you, honey!"
	.string "\pHere, this is for\n"
	.string "you in return!$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText:
	.string "My daughter will\n"
	.string "be delighted!$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFTooBadText:
	.string "Oh? You don't have\n"
	.string "one? Too bad.$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFAnotherTimeThenText:
	.string "Oh… Well, another\n"
	.string "time, then.$"

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText:
	.string "{PLAYER} gave away\n"
	.string "the EON MAIL.$"

GoldenrodPokecenter1F_Johto_LinkReceptionistPleaseAcceptGSBallText:
	.string "{PLAYER}, isn't it?\n"
	.string "Congratulations!\p"
	.string "As a special deal,\n"
	.string "a GS BALL has been\l"
	.string "sent just for you!\p"
	.string "Please accept it!$"

GoldenrodPokecenter1F_Johto_LinkReceptionistPleaseDoComeAgainText:
	.string "Please do come\n"
	.string "again!$"
