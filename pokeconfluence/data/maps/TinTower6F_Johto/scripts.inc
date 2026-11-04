TinTower6F_Johto_MapScripts::
	.byte 0

TinTower6F_Johto_TinTower6FMaxPotion_Entry::
	lockall
	goto TinTower6F_Johto_TinTower6FMaxPotion


TinTower6F_Johto_TinTower6FMaxPotion:
	finditem ITEM_MAX_POTION
	releaseall
	end
