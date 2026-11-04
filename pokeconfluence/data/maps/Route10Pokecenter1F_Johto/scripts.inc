Route10Pokecenter1F_Johto_MapScripts::
	.byte 0

Route10Pokecenter1F_Johto_Route10Pokecenter1FNurseScript_Entry::
	lockall
	goto Route10Pokecenter1F_Johto_Route10Pokecenter1FNurseScript

Route10Pokecenter1F_Johto_Route10Pokecenter1FGentlemanScript_Entry::
	lockall
	goto Route10Pokecenter1F_Johto_Route10Pokecenter1FGentlemanScript

Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideScript_Entry::
	lockall
	goto Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideScript

Route10Pokecenter1F_Johto_Route10Pokecenter1FCooltrainerFScript_Entry::
	lockall
	goto Route10Pokecenter1F_Johto_Route10Pokecenter1FCooltrainerFScript


Route10Pokecenter1F_Johto_Route10Pokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_ROUTE_10_NORTH
	goto Johto_Std_PokecenterNurseScript

Route10Pokecenter1F_Johto_Route10Pokecenter1FGentlemanScript:
	faceplayer
	message Route10Pokecenter1F_Johto_Route10Pokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideScript_ReturnedMachinePart
	message Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideScript_ReturnedMachinePart:
	message Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideText_ReturnedMachinePart
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10Pokecenter1F_Johto_Route10Pokecenter1FCooltrainerFScript:
	faceplayer
	message Route10Pokecenter1F_Johto_Route10Pokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10Pokecenter1F_Johto_Route10Pokecenter1FGentlemanText:
	.string "A POKéMON CENTER\n"
	.string "near a cave?"
	.string "\pThat's mighty\n"
	.string "convenient.$"

Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideText:
	.string "The POWER PLANT's\n"
	.string "MANAGER is looking"
	.string "\pfor a strong POKé-\n"
	.string "MON trainer."
	.string "\pHe needs help\n"
	.string "getting back"
	.string "\psomething that\n"
	.string "was stolen.$"

Route10Pokecenter1F_Johto_Route10Pokecenter1FGymGuideText_ReturnedMachinePart:
	.string "I hear TEAM ROCKET\n"
	.string "got back together"
	.string "\pin JOHTO but fell\n"
	.string "apart right away."
	.string "\pI didn't know any-\n"
	.string "thing about that.$"

Route10Pokecenter1F_Johto_Route10Pokecenter1FCooltrainerFText:
	.string "When you go out-\n"
	.string "side, you can see"
	.string "\pthe roof of a big\n"
	.string "building."
	.string "\pThat's the POWER\n"
	.string "PLANT.$"
