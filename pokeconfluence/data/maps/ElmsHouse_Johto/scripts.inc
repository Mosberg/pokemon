ElmsHouse_Johto_MapScripts::
	.byte 0

ElmsHouse_Johto_ElmsWife_Entry::
	lockall
	goto ElmsHouse_Johto_ElmsWife

ElmsHouse_Johto_ElmsSon_Entry::
	lockall
	goto ElmsHouse_Johto_ElmsSon

ElmsHouse_Johto_ElmsHousePC_Entry::
	lockall
	goto ElmsHouse_Johto_ElmsHousePC

ElmsHouse_Johto_ElmsHouseBookshelf_Entry::
	lockall
	goto ElmsHouse_Johto_ElmsHouseBookshelf


ElmsHouse_Johto_ElmsWife:
	faceplayer
	message ElmsHouse_Johto_ElmsWifeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsHouse_Johto_ElmsSon:
	faceplayer
	message ElmsHouse_Johto_ElmsSonText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsHouse_Johto_ElmsHousePC:
	message ElmsHouse_Johto_ElmsHousePCText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ElmsHouse_Johto_ElmsHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

ElmsHouse_Johto_ElmsWifeText:
	.string "Hi, {PLAYER}! My\n"
	.string "husband's always"
	.string "\pso busy--I hope\n"
	.string "he's OK."
	.string "\pWhen he's caught\n"
	.string "up in his POKéMON"
	.string "\presearch, he even\n"
	.string "forgets to eat.$"

ElmsHouse_Johto_ElmsSonText:
	.string "When I grow up,\n"
	.string "I'm going to help\l"
	.string "my dad!"
	.string "\pI'm going to be a\n"
	.string "great POKéMON\l"
	.string "professor!$"

ElmsHouse_Johto_ElmsHousePCText:
	.string "POKéMON. Where do\n"
	.string "they come from? "
	.string "\pWhere are they\n"
	.string "going?"
	.string "\pWhy has no one\n"
	.string "ever witnessed a\l"
	.string "POKéMON's birth?"
	.string "\pI want to know! I\n"
	.string "will dedicate my"
	.string "\plife to the study\n"
	.string "of POKéMON!"
	.string "\p…"
	.string "\pIt's a part of\n"
	.string "PROF.ELM's re-\l"
	.string "search papers.$"
