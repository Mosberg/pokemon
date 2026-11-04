Route6SaffronGate_Johto_MapScripts::
	.byte 0

Route6SaffronGate_Johto_Route6SaffronGuardScript_Entry::
	lockall
	goto Route6SaffronGate_Johto_Route6SaffronGuardScript


Route6SaffronGate_Johto_Route6SaffronGuardScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, Route6SaffronGate_Johto_Route6SaffronGuardScript_ReturnedPart
	message Route6SaffronGate_Johto_Route6SaffronGuardWelcomeText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6SaffronGate_Johto_Route6SaffronGuardScript_ReturnedPart:
	message Route6SaffronGate_Johto_Route6SaffronGuardMagnetTrainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

Route6SaffronGate_Johto_Route6SaffronGuardWelcomeText:
	.string "Welcome to SAFFRON\n"
	.string "CITY, home of the\l"
	.string "MAGNET TRAIN!"
	.string "\p…That's what I'd\n"
	.string "normally say, but"
	.string "\pthe MAGNET TRAIN\n"
	.string "isn't running now."
	.string "\pIt's not getting\n"
	.string "any electricity"
	.string "\pbecause there's\n"
	.string "something wrong"
	.string "\pwith the POWER\n"
	.string "PLANT.$"

Route6SaffronGate_Johto_Route6SaffronGuardMagnetTrainText:
	.string "The MAGNET TRAIN\n"
	.string "is the most famous"
	.string "\pthing about SAF-\n"
	.string "FRON.$"
