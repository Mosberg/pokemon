# Pokeemerald-Expansion Tutorials & Systems Reference

This document indexes and synthesizes the 32 comprehensive markdown tutorials located in [pokeconfluence/docs/tutorials/](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/docs/tutorials/).

## 1. Day / Night System (DNS) (`dns.md`)
- Provides real-time clock based ambient color tinting to outdoor tilesets, OW sprites, and battle backgrounds.
- 4 primary periods: Morning (4:00-9:59), Day (10:00-16:59), Evening (17:00-19:59), Night (20:00-3:59).
- Controlled by `DNS_IN_BATTLE`, `DNS_IN_OVERWORLD` in `include/config/overworld.h`.

## 2. Follower NPCs (`how_to_follower_npc.md`)
- Lets an NPC or Pokémon follow the player in the overworld.
- Supports ledge jumping, bike animations, surfing, and multi-region transitions.
- Initiated in scripts using `special SetFollowerNPC` with sprite ID and dialogue pointer.

## 3. Dynamic Weather (`how_to_dynamic_weather.md`)
- Modifies weather based on region, time of day, or quest state.
- Used by Confluence Resonance anomalies in `src/field_weather_effect.c` to generate region-wide storms, fog, and downpours.

## 4. Apricorn Trees (`how_to_apricorn_tree.md`)
- Johto daily fruit/apricorn harvest mechanic.
- Daily reset driven by RTC step in `src/clock.c` (`JohtoDailyResetFruitTrees`).
- Interacting with an apricorn tree yields specific apricorn colors (Red, Yellow, Blue, Green, Pink, White, Black) usable for Kurt's custom Poké Balls.

## 5. Overworld Wild Encounters (`how_to_overworld_wild_encounters.md`)
- Spawns interactive overworld Pokémon sprites.
- Triggers wild battle upon interaction or proximity detection via `special StartOverworldWildBattle`.

## 6. Time of Day Wild Encounters (`how_to_time_of_day_encounters.md`)
- Integrates with `src/data/wild_encounters.json`.
- Supports separate encounter tables for morning, day, and night (e.g., Hoothoot and Spinarak at night; Ledyba and Pidgey in the morning).

## 7. Dynamic Trainer Battle Scripts (`how_to_dynamic_trainer_script.md`)
- Allows dynamic trainer pools, scaling trainer levels according to badge count, and randomized rosters.
- Supports sliding trainer dialogues before Mega Evolution or upon landing critical hits.

## 8. Dynamic Shop (`how_to_dynamic_shop.md`)
- Custom shops populated dynamically at runtime based on game progression and badges held.
- Built with `special OpenDynamicShop` and an array of item IDs.

## 9. Mass Outbreaks (`how_to_mass_outbreak.md`)
- Daily swarms of rare Pokémon on specific routes.
- Driven by RTC daily events, broadcast over Johto radio ("Pokémon Talk" with Professor Oak and Mary).

## 10. Code Entry System (`how_to_code_entry.md`)
- Allows entering alphanumeric mystery gift codes in Pokémon Centers to receive special event Pokémon, items, or vanity customization.

