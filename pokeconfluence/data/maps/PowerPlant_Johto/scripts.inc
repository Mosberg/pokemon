PowerPlant_Johto_MapScripts::
	.byte 0

PowerPlant_Johto_PowerPlantOfficerScript_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantOfficerScript

PowerPlant_Johto_PowerPlantGymGuide1Script_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantGymGuide1Script

PowerPlant_Johto_PowerPlantGymGuide2Script_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantGymGuide2Script

PowerPlant_Johto_PowerPlantOfficer2Script_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantOfficer2Script

PowerPlant_Johto_PowerPlantGymGuide4Script_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantGymGuide4Script

PowerPlant_Johto_PowerPlantManager_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantManager

PowerPlant_Johto_Forest_Entry::
	lockall
	goto PowerPlant_Johto_Forest

PowerPlant_Johto_PowerPlantBookshelf_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantBookshelf

PowerPlant_Johto_PowerPlantGuardPhoneScript_Entry::
	lockall
	goto PowerPlant_Johto_PowerPlantGuardPhoneScript


PowerPlant_Johto_PowerPlantGuardPhoneScript:
	playse SE_PIN
	applymovement 1, Johto_Movement_Emote_exclamation_mark
	waitmovement 1
	waitse
	delay 30
	applymovement 1, PowerPlant_Johto_PowerPlantOfficer1ApproachGymGuide2Movement
	waitmovement 1
	applymovement 2, Johto_Movement_Face_Down
	waitmovement 2
	applymovement 3, Johto_Movement_Face_Down
	waitmovement 3
	message PowerPlant_Johto_PowerPlantOfficer1CeruleanShadyCharacterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, Johto_Movement_Face_Left
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Right
	waitmovement OBJ_EVENT_ID_PLAYER
	message PowerPlant_Johto_PowerPlantOfficer1CouldIAskForYourCooperationText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Johto_Movement_Face_Down
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, PowerPlant_Johto_PowerPlantOfficer1ReturnToPostMovement
	waitmovement 1
	setvar VAR_JOHTO_SCENE_POWER_PLANT, 0
	releaseall
	end

PowerPlant_Johto_PowerPlantOfficerScript:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantOfficerScript_ReturnedMachinePart
	goto_if_set FLAG_JOHTO_MET_MANAGER_AT_POWER_PLANT, PowerPlant_Johto_PowerPlantOfficerScript_MetManager
	message PowerPlant_Johto_PowerPlantOfficer1AThiefBrokeInText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantOfficerScript_MetManager:
	message PowerPlant_Johto_PowerPlantOfficer1CouldIAskForYourCooperationText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantOfficerScript_ReturnedMachinePart:
	message PowerPlant_Johto_PowerPlantOfficer1HaveToBeefUpSecurityText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide1Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantGymGuide1Script_ReturnedMachinePart
	message PowerPlant_Johto_PowerPlantGymGuide1SomeoneStoleAPartText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide1Script_ReturnedMachinePart:
	message PowerPlant_Johto_PowerPlantGymGuide1GeneratorUpAndRunningText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantGymGuide2Script_ReturnedMachinePart
	message PowerPlant_Johto_PowerPlantGymGuide2PowerPlantUpAndRunningText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide2Script_ReturnedMachinePart:
	message PowerPlant_Johto_PowerPlantGymGuide2GeneratorIsRunningAgainText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantOfficer2Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantOfficer2Script_ReturnedMachinePart
	message PowerPlant_Johto_PowerPlantOfficer2ManagerHasBeenSadAndFuriousText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantOfficer2Script_ReturnedMachinePart:
	message PowerPlant_Johto_PowerPlantOfficer2ManagerHasBeenCheerfulText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide4Script:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantGymGuide4Script_ReturnedMachinePart
	message PowerPlant_Johto_PowerPlantGymGuide4MagnetTrainConsumesElectricityText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantGymGuide4Script_ReturnedMachinePart:
	message PowerPlant_Johto_PowerPlantGymGuide4WeCanGetMagnetTrainRunningText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantManager:
	faceplayer
	goto_if_set FLAG_JOHTO_RETURNED_MACHINE_PART, PowerPlant_Johto_PowerPlantManager_ReturnedMachinePart
	checkitem ITEM_DEVON_PARTS, 1
	goto_if_ne VAR_RESULT, 0, PowerPlant_Johto_PowerPlantManager_FoundMachinePart
	goto_if_set FLAG_JOHTO_MET_MANAGER_AT_POWER_PLANT, PowerPlant_Johto_PowerPlantManager_MetManager
	message PowerPlant_Johto_PowerPlantManagerWhoWouldRuinMyGeneratorText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_MET_MANAGER_AT_POWER_PLANT
	clearflag FLAG_JOHTO_CERULEAN_GYM_ROCKET
	clearflag FLAG_JOHTO_FOUND_MACHINE_PART_IN_CERULEAN_GYM
	setvar VAR_JOHTO_SCENE_CERULEAN_GYM, 1
	setvar VAR_JOHTO_SCENE_POWER_PLANT, 1
	releaseall
	end

PowerPlant_Johto_PowerPlantManager_MetManager:
	message PowerPlant_Johto_PowerPlantManagerIWontForgiveCulpritText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantManager_FoundMachinePart:
	message PowerPlant_Johto_PowerPlantManagerThatsThePartText
	waitmessage
	waitbuttonpress
	removeitem ITEM_DEVON_PARTS
	setflag FLAG_JOHTO_RETURNED_MACHINE_PART
	clearflag FLAG_JOHTO_SAFFRON_TRAIN_STATION_POPULATION
	setflag FLAG_JOHTO_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH
	setflag FLAG_JOHTO_ROUTE_24_ROCKET
	setflag FLAG_JOHTO_RESTORED_POWER_TO_KANTO
	clearflag FLAG_JOHTO_GOLDENROD_TRAIN_STATION_GENTLEMAN

PowerPlant_Johto_PowerPlantManager_ReturnedMachinePart:
	goto_if_set FLAG_JOHTO_GOT_TM07_ZAP_CANNON, PowerPlant_Johto_PowerPlantManager_GotZapCannon
	message PowerPlant_Johto_PowerPlantManagerTakeThisTMText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, 0, PowerPlant_Johto_PowerPlantManager_NoRoom
	setflag FLAG_JOHTO_GOT_TM07_ZAP_CANNON
	message PowerPlant_Johto_PowerPlantManagerTM07IsZapCannonText
	waitmessage
	waitbuttonpress

PowerPlant_Johto_PowerPlantManager_NoRoom:
	closemessage
	releaseall
	end

PowerPlant_Johto_PowerPlantManager_GotZapCannon:
	message PowerPlant_Johto_PowerPlantManagerMyBelovedGeneratorText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

PowerPlant_Johto_Forest:
	faceplayer
	goto Johto_Std_Trade_FOREST

PowerPlant_Johto_PowerPlantBookshelf:
	goto Johto_Std_DifficultBookshelfScript

PowerPlant_Johto_PowerPlantOfficer1ApproachGymGuide2Movement:
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

PowerPlant_Johto_PowerPlantOfficer1ReturnToPostMovement:
	walk_down
	walk_down
	walk_left
	walk_left
	face_down
	step_end

PowerPlant_Johto_PowerPlantOfficer1AThiefBrokeInText:
	.string "A thief broke into\n"
	.string "the POWER PLANT…"
	.string "\pWhat is the world\n"
	.string "coming to?$"

PowerPlant_Johto_PowerPlantOfficer1CeruleanShadyCharacterText:
	.string "I just got word\n"
	.string "from CERULEAN."
	.string "\pIt appears that a\n"
	.string "shady character"
	.string "\phas been loitering\n"
	.string "around.$"

PowerPlant_Johto_PowerPlantOfficer1CouldIAskForYourCooperationText:
	.string "Could I ask for\n"
	.string "your cooperation?$"

PowerPlant_Johto_PowerPlantOfficer1HaveToBeefUpSecurityText:
	.string "We'll have to beef\n"
	.string "up our security\l"
	.string "presence.$"

PowerPlant_Johto_PowerPlantGymGuide1SomeoneStoleAPartText:
	.string "Someone made off\n"
	.string "with a part that's"
	.string "\pessential for the\n"
	.string "generator."
	.string "\pWithout it, the\n"
	.string "new generator's\l"
	.string "useless!$"

PowerPlant_Johto_PowerPlantGymGuide1GeneratorUpAndRunningText:
	.string "The generator's up\n"
	.string "and running. It's"
	.string "\pmaking electricity\n"
	.string "to spare.$"

PowerPlant_Johto_PowerPlantGymGuide2PowerPlantUpAndRunningText:
	.string "This POWER PLANT\n"
	.string "had been abandoned\l"
	.string "in the past."
	.string "\pWe got it back up\n"
	.string "and running to"
	.string "\pprovide power to\n"
	.string "the MAGNET TRAIN.$"

PowerPlant_Johto_PowerPlantGymGuide2GeneratorIsRunningAgainText:
	.string "The generator's\n"
	.string "running again!$"

PowerPlant_Johto_PowerPlantOfficer2ManagerHasBeenSadAndFuriousText:
	.string "The POWER PLANT's\n"
	.string "MANAGER is up\l"
	.string "ahead."
	.string "\pBut since someone\n"
	.string "wrecked the gener-\l"
	.string "ator, he's been\l"
	.string "both sad and\l"
	.string "furious…$"

PowerPlant_Johto_PowerPlantOfficer2ManagerHasBeenCheerfulText:
	.string "Since the gener-\n"
	.string "ator's been fixed,"
	.string "\pthe MANAGER has\n"
	.string "been cheerful.$"

PowerPlant_Johto_PowerPlantGymGuide4MagnetTrainConsumesElectricityText:
	.string "The MAGNET TRAIN\n"
	.string "consumes a lot of\l"
	.string "electricity."
	.string "\pIt can't move if\n"
	.string "the new generator\l"
	.string "isn't operating.$"

PowerPlant_Johto_PowerPlantGymGuide4WeCanGetMagnetTrainRunningText:
	.string "All right! We can\n"
	.string "finally get the"
	.string "\pMAGNET TRAIN\n"
	.string "running again.$"

PowerPlant_Johto_PowerPlantManagerWhoWouldRuinMyGeneratorText:
	.string "MANAGER: I, I, I'm\n"
	.string "ready to blast\l"
	.string "someone!"
	.string "\pWho would dare\n"
	.string "ruin my generator?"
	.string "\pI spent so much\n"
	.string "time on it!"
	.string "\pIf I catch him,\n"
	.string "he's going to get"
	.string "\pa taste of my ZAP\n"
	.string "CANNON!$"

PowerPlant_Johto_PowerPlantManagerIWontForgiveCulpritText:
	.string "MANAGER: I won't\n"
	.string "forgive him!"
	.string "\pThe culprit can\n"
	.string "cry and apologize,"
	.string "\pbut I'll still\n"
	.string "hammer him!"
	.string "\pGahahahah!$"

PowerPlant_Johto_PowerPlantManagerThatsThePartText:
	.string "MANAGER: Ah! Yeah!"
	.string "\pThat's the missing\n"
	.string "PART from my be-\l"
	.string "loved generator!\l"
	.string "You found it?$"

PowerPlant_Johto_PowerPlantManagerTakeThisTMText:
	.string "Wahah! Thanks!"
	.string "\pHere! Take this TM\n"
	.string "as a reward!$"

PowerPlant_Johto_PowerPlantManagerTM07IsZapCannonText:
	.string "MANAGER: TM07 is\n"
	.string "my ZAP CANNON."
	.string "\pIt's a powerful\n"
	.string "technique!"
	.string "\pIt's not what any-\n"
	.string "one would consider"
	.string "\paccurate, but it\n"
	.string "packs a wallop!$"

PowerPlant_Johto_PowerPlantManagerMyBelovedGeneratorText:
	.string "MANAGER: My be-\n"
	.string "loved generator!"
	.string "\pKeep pumping the\n"
	.string "electricity out!$"
