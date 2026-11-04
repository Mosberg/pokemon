IcePathB1F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePathB1F_Johto_OnTransition
	.byte 0

IcePathB1F_Johto_OnTransition:
	call IcePathB1F_Johto_IcePathB1FSetUpStoneTableCallback_Cb
	end

IcePathB1F_Johto_IcePathB1FBoulder_Entry::
	lockall
	goto IcePathB1F_Johto_IcePathB1FBoulder

IcePathB1F_Johto_IcePathB1FIron_Entry::
	lockall
	goto IcePathB1F_Johto_IcePathB1FIron


IcePathB1F_Johto_IcePathB1FBoulder:
	goto Johto_Std_StrengthBoulderScript

IcePathB1F_Johto_IcePathB1FIron:
	finditem ITEM_IRON
	releaseall
	end

IcePathB1F_Johto_IcePathB1FSetUpStoneTableCallback_Cb:
	@ TODO unsupported: writecmdqueue .CommandQueue
	return
