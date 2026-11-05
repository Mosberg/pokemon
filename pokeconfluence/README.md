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
  Begin in your choice of Kanto, Johto, or Hoenn. Once you secure your second badge, board the Meridian line and tackle the remaining gyms in any order. The level cap follows the number of badges you hold, in whatever region.

- **The Resonance Encounters:**
  Calm and capture the Birds, Beasts, and Titans before the land fractures: until you do, each region suffers its own storm, fog or downpour. The Meridian conductors keep a count.

- **Unified 24-Badge Circuit:**
  Collect badges across all three regions to qualify for the **Apex Summit**—a four-round tournament atop Mt. Silver against the three Regional Wardens and the Summit Champion.

- **Modern Battle Engine & Quality of Life:**
  Full Gen 9 mechanics from pokeemerald-expansion (Physical/Special split, Fairy-type, modern movepools, updated abilities), soft level caps to prevent overleveling, reusable TMs, and a Field Kit that lets your team use the HM field moves.

- **Interconnected Lore & Villainous Alliance:**
  Witness the power struggle as the remnants of Team Rocket, Team Magma, and Team Aqua collide in an escalating turf war over who controls the cross-continental hub. Beat the enforcers at the three terminals, then the Chairman, to end the Convergence Crisis.

---

## Status

Confluence is built from the `pokemultiregion` hack (Hoenn from pokeemerald-expansion, Kanto from FireRed/Yellow, Johto from Crystal, all in one ROM) plus a Confluence layer. What works today and what is still open is in [docs/CONFLUENCE.md](docs/CONFLUENCE.md); the unconverted Johto/Kanto content is in [MISSING.md](MISSING.md).

## Build

```sh
scripts/setup.sh --extras   # toolchain check, native tools, .venv, Node.js + Go in ~/.local
scripts/build.sh            # pokeconfluence.gba (plain `make -j$(nproc) confluence` works too)
scripts/test.sh             # Confluence tests in the headless mGBA runner
scripts/play.sh 8888        # embedded emulator bridge for the mgba-agent scripts
```

System packages (Ubuntu/Debian): `build-essential binutils-arm-none-eabi gcc-arm-none-eabi libpng-dev git python3 perl`.

## Credits

Based on [pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) by RHH and the [pret](https://github.com/pret) pokeemerald, pokefirered, pokecrystal and pokeyellow decompilations. See [CREDITS.md](CREDITS.md) and [UPSTREAM_README.md](UPSTREAM_README.md).
