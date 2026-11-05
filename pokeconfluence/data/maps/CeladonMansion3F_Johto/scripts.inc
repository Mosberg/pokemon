CeladonMansion3F_Johto_MapScripts::
	.byte 0

CeladonMansion3F_Johto_GameFreakGameDesignerScript_Entry::
	lockall
	goto CeladonMansion3F_Johto_GameFreakGameDesignerScript

CeladonMansion3F_Johto_GameFreakGraphicArtistScript_Entry::
	lockall
	goto CeladonMansion3F_Johto_GameFreakGraphicArtistScript

CeladonMansion3F_Johto_GameFreakProgrammerScript_Entry::
	lockall
	goto CeladonMansion3F_Johto_GameFreakProgrammerScript

CeladonMansion3F_Johto_GameFreakCharacterDesignerScript_Entry::
	lockall
	goto CeladonMansion3F_Johto_GameFreakCharacterDesignerScript

CeladonMansion3F_Johto_CeladonMansion3FDevRoomSign_Entry::
	lockall
	goto CeladonMansion3F_Johto_CeladonMansion3FDevRoomSign

CeladonMansion3F_Johto_CeladonMansion3FDrawing_Entry::
	lockall
	goto CeladonMansion3F_Johto_CeladonMansion3FDrawing

CeladonMansion3F_Johto_CeladonMansion3FGameProgram_Entry::
	lockall
	goto CeladonMansion3F_Johto_CeladonMansion3FGameProgram

CeladonMansion3F_Johto_CeladonMansion3FReferenceMaterial_Entry::
	lockall
	goto CeladonMansion3F_Johto_CeladonMansion3FReferenceMaterial


CeladonMansion3F_Johto_GameFreakGameDesignerScript:
	faceplayer
	message CeladonMansion3F_Johto_GameFreakGameDesignerText
	waitmessage
	special JohtoGetDexCaught
	goto_if_gt VAR_RESULT, 248, CeladonMansion3F_Johto_GameFreakGameDesignerScript_CompletedPokedex
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakGameDesignerScript_CompletedPokedex:
	waitbuttonpress
	message CeladonMansion3F_Johto_GameFreakGameDesignerCompletedPokedexText
	waitmessage
	playse SE_PIN
	waitse
	message CeladonMansion3F_Johto_GameFreakGameDesignerPauseForDiplomaText
	waitmessage
	waitbuttonpress
	message CeladonMansion3F_Johto_GameFreakGameDesignerAfterDiplomaText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_ENABLE_DIPLOMA_PRINTING
	releaseall
	end

CeladonMansion3F_Johto_GameFreakGraphicArtistScript:
	faceplayer
	goto_if_set FLAG_JOHTO_ENABLE_DIPLOMA_PRINTING, CeladonMansion3F_Johto_GameFreakGraphicArtistScript_CanPrintDiploma
	message CeladonMansion3F_Johto_GameFreakGraphicArtistText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakGraphicArtistScript_CanPrintDiploma:
	message CeladonMansion3F_Johto_GameFreakGraphicArtistPrintDiplomaText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, CeladonMansion3F_Johto_GameFreakGraphicArtistScript_Refused
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakGraphicArtistScript_Refused:
	message CeladonMansion3F_Johto_GameFreakGraphicArtistRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakProgrammerScript:
	faceplayer
	message CeladonMansion3F_Johto_GameFreakProgrammerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakCharacterDesignerScript:
	faceplayer
	message CeladonMansion3F_Johto_GameFreakCharacterDesignerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_CeladonMansion3FDevRoomSign:
	message CeladonMansion3F_Johto_CeladonMansion3FDevRoomSignText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_CeladonMansion3FDrawing:
	message CeladonMansion3F_Johto_CeladonMansion3FDrawingText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_CeladonMansion3FGameProgram:
	message CeladonMansion3F_Johto_CeladonMansion3FGameProgramText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_CeladonMansion3FReferenceMaterial:
	message CeladonMansion3F_Johto_CeladonMansion3FReferenceMaterialText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

CeladonMansion3F_Johto_GameFreakGameDesignerText:
	.string "Is that right?"
	.string "\pI'm the GAME\n"
	.string "DESIGNER!"
	.string "\pFilling up your\n"
	.string "POKéDEX is tough,\l"
	.string "but don't give up!$"

CeladonMansion3F_Johto_GameFreakGameDesignerCompletedPokedexText:
	.string "Wow! Excellent!\n"
	.string "You completed your\l"
	.string "POKéDEX!"
	.string "\pCongratulations!$"

CeladonMansion3F_Johto_GameFreakGameDesignerPauseForDiplomaText:
	.string "…$"

CeladonMansion3F_Johto_GameFreakGameDesignerAfterDiplomaText:
	.string "The GRAPHIC ARTIST\n"
	.string "will print out a\l"
	.string "DIPLOMA for you."
	.string "\pYou should go show\n"
	.string "it off.$"

CeladonMansion3F_Johto_GameFreakGraphicArtistText:
	.string "I'm the GRAPHIC\n"
	.string "ARTIST."
	.string "\pI drew you!$"

CeladonMansion3F_Johto_GameFreakGraphicArtistPrintDiplomaText:
	.string "I'm the GRAPHIC\n"
	.string "ARTIST."
	.string "\pOh, you completed\n"
	.string "your POKéDEX?"
	.string "\pWant me to print\n"
	.string "out your DIPLOMA?$"

CeladonMansion3F_Johto_GameFreakGraphicArtistRefusedText:
	.string "Give me a shout if\n"
	.string "you want your\l"
	.string "DIPLOMA printed.$"

CeladonMansion3F_Johto_GameFreakProgrammerText:
	.string "Who, me? I'm the\n"
	.string "PROGRAMMER."
	.string "\pPlay the slot\n"
	.string "machines!$"

CeladonMansion3F_Johto_GameFreakCharacterDesignerText:
	.string "Aren't the TWINS\n"
	.string "adorable?"
	.string "\pJASMINE's pretty\n"
	.string "too."
	.string "\pOh, I love them!$"

CeladonMansion3F_Johto_CeladonMansion3FDevRoomSignText:
	.string "GAME FREAK\n"
	.string "DEVELOPMENT ROOM$"

CeladonMansion3F_Johto_CeladonMansion3FDrawingText:
	.string "It's a detailed\n"
	.string "drawing of a\l"
	.string "pretty girl.$"

CeladonMansion3F_Johto_CeladonMansion3FGameProgramText:
	.string "It's the game\n"
	.string "program. Messing"
	.string "\pwith it could put\n"
	.string "a bug in the game!$"

CeladonMansion3F_Johto_CeladonMansion3FReferenceMaterialText:
	.string "It's crammed with\n"
	.string "reference materi-\l"
	.string "als. There's even\l"
	.string "a POKé DOLL.$"
