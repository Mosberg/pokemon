# Decompilation Scripting Bible & Reference

## 1. Script Dialect Comparison

| Crystal (GBC Assembly) | pokeemerald-expansion Bytecode | Description |
| ---------------------- | ------------------------------ | ----------- |
| `opentext` / `writetext` | `lock` / `faceplayer` / `msgbox` | Initiates interaction and displays dialogue box. |
| `closetext` | `release` | Closes text box and frees player movement. |
| `verbosegiveitem ITEM, N` | `giveitem ITEM, N` | Hands item to player with standard fanfare. |
| `setevent EVENT_NAME` | `setflag FLAG_NAME` | Sets a progress/state bit flag. |
| `clearevent EVENT_NAME` | `clearflag FLAG_NAME` | Clears a progress/state bit flag. |
| `checkevent EVENT_NAME` | `goto_if_set FLAG, Label` | Conditional branching based on flag state. |
| `waitsfx` | `waitse` | Waits for active sound effect to finish. |
| `playsound SFX_*` | `playse SE_*` | Plays a sound effect. |
| `special SpecialName` | `special SpecialName` | Executes C-level engine routine. |

## 2. Text Box Standards
GBA text engines support 2 lines per dialogue box, with a line width limit of ~34 characters:
```inc
GoldenrodCity_Johto_Text_Welcome:
    .string "Welcome to Goldenrod City!\n"
    .string "The bustling heart of Johto.$"
```
Placeholders:
- `{PLAYER}`: Player's chosen trainer name.
- `{RIVAL}`: Rival's name.
- `{STR_VAR_1}`, `{STR_VAR_2}`, `{STR_VAR_3}`: Buffered strings.
- `{BUFFER_1}`, `{BUFFER_2}`: Buffered numbers.

## 3. Dynamic Multichoice Menus
Instead of fixed multichoice lists, build menus dynamically in scripts:
```inc
Common_EventScript_ChooseDestination::
    dynmultipush Common_Text_DestVermilion, 0
    dynmultipush Common_Text_DestOlivine, 1
    dynmultipush Common_Text_DestSlateport, 2
    dynmultistack 0, 0, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
    switch VAR_RESULT
    case 0, Common_EventScript_WarpVermilion
    case 1, Common_EventScript_WarpOlivine
    case 2, Common_EventScript_WarpSlateport
    goto Common_EventScript_CancelTransit
```

## 4. Johto Phone Book Architecture
- **Registration**:
  - `special JohtoPhoneRegister` stores contact in save data.
  - Sets `FLAG_JOHTO_PHONE_*_REGISTERED`.
- **Rematches**:
  - Sets `FLAG_JOHTO_ENGINE_*_READY_FOR_REMATCH`.
  - Tier counter variable `VAR_JOHTO_MEM_W*` increments after each victory:
    - Tier 0: Level ~10-15
    - Tier 1: Level ~20-25
    - Tier 2: Level ~30-35
    - Tier 3: Level ~45-50
    - Tier 4: Level ~60+

