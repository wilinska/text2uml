// script.js - Główny plik aplikacji klienckiej
// Importy modułów (zakładamy, że są ładowane jako script tags lub przez bundler)

// ====================================================================
// ZMIENNE GLOBALNE
// ====================================================================

// Te pliki powinny być załadowane jako <script> tags w HTML:
// - utils/compressionBrowser.js (compressData, decompressData)
// - modules/configModal.js (collectConfigDataFromModal, collectCurrentParams, renderConfigFields)
// - modules/svgInteractions.js (deselectGroup, moveGroup, movePath, saveSvgToFile)
// - modules/memento.js (createSvgMemento, createTextMemento)
// - config/layoutTemplates.js (configTemplates - jako globalny obiekt)

let currentConfig = {};
let selectedGroup = null;
let lastMove = { id: null, dx: 0, dy: 0 };

// Elementy DOM
let textInput, svgOutput, diagramTypeSelect, layoutTypeSelect, edgeTypeSelect;
let configButton, configModal, applyConfigButton, renderButton, saveButton;

// Zmienne do śledzenia aktywności
let isSvgActive = false;
let isTextInputActive = false;

// Memento instances
let memento;
let textMemento;

// ====================================================================
// FUNKCJE ZARZĄDZANIA DYREKTYWAMI
// ====================================================================

/**
 * Aktualizuje dyrektywę w tekście PlantUML
 */
function updateDirective(select, directivePrefix) {
    if (!textInput) return;

    let lines = textInput.value.split("\n");

    // Usuń wszystkie linie zaczynające się od ' @<directivePrefix>
    const directiveStart = `' @${directivePrefix}`;
    lines = lines.filter(line => {
        const trimmed = line.trim();
        return !trimmed.startsWith(directiveStart);
    });

    // Znajdź indeks linii @startuml
    const startUmlIndex = lines.findIndex(line => line.trim() === '@startuml');

    // Dodaj nową linię po @startuml (lub na początek, jeśli @startuml nie istnieje)
    const newDirectiveLine = `${directiveStart} ${select.value}`;
    if (startUmlIndex !== -1) {
        lines.splice(startUmlIndex + 1, 0, newDirectiveLine);
    } else {
        lines.unshift(newDirectiveLine);
    }

    textInput.value = lines.join("\n");
    if (textMemento) textMemento.saveState();
}

/**
 * Inicjalizuje select na podstawie dyrektywy w tekście
 */
function initializeSelectFromText(select, directivePrefix) {
    if (!textInput) return;

    let lines = textInput.value.split("\n");
    const directiveStart = `' @${directivePrefix}`;

    let lastValue = null;
    for (let i = lines.length - 1; i >= 0; i--) {
        const trimmed = lines[i].trim();
        if (trimmed.startsWith(directiveStart)) {
            const match = trimmed.match(new RegExp(`${directiveStart}\\s*(.+)`));
            if (match && match[1]) {
                lastValue = match[1].trim();
                break;
            }
        }
    }

    if (lastValue) {
        const option = Array.from(select.options).find(opt => opt.value === lastValue);
        if (option) {
            select.value = lastValue;
        }
    }
}

/**
 * Snap to current positions - ustawia @position_fixed na podstawie pozycji w SVG
 */
function snapToCurrentPositions() {
    if (!svgOutput || !textInput) {
        console.error("Brak SVG lub textarea!");
        return;
    }

    let lines = textInput.value.split("\n");
    const gElements = svgOutput.querySelectorAll("g[data-id]");

    gElements.forEach((g) => {
        const dataId = g.getAttribute("data-id");
        if (!dataId || isNaN(parseInt(dataId))) return;

        const shape = g.querySelector("rect, circle");
        if (!shape) return;

        const textElement = shape.nextElementSibling;
        if (!textElement || textElement.tagName !== "text") return;

        const className = textElement.textContent.trim();
        if (!className) return;

        let x, y;
        if (shape.tagName === "rect") {
            x = parseFloat(shape.getAttribute("x")) + parseFloat(shape.getAttribute("width")) / 2 || 0;
            y = parseFloat(shape.getAttribute("y")) + parseFloat(shape.getAttribute("height")) / 2 || 0;
        } else if (shape.tagName === "circle") {
            x = parseFloat(shape.getAttribute("cx")) + parseFloat(shape.getAttribute("radius")) / 2 || 0;
            y = parseFloat(shape.getAttribute("cy")) + parseFloat(shape.getAttribute("radius")) / 2 || 0;
        } else {
            return;
        }

        let found = false;
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim();
            if (
                line.startsWith("class ") ||
                line.startsWith("abstract ") ||
                line.startsWith("interface ")
            ) {
                const name = line.split(" ")[1];
                if (name === className) {
                    removeExistingPosition(lines, i);
                    addOrUpdateFixedPosition(lines, i, x, y);
                    found = true;
                    break;
                }
            }
        }

        // Jeśli nie znaleziono klasy, dodaj nową definicję na końcu, ale przed @enduml
        if (!found) {
            const newClassDefinition = [
                `class ${className} {`,
                `' @position_fixed(${x}, ${y})`,
                "}",
            ];

            // Sprawdź, czy istnieje @enduml
            const endUmlIndex = lines.findIndex((line) => line.trim() === "@enduml");

            if (endUmlIndex !== -1) {
                // Wstaw nową definicję klasy przed @enduml
                lines.splice(endUmlIndex, 0, ...newClassDefinition);
            } else {
                // Jeśli @enduml nie istnieje, dodaj na końcu
                lines.push(...newClassDefinition);
            }
        }
    });

    textInput.value = lines.join("\n");
    if (textMemento) textMemento.saveState();
}

function removeExistingPosition(lines, classStartIndex) {
    const hasBracesInLine = lines[classStartIndex].includes("{");
    let searchStart = classStartIndex + (hasBracesInLine ? 1 : 2);

    for (let j = searchStart; j < lines.length; j++) {
        const trimmed = lines[j].trim();
        if (trimmed.startsWith("' @position(")) {
            lines.splice(j, 1);
            return;
        }
        if (trimmed === "}") break;
    }
}

function addOrUpdateFixedPosition(lines, classStartIndex, x, y) {
    const hasBracesInLine = lines[classStartIndex].includes("{");
    let searchStart = classStartIndex + (hasBracesInLine ? 1 : 2);
    let fixedIndex = -1;
    let classEndIndex = lines.length;

    if (!hasBracesInLine) {
        const nextLine = lines[classStartIndex + 1]?.trim();
        if (nextLine === "{") {
            searchStart = classStartIndex + 2;
            for (let j = searchStart; j < lines.length; j++) {
                if (lines[j].trim() === "}") {
                    classEndIndex = j;
                    break;
                }
            }
        } else {
            lines.splice(classStartIndex + 1, 0, "{");
            lines.splice(classStartIndex + 2, 0, `' @position_fixed(${x}, ${y})`);
            lines.splice(classStartIndex + 3, 0, "}");
            return;
        }
    } else {
        for (let j = searchStart; j < lines.length; j++) {
            if (lines[j].trim() === "}") {
                classEndIndex = j;
                break;
            }
        }
    }

    for (let j = searchStart; j < classEndIndex; j++) {
        const trimmed = lines[j].trim();
        if (trimmed.startsWith("' @position_fixed(")) {
            fixedIndex = j;
            break;
        }
    }

    if (fixedIndex !== -1) {
        lines[fixedIndex] = `' @position_fixed(${x}, ${y})`;
    } else {
        lines.splice(searchStart, 0, `' @position_fixed(${x}, ${y})`);
    }
}

// ====================================================================
// INICJALIZACJA INTERAKCJI SVG
// ====================================================================

function textInputHandler() {
    textMemento.saveState();
}

function initSvgInteractions() {
    if (!svgOutput.querySelector("svg")) return;

    if (textMemento && textMemento.reset) {
        textMemento.reset();
    }
    textMemento.saveState();

    if (memento) {
        memento.history.length = 0;
        memento.redoStack.length = 0;
    }

    textInput.removeEventListener("input", textInputHandler);
    textInput.addEventListener("input", textInputHandler);
}

// Funkcja do ponownej inicjalizacji interakcji SVG po aktualizacji
function setupSvgInteractions() {
    initSvgInteractions();
}

// ====================================================================
// INICJALIZACJA GŁÓWNA
// ====================================================================

document.addEventListener("DOMContentLoaded", async () => {
    console.log("DOM fully loaded and parsed");

    // B. Mapowanie elementów DOM
    const form = document.querySelector("form");
    form.addEventListener("submit", (e) => {
        e.preventDefault();
    });

    textInput = document.getElementById("text-input");
    svgOutput = document.getElementById("svg-output");
    diagramTypeSelect = document.getElementById("diagram-type");
    layoutTypeSelect = document.getElementById("layout-type");
    edgeTypeSelect = document.getElementById("edge-type");
    configButton = document.getElementById("config-button");
    configModal = document.getElementById("config-modal");
    applyConfigButton = document.getElementById("apply-config");
    renderButton = document.getElementById("render-button");
    saveButton = document.getElementById("save-button");

    // C. Inicjalizacja Memento
    memento = createSvgMemento(
        svgOutput,
        (group, dx, dy) => moveGroup(group, dx, dy, textInput),
        movePath
    );
    textMemento = createTextMemento(textInput);

    // D. Parsowanie i Inicjalizacja Stanu z URL
    const urlParams = new URLSearchParams(window.location.search);
    let initialParams = collectCurrentParams(
        currentConfig,
        configTemplates,
        textInput,
        diagramTypeSelect,
        layoutTypeSelect,
        edgeTypeSelect
    );

    if (urlParams.has("compressed")) {
        try {
            const decompressed = decompressData(urlParams.get("compressed"));
            initialParams = { ...initialParams, ...decompressed };
            currentConfig = initialParams.config || {};
        } catch (error) {
            console.error("Decompression error:", error);
        }
    }

    // E. Pierwsze renderowanie
    renderConfigFields(initialParams.layoutType, configTemplates, currentConfig);

    // Inicjalizacja interakcji SVG jeśli SVG już jest załadowane
    if (svgOutput.querySelector("svg")) {
        initSvgInteractions();
    }

    // F. Event Listenery (UI)
    const loadingOverlay = document.getElementById("loading-overlay");

    const showLoader = () => {
        if (loadingOverlay) {
            loadingOverlay.classList.add("active");
        }
    };

    const hideLoader = () => {
        if (loadingOverlay) {
            loadingOverlay.classList.remove("active");
        }
    };

    const sendRequest = async () => {
        showLoader();

        const cleanedConfig = {};
        for (const key in currentConfig) {
            cleanedConfig[key] = String(currentConfig[key]);
        }

        const params = collectCurrentParams(
            cleanedConfig,
            configTemplates,
            textInput,
            diagramTypeSelect,
            layoutTypeSelect,
            edgeTypeSelect
        );

        const compressed = compressData(params);

        // Twórz nowy URL z compressed
        const url = new URL(window.location.origin + window.location.pathname);
        url.searchParams.set("compressed", compressed);
        url.searchParams.set("_t", Date.now()); // Timestamp to prevent caching
        window.location.href = url.toString();
        hideLoader();
    };

    const renderHandler = sendRequest;

    // Fix Position Button - definicja przed użyciem
    const fixPositionButton = document.getElementById('fix-position-button');

    // Funkcja do włączania/wyłączania kontrolek w zależności od typu diagramu
    const updateControlsState = () => {
        const isActivity = diagramTypeSelect.value === 'activity';

        layoutTypeSelect.disabled = isActivity;
        edgeTypeSelect.disabled = isActivity;
        configButton.disabled = isActivity;

        if (fixPositionButton) {
            fixPositionButton.disabled = isActivity;
        }
    };

    // Event listenery dla selectów - tylko aktualizują dyrektywy w tekście
    diagramTypeSelect.addEventListener("change", () => {
        updateDirective(diagramTypeSelect, "diagram_type");
        updateControlsState();
    });

    layoutTypeSelect.addEventListener("change", () => {
        updateDirective(layoutTypeSelect, "layout_type");
    });

    edgeTypeSelect.addEventListener("change", () => {
        updateDirective(edgeTypeSelect, "edge_type");
    });

    // Inicjalizacja stanu kontrolek przy załadowaniu
    updateControlsState();

    renderButton.addEventListener("click", renderHandler);
    saveButton.addEventListener("click", () => saveSvgToFile(svgOutput));

    // Fix Position Button listener
    if (fixPositionButton) {
        fixPositionButton.addEventListener('click', () => {
            const isActivity = diagramTypeSelect.value === 'activity';
            if (isActivity) return; // Zablokuj dla activity diagram

            snapToCurrentPositions();
        });
    }

    // Modal Config
    configButton.addEventListener("click", () => {
        const isActivity = diagramTypeSelect.value === 'activity';
        if (isActivity) return; // Zablokuj dla activity diagram

        renderConfigFields(layoutTypeSelect.value, configTemplates, currentConfig);
        configModal.style.display = "flex";
    });

    applyConfigButton.addEventListener("click", () => {
        currentConfig = collectConfigDataFromModal(
            configTemplates,
            layoutTypeSelect
        );
        configModal.style.display = "none";
        renderHandler();
    });

    configModal.addEventListener("click", (e) => {
        if (e.target === configModal) {
            configModal.style.display = "none";
        }
    });

    // G. Event Listenery (Interakcja SVG/Textarea)
    document.addEventListener("mousedown", (e) => {
        if (e.target.closest("#svg-output")) {
            isSvgActive = true;
            isTextInputActive = false;
        } else if (e.target.closest("#text-input")) {
            isTextInputActive = true;
            isSvgActive = false;
            selectedGroup = deselectGroup(selectedGroup);
        } else {
            isSvgActive = false;
            isTextInputActive = false;
        }

        let targetGroup = e.target.closest("g");
        if (targetGroup && targetGroup.querySelector("rect")) {
            // Sprawdź czy rect ma stroke (nie jest labelką)
            const rect = targetGroup.querySelector("rect");
            const hasStroke = rect && rect.getAttribute("stroke") !== "none";
            const isActivity = diagramTypeSelect.value === 'activity';

            if (hasStroke && !isActivity) {
                if (selectedGroup) {
                    selectedGroup.classList.remove("highlighted");
                }
                selectedGroup = targetGroup;
                selectedGroup.classList.add("highlighted");
            } else {
                selectedGroup = deselectGroup(selectedGroup);
            }
        } else {
            selectedGroup = deselectGroup(selectedGroup);
        }
    });

    // Przesuwanie strzałkami i Undo/Redo
    document.addEventListener("keydown", (e) => {
        if (e.ctrlKey) {
            if (e.key === "z") {
                e.preventDefault();
                if (isTextInputActive) {
                    textMemento.undo();
                } else if (isSvgActive) {
                    memento.undo();
                }
            } else if (e.key === "y") {
                e.preventDefault();
                if (isTextInputActive) {
                    textMemento.redo();
                } else if (isSvgActive) {
                    memento.redo();
                }
            }
        }

        if (!selectedGroup) return;

        const isActivity = diagramTypeSelect.value === 'activity';
        if (isActivity) return; // Zablokuj przesuwanie dla activity diagram

        let dX = 0,
            dY = 0;
        switch (e.key) {
            case "ArrowUp":
                dY = -5;
                break;
            case "ArrowDown":
                dY = 5;
                break;
            case "ArrowLeft":
                dX = -5;
                break;
            case "ArrowRight":
                dX = 5;
                break;
        }

        if (dX || dY) {
            const groupId = selectedGroup.getAttribute("data-id");
            memento.applyMove(groupId, dX, dY);

            lastMove.id = groupId;
            lastMove.dx += dX;
            lastMove.dy += dY;
        }
    });

    document.addEventListener("keyup", (e) => {
        if (
            ["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"].includes(e.key) &&
            selectedGroup != null &&
            lastMove.id === selectedGroup.getAttribute("data-id")
        ) {
            memento.saveMove(lastMove.id, lastMove.dx, lastMove.dy);
            lastMove = { id: null, dx: 0, dy: 0 };
        }
    });
});
