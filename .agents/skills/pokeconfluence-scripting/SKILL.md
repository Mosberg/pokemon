---
name: pokeconfluence-scripting
description: Guides writing, migrating, and debugging Johto/Kanto event scripts, Poryscript, bytecode macros, specials, and dynamic menus. Activates when editing .inc or .pory scripts.
---

# Pokémon Confluence Scripting Skill

This skill guides developing, converting, and testing event scripts across Hoenn, Kanto, and Johto in `pokeconfluence/`.

## Scripting Principles

1. **Dialect Differences**:
   - Crystal/GBC macros use different command sets (`opentext`, `writetext`, `closetext`, `faceplayer`).
   - GBA Expansion scripts use bytecode macros: `lock`, `faceplayer`, `msgbox <label>, MSGBOX_DEFAULT`, `release`.
   - String termination: GBA strings end in `$`. Lines wrap at 34 characters (2 lines per box).

2. **Common Specials in Confluence**:
   - `special JohtoPhoneRegister`: Registers a trainer in the Johto phone system.
   - `special JohtoPhoneIsRegistered`: Checks if a trainer phone contact is already registered (`VAR_RESULT` = TRUE/FALSE).
   - `special JohtoGiveOddEgg`: Generates and gives the Crystal Odd Egg with high shiny chance and egg moves.
   - `special JohtoGiveParkBalls`: Distributes 20 Sport Balls for the Bug-Catching Contest.
   - `special Confluence_CountBadges`: Stores the total number of badges across all regions into `VAR_RESULT`.

3. **Dynamic Multichoice Menus**:
   Instead of static multichoice IDs, use dynamic multichoice:
   ```inc
   dynmultipush MyMap_Text_Option1, 0
   dynmultipush MyMap_Text_Option2, 1
   dynmultipush MyMap_Text_Option3, 2
   dynmultistack 0, 0, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
   switch VAR_RESULT
   case 0, MyMap_EventScript_Choice1
   case 1, MyMap_EventScript_Choice2
   case 2, MyMap_EventScript_Choice3
   ```

4. **Map Callbacks (`ON_TRANSITION`)**:
   - Strictly reserved for setting/clearing object hide flags (`setflag`, `clearflag`) and updating map weather/metatiles.
   - Never call `message`, `msgbox`, `waitmessage`, or `removeobject` in `ON_TRANSITION` callbacks.

5. **Trainer Sight Battles**:
   - Always put the `trainerbattle` command at the very start of the trainer label:
   ```inc
   Route30_Johto_EventScript_Joey::
       trainerbattle_single TRAINER_JOEY_1, Route30_Johto_Text_JoeyIntro, Route30_Johto_Text_JoeyDefeat
       msgbox Route30_Johto_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
       end
   ```

