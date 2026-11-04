TinTower3F_Johto_MapScripts::
	.byte 0

TinTower3F_Johto_TinTower3FFullHeal_Entry::
	lockall
	goto TinTower3F_Johto_TinTower3FFullHeal


TinTower3F_Johto_TinTower3FFullHeal:
	finditem ITEM_FULL_HEAL
	releaseall
	end
