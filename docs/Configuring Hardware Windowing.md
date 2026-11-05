### 1. Configuring Hardware Windowing (`WIN0` / `WIN1`) for Battle Splits

The GBA hardware PPU includes two rectangular window generators (**`WIN0`** and **`WIN1`**), an optional **Object Window** (derived from sprite alpha/masks), and an **Outside Window** (`WINOUT`). Windows define per-pixel clipping masks that determine which background layers (BG0–BG3) and sprites (OBJ) render, as well as whether hardware alpha blending applies.

```
Screen (240 × 160)
┌──────────────────────────────────────────────────────────────┐
│ WINOUT: Exterior boundary (World / Battle arena backdrop)   │
│                                                              │
│     WIN0: Rectangular Split / Dialogue Banner               │
│     ┌──────────────────────────────────────────────────┐     │
│     │ Inside WIN0: BG0 (Text) + BG1 (Box), Blending ON │     │
│     └──────────────────────────────────────────────────┘     │
│                                                              │
│     WIN1: Status Card / Split View                           │
│     ┌────────────────────────┐                               │
│     │ Inside WIN1: BG2 + OBJ │                               │
│     └────────────────────────┘                               │
└──────────────────────────────────────────────────────────────┘

```

#### Key Hardware Registers

| Register | Address | Description | Format / Bit Layout |
| --- | --- | --- | --- |
| `REG_DISPCNT` | `0x04000000` | Display Control | Bits 13, 14, 15 enable `WIN0`, `WIN1`, and `OBJWIN` |
| `REG_WIN0H` / `REG_WIN1H` | `0x04000040` / `42` | Horizontal Bounds | High Byte: Left edge $X_1$; Low Byte: Right edge $X_2$ |
| `REG_WIN0V` / `REG_WIN1V` | `0x04000044` / `46` | Vertical Bounds | High Byte: Top edge $Y_1$; Low Byte: Bottom edge $Y_2$ |
| `REG_WININ` | `0x04000048` | Window Interior Masks | Bits 0–5: `WIN0` layers; Bits 8–13: `WIN1` layers |
| `REG_WINOUT` | `0x0400004A` | Window Exterior Masks | Bits 0–5: `WINOUT` layers; Bits 8–13: `OBJWIN` layers |

* **Coordinate Boundary Rules:**
* Coordinates range from $0 \text{ to } 240$ horizontally and $0 \text{ to } 160$ vertically.
* If $X_1 > X_2$, the window renders from $X_1$ to $240$ and wraps from $0$ to $X_2$.
* If $X_1 = X_2$ or $Y_1 = Y_2$, the window is completely disabled for that axis.


* **Control Flags (`WININ` / `WINOUT`):**
* Bit 0: `WIN_BG0`
* Bit 1: `WIN_BG1`
* Bit 2: `WIN_BG2`
* Bit 3: `WIN_BG3`
* Bit 4: `WIN_OBJ`
* Bit 5: `WIN_BLD` (Permits alpha blending inside this window)



#### Implementation: Battle Split Wipe / Textbox Window

```c
#include "gba/gba.h"

#define WIN_LAYER_BG0     (1 << 0)
#define WIN_LAYER_BG1     (1 << 1)
#define WIN_LAYER_BG2     (1 << 2)
#define WIN_LAYER_BG3     (1 << 3)
#define WIN_LAYER_OBJ     (1 << 4)
#define WIN_LAYER_BLEND   (1 << 5)

/**
 * Configures WIN0 as an isolated battle split/message viewport.
 * - Inside WIN0: BG0 (text/UI), BG1 (box graphic), Blending enabled.
 * - Outside WIN0 (WINOUT): BG2 (battle arena), BG3 (background), OBJ (Pokémon sprites).
 */
void SetupBattleSplitWindow(u8 left, u8 top, u8 right, u8 bottom)
{
    // 1. Set spatial coordinates (High byte = Start, Low byte = End)
    REG_WIN0H = (left << 8) | right;
    REG_WIN0V = (top << 8) | bottom;

    // 2. Configure interior layers visible inside WIN0
    REG_WININ = (WIN_LAYER_BG0 | WIN_LAYER_BG1 | WIN_LAYER_BLEND);

    // 3. Configure layers visible outside WIN0 (the rest of the screen)
    REG_WINOUT = (WIN_LAYER_BG2 | WIN_LAYER_BG3 | WIN_LAYER_OBJ);

    // 4. Enable WIN0 processing in the display control register
    REG_DISPCNT |= DISPCNT_WIN0_ON;
}

/**
 * Dynamic scanline H-Blank effect: animates a horizontal curtain split.
 * Call inside a frame update/task.
 */
void UpdateBattleSplitWipe(u8 progress) // progress: 0 to 120
{
    u8 left = 120 - progress;
    u8 right = 120 + progress;

    // Full vertical screen span (0 to 160)
    REG_WIN0H = (left << 8) | right;
    REG_WIN0V = (0 << 8) | 160;
}

```

---

### 2. Multi-Argument Script Command with Variable Resolution

In `pokeemerald`, the scripting engine supports resolving dynamic registers (e.g., `VAR_TEMP_0` through `VAR_0x4000` series) alongside raw literals using **`VarGet()`**.

Here is how to create a custom command:

`givecustomreward item_id, amount_or_var, out_result_var`

```
.pory source: givecustomreward ITEM_POTION, VAR_TEMP_1, VAR_RESULT
   │
   ▼ [poryscript transpilation]
.inc assembly: .byte 0xYY; .2byte ITEM_POTION; .2byte VAR_TEMP_1; .2byte VAR_RESULT
   │
   ▼ [C Virtual Machine: ScriptContext_Step]
ScrCmd_givecustomreward()
   ├── ScriptReadHalfword() -> itemId (raw literal or VarGet)
   ├── ScriptReadHalfword() -> amount (evaluated via VarGet)
   ├── ScriptReadHalfword() -> targetVarId (raw variable register ID)
   └── SetVar(targetVarId, status)

```

#### Step 1: Implement the C Execution Handler

In `src/scrcmd.c`, read each argument sequentially using `ScriptReadHalfword()` (reads a 16-bit little-endian value and advances the internal `scriptPtr` by 2 bytes):

```c
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "script.h"

bool8 ScrCmd_givecustomreward(struct ScriptContext *ctx)
{
    // Argument 1: Item ID (Evaluated so it can take a constant or a VAR)
    u16 itemId = VarGet(ScriptReadHalfword(ctx));

    // Argument 2: Quantity (Supports direct numbers or dynamic variables)
    u16 quantity = VarGet(ScriptReadHalfword(ctx));

    // Argument 3: Target variable to store the result (Do NOT use VarGet here!)
    u16 outVarId = ScriptReadHalfword(ctx);

    bool8 success = AddBagItem(itemId, (u8)quantity);

    // Write return code into the user-supplied script variable register
    VarSet(outVarId, success ? 1 : 0);

    return FALSE; // Return FALSE to immediately advance to the next script opcode
}

```

#### Step 2: Register the Opcode in Engine Headers

1. Expose the function prototype in `include/scrcmd.h`:
```c
bool8 ScrCmd_givecustomreward(struct ScriptContext *ctx);

```


2. Locate `gScriptCmdTable` in `src/scrcmd.c` and append the handler to the bottom of the array:
```c
// At the end of gScriptCmdTable:
    /* 0xXX */ ScrCmd_last_existing_command,
    /* 0xYY */ ScrCmd_givecustomreward,

```



#### Step 3: Define Assembly Macros

Add the opcode emission pattern to `asm/macros/event.inc`:

```assembly
    .macro givecustomreward item:req, amount:req, result_var:req
    .byte 0xYY                  @ Match the index in gScriptCmdTable
    .2byte \item
    .2byte \amount
    .2byte \result_var
    .endm

```

#### Step 4: Add Poryscript Command Definition

In your project's custom commands schema file (e.g., `tools/poryscript/resources/commands.json` or custom include file), register the syntax:

```json
{
  "name": "givecustomreward",
  "parameters": [
    { "name": "item", "type": "halfword" },
    { "name": "amount", "type": "halfword" },
    { "name": "result_var", "type": "halfword" }
  ]
}

```

#### Step 5: Test in `.pory`

You can now pass numeric literals, symbolic defines, or dynamic variable registers interchangeably:

```pory
script Route101_RewardGiver {
    lock
    faceplayer
    
    // Set up a dynamic reward quantity based on player progression
    setvar(VAR_TEMP_1, 5)

    // Pass: constant item, dynamic variable for amount, and register to receive status
    givecustomreward(ITEM_SUPER_POTION, VAR_TEMP_1, VAR_RESULT)

    if (var(VAR_RESULT) == 1) {
        msgbox("Here are 5 Super Potions!")
    } else {
        msgbox("Your Bag is full...")
    }

    release
    end
}

```
