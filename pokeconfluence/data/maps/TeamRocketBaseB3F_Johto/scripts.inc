TeamRocketBaseB3F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TeamRocketBaseB3F_Johto_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TeamRocketBaseB3F_Johto_OnFrame
	.byte 0

TeamRocketBaseB3F_Johto_OnLoad:
	call TeamRocketBaseB3F_Johto_TeamRocketBaseB3FCheckGiovanniDoorCallback_Cb
	end

TeamRocketBaseB3F_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B3F, 0, TeamRocketBaseB3F_Johto_LanceGetPasswordScript_Entry
	.2byte 0

TeamRocketBaseB3F_Johto_LanceGetPasswordScript_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_LanceGetPasswordScript

TeamRocketBaseB3F_Johto_RocketBaseMurkrow_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_RocketBaseMurkrow

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FRocketScript_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FRocketScript

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FProtein_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FProtein

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FXSpecial_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FXSpecial

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FFullHeal_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FFullHeal

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FIceHeal_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FIceHeal

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FUltraBall_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FUltraBall

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FOathScript_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_TeamRocketBaseB3FOathScript

TeamRocketBaseB3F_Johto_RocketBaseBossLeft_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_RocketBaseBossLeft

TeamRocketBaseB3F_Johto_RocketBaseBossRight_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_RocketBaseBossRight

TeamRocketBaseB3F_Johto_RocketBaseRival_Entry::
	lockall
	goto TeamRocketBaseB3F_Johto_RocketBaseRival


TeamRocketBaseB3F_Johto_LanceGetPasswordScript:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	applymovement 3, Johto_Movement_Face_Right
	waitmovement 3
	delay 20
	applymovement 1, TeamRocketBaseB3F_Johto_RocketBaseLanceApproachesPlayerMovement
	waitmovement 1
	message TeamRocketBaseB3F_Johto_LanceGetPasswordText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, TeamRocketBaseB3F_Johto_RocketBaseLanceLeavesMovement
	waitmovement 1
	removeobject 1
	setvar VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B3F, 1
	releaseall
	end

TeamRocketBaseB3F_Johto_RocketBaseRival:
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Emote_exclamation_mark
	waitmovement OBJ_EVENT_ID_PLAYER
	fadeoutbgm 4
	clearflag FLAG_JOHTO_RIVAL_TEAM_ROCKET_BASE
	addobject 9
	applymovement 9, TeamRocketBaseB3F_Johto_RocketBaseRivalEnterMovement
	waitmovement 9
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Left
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	message TeamRocketBaseB3F_Johto_RocketBaseRivalText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_M_TAIL_WHIP
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB3F_Johto_RocketBaseRivalShovesPlayerMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 9, TeamRocketBaseB3F_Johto_RocketBaseRivalLeavesMovement
	waitmovement 9
	removeobject 9
	setvar VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B3F, 2
	fadedefaultbgm
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FRocketScript:
	faceplayer
	message TeamRocketBaseB3F_Johto_TeamRocketBaseB3FRocketText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB3F_Johto_RocketBaseBossLeft:
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB3F_Johto_RocketBasePlayerApproachesBossLeftMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto TeamRocketBaseB3F_Johto_RocketBaseBoss

TeamRocketBaseB3F_Johto_RocketBaseBossRight:
	applymovement OBJ_EVENT_ID_PLAYER, TeamRocketBaseB3F_Johto_RocketBasePlayerApproachesBossRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER

TeamRocketBaseB3F_Johto_RocketBaseBoss:
	delay 30
	applymovement 2, Johto_Movement_Emote_exclamation_mark
	waitmovement 2
	playbgm MUS_DUMMY, FALSE
	applymovement 2, Johto_Movement_Face_Down
	waitmovement 2
	message TeamRocketBaseB3F_Johto_ExecutiveM4BeforeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, TeamRocketBaseB3F_Johto_RocketBaseBossApproachesPlayerMovement
	waitmovement 2
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_JOHTO_EXECUTIVEM_EXECUTIVEM_4, TeamRocketBaseB3F_Johto_ExecutiveM4BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_EXECUTIVEM_4
	message TeamRocketBaseB3F_Johto_ExecutiveM4AfterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, TeamRocketBaseB3F_Johto_RocketBaseBossHitsTableMovement
	waitmovement 2
	playse SE_M_TAIL_WHIP
	applymovement 2, TeamRocketBaseB3F_Johto_RocketBaseBossLeavesMovement
	waitmovement 2
	removeobject 2
	setvar VAR_JOHTO_SCENE_TEAM_ROCKET_BASE_B3F, 3
	releaseall
	end

TeamRocketBaseB3F_Johto_RocketBaseMurkrow:
	message TeamRocketBaseB3F_Johto_RocketBaseMurkrowText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_LEARNED_HAIL_GIOVANNI
	releaseall
	end

TeamRocketBaseB3F_Johto_SlowpokeTailGrunt::
	trainerbattle_single TRAINER_JOHTO_GRUNTF_GRUNTF_5, TeamRocketBaseB3F_Johto_GruntF5SeenText, TeamRocketBaseB3F_Johto_GruntF5BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTF_5
	lock
	faceplayer
	goto TeamRocketBaseB3F_Johto_GruntF5Script

TeamRocketBaseB3F_Johto_GruntF5Script:
	message TeamRocketBaseB3F_Johto_GruntF5AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_LEARNED_SLOWPOKETAIL
	releaseall
	end

TeamRocketBaseB3F_Johto_RaticateTailGrunt::
	trainerbattle_single TRAINER_JOHTO_GRUNTM_GRUNTM_28, TeamRocketBaseB3F_Johto_GruntM28SeenText, TeamRocketBaseB3F_Johto_GruntM28BeatenText
	setflag FLAG_JOHTO_BEAT_ROCKET_GRUNTM_28
	lock
	faceplayer
	goto TeamRocketBaseB3F_Johto_GruntM28Script

TeamRocketBaseB3F_Johto_GruntM28Script:
	message TeamRocketBaseB3F_Johto_GruntM28AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_LEARNED_RATICATE_TAIL
	releaseall
	end

TeamRocketBaseB3F_Johto_TrainerScientistRoss::
	trainerbattle_single TRAINER_JOHTO_SCIENTIST_ROSS, TeamRocketBaseB3F_Johto_ScientistRossSeenText, TeamRocketBaseB3F_Johto_ScientistRossBeatenText
	setflag FLAG_JOHTO_BEAT_SCIENTIST_ROSS
	lock
	faceplayer
	goto TeamRocketBaseB3F_Johto_TrainerScientistRoss_Script

TeamRocketBaseB3F_Johto_TrainerScientistRoss_Script:
	message TeamRocketBaseB3F_Johto_ScientistRossAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB3F_Johto_TrainerScientistMitch::
	trainerbattle_single TRAINER_JOHTO_SCIENTIST_MITCH, TeamRocketBaseB3F_Johto_ScientistMitchSeenText, TeamRocketBaseB3F_Johto_ScientistMitchBeatenText
	setflag FLAG_JOHTO_BEAT_SCIENTIST_MITCH
	lock
	faceplayer
	goto TeamRocketBaseB3F_Johto_TrainerScientistMitch_Script

TeamRocketBaseB3F_Johto_TrainerScientistMitch_Script:
	message TeamRocketBaseB3F_Johto_ScientistMitchAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FOathScript:
	goto Johto_Std_TeamRocketOathScript

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FProtein:
	finditem ITEM_PROTEIN
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FXSpecial:
	finditem ITEM_X_SPECIAL
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FFullHeal:
	finditem ITEM_FULL_HEAL
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FIceHeal:
	finditem ITEM_ICE_HEAL
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FUltraBall:
	finditem ITEM_ULTRA_BALL
	releaseall
	end

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FCheckGiovanniDoorCallback_Cb:
	goto_if_set FLAG_JOHTO_OPENED_DOOR_TO_GIOVANNIS_OFFICE, TeamRocketBaseB3F_Johto_TeamRocketBaseB3FCheckGiovanniDoorCallback_OpenSesame_Cb
	return

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FCheckGiovanniDoorCallback_OpenSesame_Cb:
	setmetatile 10, 8, 514, 0
	setmetatile 11, 8, 514, 0
	setmetatile 10, 9, 514, 0
	setmetatile 11, 9, 514, 0
	special DrawWholeMapView
	return

TeamRocketBaseB3F_Johto_RocketBaseLanceApproachesPlayerMovement:
	walk_right
	step_end

TeamRocketBaseB3F_Johto_RocketBaseLanceLeavesMovement:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

TeamRocketBaseB3F_Johto_RocketBasePlayerApproachesBossLeftMovement:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	face_up
	step_end

TeamRocketBaseB3F_Johto_RocketBasePlayerApproachesBossRightMovement:
	walk_up
	walk_up
	walk_left
	walk_up
	walk_left
	walk_left
	face_up
	step_end

TeamRocketBaseB3F_Johto_RocketBaseBossApproachesPlayerMovement:
	walk_down
	step_end

TeamRocketBaseB3F_Johto_RocketBaseBossHitsTableMovement:
	walk_fast_right
	walk_fast_right
	step_end

TeamRocketBaseB3F_Johto_RocketBaseBossLeavesMovement:
	lock_facing_direction
	jump_left
	unlock_facing_direction
	delay_8
	delay_8
	walk_slow_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

TeamRocketBaseB3F_Johto_RocketBaseRivalEnterMovement:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

TeamRocketBaseB3F_Johto_RocketBaseRivalLeavesMovement:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

TeamRocketBaseB3F_Johto_RocketBaseRivalShovesPlayerMovement:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

TeamRocketBaseB3F_Johto_LanceGetPasswordText:
	.string "LANCE: It takes\n"
	.string "two passwords to"
	.string "\pget into the\n"
	.string "boss's quarters."
	.string "\pThose passwords\n"
	.string "are known only to\l"
	.string "a few ROCKETS."
	.string "\pThat ROCKET there\n"
	.string "very graciously\l"
	.string "told me so."
	.string "\p{PLAYER}, let's go\n"
	.string "get the passwords.$"

TeamRocketBaseB3F_Johto_TeamRocketBaseB3FRocketText:
	.string "Urrggh… The guy\n"
	.string "in the cape is\l"
	.string "incredibly tough…$"

TeamRocketBaseB3F_Johto_RocketBaseRivalText:
	.string "…"
	.string "\pDidn't I tell you\n"
	.string "that I was going"
	.string "\pto destroy TEAM\n"
	.string "ROCKET?"
	.string "\p…Tell me, who was\n"
	.string "the guy in the"
	.string "\pcape who used\n"
	.string "dragon POKéMON?"
	.string "\pMy POKéMON were no\n"
	.string "match at all."
	.string "\pI don't care that\n"
	.string "I lost. I can beat"
	.string "\phim by getting\n"
	.string "stronger POKéMON."
	.string "\pIt's what he said\n"
	.string "that bothers me…"
	.string "\pHe told me that\n"
	.string "I don't love and"
	.string "\ptrust my POKéMON\n"
	.string "enough."
	.string "\pI'm furious that I\n"
	.string "lost to a bleeding\l"
	.string "heart like him."
	.string "\p…Humph! I don't\n"
	.string "have the time for\l"
	.string "the likes of you!$"

TeamRocketBaseB3F_Johto_ExecutiveM4BeforeText:
	.string "What? Who are you?\n"
	.string "This is the office"
	.string "\pof our leader,\n"
	.string "GIOVANNI."
	.string "\pSince disbanding\n"
	.string "TEAM ROCKET three"
	.string "\pyears ago, he has\n"
	.string "been in training."
	.string "\pBut we're certain\n"
	.string "he will be back"
	.string "\psome day to assume\n"
	.string "command again."
	.string "\pThat's why we're\n"
	.string "standing guard."
	.string "\pI won't let any-\n"
	.string "one disturb this\l"
	.string "place!$"

TeamRocketBaseB3F_Johto_ExecutiveM4BeatenText:
	.string "I… I couldn't do a\n"
	.string "thing…"
	.string "\pGIOVANNI, please\n"
	.string "forgive me…$"

TeamRocketBaseB3F_Johto_ExecutiveM4AfterText:
	.string "No, I can't let\n"
	.string "this affect me."
	.string "\pI have to inform\n"
	.string "the others…$"

TeamRocketBaseB3F_Johto_RocketBaseMurkrowText:
	.string "MURKROW: The\n"
	.string "password is…"
	.string "\pHAIL GIOVANNI.$"

TeamRocketBaseB3F_Johto_GruntF5SeenText:
	.string "Do I know the\n"
	.string "password?"
	.string "\pMaybe."
	.string "\pBut no weakling's\n"
	.string "going to get it!$"

TeamRocketBaseB3F_Johto_GruntF5BeatenText:
	.string "All right. Stop.\n"
	.string "I'll tell you.$"

TeamRocketBaseB3F_Johto_GruntF5AfterBattleText:
	.string "The password to\n"
	.string "the boss's room is"
	.string "\pSLOWPOKETAIL."
	.string "\pBut it's useless\n"
	.string "unless you have\l"
	.string "two passwords.$"

TeamRocketBaseB3F_Johto_GruntM28SeenText:
	.string "Hyuck-hyuck-hyuck!"
	.string "\pYou're challenging\n"
	.string "me to a battle?"
	.string "\pHah! You're nuts,\n"
	.string "but you have guts!"
	.string "\pI like that!"
	.string "\pIf you can beat\n"
	.string "me, I'll tell you"
	.string "\pa password to the\n"
	.string "boss's room!$"

TeamRocketBaseB3F_Johto_GruntM28BeatenText:
	.string "Hyuck-hyuck-hyuck!\n"
	.string "You're good!$"

TeamRocketBaseB3F_Johto_GruntM28AfterBattleText:
	.string "Hyuck-hyuck-hyuck!"
	.string "\pThe password to\n"
	.string "the boss's room…"
	.string "\pUh…, I think it is\n"
	.string "RATICATE TAIL.$"

TeamRocketBaseB3F_Johto_ScientistRossSeenText:
	.string "I used to work for\n"
	.string "SILPH, but now I"
	.string "\prun research for\n"
	.string "TEAM ROCKET."
	.string "\pA meddlesome child\n"
	.string "like you needs to\l"
	.string "be punished.$"

TeamRocketBaseB3F_Johto_ScientistRossBeatenText:
	.string "A mere tactical\n"
	.string "error cost me…$"

TeamRocketBaseB3F_Johto_ScientistRossAfterBattleText:
	.string "A radio signal\n"
	.string "that drives POKé-\l"
	.string "MON mad…"
	.string "\pMy experiment is a\n"
	.string "complete success."
	.string "\pMy promotion is\n"
	.string "assured. This loss"
	.string "\pmeans absolutely\n"
	.string "nothing.$"

TeamRocketBaseB3F_Johto_ScientistMitchSeenText:
	.string "I don't care that\n"
	.string "POKéMON are hurt\l"
	.string "by our experiment.$"

TeamRocketBaseB3F_Johto_ScientistMitchBeatenText:
	.string "Thinking is my\n"
	.string "strong suit, not\l"
	.string "battling.$"

TeamRocketBaseB3F_Johto_ScientistMitchAfterBattleText:
	.string "If we turn up the\n"
	.string "power of our radio"
	.string "\psignal for broad-\n"
	.string "cast nationwide…"
	.string "\pThe very thought\n"
	.string "excites me!$"
