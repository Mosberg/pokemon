VermilionFishingSpeechHouse_Johto_MapScripts::
	.byte 0

VermilionFishingSpeechHouse_Johto_FishingDude_Entry::
	lockall
	goto VermilionFishingSpeechHouse_Johto_FishingDude

VermilionFishingSpeechHouse_Johto_FishingDudesHousePhoto_Entry::
	lockall
	goto VermilionFishingSpeechHouse_Johto_FishingDudesHousePhoto


VermilionFishingSpeechHouse_Johto_FishingDude:
	faceplayer
	message VermilionFishingSpeechHouse_Johto_FishingDudeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionFishingSpeechHouse_Johto_FishingDudesHousePhoto:
	message VermilionFishingSpeechHouse_Johto_FishingDudesHousePhotoText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

VermilionFishingSpeechHouse_Johto_FishingDudeText:
	.string "I am the FISHING\n"
	.string "DUDE, the elder of\l"
	.string "the FISHING BROS."
	.string "\pHave you met the\n"
	.string "FISHING GURU at\l"
	.string "LAKE OF RAGE?"
	.string "\pHe dreams about\n"
	.string "seeing the world's\l"
	.string "greatest MAGIKARP."
	.string "\pIf you don't mind,\n"
	.string "could you show him"
	.string "\pany MAGIKARP you\n"
	.string "catch?"
	.string "\pWho knows, you may\n"
	.string "catch the MAGIKARP\l"
	.string "of his dreams.$"

VermilionFishingSpeechHouse_Johto_FishingDudesHousePhotoText:
	.string "It's a photo of\n"
	.string "people fishing…"
	.string "\pThey're having a\n"
	.string "great time…$"
