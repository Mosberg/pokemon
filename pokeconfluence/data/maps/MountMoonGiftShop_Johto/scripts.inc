MountMoonGiftShop_Johto_MapScripts::
	.byte 0

MountMoonGiftShop_Johto_MountMoonGiftShopClerkScript_Entry::
	lockall
	goto MountMoonGiftShop_Johto_MountMoonGiftShopClerkScript

MountMoonGiftShop_Johto_MountMoonGiftShopLassScript_Entry::
	lockall
	goto MountMoonGiftShop_Johto_MountMoonGiftShopLassScript


MountMoonGiftShop_Johto_MountMoonGiftShopClerkScript:
	faceplayer
	pokemart Johto_Mart_MT_MOON
	closemessage
	releaseall
	end

MountMoonGiftShop_Johto_MountMoonGiftShopLassScript:
	faceplayer
	message MountMoonGiftShop_Johto_MountMoonGiftShopLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

MountMoonGiftShop_Johto_MountMoonGiftShopLassText:
	.string "When the sun goes\n"
	.string "down, CLEFAIRY\l"
	.string "come out to play.$"
