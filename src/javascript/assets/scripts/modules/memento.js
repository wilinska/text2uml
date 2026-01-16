/**
 * Moduł implementujący wzorzec Memento dla operacji undo/redo
 */

/**
 * Tworzy obiekt memento dla operacji SVG (przesuwanie grup)
 * @param {HTMLElement} svgOutput - Kontener z SVG
 * @param {Function} moveGroup - Funkcja do przesuwania grup
 * @param {Function} movePath - Funkcja do przesuwania ścieżek
 * @returns {Object} Obiekt z metodami undo/redo/saveMove
 */
function createSvgMemento(svgOutput, moveGroup, movePath) {
    const history = [];
    const redoStack = [];

    return {
        history,
        redoStack,

        saveMove(groupId, dx, dy) {
            if (dx === 0 && dy === 0) return;
            this.history.push({ groupId, dx, dy });
            this.redoStack.length = 0; // Wyczyść stos redo
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
                moveGroup(group, dx, dy);

                // Przesuń odpowiednie pathy (źródła)
                const source_groups = svgOutput.querySelectorAll(
                    `g[data-source="${groupId}"]`
                );
                source_groups.forEach((group) => {
                    const paths = group.querySelectorAll("path");
                    if (paths.length > 0) movePath(paths[0], dx, dy, true);
                    if (paths.length > 1) movePath(paths[1], dx, dy, false);
                });

                // Przesuń odpowiednie pathy (cele)
                const target_groups = svgOutput.querySelectorAll(
                    `g[data-target="${groupId}"]`
                );
                target_groups.forEach((group) => {
                    const paths = group.querySelectorAll("path");
                    if (paths.length > 0) movePath(paths[0], dx, dy, false);
                    if (paths.length > 1) movePath(paths[1], dx, dy, true);
                });
            }
        },
    };
}

/**
 * Tworzy obiekt memento dla operacji na textarea (undo/redo tekstu)
 * @param {HTMLTextAreaElement} textInput - Element textarea
 * @returns {Object} Obiekt z metodami undo/redo/saveState
 */
function createTextMemento(textInput) {
    const history = [];
    const redoStack = [];

    return {
        history,
        redoStack,

        saveState() {
            const currentText = textInput.value;
            if (
                this.history.length === 0 ||
                this.history[this.history.length - 1] !== currentText
            ) {
                this.history.push(currentText);
                this.redoStack.length = 0; // Wyczyść stos redo
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

// Eksport dla przeglądarki
if (typeof module !== "undefined" && module.exports) {
    module.exports = {
        createSvgMemento,
        createTextMemento,
    };
}
