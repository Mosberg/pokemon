IcePathB3F_Johto_MapScripts::
	.byte 0

IcePathB3F_Johto_IcePathB3FNevermeltice_Entry::
	lockall
	goto IcePathB3F_Johto_IcePathB3FNevermeltice

IcePathB3F_Johto_IcePathB3FRock_Entry::
	lockall
	goto IcePathB3F_Johto_IcePathB3FRock


IcePathB3F_Johto_IcePathB3FNevermeltice:
	finditem ITEM_NEVERMELTICE
	releaseall
	end

IcePathB3F_Johto_IcePathB3FRock:
	goto Johto_Std_SmashRockScript
