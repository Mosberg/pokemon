// POKE-CONFLUENCE Gallery Webview Logic
(function () {
    const vscode = acquireVsCodeApi();

    let projectData = {
        species: [],
        trainers: [],
        items: [],
        overworld: [],
        tilesets: { primary: [], secondary: [] },
        interface: [],
        stats: {}
    };

    let activeTab = 'pokemon';
    let activeGen = 'all';
    let searchQuery = '';

    const searchInput = document.getElementById('searchInput');
    const loadingIndicator = document.getElementById('loadingIndicator');
    const galleryList = document.getElementById('galleryList');
    const subfilterBar = document.getElementById('subfilterBar');
    const statsHeader = document.getElementById('statsHeader');

    // Tab buttons
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            activeTab = btn.dataset.tab;

            if (activeTab === 'pokemon') {
                subfilterBar.style.display = 'flex';
            } else {
                subfilterBar.style.display = 'none';
            }

            renderGallery();
        });
    });

    // Subfilter buttons
    document.querySelectorAll('.subfilter-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.subfilter-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            activeGen = btn.dataset.gen;
            renderGallery();
        });
    });

    // Search input
    searchInput.addEventListener('input', (e) => {
        searchQuery = e.target.value.toLowerCase().trim();
        renderGallery();
    });

    // Handle messages
    window.addEventListener('message', (event) => {
        const msg = event.data;
        if (msg.type === 'project_data') {
            projectData = msg.data;
            loadingIndicator.style.display = 'none';

            if (projectData.stats) {
                statsHeader.textContent = `${projectData.species.length} Species | ${projectData.trainers.length} Trainers | ${projectData.items.length} Items | ${projectData.overworld.length} OW`;
            }

            renderGallery();
        }
    });

    function openAsset(filePath) {
        if (!filePath) return;
        vscode.postMessage({
            type: 'open_asset',
            filePath: filePath
        });
    }

    function renderGallery() {
        galleryList.innerHTML = '';

        if (activeTab === 'pokemon') {
            renderSpecies();
        } else if (activeTab === 'trainers') {
            renderTrainers();
        } else if (activeTab === 'items') {
            renderItems();
        } else if (activeTab === 'overworld') {
            renderOverworld();
        } else if (activeTab === 'tilesets') {
            renderTilesets();
        } else if (activeTab === 'interface') {
            renderInterface();
        }
    }

    function renderSpecies() {
        let filtered = projectData.species.filter(sp => {
            const matchesQuery = sp.name.toLowerCase().includes(searchQuery);
            if (!matchesQuery) return false;

            if (activeGen === 'all') return true;
            if (activeGen === 'kanto') return sp.index <= 151;
            if (activeGen === 'johto') return sp.index > 151 && sp.index <= 251;
            if (activeGen === 'hoenn') return sp.index > 251 && sp.index <= 386;
            if (activeGen === 'later') return sp.index > 386;
            return true;
        });

        if (filtered.length === 0) {
            galleryList.innerHTML = '<div class="loading">No Pokémon species found matching criteria.</div>';
            return;
        }

        filtered.slice(0, 150).forEach(sp => {
            const card = document.createElement('div');
            card.className = 'asset-card';

            let pills = '';
            if (sp.animFront) pills += `<button class="asset-pill has-asset" data-path="${sp.animFront}">Anim</button>`;
            if (sp.front) pills += `<button class="asset-pill has-asset" data-path="${sp.front}">Front</button>`;
            if (sp.back) pills += `<button class="asset-pill has-asset" data-path="${sp.back}">Back</button>`;
            if (sp.normalPal) pills += `<button class="asset-pill has-asset" data-path="${sp.normalPal}">Pal</button>`;
            if (sp.shinyPal) pills += `<button class="asset-pill has-asset" data-path="${sp.shinyPal}">Shiny</button>`;
            if (sp.icon) pills += `<button class="asset-pill has-asset" data-path="${sp.icon}">Icon</button>`;
            if (sp.footprint) pills += `<button class="asset-pill has-asset" data-path="${sp.footprint}">Footprint</button>`;

            card.innerHTML = `
                <div class="asset-title">
                    <span>#${sp.index.toString().padStart(3, '0')} ${sp.name.replace(/_/g, ' ')}</span>
                    <span style="font-size: 8px; color: var(--text-muted);">${sp.gen}</span>
                </div>
                <div class="asset-pills">${pills}</div>
            `;

            card.querySelectorAll('.asset-pill').forEach(btn => {
                btn.addEventListener('click', (e) => {
                    e.stopPropagation();
                    openAsset(btn.dataset.path);
                });
            });

            galleryList.appendChild(card);
        });
    }

    function renderTrainers() {
        const filtered = projectData.trainers.filter(tr => {
            return tr.name.toLowerCase().includes(searchQuery);
        });

        if (filtered.length === 0) {
            galleryList.innerHTML = '<div class="loading">No trainers found.</div>';
            return;
        }

        filtered.slice(0, 100).forEach(tr => {
            const card = document.createElement('div');
            card.className = 'asset-card';
            card.innerHTML = `
                <div class="asset-title">
                    <span>${tr.name.replace(/_/g, ' ')} (${tr.type})</span>
                </div>
                <div class="asset-pills">
                    <button class="asset-pill has-asset" data-path="${tr.pic}">Sprite</button>
                    ${tr.palette ? `<button class="asset-pill has-asset" data-path="${tr.palette}">Palette</button>` : ''}
                </div>
            `;

            card.querySelectorAll('.asset-pill').forEach(btn => {
                btn.addEventListener('click', () => openAsset(btn.dataset.path));
            });

            galleryList.appendChild(card);
        });
    }

    function renderItems() {
        const filtered = projectData.items.filter(it => {
            return it.name.toLowerCase().includes(searchQuery);
        });

        if (filtered.length === 0) {
            galleryList.innerHTML = '<div class="loading">No items found.</div>';
            return;
        }

        const grid = document.createElement('div');
        grid.className = 'items-grid';

        filtered.slice(0, 150).forEach(it => {
            const card = document.createElement('div');
            card.className = 'item-thumb-card';
            card.title = it.name;
            card.innerHTML = `
                <div class="item-name">${it.name.replace(/^item_/, '').replace(/_/g, ' ')}</div>
            `;
            card.addEventListener('click', () => openAsset(it.icon));
            grid.appendChild(card);
        });

        galleryList.appendChild(grid);
    }

    function renderOverworld() {
        const filtered = projectData.overworld.filter(ow => {
            return ow.name.toLowerCase().includes(searchQuery);
        });

        if (filtered.length === 0) {
            galleryList.innerHTML = '<div class="loading">No overworld sprites found.</div>';
            return;
        }

        filtered.slice(0, 120).forEach(ow => {
            const card = document.createElement('div');
            card.className = 'asset-card';
            card.innerHTML = `
                <div class="asset-title">
                    <span>${ow.name.replace(/_/g, ' ')}</span>
                    <span style="font-size: 9px; color: var(--text-muted);">${ow.category}</span>
                </div>
                <div class="asset-pills">
                    <button class="asset-pill has-asset" data-path="${ow.path}">View Sprite</button>
                </div>
            `;

            card.querySelector('.asset-pill').addEventListener('click', () => openAsset(ow.path));
            galleryList.appendChild(card);
        });
    }

    function renderTilesets() {
        const list = [
            ...projectData.tilesets.primary.map(t => ({ ...t, kind: 'primary' })),
            ...projectData.tilesets.secondary.map(t => ({ ...t, kind: 'secondary' }))
        ].filter(ts => ts.name.toLowerCase().includes(searchQuery));

        if (list.length === 0) {
            galleryList.innerHTML = '<div class="loading">No tilesets found.</div>';
            return;
        }

        list.forEach(ts => {
            const card = document.createElement('div');
            card.className = 'asset-card';

            let palsPills = '';
            if (ts.palettes && ts.palettes.length > 0) {
                palsPills = ts.palettes.map((p, idx) => `<button class="asset-pill has-asset" data-path="${p}">Pal ${idx}</button>`).join('');
            }

            card.innerHTML = `
                <div class="asset-title">
                    <span>${ts.name}</span>
                    <span style="font-size: 9px; color: var(--text-muted);">${ts.kind}</span>
                </div>
                <div class="asset-pills">
                    ${ts.tiles ? `<button class="asset-pill has-asset" data-path="${ts.tiles}">tiles.png</button>` : ''}
                    ${palsPills}
                </div>
            `;

            card.querySelectorAll('.asset-pill').forEach(btn => {
                btn.addEventListener('click', () => openAsset(btn.dataset.path));
            });

            galleryList.appendChild(card);
        });
    }

    function renderInterface() {
        const filtered = (projectData.interface || []).filter(ui => {
            return ui.name.toLowerCase().includes(searchQuery) || ui.category.toLowerCase().includes(searchQuery);
        });

        if (filtered.length === 0) {
            galleryList.innerHTML = '<div class="loading">No UI assets found.</div>';
            return;
        }

        filtered.slice(0, 100).forEach(ui => {
            const card = document.createElement('div');
            card.className = 'asset-card';
            card.innerHTML = `
                <div class="asset-title">
                    <span>${ui.name}</span>
                    <span style="font-size: 9px; color: var(--text-muted);">${ui.category}</span>
                </div>
                <div class="asset-pills">
                    <button class="asset-pill has-asset" data-path="${ui.path}">Open File</button>
                </div>
            `;
            card.querySelector('.asset-pill').addEventListener('click', () => openAsset(ui.path));
            galleryList.appendChild(card);
        });
    }

    vscode.postMessage({ type: 'scan_project' });
})();
