---
description: GBA M4A sound engine and voicegroup rules
globs: pokeconfluence/sound/**
---

# Audio & Voicegroup Guidelines (M4A Sound Engine)

Pokémon Confluence uses the standard Game Boy Advance Music Player 2000 (M4A) sound engine.

## 1. Voicegroup Hierarchy
- Each sequence (`.s` file in `sound/songs/`) points to a voicegroup (`voicegroup***`).
- The primary soundbank is `gDefaultVoicegroup` (`voicegroup000`), which contains direct sound samples (drums, bass, leads) and programmable sound generator (PSG) square/noise waves.
- When adding new tracks from GBC Crystal or external MIDI arrangements:
  - Do not modify existing vanilla voicegroup indices directly.
  - Create a dedicated voicegroup or map instruments to standard GBA voicegroup entries.

## 2. GBC Chiptune Conversion
- GBC Crystal songs utilize 4 channels:
  - Channel 1: Pulse wave with sweep.
  - Channel 2: Pulse wave.
  - Channel 3: Custom 4-bit 32-sample wave.
  - Channel 4: White/periodic noise.
- When compiling with `mid2agb`:
  - Map PSG channels to GBA PSG hardware (DirectSound DMA channels A/B handle high quality samples, while PSG 1-4 emulate GB hardware directly).
  - Ensure tempo byte does not exceed M4A tick resolution.

## 3. Polyphony & DMA Limits
- GBA hardware can mix at most 8-12 DirectSound channels simultaneously before dropping audio samples or causing frame slowdown.
- Keep simultaneous active voices per track under 8, leaving headroom for battle/overworld sound effects (SE).

