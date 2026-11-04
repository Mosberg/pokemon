GoldenrodFlowerShop_Johto_MapScripts::
	.byte 0

GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_Entry::
	lockall
	goto GoldenrodFlowerShop_Johto_FlowerShopTeacherScript

GoldenrodFlowerShop_Johto_FlowerShopFloriaScript_Entry::
	lockall
	goto GoldenrodFlowerShop_Johto_FlowerShopFloriaScript


GoldenrodFlowerShop_Johto_FlowerShopTeacherScript:
	goto_if_set FLAG_JOHTO_FOUGHT_SUDOWOODO, GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_Lalala
	goto_if_set FLAG_JOHTO_GOT_SQUIRTBOTTLE, GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_GotSquirtbottle
	goto_if_unset FLAG_JOHTO_MET_FLORIA, GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_HaventMetFloria
	goto_if_unset FLAG_JOHTO_TALKED_TO_FLORIA_AT_FLOWER_SHOP, GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_Lalala
	goto_if_unset FLAG_JOHTO_ENGINE_PLAINBADGE, GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_NoPlainBadge
	faceplayer
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherHeresTheSquirtbottleText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SQUIRTBOTTLE
	setflag FLAG_JOHTO_GOT_SQUIRTBOTTLE
	closemessage
	setflag FLAG_JOHTO_FLORIA_AT_SUDOWOODO
	clearflag FLAG_JOHTO_FLORIA_AT_FLOWER_SHOP
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_Lalala:
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_GotSquirtbottle:
	faceplayer
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherDontDoAnythingDangerousText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_NoPlainBadge:
	faceplayer
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopTeacherScript_HaventMetFloria:
	faceplayer
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopFloriaScript:
	faceplayer
	goto_if_set FLAG_JOHTO_FOUGHT_SUDOWOODO, GoldenrodFlowerShop_Johto_FlowerShopFloriaScript_FoughtSudowoodo
	goto_if_set FLAG_JOHTO_GOT_SQUIRTBOTTLE, GoldenrodFlowerShop_Johto_FlowerShopFloriaScript_GotSquirtbottle
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_TALKED_TO_FLORIA_AT_FLOWER_SHOP
	setflag FLAG_JOHTO_FLORIA_AT_FLOWER_SHOP
	clearflag FLAG_JOHTO_FLORIA_AT_SUDOWOODO
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopFloriaScript_GotSquirtbottle:
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaYouBeatWhitneyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_FlowerShopFloriaScript_FoughtSudowoodo:
	message GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaItReallyWasAMonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text:
	.string "Have you seen that\n"
	.string "wiggly tree that's"
	.string "\pgrowing on ROUTE\n"
	.string "36?"
	.string "\pMy little sister\n"
	.string "got all excited"
	.string "\pand went to see\n"
	.string "it…"
	.string "\pI'm worried… Isn't\n"
	.string "it dangerous?$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText:
	.string "Do you want to\n"
	.string "borrow the water"
	.string "\pbottle too?\n"
	.string "I don't want you"
	.string "\pdoing anything\n"
	.string "dangerous with it.$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherHeresTheSquirtbottleText:
	.string "Oh, you're better\n"
	.string "than WHITNEY…"
	.string "\pYou'll be OK,\n"
	.string "then. Here's the\l"
	.string "SQUIRTBOTTLE!$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherDontDoAnythingDangerousText:
	.string "Don't do anything\n"
	.string "too dangerous!$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText:
	.string "Lalala lalalala.\n"
	.string "Have plenty of\l"
	.string "water, my lovely!$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText:
	.string "When I told my sis\n"
	.string "about the jiggly"
	.string "\ptree, she told me\n"
	.string "it's dangerous."
	.string "\pIf I beat WHITNEY,\n"
	.string "I wonder if she'll"
	.string "\plend me her water\n"
	.string "bottle…$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaYouBeatWhitneyText:
	.string "Wow, you beat\n"
	.string "WHITNEY? Cool!$"

GoldenrodFlowerShop_Johto_GoldenrodFlowerShopFloriaItReallyWasAMonText:
	.string "So it really was a\n"
	.string "POKéMON!$"
