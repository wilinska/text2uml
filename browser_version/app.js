// ============================================================================
// TEXT2UML - Browser Application
// ============================================================================

console.log("Text2UML Browser App Starting...");


// ============================================================================
// KONFIGURACJA LAYOUTÓW
// ============================================================================

const configTemplates = {
    Circular: [
        { label: "minDistCircle", id: "minDistCircle", name: "minDistCircle", type: "number", min: 0, step: 1, defaultValue: 100 },
        { label: "minDistLevel", id: "minDistLevel", name: "minDistLevel", type: "number", min: 0, step: 1, defaultValue: 100 },
        { label: "minDistSibling", id: "minDistSibling", name: "minDistSibling", type: "number", min: 0, step: 1, defaultValue: 70 }
    ],
    FMMM: [
        { label: "useHighLevelOptions", id: "useHighLevelOptions", name: "useHighLevelOptions", type: "boolean", defaultValue: true },
        { label: "Unit Edge Length", id: "unitEdgeLength", name: "unitEdgeLength", type: "number", min: 0, step: 1, defaultValue: 75 },
        { label: "Page Ratio", id: "pageRatio", name: "pageRatio", type: "number", min: 0, step: 1, defaultValue: 1 },
        { label: "Fine Tune Scalar", id: "fineTuneScalar", name: "fineTuneScalar", type: "number", min: 0, step: 1, defaultValue: 0.2 },
        { label: "Galaxy Choice", id: "galaxy-choice", name: "galaxyChoice", type: "select", options: ["UniformProb", "NonUniformProbHigherMass", "NonUniformProbLowerMass"], defaultValue: "NonUniformProbLowerMass" },
    ],
    OptimalHierarchy: [
        { label: "Layer Distance", id: "layerDistance", name: "layerDistance", type: "number", min: 0, step: 1, defaultValue: 30 },
        { label: "Node Distance", id: "nodeDistance", name: "nodeDistance", type: "number", min: 0, step: 1, defaultValue: 25 },
        { label: "Weight Balancing", id: "weightBalancing", name: "weightBalancing", type: "number", min: 0, max: 1, step: 0.1, defaultValue: 0.8 }
    ],
    Orthogonal: [],
    Sugiyama: [
        { label: "Distance between layers", id: "layer-distance", name: "layerDistance", type: "number", min: 0, step: 1, defaultValue: 50 },
        { label: "Distance between nodes", id: "node-distance", name: "nodeDistance", type: "number", min: 0, step: 1, defaultValue: 30 },
        { label: "Ranking type", id: "ranking-type", name: "rankingType", type: "select", options: ["OptimalRanking", "LongestPathRanking", "CoffmanGrahamRanking"], defaultValue: "OptimalRanking" },
        { label: "CrossMin algorithm type", id: "cross-type", name: "crossType", type: "select", options: ["MedianHeuristic", "BarycenterHeuristic", "GreedyInsertHeuristic"], defaultValue: "MedianHeuristic" }
    ],
    Tree: [],
};

// ============================================================================
// FUNKCJE KOMPRESJI (pako)
// ============================================================================

function compressData(data) {
    const compressed = pako.deflate(JSON.stringify(data), { to: 'string' });
    return btoa(String.fromCharCode.apply(null, compressed));
}

function decompressData(compressedData) {
    const compressed = atob(compressedData).split('').map(c => c.charCodeAt(0));
    return JSON.parse(pako.inflate(new Uint8Array(compressed), { to: 'string' }));
}

// ============================================================================
// FUNKCJE SVG INTERACTIONS
// ============================================================================

function deselectGroup(selectedGroup) {
    if (selectedGroup) {
        selectedGroup.classList.remove("highlighted");
    }
    return null;
}

function addCommentToMatchingLine(className, dx, dy, textInput) {
    let lines = textInput.value.split("\n");
    let found = false;

    for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();

        if (line.startsWith("class ") || line.startsWith("abstract ") || line.startsWith("interface ")) {
            const name = line.split(" ")[1];
            if (name === className) {
                found = true;
                const hasBraces = line.includes("{");

                if (hasBraces) {
                    let fixedPositionIndex = -1;
                    let positionIndex = -1;
                    for (let j = i + 1; j < lines.length; j++) {
                        if (lines[j].trim().startsWith("' @position_fixed(")) {
                            fixedPositionIndex = j;
                            break;
                        }
                        if (lines[j].trim().startsWith("' @position(")) {
                            positionIndex = j;
                        }
                        if (lines[j].trim() === "}") break;
                    }

                    if (fixedPositionIndex !== -1) {
                        const fixedLine = lines[fixedPositionIndex].trim();
                        const fixedRegex = /' @position_fixed\(([-]?\d*\.?\d+),\s*([-]?\d*\.?\d+)\)/;
                        const fixedMatch = fixedLine.match(fixedRegex);
                        if (fixedMatch) {
                            const currentFixedX = parseFloat(fixedMatch[1]);
                            const currentFixedY = parseFloat(fixedMatch[2]);
                            lines[fixedPositionIndex] = `' @position_fixed(${currentFixedX + dx}, ${currentFixedY + dy})`;
                        }
                    } else if (positionIndex !== -1) {
                        const positionLine = lines[positionIndex].trim();
                        const regex = /' @position\(([-]?\d*\.?\d+),\s*([-]?\d*\.?\d+)\)/;
                        const match = positionLine.match(regex);
                        if (match) {
                            const currentDx = parseFloat(match[1]);
                            const currentDy = parseFloat(match[2]);
                            lines[positionIndex] = `' @position(${currentDx + dx}, ${currentDy + dy})`;
                        }
                    } else {
                        const parts = line.split("{");
                        lines[i] = parts[0] + "{";
                        lines.splice(i + 1, 0, `' @position(${dx}, ${dy})`);
                        if (parts[1]) lines.splice(i + 2, 0, parts[1]);
                    }
                } else {
                    const nextLine = lines[i + 1]?.trim();
                    if (nextLine === "{") {
                        let fixedPositionIndex = -1;
                        let positionIndex = -1;
                        for (let j = i + 2; j < lines.length; j++) {
                            if (lines[j].trim().startsWith("' @position_fixed(")) {
                                fixedPositionIndex = j;
                                break;
                            }
                            if (lines[j].trim().startsWith("' @position(")) {
                                positionIndex = j;
                            }
                            if (lines[j].trim() === "}") break;
                        }

                        if (fixedPositionIndex !== -1) {
                            const fixedLine = lines[fixedPositionIndex].trim();
                            const fixedRegex = /' @position_fixed\(([-]?\d*\.?\d+),\s*([-]?\d*\.?\d+)\)/;
                            const fixedMatch = fixedLine.match(fixedRegex);
                            if (fixedMatch) {
                                const currentFixedX = parseFloat(fixedMatch[1]);
                                const currentFixedY = parseFloat(fixedMatch[2]);
                                lines[fixedPositionIndex] = `' @position_fixed(${currentFixedX + dx}, ${currentFixedY + dy})`;
                            }
                        } else if (positionIndex !== -1) {
                            const positionLine = lines[positionIndex].trim();
                            const positionRegex = /' @position\(([-]?\d*\.?\d+),\s*([-]?\d*\.?\d+)\)/;
                            const positionMatch = positionLine.match(positionRegex);
                            if (positionMatch) {
                                const currentDx = parseFloat(positionMatch[1]);
                                const currentDy = parseFloat(positionMatch[2]);
                                lines[positionIndex] = `' @position(${currentDx + dx}, ${currentDy + dy})`;
                            }
                        } else {
                            lines.splice(i + 2, 0, `' @position(${dx}, ${dy})`);
                        }
                    } else {
                        lines.splice(i + 1, 0, "{");
                        lines.splice(i + 2, 0, `' @position(${dx}, ${dy})`);
                        lines.splice(i + 3, 0, "}");
                    }
                }
                break;
            }
        }
    }

    if (!found) {
        const newClassDefinition = [
            `class ${className} {`,
            `' @position(${dx}, ${dy})`,
            "}",
        ];
        const endUmlIndex = lines.findIndex((line) => line.trim() === "@enduml");
        if (endUmlIndex !== -1) {
            lines.splice(endUmlIndex, 0, ...newClassDefinition);
        } else {
            lines.push(...newClassDefinition);
        }
    }

    textInput.value = lines.join("\n");
}

function moveGroup(group, dx, dy, textInput) {
    if (group) {
        const children = group.children;
        for (let i = 0; i < children.length; i++) {
            const child = children[i];
            if (child.tagName === "rect") {
                child.setAttribute("x", parseFloat(child.getAttribute("x")) + dx);
                child.setAttribute("y", parseFloat(child.getAttribute("y")) + dy);
            } else if (child.tagName === "text") {
                child.setAttribute("x", parseFloat(child.getAttribute("x")) + dx);
                child.setAttribute("y", parseFloat(child.getAttribute("y")) + dy);
            } else if (child.tagName === "circle") {
                child.setAttribute("cx", parseFloat(child.getAttribute("cx")) + dx);
                child.setAttribute("cy", parseFloat(child.getAttribute("cy")) + dy);
            } else if (child.tagName === "line") {
                child.setAttribute("x1", parseFloat(child.getAttribute("x1")) + dx);
                child.setAttribute("x2", parseFloat(child.getAttribute("x2")) + dx);
                child.setAttribute("y1", parseFloat(child.getAttribute("y1")) + dy);
                child.setAttribute("y2", parseFloat(child.getAttribute("y2")) + dy);
            }
        }

        const textElement = group.querySelector("text");
        if (textElement && textInput) {
            const className = textElement.textContent.trim();
            addCommentToMatchingLine(className, dx, dy, textInput);
        }
    }
}

function movePath(path, dx, dy, isSource) {
    const d = path.getAttribute("d");
    const commands = d.split(/(?=[MmLlHhVvCcSsQqTtAaZz])/);
    if (commands.length < 2) return;

    const modifyCoords = (command, offset) => {
        const commandType = command[0];
        const coords = command.slice(1).split(/[\s,]+/).map(parseFloat).filter((num) => !isNaN(num));

        if (coords.length >= 2) {
            coords[offset] += dx;
            coords[offset + 1] += dy;
            return commandType + coords.join(" ");
        }
        return command;
    };

    if (isSource) {
        commands[0] = modifyCoords(commands[0], 0);
    } else {
        const lastIndex = commands.length - 1;
        const lastCommandType = commands[lastIndex][0].toUpperCase();

        if (lastCommandType === "L" || lastCommandType === "M") {
            commands[lastIndex] = modifyCoords(commands[lastIndex], 0);
        } else if (["C", "S", "Q", "T"].includes(lastCommandType)) {
            const numCoords = commands[lastIndex].slice(1).split(/[\s,]+/).filter((c) => c !== "").length;
            commands[lastIndex] = modifyCoords(commands[lastIndex], numCoords - 2);
        }
    }

    path.setAttribute("d", commands.join(" "));
}

function saveSvgToFile(svgOutput) {
    const svgElement = svgOutput.querySelector("svg");
    if (!svgElement) {
        alert("No SVG content to save!");
        return;
    }

    const serializer = new XMLSerializer();
    const svgString = serializer.serializeToString(svgElement);
    const blob = new Blob([svgString], { type: "image/svg+xml" });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = "diagram.svg";
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
}

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

        // Znajdź klasę w kodzie i dodaj/zaktualizuj @position_fixed
        let found = false;
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim();
            if (line.startsWith("class ") || line.startsWith("abstract ") || line.startsWith("interface ")) {
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

// ============================================================================
// FUNKCJE CONFIG MODAL
// ============================================================================

function collectConfigDataFromModal(layoutTypeSelect) {
    const config = {};
    const layoutType = layoutTypeSelect.value;
    const fields = configTemplates[layoutType] || [];

    fields.forEach((field) => {
        const element = document.getElementById(field.id);
        if (!element) return;

        if (field.type === "boolean") {
            config[field.name] = element.checked;
        } else if (field.type === "number" || field.type === "select") {
            config[field.name] = element.value;
        }
    });
    return config;
}

function collectCurrentParams(currentConfig, textInput, diagramTypeSelect, layoutTypeSelect, edgeTypeSelect) {
    const layoutType = layoutTypeSelect.value;
    const config = {};
    const fields = configTemplates[layoutType] || [];

    fields.forEach((field) => {
        config[field.name] = currentConfig[field.name] !== undefined ? currentConfig[field.name] : field.defaultValue;
    });

    return {
        text: textInput.value,
        diagramType: diagramTypeSelect.value,
        layoutType: layoutType,
        edgeType: edgeTypeSelect.value,
        config: config,
    };
}

function renderConfigFields(layoutType, currentConfig) {
    const modalTitle = document.getElementById("modal-title");
    const container = document.getElementById("modal-fields-container");
    container.innerHTML = "";

    modalTitle.textContent = `Configuration for ${layoutType}`;
    const fields = configTemplates[layoutType] || [];

    fields.forEach((field) => {
        const value = currentConfig[field.name];
        const finalValue = value !== undefined ? value : field.defaultValue;

        const label = document.createElement("label");
        label.setAttribute("for", field.id);
        label.textContent = `${field.label}:`;
        container.appendChild(label);

        if (field.type === "number") {
            const input = document.createElement("input");
            input.type = "number";
            input.id = field.id;
            input.name = field.name;
            input.min = field.min;
            input.step = field.step;
            input.value = finalValue;
            container.appendChild(input);
        } else if (field.type === "select") {
            const select = document.createElement("select");
            select.id = field.id;
            select.name = field.name;
            field.options.forEach((option) => {
                const optionEl = document.createElement("option");
                optionEl.value = option;
                optionEl.textContent = option;
                if (option === finalValue) {
                    optionEl.selected = true;
                }
                select.appendChild(optionEl);
            });
            container.appendChild(select);
        } else if (field.type === "boolean") {
            const input = document.createElement("input");
            input.type = "checkbox";
            input.id = field.id;
            input.name = field.name;
            const isChecked = finalValue === true || finalValue === "on";
            if (isChecked) {
                input.checked = true;
            }
            container.appendChild(input);
        }
    });
}

// ============================================================================
// FUNKCJE MEMENTO (undo/redo)
// ============================================================================

function createSvgMemento(svgOutput, moveGroupFunc, movePathFunc) {
    const history = [];
    const redoStack = [];

    return {
        history,
        redoStack,

        saveMove(groupId, dx, dy) {
            if (dx === 0 && dy === 0) return;
            this.history.push({ groupId, dx, dy });
            this.redoStack.length = 0;
        },

        undo() {
            if (this.history.length === 0) return;
            const { groupId, dx, dy } = this.history.pop();
            this.redoStack.push({ groupId, dx: -dx, dy: -dy });
            this.applyMove(groupId, -dx, -dy);
        },

        redo() {
            if (this.redoStack.length === 0) return;
            const { groupId, dx, dy } = this.redoStack.pop();
            this.history.push({ groupId, dx, dy });
            this.applyMove(groupId, dx, dy);
        },

        applyMove(groupId, dx, dy) {
            const group = svgOutput.querySelector(`g[data-id="${groupId}"]`);
            if (group) {
                const textInput = document.getElementById('text-input');
                moveGroupFunc(group, dx, dy, textInput);

                const source_groups = svgOutput.querySelectorAll(`g[data-source="${groupId}"]`);
                source_groups.forEach((g) => {
                    const paths = g.querySelectorAll("path");
                    if (paths.length > 0) movePathFunc(paths[0], dx, dy, true);
                    if (paths.length > 1) movePathFunc(paths[1], dx, dy, false);
                });

                const target_groups = svgOutput.querySelectorAll(`g[data-target="${groupId}"]`);
                target_groups.forEach((g) => {
                    const paths = g.querySelectorAll("path");
                    if (paths.length > 0) movePathFunc(paths[0], dx, dy, false);
                    if (paths.length > 1) movePathFunc(paths[1], dx, dy, true);
                });
            }
        },
    };
}

function createTextMemento(textInput) {
    const history = [];
    const redoStack = [];

    return {
        history,
        redoStack,

        saveState() {
            const currentText = textInput.value;
            if (this.history.length === 0 || this.history[this.history.length - 1] !== currentText) {
                this.history.push(currentText);
                this.redoStack.length = 0;
            }
        },

        undo() {
            if (this.history.length > 1) {
                const currentState = this.history.pop();
                this.redoStack.push(currentState);
                textInput.value = this.history[this.history.length - 1];
            }
        },

        redo() {
            if (this.redoStack.length > 0) {
                const nextState = this.redoStack.pop();
                this.history.push(nextState);
                textInput.value = nextState;
            }
        },

        reset() {
            this.history.length = 0;
            this.redoStack.length = 0;
        },
    };
}

// ============================================================================
// FUNKCJE WASM & GENEROWANIE DIAGRAMÓW
// ============================================================================

async function initWasm(Text2UML) {
    try {
        const wasmModule = await Text2UML();
        return wasmModule;
    } catch (err) {
        console.error("Błąd inicjalizacji WASM:", err);
        throw err;
    }
}

function splitAtFirstSpace(str) {
    const index = str.indexOf(' ');

    // Jeśli nie ma spacji, zwróć cały string jako pierwszy element
    if (index === -1) return [str, ""];

    const firstPart = str.slice(0, index);
    const secondPart = str.slice(index + 1);

    return [firstPart, secondPart];
}

function generateDiagram(params, wasmModule, svgOutput, setupSvgInteractionsFunc) {
    if (!wasmModule) {
        console.error("WASM module not initialized.");
        return;
    }

    // Aktualizacja URL
    const dataToCompress = { ...params };
    const compressed = compressData(dataToCompress);
    const url = new URL(window.location.href);
    url.searchParams.set("compressed", compressed);
    window.history.pushState(dataToCompress, "", url.toString());

    // Generowanie SVG
    svgOutput.innerHTML = "";
    if (params.text.length === 0) return;

    try {
        const strConfig = {};
        for (const key in params.config) {
            strConfig[key] = String(params.config[key]);
        }

        const configString = JSON.stringify(strConfig || {});
        const result = wasmModule.Generator.generate(
            params.text,
            params.diagramType,
            params.layoutType,
            params.edgeType,
            configString
        );
        const [diagram_type, diagram_svg] = splitAtFirstSpace(result);

        // Aktualizuj select jeśli typ się zmienił
        if (diagram_type && diagram_type !== params.diagramType) {
            const diagramSelect = document.getElementById('diagram-type');
            if (diagramSelect) {
                diagramSelect.value = diagram_type;
                // Zaktualizuj stan kontrolek
                const isActivity = diagram_type === 'activity';
                const layoutSelect = document.getElementById('layout-type');
                const edgeSelect = document.getElementById('edge-type');
                const configBtn = document.getElementById('config-button');
                if (layoutSelect) layoutSelect.disabled = isActivity;
                if (edgeSelect) edgeSelect.disabled = isActivity;
                if (configBtn) configBtn.disabled = isActivity;
            }
        }

        svgOutput.innerHTML = diagram_svg;

        if (setupSvgInteractionsFunc) {
            setupSvgInteractionsFunc();
        }
    } catch (error) {
        console.error("Generate error:", error.message);
        svgOutput.innerHTML = `<p style="color: red;">Błąd generowania: ${error.message}</p>`;
    }
}

// ============================================================================
// GŁÓWNA APLIKACJA
// ============================================================================

function updateLayoutTypeInCode() {
    if (!textInput || !layoutTypeSelect) return;

    const layoutType = layoutTypeSelect.value;
    let lines = textInput.value.split("\n");
    let layoutLineIndex = -1;
    let startumlIndex = -1;

    // Znajdź linię @startuml i istniejącą linię @layout_type
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();
        if (line === "@startuml") {
            startumlIndex = i;
        }
        if (line.startsWith("' @layout_type")) {
            layoutLineIndex = i;
            break;
        }
    }

    const newLayoutLine = `' @layout_type ${layoutType}`;

    // Jeśli istnieje linia z @layout_type, zaktualizuj ją
    if (layoutLineIndex !== -1) {
        lines[layoutLineIndex] = newLayoutLine;
    } else if (startumlIndex !== -1) {
        // Jeśli nie ma, dodaj po @startuml
        lines.splice(startumlIndex + 1, 0, newLayoutLine);
    } else {
        // Jeśli nie ma @startuml, dodaj na początku
        lines.unshift(newLayoutLine);
    }

    textInput.value = lines.join("\n");
}

function updateEdgeTypeInCode() {
    if (!textInput || !edgeTypeSelect) return;

    const edgeType = edgeTypeSelect.value;
    let lines = textInput.value.split("\n");
    let edgeLineIndex = -1;
    let startumlIndex = -1;

    // Znajdź linię @startuml i istniejącą linię @edge_type
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();
        if (line === "@startuml") {
            startumlIndex = i;
        }
        if (line.startsWith("' @edge_type")) {
            edgeLineIndex = i;
            break;
        }
    }

    const newEdgeLine = `' @edge_type ${edgeType}`;

    // Jeśli istnieje linia z @edge_type, zaktualizuj ją
    if (edgeLineIndex !== -1) {
        lines[edgeLineIndex] = newEdgeLine;
    } else if (startumlIndex !== -1) {
        // Jeśli nie ma, dodaj po @startuml (lub po @layout_type jeśli istnieje)
        let insertIndex = startumlIndex + 1;
        for (let i = startumlIndex + 1; i < lines.length; i++) {
            if (lines[i].trim().startsWith("' @layout_type")) {
                insertIndex = i + 1;
                break;
            }
            if (!lines[i].trim().startsWith("'")) {
                break;
            }
        }
        lines.splice(insertIndex, 0, newEdgeLine);
    } else {
        // Jeśli nie ma @startuml, dodaj na początku
        lines.unshift(newEdgeLine);
    }

    textInput.value = lines.join("\n");
}

let wasmModule = null;
let currentConfig = {};
let selectedGroup = null;
let lastMove = { id: null, dx: 0, dy: 0 };
let isSvgActive = false;
let isTextInputActive = false;

let textInput, svgOutput, diagramTypeSelect, layoutTypeSelect, edgeTypeSelect;
let configButton, configModal, applyConfigButton, renderButton, saveButton;
let memento, textMemento;

function updateControlsState() {
    const isActivity = diagramTypeSelect.value === 'activity';
    layoutTypeSelect.disabled = isActivity;
    edgeTypeSelect.disabled = isActivity;
    configButton.disabled = isActivity;
    if (isActivity) isSvgActive = false;
}

function setupSvgInteractions() {
    const groups = svgOutput.querySelectorAll("g[data-id]");

    groups.forEach((group) => {
        let isDragging = false;
        let startX = 0, startY = 0;
        let currentDx = 0, currentDy = 0;

        group.addEventListener("mousedown", (e) => {
            if (!isSvgActive || diagramTypeSelect.value === 'activity') return;

            isDragging = true;
            startX = e.clientX;
            startY = e.clientY;
            currentDx = 0;
            currentDy = 0;

            selectedGroup = deselectGroup(selectedGroup);
            selectedGroup = group;
            selectedGroup.classList.add("highlighted");
            e.preventDefault();
        });

        document.addEventListener("mousemove", (e) => {
            if (!isDragging) return;

            const dx = e.clientX - startX;
            const dy = e.clientY - startY;
            const deltaDx = dx - currentDx;
            const deltaDy = dy - currentDy;

            moveGroup(group, deltaDx, deltaDy, textInput);

            const groupId = group.getAttribute("data-id");
            const sourceGroups = svgOutput.querySelectorAll(`g[data-source="${groupId}"]`);
            sourceGroups.forEach((g) => {
                const paths = g.querySelectorAll("path");
                if (paths.length > 0) movePath(paths[0], deltaDx, deltaDy, true);
                if (paths.length > 1) movePath(paths[1], deltaDx, deltaDy, false);
            });

            const targetGroups = svgOutput.querySelectorAll(`g[data-target="${groupId}"]`);
            targetGroups.forEach((g) => {
                const paths = g.querySelectorAll("path");
                if (paths.length > 0) movePath(paths[0], deltaDx, deltaDy, false);
                if (paths.length > 1) movePath(paths[1], deltaDx, deltaDy, true);
            });

            currentDx = dx;
            currentDy = dy;
        });

        document.addEventListener("mouseup", () => {
            if (!isDragging) return;
            isDragging = false;

            if (currentDx !== 0 || currentDy !== 0) {
                const groupId = group.getAttribute("data-id");
                memento.saveMove(groupId, currentDx, currentDy);
                lastMove = { id: groupId, dx: currentDx, dy: currentDy };
            }
        });
    });
}

function renderDiagram() {
    const params = collectCurrentParams(currentConfig, textInput, diagramTypeSelect, layoutTypeSelect, edgeTypeSelect);
    generateDiagram(params, wasmModule, svgOutput, setupSvgInteractions);
}

function loadFromURL() {
    const urlParams = new URLSearchParams(window.location.search);
    const compressed = urlParams.get("compressed");

    if (compressed) {
        try {
            const data = decompressData(compressed);
            textInput.value = data.text || "";
            diagramTypeSelect.value = data.diagramType || "auto";
            layoutTypeSelect.value = data.layoutType || "Sugiyama";
            edgeTypeSelect.value = data.edgeType || "Bends";
            currentConfig = data.config || {};
            textMemento.saveState();
            renderDiagram();
        } catch (error) {
            console.error("Błąd dekompresji URL:", error);
        }
    }
}

// ============================================================================
// INICJALIZACJA
// ============================================================================

document.addEventListener("DOMContentLoaded", async () => {
    console.log("DOM loaded");

    // Pobierz elementy DOM
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

    // Inicjalizuj WASM
    try {
        wasmModule = await initWasm(Text2UML);
    } catch (error) {
        console.error("Błąd ładowania WASM:", error);
        svgOutput.innerHTML = '<p style="color: red;">Błąd ładowania WASM: ' + error.message + '</p>';
        return;
    }

    // Inicjalizuj memento
    memento = createSvgMemento(svgOutput, moveGroup, movePath);
    textMemento = createTextMemento(textInput);

    // Załaduj z URL lub wygeneruj początkowy diagram
    const urlParams = new URLSearchParams(window.location.search);
    if (urlParams.has("compressed")) {
        loadFromURL();
    } else if (textInput.value.trim()) {
        textMemento.saveState();
        renderDiagram();
    }

    // Event listenery
    renderButton.addEventListener("click", () => {
        textMemento.saveState();
        renderDiagram();
    });

    saveButton.addEventListener("click", () => saveSvgToFile(svgOutput));

    const fixPositionButton = document.getElementById("fix-position-button");
    if (fixPositionButton) {
        fixPositionButton.addEventListener("click", () => {
            snapToCurrentPositions();
            renderDiagram();
        });
    }

    configButton.addEventListener("click", () => {
        if (diagramTypeSelect.value === 'activity') return;
        renderConfigFields(layoutTypeSelect.value, currentConfig);
        configModal.style.display = "flex";
    });

    applyConfigButton.addEventListener("click", () => {
        currentConfig = collectConfigDataFromModal(layoutTypeSelect);
        configModal.style.display = "none";
        textMemento.saveState();
        renderDiagram();
    });

    configModal.addEventListener("click", (e) => {
        if (e.target === configModal) {
            configModal.style.display = "none";
        }
    });

    diagramTypeSelect.addEventListener("change", updateControlsState);
    layoutTypeSelect.addEventListener("change", () => {
        currentConfig = {};
        updateLayoutTypeInCode();
    });
    edgeTypeSelect.addEventListener("change", () => {
        updateEdgeTypeInCode();
    });    // Śledzenie aktywności
    textInput.addEventListener("focus", () => {
        isTextInputActive = true;
        isSvgActive = false;
    });

    svgOutput.addEventListener("click", () => {
        if (diagramTypeSelect.value !== 'activity') {
            isSvgActive = true;
            isTextInputActive = false;
        }
    });

    // Undo/Redo
    document.addEventListener("keydown", (e) => {
        if (e.ctrlKey && e.key === "z") {
            e.preventDefault();
            if (isSvgActive) memento.undo();
            else if (isTextInputActive) textMemento.undo();
        } else if (e.ctrlKey && e.key === "y") {
            e.preventDefault();
            if (isSvgActive) memento.redo();
            else if (isTextInputActive) textMemento.redo();
        }

        // Przesuwanie strzałkami
        if (!selectedGroup || diagramTypeSelect.value === 'activity') return;

        let dX = 0, dY = 0;
        switch (e.key) {
            case "ArrowUp": dY = -5; break;
            case "ArrowDown": dY = 5; break;
            case "ArrowLeft": dX = -5; break;
            case "ArrowRight": dX = 5; break;
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
        if (["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"].includes(e.key) &&
            selectedGroup && lastMove.id === selectedGroup.getAttribute("data-id")) {
            memento.saveMove(lastMove.id, lastMove.dx, lastMove.dy);
            lastMove = { id: null, dx: 0, dy: 0 };
        }
    });

    // Deselect
    document.addEventListener("click", (e) => {
        if (!e.target.closest("g[data-id]") && isSvgActive) {
            selectedGroup = deselectGroup(selectedGroup);
        }
    });

    updateControlsState();
});
