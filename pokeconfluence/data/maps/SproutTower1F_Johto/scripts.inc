SproutTower1F_Johto_MapScripts::
	.byte 0

SproutTower1F_Johto_SproutTower1FSage1Script_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FSage1Script

SproutTower1F_Johto_SproutTower1FSage2Script_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FSage2Script

SproutTower1F_Johto_SproutTower1FGrannyScript_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FGrannyScript

SproutTower1F_Johto_SproutTower1FTeacherScript_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FTeacherScript

SproutTower1F_Johto_SproutTower1FParlyzHeal_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FParlyzHeal

SproutTower1F_Johto_SproutTower1FStatue_Entry::
	lockall
	goto SproutTower1F_Johto_SproutTower1FStatue


SproutTower1F_Johto_SproutTower1FSage1Script:
	faceplayer
	message SproutTower1F_Johto_SproutTower1FSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_SproutTower1FSage2Script:
	faceplayer
	message SproutTower1F_Johto_SproutTower1FSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_SproutTower1FGrannyScript:
	faceplayer
	message SproutTower1F_Johto_SproutTower1FGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_SproutTower1FTeacherScript:
	faceplayer
	message SproutTower1F_Johto_SproutTower1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_TrainerSageChow::
	trainerbattle_single TRAINER_JOHTO_SAGE_CHOW, SproutTower1F_Johto_SageChowSeenText, SproutTower1F_Johto_SageChowBeatenText
	setflag FLAG_JOHTO_BEAT_SAGE_CHOW
	lock
	faceplayer
	goto SproutTower1F_Johto_TrainerSageChow_Script

SproutTower1F_Johto_TrainerSageChow_Script:
	message SproutTower1F_Johto_SageChowAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_SproutTower1FParlyzHeal:
	finditem ITEM_PARLYZ_HEAL
	releaseall
	end

SproutTower1F_Johto_SproutTower1FStatue:
	message SproutTower1F_Johto_SproutTower1FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

SproutTower1F_Johto_SageChowSeenText:
	.string "We stand guard in\n"
	.string "this tower."
	.string "\pHere, we express\n"
	.string "our gratitude to\l"
	.string "honor all POKéMON.$"

SproutTower1F_Johto_SageChowBeatenText:
	.string "Th-Thank you!$"

SproutTower1F_Johto_SageChowAfterBattleText:
	.string "All living beings\n"
	.string "coexist through\l"
	.string "cooperation."
	.string "\pWe must always be\n"
	.string "thankful for this.$"

SproutTower1F_Johto_SproutTower1FSage1Text:
	.string "Only if you reach\n"
	.string "the top will you\l"
	.string "obtain an HM.$"

SproutTower1F_Johto_SproutTower1FSage2Text:
	.string "SPROUT TOWER was\n"
	.string "built long ago"
	.string "\pas a place for\n"
	.string "POKéMON training.$"

SproutTower1F_Johto_SproutTower1FGrannyText:
	.string "A BELLSPROUT over\n"
	.string "100 feet tall…"
	.string "\pPeople say that it\n"
	.string "became the center\l"
	.string "pillar here.$"

SproutTower1F_Johto_SproutTower1FTeacherText:
	.string "See the pillar\n"
	.string "shaking?"
	.string "\pPeople are train-\n"
	.string "ing upstairs.$"

SproutTower1F_Johto_SproutTower1FStatueText:
	.string "A POKéMON statue…"
	.string "\pIt looks very\n"
	.string "distinguished.$"
