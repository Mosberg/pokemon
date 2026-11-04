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
	setvar VAR_RESULT, 0
	@ TODO unsupported: special BattleTowerAction
	goto Johto_EventScript_Unimplemented

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1F_GSBallSceneRight:
	setvar VAR_RESULT, 0
	@ TODO unsupported: special BattleTowerAction
	goto Johto_EventScript_Unimplemented

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
	@ TODO unsupported: takeitem EON_MAIL
	goto Johto_EventScript_Unimplemented

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanF_NoEonMail:
	message GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFTooBadText
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

GoldenrodPokecenter1F_Johto_GoldenrodPokecenter1FPokefanFTooBadText:
	.string "Oh? You don't have\n"
	.string "one? Too bad.$"
