CianwoodPhotoStudio_Johto_MapScripts::
	.byte 0

CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruScript_Entry::
	lockall
	goto CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruScript


CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruScript:
	faceplayer
	message CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_Question
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruScript_Refused
	message CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_Yes
	waitmessage
	waitbuttonpress
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruScript_Refused:
	message CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_No
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_Question:
	.string "You have magnifi-\n"
	.string "cent POKéMON with\l"
	.string "you."
	.string "\pHow about a photo\n"
	.string "for a souvenir?$"

CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_Yes:
	.string "OK! Big smile now!$"

CianwoodPhotoStudio_Johto_CianwoodPhotoStudioFishingGuruText_No:
	.string "Oh, that's too\n"
	.string "bad. I thought it"
	.string "\pwould be a great\n"
	.string "memento…$"
