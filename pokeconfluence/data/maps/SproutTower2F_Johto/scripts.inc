SproutTower2F_Johto_MapScripts::
	.byte 0

SproutTower2F_Johto_SproutTower2FXAccuracy_Entry::
	lockall
	goto SproutTower2F_Johto_SproutTower2FXAccuracy

SproutTower2F_Johto_SproutTower2FStatue_Entry::
	lockall
	goto SproutTower2F_Johto_SproutTower2FStatue


SproutTower2F_Johto_TrainerSageNico::
	trainerbattle_single TRAINER_JOHTO_SAGE_NICO, SproutTower2F_Johto_SageNicoSeenText, SproutTower2F_Johto_SageNicoBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_NICO
	lock
	faceplayer
	goto SproutTower2F_Johto_TrainerSageNico_Script

SproutTower2F_Johto_TrainerSageNico_Script:
	message SproutTower2F_Johto_SageNicoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower2F_Johto_TrainerSageEdmond::
	trainerbattle_single TRAINER_JOHTO_SAGE_EDMOND, SproutTower2F_Johto_SageEdmondSeenText, SproutTower2F_Johto_SageEdmondBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_EDMOND
	lock
	faceplayer
	goto SproutTower2F_Johto_TrainerSageEdmond_Script

SproutTower2F_Johto_TrainerSageEdmond_Script:
	message SproutTower2F_Johto_SageEdmondAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower2F_Johto_SproutTower2FStatue:
	message SproutTower2F_Johto_SproutTower2FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower2F_Johto_SproutTower2FXAccuracy:
	finditem ITEM_X_ACCURACY
	releaseall
	end

SproutTower2F_Johto_SageNicoSeenText:
	.string "However hard we\n"
	.string "battle, the TOWER\l"
	.string "will stand strong.$"

SproutTower2F_Johto_SageNicoBeatenText:
	.string "I fought hard but\n"
	.string "I'm too weak.$"

SproutTower2F_Johto_SageNicoAfterBattleText:
	.string "The flexible pil-\n"
	.string "lar protects the"
	.string "\pTOWER, even from\n"
	.string "earthquakes.$"

SproutTower2F_Johto_SageEdmondSeenText:
	.string "…Sway like leaves\n"
	.string "in the wind…$"

SproutTower2F_Johto_SageEdmondBeatenText:
	.string "Oh, I'm weak!$"

SproutTower2F_Johto_SageEdmondAfterBattleText:
	.string "I tried to copy\n"
	.string "BELLSPROUT's"
	.string "\pgentle movements\n"
	.string "for battle…"
	.string "\pBut I didn't train\n"
	.string "well enough.$"

SproutTower2F_Johto_SproutTower2FStatueText:
	.string "A POKéMON statue…"
	.string "\pIt looks very\n"
	.string "distinguished.$"
