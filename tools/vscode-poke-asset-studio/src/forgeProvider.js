// POKE-CONFLUENCE Pokémon GBA Forge Webview Panel Provider
const vscode = require('vscode');
const fs = require('fs');
const path = require('path');
const scanner = require('./scanner');

function parsePjsContent(content) {
    const lines = content.split(/\r?\n/);
    const data = {};
    let curKey = null;

    for (const line of lines) {
        const trimmed = line.trim();
        if (!trimmed || trimmed.startsWith('//') || trimmed.startsWith('$')) continue;

        if (!line.startsWith(' ') && !line.startsWith('\t')) {
            const match = trimmed.match(/^[a-zA-Z0-9_]+/);
            if (match && !trimmed.includes('=')) {
                curKey = match[0];
                data[curKey] = [];
            } else {
                curKey = null;
            }
        } else if (curKey) {
            data[curKey].push(trimmed);
        }
    }
    return data;
}

class PokeGbaForgeProvider {
    static currentPanel = undefined;

    static createOrShow(context) {
        const column = vscode.window.activeTextEditor
            ? vscode.window.activeTextEditor.viewColumn
            : undefined;

        if (PokeGbaForgeProvider.currentPanel) {
            PokeGbaForgeProvider.currentPanel.panel.reveal(column);
            return;
        }

        const panel = vscode.window.createWebviewPanel(
            'pokeAssetStudio.forge',
            'Pokémon GBA Forge Studio',
            column || vscode.ViewColumn.One,
            {
                enableScripts: true,
                retainContextWhenHidden: true,
                localResourceRoots: [
                    vscode.Uri.file(context.extensionPath),
                    vscode.Uri.file(path.join(context.extensionPath, 'src', 'html')),
                    vscode.Uri.file(path.join(context.extensionPath, 'src', 'pjs'))
                ]
            }
        );

        PokeGbaForgeProvider.currentPanel = new PokeGbaForgeProvider(panel, context);
    }

    constructor(panel, context) {
        this.panel = panel;
        this.context = context;

        this.update();
        this.panel.onDidDispose(() => this.dispose(), null, this.context.subscriptions);

        // Handle messages from the Forge webview
        this.panel.webview.onDidReceiveMessage(async (msg) => {
            if (msg.type === 'export_to_pokeconfluence') {
                try {
                    const root = scanner.findProjectRoot(vscode.workspace.rootPath || process.cwd());
                    const name = (msg.name || 'custom_species').toLowerCase().replace(/[^a-z0-9_]/g, '_');
                    const targetDir = path.join(root, 'graphics', 'pokemon', name);

                    if (!fs.existsSync(targetDir)) {
                        fs.mkdirSync(targetDir, { recursive: true });
                    }

                    let count = 0;
                    if (msg.front) {
                        fs.writeFileSync(path.join(targetDir, 'front.png'), Buffer.from(msg.front.replace(/^data:image\/png;base64,/, ''), 'base64'));
                        count++;
                    }
                    if (msg.back) {
                        fs.writeFileSync(path.join(targetDir, 'back.png'), Buffer.from(msg.back.replace(/^data:image\/png;base64,/, ''), 'base64'));
                        count++;
                    }
                    if (msg.animFront) {
                        fs.writeFileSync(path.join(targetDir, 'anim_front.png'), Buffer.from(msg.animFront.replace(/^data:image\/png;base64,/, ''), 'base64'));
                        count++;
                    }
                    if (msg.icon) {
                        fs.writeFileSync(path.join(targetDir, 'icon.png'), Buffer.from(msg.icon.replace(/^data:image\/png;base64,/, ''), 'base64'));
                        count++;
                    }
                    if (msg.footprint) {
                        fs.writeFileSync(path.join(targetDir, 'footprint.png'), Buffer.from(msg.footprint.replace(/^data:image\/png;base64,/, ''), 'base64'));
                        count++;
                    }
                    if (msg.normalPal) {
                        fs.writeFileSync(path.join(targetDir, 'normal.pal'), msg.normalPal, 'utf-8');
                        count++;
                    }
                    if (msg.shinyPal) {
                        fs.writeFileSync(path.join(targetDir, 'shiny.pal'), msg.shinyPal, 'utf-8');
                        count++;
                    }

                    const action = await vscode.window.showInformationMessage(
                        `Saved ${count} assets for ${name} into pokeconfluence!`,
                        'Open in Asset Studio'
                    );

                    if (action === 'Open in Asset Studio') {
                        const frontUri = vscode.Uri.file(path.join(targetDir, 'front.png'));
                        await vscode.commands.executeCommand('vscode.openWith', frontUri, 'pokeAssetStudio.editor');
                    }
                } catch (err) {
                    vscode.window.showErrorMessage(`Failed to export species: ${err.message}`);
                }
            } else if (msg.type === 'notify') {
                vscode.window.showInformationMessage(msg.message);
            }
        });
    }

    dispose() {
        PokeGbaForgeProvider.currentPanel = undefined;
        this.panel.dispose();
    }

    update() {
        const forgeHtmlPath = path.join(this.context.extensionPath, 'src', 'html', 'index.html');
        const forgePjsPath = path.join(this.context.extensionPath, 'src', 'pjs', 'main.pjs');

        if (fs.existsSync(forgeHtmlPath)) {
            let html = fs.readFileSync(forgeHtmlPath, 'utf-8');

            // Parse Perchance tables if main.pjs exists
            let perchanceData = {};
            if (fs.existsSync(forgePjsPath)) {
                try {
                    const pjsContent = fs.readFileSync(forgePjsPath, 'utf-8');
                    perchanceData = parsePjsContent(pjsContent);
                } catch (e) {
                    console.error('Failed to parse main.pjs:', e);
                }
            }

            // Inject VSCode API bridge, Perchance Generator tables & Save to Game button
            const bridgeScript = `
<script>
    const vscode = acquireVsCodeApi();
    window.PERCHANCE_FORGE_DATA = ${JSON.stringify(perchanceData)};

    // Enhanced Randomizer using Perchance main.pjs tables
    if (window.PERCHANCE_FORGE_DATA && Object.keys(window.PERCHANCE_FORGE_DATA).length > 0) {
        const pjs = window.PERCHANCE_FORGE_DATA;
        const pick = (arr) => arr && arr.length > 0 ? arr[Math.floor(Math.random() * arr.length)] : null;

        const diceBtn = document.getElementById('diceBtn');
        if (diceBtn) {
            diceBtn.onclick = () => {
                // Name generation: either sampleName or prefix + suffix
                let name = '';
                if (pjs.sampleName && Math.random() < 0.6) {
                    name = pick(pjs.sampleName);
                } else if (pjs.namePrefix && pjs.nameSuffix) {
                    name = pick(pjs.namePrefix) + pick(pjs.nameSuffix).toLowerCase();
                } else {
                    name = pick(['Embercub', 'Aquaffin', 'Thornimp', 'Galvokit', 'Cindrake', 'Frostnip', 'Voltpup']);
                }
                document.getElementById('nameInput').value = name;

                // Types
                const types = (pjs.pokeType && pjs.pokeType.length > 0) ? pjs.pokeType : TYPES.slice(1);
                document.getElementById('type1Input').value = pick(types);
                document.getElementById('type2Input').value = Math.random() < 0.4 ? pick(types) : 'None';

                // Body plan
                if (pjs.bodyPlan && pjs.bodyPlan.length > 0) {
                    document.getElementById('bodyInput').value = pick(pjs.bodyPlan);
                }

                // Description traits
                const traits = [];
                if (pjs.trait) traits.push(pick(pjs.trait));
                if (pjs.personality && Math.random() < 0.5) traits.push(pick(pjs.personality));
                if (traits.length > 0 && document.getElementById('descInput')) {
                    document.getElementById('descInput').value = traits.join(', ');
                }

                if (typeof refreshPrompt === 'function') refreshPrompt();
            };
        }
    }

    window.exportToGame = function() {
        if (!S.front) {
            alert('Please generate or upload a sprite first!');
            return;
        }
        const name = (document.getElementById('nameInput').value || 'new_pokemon').trim();

        // Front canvas
        const cFront = document.createElement('canvas');
        drawIndexed(cFront, S.front, S.front.pal);

        // Back canvas
        let backData = null;
        if (S.back) {
            const cBack = document.createElement('canvas');
            drawIndexed(cBack, S.back, S.front.pal);
            backData = cBack.toDataURL('image/png');
        }

        // Anim Front
        const animCanvas = document.getElementById('animCanvas');
        const iconCanvas = document.getElementById('iconCanvas');
        const footCanvas = document.getElementById('footCanvas');

        // Palettes
        const normalPal = jascPal(S.front.pal);
        const shinyPal = S.shinyPal ? jascPal(S.shinyPal) : null;

        vscode.postMessage({
            type: 'export_to_pokeconfluence',
            name: name,
            front: cFront.toDataURL('image/png'),
            back: backData,
            animFront: animCanvas ? animCanvas.toDataURL('image/png') : null,
            icon: iconCanvas ? iconCanvas.toDataURL('image/png') : null,
            footprint: footCanvas ? footCanvas.toDataURL('image/png') : null,
            normalPal: normalPal,
            shinyPal: shinyPal
        });
    };
</script>
`;
            // Add Export to pokeconfluence button in the top header
            const exportButtonHtml = `
            <button onclick="window.exportToGame()" style="background: #9bbc0f; color: #0a140a; border: 2px solid #000; border-radius: 6px; padding: 4px 12px; font-weight: bold; cursor: pointer; font-size: 11px; margin-left: 12px;">
                ⚡ Save to pokeconfluence
            </button>
            `;

            html = html.replace('</header>', `${exportButtonHtml}</header>`);
            html = html.replace('</body>', `${bridgeScript}</body>`);

            this.panel.webview.html = html;
        } else {
            this.panel.webview.html = `<h3>Pokémon GBA Forge not found at src/html/index.html</h3>`;
        }
    }
}

module.exports = {
    PokeGbaForgeProvider
};
