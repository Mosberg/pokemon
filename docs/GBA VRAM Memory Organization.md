### 1. GBA VRAM Memory Organization & Affine Backgrounds

The GBA features **96 KB of internal Video RAM (VRAM)** mapped from `0x06000000` to `0x06017FFF`. In tiled background modes (Modes 0, 1, and 2), this memory is divided into two logical structures: **Character Base Blocks (CBB)** for raw pixel patterns and **Screen Base Blocks (SBB)** for tile placement maps.

```
0x06000000 ┌─────────────────────────────────────────────────────────┐
           │ Char Block 0 (16 KB) - BG Tiles                         │
0x06004000 ├─────────────────────────────────────────────────────────┤
           │ Char Block 1 (16 KB) - BG Tiles                         │
0x06008000 ├─────────────────────────────────────────────────────────┤
           │ Char Block 2 (16 KB) - BG Tiles                         │
0x0600C000 ├─────────────────────────────────────────────────────────┤
           │ Char Block 3 (16 KB) - BG Tiles                         │
0x06010000 ├─────────────────────────────────────────────────────────┤
           │ Char Block 4 (16 KB) - OBJ (Sprite) Tiles (Lower 16 KB) │
0x06014000 ├─────────────────────────────────────────────────────────┤
           │ Char Block 5 (16 KB) - OBJ (Sprite) Tiles (Upper 16 KB) │
0x06018000 └─────────────────────────────────────────────────────────┘

```

#### Base Block Allocations

* **Character Base Blocks (CBB 0–3 for BG, 4–5 for Sprites):**
* Sized at **16 KB (16,384 bytes)** each.
* In **4bpp** mode (32 bytes per $8 \times 8$ tile), a single CBB holds up to **512 tiles**.
* In **8bpp** mode (64 bytes per $8 \times 8$ tile), a CBB holds up to **256 tiles**.
* Configured via bits 2–3 of the background control register `REG_BGxCNT`.


* **Screen Base Blocks (SBB 0–31):**
* Sized at **2 KB (2,048 bytes)** each.
* SBBs overlay the exact same physical VRAM as CBBs. Developers reserve higher blocks (typically SBB 24–31, starting at `0x0600C000` or `0x0600E000`) for tilemaps so they do not collide with active tile patterns in CBB 0–1.
* Configured via bits 8–12 of `REG_BGxCNT`.



#### Regular (Text) vs. Affine (Rot/Scale) Backgrounds

| Feature | Regular (Text) BG (Mode 0, 1) | Affine (Rot/Scale) BG (Mode 1, 2) |
| --- | --- | --- |
| **Color Depth** | 4bpp (16 palettes of 16 colors) or 8bpp | **8bpp strictly** (Single 256-color palette) |
| **Map Entry Size** | **2 bytes (16 bits)** per cell | **1 byte (8 bits)** per cell |
| **Flips via Map** | Horizontal and vertical flip bits included | **No flip bits** (Flips handled via matrix) |
| **Tile Range** | References tile indices $0\text{--}1023$ | References tile indices $0\text{--}255$ only |
| **Hardware Transforms** | Integral pixel scroll offsets ($X, Y$) | Affine matrix ($PA, PB, PC, PD$) + reference points |

#### Affine Background Mechanics & Matrix Math

In Mode 1 (BG2 is Affine) and Mode 2 (BG2 and BG3 are Affine), the PPU calculates screen scanlines by mapping screen coordinates $(x, y)$ back to background texture coordinates $(x', y')$ through an inverse affine transformation matrix:

$$\begin{bmatrix} x' \\ y' \end{bmatrix} = \begin{bmatrix} PA & PB \\ PC & PD \end{bmatrix} \begin{bmatrix} x - x_0 \\ y - y_0 \end{bmatrix} + \begin{bmatrix} x_{ref} \\ y_{ref} \end{bmatrix}$$

* **Matrix Registers (Fixed-Point 8.8):**
* `REG_BGxPA`: Horizontal scale factor / rotation cosine ($\Delta x' / \Delta x$).
* `REG_BGxPB`: Horizontal shear factor / rotation sine ($\Delta x' / \Delta y$).
* `REG_BGxPC`: Vertical shear factor / rotation sine ($\Delta y' / \Delta x$).
* `REG_BGxPD`: Vertical scale factor / rotation cosine ($\Delta y' / \Delta y$).


* **Reference Registers (Fixed-Point 19.8):**
* `REG_BGxX` and `REG_BGxY` provide internal 28-bit accumulators specifying the pivot coordinate at $(x_0, y_0)$.


* **Map Formats:** Each byte in an affine SBB is simply a direct 8-bit pointer to an $8 \times 8$ tile pattern within the selected CBB.
* **Pokémon Engine Use-Cases:** Affine backgrounds generate the 3D rotating Poké Ball in trade sequences, the soaring latios/latias intro cinematic, and the zooming/tilting battle arena backgrounds.

---

### 2. Tracing a Poryscript Event Execution in C Source

When an NPC script created in Poryscript executes, control transfers across input polling, spatial detection, task scheduling, and the virtual machine loop.

```
Player presses 'A' facing NPC
   │
   ▼
Task_ProcessPlayerInput() -> TryStartInteraction()
   │
   ▼
GetInteractedObjectScript() -> Extracts script pointer from ROM
   │
   ▼
ScriptContext_SetupScript() -> Loads script into sScriptContext1
   │
   ▼
ScriptContext_RunScript() (invoked every engine frame)
   │
   ▼
ScriptContext_Step() -> Fetch opcode byte -> Call table entry: gScriptCmdTable[opcode]()

```

#### Step 1: Input Detection & Spatial Queries

1. During normal overworld traversal, the engine loop calls `Task_ProcessPlayerInput()` in `src/overworld.c`.
2. When the player presses the `A_BUTTON`, `TryStartInteraction()` inspects coordinates one tile ahead of the player sprite based on the facing direction (`GetFacingTileCoords()`).
3. If an object event (NPC) exists at those coordinates, the engine queries the map's event data (`gSaveBlock1Ptr->objectEvents`) and retrieves the local template ID.

#### Step 2: Extracting the Script Pointer

1. `GetInteractedObjectScript()` inside `src/scrcmd.c` locates the object event template from the active map header:
```c
const u8 *script = GetObjectEventScriptPointerByObjectEventId(objectId);

```


2. The returned `script` is an absolute 32-bit ROM pointer (e.g., `0x0815F8C4`) pointing to the compiled bytecode generated from the original `.pory` file.

#### Step 3: Initializing ScriptContext

1. The engine transfers the pointer to the primary scripting interpreter by calling `ScriptContext_SetupScript(script)` in `src/script.c`.
2. This clears and configures the global script context structure:
```c
void ScriptContext_SetupScript(const u8 *ptr)
{
    InitScriptContext(&sScriptContext1, gScriptCmdTable, gScriptCmdTableEnd);
    SetupBytecodeScript(&sScriptContext1, ptr);
    LockPlayerFieldControls(); // Disables normal directional input
}

```


3. `sScriptContext1.stackDepth` is set to 0, and `sScriptContext1.scriptPtr` points to the start of the bytecode sequence.

#### Step 4: The Bytecode Dispatch Loop

On every subsequent frame, `ScriptContext_RunScript()` executes in `src/script.c`:

```c
bool8 ScriptContext_Step(struct ScriptContext *ctx)
{
    u8 opcode;
    ScriptCmdFunc func;

    if (!ctx->isRunning)
        return FALSE;

    opcode = *ctx->scriptPtr++;     // 1. Fetch opcode
    func = ctx->cmdTable[opcode];   // 2. Resolve handler via function pointer array
    return func(ctx);               // 3. Execute command handler
}

```

* **Handling `lock` (`ScrCmd_lock`):** Halts ambient NPC movement routines and locks player orientation.
* **Handling `msgbox` (`ScrCmd_msgbox`):**
* Reads the 32-bit string pointer argument using `ScriptReadWord(ctx)`.
* Passes the address to `ShowFieldMessage()` and queues `Task_DrawFieldMessage()`.
* Sets `ctx->isRunning = FALSE`, pausing VM advancement until the player presses `A` to exhaust dialog characters.


* **Handling `release` & `end` (`ScrCmd_release`, `ScrCmd_end`):**
* Restores player movement vectors.
* Resets `sScriptContext1.isRunning` to `FALSE` and clears active script memory, handing control back to standard input polling.



---

### 3. Creating a Custom Instrument Voicegroup for mid2agb

Adding a custom PCM instrument (e.g., an 8-bit sample) requires importing raw sound data, defining an m4a `WaveData` structure, binding it to a `Voicegroup`, and setting up tracking in MIDI.

#### Step 1: Prepare the Audio Waveform

1. Convert your audio file to a **monophonic signed 8-bit PCM WAV** at an m4a-friendly sample rate (e.g., `10512 Hz`, `13379 Hz`, or `18157 Hz` to fit within GBA timer dividers).
2. Place the resulting file in the sound assets folder:
```
sound/direct_sound_samples/custom_synth.wav

```


3. The build toolchain uses `gbagfx` or `wav2agb` rules in `audio_rules.mk` to convert `.wav` files into linkable raw binary `.bin` sample chunks containing an internal GBA PCM header.

#### Step 2: Declare the Sample in Assembly

Open `sound/direct_sound_samples.inc` and declare the sample's `WaveData` header:

```assembly
    .align 2
    .global sound_sample_custom_synth
sound_sample_custom_synth::
    .word 0                    @ Flags / Type (0 = PCM single-shot, 1 = PCM looped)
    .word 13379 * 1024         @ Fine pitch / playback frequency ratio (Freq * 1024)
    .word 0                    @ Loop start offset (in bytes)
    .word 4200                 @ Total sample length (in bytes)
    .incbin "sound/direct_sound_samples/custom_synth.bin"

```

#### Step 3: Construct the Voicegroup Entry

Voicegroups are 12-byte structural arrays mapping MIDI program numbers ($0\text{--}127$) to sound generators. Open or create an include file in `sound/voicegroups/` (e.g., `sound/voicegroups/voicegroup_custom.inc`):

```assembly
    .align 2
    .global voicegroup_custom
voicegroup_custom:
    @ Program 0: Standard Acoustic Piano replaced with Custom PCM Synth
    .byte 0                    @ Voice Type: 0 = DirectSound PCM (non-fixed pitch)
    .byte 60                   @ Base MIDI root key (60 = Middle C)
    .byte 0                    @ Reserved / Pan flags
    .byte 0                    @ Reserved
    .word sound_sample_custom_synth  @ Pointer to WaveData struct
    .byte 255                  @ Attack Rate (0-255, 255 = instant peak volume)
    .byte 0                    @ Decay Rate  (0-255)
    .byte 255                  @ Sustain Level (0-255, 255 = max hold)
    .byte 40                   @ Release Rate (0-255, decay speed after Note-Off)

    @ Program 1: Legacy Game Boy Square Wave 1 (DMG Channel 1)
    .byte 1                    @ Voice Type: 1 = PSG / DMG Square 1
    .byte 0                    @ Unused root key
    .byte 0                    @ Sweep parameters
    .byte 0                    @ Duty cycle setting (0 = 12.5%, 1 = 25%, 2 = 50%, 3 = 75%)
    .word 0                    @ No WaveData pointer required
    .byte 255                  @ Attack
    .byte 0                    @ Decay
    .byte 240                  @ Sustain
    .byte 10                   @ Release

    @ Fill remaining slots up to 127 with placeholders or existing instruments...

```

#### Step 4: MIDI Sequence Setup & `mid2agb` Compilation

1. In your digital audio workstation (DAW) or MIDI sequencer:
* Assign the desired channel to **Program Change 0** (to trigger `sound_sample_custom_synth`).
* Keep velocity values within range ($1\text{--}127$) and avoid note overlap on the same channel (m4a tracks are monophonic per sequence channel).


2. Export your arrangement as a standard MIDI file: `sound/songs/midi/mus_custom_track.mid`.
3. In `sound/songs.mk`, configure the compilation recipe invoking `mid2agb`:
```makefile
sound/songs/mus_custom_track.s: sound/songs/midi/mus_custom_track.mid
	mid2agb $< $@ -gvoicegroup_custom

```


* The `-gvoicegroup_custom` flag instructs `mid2agb` to resolve all note events and voice indices against your new table.


4. Link the generated song in `sound/song_table.inc`:
```assembly
song mus_custom_track, 0, 0

```


5. Trigger the song in C code or Poryscript via `playbgm(MUS_CUSTOM_TRACK, 0)` or `PlayBGM(MUS_CUSTOM_TRACK)`.
