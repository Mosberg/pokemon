IcePath1F_Johto_MapScripts::
	.byte 0

IcePath1F_Johto_IcePath1FHMWaterfall_Entry::
	lockall
	goto IcePath1F_Johto_IcePath1FHMWaterfall

IcePath1F_Johto_IcePath1FPPUp_Entry::
	lockall
	goto IcePath1F_Johto_IcePath1FPPUp

IcePath1F_Johto_IcePath1FProtein_Entry::
	lockall
	goto IcePath1F_Johto_IcePath1FProtein


IcePath1F_Johto_IcePath1FHMWaterfall:
	finditem ITEM_HM_WATERFALL
	releaseall
	end

IcePath1F_Johto_IcePath1FPPUp:
	finditem ITEM_PP_UP
	releaseall
	end

IcePath1F_Johto_IcePath1FProtein:
	finditem ITEM_PROTEIN
	releaseall
	end
