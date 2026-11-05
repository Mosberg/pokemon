# Battle Engine & AI Scripting Architecture

## 1. Modern Battle Mechanics in Pokeemerald-Expansion
The battle engine in `pokeconfluence/` incorporates modern Gen 9 mechanics and battle gimmicks:
- **Battle Gimmicks**: Mega Evolution, Primal Reversion, Ultra Burst, Z-Moves, Dynamax, Gigantamax, and Terastallization.
- **Custom Battle Types**: Double Wild Battles, Inverse Battles, 1v2 / 2v1 battles, and Sky Battles.
- **Modern Mechanics**: Critical capture, Frostbite, move effectiveness hints in battle, simultaneous HP reduction, modern EXP curves, and soft level caps.

## 2. Showdown Team Parser Integration
Trainers in `src/data/trainers.party` support Pokémon Showdown team format directly:
```
=== TRAINER_ROXANNE_1 ===
Name: Roxanne
Class: Leader
Pic: Roxanne
Gender: Female
Music: Female
DoubleBattle: No

Geodude (F) @ Oran Berry
Ability: Rock Head
Level: 14
IVs: 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
Bold Nature
- Rock Throw
- Rock Tomb
- Defense Curl
- Tackle

Nosepass (F) @ Sitrus Berry
Ability: Sturdy
Level: 15
IVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
Modest Nature
- Rock Tomb
- Harden
- Tackle
```

## 3. Advanced AI Flags & Decision Scoring
Located in `include/constants/battle_ai.h`:
- `AI_FLAG_CHECK_BAD_MOVE`: Avoids ineffective moves (e.g., Electric vs Ground, status on immune targets).
- `AI_FLAG_TRY_TO_FAINT`: Prioritizes lethal damage calculations.
- `AI_FLAG_CHECK_VIABILITY`: Calculates multi-turn advantages, setup moves, and status infliction.
- `AI_FLAG_SMART_SWITCHING`: Evaluates type matchups and switches to favorable counters.
- `AI_FLAG_ACE_POKEMON`: Reserves the trainer's signature ace Pokémon for last.
- `AI_FLAG_DOUBLE_BATTLE`: Evaluates partner synergy, spread moves, and self-target protection.

## 4. Dynamic AI Functions
Dynamic AI evaluation functions calculate situational scores for moves:
- `ScoreMoveByDamage`: Computes exact damage brackets against the player's active battler.
- `ScoreSetupMoves`: Evaluates whether stat boosts are safe given the opponent's speed and remaining HP.
- `ScoreHazardDeployment`: Evaluates entry hazards (Stealth Rock, Spikes) relative to remaining player party size.

