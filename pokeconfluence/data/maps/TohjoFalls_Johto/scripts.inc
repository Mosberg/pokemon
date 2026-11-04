TohjoFalls_Johto_MapScripts::
	.byte 0

TohjoFalls_Johto_TohjoFallsMoonStone_Entry::
	lockall
	goto TohjoFalls_Johto_TohjoFallsMoonStone


TohjoFalls_Johto_TohjoFallsMoonStone:
	finditem ITEM_MOON_STONE
	releaseall
	end
