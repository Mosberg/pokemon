// POKE-CONFLUENCE Custom Editor Provider for GBA Graphics & Palettes
const vscode = require('vscode');
const fs = require('fs');
const path = require('path');
const gba = require('./gba');

class PokeAssetEditorProvider {
    static register(context) {
        const provider = new PokeAssetEditorProvider(context);
        return vscode.window.registerCustomEditorProvider(
            'pokeAssetStudio.editor',
            provider,
            {
                webviewOptions: { retainContextWhenHidden: true },
                supportsMultipleEditorsPerDocument: false
            }
        );
    }

    constructor(context) {
        this.context = context;
    }

    async openCustomDocument(uri) {
        return {
            uri,
            dispose: () => {}
        };
    }

    async resolveCustomEditor(document, webviewPanel) {
        webviewPanel.webview.options = {
            enableScripts: true,
            localResourceRoots: [
                vscode.Uri.file(this.context.extensionPath),
                vscode.Uri.file(vscode.workspace.rootPath || ''),
                vscode.Uri.file(path.dirname(document.uri.fsPath))
            ]
        };

        const filePath = document.uri.fsPath;
        const ext = path.extname(filePath).toLowerCase();
        const baseName = path.basename(filePath);
        const dirName = path.dirname(filePath);

        // Fetch user configuration settings
        const config = vscode.workspace.getConfiguration('pokeAssetStudio');
        const settings = {
            defaultZoom: config.get('defaultZoom', 8),
            defaultGrid: config.get('defaultGrid', 'none'),
            defaultBackground: config.get('defaultBackground', 'checkerboard-dark'),
            animationFps: config.get('animationFps', 15),
            strictBgr555: config.get('strictBgr555', true),
            slotZeroStrict: config.get('slotZeroStrict', true),
            autoSavePalWithPng: config.get('autoSavePalWithPng', true)
        };

        webviewPanel.webview.html = this.getHtmlForWebview(webviewPanel.webview);

        // Find potential sibling palette
        let defaultPalette = null;
        const candidatePals = [
            path.join(dirName, 'normal.pal'),
            path.join(dirName, `${path.basename(filePath, ext)}.pal`),
            path.join(dirName, 'palette.pal')
        ];
        for (const p of candidatePals) {
            if (fs.existsSync(p)) {
                try {
                    const palContent = fs.readFileSync(p, 'utf-8');
                    defaultPalette = gba.parseJascPal(palContent);
                    break;
                } catch (e) {}
            }
        }

        webviewPanel.webview.onDidReceiveMessage(async (msg) => {
            if (msg.type === 'ready') {
                try {
                    if (ext === '.png') {
                        const buffer = fs.readFileSync(filePath);
                        const base64 = buffer.toString('base64');
                        const dataUrl = `data:image/png;base64,${base64}`;
                        webviewPanel.webview.postMessage({
                            type: 'load_image',
                            fileName: baseName,
                            filePath: filePath,
                            dataUrl: dataUrl,
                            palette: defaultPalette,
                            settings: settings
                        });
                    } else if (ext === '.pal') {
                        const content = fs.readFileSync(filePath, 'utf-8');
                        const palette = gba.parseJascPal(content);
                        webviewPanel.webview.postMessage({
                            type: 'load_palette',
                            fileName: baseName,
                            filePath: filePath,
                            palette: palette,
                            settings: settings
                        });
                    } else if (ext === '.gbapal') {
                        const buffer = fs.readFileSync(filePath);
                        const palette = gba.parseGbapal(buffer);
                        webviewPanel.webview.postMessage({
                            type: 'load_palette',
                            fileName: baseName,
                            filePath: filePath,
                            palette: palette,
                            settings: settings
                        });
                    } else if (ext === '.act') {
                        const buffer = fs.readFileSync(filePath);
                        const palette = gba.parseAct(buffer);
                        webviewPanel.webview.postMessage({
                            type: 'load_palette',
                            fileName: baseName,
                            filePath: filePath,
                            palette: palette,
                            settings: settings
                        });
                    } else if (ext === '.4bpp' || ext === '.8bpp') {
                        const buffer = fs.readFileSync(filePath);
                        const tiles = Math.floor(buffer.length / (ext === '.4bpp' ? 32 : 64));
                        const tilesPerRow = Math.min(16, Math.max(1, Math.round(Math.sqrt(tiles))));
                        const tilesPerCol = Math.ceil(tiles / tilesPerRow);
                        const palToUse = defaultPalette || [];
                        const decoded = ext === '.4bpp'
                            ? gba.decode4bpp(buffer, tilesPerRow, tilesPerCol, palToUse)
                            : gba.decode8bpp(buffer, tilesPerRow, tilesPerCol, palToUse);

                        webviewPanel.webview.postMessage({
                            type: 'load_raw_tiles',
                            fileName: baseName,
                            filePath: filePath,
                            width: decoded.width,
                            height: decoded.height,
                            indices: Array.from(decoded.indices),
                            palette: palToUse,
                            is4bpp: ext === '.4bpp',
                            is8bpp: ext === '.8bpp',
                            settings: settings
                        });
                    }
                } catch (err) {
                    vscode.window.showErrorMessage(`Error reading asset ${baseName}: ${err.message}`);
                }
            } else if (msg.type === 'save_file') {
                try {
                    if (ext === '.png' && msg.dataUrl) {
                        const base64Data = msg.dataUrl.replace(/^data:image\/png;base64,/, '');
                        fs.writeFileSync(filePath, Buffer.from(base64Data, 'base64'));

                        // If autoSavePalWithPng is true, write matching .pal too
                        if (settings.autoSavePalWithPng && candidatePals[0] && msg.palette) {
                            const jascText = gba.writeJascPal(msg.palette);
                            fs.writeFileSync(candidatePals[0], jascText, 'utf-8');
                        }

                        vscode.window.showInformationMessage(`Successfully saved ${baseName}`);
                    } else if (ext === '.pal' && msg.palette) {
                        const jascText = gba.writeJascPal(msg.palette);
                        fs.writeFileSync(filePath, jascText, 'utf-8');
                        vscode.window.showInformationMessage(`Successfully saved palette ${baseName}`);
                    } else if (ext === '.gbapal' && msg.palette) {
                        const gbapalBytes = gba.writeGbapal(msg.palette);
                        fs.writeFileSync(filePath, gbapalBytes);
                        vscode.window.showInformationMessage(`Successfully saved GBA binary palette ${baseName}`);
                    } else if (ext === '.act' && msg.palette) {
                        const actBytes = gba.writeAct(msg.palette);
                        fs.writeFileSync(filePath, actBytes);
                        vscode.window.showInformationMessage(`Successfully saved Photoshop ACT palette ${baseName}`);
                    } else if (ext === '.4bpp' && msg.indices) {
                        const rawBytes = gba.encode4bpp(msg.indices, msg.width, msg.height);
                        fs.writeFileSync(filePath, rawBytes);
                        vscode.window.showInformationMessage(`Successfully encoded and saved 4bpp binary tiles ${baseName}`);
                    } else if (ext === '.8bpp' && msg.indices) {
                        const rawBytes = gba.encode8bpp(msg.indices, msg.width, msg.height);
                        fs.writeFileSync(filePath, rawBytes);
                        vscode.window.showInformationMessage(`Successfully encoded and saved 8bpp binary tiles ${baseName}`);
                    }
                } catch (err) {
                    vscode.window.showErrorMessage(`Failed to save ${baseName}: ${err.message}`);
                }
            } else if (msg.type === 'copy_c_array') {
                const varName = path.basename(filePath, ext);
                const text = gba.exportCArray(msg.palette, varName);
                await vscode.env.clipboard.writeText(text);
                vscode.window.showInformationMessage(`C Array for ${varName} copied to clipboard!`);
            } else if (msg.type === 'export_palette_jasc') {
                const text = gba.writeJascPal(msg.palette);
                const doc = await vscode.workspace.openTextDocument({ content: text, language: 'plaintext' });
                vscode.window.showTextDocument(doc);
            } else if (msg.type === 'export_palette_c') {
                const varName = path.basename(filePath, ext);
                const text = gba.exportCArray(msg.palette, varName);
                const doc = await vscode.workspace.openTextDocument({ content: text, language: 'c' });
                vscode.window.showTextDocument(doc);
            } else if (msg.type === 'export_palette_gpl') {
                const varName = path.basename(filePath, ext);
                const text = gba.writeGpl(msg.palette, varName);
                const doc = await vscode.workspace.openTextDocument({ content: text, language: 'plaintext' });
                vscode.window.showTextDocument(doc);
            } else if (msg.type === 'notify') {
                vscode.window.showInformationMessage(msg.message);
            }
        });
    }

    getHtmlForWebview(webview) {
        const scriptUri = webview.asWebviewUri(vscode.Uri.file(
            path.join(this.context.extensionPath, 'media', 'editor.js')
        ));
        const styleUri = webview.asWebviewUri(vscode.Uri.file(
            path.join(this.context.extensionPath, 'media', 'editor.css')
        ));

        return `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="${styleUri}">
    <title>Pokémon GBA Asset Studio</title>
</head>
<body>
    <!-- Top Toolbar -->
    <div class="toolbar">
        <div class="tool-group">
            <span class="badge" id="fileNameBadge">file.png</span>
            <span class="badge success" id="dimensionsBadge">64x64</span>
            <span class="badge" id="depthBadge">16 Colors (4bpp)</span>
            <span class="badge" id="vramTilesBadge">64 Tiles</span>
        </div>

        <div class="tool-group">
            <button class="tool-btn active" data-tool="pencil" title="Pencil (B)">✏️ Pencil</button>
            <button class="tool-btn" data-tool="eraser" title="Eraser / Transparent (E)">🧹 Eraser</button>
            <button class="tool-btn" data-tool="line" title="Straight Line (L)">📏 Line</button>
            <button class="tool-btn" data-tool="rect" title="Rectangle (U)">⬜ Box</button>
            <button class="tool-btn" data-tool="circle" title="Circle (C)">⚪ Circle</button>
            <button class="tool-btn" data-tool="fill" title="Bucket Fill (G)">🪣 Fill</button>
            <button class="tool-btn" data-tool="replace" title="Color Replace (R)">🔄 Replace</button>
            <button class="tool-btn" data-tool="eyedropper" title="Eyedropper / Pick Color (I)">💧 Pick</button>
            <button class="tool-btn" data-tool="pan" title="Pan Canvas (Space / H)">🖐️ Pan</button>
        </div>

        <div class="tool-group">
            <label style="color: var(--text-muted); font-size: 10px;">Brush:</label>
            <button class="tool-btn active" id="btnBrush1">1px</button>
            <button class="tool-btn" id="btnBrush2">2px</button>
            <button class="tool-btn" id="btnBrush4">4px</button>
        </div>

        <div class="tool-group">
            <button class="tool-btn" id="btnFlipH" title="Flip Horizontal (Mirror X)">↔️ Flip H</button>
            <button class="tool-btn" id="btnFlipV" title="Flip Vertical (Mirror Y)">↕️ Flip V</button>
            <button class="tool-btn" id="btnRotate" title="Rotate 90° Clockwise">↷ Rotate</button>
        </div>

        <div class="tool-group">
            <button class="tool-btn" id="btnZoomOut" title="Zoom Out">-</button>
            <span id="zoomLevelText" style="min-width: 42px; text-align: center; font-family: monospace;">800%</span>
            <button class="tool-btn" id="btnZoomIn" title="Zoom In">+</button>
            <button class="tool-btn" id="btnZoomReset" title="Reset Zoom">Reset</button>
        </div>

        <div class="tool-group">
            <button class="tool-btn" id="btnGridTile" title="Toggle 8x8 Tile Grid">8x8 Tile</button>
            <button class="tool-btn" id="btnGridMetatile" title="Toggle 16x16 Metatile Grid">16x16 Meta</button>
            <button class="tool-btn" id="btnGridFrame" title="Toggle 64x64 Frame Grid">64x64 Frame</button>
            <button class="tool-btn" id="btnOnionSkin" title="Toggle Onion Skinning for Animations">🧅 Onion</button>
        </div>

        <div class="tool-group">
            <label style="color: var(--text-muted); font-size: 10px;">BG:</label>
            <select id="bgSelect" style="background: var(--bg-primary); color: var(--text-primary); border: 1px solid var(--border-color); border-radius: 3px; padding: 2px 4px; font-size: 11px;">
                <option value="checkerboard-dark">Dark Checkers</option>
                <option value="checkerboard-light">Light Checkers</option>
                <option value="magenta">GBA Magenta</option>
                <option value="black">Black</option>
                <option value="white">White</option>
            </select>
        </div>

        <div class="tool-group" style="margin-left: auto;">
            <button class="tool-btn btn-save" id="btnSave" title="Save Asset (Ctrl+S)">💾 Save Asset</button>
        </div>
    </div>

    <!-- Main Container -->
    <div class="main-container">
        <!-- Center Viewport -->
        <div class="viewport bg-checkerboard-dark" id="viewport">
            <div class="canvas-wrapper" id="canvasWrapper">
                <canvas id="onionCanvas" width="64" height="64" style="position: absolute; top: 0; left: 0; pointer-events: none; opacity: 0.35; display: none;"></canvas>
                <canvas id="imageCanvas" width="64" height="64"></canvas>
                <canvas id="overlayCanvas" width="64" height="64"></canvas>
            </div>
            <div class="cursor-hud" id="cursorHud">
                <span>X: 0 Y: 0</span>
                <span>Slot: [0] (TRANS)</span>
                <span>HEX: #FF00FF</span>
                <span>BGR555: 0x7C1F</span>
            </div>
        </div>

        <!-- Right Side Inspector -->
        <div class="inspector">
            <!-- 1:1 Live Scale Preview -->
            <div class="panel-section">
                <div class="section-title">
                    <span>1:1 Actual GBA Scale Preview</span>
                    <span style="font-size: 9px; color: var(--text-muted);">Real-time</span>
                </div>
                <div class="actual-preview-container">
                    <canvas id="actualScaleCanvas" width="64" height="64" class="actual-scale-canvas"></canvas>
                </div>
            </div>

            <!-- 16-Color Palette Panel -->
            <div class="panel-section">
                <div class="section-title">
                    <span>GBA Palette (16 Colors)</span>
                    <span style="font-size: 9px; color: var(--text-muted);">Double-click to edit</span>
                </div>
                <div class="palette-grid" id="paletteGrid"></div>
                <div class="btn-row">
                    <button class="btn-action accent" id="btnFixSlot0" title="Ensure Slot 0 is strictly transparent in PPU">Fix Slot 0</button>
                    <button class="btn-action" id="btnGenShiny" title="Generate Shiny Variant by Hue Shift">Gen Shiny</button>
                    <button class="btn-action" id="btnQuantize" title="Quantize Image to 16 Colors (BGR555)">Quantize 16</button>
                </div>
                <div class="btn-row">
                    <button class="btn-action" id="btnAdjBrightContrast">Tweak Colors</button>
                    <button class="btn-action" id="btnSwapColors">Swap Slots</button>
                </div>
                <div class="btn-row">
                    <button class="btn-action" id="btnCopyCArray" title="Copy C Array directly to Clipboard">Copy C Code</button>
                    <button class="btn-action" id="btnExportPal">Export .pal</button>
                    <button class="btn-action" id="btnExportGbapal">Export .gbapal</button>
                    <button class="btn-action" id="btnExportGpl">Export .gpl</button>
                </div>
            </div>

            <!-- Animation Preview Panel -->
            <div class="panel-section">
                <div class="section-title">
                    <span>Sprite Animation Player</span>
                    <span id="frameCounter" style="font-family: monospace;">1 / 1</span>
                </div>
                <div class="anim-preview-box">
                    <canvas id="animCanvas" width="64" height="64"></canvas>
                </div>
                <div class="anim-controls">
                    <button class="tool-btn" id="btnPrevFrame">⏮</button>
                    <button class="tool-btn" id="btnPlayAnim">▶ Play</button>
                    <button class="tool-btn" id="btnNextFrame">⏭</button>
                </div>
                <div class="direction-controls" id="directionControls" style="display: none; justify-content: center; gap: 4px; margin-top: 6px;">
                    <button class="tool-btn active" data-dir="down">⬇️ Down</button>
                    <button class="tool-btn" data-dir="up">⬆️ Up</button>
                    <button class="tool-btn" data-dir="left">⬅️ Left</button>
                    <button class="tool-btn" data-dir="right">➡️ Right</button>
                </div>
                <div style="display: flex; align-items: center; gap: 8px; margin-top: 8px;">
                    <label style="font-size: 10px; color: var(--text-muted);">Speed:</label>
                    <input type="range" id="fpsSlider" min="1" max="60" value="15" style="flex: 1;">
                    <span id="fpsValueText" style="font-size: 10px; font-family: monospace; width: 40px;">15 FPS</span>
                </div>
            </div>

            <!-- Engine & Hardware Compliance Auditor -->
            <div class="panel-section">
                <div class="section-title">
                    <span>Hardware Compliance Audit</span>
                </div>
                <div class="audit-list" id="auditList">
                    <div class="audit-item ok">✅ Validating GBA boundaries...</div>
                </div>
            </div>
        </div>
    </div>

    <!-- Color Picker Modal -->
    <div class="modal-overlay" id="colorPickerModal">
        <div class="modal-card">
            <h3 style="margin-bottom: 12px; font-size: 13px;">GBA BGR555 Color Editor</h3>
            <div style="display: flex; gap: 12px; align-items: center; margin-bottom: 14px;">
                <div id="previewColorBox" style="width: 48px; height: 48px; border-radius: 4px; border: 1px solid var(--border-color);"></div>
                <div>
                    <div id="previewBgrText" style="font-family: monospace; font-size: 12px; font-weight: bold;">#000000 | 0x0000</div>
                    <div style="font-size: 10px; color: var(--text-muted); margin-top: 2px;">Hardware 15-bit Snap (0-31)</div>
                </div>
            </div>

            <div class="color-slider-row">
                <label style="color: #ff6b6b;">R</label>
                <input type="range" id="pickerRed" min="0" max="31" step="1">
                <span id="valRed">0</span>
            </div>
            <div class="color-slider-row">
                <label style="color: #51cf66;">G</label>
                <input type="range" id="pickerGreen" min="0" max="31" step="1">
                <span id="valGreen">0</span>
            </div>
            <div class="color-slider-row">
                <label style="color: #339af0;">B</label>
                <input type="range" id="pickerBlue" min="0" max="31" step="1">
                <span id="valBlue">0</span>
            </div>

            <div style="display: flex; gap: 8px; margin-top: 16px;">
                <button class="btn-action" id="btnCancelColor">Cancel</button>
                <button class="btn-action accent" id="btnApplyColor">Apply Color</button>
            </div>
        </div>
    </div>

    <!-- Brightness & Contrast Modal -->
    <div class="modal-overlay" id="adjustColorModal">
        <div class="modal-card">
            <h3 style="margin-bottom: 12px; font-size: 13px;">Adjust Brightness & Contrast</h3>
            <div class="color-slider-row">
                <label style="width: 70px;">Brightness</label>
                <input type="range" id="sliderBrightness" min="-60" max="60" value="0">
                <span id="textBrightness">0</span>
            </div>
            <div class="color-slider-row">
                <label style="width: 70px;">Contrast</label>
                <input type="range" id="sliderContrast" min="-60" max="60" value="0">
                <span id="textContrast">0</span>
            </div>
            <div style="display: flex; gap: 8px; margin-top: 16px;">
                <button class="btn-action" id="btnCancelAdjust">Cancel</button>
                <button class="btn-action accent" id="btnApplyAdjust">Apply Adjustments</button>
            </div>
        </div>
    </div>

    <!-- Swap Colors Modal -->
    <div class="modal-overlay" id="swapColorModal">
        <div class="modal-card">
            <h3 style="margin-bottom: 12px; font-size: 13px;">Swap Palette Slots</h3>
            <div style="display: flex; align-items: center; justify-content: space-around; margin: 15px 0;">
                <div>
                    <label style="display: block; font-size: 10px; margin-bottom: 4px;">Slot A</label>
                    <select id="swapSlotA" style="background: var(--bg-primary); color: #eee; padding: 4px; border: 1px solid var(--border-color);"></select>
                </div>
                <span style="font-size: 16px;">⇄</span>
                <div>
                    <label style="display: block; font-size: 10px; margin-bottom: 4px;">Slot B</label>
                    <select id="swapSlotB" style="background: var(--bg-primary); color: #eee; padding: 4px; border: 1px solid var(--border-color);"></select>
                </div>
            </div>
            <div style="display: flex; gap: 8px; margin-top: 16px;">
                <button class="btn-action" id="btnCancelSwap">Cancel</button>
                <button class="btn-action accent" id="btnApplySwap">Swap Slots</button>
            </div>
        </div>
    </div>

    <script src="${scriptUri}"></script>
</body>
</html>`;
    }
}

module.exports = {
    PokeAssetEditorProvider
};
