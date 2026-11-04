SilverCavePokecenter1F_Johto_MapScripts::
	.byte 0

SilverCavePokecenter1F_Johto_SilverCavePokecenter1FNurseScript_Entry::
	lockall
	goto SilverCavePokecenter1F_Johto_SilverCavePokecenter1FNurseScript

SilverCavePokecenter1F_Johto_SilverCavePokecenter1FGrannyScript_Entry::
	lockall
	goto SilverCavePokecenter1F_Johto_SilverCavePokecenter1FGrannyScript


SilverCavePokecenter1F_Johto_SilverCavePokecenter1FNurseScript:
	setrespawn HEAL_LOCATION_JOHTO_SILVER_CAVE_OUTSIDE
	goto Johto_Std_PokecenterNurseScript

SilverCavePokecenter1F_Johto_SilverCavePokecenter1FGrannyScript:
	faceplayer
	message SilverCavePokecenter1F_Johto_SilverCavePokecenter1FGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SilverCavePokecenter1F_Johto_SilverCavePokecenter1FGrannyText:
	.string "Trainers who seek\n"
	.string "power climb MT."
	.string "\pSILVER despite its\n"
	.string "many dangers…"
	.string "\pWith their trusted\n"
	.string "POKéMON, they must"
	.string "\pfeel they can go\n"
	.string "anywhere…$"
