WhirlIslandNE_Johto_MapScripts::
	.byte 0

WhirlIslandNE_Johto_WhirlIslandNEUltraBall_Entry::
	lockall
	goto WhirlIslandNE_Johto_WhirlIslandNEUltraBall


WhirlIslandNE_Johto_WhirlIslandNEUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end
