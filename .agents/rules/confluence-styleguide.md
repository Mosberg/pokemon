---
description: C coding conventions and formatting standards for Pokémon Confluence
globs: pokeconfluence/src/**/*.c, pokeconfluence/include/**/*.h, pokeconfluence/test/**/*.c
---

# Pokémon Confluence C Styleguide & Standards

All C source code in `pokeconfluence/` must adhere to these rules:

## 1. Naming Conventions
- **Functions**: `PascalCase` (e.g. `Confluence_CountBadges`, `JohtoGiveOddEgg`).
- **Structs & Typedefs**: `PascalCase` (e.g. `struct ConfluenceState`, `TrainerParty`).
- **Variables & Struct Fields**: `camelCase` (e.g. `badgeCount`, `metLocation`).
- **Globals**: Prefix with `g` (e.g. `gPlayerPartyCount`, `gSaveBlock1Ptr`).
- **Static File-Scope Variables**: Prefix with `s` (e.g. `sFieldKitMoves`, `sOddEggSpecies`).
- **Macros & Constants**: `UPPER_SNAKE_CASE` (e.g. `MAX_LEVEL`, `FLAG_CONFLUENCE_APEX_CHAMPION`).
- **Enums**: `UPPER_SNAKE_CASE` values (e.g. `MAPSEC_JOHTO_NEW_BARK_TOWN`).

## 2. Formatting & Layout
- **Indentation**: Exactly 4 spaces. Never use hard tabs in `.c` or `.h` files.
- **Braces**: Allman style. Opening and closing braces must be placed on their own lines:
  ```c
  if (condition)
  {
      DoAction();
  }
  else
  {
      DoOtherAction();
  }
  ```
- **Control Statements**: Space between keyword and condition: `if (...)`, `for (...)`, `while (...)`, `switch (...)`.
- **Switch Alignment**: `case` labels align with the `switch` block level:
  ```c
  switch (region)
  {
  case REGION_HOENN:
      return 8;
  case REGION_KANTO:
      return 16;
  default:
      return 0;
  }
  ```
- **Operators**: Space around binary operators (`a + b`, `x == y`, `ptr->field`). No space around unary/increment operators (`i++`, `!flag`).

## 3. Comments & Traceability
- Mark all custom logic with `// POKE-CONFLUENCE`.
- Single-line comments start with `// ` (capitalized, ending with a period).
- Block comments use `/* ... */`.
- Never delete or modify unrelated upstream comments.

