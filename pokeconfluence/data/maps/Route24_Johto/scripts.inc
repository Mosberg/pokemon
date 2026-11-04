Route24_Johto_MapScripts::
	.byte 0

Route24_Johto_Route24RocketScript_Entry::
	lockall
	goto Route24_Johto_Route24RocketScript


Route24_Johto_Route24RocketScript:
	faceplayer
	playbgm MUS_DUMMY, FALSE
	message Route24_Johto_Route24RocketSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_GRUNTM_GRUNTM_31, Route24_Johto_Route24RocketBeatenText
	playbgm MUS_DUMMY, FALSE
	message Route24_Johto_Route24RocketAfterBattleText
	waitmessage
	waitbuttonpress
	fadeoutbgm 4
	message Route24_Johto_Route24RocketDisappearsText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	delay 25
	fadescreen FADE_FROM_BLACK
	fadedefaultbgm
	releaseall
	end

Route24_Johto_Route24RocketSeenText:
	.string "Hey, kid! Me am a\n"
	.string "TEAM ROCKET member\l"
	.string "kind of guy!"
	.string "\pCome from another\n"
	.string "country, a trainer\l"
	.string "number one, me!"
	.string "\pThink I did, if\n"
	.string "stop the energy,"
	.string "\pbe big panic for\n"
	.string "here people!"
	.string "\pSecret it is my\n"
	.string "mission, so tell\l"
	.string "you I not!"
	.string "\pBut! If win you do\n"
	.string "versus me, a man I"
	.string "\pbe and mine secret\n"
	.string "to you I tell."
	.string "\pHey, kid! Battle\n"
	.string "begin we do!$"

Route24_Johto_Route24RocketBeatenText:
	.string "Ayieeeh! No, no,\n"
	.string "no, believe it I\l"
	.string "can't!"
	.string "\pStrong very much\n"
	.string "be you! Match I am\l"
	.string "not to you!$"

Route24_Johto_Route24RocketAfterBattleText:
	.string "OK. Tell you mine\n"
	.string "secret will I."
	.string "\pMACHINE PART steal\n"
	.string "by me, hide it I"
	.string "\pdid in GYM of the\n"
	.string "CERULEAN."
	.string "\pInside water put\n"
	.string "it I did. Look for"
	.string "\pin water center of\n"
	.string "GYM at."
	.string "\pBut you forget me\n"
	.string "not!"
	.string "\pBeat you for sure\n"
	.string "will TEAM ROCKET."
	.string "\pCome from JOHTO\n"
	.string "will they, mine"
	.string "\pfriends, yes. Will\n"
	.string "revenge they are.$"

Route24_Johto_Route24RocketDisappearsText:
	.string "…"
	.string "\pYou say what? TEAM\n"
	.string "ROCKET bye-bye a"
	.string "\pgo-go? Broken it\n"
	.string "is says you?"
	.string "\pOh, no! Should I\n"
	.string "do what now on\l"
	.string "from, me?$"
