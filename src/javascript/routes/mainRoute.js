const { decompressData } = require("../utils/compression");

function splitAtFirstSpace(str) {
    const index = str.indexOf(' ');

    // Jeśli nie ma spacji, zwróć cały string jako pierwszy element
    if (index === -1) return [str, ""];

    const firstPart = str.slice(0, index);
    const secondPart = str.slice(index + 1);

    return [firstPart, secondPart];
}

/**
 * Obsługuje routing dla głównej strony aplikacji
 * @param {Function} getWasmModule - Funkcja zwracająca aktualny moduł WASM
 * @param {Function} reinitWasm - Funkcja do reinicjalizacji WASM
 * @returns {Function} Handler dla Express route
 */
function createMainRouteHandler(getWasmModule, reinitWasm) {
    return async (req, res) => {
        let parameters = {
            text: "",
            diagramType: "auto",
            layoutType: "Sugiyama",
            edgeType: "Bends",
            config: {},
            svg: undefined
        };

        // console.log("Request query:", req.query);

        if (req.query.compressed) {
            try {
                const decompressed = decompressData(req.query.compressed);
                // Użyj SVG z dekompresowanych danych jeśli istnieje
                parameters.text = decompressed.text || "";
                parameters.diagramType = decompressed.diagramType || "auto";
                parameters.layoutType = decompressed.layoutType || "Sugiyama";
                parameters.edgeType = decompressed.edgeType || "Bends";
                parameters.config = decompressed.config || {};
                parameters.svg = decompressed.svg || undefined;


                const cleanedConfig = {};
                for (const key in parameters.config) {
                    cleanedConfig[key] = String(parameters.config[key]);
                }
                parameters.config = cleanedConfig
                const configString = JSON.stringify(parameters.config || {});
                if (parameters.text.length > 0) {
                    try {
                        const Text2UML = getWasmModule();
                        const result = Text2UML.Generator.generate(
                            parameters.text,
                            parameters.diagramType,
                            parameters.layoutType,
                            parameters.edgeType,
                            configString
                        );
                        const [diagram_type, diagram_svg] = splitAtFirstSpace(result);
                        parameters.diagramType = diagram_type;
                        parameters.svg = diagram_svg;
                        console.log("Generated successfully diagram type:", diagram_type);
                    } catch (error) {
                        console.error("Generate error:", error.message);
                    } finally {
                        // Reinicjalizacja WASM po użyciu
                        await reinitWasm();
                    }
                }
            } catch (error) {
                console.error("Decompression error:", error);
            }
        }
        res.render("index", parameters);
    };
}

module.exports = { createMainRouteHandler };
