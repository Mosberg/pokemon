FuchsiaPokecenter1F_Johto_MapScripts::
	.byte 0

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FNurseScript_Entry::
	lockall
	goto FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FNurseScript

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerMScript_Entry::
	lockall
	goto FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerMScript

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerFScript_Entry::
	lockall
	goto FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerFScript

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorScript_Entry::
	lockall
	goto FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorScript


FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_FUCHSIA_CITY
	goto Johto_Std_PokecenterNurseScript

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerMScript:
	faceplayer
	message FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerFScript:
	faceplayer
	message FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorScript:
	faceplayer
	message FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorSpinMovement
	waitmovement 4
	faceplayer
	message FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorSpinMovement
	waitmovement 4
	faceplayer
	releaseall
	end

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorSpinMovement:
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerMText:
	.string "Hey! You have a\n"
	.string "brand new kind of\l"
	.string "POKéDEX."
	.string "\pDid PROF.OAK give\n"
	.string "that to you?$"

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FCooltrainerFText:
	.string "I got quite a\n"
	.string "shock at the GYM."
	.string "\pThere were all\n"
	.string "these girls who\l"
	.string "looked identical.$"

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorText1:
	.string "I'm JANINE! Hocus-\n"
	.string "pocus… Poof!$"

FuchsiaPokecenter1F_Johto_FuchsiaPokecenter1FJanineImpersonatorText2:
	.string "See? I look just\n"
	.string "like her now!$"
