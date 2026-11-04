Route39Barn_Johto_MapScripts::
	.byte 0

Route39Barn_Johto_Route39BarnTwin1Script_Entry::
	lockall
	goto Route39Barn_Johto_Route39BarnTwin1Script

Route39Barn_Johto_Route39BarnTwin2Script_Entry::
	lockall
	goto Route39Barn_Johto_Route39BarnTwin2Script

Route39Barn_Johto_MoomooScript_Entry::
	lockall
	goto Route39Barn_Johto_MoomooScript


Route39Barn_Johto_Route39BarnTwin1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_Route39BarnTwin1Script_FeedingMooMoo
	message Route39Barn_Johto_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin1Script_FeedingMooMoo:
	message Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Right
	waitmovement 1
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_Route39BarnTwin2Script_FeedingMooMoo
	message Route39Barn_Johto_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	releaseall
	end

Route39Barn_Johto_Route39BarnTwin2Script_FeedingMooMoo:
	message Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, Johto_Movement_Face_Left
	waitmovement 2
	releaseall
	end

Route39Barn_Johto_MoomooScript:
	goto_if_set FLAG_JOHTO_HEALED_MOOMOO, Route39Barn_Johto_MoomooScript_HappyCow
	message Route39Barn_Johto_MoomooWeakMooText
	waitmessage
	setvar VAR_0x8004, SPECIES_MILTANK
	@ TODO unsupported: special PlaySlowCry
	goto Johto_EventScript_Unimplemented

Route39Barn_Johto_MoomooScript_HappyCow:
	message Route39Barn_Johto_MoomooHappyMooText
	waitmessage
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

Route39Barn_Johto_Route39BarnTwinMoomooIsSickText:
	.string "MOOMOO is sick…"
	.string "\pShe needs lots of\n"
	.string "BERRIES.$"

Route39Barn_Johto_Route39BarnTwinWereFeedingMoomooText:
	.string "We're feeding\n"
	.string "MOOMOO!$"

Route39Barn_Johto_MoomooWeakMooText:
	.string "MILTANK: …Moo…$"

Route39Barn_Johto_MoomooHappyMooText:
	.string "MILTANK: Mooo!$"
