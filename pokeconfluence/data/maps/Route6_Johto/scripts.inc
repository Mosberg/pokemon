Route6_Johto_MapScripts::
	.byte 0

Route6_Johto_Route6PokefanMScript_Entry::
	lockall
	goto Route6_Johto_Route6PokefanMScript

Route6_Johto_Route6UndergroundPathSign_Entry::
	lockall
	goto Route6_Johto_Route6UndergroundPathSign


Route6_Johto_TrainerPokefanmRex::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_REX, Route6_Johto_PokefanmRexSeenText, Route6_Johto_PokefanmRexBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_REX
	lock
	faceplayer
	goto Route6_Johto_TrainerPokefanmRex_Script

Route6_Johto_TrainerPokefanmRex_Script:
	message Route6_Johto_PokefanmRexAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6_Johto_TrainerPokefanmAllan::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_ALLAN, Route6_Johto_PokefanmAllanSeenText, Route6_Johto_PokefanmAllanBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_ALLAN
	lock
	faceplayer
	goto Route6_Johto_TrainerPokefanmAllan_Script

Route6_Johto_TrainerPokefanmAllan_Script:
	message Route6_Johto_PokefanmAllanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6_Johto_Route6PokefanMScript:
	faceplayer
	message Route6_Johto_Route6PokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6_Johto_Route6UndergroundPathSign:
	message Route6_Johto_Route6UndergroundPathSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6_Johto_Route6PokefanMText:
	.string "The road is closed\n"
	.string "until the problem"
	.string "\pat the POWER PLANT\n"
	.string "is solved.$"

Route6_Johto_Route6UndergroundPathSignText:
	.string "UNDERGROUND PATH"
	.string "\pCERULEAN CITY -\n"
	.string "VERMILION CITY$"

Route6_Johto_PokefanmRexSeenText:
	.string "My PHANPY is the\n"
	.string "cutest in the\l"
	.string "world.$"

Route6_Johto_PokefanmRexBeatenText:
	.string "My PHANPY!$"

Route6_Johto_PokefanmRexAfterBattleText:
	.string "Look how adorable\n"
	.string "my PHANPY acts!"
	.string "\pIsn't it cute\n"
	.string "enough to make\l"
	.string "your heart melt?$"

Route6_Johto_PokefanmAllanSeenText:
	.string "My TEDDIURSA is\n"
	.string "the cutest in the\l"
	.string "world.$"

Route6_Johto_PokefanmAllanBeatenText:
	.string "My TEDDIURSA!$"

Route6_Johto_PokefanmAllanAfterBattleText:
	.string "Look how adorable\n"
	.string "my TEDDIURSA acts!"
	.string "\pIsn't it cute\n"
	.string "enough to make\l"
	.string "your heart melt?$"
