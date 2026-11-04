BluesHouse_Johto_MapScripts::
	.byte 0

BluesHouse_Johto_DaisyScript_Entry::
	lockall
	goto BluesHouse_Johto_DaisyScript


BluesHouse_Johto_DaisyScript:
	faceplayer
	@ TODO unsupported: readvar VAR_HOUR
	goto Johto_EventScript_Unimplemented
