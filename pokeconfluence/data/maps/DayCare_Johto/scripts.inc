DayCare_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DayCare_Johto_OnTransition
	.byte 0

DayCare_Johto_OnTransition:
	call DayCare_Johto_DayCareEggCheckCallback_Cb
	end

DayCare_Johto_DayCareBookshelf_Entry::
	lockall
	goto DayCare_Johto_DayCareBookshelf


DayCare_Johto_DayCareBookshelf:
	goto Johto_Std_DifficultBookshelfScript

DayCare_Johto_DayCareManScript::
	lock
	faceplayer
	goto_if_set FLAG_JOHTO_GOT_ODD_EGG, DayCare_Johto_DayCareManScript_AlreadyGotOddEgg
	msgbox DayCare_Johto_DayCareManText_GiveOddEgg, MSGBOX_DEFAULT
	special JohtoGiveOddEgg
	goto_if_eq VAR_RESULT, FALSE, DayCare_Johto_DayCareManScript_PartyFull
	playfanfare MUS_OBTAIN_ITEM
	message DayCare_Johto_DayCareText_GotOddEgg
	waitfanfare
	waitbuttonpress
	msgbox DayCare_Johto_DayCareText_DescribeOddEgg, MSGBOX_DEFAULT
	setflag FLAG_JOHTO_GOT_ODD_EGG
	release
	end

DayCare_Johto_DayCareManScript_PartyFull:
	msgbox DayCare_Johto_DayCareText_PartyFull, MSGBOX_DEFAULT
	release
	end

DayCare_Johto_DayCareManScript_AlreadyGotOddEgg:
	goto Route117_EventScript_DaycareMan

DayCare_Johto_DayCareManText_GiveOddEgg:
	.string "I'm the DAY-CARE MAN.\n"
	.string "Do you know about EGGS?\p"
	.string "I was raising POKéMON with\n"
	.string "my wife, you see.\p"
	.string "We were shocked to find\n"
	.string "an EGG!\p"
	.string "How incredible is that?\n"
	.string "Well, wouldn't you like this EGG?\p"
	.string "Then fine, this is yours to keep!$"

DayCare_Johto_DayCareText_GotOddEgg:
	.string "{PLAYER} received the ODD EGG!$"

DayCare_Johto_DayCareText_DescribeOddEgg:
	.string "I found that when I was caring\n"
	.string "for someone's POKéMON before.\p"
	.string "But the trainer didn't want the\n"
	.string "EGG, so I'd kept it around.$"

DayCare_Johto_DayCareText_PartyFull:
	.string "You've no room for this.$"

DayCare_Johto_DayCareEggCheckCallback_Cb:
	goto_if_set FLAG_JOHTO_ENGINE_DAY_CARE_MAN_HAS_EGG, DayCare_Johto_DayCareEggCheckCallback_PutDayCareManOutside_Cb
	clearflag FLAG_JOHTO_DAY_CARE_MAN_IN_DAY_CARE
	setflag FLAG_JOHTO_DAY_CARE_MAN_ON_ROUTE_34
	return

DayCare_Johto_DayCareEggCheckCallback_PutDayCareManOutside_Cb:
	setflag FLAG_JOHTO_DAY_CARE_MAN_IN_DAY_CARE
	clearflag FLAG_JOHTO_DAY_CARE_MAN_ON_ROUTE_34
	return
