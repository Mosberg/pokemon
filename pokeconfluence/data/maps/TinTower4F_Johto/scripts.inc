TinTower4F_Johto_MapScripts::
	.byte 0

TinTower4F_Johto_TinTower4FUltraBall_Entry::
	lockall
	goto TinTower4F_Johto_TinTower4FUltraBall

TinTower4F_Johto_TinTower4FPPUp_Entry::
	lockall
	goto TinTower4F_Johto_TinTower4FPPUp

TinTower4F_Johto_TinTower4FEscapeRope_Entry::
	lockall
	goto TinTower4F_Johto_TinTower4FEscapeRope


TinTower4F_Johto_TinTower4FUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

TinTower4F_Johto_TinTower4FPPUp:
	finditem ITEM_PP_UP
	releaseall
	end

TinTower4F_Johto_TinTower4FEscapeRope:
	finditem ITEM_ESCAPE_ROPE
	releaseall
	end
