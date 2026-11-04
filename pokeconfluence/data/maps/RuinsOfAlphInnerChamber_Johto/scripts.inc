RuinsOfAlphInnerChamber_Johto_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlphInnerChamber_Johto_OnFrame
	.byte 0

RuinsOfAlphInnerChamber_Johto_OnFrame:
	map_script_2 VAR_JOHTO_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 1, RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStrangePresenceScript_Entry
	.2byte 0

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberFisherScript_Entry::
	lockall
	goto RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberFisherScript

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberTeacherScript_Entry::
	lockall
	goto RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberTeacherScript

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberGrampsScript_Entry::
	lockall
	goto RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberGrampsScript

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStatue_Entry::
	lockall
	goto RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStatue

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStrangePresenceScript_Entry::
	lockall
	goto RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStrangePresenceScript


RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStrangePresenceScript:
	message RuinsOfAlphInnerChamber_Johto_RuinsOfAlphStrangePresenceText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_JOHTO_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 0
	setflag FLAG_JOHTO_MADE_UNOWN_APPEAR_IN_RUINS
	clearflag FLAG_JOHTO_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER
	releaseall
	end

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberFisherScript:
	faceplayer
	message RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberFisherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberTeacherScript:
	faceplayer
	message RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberGrampsScript:
	faceplayer
	message RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStatue:
	message RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStatueText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphStrangePresenceText:
	.string "There is a strange\n"
	.string "presence here…$"

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberFisherText:
	.string "This is a big\n"
	.string "room, but there's\l"
	.string "nothing here.$"

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberTeacherText:
	.string "This place has a\n"
	.string "mystical quality\l"
	.string "to it."
	.string "\pIt feels sort of\n"
	.string "ethereal even.$"

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberGrampsText:
	.string "Ancient buildings\n"
	.string "are often tombs of\l"
	.string "kings."
	.string "\pLike the pyramids,\n"
	.string "for instance.$"

RuinsOfAlphInnerChamber_Johto_RuinsOfAlphInnerChamberStatueText:
	.string "It's a replica of\n"
	.string "an ancient POKé-\l"
	.string "MON.$"
