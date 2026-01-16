/**
 * Moduł zarządzający modalem konfiguracji i polami dynamicznymi
 */

/**
 * Zbiera dane konfiguracyjne z modala
 * @param {Object} configTemplates - Szablony konfiguracji dla różnych layoutów
 * @param {HTMLSelectElement} layoutTypeSelect - Element select z typem layoutu
 * @returns {Object} Konfiguracja zebrana z pól modala
 */
function collectConfigDataFromModal(configTemplates, layoutTypeSelect) {
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

/**
 * Zbiera aktualne parametry z formularza
 * @param {Object} currentConfig - Aktualna konfiguracja
 * @param {Object} configTemplates - Szablony konfiguracji
 * @param {HTMLTextAreaElement} textInput - Element textarea
 * @param {HTMLSelectElement} diagramTypeSelect - Select typu diagramu
 * @param {HTMLSelectElement} layoutTypeSelect - Select typu layoutu
 * @param {HTMLSelectElement} edgeTypeSelect - Select typu krawędzi
 * @returns {Object} Parametry zebrane z formularza
 */
function collectCurrentParams(
    currentConfig,
    configTemplates,
    textInput,
    diagramTypeSelect,
    layoutTypeSelect,
    edgeTypeSelect
) {
    const layoutType = layoutTypeSelect.value;
    const config = {};
    const fields = configTemplates[layoutType] || [];

    fields.forEach((field) => {
        config[field.name] =
            currentConfig[field.name] !== undefined
                ? currentConfig[field.name]
                : field.defaultValue;
    });

    return {
        text: textInput.value,
        diagramType: diagramTypeSelect.value,
        layoutType: layoutType,
        edgeType: edgeTypeSelect.value,
        config: config,
    };
}

/**
 * Renderuje dynamiczne pola konfiguracyjne w modalu
 * @param {string} layoutType - Typ layoutu
 * @param {Object} configTemplates - Szablony konfiguracji
 * @param {Object} currentConfig - Aktualna konfiguracja
 */
function renderConfigFields(layoutType, configTemplates, currentConfig) {
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

// Eksport dla przeglądarki
if (typeof module !== "undefined" && module.exports) {
    module.exports = {
        collectConfigDataFromModal,
        collectCurrentParams,
        renderConfigFields,
    };
}
