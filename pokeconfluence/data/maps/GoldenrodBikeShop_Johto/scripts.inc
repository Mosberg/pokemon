GoldenrodBikeShop_Johto_MapScripts::
	.byte 0

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript_Entry::
	lockall
	goto GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript

GoldenrodBikeShop_Johto_GoldenrodBikeShopBicycle_Entry::
	lockall
	goto GoldenrodBikeShop_Johto_GoldenrodBikeShopBicycle


GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_BICYCLE, GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript_GotBicycle
	message GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript_Refused
	message GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkAgreedText
	waitmessage
	waitbuttonpress
	waitse
	additem ITEM_BICYCLE
	message GoldenrodBikeShop_Johto_BorrowedABicycleText
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_BIKE_SHOP_CALL_ENABLED
	setflag FLAG_JOHTO_GOT_BICYCLE

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript_GotBicycle:
	message GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkFirstRateBikesText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkScript_Refused:
	message GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodBikeShop_Johto_GoldenrodBikeShopBicycle:
	message GoldenrodBikeShop_Johto_GoldenrodBikeShopBicycleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkIntroText:
	.string "…sigh… I moved\n"
	.string "here, but I can't"
	.string "\psell my BICYCLES.\n"
	.string "Why is that?"
	.string "\pCould you ride a\n"
	.string "BICYCLE and adver-\l"
	.string "tise for me?$"

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkAgreedText:
	.string "Really? Great!"
	.string "\pGive me your name\n"
	.string "and phone number,"
	.string "\pand I'll loan you\n"
	.string "a BICYCLE.$"

GoldenrodBikeShop_Johto_BorrowedABicycleText:
	.string "{PLAYER} borrowed a\n"
	.string "BICYCLE.$"

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkFirstRateBikesText:
	.string "My BICYCLES are\n"
	.string "first-rate! You"
	.string "\pcan ride them\n"
	.string "anywhere.$"

GoldenrodBikeShop_Johto_GoldenrodBikeShopClerkRefusedText:
	.string "…sigh… Oh, for\n"
	.string "the kindness of\l"
	.string "people…$"

GoldenrodBikeShop_Johto_GoldenrodBikeShopBicycleText:
	.string "It's a shiny new\n"
	.string "BICYCLE!$"
