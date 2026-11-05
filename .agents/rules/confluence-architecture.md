---
description: Architectural systems of Pokémon Confluence multi-region design
globs: pokeconfluence/**
---

# Pokémon Confluence Architectural Rules

Pokémon Confluence is built on top of `pokeemerald-expansion` and `pokemultiregion` with a specialized Confluence layer.

## 1. Multi-Region Tracking
- Three regions are unified into a single ROM:
  - Hoenn (Emerald)
  - Kanto (FireRed)
  - Johto (Crystal)
- System query: `GetCurrentRegion()` in [src/confluence.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/confluence.c) returns `REGION_HOENN`, `REGION_KANTO`, or `REGION_JOHTO`.
- `Confluence_CountBadges()` aggregates all 24 gym badges.

## 2. Dynamic Level Scaling & Level Caps
- `B_EXP_CAP_TYPE = EXP_CAP_SOFT`
- `B_LEVEL_CAP_TYPE = LEVEL_CAP_BADGE_COUNT`
- Cap table progression:
  - 0 Badges: 15
  - 8 Badges: 48
  - 24 Badges: 80
  - Apex Champion: 100
- Scaling formula: Leaders, Elite Four, and Champions boost each party member so that the highest level matches the current level cap via `Confluence_GetTrainerLevelBoost()`.

## 3. Transit & Regional Gating
- Meridian Transit connects Slateport Harbor, Vermilion City, and Olivine City via `MeridianStation_Johto`.
- Unlocks when player holds `>= 2` badges.
- Platform 1: Vermilion City (Kanto)
- Platform 2: Olivine City (Johto)
- Platform 3: Slateport City (Hoenn)
- Platform 4: Closed / Crisis route

## 4. Resonance Legends & Weather Anomalies
- The 9 regional legends (Articuno, Zapdos, Moltres, Raikou, Entei, Suicune, Regirock, Regice, Registeel) are tracked by `Confluence_CountResonanceCalmed()`.
- Anomaly weather triggers after Badge 2:
  - Kanto outdoor maps -> Thunderstorms
  - Johto outdoor maps -> Fog
  - Hoenn outdoor maps -> Downpours
- Anomalies clear when that region's 3 legends are caught or the Convergence Crisis Chairman is defeated (`FLAG_CONFLUENCE_CRISIS_RESOLVED`).

## 5. Field Kit System
- `ITEM_FIELD_KIT` eliminates HM slave dependence.
- Automatically handles overworld field moves (Cut, Strength, Rock Smash, Rock Climb) via facing interaction prompts.
- Provides a dedicated `FIELD KIT` submenu in the party menu for Surf, Fly, Flash, Dig, Teleport, Dive, Waterfall without requiring the Pokémon to know the move.
- Still enforces gym badge prerequisites before executing field moves.

