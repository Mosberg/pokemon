Route27SandstormHouse_Johto_MapScripts::
	.byte 0

Route27SandstormHouse_Johto_SandstormHouseWoman_Entry::
	lockall
	goto Route27SandstormHouse_Johto_SandstormHouseWoman

Route27SandstormHouse_Johto_SandstormHouseBookshelf_Entry::
	lockall
	goto Route27SandstormHouse_Johto_SandstormHouseBookshelf


Route27SandstormHouse_Johto_SandstormHouseWoman:
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_TM37_SANDSTORM, Route27SandstormHouse_Johto_SandstormHouseWoman_AlreadyGotItem
	special JohtoGetFirstMonHappiness
	message Route27SandstormHouse_Johto_SandstormHouseWomanText1
	waitmessage
	waitbuttonpress
	@ TODO unsupported: ifgreater 150 - 1, .Loyal
	goto Johto_EventScript_Unimplemented

Route27SandstormHouse_Johto_SandstormHouseWoman_AlreadyGotItem:
	message Route27SandstormHouse_Johto_SandstormHouseSandstormDescription
	waitmessage
	waitbuttonpress

Route27SandstormHouse_Johto_SandstormHouseWoman_Done:
	closemessage
	releaseall
	end

Route27SandstormHouse_Johto_SandstormHouseBookshelf:
	goto Johto_Std_MagazineBookshelfScript

Route27SandstormHouse_Johto_SandstormHouseWomanText1:
	.string "Where are you off\n"
	.string "to with POKéMON?"
	.string "\pPOKéMON LEAGUE?"
	.string "\pAre your POKéMON\n"
	.string "loyal enough for\l"
	.string "you to win?"
	.string "\pLet me see…$"

Route27SandstormHouse_Johto_SandstormHouseSandstormDescription:
	.string "TM37 happens to be\n"
	.string "SANDSTORM."
	.string "\pIt's a move that\n"
	.string "inflicts damage on\l"
	.string "both battlers."
	.string "\pIt's for advanced\n"
	.string "trainers only."
	.string "\pUse it if you\n"
	.string "dare. Good luck!$"
