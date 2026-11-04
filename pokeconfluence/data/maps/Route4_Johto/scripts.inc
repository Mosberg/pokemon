Route4_Johto_MapScripts::
	.byte 0

Route4_Johto_Route4HPUp_Entry::
	lockall
	goto Route4_Johto_Route4HPUp

Route4_Johto_MtMoonSquareSign_Entry::
	lockall
	goto Route4_Johto_MtMoonSquareSign


Route4_Johto_TrainerBirdKeeperHank::
	trainerbattle_single TRAINER_JOHTO_BIRD_KEEPER_HANK, Route4_Johto_BirdKeeperHankSeenText, Route4_Johto_BirdKeeperHankBeatenText
	setflag FLAG_JOHTO_BEAT_BIRD_KEEPER_HANK
	lock
	faceplayer
	goto Route4_Johto_TrainerBirdKeeperHank_Script

Route4_Johto_TrainerBirdKeeperHank_Script:
	message Route4_Johto_BirdKeeperHankAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route4_Johto_TrainerPicnickerHope::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_HOPE, Route4_Johto_PicnickerHopeSeenText, Route4_Johto_PicnickerHopeBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_HOPE
	lock
	faceplayer
	goto Route4_Johto_TrainerPicnickerHope_Script

Route4_Johto_TrainerPicnickerHope_Script:
	message Route4_Johto_PicnickerHopeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route4_Johto_TrainerPicnickerSharon::
	trainerbattle_single TRAINER_JOHTO_PICNICKER_SHARON, Route4_Johto_PicnickerSharonSeenText, Route4_Johto_PicnickerSharonBeatenText
	setflag FLAG_JOHTO_BEAT_PICNICKER_SHARON
	lock
	faceplayer
	goto Route4_Johto_TrainerPicnickerSharon_Script

Route4_Johto_TrainerPicnickerSharon_Script:
	message Route4_Johto_PicnickerSharonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route4_Johto_MtMoonSquareSign:
	message Route4_Johto_MtMoonSquareSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route4_Johto_Route4HPUp:
	finditem ITEM_HP_UP
	releaseall
	end

Route4_Johto_BirdKeeperHankSeenText:
	.string "I'm raising my\n"
	.string "POKéMON. Want to\l"
	.string "battle with me?$"

Route4_Johto_BirdKeeperHankBeatenText:
	.string "Ack! I lost that\n"
	.string "one…$"

Route4_Johto_BirdKeeperHankAfterBattleText:
	.string "If you have a\n"
	.string "specific POKéMON"
	.string "\pthat you want to\n"
	.string "raise, put it out"
	.string "\pfirst, then switch\n"
	.string "it right away."
	.string "\pThat's how to do\n"
	.string "it.$"

Route4_Johto_PicnickerHopeSeenText:
	.string "I have a feeling\n"
	.string "that I can win."
	.string "\pLet's see if I'm\n"
	.string "right!$"

Route4_Johto_PicnickerHopeBeatenText:
	.string "Aww, you are too\n"
	.string "strong.$"

Route4_Johto_PicnickerHopeAfterBattleText:
	.string "I heard CLEFAIRY\n"
	.string "appear at MT.MOON."
	.string "\pBut where could\n"
	.string "they be?$"

Route4_Johto_PicnickerSharonSeenText:
	.string "Um…\n"
	.string "I…$"

Route4_Johto_PicnickerSharonBeatenText:
	.string "…$"

Route4_Johto_PicnickerSharonAfterBattleText:
	.string "……I'll go train\n"
	.string "some more…$"

Route4_Johto_MtMoonSquareSignText:
	.string "MT.MOON SQUARE"
	.string "\pJust go up the\n"
	.string "stairs.$"
