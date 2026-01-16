#!/usr/bin/env node

const fs = require('fs');

/**
 * CLI dla generowania diagramów UML
 * Użycie: node cli.js <input_file> <output_file> [options]
 *
 * Opcje:
 *   --diagram-type <type>  Typ diagramu (auto, class, activity)
 *   --layout <type>        Typ layoutu (Sugiyama, Orthogonal, OptimalHierarchy, etc.)
 *   --edge <type>          Typ krawędzi (Bends, Polyline)
 *   --config <json>        Konfiguracja jako JSON string
 *
 * Przykład:
 *   node cli.js input.txt output.svg --diagram-type class --layout Sugiyama
 */

function splitAtFirstSpace(str) {
    const index = str.indexOf(' ');

    // Jeśli nie ma spacji, zwróć cały string jako pierwszy element
    if (index === -1) return [str, ""];

    const firstPart = str.slice(0, index);
    const secondPart = str.slice(index + 1);

    return [firstPart, secondPart];
}

async function main() {
    const args = process.argv.slice(2);

    if (args.length < 2) {
        console.error('Użycie: node cli.js <input_file> <output_file> [options]');
        console.error('');
        console.error('Opcje:');
        console.error('  --diagram-type <type>  Typ diagramu (auto, class, activity)');
        console.error('  --layout <type>        Typ layoutu (Sugiyama, Orthogonal, OptimalHierarchy)');
        console.error('  --edge <type>          Typ krawędzi (Bends, Polyline)');
        console.error('  --config <json>        Konfiguracja jako JSON string');
        process.exit(1);
    }

    const inputFile = args[0];
    const outputFile = args[1];

    // Parsowanie opcji
    let diagramType = 'auto';
    let layoutType = 'Sugiyama';
    let edgeType = 'Bends';
    let config = {};

    for (let i = 2; i < args.length; i++) {
        switch (args[i]) {
            case '--diagram-type':
                diagramType = args[++i];
                break;
            case '--layout':
                layoutType = args[++i];
                break;
            case '--edge':
                edgeType = args[++i];
                break;
            case '--config':
                try {
                    config = JSON.parse(args[++i]);
                } catch (e) {
                    console.error('Błąd parsowania konfiguracji JSON:', e.message);
                    process.exit(1);
                }
                break;
            default:
                console.error('Nieznana opcja:', args[i]);
                process.exit(1);
        }
    }

    // Sprawdź czy plik wejściowy istnieje
    if (!fs.existsSync(inputFile)) {
        console.error(`Plik wejściowy nie istnieje: ${inputFile}`);
        process.exit(1);
    }

    // Wczytaj treść pliku
    const inputText = fs.readFileSync(inputFile, 'utf8');

    if (!inputText.trim()) {
        console.error('Plik wejściowy jest pusty');
        process.exit(1);
    }

    console.log('Ładowanie modułu WASM...');

    // Załaduj moduł WASM
    const Library = require('./dist/wasm/umd');
    const Text2UML = await Library();

    console.log('Generowanie diagramu...');
    console.log(`  Typ diagramu: ${diagramType}`);
    console.log(`  Layout: ${layoutType}`);
    console.log(`  Typ krawędzi: ${edgeType}`);

    try {
        const configString = JSON.stringify(config);
        const result = Text2UML.Generator.generate(
            inputText,
            diagramType,
            layoutType,
            edgeType,
            configString
        );
        const [diagram_type, diagram_svg] = splitAtFirstSpace(result);

        // Zapisz wynik do pliku
        fs.writeFileSync(outputFile, diagram_svg, 'utf8');
        console.log(`✓ Diagram ${diagram_type} zapisany do: ${outputFile}`);

    } catch (error) {
        console.error('Błąd podczas generowania diagramu:', error.message);
        process.exit(1);
    }
}

main().catch(error => {
    console.error('Nieoczekiwany błąd:', error);
    process.exit(1);
});
