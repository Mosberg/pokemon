#include "global.h"
#include "main.h"
#include "data.h"
#include "move.h"
#include "random.h"
#include "string_util.h"
#include "trainer_util.h"
#include "confluence.h"
#include "event_data.h"
#include "text.h"

#include "constants/battle_ai.h"
#include "constants/pokeball.h"

rng_value_t GeneratePartySeed(const struct Trainer *trainer)
{
    u32 seed = Crc32B((const u8 *)trainer, sizeof(struct Trainer)) ^ READ_OTID_FROM_SAVE;
    return LocalRandomSeed(seed);
}

static void CustomTrainerPartyAssignMoves(struct Pokemon *mon, const struct TrainerMon *partyEntry)
{
    bool32 noMoveSet = TRUE;
    u32 j;

    for (j = 0; j < MAX_MON_MOVES; ++j)
    {
        if (partyEntry->moves[j] != MOVE_NONE)
            noMoveSet = FALSE;
    }
    if (noMoveSet)
    {
        GiveMonInitialMoveset(mon);
        // TODO: Figure out a default strategy when moves are not set, to generate a good moveset
        return;
    }

    for (j = 0; j < MAX_MON_MOVES; ++j)
    {
        u32 pp = GetMovePP(partyEntry->moves[j]);
        SetMonData(mon, MON_DATA_MOVE1 + j, &partyEntry->moves[j]);
        SetMonData(mon, MON_DATA_PP1 + j, &pp);
    }
}

u32 GeneratePersonalityForGender(u32 gender, u32 species, u32 genderRng)
{
    const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[species];
    if (gender == MON_MALE)
    {
        assertf(speciesInfo->genderRatio < MON_FEMALE, "species %d cannot be male", species);
        return speciesInfo->genderRatio + (genderRng % (256 - speciesInfo->genderRatio));
    }
    if (gender == MON_FEMALE)
    {
        assertf(speciesInfo->genderRatio != MON_MALE && speciesInfo->genderRatio != MON_GENDERLESS, "species %d cannot be female", species);
        return genderRng % speciesInfo->genderRatio;
    }
    if (gender == MON_GENDERLESS)
        assertf(speciesInfo->genderRatio == MON_GENDERLESS, "species %d cannot be genderless", species);
    else
        errorf("GeneratePersonalityForGender called with invalid gender value %d", gender);
    return 0;
}

const u8 sModuloLUT[25] = {0, 21, 17, 13, 9, 5, 1, 22, 18, 14, 10, 6, 2, 23, 19, 15, 11, 7, 3, 24, 20, 16, 12, 8, 4};

void ModifyPersonalityForNature(u32 *personality, s32 newNature)
{
    s32 nature = GetNatureFromPersonality(*personality);
    s32 diff = abs(newNature - nature);
    s32 sign = (newNature > nature) ? 1 : -1;
    if (diff > NUM_NATURES / 2)
    {
        diff = NUM_NATURES - diff;
        sign *= -1;
    }
    *personality += (sModuloLUT[diff] * 0x100 * sign);
}

bool32 SetCorrectAbilityNum(struct Pokemon *mon, enum Species species, enum Ability ability)
{
    const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[species];
    u32 abilityNum;
    u32 maxAbilityNum = ARRAY_COUNT(speciesInfo->abilities);
    for (abilityNum = 0; abilityNum < maxAbilityNum; ++abilityNum)
    {
        if (speciesInfo->abilities[abilityNum] == ability)
            break;
    }
    assertf(abilityNum < maxAbilityNum, "illegal ability %S for %S", gAbilitiesInfo[ability].name, speciesInfo->speciesName)
    {
        return FALSE;
    }
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    return TRUE;
}

void MakeTrainerGenerator(struct TrainerGenerator *trainerGen, const struct Trainer *trainer)
{
    trainerGen->gender = trainer->gender;
    if (trainer->aiFlags & AI_FLAG_SMART_TERA)
        trainerGen->smartTera = TRUE;
    trainerGen->isFrontier = FALSE;
    StringCopyN(trainerGen->name, trainer->trainerName, TRAINER_NAME_LENGTH + 1);
    trainerGen->trainerClass = trainer->trainerClass;
    trainerGen->otID = OTID_STRUCT_RANDOM_NO_SHINY;
    trainerGen->localRngState = GeneratePartySeed(trainer);
    trainerGen->levelBoost = Confluence_GetTrainerLevelBoost(trainer);
}

void MakePartnerGenerator(struct TrainerGenerator *trainerGen, const struct Trainer *partner)
{
    u32 otID;
    trainerGen->gender = partner->gender;
    if (partner->aiFlags & AI_FLAG_SMART_TERA)
        trainerGen->smartTera = TRUE;
    trainerGen->isFrontier = FALSE;
    StringCopyN(trainerGen->name, partner->trainerName, TRAINER_NAME_LENGTH + 1);
    trainerGen->trainerClass = partner->trainerClass;
    otID = Crc32B((const u8 *)partner, sizeof(struct Trainer));
    trainerGen->otID = OTID_STRUCT_PRESET(otID);
    trainerGen->localRngState = LocalRandomSeed(otID);
    trainerGen->levelBoost = 0;
}

// POKE-CONFLUENCE: Authentic Crystal trainer class DVs mapped to 31-point IVs
static u32 GetTrainerClassDVs(u8 trainerClass)
{
    switch (trainerClass)
    {
    case TRAINER_CLASS_YOUNGSTER:
    case TRAINER_CLASS_YOUNGSTER_FRLG:
    case TRAINER_CLASS_BUG_CATCHER:
    case TRAINER_CLASS_BUG_CATCHER_FRLG:
    case TRAINER_CLASS_SAILOR:
    case TRAINER_CLASS_SAILOR_FRLG:
    case TRAINER_CLASS_CAMPER:
    case TRAINER_CLASS_CAMPER_FRLG:
    case TRAINER_CLASS_POKEMANIAC:
    case TRAINER_CLASS_POKEMANIAC_FRLG:
    case TRAINER_CLASS_SUPER_NERD_FRLG:
    case TRAINER_CLASS_FISHERMAN:
    case TRAINER_CLASS_FISHERMAN_FRLG:
    case TRAINER_CLASS_SWIMMER_M:
    case TRAINER_CLASS_SWIMMER_M_FRLG:
    case TRAINER_CLASS_BIKER_FRLG:
    case TRAINER_CLASS_BURGLAR_FRLG:
    case TRAINER_CLASS_JUGGLER_FRLG:
    case TRAINER_CLASS_BIRD_KEEPER:
    case TRAINER_CLASS_BIRD_KEEPER_FRLG:
    case TRAINER_CLASS_BLACK_BELT:
    case TRAINER_CLASS_BLACK_BELT_FRLG:
    case TRAINER_CLASS_SCIENTIST_FRLG:
    case TRAINER_CLASS_GENTLEMAN:
    case TRAINER_CLASS_GENTLEMAN_FRLG:
    case TRAINER_CLASS_POKEFAN:
    case TRAINER_CLASS_GUITARIST:
    case TRAINER_CLASS_PSYCHIC:
    case TRAINER_CLASS_PSYCHIC_FRLG:
    case TRAINER_CLASS_SCHOOL_KID:
        return 0x2318C671U; // DVs: Atk=9, Def=8, Spd=8, Spc=8
    case TRAINER_CLASS_LASS:
    case TRAINER_CLASS_LASS_FRLG:
        return 0x2318C551U; // DVs: Atk=5, Def=8, Spd=8, Spc=8
    case TRAINER_CLASS_SWIMMER_F:
    case TRAINER_CLASS_SWIMMER_F_FRLG:
        return 0x2318C5D1U; // DVs: Atk=7, Def=8, Spd=8, Spc=8
    case TRAINER_CLASS_HIKER:
    case TRAINER_CLASS_HIKER_FRLG:
        return 0x2318C6A0U; // DVs: Atk=10, Def=8, Spd=8, Spc=8
    case TRAINER_CLASS_PICNICKER:
    case TRAINER_CLASS_PICNICKER_FRLG:
        return 0x231AD580U; // DVs: Atk=6, Def=10, Spd=10, Spc=8
    case TRAINER_CLASS_BEAUTY:
    case TRAINER_CLASS_BEAUTY_FRLG:
        return 0x231CCD88U; // DVs: Atk=6, Def=9, Spd=12, Spc=8
    case TRAINER_CLASS_TWINS:
    case TRAINER_CLASS_TWINS_FRLG:
        return 0x231AC580U; // DVs: Atk=6, Def=8, Spd=10, Spc=8
    case TRAINER_CLASS_COOLTRAINER:
    case TRAINER_CLASS_COOLTRAINER_2:
    case TRAINER_CLASS_COOLTRAINER_FRLG:
        return 0x231CC771U; // DVs: Atk=13, Def=8, Spd=12, Spc=8
    case TRAINER_CLASS_TEAM_ROCKET_FRLG:
        return 0x231AC771U; // DVs: Atk=13, Def=8, Spd=10, Spc=8
    case TRAINER_CLASS_LEADER:
    case TRAINER_CLASS_LEADER_FRLG:
        return 0x1CE75677U; // DVs: Atk=9, Def=10, Spd=7, Spc=7
    case TRAINER_CLASS_ELITE_FOUR:
    case TRAINER_CLASS_ELITE_FOUR_FRLG:
        return 0x37BDE777U; // DVs: Atk=13, Def=12, Spd=13, Spc=13
    case TRAINER_CLASS_CHAMPION:
        return 0x37BDE777U; // DVs: Atk=13, Def=12, Spd=13, Spc=13
    case TRAINER_CLASS_CHAMPION_FRLG:
    case TRAINER_CLASS_BOSS_FRLG:
        return 0x3BDDEFFDU; // DVs: Atk=15, Def=13, Spd=13, Spc=14
    case TRAINER_CLASS_RIVAL:
    case TRAINER_CLASS_RIVAL_EARLY_FRLG:
        return 0x37BDEF7FU; // DVs: Atk=13, Def=13, Spd=13, Spc=13
    case TRAINER_CLASS_RIVAL_LATE_FRLG:
        return 0x37BDEE7FU; // DVs: Atk=9, Def=13, Spd=13, Spc=13
    default:
        return 0x2318C671U; // Default DVs (9, 8, 8, 8)
    }
}

void GenerateMonFromTrainerMon(struct Pokemon *mon, const struct TrainerMon *trainerMon, struct TrainerGenerator *trainer)
{
    u32 data;
    u32 personality = (LocalRandom32(&trainer->localRngState) & 0xFFFFDF00) + 0x1000;
    u32 genderValue = LocalRandom32(&trainer->localRngState);
    if (trainerMon->gender == TRAINER_MON_RANDOM_GENDER)
        genderValue = genderValue & 0x000000FF;
    else if (trainerMon->gender == TRAINER_MON_MALE)
        genderValue = GeneratePersonalityForGender(MON_MALE, trainerMon->species, genderValue);
    else if (trainerMon->gender == TRAINER_MON_FEMALE)
        genderValue = GeneratePersonalityForGender(MON_FEMALE, trainerMon->species, genderValue);
    else
        errorf("Unkwown trainer mon gender value %d", trainerMon->gender);
    personality |= genderValue;
    ModifyPersonalityForNature(&personality, trainerMon->nature);
	{
		u8 level = FlagGet(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE) ? MAX_LEVEL : min(trainerMon->lvl + trainer->levelBoost, MAX_LEVEL);
		CreateMon(mon, trainerMon->species, level, personality, trainer->otID);
	}
	if (trainerMon->nickname != NULL)
		SetMonData(mon, MON_DATA_NICKNAME, trainerMon->nickname);
	if (trainerMon->ev) //ev in struct TrainerMon are stored in Showdown order not vanilla Emerald order
    {
        SetMonData(mon, MON_DATA_HP_EV, &trainerMon->ev[0]);
        SetMonData(mon, MON_DATA_ATK_EV, &trainerMon->ev[1]);
        SetMonData(mon, MON_DATA_DEF_EV, &trainerMon->ev[2]);
        SetMonData(mon, MON_DATA_SPATK_EV, &trainerMon->ev[3]);
        SetMonData(mon, MON_DATA_SPDEF_EV, &trainerMon->ev[4]);
        SetMonData(mon, MON_DATA_SPEED_EV, &trainerMon->ev[5]);
    }

    // POKE-CONFLUENCE: If trainerMon has no custom IVs set, apply authentic trainer class DVs
    if (trainerMon->iv == 0)
    {
        u32 classIVs = GetTrainerClassDVs(trainer->trainerClass);
        SetMonData(mon, MON_DATA_IVS, &classIVs);
    }
    else
    {
        SetMonData(mon, MON_DATA_IVS, &trainerMon->iv);
    }
    CustomTrainerPartyAssignMoves(mon, trainerMon);
    SetMonData(mon, MON_DATA_HELD_ITEM, &trainerMon->heldItem);

	// POKE-CONFLUENCE: Apex Summit Gauntlet auto-tuning (max IVs, competitive EVs, and held items)
	if (FlagGet(FLAG_CONFLUENCE_APEX_CHALLENGE_ACTIVE))
	{
		u32 maxIVs = 31 | (31 << 5) | (31 << 10) | (31 << 15) | (31 << 20) | (31 << 25);
		SetMonData(mon, MON_DATA_IVS, &maxIVs);

		if (trainerMon->ev == NULL)
		{
			u8 ev252 = 252;
			u8 ev4 = 4;
			if (gSpeciesInfo[trainerMon->species].baseAttack >= gSpeciesInfo[trainerMon->species].baseSpAttack)
				SetMonData(mon, MON_DATA_ATK_EV, &ev252);
			else
				SetMonData(mon, MON_DATA_SPATK_EV, &ev252);
			SetMonData(mon, MON_DATA_SPEED_EV, &ev252);
			SetMonData(mon, MON_DATA_HP_EV, &ev4);
		}
		if (trainerMon->heldItem == ITEM_NONE)
		{
			u16 item = ITEM_LEFTOVERS;
			if (gSpeciesInfo[trainerMon->species].baseSpeed >= 100)
				item = ITEM_LIFE_ORB;
			else if (gSpeciesInfo[trainerMon->species].baseDefense >= 100 || gSpeciesInfo[trainerMon->species].baseSpDefense >= 100)
				item = ITEM_LEFTOVERS;
			else
				item = ITEM_SITRUS_BERRY;
			SetMonData(mon, MON_DATA_HELD_ITEM, &item);
		}
	}

	bool32 abilitySet = FALSE;
	if (trainerMon->ability)
	{
        abilitySet = SetCorrectAbilityNum(mon, trainerMon->species, trainerMon->ability);
    }

    if (!abilitySet)
    {
        if (B_TRAINER_MON_RANDOM_ABILITY == 2)
        {
            do {
                data = Random() % NUM_ABILITY_SLOTS; // includes hidden abilities
            } while (GetAbilityBySpecies(trainerMon->species, data) == ABILITY_NONE);
            SetMonData(mon, MON_DATA_ABILITY_NUM, &data);
        }
        else if (B_TRAINER_MON_RANDOM_ABILITY == 0)
        {
            data = 0;
            SetMonData(mon, MON_DATA_ABILITY_NUM, &data);
        }
        // else B_TRAINER_MON_RANDOM_ABILITY == 1
        // this is the default from CreateMon (random non-hidden ability based on personality)
    }

    if (trainerMon->ball < POKEBALL_COUNT)
    {
        data = trainerMon->ball;
        SetMonData(mon, MON_DATA_POKEBALL, &data);
    }
    else if (B_TRAINER_CLASS_POKE_BALLS >= GEN_7 && trainer->trainerClass && trainerMon->ball == POKEBALL_COUNT)
    {
        data = gTrainerClasses[trainer->trainerClass].ball ?: BALL_POKE;
        SetMonData(mon, MON_DATA_POKEBALL, &data);
    }
    else if (trainerMon->ball > POKEBALL_COUNT)
    {
        errorf("Invalid ball for %S in %S's party", GetMonData(mon, MON_DATA_NICKNAME), trainer->name);
    }

    SetMonData(mon, MON_DATA_FRIENDSHIP, &trainerMon->friendship);

    data = trainerMon->isShiny;
    SetMonData(mon, MON_DATA_IS_SHINY, &data);
    if (trainerMon->shouldUseDynamax)
    {
        data = trainerMon->dynamaxLevel;
    }
    else
    {
        data = BLOCK_AI_DYNAMAX;
    }
    SetMonData(mon, MON_DATA_DYNAMAX_LEVEL, &data);
    if (trainerMon->gigantamaxFactor)
    {
        data = trainerMon->gigantamaxFactor;
        SetMonData(mon, MON_DATA_GIGANTAMAX_FACTOR, &data);
    }
    if (trainerMon->teraType)
    {
        data = trainerMon->teraType;
        SetMonData(mon, MON_DATA_TERA_TYPE, &data);
    }
    else if (!trainer->smartTera)
    {
        data = TYPE_MYSTERY;
        SetMonData(mon, MON_DATA_TERA_TYPE, &data);
    }

    CalculateMonStats(mon);
    SetMonData(mon, MON_DATA_OT_NAME, trainer->name);
    data = trainer->gender;
    SetMonData(mon, MON_DATA_OT_GENDER, &data);
}
