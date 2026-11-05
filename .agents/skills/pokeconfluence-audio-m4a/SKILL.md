---
name: pokeconfluence-audio-m4a
description: Music, sound effects, voicegroups, and mid2agb chiptune conversion in Pokémon Confluence. Activates when adding or editing songs or sound effects.
---

# Pokémon Confluence Audio & M4A Sound Engine Skill

This skill guides converting music, assembling voicegroups, and integrating GBC/MIDI tracks into the GBA M4A Sound Engine.

## 1. Engine Architecture
- The M4A (Music Player 2000) sound driver resides in `pokeconfluence/sound/m4a.s`.
- Songs are defined in [pokeconfluence/sound/songs.bld](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/sound/songs.bld) and declared in [pokeconfluence/include/constants/songs.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/constants/songs.h).
- Sequences are stored as `.s` assembler files in `pokeconfluence/sound/songs/`.

## 2. Converting MIDI to GBA Assembly
To convert standard MIDI files to GBA format:
```bash
# Convert midi to .s assembly sequence
tools/mid2agb/mid2agb path/to/input.mid sound/songs/mus_custom_track.s -Gvoicegroup000
```
- `-G<voicegroup>`: Specifies the target voicegroup. Default is `gDefaultVoicegroup` (`voicegroup000`).

## 3. Integrating GBC Crystal Chiptunes
1. Extract MIDI from `pokecrystal` using `gb-asm-tools` or `crystal-sound` parser.
2. Ensure channels are mapped:
   - Tracks 1 & 2: Square waves (PSG 1 & 2).
   - Track 3: Custom programmable wave / Bass (PSG 3).
   - Track 4: Drum / Noise (PSG 4).
3. Compile with `mid2agb` using `voicegroup_crystal` or `voicegroup000`.
4. Register the new song in `sound/songs.bld`:
   ```
   mus_johto_route30 sound/songs/mus_johto_route30.s 2 2
   ```
5. Add `MUS_JOHTO_ROUTE30` enum to `include/constants/songs.h`.

## 4. Playback Diagnostics
- If a song plays but lacks instruments: The voicegroup table does not contain definitions for the program change numbers requested in the MIDI.
- If battle sound effects cut out: DirectSound polyphony exceeds the hardware mixing buffer (max 8 channels). Reduce simultaneous polyphonic voices in background music.

