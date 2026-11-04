TinTower9F_Johto_MapScripts::
	.byte 0

TinTower9F_Johto_TinTower9FHPUp_Entry::
	lockall
	goto TinTower9F_Johto_TinTower9FHPUp


TinTower9F_Johto_TinTower9FHPUp:
	finditem ITEM_HP_UP
	releaseall
	end
