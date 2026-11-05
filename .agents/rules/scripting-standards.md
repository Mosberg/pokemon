---
description: Scripting conventions for Poryscript and asm event scripts in Pokémon Confluence
globs: pokeconfluence/data/maps/**/*.inc, pokeconfluence/data/maps/**/*.pory, pokeconfluence/data/scripts/**/*.inc
---

# Scripting Standards & Event Conversion Rules

All event scripting in `pokeconfluence/` must adhere to these rules:

## 1. Poryscript and Bytecode Assembly
- Scripts are located in `pokeconfluence/data/maps/<MapName>/scripts.inc` or `.pory`.
- When writing assembly `.inc` scripts, indent with tabs.
- Macro arguments must be separated by comma or space without unescaped C++ expressions (e.g. write literal trainer IDs or definitions, not arithmetic like `BASE + 5`).

## 2. Text Formatting
- Strings must be terminated with `$`.
- Overworld text boxes support a maximum of 2 lines per scroll block:
  ```inc
  MyMap_Text_Intro:
      .string "Welcome to Goldenrod City!\n"
      .string "The bustling heart of Johto.$"
  ```
- Use standard expansion placeholders (`{PLAYER}`, `{STR_VAR_1}`, `{STR_VAR_2}`).
- Do not leave untranslated Crystal placeholders (`<...>`).

## 3. Map Callbacks & ON_TRANSITION
- `ON_TRANSITION` callbacks run before map object events are spawned.
- **FORBIDDEN** in `ON_TRANSITION`:
  - `removeobject` / `addobject`
  - `message` / `msgbox`
  - `waitmessage` / `waitbuttonpress`
  - Long delays or task loops
  - Doing any of these will result in a black screen hang during map transition.
- Use `ON_TRANSITION` strictly for setting/clearing object hide flags (`setflag`, `clearflag`) and updating map weather or metatiles (`setweather`, `changeblock`).

## 4. Trainer Battles
- Trainer event scripts must start immediately with the `trainerbattle` command (no preceding `lockall` or `faceplayer` wrapper, which breaks trainer sight detection):
  ```inc
  Route30_Johto_EventScript_Joey::
      trainerbattle_single TRAINER_JOEY_1, Route30_Johto_Text_JoeyIntro, Route30_Johto_Text_JoeyDefeat
      msgbox Route30_Johto_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
      end
  ```

## 5. Dynamic Multichoice Menus
- Use the expansion dynamic multichoice system (`dynmultipush`, `dynmultistack`) for variable menus instead of hardcoded multichoice IDs.
- Result is stored in `VAR_RESULT` (`0` to `n-1`, or `MULTICHOICE_B_PRESSED` / `127`).

