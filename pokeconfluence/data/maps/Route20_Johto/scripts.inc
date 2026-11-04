Route20_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_Johto_OnTransition
	.byte 0

Route20_Johto_OnTransition:
	call Route20_Johto_Route20ClearRocksCallback_Cb
	end

Route20_Johto_CinnabarGymSign_Entry::
	lockall
	goto Route20_Johto_CinnabarGymSign


Route20_Johto_TrainerSwimmerfNicole::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_NICOLE, Route20_Johto_SwimmerfNicoleSeenText, Route20_Johto_SwimmerfNicoleBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_NICOLE
	lock
	faceplayer
	goto Route20_Johto_TrainerSwimmerfNicole_Script

Route20_Johto_TrainerSwimmerfNicole_Script:
	message Route20_Johto_SwimmerfNicoleAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route20_Johto_TrainerSwimmerfLori::
	trainerbattle_single TRAINER_JOHTO_SWIMMERF_LORI, Route20_Johto_SwimmerfLoriSeenText, Route20_Johto_SwimmerfLoriBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERF_LORI
	lock
	faceplayer
	goto Route20_Johto_TrainerSwimmerfLori_Script

Route20_Johto_TrainerSwimmerfLori_Script:
	message Route20_Johto_SwimmerfLoriAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route20_Johto_TrainerSwimmermCameron::
	trainerbattle_single TRAINER_JOHTO_SWIMMERM_CAMERON, Route20_Johto_SwimmermCameronSeenText, Route20_Johto_SwimmermCameronBeatenText
	setflag FLAG_JOHTO_BEAT_SWIMMERM_CAMERON
	lock
	faceplayer
	goto Route20_Johto_TrainerSwimmermCameron_Script

Route20_Johto_TrainerSwimmermCameron_Script:
	message Route20_Johto_SwimmermCameronAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route20_Johto_CinnabarGymSign:
	message Route20_Johto_CinnabarGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route20_Johto_Route20ClearRocksCallback_Cb:
	setflag FLAG_JOHTO_CINNABAR_ROCKS_CLEARED
	return

Route20_Johto_SwimmerfNicoleSeenText:
	.string "I feel so much\n"
	.string "lighter in water.$"

Route20_Johto_SwimmerfNicoleBeatenText:
	.string "Oh, no!$"

Route20_Johto_SwimmerfNicoleAfterBattleText:
	.string "Swimming exercises\n"
	.string "your full body."
	.string "\pIt's really good\n"
	.string "for you.$"

Route20_Johto_SwimmerfLoriSeenText:
	.string "What an impressive\n"
	.string "collection of GYM"
	.string "\pBADGES. We should\n"
	.string "battle!$"

Route20_Johto_SwimmerfLoriBeatenText:
	.string "No!$"

Route20_Johto_SwimmerfLoriAfterBattleText:
	.string "SURF is no longer\n"
	.string "the only HM move\l"
	.string "you use in water.$"

Route20_Johto_SwimmermCameronSeenText:
	.string "I guess it's im-\n"
	.string "possible to swim"
	.string "\pall the way to\n"
	.string "JOHTO.$"

Route20_Johto_SwimmermCameronBeatenText:
	.string "Aiyah!$"

Route20_Johto_SwimmermCameronAfterBattleText:
	.string "Besides the sea, I\n"
	.string "can also swim in\l"
	.string "ponds and rivers.$"

Route20_Johto_CinnabarGymSignText:
	.string "What does this\n"
	.string "sign say?"
	.string "\pCINNABAR GYM\n"
	.string "LEADER: BLAINE$"
