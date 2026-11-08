// POKE-CONFLUENCE Pokémon GBA Asset Studio Extension Entry Point
const vscode = require('vscode');
const { PokeAssetEditorProvider } = require('./src/editorProvider');
const { PokeAssetGalleryViewProvider } = require('./src/galleryProvider');
const scanner = require('./src/scanner');

/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {
    console.log('[PokeAssetStudio] Pokémon GBA Asset Studio v1.1.0 activating...');

    // 1. Register Custom Editor for Images and Palettes (.png, .pal, .gbapal, .4bpp, .8bpp, .act, .gpl)
    context.subscriptions.push(PokeAssetEditorProvider.register(context));

    // 2. Register Activity Bar Gallery View
    context.subscriptions.push(PokeAssetGalleryViewProvider.register(context));

    // 3. Register Context Menu Command
    context.subscriptions.push(
        vscode.commands.registerCommand('pokeAssetStudio.openInStudio', async (uri) => {
            if (!uri && vscode.window.activeTextEditor) {
                uri = vscode.window.activeTextEditor.document.uri;
            }
            if (uri) {
                await vscode.commands.executeCommand('vscode.openWith', uri, 'pokeAssetStudio.editor');
            }
        })
    );

    // 4. Register Quick Open Gallery Command
    context.subscriptions.push(
        vscode.commands.registerCommand('pokeAssetStudio.openGallery', async () => {
            await vscode.commands.executeCommand('workbench.view.extension.poke-asset-studio');
        })
    );

    // 5. Register Project Graphics Auditor Command
    context.subscriptions.push(
        vscode.commands.registerCommand('pokeAssetStudio.auditAssets', async () => {
            const root = vscode.workspace.rootPath || process.cwd();
            vscode.window.withProgress({
                location: vscode.ProgressLocation.Notification,
                title: "Auditing Pokémon Confluence graphics...",
                cancellable: false
            }, async (progress) => {
                const scan = scanner.scanAssets(root);
                const doc = await vscode.workspace.openTextDocument({
                    content: `# Pokémon Confluence Asset Audit Report
Generated: ${new Date().toLocaleString()}

## Summary Statistics
- **Total Species Registered**: ${scan.species.length}
- **Total Trainer Classes**: ${scan.trainers.length}
- **Total Items**: ${scan.items.length}
- **Overworld Object Events**: ${scan.overworld.length}
- **Tilesets**: ${scan.tilesets.primary.length} Primary | ${scan.tilesets.secondary.length} Secondary
- **Interface & UI Files**: ${scan.interface.length}

## Species Generation Breakdown
- **Kanto (Gen 1)**: ${scan.species.filter(s => s.index <= 151).length}
- **Johto (Gen 2)**: ${scan.species.filter(s => s.index > 151 && s.index <= 251).length}
- **Hoenn (Gen 3)**: ${scan.species.filter(s => s.index > 251 && s.index <= 386).length}
- **Later Gens / Custom**: ${scan.species.filter(s => s.index > 386).length}

## Engine Limits Compliance
- **GBA PPU Palette Limit**: 16 colors per palette slot, 16 slots (256 colors total).
- **Slot 0 Policy**: Strictly reserved as transparent.
- **BGR555 Snap**: Hardware 5-bit color quantization.
`,
                    language: 'markdown'
                });
                await vscode.window.showTextDocument(doc);
            });
        })
    );

    console.log('[PokeAssetStudio] Pokémon GBA Asset Studio successfully activated.');
}

function deactivate() {
    console.log('[PokeAssetStudio] Pokémon GBA Asset Studio deactivated.');
}

module.exports = {
    activate,
    deactivate
};
