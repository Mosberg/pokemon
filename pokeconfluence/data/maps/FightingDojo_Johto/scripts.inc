FightingDojo_Johto_MapScripts::
	.byte 0

FightingDojo_Johto_FightingDojoBlackBelt_Entry::
	lockall
	goto FightingDojo_Johto_FightingDojoBlackBelt

FightingDojo_Johto_FightingDojoFocusBand_Entry::
	lockall
	goto FightingDojo_Johto_FightingDojoFocusBand

FightingDojo_Johto_FightingDojoSign1_Entry::
	lockall
	goto FightingDojo_Johto_FightingDojoSign1

FightingDojo_Johto_FightingDojoSign2_Entry::
	lockall
	goto FightingDojo_Johto_FightingDojoSign2


FightingDojo_Johto_FightingDojoBlackBelt:
	faceplayer
	message FightingDojo_Johto_FightingDojoBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FightingDojo_Johto_FightingDojoSign1:
	message FightingDojo_Johto_FightingDojoSign1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FightingDojo_Johto_FightingDojoSign2:
	message FightingDojo_Johto_FightingDojoSign2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FightingDojo_Johto_FightingDojoFocusBand:
	finditem ITEM_FOCUS_BAND
	releaseall
	end

FightingDojo_Johto_FightingDojoBlackBeltText:
	.string "Hello!"
	.string "\pKARATE KING, the\n"
	.string "FIGHTING DOJO's"
	.string "\pmaster, is in a\n"
	.string "cave in JOHTO for\l"
	.string "training.$"

FightingDojo_Johto_FightingDojoSign1Text:
	.string "What goes around\n"
	.string "comes around!$"

FightingDojo_Johto_FightingDojoSign2Text:
	.string "Enemies on every\n"
	.string "side!$"
