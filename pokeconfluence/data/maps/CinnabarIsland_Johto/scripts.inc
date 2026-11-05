CinnabarIsland_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_Johto_OnTransition
	.byte 0

CinnabarIsland_Johto_OnTransition:
	call CinnabarIsland_Johto_CinnabarIslandFlypointCallback_Cb
	end

CinnabarIsland_Johto_CinnabarIslandBlue_Entry::
	lockall
	goto CinnabarIsland_Johto_CinnabarIslandBlue

CinnabarIsland_Johto_CinnabarIslandPokecenterSign_Entry::
	lockall
	goto CinnabarIsland_Johto_CinnabarIslandPokecenterSign

CinnabarIsland_Johto_CinnabarIslandGymSign_Entry::
	lockall
	goto CinnabarIsland_Johto_CinnabarIslandGymSign

CinnabarIsland_Johto_CinnabarIslandSign_Entry::
	lockall
	goto CinnabarIsland_Johto_CinnabarIslandSign


CinnabarIsland_Johto_CinnabarIslandBlue:
	faceplayer
	message CinnabarIsland_Johto_CinnabarIslandBlueText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_WARP_IN
	applymovement 1, CinnabarIsland_Johto_CinnabarIslandBlueTeleport
	waitmovement 1
	removeobject 1
	clearflag FLAG_JOHTO_VIRIDIAN_GYM_BLUE
	releaseall
	end

CinnabarIsland_Johto_CinnabarIslandGymSign:
	message CinnabarIsland_Johto_CinnabarIslandGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CinnabarIsland_Johto_CinnabarIslandSign:
	message CinnabarIsland_Johto_CinnabarIslandSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CinnabarIsland_Johto_CinnabarIslandPokecenterSign:
	goto Johto_Std_PokecenterSignScript

CinnabarIsland_Johto_CinnabarIslandFlypointCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_FLYPOINT_CINNABAR
	return

CinnabarIsland_Johto_CinnabarIslandBlueTeleport:
	set_invisible
	step_end

CinnabarIsland_Johto_CinnabarIslandBlueText:
	.string "Who are you?"
	.string "\pWell, it's plain\n"
	.string "to see that you're\l"
	.string "a trainer…"
	.string "\pMy name's BLUE."
	.string "\pI was once the\n"
	.string "CHAMPION, although"
	.string "\pit was for only a\n"
	.string "short time…"
	.string "\pThat meddling RED\n"
	.string "did me in…"
	.string "\pAnyway, what do\n"
	.string "you want? You want"
	.string "\pto challenge me or\n"
	.string "something?"
	.string "\p…I hate to say\n"
	.string "it, but I'm not in"
	.string "\pthe mood for a\n"
	.string "battle now."
	.string "\pTake a good look\n"
	.string "around you…"
	.string "\pA volcano erupts,\n"
	.string "and just like"
	.string "\pthat, a whole town\n"
	.string "disappears."
	.string "\pWe can go on win-\n"
	.string "ning and losing in"
	.string "\pPOKéMON. But if\n"
	.string "nature so much as"
	.string "\ptwitches, we can\n"
	.string "lose in a second."
	.string "\p…"
	.string "\pThat's the way it\n"
	.string "is…"
	.string "\pBut, anyway, I'm\n"
	.string "still a trainer."
	.string "\pIf I see a strong\n"
	.string "opponent, it makes\l"
	.string "me want to battle."
	.string "\pIf you want to\n"
	.string "battle me, come to\l"
	.string "the VIRIDIAN GYM."
	.string "\pI'll take you on\n"
	.string "then.$"

CinnabarIsland_Johto_CinnabarIslandGymSignText:
	.string "There's a notice\n"
	.string "here…"
	.string "\pCINNABAR GYM has\n"
	.string "relocated to SEA-\l"
	.string "FOAM ISLANDS."
	.string "\pBLAINE$"

CinnabarIsland_Johto_CinnabarIslandSignText:
	.string "CINNABAR ISLAND"
	.string "\pThe Fiery Town of\n"
	.string "Burning Desire$"
