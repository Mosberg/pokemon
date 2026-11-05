### 1. DirectSound Multi-Channel DMA Buffers in m4a

The GBA hardware has no dynamic hardware mixer for PCM samples. DirectSound channels A and B are simple 8-bit digital-to-analog converters fed by 32-bit hardware FIFOs (`REG_FIFO_A` at `0x040000A0`, `REG_FIFO_B` at `0x040000A4`). The **m4a (Music Player 2000)** sound driver handles multi-channel mixing entirely in software, typically allocating **8 to 16 virtual software channels** that sum into a double-buffered PCM output block.

```
Virtual Channel 0 (PCM Sample) ──┐
Virtual Channel 1 (PCM Sample) ──┼──> Software Mixer (m4aMain / SoundMainRAM)
Virtual Channel 2 (PCM Sample) ──┤       ├── Linear volume & pan scaling
Virtual Channel N (PCM Sample) ──┘       ├── Resampling interpolation
                                         └── Dynamic headroom clamping
                                                        │
                                                        ▼
                        Double-Buffered Ring Array (e.g., 2 × 576 bytes in IWRAM)
                                  ┌─────────────────────┬─────────────────────┐
                                  │   Buffer 0 (Play)   │  Buffer 1 (Filling) │
                                  └─────────────────────┴─────────────────────┘
                                             │
                                             ▼
                                DirectSound DMA (Timer 0/1 tick triggers FIFO pull)

```

#### Mixing Pipeline and Software Synthesis

1. **Per-Channel Stepping:** For every active virtual voice in the `SoundChannel` list, `m4a` tracks fractional position pointers (`current_ptr` and `fractional_phase`). On each audio frame, it reads the signed 8-bit sample data ($\text{sample} \in [-128, 127]$).
2. **Volume / Pan Modulation:** The sample byte is multiplied by the channel envelope (ADSR) and left/right stereo weights (linear panning).
3. **Buffer Accumulation:** Individual samples are accumulated into intermediate signed 16-bit or 32-bit integer buffers to prevent clipping while summing:

$$\text{MixBuffer}[i] = \sum_{c=0}^{\text{channels}-1} \text{Sample}_{c}[i] \times \text{VolLeft/Right}_{c}$$


4. **Master Volume & Clamping:** The accumulated sum is scaled by the master volume register and clamped back to signed 8-bit values ($[-128, 127]$) or unsigned 8-bit values ($[0, 255]$) depending on hardware initialization.

#### Hardware DMA Double-Buffering Setup

The sound driver uses **Timer 0** (or Timer 1) to pace the hardware FIFO and **DMA Channel 1 or 2** to feed the FIFO automatically:

```c
// Registers involved in DirectSound A setup:
// REG_SOUNDCNT_H (0x04000082) controls channel enabling, reset, and timer selection
REG_SOUNDCNT_H = SOUND_A_LEFT_OUTPUT
               | SOUND_A_RIGHT_OUTPUT
               | SOUND_A_TIMER_0       // Timer 0 overflow triggers FIFO reload
               | SOUND_A_FIFO_RESET;

// Configure Timer 0 to tick at the target sampling rate (e.g., 13379 Hz)
// System Clock = 16.78 MHz (16,777,216 Hz)
// Timer Reload Value = 65536 - (System Clock / Sample Rate)
// For 13379 Hz: 65536 - (16777216 / 13379) = 65536 - 1254 = 64282 (0xFB7A)
REG_TM0CNT_L = 64282;
REG_TM0CNT_H = TIMER_ENABLE | TIMER_DIV_1;

// DMA 1 / 2 configured to repeat transfers to FIFO on Timer overflow
REG_DMA1SAD = (u32)activeBuffer;             // Source address in IWRAM
REG_DMA1DAD = (u32)&REG_FIFO_A;              // Destination FIFO address
REG_DMA1CNT_H = DMA_DEST_FIXED               // FIFO address does not increment
              | DMA_REPEAT                   // Reload source address on end
              | DMA_32                       // Transfers 32-bit words (4 samples per word)
              | DMA_SPECIAL                  // Synced with Sound FIFO / Timer
              | DMA_ENABLE;

```

---

### 2. Affine Transformation Matrix Calculator in C

The GBA PPU expects affine transform parameters ($PA, PB, PC, PD$) in **fixed-point 8.8 format** (8 integer bits, 8 fractional bits: $1.0 = 256 = \text{0x0100}$).

The transformation maps screen display coordinates $(x, y)$ back to background texture space $(x', y')$:


$$\begin{bmatrix} x' \\ y' \end{bmatrix} = \begin{bmatrix} PA & PB \\ PC & PD \end{bmatrix} \begin{bmatrix} x - x_{\text{pivot}} \\ y - y_{\text{pivot}} \end{bmatrix} + \begin{bmatrix} x_{\text{pivot}} \\ y_{\text{pivot}} \end{bmatrix}$$

Given an angle $\theta$ (clockwise rotation) and scaling factors $S_x, S_y$ (where $>1$ zooms in and $<1$ zooms out):

* $PA = \frac{1}{S_x} \cos(-\theta) = \frac{1}{S_x} \cos(\theta)$
* $PB = \frac{1}{S_x} \sin(-\theta) = -\frac{1}{S_x} \sin(\theta)$
* $PC = \frac{1}{S_y} -\sin(-\theta) = \frac{1}{S_y} \sin(\theta)$
* $PD = \frac{1}{S_y} \cos(-\theta) = \frac{1}{S_y} \cos(\theta)$

```c
#include "gba/types.h"

// GBA Fixed-point types
typedef s16 fp8_8;   // Signed 8.8 (1 sign + 7 integer bits + 8 fractional bits)
typedef s32 fp19_8;  // Signed 19.8 (Used for reference point registers BGxX / BGxY)

#define FP8_8_ONE 256

// Simple fixed-point lookup table definitions (0-255 map to 0-360 degrees)
// Values stored in 1.14 or 8.8 format. Assuming Sin/Cos returning 8.8 format (-256 to 256):
extern s16 Cos(u8 angle);
extern s16 Sin(u8 angle);

typedef struct {
    fp8_8 pa;
    fp8_8 pb;
    fp8_8 pc;
    fp8_8 pd;
    fp19_8 x_ref;
    fp19_8 y_ref;
} AffineBgParams;

/**
 * Calculates affine BG parameters for GBA hardware.
 * @param angle        Rotation angle: 0-255 (0 = 0 deg, 64 = 90 deg, 128 = 180 deg)
 * @param scaleX       Horizontal zoom in 8.8 fixed-point (256 = 1.0x, 512 = 2.0x)
 * @param scaleY       Vertical zoom in 8.8 fixed-point (256 = 1.0x, 512 = 2.0x)
 * @param pivotX       Pivot center on screen (0-239)
 * @param pivotY       Pivot center on screen (0-159)
 * @param texCenterX   Target center coordinate in the background texture
 * @param texCenterY   Target center coordinate in the background texture
 * @param out          Destination struct loaded into REG_BGxPA-PD and REG_BGxX-Y
 */
void CalculateAffineMatrix(u8 angle, fp8_8 scaleX, fp8_8 scaleY,
                           s16 pivotX, s16 pivotY,
                           s16 texCenterX, s16 texCenterY,
                           AffineBgParams *out)
{
    // Avoid division by zero
    if (scaleX == 0) scaleX = 1;
    if (scaleY == 0) scaleY = 1;

    // Retrieve trig factors (range -256 to +256)
    s32 cosVal = Cos(angle);
    s32 sinVal = Sin(angle);

    // Compute inverse scale components in 8.8: (256 * 256) / scale
    s32 invScaleX = (FP8_8_ONE * FP8_8_ONE) / scaleX;
    s32 invScaleY = (FP8_8_ONE * FP8_8_ONE) / scaleY;

    // Multiply trigonometric terms by inverse scale, shift off extra fractional byte
    out->pa = (fp8_8)((cosVal * invScaleX) >> 8);
    out->pb = (fp8_8)((-sinVal * invScaleX) >> 8);
    out->pc = (fp8_8)((sinVal * invScaleY) >> 8);
    out->pd = (fp8_8)((cosVal * invScaleY) >> 8);

    // Compute origin reference point in 19.8 format
    // Ref = TextureCenter - Matrix * ScreenPivot
    out->x_ref = ((fp19_8)texCenterX << 8) - ((out->pa * pivotX) + (out->pb * pivotY));
    out->y_ref = ((fp19_8)texCenterY << 8) - ((out->pc * pivotX) + (out->pd * pivotY));
}

```

---

### 3. Implementing Custom Bytecode Instructions in `pokeemerald`

Adding a new script command (e.g., `healpartycustom`) requires syncing the C execution table, the assembly macro definitions, and the Poryscript lexer/grammar.

#### Step 1: Write the C Execution Handler

In `src/scrcmd.c`, define the function implementing the command logic. Script command functions return `bool8` (`FALSE` continues running commands this frame, `TRUE` halts the VM loop until the next frame/event):

```c
bool8 ScrCmd_healpartycustom(struct ScriptContext *ctx)
{
    // Optional argument reading (e.g., reading a 16-bit word or 8-bit byte):
    // u16 partySlot = ScriptReadHalfword(ctx);

    u8 i;
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        HealPokemon(&gPlayerParty[i]);
    }

    return FALSE; // Continue processing subsequent script instructions immediately
}

```

#### Step 2: Register Function in Script Command Table

Add your handler prototype and assign it to the next available opcode in `include/scrcmd.h` and the dispatch array in `src/scrcmd.c`:

```c
// In src/scrcmd.c inside gScriptCmdTable[]:
    /* 0xXX */ ScrCmd_last_standard_command,
    /* 0xYY */ ScrCmd_healpartycustom, // New opcode slot

```

#### Step 3: Define Assembly Macros

Add the opcode mapping and mnemonic macro in `asm/macros/event.inc` so the assembler can generate the bytecode:

```assembly
    .macro healpartycustom
    .byte 0xYY      @ The identical numeric index from gScriptCmdTable[]
    @ If arguments were read via ScriptReadHalfword:
    @ .2byte \arg1
    .endm

```

#### Step 4: Expose to Poryscript

To call this command directly in `.pory` files, declare the keyword in your Poryscript build config or custom command definitions.

1. In projects using external `poryscript`, custom commands are defined in a custom commands definition file (or embedded `commands.json` / `poryscript.json`):
```json
{
  "name": "healpartycustom",
  "parameters": []
}

```


2. You can now use the instruction directly inside your `.pory` scripts:
```pory
script Route1_Nurse {
    lock
    msgbox("I will heal your team right away!")
    healpartycustom
    playfanfare(MUS_HEAL)
    waitfanfare
    msgbox("All set!")
    release
    end
}

```


3. Running `make` invokes `poryscript`, translating `healpartycustom` into `.byte 0xYY` in `Route1_Nurse.inc`, which the C interpreter parses via `ScrCmd_healpartycustom()`.
