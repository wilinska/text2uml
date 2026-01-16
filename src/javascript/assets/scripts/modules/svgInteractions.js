/**
 * Moduł zarządzający interakcjami z elementami SVG
 */

/**
 * Usuwa zaznaczenie z grupy SVG
 * @param {HTMLElement} selectedGroup - Aktualnie zaznaczona grupa
 * @returns {null}
 */
function deselectGroup(selectedGroup) {
    if (selectedGroup) {
        selectedGroup.classList.remove("highlighted");
    }
    return null;
}

/**
 * Dodaje lub aktualizuje komentarz @position w PlantUML
 * @param {string} className - Nazwa klasy do znalezienia
 * @param {number} dx - Przesunięcie w osi X
 * @param {number} dy - Przesunięcie w osi Y
 * @param {HTMLTextAreaElement} textInput - Element textarea z kodem PlantUML
 */
function addCommentToMatchingLine(className, dx, dy, textInput) {
    let lines = textInput.value.split("\n");
    let found = false;

    // Przeszukaj linijki w poszukiwaniu klasy
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();

        // Sprawdź, czy linijka zawiera definicję klasy
        if (
            line.startsWith("class ") ||
            line.startsWith("abstract ") ||
            line.startsWith("interface ")
        ) {
            const name = line.split(" ")[1];
            if (name === className) {
                found = true;

                // Sprawdź, czy klasa ma nawiasy
                const hasBraces = line.includes("{");

                if (hasBraces) {
                    // Jeśli nawiasy są w tej samej linii, sprawdź @position_fixed lub @position
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
                        if (lines[j].trim() === "}") {
                            break;
                        }
                    }

                    // Priorytet: modyfikuj @position_fixed
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
                    // Sprawdź, czy następna linia zawiera nawias
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

    // Jeśli nie znaleziono klasy, dodaj nową definicję na końcu, ale przed @enduml
    if (!found) {
        const newClassDefinition = [
            `class ${className} {`,
            `' @position(${dx}, ${dy})`,
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

    // Zaktualizuj tekst w textarea
    textInput.value = lines.join("\n");
}

/**
 * Przesuwa grupę SVG o podane wartości
 * @param {HTMLElement} group - Grupa SVG do przesunięcia
 * @param {number} dx - Przesunięcie w osi X
 * @param {number} dy - Przesunięcie w osi Y
 * @param {HTMLTextAreaElement} textInput - Element textarea z kodem PlantUML
 */
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

/**
 * Przesuwa ścieżkę SVG (strzałkę)
 * @param {SVGPathElement} path - Element path do przesunięcia
 * @param {number} dx - Przesunięcie w osi X
 * @param {number} dy - Przesunięcie w osi Y
 * @param {boolean} isSource - Czy modyfikować punkt początkowy (true) czy końcowy (false)
 */
function movePath(path, dx, dy, isSource) {
    const d = path.getAttribute("d");
    const commands = d.split(/(?=[MmLlHhVvCcSsQqTtAaZz])/);
    if (commands.length < 2) return;

    // Funkcja pomocnicza do parsowania i modyfikacji koordynat
    const modifyCoords = (command, offset) => {
        const commandType = command[0];
        const coords = command
            .slice(1)
            .split(/[\s,]+/)
            .map(parseFloat)
            .filter((num) => !isNaN(num));

        if (coords.length >= 2) {
            coords[offset] += dx;
            coords[offset + 1] += dy;
            return commandType + coords.join(" ");
        }
        return command;
    };

    if (isSource) {
        // Pierwszy punkt (M) - modyfikujemy pierwsze dwie współrzędne
        commands[0] = modifyCoords(commands[0], 0);
    } else {
        // Ostatni punkt (L lub ostatnia para w C/S/Q/T) - modyfikujemy ostatnie dwie współrzędne
        const lastIndex = commands.length - 1;
        const lastCommandType = commands[lastIndex][0].toUpperCase();

        if (lastCommandType === "L" || lastCommandType === "M") {
            commands[lastIndex] = modifyCoords(commands[lastIndex], 0);
        } else if (
            lastCommandType === "C" ||
            lastCommandType === "S" ||
            lastCommandType === "Q" ||
            lastCommandType === "T"
        ) {
            // Dla krzywych, ostatnie współrzędne są ostatnimi dwoma
            const numCoords = commands[lastIndex]
                .slice(1)
                .split(/[\s,]+/)
                .filter((c) => c !== "").length;
            commands[lastIndex] = modifyCoords(commands[lastIndex], numCoords - 2);
        }
    }

    path.setAttribute("d", commands.join(" "));
}

/**
 * Zapisuje SVG do pliku
 * @param {HTMLElement} svgOutput - Kontener z elementem SVG
 */
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

// Eksport dla przeglądarki (jeśli używane w browser_version, można użyć window)
if (typeof module !== "undefined" && module.exports) {
    module.exports = {
        deselectGroup,
        addCommentToMatchingLine,
        moveGroup,
        movePath,
        saveSvgToFile,
    };
}
