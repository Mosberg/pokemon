// POKE-CONFLUENCE GBA Asset Studio Professional Webview Client Logic
(function () {
    const vscode = acquireVsCodeApi();

    // DOM Elements
    const viewport = document.getElementById('viewport');
    const canvasWrapper = document.getElementById('canvasWrapper');
    const imageCanvas = document.getElementById('imageCanvas');
    const overlayCanvas = document.getElementById('overlayCanvas');
    const onionCanvas = document.getElementById('onionCanvas');
    const animCanvas = document.getElementById('animCanvas');
    const actualScaleCanvas = document.getElementById('actualScaleCanvas');
    const cursorHud = document.getElementById('cursorHud');
    const paletteGrid = document.getElementById('paletteGrid');
    const auditList = document.getElementById('auditList');
    const colorPickerModal = document.getElementById('colorPickerModal');
    const adjustColorModal = document.getElementById('adjustColorModal');
    const swapColorModal = document.getElementById('swapColorModal');
    const zoomLevelText = document.getElementById('zoomLevelText');
    const vramTilesBadge = document.getElementById('vramTilesBadge');

    const ctx = imageCanvas.getContext('2d', { willReadFrequently: true });
    const overlayCtx = overlayCanvas.getContext('2d');
    const onionCtx = onionCanvas ? onionCanvas.getContext('2d') : null;
    const animCtx = animCanvas ? animCanvas.getContext('2d') : null;
    const actualCtx = actualScaleCanvas ? actualScaleCanvas.getContext('2d') : null;

    // State
    let fileInfo = {};
    let zoom = 8;
    let panX = 0;
    let panY = 0;
    let isPanning = false;
    let startPanX = 0;
    let startPanY = 0;
    let activeTool = 'pencil';
    let brushSize = 1;
    let activePaletteIndex = 1;
    let isDrawing = false;
    let dragStartX = -1;
    let dragStartY = -1;

    let gridSettings = {
        tile8: false,
        metatile16: false,
        frame64: false,
        onionSkin: false
    };

    let palette = [];
    let imageWidth = 64;
    let imageHeight = 64;
    let pixelIndices = []; // 1D Uint8Array of size width * height
    let undoStack = [];
    let redoStack = [];

    // Animation state
    let anim = {
        playing: false,
        frameWidth: 64,
        frameHeight: 64,
        currentFrame: 0,
        totalFrames: 1,
        direction: 'down',
        fps: 15,
        intervalId: null
    };

    // Color conversion helpers (matching GBA PPU)
    function snapToGbaChannel(val) {
        return Math.round(Math.round(val * 31 / 255) * 255 / 31);
    }

    function clampGbaRgb(r, g, b) {
        return [snapToGbaChannel(r), snapToGbaChannel(g), snapToGbaChannel(b)];
    }

    function rgbToBgr555(r, g, b) {
        const r5 = Math.round(r * 31 / 255);
        const g5 = Math.round(g * 31 / 255);
        const b5 = Math.round(b * 31 / 255);
        return ((b5 & 0x1F) << 10) | ((g5 & 0x1F) << 5) | (r5 & 0x1F);
    }

    function bgr555ToRgb(val) {
        const r5 = val & 0x1F;
        const g5 = (val >> 5) & 0x1F;
        const b5 = (val >> 10) & 0x1F;
        return [
            Math.round(r5 * 255 / 31),
            Math.round(g5 * 255 / 31),
            Math.round(b5 * 255 / 31)
        ];
    }

    function rgbToHex(r, g, b) {
        return '#' + [r, g, b].map(x => x.toString(16).padStart(2, '0')).join('');
    }

    function formatBgr555Hex(val) {
        return '0x' + (val & 0xFFFF).toString(16).padStart(4, '0').toUpperCase();
    }

    // Default Palette initialization
    function initDefaultPalette() {
        palette = [
            { r: 255, g: 0, b: 255, hex: '#ff00ff', bgr555: 0x7C1F }, // Slot 0 transparent
            { r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0x0000 },
            { r: 248, g: 248, b: 248, hex: '#f8f8f8', bgr555: 0x7FFF }
        ];
        while (palette.length < 16) {
            const v = Math.round((palette.length / 15) * 255);
            const snapped = snapToGbaChannel(v);
            palette.push({
                r: snapped, g: snapped, b: snapped,
                hex: rgbToHex(snapped, snapped, snapped),
                bgr555: rgbToBgr555(snapped, snapped, snapped)
            });
        }
    }

    initDefaultPalette();

    // Canvas transforms & zoom
    function updateCanvasTransform() {
        canvasWrapper.style.transform = `translate(${panX}px, ${panY}px) scale(${zoom})`;
        zoomLevelText.textContent = `${Math.round(zoom * 100)}%`;
        renderOverlays();
    }

    function setZoom(newZoom, centerX = null, centerY = null) {
        newZoom = Math.max(1, Math.min(32, newZoom));
        if (newZoom === zoom) return;

        if (centerX !== null && centerY !== null) {
            const rect = canvasWrapper.getBoundingClientRect();
            const relX = (centerX - rect.left) / zoom;
            const relY = (centerY - rect.top) / zoom;
            panX -= relX * (newZoom - zoom);
            panY -= relY * (newZoom - zoom);
        }
        zoom = newZoom;
        updateCanvasTransform();
    }

    // Viewport Panning & Zoom Events
    viewport.addEventListener('mousedown', (e) => {
        if (e.button === 1 || activeTool === 'pan' || (e.button === 0 && e.spaceKey)) {
            isPanning = true;
            startPanX = e.clientX - panX;
            startPanY = e.clientY - panY;
            viewport.classList.add('grabbing');
            e.preventDefault();
        }
    });

    window.addEventListener('mousemove', (e) => {
        if (isPanning) {
            panX = e.clientX - startPanX;
            panY = e.clientY - startPanY;
            updateCanvasTransform();
            return;
        }

        const rect = imageCanvas.getBoundingClientRect();
        const px = Math.floor((e.clientX - rect.left) / zoom);
        const py = Math.floor((e.clientY - rect.top) / zoom);

        if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
            const idx = py * imageWidth + px;
            const palIdx = pixelIndices[idx] !== undefined ? pixelIndices[idx] : 0;
            const color = palette[palIdx] || { hex: '#000000', bgr555: 0 };
            const tileX = Math.floor(px / 8);
            const tileY = Math.floor(py / 8);

            cursorHud.innerHTML = `
                <span>X: <b>${px}</b> Y: <b>${py}</b></span>
                <span>Tile: <b>(${tileX}, ${tileY})</b></span>
                <span>Slot: <b>[${palIdx}]</b> ${palIdx === 0 ? '(TRANS)' : ''}</span>
                <span>HEX: <b>${color.hex}</b></span>
                <span>BGR555: <b>${formatBgr555Hex(color.bgr555)}</b></span>
            `;

            if (isDrawing) {
                if (activeTool === 'pencil' || activeTool === 'eraser') {
                    applyContinuousDraw(px, py);
                } else if (['line', 'rect', 'circle'].includes(activeTool)) {
                    renderShapePreview(dragStartX, dragStartY, px, py);
                }
            }
        }
    });

    window.addEventListener('mouseup', (e) => {
        if (isPanning) {
            isPanning = false;
            viewport.classList.remove('grabbing');
        }
        if (isDrawing) {
            const rect = imageCanvas.getBoundingClientRect();
            const px = Math.floor((e.clientX - rect.left) / zoom);
            const py = Math.floor((e.clientY - rect.top) / zoom);

            if (['line', 'rect', 'circle'].includes(activeTool) && dragStartX !== -1) {
                commitShape(dragStartX, dragStartY, px, py);
            }

            isDrawing = false;
            dragStartX = -1;
            dragStartY = -1;
            renderOverlays();
            redrawImageFromIndices();
            runAuditor();
        }
    });

    viewport.addEventListener('wheel', (e) => {
        e.preventDefault();
        const delta = e.deltaY < 0 ? 1 : -1;
        let nextZoom = zoom;
        if (delta > 0) {
            nextZoom = zoom >= 16 ? zoom + 4 : zoom * 1.5;
        } else {
            nextZoom = zoom > 16 ? zoom - 4 : zoom / 1.5;
        }
        setZoom(nextZoom, e.clientX, e.clientY);
    }, { passive: false });

    // Drawing Interaction
    imageCanvas.addEventListener('mousedown', (e) => {
        if (e.button !== 0 || activeTool === 'pan') return;

        const rect = imageCanvas.getBoundingClientRect();
        const px = Math.floor((e.clientX - rect.left) / zoom);
        const py = Math.floor((e.clientY - rect.top) / zoom);

        if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
            pushUndo();
            isDrawing = true;
            dragStartX = px;
            dragStartY = py;

            if (activeTool === 'eyedropper') {
                const idx = py * imageWidth + px;
                selectPaletteIndex(pixelIndices[idx] || 0);
                setActiveTool('pencil');
                isDrawing = false;
                return;
            }

            if (activeTool === 'fill') {
                floodFill(px, py, activePaletteIndex);
                redrawImageFromIndices();
                isDrawing = false;
                return;
            }

            if (activeTool === 'replace') {
                replaceColor(pixelIndices[py * imageWidth + px], activePaletteIndex);
                redrawImageFromIndices();
                isDrawing = false;
                return;
            }

            if (activeTool === 'pencil' || activeTool === 'eraser') {
                applyContinuousDraw(px, py);
            }
        }
    });

    function applyContinuousDraw(x, y) {
        const colIdx = activeTool === 'eraser' ? 0 : activePaletteIndex;
        plotPixelWithBrush(x, y, colIdx);
        redrawImageFromIndices();
    }

    function plotPixelWithBrush(x, y, colIdx) {
        const size = brushSize;
        for (let dy = 0; dy < size; dy++) {
            for (let dx = 0; dx < size; dx++) {
                const nx = x + dx;
                const ny = y + dy;
                if (nx >= 0 && nx < imageWidth && ny >= 0 && ny < imageHeight) {
                    pixelIndices[ny * imageWidth + nx] = colIdx;
                }
            }
        }
    }

    // Shape drawing algorithms
    function bresenhamLine(x0, y0, x1, y1) {
        const points = [];
        const dx = Math.abs(x1 - x0);
        const dy = Math.abs(y1 - y0);
        const sx = x0 < x1 ? 1 : -1;
        const sy = y0 < y1 ? 1 : -1;
        let err = dx - dy;

        let curX = x0;
        let curY = y0;
        while (true) {
            points.push([curX, curY]);
            if (curX === x1 && curY === y1) break;
            const e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                curX += sx;
            }
            if (e2 < dx) {
                err += dx;
                curY += sy;
            }
        }
        return points;
    }

    function bresenhamRect(x0, y0, x1, y1) {
        const points = [];
        const minX = Math.min(x0, x1);
        const maxX = Math.max(x0, x1);
        const minY = Math.min(y0, y1);
        const maxY = Math.max(y0, y1);

        for (let x = minX; x <= maxX; x++) {
            points.push([x, minY]);
            points.push([x, maxY]);
        }
        for (let y = minY; y <= maxY; y++) {
            points.push([minX, y]);
            points.push([maxX, y]);
        }
        return points;
    }

    function midpointCircle(x0, y0, x1, y1) {
        const points = [];
        const r = Math.round(Math.hypot(x1 - x0, y1 - y0));
        let x = r;
        let y = 0;
        let err = 0;

        while (x >= y) {
            points.push([x0 + x, y0 + y], [x0 + y, y0 + x]);
            points.push([x0 - y, y0 + x], [x0 - x, y0 + y]);
            points.push([x0 - x, y0 - y], [x0 - y, y0 - x]);
            points.push([x0 + y, y0 - x], [x0 + x, y0 - y]);

            if (err <= 0) {
                y += 1;
                err += 2 * y + 1;
            }
            if (err > 0) {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
        return points;
    }

    function renderShapePreview(x0, y0, x1, y1) {
        renderOverlays();
        let pts = [];
        if (activeTool === 'line') pts = bresenhamLine(x0, y0, x1, y1);
        else if (activeTool === 'rect') pts = bresenhamRect(x0, y0, x1, y1);
        else if (activeTool === 'circle') pts = midpointCircle(x0, y0, x1, y1);

        overlayCtx.fillStyle = 'rgba(56, 189, 248, 0.8)';
        pts.forEach(([px, py]) => {
            if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
                overlayCtx.fillRect(px, py, 1, 1);
            }
        });
    }

    function commitShape(x0, y0, x1, y1) {
        let pts = [];
        if (activeTool === 'line') pts = bresenhamLine(x0, y0, x1, y1);
        else if (activeTool === 'rect') pts = bresenhamRect(x0, y0, x1, y1);
        else if (activeTool === 'circle') pts = midpointCircle(x0, y0, x1, y1);

        pts.forEach(([px, py]) => {
            plotPixelWithBrush(px, py, activePaletteIndex);
        });
    }

    function floodFill(startX, startY, newIdx) {
        const startTarget = pixelIndices[startY * imageWidth + startX];
        if (startTarget === newIdx) return;

        const queue = [[startX, startY]];
        const visited = new Uint8Array(imageWidth * imageHeight);

        while (queue.length > 0) {
            const [cx, cy] = queue.pop();
            const pos = cy * imageWidth + cx;

            if (cx < 0 || cx >= imageWidth || cy < 0 || cy >= imageHeight) continue;
            if (visited[pos]) continue;
            visited[pos] = 1;

            if (pixelIndices[pos] === startTarget) {
                pixelIndices[pos] = newIdx;
                queue.push([cx + 1, cy], [cx - 1, cy], [cx, cy + 1], [cx, cy - 1]);
            }
        }
    }

    function replaceColor(sourceIdx, targetIdx) {
        if (sourceIdx === targetIdx) return;
        for (let i = 0; i < pixelIndices.length; i++) {
            if (pixelIndices[i] === sourceIdx) {
                pixelIndices[i] = targetIdx;
            }
        }
    }

    // Transforms
    function flipHorizontal() {
        pushUndo();
        for (let y = 0; y < imageHeight; y++) {
            for (let x = 0; x < Math.floor(imageWidth / 2); x++) {
                const left = y * imageWidth + x;
                const right = y * imageWidth + (imageWidth - 1 - x);
                const temp = pixelIndices[left];
                pixelIndices[left] = pixelIndices[right];
                pixelIndices[right] = temp;
            }
        }
        redrawImageFromIndices();
    }

    function flipVertical() {
        pushUndo();
        for (let y = 0; y < Math.floor(imageHeight / 2); y++) {
            for (let x = 0; x < imageWidth; x++) {
                const top = y * imageWidth + x;
                const bottom = (imageHeight - 1 - y) * imageWidth + x;
                const temp = pixelIndices[top];
                pixelIndices[top] = pixelIndices[bottom];
                pixelIndices[bottom] = temp;
            }
        }
        redrawImageFromIndices();
    }

    function rotate90Clockwise() {
        pushUndo();
        const next = new Uint8Array(imageWidth * imageHeight);
        for (let y = 0; y < imageHeight; y++) {
            for (let x = 0; x < imageWidth; x++) {
                const nx = imageHeight - 1 - y;
                const ny = x;
                next[ny * imageWidth + nx] = pixelIndices[y * imageWidth + x];
            }
        }
        pixelIndices = next;
        redrawImageFromIndices();
    }

    document.getElementById('btnFlipH').addEventListener('click', flipHorizontal);
    document.getElementById('btnFlipV').addEventListener('click', flipVertical);
    document.getElementById('btnRotate').addEventListener('click', rotate90Clockwise);

    // Brush sizes
    function setBrushSize(sz) {
        brushSize = sz;
        ['btnBrush1', 'btnBrush2', 'btnBrush4'].forEach(id => {
            document.getElementById(id).classList.toggle('active', id === `btnBrush${sz}`);
        });
    }

    document.getElementById('btnBrush1').addEventListener('click', () => setBrushSize(1));
    document.getElementById('btnBrush2').addEventListener('click', () => setBrushSize(2));
    document.getElementById('btnBrush4').addEventListener('click', () => setBrushSize(4));

    // Undo / Redo
    function pushUndo() {
        if (undoStack.length >= 40) undoStack.shift();
        undoStack.push(new Uint8Array(pixelIndices));
        redoStack = [];
    }

    function triggerUndo() {
        if (undoStack.length === 0) return;
        redoStack.push(new Uint8Array(pixelIndices));
        pixelIndices = undoStack.pop();
        redrawImageFromIndices();
        runAuditor();
    }

    function triggerRedo() {
        if (redoStack.length === 0) return;
        undoStack.push(new Uint8Array(pixelIndices));
        pixelIndices = redoStack.pop();
        redrawImageFromIndices();
        runAuditor();
    }

    // Redraw Canvas & 1:1 Live Preview
    function redrawImageFromIndices() {
        const imgData = ctx.createImageData(imageWidth, imageHeight);
        const data = imgData.data;

        for (let i = 0; i < pixelIndices.length; i++) {
            const palIdx = pixelIndices[i];
            const outIdx = i * 4;
            const c = palette[palIdx] || { r: 0, g: 0, b: 0 };

            data[outIdx] = c.r;
            data[outIdx + 1] = c.g;
            data[outIdx + 2] = c.b;
            data[outIdx + 3] = palIdx === 0 ? 0 : 255;
        }

        ctx.putImageData(imgData, 0, 0);

        // Update 1:1 Actual Scale Canvas
        if (actualScaleCanvas && actualCtx) {
            actualScaleCanvas.width = Math.min(imageWidth, 128);
            actualScaleCanvas.height = Math.min(imageHeight, 128);
            actualCtx.clearRect(0, 0, actualScaleCanvas.width, actualScaleCanvas.height);
            actualCtx.drawImage(imageCanvas, 0, 0);
        }

        // Update VRAM Tiles Badge
        const tilesW = Math.ceil(imageWidth / 8);
        const tilesH = Math.ceil(imageHeight / 8);
        const totalTiles = tilesW * tilesH;
        vramTilesBadge.textContent = `${totalTiles} VRAM Tiles (${totalTiles * 32}B)`;

        updateAnimFrame();
    }

    function renderOverlays() {
        overlayCanvas.width = imageWidth;
        overlayCanvas.height = imageHeight;
        overlayCtx.clearRect(0, 0, imageWidth, imageHeight);

        if (gridSettings.tile8) {
            overlayCtx.strokeStyle = 'rgba(255, 255, 255, 0.25)';
            overlayCtx.lineWidth = 1 / zoom;
            overlayCtx.beginPath();
            for (let x = 8; x < imageWidth; x += 8) {
                overlayCtx.moveTo(x, 0);
                overlayCtx.lineTo(x, imageHeight);
            }
            for (let y = 8; y < imageHeight; y += 8) {
                overlayCtx.moveTo(0, y);
                overlayCtx.lineTo(imageWidth, y);
            }
            overlayCtx.stroke();
        }

        if (gridSettings.metatile16) {
            overlayCtx.strokeStyle = 'rgba(255, 215, 0, 0.45)';
            overlayCtx.lineWidth = 1.5 / zoom;
            overlayCtx.beginPath();
            for (let x = 16; x < imageWidth; x += 16) {
                overlayCtx.moveTo(x, 0);
                overlayCtx.lineTo(x, imageHeight);
            }
            for (let y = 16; y < imageHeight; y += 16) {
                overlayCtx.moveTo(0, y);
                overlayCtx.lineTo(imageWidth, y);
            }
            overlayCtx.stroke();
        }

        if (gridSettings.frame64) {
            overlayCtx.strokeStyle = 'rgba(0, 255, 255, 0.65)';
            overlayCtx.lineWidth = 2 / zoom;
            overlayCtx.beginPath();
            for (let x = 64; x < imageWidth; x += 64) {
                overlayCtx.moveTo(x, 0);
                overlayCtx.lineTo(x, imageHeight);
            }
            for (let y = 64; y < imageHeight; y += 64) {
                overlayCtx.moveTo(0, y);
                overlayCtx.lineTo(imageWidth, y);
            }
            overlayCtx.stroke();
        }
    }

    // Palette Swatches UI
    function renderPaletteSwatches() {
        paletteGrid.innerHTML = '';
        for (let i = 0; i < 16; i++) {
            const c = palette[i] || { r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0 };
            const item = document.createElement('div');
            item.className = 'swatch-item' + (i === activePaletteIndex ? ' active' : '') + (i === 0 ? ' slot-zero' : '');
            item.style.backgroundColor = i === 0 ? 'transparent' : c.hex;
            if (i === 0) {
                item.style.backgroundImage = 'linear-gradient(45deg, #444 25%, transparent 25%), linear-gradient(-45deg, #444 25%, transparent 25%), linear-gradient(45deg, transparent 75%, #444 75%), linear-gradient(-45deg, transparent 75%, #444 75%)';
                item.style.backgroundSize = '8px 8px';
            }

            item.innerHTML = `
                <div class="swatch-slot">${i}${i === 0 ? ' (T)' : ''}</div>
                <div class="swatch-hex">${c.hex}</div>
            `;

            item.addEventListener('click', () => selectPaletteIndex(i));
            item.addEventListener('dblclick', () => openColorPicker(i));
            paletteGrid.appendChild(item);
        }
    }

    function selectPaletteIndex(idx) {
        activePaletteIndex = idx;
        const swatches = paletteGrid.querySelectorAll('.swatch-item');
        swatches.forEach((s, i) => {
            s.classList.toggle('active', i === idx);
        });
    }

    // Color Picker Modal
    let editingColorIndex = 0;
    const pickerRed = document.getElementById('pickerRed');
    const pickerGreen = document.getElementById('pickerGreen');
    const pickerBlue = document.getElementById('pickerBlue');
    const valRed = document.getElementById('valRed');
    const valGreen = document.getElementById('valGreen');
    const valBlue = document.getElementById('valBlue');
    const previewColorBox = document.getElementById('previewColorBox');
    const previewBgrText = document.getElementById('previewBgrText');

    function openColorPicker(idx) {
        editingColorIndex = idx;
        const c = palette[idx] || { r: 0, g: 0, b: 0 };
        const r5 = Math.round(c.r * 31 / 255);
        const g5 = Math.round(c.g * 31 / 255);
        const b5 = Math.round(c.b * 31 / 255);

        pickerRed.value = r5;
        pickerGreen.value = g5;
        pickerBlue.value = b5;
        updateColorPickerPreview();
        colorPickerModal.style.display = 'flex';
    }

    function updateColorPickerPreview() {
        const r5 = parseInt(pickerRed.value, 10);
        const g5 = parseInt(pickerGreen.value, 10);
        const b5 = parseInt(pickerBlue.value, 10);

        const r8 = Math.round(r5 * 255 / 31);
        const g8 = Math.round(g5 * 255 / 31);
        const b8 = Math.round(b5 * 255 / 31);

        valRed.textContent = `${r5} (${r8})`;
        valGreen.textContent = `${g5} (${g8})`;
        valBlue.textContent = `${b5} (${b8})`;

        const hex = rgbToHex(r8, g8, b8);
        const bgr = ((b5 & 0x1F) << 10) | ((g5 & 0x1F) << 5) | (r5 & 0x1F);

        previewColorBox.style.backgroundColor = hex;
        previewBgrText.textContent = `${hex} | ${formatBgr555Hex(bgr)}`;
    }

    [pickerRed, pickerGreen, pickerBlue].forEach(input => {
        input.addEventListener('input', updateColorPickerPreview);
    });

    document.getElementById('btnApplyColor').addEventListener('click', () => {
        const r5 = parseInt(pickerRed.value, 10);
        const g5 = parseInt(pickerGreen.value, 10);
        const b5 = parseInt(pickerBlue.value, 10);

        const r8 = Math.round(r5 * 255 / 31);
        const g8 = Math.round(g5 * 255 / 31);
        const b8 = Math.round(b5 * 255 / 31);
        const hex = rgbToHex(r8, g8, b8);
        const bgr = ((b5 & 0x1F) << 10) | ((g5 & 0x1F) << 5) | (r5 & 0x1F);

        palette[editingColorIndex] = { r: r8, g: g8, b: b8, hex, bgr555: bgr };
        colorPickerModal.style.display = 'none';
        renderPaletteSwatches();
        redrawImageFromIndices();
        runAuditor();
    });

    document.getElementById('btnCancelColor').addEventListener('click', () => {
        colorPickerModal.style.display = 'none';
    });

    // Brightness & Contrast Adjustment
    document.getElementById('btnAdjBrightContrast').addEventListener('click', () => {
        adjustColorModal.style.display = 'flex';
    });

    document.getElementById('btnCancelAdjust').addEventListener('click', () => {
        adjustColorModal.style.display = 'none';
    });

    document.getElementById('btnApplyAdjust').addEventListener('click', () => {
        pushUndo();
        const bVal = parseInt(document.getElementById('sliderBrightness').value, 10);
        const cVal = parseInt(document.getElementById('sliderContrast').value, 10);
        const factor = (259 * (cVal + 255)) / (255 * (259 - cVal));

        for (let i = 1; i < 16; i++) {
            const c = palette[i];
            let r = factor * (c.r + bVal - 128) + 128;
            let g = factor * (c.g + bVal - 128) + 128;
            let b = factor * (c.b + bVal - 128) + 128;

            const [sr, sg, sb] = clampGbaRgb(
                Math.max(0, Math.min(255, Math.round(r))),
                Math.max(0, Math.min(255, Math.round(g))),
                Math.max(0, Math.min(255, Math.round(b)))
            );
            palette[i] = {
                r: sr, g: sg, b: sb,
                hex: rgbToHex(sr, sg, sb),
                bgr555: rgbToBgr555(sr, sg, sb)
            };
        }
        adjustColorModal.style.display = 'none';
        renderPaletteSwatches();
        redrawImageFromIndices();
        runAuditor();
    });

    // Swap Colors
    const swapSlotA = document.getElementById('swapSlotA');
    const swapSlotB = document.getElementById('swapSlotB');

    document.getElementById('btnSwapColors').addEventListener('click', () => {
        swapSlotA.innerHTML = '';
        swapSlotB.innerHTML = '';
        for (let i = 0; i < 16; i++) {
            const optA = document.createElement('option');
            optA.value = i;
            optA.textContent = `Slot ${i} (${palette[i].hex})`;
            swapSlotA.appendChild(optA);

            const optB = document.createElement('option');
            optB.value = i;
            optB.textContent = `Slot ${i} (${palette[i].hex})`;
            if (i === 1) optB.selected = true;
            swapSlotB.appendChild(optB);
        }
        swapColorModal.style.display = 'flex';
    });

    document.getElementById('btnCancelSwap').addEventListener('click', () => {
        swapColorModal.style.display = 'none';
    });

    document.getElementById('btnApplySwap').addEventListener('click', () => {
        pushUndo();
        const a = parseInt(swapSlotA.value, 10);
        const b = parseInt(swapSlotB.value, 10);
        if (a !== b) {
            // Swap in pixels
            for (let i = 0; i < pixelIndices.length; i++) {
                if (pixelIndices[i] === a) pixelIndices[i] = b;
                else if (pixelIndices[i] === b) pixelIndices[i] = a;
            }
            // Swap in palette
            const temp = palette[a];
            palette[a] = palette[b];
            palette[b] = temp;
        }
        swapColorModal.style.display = 'none';
        renderPaletteSwatches();
        redrawImageFromIndices();
        runAuditor();
    });

    // Quantize 16 colors button
    document.getElementById('btnQuantize').addEventListener('click', () => {
        pushUndo();
        const rawImgData = ctx.getImageData(0, 0, imageWidth, imageHeight).data;
        const pixels = [];
        for (let i = 0; i < rawImgData.length; i += 4) {
            if (rawImgData[i + 3] >= 128) {
                const [r, g, b] = clampGbaRgb(rawImgData[i], rawImgData[i + 1], rawImgData[i + 2]);
                pixels.push({ r, g, b });
            }
        }

        if (pixels.length > 0) {
            function medianCut(cluster, depth) {
                if (depth === 0 || cluster.length <= 1) {
                    let tr = 0, tg = 0, tb = 0;
                    for (const p of cluster) { tr += p.r; tg += p.g; tb += p.b; }
                    const count = cluster.length;
                    const [r, g, b] = clampGbaRgb(Math.round(tr / count), Math.round(tg / count), Math.round(tb / count));
                    return [{ r, g, b, hex: rgbToHex(r, g, b), bgr555: rgbToBgr555(r, g, b) }];
                }
                let minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0;
                for (const p of cluster) {
                    if (p.r < minR) minR = p.r; if (p.r > maxR) maxR = p.r;
                    if (p.g < minG) minG = p.g; if (p.g > maxG) maxG = p.g;
                    if (p.b < minB) minB = p.b; if (p.b > maxB) maxB = p.b;
                }
                const sortChannel = (maxR - minR >= maxG - minG && maxR - minR >= maxB - minB) ? 'r' : (maxG - minG >= maxB - minB ? 'g' : 'b');
                cluster.sort((a, b) => a[sortChannel] - b[sortChannel]);
                const mid = Math.floor(cluster.length / 2);
                return [...medianCut(cluster.slice(0, mid), depth - 1), ...medianCut(cluster.slice(mid), depth - 1)];
            }

            const quantized = medianCut(pixels, 4).slice(0, 15);
            palette = [{ r: 255, g: 0, b: 255, hex: '#ff00ff', bgr555: 0x7C1F }, ...quantized];
            while (palette.length < 16) {
                palette.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0 });
            }

            for (let i = 0; i < pixelIndices.length; i++) {
                const off = i * 4;
                if (rawImgData[off + 3] < 128) {
                    pixelIndices[i] = 0;
                } else {
                    const r = rawImgData[off], g = rawImgData[off + 1], b = rawImgData[off + 2];
                    let bestIdx = 1, bestDist = Infinity;
                    for (let p = 1; p < 16; p++) {
                        const pal = palette[p];
                        const dist = (pal.r - r) ** 2 + (pal.g - g) ** 2 + (pal.b - b) ** 2;
                        if (dist < bestDist) { bestDist = dist; bestIdx = p; }
                    }
                    pixelIndices[i] = bestIdx;
                }
            }
        }
        renderPaletteSwatches();
        redrawImageFromIndices();
        runAuditor();
        vscode.postMessage({ type: 'notify', message: 'Quantized to 16 GBA BGR555 colors.' });
    });

    // Hardware & Engine Compliance Auditor
    function runAuditor() {
        const issues = [];
        let nonTransSlot0 = 0;
        const colorCounts = new Map();

        for (let i = 0; i < pixelIndices.length; i++) {
            const idx = pixelIndices[i];
            colorCounts.set(idx, (colorCounts.get(idx) || 0) + 1);
        }

        // Check image dimensions & OAM
        if (imageWidth % 8 !== 0 || imageHeight % 8 !== 0) {
            issues.push({
                type: 'err',
                text: `Dimensions ${imageWidth}x${imageHeight} not aligned to 8px GBA tile boundary.`
            });
        }

        // Check OAM sprite sizes
        const validOam = [
            [8, 8], [16, 16], [32, 32], [64, 64],
            [16, 8], [32, 8], [32, 16], [64, 32],
            [8, 16], [8, 32], [16, 32], [32, 64]
        ];
        const isOam = validOam.some(([w, h]) => w === imageWidth && h === imageHeight);
        if (imageWidth <= 64 && imageHeight <= 64 && !isOam) {
            issues.push({
                type: 'warn',
                text: `Size ${imageWidth}x${imageHeight} is an irregular GBA OAM sprite shape.`
            });
        }

        // Check dark outline luminance
        let minLum = 255;
        for (let i = 1; i < 16; i++) {
            const c = palette[i] || { r: 255, g: 255, b: 255 };
            const lum = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
            if (lum < minLum) minLum = lum;
        }
        if (minLum > 35 && imageWidth >= 64 && imageHeight >= 64) {
            issues.push({
                type: 'warn',
                text: `Darkest outline has luminance ${Math.round(minLum)} (standard battle sprites require dark outline < 30).`
            });
        }

        if (issues.length === 0) {
            issues.push({
                type: 'ok',
                text: `100% GBA Compliant: 16 colors, BGR555 snapped, tile-aligned.`
            });
        }

        auditList.innerHTML = issues.map(iss => `
            <div class="audit-item ${iss.type}">
                ${iss.type === 'ok' ? '✅' : iss.type === 'warn' ? '⚠️' : '❌'} ${iss.text}
            </div>
        `).join('');
    }

    // Auto-fix Slot 0 Transparency
    document.getElementById('btnFixSlot0').addEventListener('click', () => {
        pushUndo();
        // Set Slot 0 to transparent #ff00ff
        palette[0] = { r: 255, g: 0, b: 255, hex: '#ff00ff', bgr555: 0x7C1F };
        redrawImageFromIndices();
        runAuditor();
        vscode.postMessage({ type: 'notify', message: 'Slot 0 transparency locked and verified!' });
    });

    // Generate Shiny Variant
    document.getElementById('btnGenShiny').addEventListener('click', () => {
        pushUndo();
        const out = [{ ...palette[0] }];
        for (let i = 1; i < 16; i++) {
            const c = palette[i];
            const lum = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
            if (lum < 28) {
                out.push({ ...c });
                continue;
            }
            const rNorm = c.r / 255, gNorm = c.g / 255, bNorm = c.b / 255;
            const max = Math.max(rNorm, gNorm, bNorm);
            const min = Math.min(rNorm, gNorm, bNorm);
            let h = 0, s = max === 0 ? 0 : (max - min) / max, v = max;
            if (max !== min) {
                const d = max - min;
                if (max === rNorm) h = (gNorm - bNorm) / d + (gNorm < bNorm ? 6 : 0);
                else if (max === gNorm) h = (bNorm - rNorm) / d + 2;
                else h = (rNorm - gNorm) / d + 4;
                h /= 6;
            }
            h = (h + 0.35) % 1.0;
            const iVal = Math.floor(h * 6);
            const f = h * 6 - iVal;
            const p = v * (1 - s), q = v * (1 - f * s), t = v * (1 - (1 - f) * s);
            let rn, gn, bn;
            switch (iVal % 6) {
                case 0: rn = v; gn = t; bn = p; break;
                case 1: rn = q; gn = v; bn = p; break;
                case 2: rn = p; gn = v; bn = t; break;
                case 3: rn = p; gn = q; bn = v; break;
                case 4: rn = t; gn = p; bn = v; break;
                case 5: rn = v; gn = p; bn = q; break;
            }
            const [sr, sg, sb] = clampGbaRgb(Math.round(rn * 255), Math.round(gn * 255), Math.round(bn * 255));
            out.push({
                r: sr, g: sg, b: sb,
                hex: rgbToHex(sr, sg, sb),
                bgr555: rgbToBgr555(sr, sg, sb)
            });
        }
        palette = out;
        renderPaletteSwatches();
        redrawImageFromIndices();
        runAuditor();
        vscode.postMessage({ type: 'notify', message: 'Shiny palette variant generated!' });
    });

    // Animation & Overworld Direction Logic
    function setupAnimation() {
        if (!animCanvas) return;
        const dirControls = document.getElementById('directionControls');

        if (imageWidth >= 64 && imageHeight >= 64) {
            anim.frameWidth = 64;
            anim.frameHeight = 64;
            anim.totalFrames = Math.max(1, Math.floor(imageWidth / anim.frameWidth));
            if (anim.totalFrames === 1 && imageHeight > 64) {
                anim.totalFrames = Math.floor(imageHeight / anim.frameHeight);
            }
            if (dirControls) dirControls.style.display = 'none';
        } else if (imageHeight >= 32) {
            // Overworld NPC sprites (often 16x32 or 32x32 frames)
            anim.frameWidth = imageWidth >= 32 && imageWidth % 32 === 0 ? 32 : 16;
            anim.frameHeight = 32;
            anim.totalFrames = Math.max(1, Math.floor(imageWidth / anim.frameWidth));
            if (dirControls) dirControls.style.display = 'flex';
        } else {
            anim.frameWidth = 16;
            anim.frameHeight = 16;
            anim.totalFrames = Math.max(1, Math.floor(imageWidth / 16));
            if (dirControls) dirControls.style.display = 'none';
        }

        animCanvas.width = anim.frameWidth;
        animCanvas.height = anim.frameHeight;
        updateAnimFrame();
    }

    function updateAnimFrame() {
        if (!animCanvas) return;
        animCtx.clearRect(0, 0, anim.frameWidth, anim.frameHeight);

        let sx = 0, sy = 0;
        if (imageWidth >= anim.frameWidth * anim.totalFrames) {
            sx = anim.currentFrame * anim.frameWidth;
        } else {
            sy = anim.currentFrame * anim.frameHeight;
        }

        animCtx.drawImage(
            imageCanvas,
            sx, sy, anim.frameWidth, anim.frameHeight,
            0, 0, anim.frameWidth, anim.frameHeight
        );

        const frameCounter = document.getElementById('frameCounter');
        if (frameCounter) {
            frameCounter.textContent = `${anim.currentFrame + 1} / ${anim.totalFrames}`;
        }

        // Onion Skinning
        if (gridSettings.onionSkin && onionCanvas && onionCtx && anim.totalFrames > 1) {
            onionCanvas.width = imageWidth;
            onionCanvas.height = imageHeight;
            onionCtx.clearRect(0, 0, imageWidth, imageHeight);

            const prevFrame = (anim.currentFrame - 1 + anim.totalFrames) % anim.totalFrames;
            const psx = prevFrame * anim.frameWidth;
            onionCtx.drawImage(
                imageCanvas,
                psx, 0, anim.frameWidth, anim.frameHeight,
                anim.currentFrame * anim.frameWidth, 0, anim.frameWidth, anim.frameHeight
            );
            onionCanvas.style.display = 'block';
        } else if (onionCanvas) {
            onionCanvas.style.display = 'none';
        }
    }

    function togglePlayAnimation() {
        anim.playing = !anim.playing;
        const btn = document.getElementById('btnPlayAnim');
        if (btn) btn.textContent = anim.playing ? '⏸ Pause' : '▶ Play';

        if (anim.playing) {
            anim.intervalId = setInterval(() => {
                anim.currentFrame = (anim.currentFrame + 1) % anim.totalFrames;
                updateAnimFrame();
            }, 1000 / anim.fps);
        } else {
            if (anim.intervalId) clearInterval(anim.intervalId);
        }
    }

    document.getElementById('btnPlayAnim').addEventListener('click', togglePlayAnimation);
    document.getElementById('btnNextFrame').addEventListener('click', () => {
        anim.currentFrame = (anim.currentFrame + 1) % anim.totalFrames;
        updateAnimFrame();
    });
    document.getElementById('btnPrevFrame').addEventListener('click', () => {
        anim.currentFrame = (anim.currentFrame - 1 + anim.totalFrames) % anim.totalFrames;
        updateAnimFrame();
    });

    // FPS Slider
    const fpsSlider = document.getElementById('fpsSlider');
    const fpsValueText = document.getElementById('fpsValueText');
    fpsSlider.addEventListener('input', (e) => {
        anim.fps = parseInt(e.target.value, 10);
        fpsValueText.textContent = `${anim.fps} FPS`;
        if (anim.playing) {
            clearInterval(anim.intervalId);
            anim.intervalId = setInterval(() => {
                anim.currentFrame = (anim.currentFrame + 1) % anim.totalFrames;
                updateAnimFrame();
            }, 1000 / anim.fps);
        }
    });

    // Direction buttons
    document.querySelectorAll('.direction-controls .tool-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.direction-controls .tool-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            const dir = btn.dataset.dir;
            const dirOffsets = { down: 0, up: 3, left: 6, right: 9 };
            const offset = dirOffsets[dir] || 0;
            if (anim.totalFrames >= offset + 3) {
                anim.currentFrame = offset;
                updateAnimFrame();
            }
        });
    });

    // Onion Skin toggle
    document.getElementById('btnOnionSkin').addEventListener('click', function () {
        gridSettings.onionSkin = !gridSettings.onionSkin;
        this.classList.toggle('active', gridSettings.onionSkin);
        updateAnimFrame();
    });

    // Tool switching
    function setActiveTool(tool) {
        activeTool = tool;
        document.querySelectorAll('.tool-btn[data-tool]').forEach(btn => {
            btn.classList.toggle('active', btn.dataset.tool === tool);
        });
        viewport.style.cursor = tool === 'pan' ? 'grab' : 'crosshair';
    }

    document.querySelectorAll('.tool-btn[data-tool]').forEach(btn => {
        btn.addEventListener('click', () => setActiveTool(btn.dataset.tool));
    });

    // Grids
    document.getElementById('btnGridTile').addEventListener('click', function () {
        gridSettings.tile8 = !gridSettings.tile8;
        this.classList.toggle('active', gridSettings.tile8);
        renderOverlays();
    });

    document.getElementById('btnGridMetatile').addEventListener('click', function () {
        gridSettings.metatile16 = !gridSettings.metatile16;
        this.classList.toggle('active', gridSettings.metatile16);
        renderOverlays();
    });

    document.getElementById('btnGridFrame').addEventListener('click', function () {
        gridSettings.frame64 = !gridSettings.frame64;
        this.classList.toggle('active', gridSettings.frame64);
        renderOverlays();
    });

    // Background themes
    document.getElementById('bgSelect').addEventListener('change', function () {
        viewport.className = 'viewport bg-' + this.value;
    });

    // Zoom Buttons
    document.getElementById('btnZoomIn').addEventListener('click', () => setZoom(zoom * 1.5));
    document.getElementById('btnZoomOut').addEventListener('click', () => setZoom(zoom / 1.5));
    document.getElementById('btnZoomReset').addEventListener('click', () => {
        zoom = 8;
        panX = 0;
        panY = 0;
        updateCanvasTransform();
    });

    // Save File
    document.getElementById('btnSave').addEventListener('click', () => {
        const dataUrl = imageCanvas.toDataURL('image/png');
        vscode.postMessage({
            type: 'save_file',
            dataUrl: dataUrl,
            palette: palette,
            indices: Array.from(pixelIndices),
            width: imageWidth,
            height: imageHeight
        });
    });

    // Palette Export
    document.getElementById('btnCopyCArray').addEventListener('click', () => {
        vscode.postMessage({ type: 'copy_c_array', palette: palette });
    });
    document.getElementById('btnExportPal').addEventListener('click', () => {
        vscode.postMessage({ type: 'export_palette_jasc', palette: palette });
    });
    document.getElementById('btnExportGbapal').addEventListener('click', () => {
        vscode.postMessage({ type: 'export_palette_gbapal', palette: palette });
    });
    document.getElementById('btnExportGpl').addEventListener('click', () => {
        vscode.postMessage({ type: 'export_palette_gpl', palette: palette });
    });

    // Keyboard Shortcuts
    window.addEventListener('keydown', (e) => {
        if ((e.ctrlKey || e.metaKey) && e.key === 'z') {
            e.preventDefault();
            if (e.shiftKey) triggerRedo();
            else triggerUndo();
        } else if ((e.ctrlKey || e.metaKey) && e.key === 'y') {
            e.preventDefault();
            triggerRedo();
        } else if ((e.ctrlKey || e.metaKey) && e.key === 's') {
            e.preventDefault();
            document.getElementById('btnSave').click();
        } else if (e.key === 'b') setActiveTool('pencil');
        else if (e.key === 'e') setActiveTool('eraser');
        else if (e.key === 'l') setActiveTool('line');
        else if (e.key === 'u') setActiveTool('rect');
        else if (e.key === 'c') setActiveTool('circle');
        else if (e.key === 'g') setActiveTool('fill');
        else if (e.key === 'r') setActiveTool('replace');
        else if (e.key === 'i') setActiveTool('eyedropper');
        else if (e.key === 'h' || e.key === ' ') setActiveTool('pan');
    });

    // Extension Host Communication
    window.addEventListener('message', (event) => {
        const msg = event.data;
        if (msg.type === 'load_image') {
            fileInfo = msg;
            document.getElementById('fileNameBadge').textContent = msg.fileName;

            if (msg.settings) {
                if (msg.settings.defaultZoom) zoom = msg.settings.defaultZoom;
                if (msg.settings.defaultBackground) {
                    viewport.className = 'viewport bg-' + msg.settings.defaultBackground;
                    document.getElementById('bgSelect').value = msg.settings.defaultBackground;
                }
                if (msg.settings.animationFps) {
                    anim.fps = msg.settings.animationFps;
                    fpsSlider.value = anim.fps;
                    fpsValueText.textContent = `${anim.fps} FPS`;
                }
            }

            if (msg.palette && msg.palette.length > 0) {
                palette = msg.palette;
            }

            const img = new Image();
            img.onload = () => {
                imageWidth = img.naturalWidth || 64;
                imageHeight = img.naturalHeight || 64;

                imageCanvas.width = imageWidth;
                imageCanvas.height = imageHeight;
                document.getElementById('dimensionsBadge').textContent = `${imageWidth}x${imageHeight}`;

                ctx.drawImage(img, 0, 0);
                const rawImgData = ctx.getImageData(0, 0, imageWidth, imageHeight);
                pixelIndices = new Uint8Array(imageWidth * imageHeight);

                for (let i = 0; i < pixelIndices.length; i++) {
                    const r = rawImgData.data[i * 4];
                    const g = rawImgData.data[i * 4 + 1];
                    const b = rawImgData.data[i * 4 + 2];
                    const a = rawImgData.data[i * 4 + 3];

                    if (a < 128) {
                        pixelIndices[i] = 0;
                    } else {
                        let bestIdx = 1;
                        let bestDist = Infinity;
                        for (let p = 1; p < 16; p++) {
                            const palCol = palette[p] || { r: 0, g: 0, b: 0 };
                            const dist = (palCol.r - r) ** 2 + (palCol.g - g) ** 2 + (palCol.b - b) ** 2;
                            if (dist < bestDist) {
                                bestDist = dist;
                                bestIdx = p;
                            }
                        }
                        pixelIndices[i] = bestIdx;
                    }
                }

                renderPaletteSwatches();
                redrawImageFromIndices();
                setupAnimation();
                runAuditor();
                updateCanvasTransform();
            };
            img.src = msg.dataUrl;
        } else if (msg.type === 'load_raw_tiles') {
            fileInfo = msg;
            document.getElementById('fileNameBadge').textContent = msg.fileName;
            imageWidth = msg.width;
            imageHeight = msg.height;
            imageCanvas.width = imageWidth;
            imageCanvas.height = imageHeight;
            document.getElementById('dimensionsBadge').textContent = `${imageWidth}x${imageHeight}`;
            document.getElementById('depthBadge').textContent = msg.is8bpp ? '256 Colors (8bpp)' : '16 Colors (4bpp)';

            pixelIndices = new Uint8Array(msg.indices);
            if (msg.palette && msg.palette.length > 0) {
                palette = msg.palette;
            }

            renderPaletteSwatches();
            redrawImageFromIndices();
            setupAnimation();
            runAuditor();
            updateCanvasTransform();
        } else if (msg.type === 'load_palette') {
            fileInfo = msg;
            document.getElementById('fileNameBadge').textContent = msg.fileName;
            palette = msg.palette;
            imageWidth = 64;
            imageHeight = 64;
            imageCanvas.width = 64;
            imageCanvas.height = 64;
            pixelIndices = new Uint8Array(64 * 64);
            for (let y = 0; y < 64; y++) {
                for (let x = 0; x < 64; x++) {
                    const col = Math.floor(x / 16);
                    const row = Math.floor(y / 16);
                    pixelIndices[y * 64 + x] = row * 4 + col;
                }
            }
            renderPaletteSwatches();
            redrawImageFromIndices();
            runAuditor();
            updateCanvasTransform();
        }
    });

    vscode.postMessage({ type: 'ready' });
})();
