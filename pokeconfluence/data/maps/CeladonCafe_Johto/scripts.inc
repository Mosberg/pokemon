CeladonCafe_Johto_MapScripts::
	.byte 0

CeladonCafe_Johto_CeladonCafeChef_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeChef

CeladonCafe_Johto_CeladonCafeFisher1_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeFisher1

CeladonCafe_Johto_CeladonCafeFisher2_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeFisher2

CeladonCafe_Johto_CeladonCafeFisher3_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeFisher3

CeladonCafe_Johto_CeladonCafeTeacher_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeTeacher

CeladonCafe_Johto_EatathonContestPoster_Entry::
	lockall
	goto CeladonCafe_Johto_EatathonContestPoster

CeladonCafe_Johto_CeladonCafeTrashcan_Entry::
	lockall
	goto CeladonCafe_Johto_CeladonCafeTrashcan


CeladonCafe_Johto_CeladonCafeChef:
	faceplayer
	message CeladonCafe_Johto_ChefText_Eatathon
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCafe_Johto_CeladonCafeFisher1:
	message CeladonCafe_Johto_Fisher1Text_Snarfle
	waitmessage
	waitbuttonpress
	closemessage
	faceplayer
	message CeladonCafe_Johto_Fisher1Text_Concentration
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	releaseall
	end

CeladonCafe_Johto_CeladonCafeFisher2:
	message CeladonCafe_Johto_Fisher2Text_GulpChew
	waitmessage
	waitbuttonpress
	closemessage
	faceplayer
	message CeladonCafe_Johto_Fisher2Text_Quantity
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, Johto_Movement_Face_Right
	waitmovement 3
	releaseall
	end

CeladonCafe_Johto_CeladonCafeFisher3:
	message CeladonCafe_Johto_Fisher3Text_MunchMunch
	waitmessage
	waitbuttonpress
	closemessage
	faceplayer
	message CeladonCafe_Johto_Fisher3Text_GoldenrodIsBest
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, Johto_Movement_Face_Right
	waitmovement 4
	releaseall
	end

CeladonCafe_Johto_CeladonCafeTeacher:
	checkitem ITEM_COIN_CASE, 1
	goto_if_ne VAR_RESULT, 0, CeladonCafe_Johto_CeladonCafeTeacher_HasCoinCase
	message CeladonCafe_Johto_TeacherText_CrunchCrunch
	waitmessage
	waitbuttonpress
	closemessage
	faceplayer
	message CeladonCafe_Johto_TeacherText_NoCoinCase
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Left
	waitmovement 5
	releaseall
	end

CeladonCafe_Johto_CeladonCafeTeacher_HasCoinCase:
	message CeladonCafe_Johto_TeacherText_KeepEating
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Right
	waitmovement 5
	message CeladonCafe_Johto_TeacherText_MoreChef
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, Johto_Movement_Face_Left
	waitmovement 5
	releaseall
	end

CeladonCafe_Johto_EatathonContestPoster:
	message CeladonCafe_Johto_EatathonContestPosterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCafe_Johto_CeladonCafeTrashcan:
	goto_if_set FLAG_JOHTO_FOUND_LEFTOVERS_IN_CELADON_CAFE, CeladonCafe_Johto_CeladonCafeTrashcan_TrashEmpty
	additem ITEM_LEFTOVERS
	goto_if_eq VAR_RESULT, 0, CeladonCafe_Johto_CeladonCafeTrashcan_PackFull
	bufferitemname STR_VAR_1, ITEM_LEFTOVERS
	message CeladonCafe_Johto_FoundLeftoversText
	waitmessage
	playse SE_PIN
	waitse
	closemessage
	setflag FLAG_JOHTO_FOUND_LEFTOVERS_IN_CELADON_CAFE
	releaseall
	end

CeladonCafe_Johto_CeladonCafeTrashcan_PackFull:
	bufferitemname STR_VAR_1, ITEM_LEFTOVERS
	message CeladonCafe_Johto_FoundLeftoversText
	waitmessage
	waitbuttonpress
	message CeladonCafe_Johto_NoRoomForLeftoversText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonCafe_Johto_CeladonCafeTrashcan_TrashEmpty:
	goto Johto_Std_TrashCanScript

CeladonCafe_Johto_ChefText_Eatathon:
	.string "Hi!"
	.string "\pWe're holding an\n"
	.string "eatathon contest."
	.string "\pWe can't serve you\n"
	.string "right now. Sorry.$"

CeladonCafe_Johto_Fisher1Text_Snarfle:
	.string "…Snarfle, chew…$"

CeladonCafe_Johto_Fisher1Text_Concentration:
	.string "Don't talk to me!"
	.string "\pYou'll break my\n"
	.string "concentration!$"

CeladonCafe_Johto_Fisher2Text_GulpChew:
	.string "…Gulp… Chew…$"

CeladonCafe_Johto_Fisher2Text_Quantity:
	.string "I take quantity\n"
	.string "over quality!"
	.string "\pI'm happy when I'm\n"
	.string "full!$"

CeladonCafe_Johto_Fisher3Text_MunchMunch:
	.string "Munch, munch…$"

CeladonCafe_Johto_Fisher3Text_GoldenrodIsBest:
	.string "The food is good\n"
	.string "here, but GOLDEN-\l"
	.string "ROD has the best\l"
	.string "food anywhere.$"

CeladonCafe_Johto_TeacherText_CrunchCrunch:
	.string "Crunch… Crunch…$"

CeladonCafe_Johto_TeacherText_NoCoinCase:
	.string "Nobody here will\n"
	.string "give you a COIN"
	.string "\pCASE. You should\n"
	.string "look in JOHTO.$"

CeladonCafe_Johto_TeacherText_KeepEating:
	.string "Crunch… Crunch…"
	.string "\pI can keep eating!$"

CeladonCafe_Johto_TeacherText_MoreChef:
	.string "More, CHEF!$"

CeladonCafe_Johto_EatathonContestPosterText:
	.string "Eatathon Contest!\n"
	.string "No time limit!"
	.string "\pA battle without\n"
	.string "end! The biggest"
	.string "\pmuncher gets it\n"
	.string "all for free!$"

CeladonCafe_Johto_FoundLeftoversText:
	.string "{PLAYER} found\n"
	.string "{STR_VAR_1}!$"

CeladonCafe_Johto_NoRoomForLeftoversText:
	.string "But {PLAYER} can't\n"
	.string "hold another item…$"
