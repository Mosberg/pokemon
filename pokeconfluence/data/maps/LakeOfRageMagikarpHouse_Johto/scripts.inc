LakeOfRageMagikarpHouse_Johto_MapScripts::
	.byte 0

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_Entry::
	lockall
	goto LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript

LakeOfRageMagikarpHouse_Johto_MagikarpHouseBookshelf_Entry::
	lockall
	goto LakeOfRageMagikarpHouse_Johto_MagikarpHouseBookshelf


LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript:
	faceplayer
	goto_if_set FLAG_JOHTO_LAKE_OF_RAGE_ELIXIR_ON_STANDBY, LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_GetReward
	goto_if_set FLAG_JOHTO_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP, LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_AskedForMagikarp
	goto_if_set FLAG_JOHTO_CLEARED_ROCKET_HIDEOUT, LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_ClearedRocketHideout
	goto_if_set FLAG_JOHTO_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP, LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_ExplainedHistory
	message LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_LakeOfRageHistory
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP
	releaseall
	end

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_ExplainedHistory:
	message LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_MenInBlack
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_ClearedRocketHideout:
	message LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_WorldsLargestMagikarp
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP
	releaseall
	end

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_AskedForMagikarp:
	setvar VAR_0x8004, SPECIES_MAGIKARP
	@ TODO unsupported: special FindPartyMonThatSpecies
	goto Johto_EventScript_Unimplemented

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_GetReward:
	message LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_Memento
	waitmessage
	waitbuttonpress
	giveitem ITEM_ELIXER
	goto_if_eq VAR_RESULT, 0, LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_NoRoom
	message LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_Bonus
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_JOHTO_LAKE_OF_RAGE_ELIXIR_ON_STANDBY
	releaseall
	end

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterScript_NoRoom:
	closemessage
	setflag FLAG_JOHTO_LAKE_OF_RAGE_ELIXIR_ON_STANDBY
	releaseall
	end

LakeOfRageMagikarpHouse_Johto_MagikarpHouseBookshelf:
	goto Johto_Std_DifficultBookshelfScript

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_LakeOfRageHistory:
	.string "LAKE OF RAGE is\n"
	.string "actually a crater"
	.string "\pmade by rampaging\n"
	.string "GYARADOS."
	.string "\pThe crater filled\n"
	.string "up with rainwater"
	.string "\pand the LAKE was\n"
	.string "formed."
	.string "\pThat's the story\n"
	.string "passed on from my"
	.string "\pGrandpa's great-\n"
	.string "great-grandpa."
	.string "\pIt used to be that\n"
	.string "you could catch"
	.string "\plively MAGIKARP\n"
	.string "there, but…"
	.string "\pI don't understand\n"
	.string "what's happening.$"

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_MenInBlack:
	.string "The LAKE hasn't\n"
	.string "been normal since"
	.string "\pthose men wearing\n"
	.string "black arrived.$"

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_WorldsLargestMagikarp:
	.string "LAKE OF RAGE is\n"
	.string "back to normal."
	.string "\pThe MAGIKARP have\n"
	.string "returned."
	.string "\pI may yet realize\n"
	.string "my dream of see-\l"
	.string "ing the world's\l"
	.string "largest MAGIKARP."
	.string "\pDo you have a ROD?\n"
	.string "Please help me if\l"
	.string "you do.$"

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_Memento:
	.string "Wow! This one is\n"
	.string "outstanding!"
	.string "\pI tip my hat to\n"
	.string "you!"
	.string "\pTake this as a\n"
	.string "memento!$"

LakeOfRageMagikarpHouse_Johto_MagikarpLengthRaterText_Bonus:
	.string "The record is the\n"
	.string "important thing."
	.string "\pThink of that as\n"
	.string "a bonus!$"
