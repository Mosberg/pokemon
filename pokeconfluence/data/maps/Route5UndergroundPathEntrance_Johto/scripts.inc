Route5UndergroundPathEntrance_Johto_MapScripts::
	.byte 0

Route5UndergroundPathEntrance_Johto_Route5UndergroundPathEntranceTeacherScript_Entry::
	lockall
	goto Route5UndergroundPathEntrance_Johto_Route5UndergroundPathEntranceTeacherScript


Route5UndergroundPathEntrance_Johto_Route5UndergroundPathEntranceTeacherScript:
	faceplayer
	message Route5UndergroundPathEntrance_Johto_Route5UndergroundPathEntranceTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route5UndergroundPathEntrance_Johto_Route5UndergroundPathEntranceTeacherText:
	.string "Many cities in\n"
	.string "JOHTO have long"
	.string "\phistories. I'd\n"
	.string "love to visit!$"
