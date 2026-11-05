# Pokémon Confluence Version

**Three continents. One fractured balance.**

For generations, the natural boundaries between Kanto, Johto, and Hoenn kept the world’s primal energies contained. That ended with the completion of the **Great Meridian Transit line**—a deep-sea tectonic transit network linking the three landmasses for the first time in history.

The construction disturbed ancient fault lines, triggering the **Convergence Crisis**:

- Kanto's skies churn violently as the Legendary Birds abandon their roosts.
- Johto's sacred towers resonate with strange seismic tremors, driving the Legendary Beasts wild.
- Deep beneath the sea, the slumber of Hoenn's Ancient Titans has destabilized.

As an ambitious trainer embarking on an unprecedented inter-regional League challenge, you quickly uncover that the corporate syndicate funding the transit route isn't just moving passengers—they are siphoning regional leyline energy to awaken something far worse.

---

## What Sets It Apart

- **Non-Linear Regional Navigation:**
  Begin in your choice of Kanto, Johto, or Hoenn. Once you secure your second badge, board the high-speed Meridian line and tackle the remaining gyms in any order with a dynamic scaling system.

- **The Resonance Encounters:**
  Track weather anomalies and localized catastrophes across all three regions to calm and capture the Birds, Beasts, and Titans before the land fractures.

- **Unified 24-Badge Circuit:**
  Collect badges across all three regions to qualify for the **Apex Summit**—a grueling endgame tournament held atop Mt. Silver against gym leaders, frontier brains, and regional champions.

- **Modern Battle Engine & Quality of Life:**
  Full Gen 9 mechanics (Physical/Special split, Fairy-type, modern movepools, updated abilities), built-in soft level caps to prevent overleveling, reusable TMs, and HM field moves assigned directly to key items.

- **Interconnected Lore & Villainous Alliance:**
  Witness the power struggle as the remnants of Team Rocket, Team Magma, and Team Aqua collide in an escalating turf war over who controls the cross-continental hub.

---

## Repository layout

- [`pokeconfluence/`](pokeconfluence/) – the game: source tree, build (`make -j$(nproc) confluence`), tests and helper scripts. Start with [`pokeconfluence/docs/CONFLUENCE.md`](pokeconfluence/docs/CONFLUENCE.md).
- `tools/` – the toolchain the base hack was made with (poke-migrator-pro, pokeemerald-ai-bridge, porymap, porytiles, poryscript, porypal, agbcc).
- `games/` – reference projects (pokemultiregion, pokeemerald-expansion, pokeemerald, pokefirered, pokecrystal, pokeyellow); not tracked.

Quick start: `cd pokeconfluence && scripts/setup.sh --extras && scripts/build.sh && scripts/test.sh`.
