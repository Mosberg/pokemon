FuchsiaGym_Johto_MapScripts::
	.byte 0

FuchsiaGym_Johto_FuchsiaGymJanineScript_Entry::
	lockall
	goto FuchsiaGym_Johto_FuchsiaGymJanineScript

FuchsiaGym_Johto_LassAliceScript_Entry::
	lockall
	goto FuchsiaGym_Johto_LassAliceScript

FuchsiaGym_Johto_LassLindaScript_Entry::
	lockall
	goto FuchsiaGym_Johto_LassLindaScript

FuchsiaGym_Johto_PicnickerCindyScript_Entry::
	lockall
	goto FuchsiaGym_Johto_PicnickerCindyScript

FuchsiaGym_Johto_CamperBarryScript_Entry::
	lockall
	goto FuchsiaGym_Johto_CamperBarryScript

FuchsiaGym_Johto_FuchsiaGymGuideScript_Entry::
	lockall
	goto FuchsiaGym_Johto_FuchsiaGymGuideScript

FuchsiaGym_Johto_FuchsiaGymStatue_Entry::
	lockall
	goto FuchsiaGym_Johto_FuchsiaGymStatue


FuchsiaGym_Johto_FuchsiaGymJanineScript:
	goto_if_set FLAG_JOHTO_ENGINE_SOULBADGE, FuchsiaGym_Johto_FuchsiaGymJanineScript_FightDone
	applymovement 1, FuchsiaGym_Johto_Movement_NinjaSpin
	waitmovement 1
	faceplayer
	message FuchsiaGym_Johto_JanineText_DisappointYou
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_JANINE_JANINE1, FuchsiaGym_Johto_JanineText_ToughOne
	setflag FLAG_JOHTO_BEAT_JANINE
	setflag FLAG_JOHTO_BEAT_LASS_ALICE
	setflag FLAG_JOHTO_BEAT_LASS_LINDA
	setflag FLAG_JOHTO_BEAT_PICNICKER_CINDY
	setflag FLAG_JOHTO_BEAT_CAMPER_BARRY
	message FuchsiaGym_Johto_Text_ReceivedSoulBadge
	waitmessage
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	waitse
	setflag FLAG_JOHTO_ENGINE_SOULBADGE
	goto FuchsiaGym_Johto_FuchsiaGymJanineScript_AfterBattle

FuchsiaGym_Johto_FuchsiaGymJanineScript_FightDone:
	faceplayer

FuchsiaGym_Johto_FuchsiaGymJanineScript_AfterBattle:
	goto_if_set FLAG_JOHTO_GOT_TM06_TOXIC, FuchsiaGym_Johto_FuchsiaGymJanineScript_AfterTM
	message FuchsiaGym_Johto_JanineText_ToxicSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_TOXIC
	goto_if_eq VAR_RESULT, 0, FuchsiaGym_Johto_FuchsiaGymJanineScript_AfterTM
	setflag FLAG_JOHTO_GOT_TM06_TOXIC

FuchsiaGym_Johto_FuchsiaGymJanineScript_AfterTM:
	message FuchsiaGym_Johto_JanineText_ApplyMyself
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_LassAliceScript:
	goto_if_set FLAG_JOHTO_BEAT_LASS_ALICE, FuchsiaGym_Johto_LassAliceScript_AliceUnmasked
	applymovement 2, FuchsiaGym_Johto_Movement_NinjaSpin
	waitmovement 2
	faceplayer

FuchsiaGym_Johto_LassAliceScript_AliceUnmasked:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_LASS_ALICE, FuchsiaGym_Johto_LassAliceScript_AliceAfterScript
	message FuchsiaGym_Johto_LassAliceBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_LASS_ALICE, FuchsiaGym_Johto_LassAliceBeatenText
	goto_if_set FLAG_JOHTO_BEAT_LASS_ALICE, FuchsiaGym_Johto_LassAliceScript_AliceBecomesJanine
	setflag FLAG_JOHTO_BEAT_LASS_ALICE
	releaseall
	end

FuchsiaGym_Johto_LassAliceScript_AliceBecomesJanine:
	releaseall
	end

FuchsiaGym_Johto_LassAliceScript_AliceAfterScript:
	message FuchsiaGym_Johto_LassAliceAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_LassLindaScript:
	goto_if_set FLAG_JOHTO_BEAT_LASS_LINDA, FuchsiaGym_Johto_LassLindaScript_LindaUnmasked
	applymovement 3, FuchsiaGym_Johto_Movement_NinjaSpin
	waitmovement 3
	faceplayer

FuchsiaGym_Johto_LassLindaScript_LindaUnmasked:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_LASS_LINDA, FuchsiaGym_Johto_LassLindaScript_LindaAfterScript
	message FuchsiaGym_Johto_LassLindaBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_LASS_LINDA, FuchsiaGym_Johto_LassLindaBeatenText
	goto_if_set FLAG_JOHTO_BEAT_LASS_LINDA, FuchsiaGym_Johto_LassLindaScript_LindaBecomesJanine
	setflag FLAG_JOHTO_BEAT_LASS_LINDA
	releaseall
	end

FuchsiaGym_Johto_LassLindaScript_LindaBecomesJanine:
	releaseall
	end

FuchsiaGym_Johto_LassLindaScript_LindaAfterScript:
	message FuchsiaGym_Johto_LassLindaAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_PicnickerCindyScript:
	goto_if_set FLAG_JOHTO_BEAT_PICNICKER_CINDY, FuchsiaGym_Johto_PicnickerCindyScript_CindyUnmasked
	applymovement 4, FuchsiaGym_Johto_Movement_NinjaSpin
	waitmovement 4
	faceplayer

FuchsiaGym_Johto_PicnickerCindyScript_CindyUnmasked:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_PICNICKER_CINDY, FuchsiaGym_Johto_PicnickerCindyScript_CindyAfterScript
	message FuchsiaGym_Johto_PicnickerCindyBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_PICNICKER_CINDY, FuchsiaGym_Johto_PicnickerCindyBeatenText
	goto_if_set FLAG_JOHTO_BEAT_PICNICKER_CINDY, FuchsiaGym_Johto_PicnickerCindyScript_CindyBecomesJanine
	setflag FLAG_JOHTO_BEAT_PICNICKER_CINDY
	releaseall
	end

FuchsiaGym_Johto_PicnickerCindyScript_CindyBecomesJanine:
	releaseall
	end

FuchsiaGym_Johto_PicnickerCindyScript_CindyAfterScript:
	message FuchsiaGym_Johto_PicnickerCindyAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_CamperBarryScript:
	goto_if_set FLAG_JOHTO_BEAT_CAMPER_BARRY, FuchsiaGym_Johto_CamperBarryScript_BarryUnmasked
	applymovement 5, FuchsiaGym_Johto_Movement_NinjaSpin
	waitmovement 5
	faceplayer

FuchsiaGym_Johto_CamperBarryScript_BarryUnmasked:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_CAMPER_BARRY, FuchsiaGym_Johto_CamperBarryScript_BarryAfterScript
	message FuchsiaGym_Johto_CamperBarryBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_JOHTO_CAMPER_BARRY, FuchsiaGym_Johto_CamperBarryBeatenText
	goto_if_set FLAG_JOHTO_BEAT_CAMPER_BARRY, FuchsiaGym_Johto_CamperBarryScript_BarryBecomesJanine
	setflag FLAG_JOHTO_BEAT_CAMPER_BARRY
	releaseall
	end

FuchsiaGym_Johto_CamperBarryScript_BarryBecomesJanine:
	releaseall
	end

FuchsiaGym_Johto_CamperBarryScript_BarryAfterScript:
	message FuchsiaGym_Johto_CamperBarryAfterText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_FuchsiaGymGuideScript:
	faceplayer
	goto_if_set FLAG_JOHTO_BEAT_JANINE, FuchsiaGym_Johto_FuchsiaGymGuideScript_FuchsiaGymGuideWinScript
	message FuchsiaGym_Johto_FuchsiaGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_FuchsiaGymGuideScript_FuchsiaGymGuideWinScript:
	message FuchsiaGym_Johto_FuchsiaGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

FuchsiaGym_Johto_FuchsiaGymStatue:
	goto_if_set FLAG_JOHTO_ENGINE_SOULBADGE, FuchsiaGym_Johto_FuchsiaGymStatue_Beaten
	goto Johto_Std_GymStatue1Script

FuchsiaGym_Johto_FuchsiaGymStatue_Beaten:
	goto Johto_Std_GymStatue2Script

FuchsiaGym_Johto_Movement_NinjaSpin:
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end

FuchsiaGym_Johto_JanineText_DisappointYou:
	.string "Fufufufu…"
	.string "\pI'm sorry to dis-\n"
	.string "appoint you…"
	.string "\pI'm only joking!"
	.string "\pI'm the real deal!"
	.string "\pJANINE of FUCHSIA\n"
	.string "GYM, that's me!$"

FuchsiaGym_Johto_JanineText_ToughOne:
	.string "JANINE: You're a\n"
	.string "tough one. You\l"
	.string "definitely won…"
	.string "\pHere's SOULBADGE.\n"
	.string "Take it.$"

FuchsiaGym_Johto_Text_ReceivedSoulBadge:
	.string "{PLAYER} received\n"
	.string "SOULBADGE.$"

FuchsiaGym_Johto_JanineText_ToxicSpeech:
	.string "JANINE: You're so\n"
	.string "tough! I have a\l"
	.string "special gift!"
	.string "\pIt's TOXIC, a pow-\n"
	.string "erful poison that"
	.string "\psteadily saps the\n"
	.string "victim's HP.$"

FuchsiaGym_Johto_JanineText_ApplyMyself:
	.string "JANINE: I'm going\n"
	.string "to really apply"
	.string "\pmyself and improve\n"
	.string "my skills."
	.string "\pI want to become\n"
	.string "better than both\l"
	.string "Father and you!$"

FuchsiaGym_Johto_LassAliceBeforeText:
	.string "Fufufu!"
	.string "\pI'm JANINE, the\n"
	.string "GYM LEADER!"
	.string "\pNo, I'm not!\n"
	.string "Gotcha, sucker!$"

FuchsiaGym_Johto_LassAliceBeatenText:
	.string "I had you fooled…$"

FuchsiaGym_Johto_LassAliceAfterText:
	.string "How will you dis-\n"
	.string "tinguish our real\l"
	.string "LEADER?$"

FuchsiaGym_Johto_LassLindaBeforeText:
	.string "Fooled you!\n"
	.string "Hahaha!$"

FuchsiaGym_Johto_LassLindaBeatenText:
	.string "Ooh… I lost…\n"
	.string "You're not weak…$"

FuchsiaGym_Johto_LassLindaAfterText:
	.string "Well? Wasn't my\n"
	.string "disguise perfect?$"

FuchsiaGym_Johto_PicnickerCindyBeforeText:
	.string "I'm JANINE!"
	.string "\pHow did you know I\n"
	.string "was real?"
	.string "\pLet's battle!$"

FuchsiaGym_Johto_PicnickerCindyBeatenText:
	.string "Darn it!\n"
	.string "I wanted to win!$"

FuchsiaGym_Johto_PicnickerCindyAfterText:
	.string "You must be\n"
	.string "getting tired.$"

FuchsiaGym_Johto_CamperBarryBeforeText:
	.string "Wahahaha!"
	.string "\pYou betcha!\n"
	.string "I'm JANINE!$"

FuchsiaGym_Johto_CamperBarryBeatenText:
	.string "My disguise was\n"
	.string "right on! Dang!$"

FuchsiaGym_Johto_CamperBarryAfterText:
	.string "Hey, you. Was my\n"
	.string "disguise cute or\l"
	.string "what, huh?$"

FuchsiaGym_Johto_FuchsiaGymGuideText:
	.string "Yo, CHAMP in\n"
	.string "making!"
	.string "\pWhoops! Take a\n"
	.string "good look around"
	.string "\pyou. The trainers\n"
	.string "all look like the\l"
	.string "LEADER, JANINE."
	.string "\pWhich of them is\n"
	.string "the real JANINE?$"

FuchsiaGym_Johto_FuchsiaGymGuideWinText:
	.string "That was a great\n"
	.string "battle, trainer\l"
	.string "from JOHTO!$"
