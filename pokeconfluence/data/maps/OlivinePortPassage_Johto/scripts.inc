OlivinePortPassage_Johto_MapScripts::
	.byte 0

OlivinePortPassage_Johto_OlivinePortPassagePokefanMScript_Entry::
	lockall
	goto OlivinePortPassage_Johto_OlivinePortPassagePokefanMScript


OlivinePortPassage_Johto_OlivinePortPassagePokefanMScript:
	faceplayer
	message OlivinePortPassage_Johto_OlivinePortPassagePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

OlivinePortPassage_Johto_OlivinePortPassagePokefanMText:
	.string "FAST SHIP S.S.AQUA\n"
	.string "sails to KANTO on"
	.string "\pMondays and Fri-\n"
	.string "days.$"
