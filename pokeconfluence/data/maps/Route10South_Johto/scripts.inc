Route10South_Johto_MapScripts::
	.byte 0

Route10South_Johto_Route10Sign_Entry::
	lockall
	goto Route10South_Johto_Route10Sign


Route10South_Johto_TrainerHikerJim::
	trainerbattle_single TRAINER_JOHTO_HIKER_JIM, Route10South_Johto_HikerJimSeenText, Route10South_Johto_HikerJimBeatenText
	setflag FLAG_JOHTO_BEAT_HIKER_JIM
	lock
	faceplayer
	goto Route10South_Johto_TrainerHikerJim_Script

Route10South_Johto_TrainerHikerJim_Script:
	message Route10South_Johto_HikerJimAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10South_Johto_TrainerPokefanmRobert::
	trainerbattle_single TRAINER_JOHTO_POKEFANM_ROBERT, Route10South_Johto_PokefanmRobertSeenText, Route10South_Johto_PokefanmRobertBeatenText
	setflag FLAG_JOHTO_BEAT_POKEFANM_ROBERT
	lock
	faceplayer
	goto Route10South_Johto_TrainerPokefanmRobert_Script

Route10South_Johto_TrainerPokefanmRobert_Script:
	message Route10South_Johto_PokefanmRobertAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10South_Johto_Route10Sign:
	message Route10South_Johto_Route10SignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route10South_Johto_HikerJimSeenText:
	.string "Hahahah!$"

Route10South_Johto_HikerJimBeatenText:
	.string "Hahaha-hachoo!$"

Route10South_Johto_HikerJimAfterBattleText:
	.string "Hay fever is\n"
	.string "making me sneeze!\l"
	.string "Ahahah-CHOO!$"

Route10South_Johto_PokefanmRobertSeenText:
	.string "You like POKéMON,\n"
	.string "don't you?"
	.string "\pMe too!$"

Route10South_Johto_PokefanmRobertBeatenText:
	.string "I'd have to say\n"
	.string "that's my loss.$"

Route10South_Johto_PokefanmRobertAfterBattleText:
	.string "Look what you did\n"
	.string "to my POKéMON…"
	.string "\pI won't forget\n"
	.string "this…$"

Route10South_Johto_Route10SignText:
	.string "ROUTE 10"
	.string "\pCERULEAN CITY -\n"
	.string "LAVENDER TOWN$"
