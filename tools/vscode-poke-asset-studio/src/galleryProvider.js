// POKE-CONFLUENCE Activity Bar Asset Gallery View Provider
const vscode = require('vscode');
const path = require('path');
const scanner = require('./scanner');

class PokeAssetGalleryViewProvider {
    static register(context) {
        const provider = new PokeAssetGalleryViewProvider(context);
        return vscode.window.registerWebviewViewProvider(
            'pokeAssetStudio.galleryView',
            provider,
            {
                webviewOptions: { retainContextWhenHidden: true }
            }
        );
    }

    constructor(context) {
        this.context = context;
        this.view = null;
    }

    resolveWebviewView(webviewView) {
        this.view = webviewView;
        webviewView.webview.options = {
            enableScripts: true,
            localResourceRoots: [
                vscode.Uri.file(this.context.extensionPath),
                vscode.Uri.file(vscode.workspace.rootPath || '')
            ]
        };

        webviewView.webview.html = this.getHtmlForWebview(webviewView.webview);

        webviewView.webview.onDidReceiveMessage(async (msg) => {
            if (msg.type === 'scan_project') {
                const root = vscode.workspace.rootPath || process.cwd();
                const scanData = scanner.scanAssets(root);
                webviewView.webview.postMessage({
                    type: 'project_data',
                    data: scanData
                });
            } else if (msg.type === 'open_asset') {
                const uri = vscode.Uri.file(msg.filePath);
                try {
                    await vscode.commands.executeCommand('vscode.openWith', uri, 'pokeAssetStudio.editor');
                } catch (e) {
                    await vscode.commands.executeCommand('vscode.open', uri);
                }
            } else if (msg.type === 'notify') {
                vscode.window.showInformationMessage(msg.message);
            }
        });
    }

    getHtmlForWebview(webview) {
        const scriptUri = webview.asWebviewUri(vscode.Uri.file(
            path.join(this.context.extensionPath, 'media', 'gallery.js')
        ));
        const styleUri = webview.asWebviewUri(vscode.Uri.file(
            path.join(this.context.extensionPath, 'media', 'gallery.css')
        ));

        return `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="${styleUri}">
    <title>Asset Gallery</title>
</head>
<body>
    <div class="gallery-header">
        <div class="stats-bar" id="statsHeader">Loading project assets...</div>
        <input type="text" id="searchInput" placeholder="Filter species, trainers, items..." class="search-box">
        <div class="tab-bar">
            <button class="tab-btn active" data-tab="pokemon">🐾 Battlers</button>
            <button class="tab-btn" data-tab="trainers">🧑 Trainers</button>
            <button class="tab-btn" data-tab="items">🎒 Items</button>
            <button class="tab-btn" data-tab="overworld">🚶 Overworld</button>
            <button class="tab-btn" data-tab="tilesets">🏛️ Tilesets</button>
            <button class="tab-btn" data-tab="interface">🗺️ UI & Maps</button>
        </div>
        <div class="subfilter-bar" id="subfilterBar">
            <button class="subfilter-btn active" data-gen="all">All</button>
            <button class="subfilter-btn" data-gen="kanto">Gen 1 Kanto</button>
            <button class="subfilter-btn" data-gen="johto">Gen 2 Johto</button>
            <button class="subfilter-btn" data-gen="hoenn">Gen 3 Hoenn</button>
            <button class="subfilter-btn" data-gen="later">Gen 4+ / Custom</button>
        </div>
    </div>

    <div class="gallery-content">
        <div id="loadingIndicator" class="loading">Scanning project assets...</div>
        <div id="galleryList" class="gallery-list"></div>
    </div>

    <script src="${scriptUri}"></script>
</body>
</html>`;
    }
}

module.exports = {
    PokeAssetGalleryViewProvider
};
