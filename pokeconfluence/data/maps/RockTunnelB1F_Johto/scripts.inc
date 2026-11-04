RockTunnelB1F_Johto_MapScripts::
	.byte 0

RockTunnelB1F_Johto_RockTunnelB1FIron_Entry::
	lockall
	goto RockTunnelB1F_Johto_RockTunnelB1FIron

RockTunnelB1F_Johto_RockTunnelB1FPPUp_Entry::
	lockall
	goto RockTunnelB1F_Johto_RockTunnelB1FPPUp

RockTunnelB1F_Johto_RockTunnelB1FRevive_Entry::
	lockall
	goto RockTunnelB1F_Johto_RockTunnelB1FRevive


RockTunnelB1F_Johto_RockTunnelB1FIron:
	finditem ITEM_IRON
	releaseall
	end

RockTunnelB1F_Johto_RockTunnelB1FPPUp:
	finditem ITEM_PP_UP
	releaseall
	end

RockTunnelB1F_Johto_RockTunnelB1FRevive:
	finditem ITEM_REVIVE
	releaseall
	end
