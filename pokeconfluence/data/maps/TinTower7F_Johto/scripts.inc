TinTower7F_Johto_MapScripts::
	.byte 0

TinTower7F_Johto_TinTower7FMaxRevive_Entry::
	lockall
	goto TinTower7F_Johto_TinTower7FMaxRevive


TinTower7F_Johto_TinTower7FMaxRevive:
	finditem ITEM_MAX_REVIVE
	releaseall
	end
