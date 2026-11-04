DiglettsCave_Johto_MapScripts::
	.byte 0

DiglettsCave_Johto_DiglettsCavePokefanMScript_Entry::
	lockall
	goto DiglettsCave_Johto_DiglettsCavePokefanMScript


DiglettsCave_Johto_DiglettsCavePokefanMScript:
	faceplayer
	message DiglettsCave_Johto_DiglettsCavePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

DiglettsCave_Johto_DiglettsCavePokefanMText:
	.string "A bunch of DIGLETT\n"
	.string "popped out of the"
	.string "\pground! That was\n"
	.string "shocking.$"
