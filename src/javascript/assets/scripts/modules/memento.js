/**
 * Module implementing Memento pattern for undo/redo operations
 */

/**
 * Creates memento object for SVG operations (moving groups)
 * @param {HTMLElement} svgOutput - SVG container
 * @param {Function} moveGroup - Function to move groups
 * @param {Function} movePath - Function to move paths
 * @returns {Object} Object with undo/redo/saveMove methods
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
            this.redoStack.length = 0; // Clear redo stack
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

                // Move appropriate paths (sources)
                const source_groups = svgOutput.querySelectorAll(
                    `g[data-source="${groupId}"]`
                );
                source_groups.forEach((group) => {
                    const paths = group.querySelectorAll("path");
                    if (paths.length > 0) movePath(paths[0], dx, dy, true);
                    if (paths.length > 1) movePath(paths[1], dx, dy, false);
                });

                // Move appropriate paths (targets)
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
 * Creates memento object for textarea operations (text undo/redo)
 * @param {HTMLTextAreaElement} textInput - Textarea element
 * @returns {Object} Object with undo/redo/saveState methods
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
                this.redoStack.length = 0; // Clear redo stack
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

// Export for browser
if (typeof module !== "undefined" && module.exports) {
    module.exports = {
        createSvgMemento,
        createTextMemento,
    };
}
