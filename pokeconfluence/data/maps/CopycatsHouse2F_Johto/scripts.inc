CopycatsHouse2F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CopycatsHouse2F_Johto_OnTransition
	.byte 0

CopycatsHouse2F_Johto_OnTransition:
	call CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Cb
	end

CopycatsHouse2F_Johto_Copycat_Entry::
	lockall
	goto CopycatsHouse2F_Johto_Copycat

CopycatsHouse2F_Johto_CopycatsDodrio_Entry::
	lockall
	goto CopycatsHouse2F_Johto_CopycatsDodrio

CopycatsHouse2F_Johto_CopycatsHouse2FDoll_Entry::
	lockall
	goto CopycatsHouse2F_Johto_CopycatsHouse2FDoll

CopycatsHouse2F_Johto_CopycatsHouse2FBookshelf_Entry::
	lockall
	goto CopycatsHouse2F_Johto_CopycatsHouse2FBookshelf


CopycatsHouse2F_Johto_Copycat:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_PASS_FROM_COPYCAT, CopycatsHouse2F_Johto_Copycat_GotPass
	goto_if_set FLAG_JOHTO_RETURNED_LOST_ITEM_TO_COPYCAT, CopycatsHouse2F_Johto_Copycat_TryGivePassAgain
	checkitem ITEM_LOST_ITEM, 1
	goto_if_ne VAR_RESULT, 0, CopycatsHouse2F_Johto_Copycat_ReturnLostItem
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_Default_Female_1
	applymovement 1, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 1
	faceplayer
	goto CopycatsHouse2F_Johto_Copycat_Default_Merge_1

CopycatsHouse2F_Johto_Copycat_Default_Female_1:
	applymovement 6, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 6
	faceplayer

CopycatsHouse2F_Johto_Copycat_Default_Merge_1:
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, CopycatsHouse2F_Johto_Copycat_TalkAboutLostItem
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_Default_Female_2a
	message CopycatsHouse2F_Johto_CopycatText_Male_1
	waitmessage
	goto CopycatsHouse2F_Johto_Copycat_Default_Merge_2a

CopycatsHouse2F_Johto_Copycat_Default_Female_2a:
	message CopycatsHouse2F_Johto_CopycatText_Female_1
	waitmessage

CopycatsHouse2F_Johto_Copycat_Default_Merge_2a:
	waitbuttonpress
	closemessage
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_Default_Female_3a
	applymovement 1, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 1
	goto CopycatsHouse2F_Johto_Copycat_Default_Merge_3a

CopycatsHouse2F_Johto_Copycat_Default_Female_3a:
	applymovement 6, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 6

CopycatsHouse2F_Johto_Copycat_Default_Merge_3a:
	faceplayer
	message CopycatsHouse2F_Johto_CopycatText_QuickMimicking
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse2F_Johto_Copycat_TalkAboutLostItem:
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_Default_Female_2b
	message CopycatsHouse2F_Johto_CopycatText_Male_2
	waitmessage
	goto CopycatsHouse2F_Johto_Copycat_Default_Merge_2b

CopycatsHouse2F_Johto_Copycat_Default_Female_2b:
	message CopycatsHouse2F_Johto_CopycatText_Female_2
	waitmessage

CopycatsHouse2F_Johto_Copycat_Default_Merge_2b:
	waitbuttonpress
	closemessage
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_Default_Female_3b
	applymovement 1, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 1
	goto CopycatsHouse2F_Johto_Copycat_Default_Merge_3b

CopycatsHouse2F_Johto_Copycat_Default_Female_3b:
	applymovement 6, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 6

CopycatsHouse2F_Johto_Copycat_Default_Merge_3b:
	faceplayer
	message CopycatsHouse2F_Johto_CopycatText_Worried
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_MET_COPYCAT_FOUND_OUT_ABOUT_LOST_ITEM
	releaseall
	end

CopycatsHouse2F_Johto_Copycat_ReturnLostItem:
	message CopycatsHouse2F_Johto_CopycatText_GiveDoll
	waitmessage
	waitbuttonpress
	removeitem ITEM_LOST_ITEM
	setflag FLAG_JOHTO_RETURNED_LOST_ITEM_TO_COPYCAT
	clearflag FLAG_JOHTO_COPYCATS_HOUSE_2F_DOLL
	addobject 3
	goto CopycatsHouse2F_Johto_Copycat_GivePass

CopycatsHouse2F_Johto_Copycat_TryGivePassAgain:

CopycatsHouse2F_Johto_Copycat_GivePass:
	message CopycatsHouse2F_Johto_CopycatText_GivePass
	waitmessage
	waitbuttonpress
	giveitem ITEM_PASS
	goto_if_eq VAR_RESULT, 0, CopycatsHouse2F_Johto_Copycat_Cancel
	setflag FLAG_JOHTO_GOT_PASS_FROM_COPYCAT
	message CopycatsHouse2F_Johto_CopycatText_ExplainPass
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse2F_Johto_Copycat_GotPass:
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_GotPass_Female_1
	applymovement 1, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 1
	faceplayer
	goto CopycatsHouse2F_Johto_Copycat_GotPass_Merge_1

CopycatsHouse2F_Johto_Copycat_GotPass_Female_1:
	applymovement 6, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 6
	faceplayer

CopycatsHouse2F_Johto_Copycat_GotPass_Merge_1:
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_GotPass_Female_2
	message CopycatsHouse2F_Johto_CopycatText_Male_3
	waitmessage
	goto CopycatsHouse2F_Johto_Copycat_GotPass_Merge_2

CopycatsHouse2F_Johto_Copycat_GotPass_Female_2:
	message CopycatsHouse2F_Johto_CopycatText_Female_3
	waitmessage

CopycatsHouse2F_Johto_Copycat_GotPass_Merge_2:
	waitbuttonpress
	closemessage
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_Copycat_GotPass_Female_3
	applymovement 1, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 1
	goto CopycatsHouse2F_Johto_Copycat_GotPass_Merge_3

CopycatsHouse2F_Johto_Copycat_GotPass_Female_3:
	applymovement 6, CopycatsHouse2F_Johto_CopycatSpinAroundMovementData
	waitmovement 6

CopycatsHouse2F_Johto_Copycat_GotPass_Merge_3:
	faceplayer
	message CopycatsHouse2F_Johto_CopycatText_ItsAScream
	waitmessage
	waitbuttonpress

CopycatsHouse2F_Johto_Copycat_Cancel:
	closemessage
	releaseall
	end

CopycatsHouse2F_Johto_CopycatsDodrio:
	message CopycatsHouse2F_Johto_CopycatsDodrioText1
	waitmessage
	playmoncry SPECIES_DODRIO, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	message CopycatsHouse2F_Johto_CopycatsDodrioText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse2F_Johto_CopycatsHouse2FDoll:
	message CopycatsHouse2F_Johto_CopycatsHouse2FDollText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CopycatsHouse2F_Johto_CopycatsHouse2FBookshelf:
	goto Johto_Std_PictureBookshelfScript

CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_PLAYER_IS_FEMALE, CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Female_Cb
	setflag FLAG_JOHTO_COPYCAT_2
	clearflag FLAG_JOHTO_COPYCAT_1
	goto CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Done_Cb

CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Female_Cb:
	setflag FLAG_JOHTO_COPYCAT_1
	clearflag FLAG_JOHTO_COPYCAT_2

CopycatsHouse2F_Johto_CopycatsHouse2FWhichGenderCallback_Done_Cb:
	return

CopycatsHouse2F_Johto_CopycatSpinAroundMovementData:
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

CopycatsHouse2F_Johto_CopycatText_Male_1:
	.string "{PLAYER}: Hi! Do\n"
	.string "you like POKéMON?"
	.string "\p{PLAYER}: Uh, no, I\n"
	.string "just asked you."
	.string "\p{PLAYER}: Huh?\n"
	.string "You're strange!$"

CopycatsHouse2F_Johto_CopycatText_QuickMimicking:
	.string "COPYCAT: Hmm?\n"
	.string "Quit mimicking?"
	.string "\pBut that's my\n"
	.string "favorite hobby!$"

CopycatsHouse2F_Johto_CopycatText_Male_2:
	.string "{PLAYER}: Hi!\n"
	.string "I heard that you"
	.string "\plost your favorite\n"
	.string "POKé DOLL."
	.string "\p{PLAYER}: If I find\n"
	.string "it, you'll give me\l"
	.string "a rail PASS?"
	.string "\p{PLAYER}: I'll go\n"
	.string "find it for you."
	.string "\pYou think you lost\n"
	.string "it when you went\l"
	.string "to VERMILION CITY?$"

CopycatsHouse2F_Johto_CopycatText_Worried:
	.string "COPYCAT: Pardon?"
	.string "\pI shouldn't decide\n"
	.string "what you should\l"
	.string "do?"
	.string "\pBut I'm really\n"
	.string "worried… What if\l"
	.string "someone finds it?$"

CopycatsHouse2F_Johto_CopycatText_GiveDoll:
	.string "COPYCAT: Yay!\n"
	.string "That's my CLEFAIRY\l"
	.string "POKé DOLL!"
	.string "\pSee the tear where\n"
	.string "the right leg is"
	.string "\psewn on? That's\n"
	.string "proof!$"

CopycatsHouse2F_Johto_CopycatText_GivePass:
	.string "OK. Here's the\n"
	.string "MAGNET TRAIN PASS\l"
	.string "like I promised!$"

CopycatsHouse2F_Johto_CopycatText_ExplainPass:
	.string "COPYCAT: That's\n"
	.string "the PASS for the\l"
	.string "MAGNET TRAIN."
	.string "\pThe rail company\n"
	.string "man gave me that"
	.string "\pwhen they tore\n"
	.string "down our old house\l"
	.string "for the STATION.$"

CopycatsHouse2F_Johto_CopycatText_Male_3:
	.string "{PLAYER}: Hi!\n"
	.string "Thanks a lot for\l"
	.string "the rail PASS!"
	.string "\p{PLAYER}: Pardon?"
	.string "\p{PLAYER}: Is it\n"
	.string "that fun to mimic\l"
	.string "my every move?$"

CopycatsHouse2F_Johto_CopycatText_ItsAScream:
	.string "COPYCAT: You bet!\n"
	.string "It's a scream!$"

CopycatsHouse2F_Johto_CopycatText_Female_1:
	.string "{PLAYER}: Hi. You\n"
	.string "must like POKéMON."
	.string "\p{PLAYER}: No, not\n"
	.string "me. I asked you."
	.string "\p{PLAYER}: Pardon?\n"
	.string "You're weird!$"

CopycatsHouse2F_Johto_CopycatText_Female_2:
	.string "{PLAYER}: Hi. Did\n"
	.string "you really lose\l"
	.string "your POKé DOLL?"
	.string "\p{PLAYER}: You'll\n"
	.string "really give me a"
	.string "\prail PASS if I\n"
	.string "find it for you?"
	.string "\p{PLAYER}: Sure,\n"
	.string "I'll look for it!"
	.string "\pYou think you lost\n"
	.string "it when you were\l"
	.string "in VERMILION?$"

CopycatsHouse2F_Johto_CopycatText_Female_3:
	.string "{PLAYER}: Thank you\n"
	.string "for the rail PASS!"
	.string "\p{PLAYER}: …Pardon?"
	.string "\p{PLAYER}: Is it\n"
	.string "really that fun to"
	.string "\pcopy what I say\n"
	.string "and do?$"

CopycatsHouse2F_Johto_CopycatsDodrioText1:
	.string "DODRIO: Gii giii!$"

CopycatsHouse2F_Johto_CopycatsDodrioText2:
	.string "MIRROR, MIRROR ON\n"
	.string "THE WALL, WHO'S"
	.string "\pTHE FAIREST ONE OF\n"
	.string "ALL?$"

CopycatsHouse2F_Johto_CopycatsHouse2FDollText:
	.string "This is a rare\n"
	.string "POKéMON! Huh?"
	.string "\pIt's only a doll…$"
