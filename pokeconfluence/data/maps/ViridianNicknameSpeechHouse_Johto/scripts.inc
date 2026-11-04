ViridianNicknameSpeechHouse_Johto_MapScripts::
	.byte 0

ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHousePokefanMScript_Entry::
	lockall
	goto ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHousePokefanMScript

ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHouseLassScript_Entry::
	lockall
	goto ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHouseLassScript

ViridianNicknameSpeechHouse_Johto_Speary_Entry::
	lockall
	goto ViridianNicknameSpeechHouse_Johto_Speary

ViridianNicknameSpeechHouse_Johto_Rattey_Entry::
	lockall
	goto ViridianNicknameSpeechHouse_Johto_Rattey


ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHousePokefanMScript:
	faceplayer
	message ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHousePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHouseLassScript:
	faceplayer
	message ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianNicknameSpeechHouse_Johto_Speary:
	message ViridianNicknameSpeechHouse_Johto_SpearyText
	waitmessage
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianNicknameSpeechHouse_Johto_Rattey:
	message ViridianNicknameSpeechHouse_Johto_RatteyText
	waitmessage
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	releaseall
	end

ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHousePokefanMText:
	.string "Do you put a lot\n"
	.string "of thought into"
	.string "\pnaming your\n"
	.string "POKéMON?"
	.string "\pGiving them good\n"
	.string "nicknames adds to"
	.string "\pthe fun of trading\n"
	.string "with others.$"

ViridianNicknameSpeechHouse_Johto_ViridianNicknameSpeechHouseLassText:
	.string "They're SPEARY--\n"
	.string "a SPEAROW--and\l"
	.string "RATTEY--a RATTATA.$"

ViridianNicknameSpeechHouse_Johto_SpearyText:
	.string "SPEARY: Ch-chun!$"

ViridianNicknameSpeechHouse_Johto_RatteyText:
	.string "RATTEY: Kikiii!$"
