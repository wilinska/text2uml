// script.js - Main client application file
// Module imports (assuming they are loaded as script tags or through bundler)

// ====================================================================
// GLOBAL VARIABLES
// ====================================================================

// These files should be loaded as <script> tags in HTML:
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

// Variables for tracking activity
let isSvgActive = false;
let isTextInputActive = false;

// Memento instances
let memento;
let textMemento;

// ====================================================================
// DIRECTIVE MANAGEMENT FUNCTIONS
// ====================================================================

/**
 * Updates directive in PlantUML text
 */
function updateDirective(select, directivePrefix) {
    if (!textInput) return;

    let lines = textInput.value.split("\n");

    // Remove all lines starting with ' @<directivePrefix>
    const directiveStart = `' @${directivePrefix}`;
    lines = lines.filter(line => {
        const trimmed = line.trim();
        return !trimmed.startsWith(directiveStart);
    });

    // Find index of @startuml line
    const startUmlIndex = lines.findIndex(line => line.trim() === '@startuml');

    // Add new line after @startuml (or at the beginning if @startuml doesn't exist)
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
 * Initializes select based on directive in text
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
 * Snap to current positions - sets @position_fixed based on positions in SVG
 */
function snapToCurrentPositions() {
    if (!svgOutput || !textInput) {
        console.error("No SVG or textarea!");
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

        // If class not found, add new definition at the end, but before @enduml
        if (!found) {
            const newClassDefinition = [
                `class ${className} {`,
                `' @position_fixed(${x}, ${y})`,
                "}",
            ];

            // Check if @enduml exists
            const endUmlIndex = lines.findIndex((line) => line.trim() === "@enduml");

            if (endUmlIndex !== -1) {
                // Insert new class definition before @enduml
                lines.splice(endUmlIndex, 0, ...newClassDefinition);
            } else {
                // If @enduml doesn't exist, add at the end
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
// SVG INTERACTIONS INITIALIZATION
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

// Function to reinitialize SVG interactions after update
function setupSvgInteractions() {
    initSvgInteractions();
}

// ====================================================================
// MAIN INITIALIZATION
// ====================================================================

document.addEventListener("DOMContentLoaded", async () => {
    console.log("DOM fully loaded and parsed");

    // B. DOM element mapping
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

    // D. Parse and Initialize State from URL
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

    // E. First render
    renderConfigFields(initialParams.layoutType, initialParams.diagram_type, configTemplates, currentConfig);

    // Initialize SVG interactions if SVG is already loaded
    if (svgOutput.querySelector("svg")) {
        initSvgInteractions();
    }

    // F. Event Listeners (UI)
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
        console.log("Cleaned config before sending request:", cleanedConfig);

        const params = collectCurrentParams(
            cleanedConfig,
            configTemplates,
            textInput,
            diagramTypeSelect,
            layoutTypeSelect,
            edgeTypeSelect
        );

        const compressed = compressData(params);

        // Create new URL with compressed
        const url = new URL(window.location.origin + window.location.pathname);
        url.searchParams.set("compressed", compressed);
        url.searchParams.set("_t", Date.now()); // Timestamp to prevent caching
        window.location.href = url.toString();
        hideLoader();
    };

    const renderHandler = sendRequest;

    // Fix Position Button - definition before use
    const fixPositionButton = document.getElementById('fix-position-button');

    // Function to enable/disable controls depending on diagram type
    const updateControlsState = () => {
        const isActivity = diagramTypeSelect.value === 'activity';

        layoutTypeSelect.disabled = isActivity;
        edgeTypeSelect.disabled = isActivity;

        if (fixPositionButton) {
            fixPositionButton.disabled = isActivity;
        }
    };

    // Event listeners for selects - only update directives in text
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

    // Initialize controls state on load
    updateControlsState();

    renderButton.addEventListener("click", renderHandler);
    saveButton.addEventListener("click", () => saveSvgToFile(svgOutput));

    // Fix Position Button listener
    if (fixPositionButton) {
        fixPositionButton.addEventListener('click', () => {
            const isActivity = diagramTypeSelect.value === 'activity';
            if (isActivity) return; // Block for activity diagram

            snapToCurrentPositions();
        });
    }

    // Modal Config
    configButton.addEventListener("click", () => {
        renderConfigFields(layoutTypeSelect.value, diagramTypeSelect.value, configTemplates, currentConfig);
        configModal.style.display = "flex";
    });

    applyConfigButton.addEventListener("click", () => {
        currentConfig = collectConfigDataFromModal(
            configTemplates,
            layoutTypeSelect,
            diagramTypeSelect
        );
        configModal.style.display = "none";
        renderHandler();
    });

    configModal.addEventListener("click", (e) => {
        if (e.target === configModal) {
            configModal.style.display = "none";
        }
    });

    // G. Event Listeners (SVG/Textarea Interaction)
    document.addEventListener("mousedown", (e) => {
        if (e.target.closest("#svg-output")) {
            isSvgActive = true;
            isTextInputActive = true;
        } else if (e.target.closest("#text-input")) {
            isTextInputActive = true;
            isSvgActive = false;
            selectedGroup = deselectGroup(selectedGroup);
        } else {
            isSvgActive = false;
            isTextInputActive = true;
        }

        let targetGroup = e.target.closest("g");
        if (targetGroup && targetGroup.querySelector("rect")) {
            // Check if rect has stroke (not a label)
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

    // Arrow keys movement and Undo/Redo
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
        if (isActivity) return; // Block movement for activity diagram

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
