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
	@ TODO unsupported: checkitem MACHINE_PART
	goto Johto_EventScript_Unimplemented

PowerPlant_Johto_PowerPlantManager_ReturnedMachinePart:
	goto_if_set FLAG_JOHTO_GOT_TM07_ZAP_CANNON, PowerPlant_Johto_PowerPlantManager_GotZapCannon
	message PowerPlant_Johto_PowerPlantManagerTakeThisTMText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NUGGET
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
