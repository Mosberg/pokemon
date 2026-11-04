TinTower5F_Johto_MapScripts::
	.byte 0

TinTower5F_Johto_TinTower5FRareCandy_Entry::
	lockall
	goto TinTower5F_Johto_TinTower5FRareCandy


TinTower5F_Johto_TinTower5FRareCandy:
	finditem ITEM_RARE_CANDY
	releaseall
	end
