// POKE-CONFLUENCE Workspace Graphics & Asset Scanner
const fs = require('fs');
const path = require('path');

function findProjectRoot(startPath) {
    let current = startPath;
    for (let i = 0; i < 5; i++) {
        if (fs.existsSync(path.join(current, 'pokeconfluence'))) {
            return path.join(current, 'pokeconfluence');
        }
        if (fs.existsSync(path.join(current, 'include', 'global.h')) &&
            fs.existsSync(path.join(current, 'data', 'maps'))) {
            return current;
        }
        const parent = path.dirname(current);
        if (parent === current) break;
        current = parent;
    }
    return startPath;
}

function getSpeciesGen(index) {
    if (index <= 151) return 'Kanto (Gen 1)';
    if (index <= 251) return 'Johto (Gen 2)';
    if (index <= 386) return 'Hoenn (Gen 3)';
    if (index <= 493) return 'Sinnoh (Gen 4)';
    if (index <= 649) return 'Unova (Gen 5)';
    if (index <= 721) return 'Kalos (Gen 6)';
    if (index <= 809) return 'Alola (Gen 7)';
    if (index <= 905) return 'Galar (Gen 8)';
    return 'Paldea / Confluence';
}

function scanAssets(projectRoot) {
    const root = findProjectRoot(projectRoot);
    const result = {
        projectRoot: root,
        species: [],
        trainers: [],
        items: [],
        overworld: [],
        tilesets: { primary: [], secondary: [] },
        battleEnvs: [],
        interface: [],
        palettes: [],
        stats: {
            totalSpecies: 0,
            totalTrainers: 0,
            totalItems: 0,
            totalOverworld: 0,
            totalTilesets: 0,
            totalInterface: 0
        }
    };

    // 1. Scan Pokémon Species
    const pokemonDir = path.join(root, 'graphics', 'pokemon');
    if (fs.existsSync(pokemonDir)) {
        const entries = fs.readdirSync(pokemonDir, { withFileTypes: true });
        let spIdx = 1;
        for (const entry of entries) {
            if (entry.isDirectory()) {
                const spDir = path.join(pokemonDir, entry.name);
                const files = fs.readdirSync(spDir);
                const spObj = {
                    index: spIdx++,
                    name: entry.name,
                    gen: getSpeciesGen(spIdx),
                    dir: spDir,
                    front: files.includes('front.png') ? path.join(spDir, 'front.png') : null,
                    animFront: files.includes('anim_front.png') ? path.join(spDir, 'anim_front.png') : null,
                    back: files.includes('back.png') ? path.join(spDir, 'back.png') : null,
                    normalPal: files.includes('normal.pal') ? path.join(spDir, 'normal.pal') : null,
                    shinyPal: files.includes('shiny.pal') ? path.join(spDir, 'shiny.pal') : null,
                    icon: files.includes('icon.png') ? path.join(spDir, 'icon.png') : null,
                    footprint: files.includes('footprint.png') ? path.join(spDir, 'footprint.png') : null
                };
                if (spObj.front || spObj.animFront || spObj.normalPal || spObj.icon) {
                    result.species.push(spObj);
                }
            }
        }
    }

    // 2. Scan Trainers
    const trainersDir = path.join(root, 'graphics', 'trainers');
    if (fs.existsSync(trainersDir)) {
        const frontPicsDir = path.join(trainersDir, 'front_pics');
        const backPicsDir = path.join(trainersDir, 'back_pics');
        const palettesDir = path.join(trainersDir, 'palettes');

        if (fs.existsSync(frontPicsDir)) {
            const files = fs.readdirSync(frontPicsDir);
            for (const f of files) {
                if (f.endsWith('.png')) {
                    const base = f.replace(/\.png$/, '');
                    const palPath = path.join(palettesDir, `${base}.pal`);
                    result.trainers.push({
                        name: base,
                        type: 'front',
                        pic: path.join(frontPicsDir, f),
                        palette: fs.existsSync(palPath) ? palPath : null
                    });
                }
            }
        }
        if (fs.existsSync(backPicsDir)) {
            const files = fs.readdirSync(backPicsDir);
            for (const f of files) {
                if (f.endsWith('.png')) {
                    const base = f.replace(/\.png$/, '');
                    const palPath = path.join(palettesDir, `${base}.pal`);
                    result.trainers.push({
                        name: base,
                        type: 'back',
                        pic: path.join(backPicsDir, f),
                        palette: fs.existsSync(palPath) ? palPath : null
                    });
                }
            }
        }
    }

    // 3. Scan Items
    const itemsDir = path.join(root, 'graphics', 'items');
    if (fs.existsSync(itemsDir)) {
        const iconsDir = path.join(itemsDir, 'icons');
        if (fs.existsSync(iconsDir)) {
            const files = fs.readdirSync(iconsDir);
            for (const f of files) {
                if (f.endsWith('.png')) {
                    const base = f.replace(/\.png$/, '');
                    const palPath = path.join(iconsDir, `${base}.pal`);
                    result.items.push({
                        name: base,
                        icon: path.join(iconsDir, f),
                        palette: fs.existsSync(palPath) ? palPath : null
                    });
                }
            }
        }
    }

    // 4. Scan Overworld Object Events
    const owDir = path.join(root, 'graphics', 'object_events');
    if (fs.existsSync(owDir)) {
        const subdirs = [
            { folder: path.join(owDir, 'pics', 'people'), category: 'people' },
            { folder: path.join(owDir, 'pics', 'pokemon'), category: 'pokemon' },
            { folder: path.join(owDir, 'pics', 'misc'), category: 'misc' }
        ];

        for (const sub of subdirs) {
            if (fs.existsSync(sub.folder)) {
                const files = fs.readdirSync(sub.folder);
                for (const f of files) {
                    if (f.endsWith('.png')) {
                        result.overworld.push({
                            name: f.replace(/\.png$/, ''),
                            category: sub.category,
                            path: path.join(sub.folder, f)
                        });
                    }
                }
            }
        }
    }

    // 5. Scan Tilesets
    const tilesetsDir = path.join(root, 'data', 'tilesets');
    if (fs.existsSync(tilesetsDir)) {
        const primaryDir = path.join(tilesetsDir, 'primary');
        if (fs.existsSync(primaryDir)) {
            const entries = fs.readdirSync(primaryDir, { withFileTypes: true });
            for (const entry of entries) {
                if (entry.isDirectory()) {
                    const dir = path.join(primaryDir, entry.name);
                    const files = fs.readdirSync(dir);
                    const palsDir = path.join(dir, 'palettes');
                    let pals = [];
                    if (fs.existsSync(palsDir)) {
                        pals = fs.readdirSync(palsDir).filter(p => p.endsWith('.pal')).map(p => path.join(palsDir, p));
                    }
                    result.tilesets.primary.push({
                        name: entry.name,
                        dir: dir,
                        tiles: files.includes('tiles.png') ? path.join(dir, 'tiles.png') : null,
                        metatiles: files.includes('metatiles.bin') ? path.join(dir, 'metatiles.bin') : null,
                        palettes: pals
                    });
                }
            }
        }

        const secondaryDir = path.join(tilesetsDir, 'secondary');
        if (fs.existsSync(secondaryDir)) {
            const entries = fs.readdirSync(secondaryDir, { withFileTypes: true });
            for (const entry of entries) {
                if (entry.isDirectory()) {
                    const dir = path.join(secondaryDir, entry.name);
                    const files = fs.readdirSync(dir);
                    const palsDir = path.join(dir, 'palettes');
                    let pals = [];
                    if (fs.existsSync(palsDir)) {
                        pals = fs.readdirSync(palsDir).filter(p => p.endsWith('.pal')).map(p => path.join(palsDir, p));
                    }
                    result.tilesets.secondary.push({
                        name: entry.name,
                        dir: dir,
                        tiles: files.includes('tiles.png') ? path.join(dir, 'tiles.png') : null,
                        metatiles: files.includes('metatiles.bin') ? path.join(dir, 'metatiles.bin') : null,
                        palettes: pals
                    });
                }
            }
        }
    }

    // 6. Scan Battle Environments
    const battleEnvDir = path.join(root, 'graphics', 'battle_environment');
    if (fs.existsSync(battleEnvDir)) {
        const entries = fs.readdirSync(battleEnvDir, { withFileTypes: true });
        for (const entry of entries) {
            if (entry.isDirectory()) {
                const dir = path.join(battleEnvDir, entry.name);
                const files = fs.readdirSync(dir);
                result.battleEnvs.push({
                    name: entry.name,
                    dir: dir,
                    tiles: files.includes('tiles.png') ? path.join(dir, 'tiles.png') : null,
                    palette: files.includes('palette.pal') ? path.join(dir, 'palette.pal') : null,
                    map: files.includes('map.bin') ? path.join(dir, 'map.bin') : null
                });
            }
        }
    }

    // 7. Scan Interface, UI & Region Maps
    const uiFolders = ['pokenav', 'interface', 'battle_interface', 'title_screen', 'fonts', 'fame_checker', 'map_popups'];
    for (const uif of uiFolders) {
        const uiPath = path.join(root, 'graphics', uif);
        if (fs.existsSync(uiPath)) {
            const scanRec = (curDir, subName) => {
                const entries = fs.readdirSync(curDir, { withFileTypes: true });
                for (const e of entries) {
                    const full = path.join(curDir, e.name);
                    if (e.isDirectory()) {
                        scanRec(full, `${subName}/${e.name}`);
                    } else if (e.name.endsWith('.png') || e.name.endsWith('.pal')) {
                        result.interface.push({
                            name: e.name.replace(/\.[^.]+$/, ''),
                            category: uif,
                            subpath: subName,
                            path: full
                        });
                    }
                }
            };
            scanRec(uiPath, uif);
        }
    }

    result.stats.totalSpecies = result.species.length;
    result.stats.totalTrainers = result.trainers.length;
    result.stats.totalItems = result.items.length;
    result.stats.totalOverworld = result.overworld.length;
    result.stats.totalTilesets = result.tilesets.primary.length + result.tilesets.secondary.length;
    result.stats.totalInterface = result.interface.length;

    return result;
}

module.exports = {
    findProjectRoot,
    scanAssets
};
