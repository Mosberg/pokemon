WhirlIslandSW_Johto_MapScripts::
	.byte 0

WhirlIslandSW_Johto_WhirlIslandSWUltraBall_Entry::
	lockall
	goto WhirlIslandSW_Johto_WhirlIslandSWUltraBall


WhirlIslandSW_Johto_WhirlIslandSWUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end
