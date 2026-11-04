TinTower8F_Johto_MapScripts::
	.byte 0

TinTower8F_Johto_TinTower8FNugget_Entry::
	lockall
	goto TinTower8F_Johto_TinTower8FNugget

TinTower8F_Johto_TinTower8FMaxElixer_Entry::
	lockall
	goto TinTower8F_Johto_TinTower8FMaxElixer

TinTower8F_Johto_TinTower8FFullRestore_Entry::
	lockall
	goto TinTower8F_Johto_TinTower8FFullRestore


TinTower8F_Johto_TinTower8FNugget:
	finditem ITEM_NUGGET
	releaseall
	end

TinTower8F_Johto_TinTower8FMaxElixer:
	finditem ITEM_MAX_ELIXER
	releaseall
	end

TinTower8F_Johto_TinTower8FFullRestore:
	finditem ITEM_FULL_RESTORE
	releaseall
	end
