// POKE-CONFLUENCE GBA Hardware, Tile & Color Engine Core
// Strict adherence to GBA 15-bit BGR555, JASC-PAL, ACT, GPL, and planar 4bpp/8bpp formats.

function snapToGbaChannel(val) {
    const c5 = Math.round(val * 31 / 255);
    return Math.round(c5 * 255 / 31);
}

function clampGbaRgb(r, g, b) {
    return [
        snapToGbaChannel(r),
        snapToGbaChannel(g),
        snapToGbaChannel(b)
    ];
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
    const toHex = (c) => c.toString(16).padStart(2, '0');
    return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
}

function hexToRgb(hex) {
    let clean = hex.replace('#', '');
    if (clean.length === 3) {
        clean = clean.split('').map(c => c + c).join('');
    }
    const num = parseInt(clean, 16);
    return [(num >> 16) & 255, (num >> 8) & 255, num & 255];
}

function formatBgr555Hex(val) {
    return '0x' + (val & 0xFFFF).toString(16).padStart(4, '0').toUpperCase();
}

/**
 * Validates GBA hardware OAM sprite shapes and dimensions.
 * Valid shapes:
 * - Square: 8x8, 16x16, 32x32, 64x64
 * - Horizontal: 16x8, 32x8, 32x16, 64x32
 * - Vertical: 8x16, 8x32, 16x32, 32x64
 */
function validateOamSize(width, height) {
    const valid = [
        [8, 8], [16, 16], [32, 32], [64, 64],
        [16, 8], [32, 8], [32, 16], [64, 32],
        [8, 16], [8, 32], [16, 32], [32, 64]
    ];
    for (const [w, h] of valid) {
        if (width === w && height === h) {
            return { isValid: true, shape: w === h ? 'Square' : w > h ? 'Horizontal' : 'Vertical', w, h };
        }
    }
    return { isValid: false, shape: 'Custom/Sheet', w: width, h: height };
}

/**
 * Checks if sprite darkest outline meets standard GBA battle sprite outline luminance (< 28).
 */
function checkDarkOutlineLuminance(palette) {
    let minLum = 255;
    for (let i = 1; i < 16; i++) {
        const c = palette[i] || { r: 255, g: 255, b: 255 };
        const lum = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
        if (lum < minLum) minLum = lum;
    }
    return {
        compliant: minLum <= 32,
        minLuminance: Math.round(minLum)
    };
}

/**
 * Parses a JASC-PAL string into an array of colors: { r, g, b, hex, bgr555 }
 */
function parseJascPal(text) {
    const lines = text.split(/\r?\n/).map(l => l.trim()).filter(l => l.length > 0);
    const defaultColor = { r: 255, g: 0, b: 255, hex: '#ff00ff', bgr555: 0x7C1F };
    if (lines.length < 3 || lines[0] !== 'JASC-PAL') {
        const out = [defaultColor];
        while (out.length < 16) out.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0x0000 });
        return out;
    }

    const count = parseInt(lines[2], 10) || 16;
    const colors = [];
    for (let i = 3; i < 3 + count && i < lines.length; i++) {
        const parts = lines[i].split(/\s+/).map(Number);
        if (parts.length >= 3) {
            const [r, g, b] = clampGbaRgb(parts[0], parts[1], parts[2]);
            const bgr = rgbToBgr555(r, g, b);
            colors.push({ r, g, b, hex: rgbToHex(r, g, b), bgr555: bgr });
        }
    }
    while (colors.length < 16) {
        colors.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0x0000 });
    }
    return colors;
}

/**
 * Serializes colors to standard JASC-PAL string.
 */
function writeJascPal(colors, count = 16) {
    const num = Math.max(16, Math.min(256, count));
    const lines = ['JASC-PAL', '0100', num.toString()];
    for (let i = 0; i < num; i++) {
        const c = colors[i] || { r: 0, g: 0, b: 0 };
        const [r, g, b] = clampGbaRgb(c.r, c.g, c.b);
        lines.push(`${r} ${g} ${b}`);
    }
    return lines.join('\n') + '\n';
}

/**
 * Parses raw GBA binary palette (.gbapal) into array of colors.
 */
function parseGbapal(buffer) {
    const totalColors = Math.min(256, Math.floor(buffer.length / 2));
    const colors = [];
    for (let i = 0; i < totalColors; i++) {
        const offset = i * 2;
        const val = buffer[offset] | (buffer[offset + 1] << 8);
        const [r, g, b] = bgr555ToRgb(val);
        colors.push({ r, g, b, hex: rgbToHex(r, g, b), bgr555: val });
    }
    while (colors.length < 16) {
        colors.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0x0000 });
    }
    return colors;
}

/**
 * Serializes colors to a GBA binary palette (.gbapal) Uint8Array.
 */
function writeGbapal(colors, count = 16) {
    const out = new Uint8Array(count * 2);
    for (let i = 0; i < count; i++) {
        const c = colors[i] || { r: 0, g: 0, b: 0 };
        const val = rgbToBgr555(c.r, c.g, c.b);
        out[i * 2] = val & 0xFF;
        out[i * 2 + 1] = (val >> 8) & 0xFF;
    }
    return out;
}

/**
 * Parses Adobe Photoshop .act color table (768 bytes = 256 colors).
 */
function parseAct(buffer) {
    const colors = [];
    const count = Math.min(256, Math.floor(buffer.length / 3));
    for (let i = 0; i < count; i++) {
        const r = buffer[i * 3];
        const g = buffer[i * 3 + 1];
        const b = buffer[i * 3 + 2];
        const [sr, sg, sb] = clampGbaRgb(r, g, b);
        colors.push({
            r: sr, g: sg, b: sb,
            hex: rgbToHex(sr, sg, sb),
            bgr555: rgbToBgr555(sr, sg, sb)
        });
    }
    while (colors.length < 16) {
        colors.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0 });
    }
    return colors;
}

/**
 * Serializes colors to Adobe Photoshop .act color table (768 bytes).
 */
function writeAct(colors) {
    const out = new Uint8Array(768);
    for (let i = 0; i < 256; i++) {
        const c = colors[i] || { r: 0, g: 0, b: 0 };
        const [r, g, b] = clampGbaRgb(c.r, c.g, c.b);
        out[i * 3] = r;
        out[i * 3 + 1] = g;
        out[i * 3 + 2] = b;
    }
    return out;
}

/**
 * Serializes colors to GIMP Palette (.gpl) format.
 */
function writeGpl(colors, name = 'GBA Palette') {
    const lines = [
        'GIMP Palette',
        `Name: ${name}`,
        'Columns: 8',
        '#'
    ];
    for (let i = 0; i < colors.length && i < 256; i++) {
        const c = colors[i] || { r: 0, g: 0, b: 0 };
        const [r, g, b] = clampGbaRgb(c.r, c.g, c.b);
        lines.push(`${r.toString().padStart(3, ' ')} ${g.toString().padStart(3, ' ')} ${sb = b.toString().padStart(3, ' ')}  Slot_${i}`);
    }
    return lines.join('\n') + '\n';
}

/**
 * Generates C Header array definition for pokeemerald/pokeconfluence.
 */
function exportCArray(colors, varName) {
    const safeName = (varName || 'gPalette').replace(/[^a-zA-Z0-9_]/g, '_');
    const lines = [
        '// POKE-CONFLUENCE Generated GBA Palette',
        `const u16 ${safeName}[16] = {`
    ];
    for (let i = 0; i < 16; i++) {
        const c = colors[i] || { r: 0, g: 0, b: 0 };
        const bgr = rgbToBgr555(c.r, c.g, c.b);
        const hex = formatBgr555Hex(bgr);
        const comment = `// [${i.toString().padStart(2, ' ')}] RGB(${c.r}, ${c.g}, ${c.b}) ${i === 0 ? '<-- TRANSPARENT' : ''}`;
        lines.push(`    ${hex}, ${comment}`);
    }
    lines.push('};');
    return lines.join('\n');
}

/**
 * Decodes 4bpp planar GBA tiles (32 bytes per 8x8 tile).
 */
function decode4bpp(buffer, widthTiles, heightTiles, palette) {
    const width = widthTiles * 8;
    const height = heightTiles * 8;
    const rgba = new Uint8ClampedArray(width * height * 4);
    const indices = new Uint8Array(width * height);

    let tileIdx = 0;
    for (let ty = 0; ty < heightTiles; ty++) {
        for (let tx = 0; tx < widthTiles; tx++) {
            const tileOffset = tileIdx * 32;
            tileIdx++;
            if (tileOffset >= buffer.length) break;

            for (let py = 0; py < 8; py++) {
                for (let px = 0; px < 8; px += 2) {
                    const byteOffset = tileOffset + py * 4 + (px >> 1);
                    const b = byteOffset < buffer.length ? buffer[byteOffset] : 0;
                    const p0 = b & 0x0F;
                    const p1 = (b >> 4) & 0x0F;

                    const plotPixel = (xOffset, palIdx) => {
                        const targetX = tx * 8 + xOffset;
                        const targetY = ty * 8 + py;
                        const pos = targetY * width + targetX;
                        indices[pos] = palIdx;
                        const outIdx = pos * 4;
                        const col = palette[palIdx] || { r: 0, g: 0, b: 0 };
                        rgba[outIdx] = col.r;
                        rgba[outIdx + 1] = col.g;
                        rgba[outIdx + 2] = col.b;
                        rgba[outIdx + 3] = palIdx === 0 ? 0 : 255;
                    };

                    plotPixel(px, p0);
                    plotPixel(px + 1, p1);
                }
            }
        }
    }
    return { width, height, data: rgba, indices };
}

/**
 * Encodes pixel indices into 4bpp planar GBA tile binary (32 bytes per 8x8 tile).
 */
function encode4bpp(pixelIndices, width, height) {
    const widthTiles = Math.ceil(width / 8);
    const heightTiles = Math.ceil(height / 8);
    const totalTiles = widthTiles * heightTiles;
    const buffer = new Uint8Array(totalTiles * 32);

    let tileIdx = 0;
    for (let ty = 0; ty < heightTiles; ty++) {
        for (let tx = 0; tx < widthTiles; tx++) {
            const tileOffset = tileIdx * 32;
            tileIdx++;

            for (let py = 0; py < 8; py++) {
                for (let px = 0; px < 8; px += 2) {
                    const srcX0 = tx * 8 + px;
                    const srcY0 = ty * 8 + py;
                    const p0 = (srcX0 < width && srcY0 < height) ? (pixelIndices[srcY0 * width + srcX0] & 0x0F) : 0;

                    const srcX1 = tx * 8 + px + 1;
                    const srcY1 = ty * 8 + py;
                    const p1 = (srcX1 < width && srcY1 < height) ? (pixelIndices[srcY1 * width + srcX1] & 0x0F) : 0;

                    const byteOffset = tileOffset + py * 4 + (px >> 1);
                    buffer[byteOffset] = p0 | (p1 << 4);
                }
            }
        }
    }
    return buffer;
}

/**
 * Decodes 8bpp planar GBA tiles (64 bytes per 8x8 tile).
 */
function decode8bpp(buffer, widthTiles, heightTiles, palette) {
    const width = widthTiles * 8;
    const height = heightTiles * 8;
    const rgba = new Uint8ClampedArray(width * height * 4);
    const indices = new Uint8Array(width * height);

    let tileIdx = 0;
    for (let ty = 0; ty < heightTiles; ty++) {
        for (let tx = 0; tx < widthTiles; tx++) {
            const tileOffset = tileIdx * 64;
            tileIdx++;
            if (tileOffset >= buffer.length) break;

            for (let py = 0; py < 8; py++) {
                for (let px = 0; px < 8; px++) {
                    const byteOffset = tileOffset + py * 8 + px;
                    const palIdx = byteOffset < buffer.length ? buffer[byteOffset] : 0;
                    const targetX = tx * 8 + px;
                    const targetY = ty * 8 + py;
                    const pos = targetY * width + targetX;
                    indices[pos] = palIdx;
                    const outIdx = pos * 4;
                    const col = palette[palIdx] || { r: 0, g: 0, b: 0 };
                    rgba[outIdx] = col.r;
                    rgba[outIdx + 1] = col.g;
                    rgba[outIdx + 2] = col.b;
                    rgba[outIdx + 3] = palIdx === 0 ? 0 : 255;
                }
            }
        }
    }
    return { width, height, data: rgba, indices };
}

/**
 * Encodes pixel indices into 8bpp planar GBA tile binary (64 bytes per 8x8 tile).
 */
function encode8bpp(pixelIndices, width, height) {
    const widthTiles = Math.ceil(width / 8);
    const heightTiles = Math.ceil(height / 8);
    const totalTiles = widthTiles * heightTiles;
    const buffer = new Uint8Array(totalTiles * 64);

    let tileIdx = 0;
    for (let ty = 0; ty < heightTiles; ty++) {
        for (let tx = 0; tx < widthTiles; tx++) {
            const tileOffset = tileIdx * 64;
            tileIdx++;

            for (let py = 0; py < 8; py++) {
                for (let px = 0; px < 8; px++) {
                    const srcX = tx * 8 + px;
                    const srcY = ty * 8 + py;
                    const palIdx = (srcX < width && srcY < height) ? (pixelIndices[srcY * width + srcX] & 0xFF) : 0;
                    buffer[tileOffset + py * 8 + px] = palIdx;
                }
            }
        }
    }
    return buffer;
}

/**
 * Intelligent GBA Color Quantizer:
 * Takes RGBA pixel data, clusters opaque colors into 15 unique BGR555 colors using median-cut,
 * locks Slot 0 to transparent #FF00FF, and re-maps all pixels.
 */
function quantizeRgbToGba(rgbaData, width, height) {
    const pixels = [];
    const alphaThreshold = 128;

    for (let i = 0; i < rgbaData.length; i += 4) {
        const a = rgbaData[i + 3];
        if (a >= alphaThreshold) {
            const [r, g, b] = clampGbaRgb(rgbaData[i], rgbaData[i + 1], rgbaData[i + 2]);
            pixels.push({ r, g, b });
        }
    }

    let palette = [{ r: 255, g: 0, b: 255, hex: '#ff00ff', bgr555: 0x7C1F }]; // Slot 0 transparent

    if (pixels.length === 0) {
        while (palette.length < 16) {
            palette.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0 });
        }
    } else {
        // Median-cut algorithm up to 15 colors
        function medianCut(cluster, depth) {
            if (depth === 0 || cluster.length <= 1) {
                // Average
                let tr = 0, tg = 0, tb = 0;
                for (const p of cluster) {
                    tr += p.r; tg += p.g; tb += p.b;
                }
                const count = cluster.length;
                const [r, g, b] = clampGbaRgb(Math.round(tr / count), Math.round(tg / count), Math.round(tb / count));
                return [{ r, g, b, hex: rgbToHex(r, g, b), bgr555: rgbToBgr555(r, g, b) }];
            }

            // Find channel with maximum range
            let minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0;
            for (const p of cluster) {
                if (p.r < minR) minR = p.r; if (p.r > maxR) maxR = p.r;
                if (p.g < minG) minG = p.g; if (p.g > maxG) maxG = p.g;
                if (p.b < minB) minB = p.b; if (p.b > maxB) maxB = p.b;
            }

            const rangeR = maxR - minR;
            const rangeG = maxG - minG;
            const rangeB = maxB - minB;
            const sortChannel = rangeR >= rangeG && rangeR >= rangeB ? 'r' : rangeG >= rangeB ? 'g' : 'b';

            cluster.sort((a, b) => a[sortChannel] - b[sortChannel]);
            const mid = Math.floor(cluster.length / 2);
            return [
                ...medianCut(cluster.slice(0, mid), depth - 1),
                ...medianCut(cluster.slice(mid), depth - 1)
            ];
        }

        const colors = medianCut(pixels, 4).slice(0, 15);
        palette = palette.concat(colors);
        while (palette.length < 16) {
            palette.push({ r: 0, g: 0, b: 0, hex: '#000000', bgr555: 0 });
        }
    }

    // Remap all pixels to closest palette index
    const indices = new Uint8Array(width * height);
    for (let i = 0; i < indices.length; i++) {
        const offset = i * 4;
        const a = rgbaData[offset + 3];
        if (a < alphaThreshold) {
            indices[i] = 0;
        } else {
            const r = rgbaData[offset];
            const g = rgbaData[offset + 1];
            const b = rgbaData[offset + 2];

            let bestIdx = 1;
            let bestDist = Infinity;
            for (let p = 1; p < 16; p++) {
                const pal = palette[p];
                const dr = pal.r - r;
                const dg = pal.g - g;
                const db = pal.b - b;
                const dist = dr * dr + dg * dg + db * db;
                if (dist < bestDist) {
                    bestDist = dist;
                    bestIdx = p;
                }
            }
            indices[i] = bestIdx;
        }
    }

    return { palette, indices };
}

/**
 * Swaps two palette indices across the entire pixel array.
 */
function swapPaletteIndices(indices, idxA, idxB) {
    for (let i = 0; i < indices.length; i++) {
        if (indices[i] === idxA) indices[i] = idxB;
        else if (indices[i] === idxB) indices[i] = idxA;
    }
}

/**
 * Adjusts palette brightness (-100 to +100) and contrast (-100 to +100) with BGR555 snapping.
 * Locks Slot 0 transparency.
 */
function adjustPaletteBrightnessContrast(palette, brightness, contrast) {
    const factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    const out = [{ ...palette[0] }]; // Slot 0 preserved

    for (let i = 1; i < palette.length; i++) {
        const c = palette[i] || { r: 0, g: 0, b: 0 };
        // Brightness
        let r = c.r + brightness;
        let g = c.g + brightness;
        let b = c.b + brightness;

        // Contrast
        r = factor * (r - 128) + 128;
        g = factor * (g - 128) + 128;
        b = factor * (b - 128) + 128;

        const clampedR = Math.max(0, Math.min(255, Math.round(r)));
        const clampedG = Math.max(0, Math.min(255, Math.round(g)));
        const clampedB = Math.max(0, Math.min(255, Math.round(b)));

        const [sr, sg, sb] = clampGbaRgb(clampedR, clampedG, clampedB);
        const bgr = rgbToBgr555(sr, sg, sb);
        out.push({ r: sr, g: sg, b: sb, hex: rgbToHex(sr, sg, sb), bgr555: bgr });
    }
    return out;
}

/**
 * Generates an authentic shiny palette variant by rotating hue,
 * while locking Slot 0 transparency and preserving dark outlines.
 */
function generateShinyPalette(normalPal, hueShift = 0.35) {
    const out = [{ ...normalPal[0] }]; // Slot 0 preserved
    for (let i = 1; i < 16; i++) {
        const c = normalPal[i] || { r: 0, g: 0, b: 0 };
        const luminance = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
        if (luminance < 28) {
            // Keep deep black/dark outlines untouched
            out.push({ ...c });
            continue;
        }

        // RGB to HSV
        const rNorm = c.r / 255;
        const gNorm = c.g / 255;
        const bNorm = c.b / 255;
        const max = Math.max(rNorm, gNorm, bNorm);
        const min = Math.min(rNorm, gNorm, bNorm);
        let h = 0;
        let s = max === 0 ? 0 : (max - min) / max;
        let v = max;

        if (max !== min) {
            const d = max - min;
            switch (max) {
                case rNorm: h = (gNorm - bNorm) / d + (gNorm < bNorm ? 6 : 0); break;
                case gNorm: h = (bNorm - rNorm) / d + 2; break;
                case bNorm: h = (rNorm - gNorm) / d + 4; break;
            }
            h /= 6;
        }

        // Rotate hue
        h = (h + hueShift) % 1.0;

        // HSV to RGB
        let rn, gn, bn;
        const iVal = Math.floor(h * 6);
        const f = h * 6 - iVal;
        const p = v * (1 - s);
        const q = v * (1 - f * s);
        const t = v * (1 - (1 - f) * s);

        switch (iVal % 6) {
            case 0: rn = v; gn = t; bn = p; break;
            case 1: rn = q; gn = v; bn = p; break;
            case 2: rn = p; gn = v; bn = t; break;
            case 3: rn = p; gn = q; bn = v; break;
            case 4: rn = t; gn = p; bn = v; break;
            case 5: rn = v; gn = p; bn = q; break;
        }

        const [sr, sg, sb] = clampGbaRgb(
            Math.round(rn * 255),
            Math.round(gn * 255),
            Math.round(bn * 255)
        );
        const bgr = rgbToBgr555(sr, sg, sb);
        out.push({ r: sr, g: sg, b: sb, hex: rgbToHex(sr, sg, sb), bgr555: bgr });
    }
    return out;
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        snapToGbaChannel,
        clampGbaRgb,
        rgbToBgr555,
        bgr555ToRgb,
        rgbToHex,
        hexToRgb,
        formatBgr555Hex,
        validateOamSize,
        checkDarkOutlineLuminance,
        parseJascPal,
        writeJascPal,
        parseGbapal,
        writeGbapal,
        parseAct,
        writeAct,
        writeGpl,
        exportCArray,
        decode4bpp,
        encode4bpp,
        decode8bpp,
        encode8bpp,
        quantizeRgbToGba,
        swapPaletteIndices,
        adjustPaletteBrightnessContrast,
        generateShinyPalette
    };
}
