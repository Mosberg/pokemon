SilverCaveRoom2_Johto_MapScripts::
	.byte 0

SilverCaveRoom2_Johto_SilverCaveRoom2Calcium_Entry::
	lockall
	goto SilverCaveRoom2_Johto_SilverCaveRoom2Calcium

SilverCaveRoom2_Johto_SilverCaveRoom2UltraBall_Entry::
	lockall
	goto SilverCaveRoom2_Johto_SilverCaveRoom2UltraBall

SilverCaveRoom2_Johto_SilverCaveRoom2PPUp_Entry::
	lockall
	goto SilverCaveRoom2_Johto_SilverCaveRoom2PPUp


SilverCaveRoom2_Johto_SilverCaveRoom2Calcium:
	finditem ITEM_CALCIUM
	releaseall
	end

SilverCaveRoom2_Johto_SilverCaveRoom2UltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

SilverCaveRoom2_Johto_SilverCaveRoom2PPUp:
	finditem ITEM_PP_UP
	releaseall
	end
