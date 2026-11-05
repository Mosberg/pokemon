BlackthornGym2F_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornGym2F_Johto_OnTransition
	.byte 0

BlackthornGym2F_Johto_OnTransition:
	call BlackthornGym2F_Johto_BlackthornGym2FSetUpStoneTableCallback_Cb
	end

BlackthornGym2F_Johto_BlackthornGymBoulder_Entry::
	lockall
	goto BlackthornGym2F_Johto_BlackthornGymBoulder


BlackthornGym2F_Johto_BlackthornGymBoulder:
	goto Johto_Std_StrengthBoulderScript

BlackthornGym2F_Johto_TrainerCooltrainermCody::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERM_CODY, BlackthornGym2F_Johto_CooltrainermCodySeenText, BlackthornGym2F_Johto_CooltrainermCodyBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERM_CODY
	lock
	faceplayer
	goto BlackthornGym2F_Johto_TrainerCooltrainermCody_Script

BlackthornGym2F_Johto_TrainerCooltrainermCody_Script:
	message BlackthornGym2F_Johto_CooltrainermCodyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym2F_Johto_TrainerCooltrainerfFran::
	trainerbattle_single TRAINER_JOHTO_COOLTRAINERF_FRAN, BlackthornGym2F_Johto_CooltrainerfFranSeenText, BlackthornGym2F_Johto_CooltrainerfFranBeatenText
	setflag FLAG_JOHTO_BEAT_COOLTRAINERF_FRAN
	lock
	faceplayer
	goto BlackthornGym2F_Johto_TrainerCooltrainerfFran_Script

BlackthornGym2F_Johto_TrainerCooltrainerfFran_Script:
	message BlackthornGym2F_Johto_CooltrainerfFranAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BlackthornGym2F_Johto_BlackthornGym2FSetUpStoneTableCallback_Cb:
	return

BlackthornGym2F_Johto_CooltrainermCodySeenText:
	.string "It's not as if we\n"
	.string "all use dragon-\l"
	.string "type POKéMON.$"

BlackthornGym2F_Johto_CooltrainermCodyBeatenText:
	.string "Rats! If only I\n"
	.string "had a dragon!$"

BlackthornGym2F_Johto_CooltrainermCodyAfterBattleText:
	.string "Members of our\n"
	.string "dragon-user clan"
	.string "\pcan use dragon\n"
	.string "POKéMON only after"
	.string "\pour MASTER allows\n"
	.string "it.$"

BlackthornGym2F_Johto_CooltrainerfFranSeenText:
	.string "I can't allow a\n"
	.string "nameless trainer\l"
	.string "past me!"
	.string "\pCLAIR would be\n"
	.string "livid if I did!$"

BlackthornGym2F_Johto_CooltrainerfFranBeatenText:
	.string "Awww… I lost…$"

BlackthornGym2F_Johto_CooltrainerfFranAfterBattleText:
	.string "Uh-oh… CLAIR is\n"
	.string "going to be mad…$"
