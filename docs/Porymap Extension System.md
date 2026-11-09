# Porymap Extension System

## Overview

Yes. While Porymap does not use traditional compiled `.dll` or `.so` plugin binaries, it includes a built-in **Custom Scripting API** designed specifically to create extensions, custom tools, and automations without modifying Porymap’s C++/Qt source code.

---

### How Extensions Work in Porymap

Porymap embeds a JavaScript/ECMAScript engine that exposes editor hooks and APIs:

* **Custom Script Files (`.js`):** You write JavaScript files containing custom behavior, utility actions, or visual overlays.


* **Management UI:** Scripts are managed directly in the application via **Options $\rightarrow$ Custom Scripts...**.


* **Script Actions:** You can register custom commands that become clickable actions or hotkeys within Porymap.



---

### Key Capabilities of the Scripting API

1. **Event Callbacks:**
Your script can export functions that automatically trigger on application events, such as:


* `onProjectOpened` / `onProjectClosed`


* `onMapOpened` / `onLayoutOpened`


* `onBlockChanged` (fires whenever a tile/metatile is painted)


* `onBlockHoverChanged` / `onBlockHoverCleared`


* `onMapResized` / `onMapShifted`


* `onTilesetUpdated`




2. **Map & Layout Manipulation:**
* Read and set metatiles (`map.getMetatileId()`, `map.setMetatileId()`).
* Modify collisions, elevations, and map dimensions.
* Batch updates and manage undo history (`map.commit()`, `map.redraw()`).


3. **Overlay & Diagnostics:**
* Draw custom shapes, text, rectangles, or highlights over the map view to flag errors, visualize event zones, or inspect layers.




4. **Common Use Cases:**
* Randomizing grass or terrain metatiles during painting.
* Automated tile error checking (e.g., solid tiles lacking collision, invalid warp alignments).


* Procedural map/room generators.
* Custom day/night palette preview toggles.



---

### Minimal Example

To create an extension:

1. Open Porymap and go to **Options $\rightarrow$ Custom Scripts...**.


2. Click the new script button to create a `.js` template.
3. Add custom logic to exported callbacks or register a custom menu action:

```javascript
// Automatically paint an alternate variation when placing a specific metatile
export function onBlockChanged(x, y, metatileId) {
    if (metatileId === 0x0001) {
        // Replace with variation 0x0002
        map.setMetatileId(x, y, 0x0002, true, true);
    }
}

```

For full API function signatures (`map.*`, `overlay.*`, `utility.*`, and `constants.*`), refer to the [Porymap Scripting Capabilities Manual](https://huderlem.github.io/porymap/manual/scripting-capabilities.html).
