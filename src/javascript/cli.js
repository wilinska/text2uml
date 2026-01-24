#!/usr/bin/env node

const fs = require('fs');

/**
 * CLI for generating UML diagrams
 * Usage: node cli.js <input_file> <output_file> [options]
 *
 * Options:
 *   --diagram-type <type>  Diagram type (auto, class, activity)
 *   --layout <type>        Layout type (Sugiyama, Orthogonal, OptimalHierarchy, etc.)
 *   --edge <type>          Edge type (Bends, Polyline)
 *   --config <json>        Configuration as JSON string
 *
 * Example:
 *   node cli.js input.txt output.svg --diagram-type class --layout Sugiyama
 */

function splitAtFirstSpace(str) {
    const index = str.indexOf(' ');

    // If there's no space, return the whole string as the first element
    if (index === -1) return [str, ""];

    const firstPart = str.slice(0, index);
    const secondPart = str.slice(index + 1);

    return [firstPart, secondPart];
}

async function main() {
    const args = process.argv.slice(2);

    if (args.length < 2) {
        console.error('Usage: node cli.js <input_file> <output_file> [options]');
        console.error('');
        console.error('Options:');
        console.error('  --diagram-type <type>  Diagram type (auto, class, activity)');
        console.error('  --layout <type>        Layout type (Sugiyama, Orthogonal, OptimalHierarchy)');
        console.error('  --edge <type>          Edge type (Bends, Polyline)');
        console.error('  --config <json>        Configuration as JSON string');
        process.exit(1);
    }

    const inputFile = args[0];
    const outputFile = args[1];

    // Parse options
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
                    console.error('JSON configuration parsing error:', e.message);
                    process.exit(1);
                }
                break;
            default:
                console.error('Unknown option:', args[i]);
                process.exit(1);
        }
    }

    // Check if input file exists
    if (!fs.existsSync(inputFile)) {
        console.error(`Input file does not exist: ${inputFile}`);
        process.exit(1);
    }

    // Load file content
    const inputText = fs.readFileSync(inputFile, 'utf8');

    if (!inputText.trim()) {
        console.error('Input file is empty');
        process.exit(1);
    }

    console.log('Loading WASM module...');

    // Load WASM module
    const Library = require('./dist/wasm/umd');
    const Text2UML = await Library();

    console.log('Generating diagram...');
    console.log(`  Diagram type: ${diagramType}`);
    console.log(`  Layout: ${layoutType}`);
    console.log(`  Edge type: ${edgeType}`);

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

        // Save result to file
        fs.writeFileSync(outputFile, diagram_svg, 'utf8');
        console.log(`✓ Diagram ${diagram_type} saved to: ${outputFile}`);

    } catch (error) {
        console.error('Error generating diagram:', error.message);
        process.exit(1);
    }
}

main().catch(error => {
    console.error('Unexpected error:', error);
    process.exit(1);
});
