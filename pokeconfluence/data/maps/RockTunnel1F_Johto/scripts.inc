RockTunnel1F_Johto_MapScripts::
	.byte 0

RockTunnel1F_Johto_RockTunnel1FElixer_Entry::
	lockall
	goto RockTunnel1F_Johto_RockTunnel1FElixer

RockTunnel1F_Johto_RockTunnel1FTMSteelWing_Entry::
	lockall
	goto RockTunnel1F_Johto_RockTunnel1FTMSteelWing


RockTunnel1F_Johto_RockTunnel1FElixer:
	finditem ITEM_ELIXER
	releaseall
	end

RockTunnel1F_Johto_RockTunnel1FTMSteelWing:
	finditem ITEM_TM_STEEL_WING
	releaseall
	end
