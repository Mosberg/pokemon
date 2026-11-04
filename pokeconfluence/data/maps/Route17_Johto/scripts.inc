Route17_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route17_Johto_OnTransition
	.byte 0

Route17_Johto_OnTransition:
	call Route17_Johto_Route17AlwaysOnBikeCallback_Cb
	end



Route17_Johto_TrainerBikerCharles::
	trainerbattle_single TRAINER_JOHTO_BIKER_CHARLES, Route17_Johto_BikerCharlesSeenText, Route17_Johto_BikerCharlesBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_CHARLES
	lock
	faceplayer
	goto Route17_Johto_TrainerBikerCharles_Script

Route17_Johto_TrainerBikerCharles_Script:
	message Route17_Johto_BikerCharlesAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route17_Johto_TrainerBikerRiley::
	trainerbattle_single TRAINER_JOHTO_BIKER_RILEY, Route17_Johto_BikerRileySeenText, Route17_Johto_BikerRileyBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_RILEY
	lock
	faceplayer
	goto Route17_Johto_TrainerBikerRiley_Script

Route17_Johto_TrainerBikerRiley_Script:
	message Route17_Johto_BikerRileyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route17_Johto_TrainerBikerJoel::
	trainerbattle_single TRAINER_JOHTO_BIKER_JOEL, Route17_Johto_BikerJoelSeenText, Route17_Johto_BikerJoelBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_JOEL
	lock
	faceplayer
	goto Route17_Johto_TrainerBikerJoel_Script

Route17_Johto_TrainerBikerJoel_Script:
	message Route17_Johto_BikerJoelAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route17_Johto_TrainerBikerGlenn::
	trainerbattle_single TRAINER_JOHTO_BIKER_GLENN, Route17_Johto_BikerGlennSeenText, Route17_Johto_BikerGlennBeatenText
	setflag FLAG_JOHTO_BEAT_BIKER_GLENN
	lock
	faceplayer
	goto Route17_Johto_TrainerBikerGlenn_Script

Route17_Johto_TrainerBikerGlenn_Script:
	message Route17_Johto_BikerGlennAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route17_Johto_Route17AlwaysOnBikeCallback_Cb:
	setflag FLAG_JOHTO_ENGINE_ALWAYS_ON_BIKE
	setflag FLAG_JOHTO_ENGINE_DOWNHILL
	return

Route17_Johto_BikerRileySeenText:
	.string "Hey, you! You're\n"
	.string "from JOHTO, huh?$"

Route17_Johto_BikerRileyBeatenText:
	.string "Whoa, you kick!$"

Route17_Johto_BikerRileyAfterBattleText:
	.string "Don't get cocky,\n"
	.string "you JOHTO punk!$"

Route17_Johto_BikerJoelSeenText:
	.string "Wow. That's a cool\n"
	.string "BICYCLE!$"

Route17_Johto_BikerJoelBeatenText:
	.string "But you don't just\n"
	.string "look cool…$"

Route17_Johto_BikerJoelAfterBattleText:
	.string "I look cool, but\n"
	.string "I'm weak, so I'm\l"
	.string "not really cool."
	.string "\pI have to train\n"
	.string "harder…$"

Route17_Johto_BikerGlennSeenText:
	.string "Hey! Want to have\n"
	.string "a speed battle?$"

Route17_Johto_BikerGlennBeatenText:
	.string "Yikes! You've got\n"
	.string "awesome torque!$"

Route17_Johto_BikerGlennAfterBattleText:
	.string "Hands-free riding\n"
	.string "is considered cool\l"
	.string "on CYCLING ROAD.$"

Route17_Johto_BikerCharlesSeenText:
	.string "We're fearless\n"
	.string "highway stars!$"

Route17_Johto_BikerCharlesBeatenText:
	.string "Arrrgh! Crash and\n"
	.string "burn!$"

Route17_Johto_BikerCharlesAfterBattleText:
	.string "Reckless driving\n"
	.string "causes accidents!\l"
	.string "Take it easy!$"
