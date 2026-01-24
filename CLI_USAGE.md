# Generating Diagrams from Command Line

## Method 1: CLI with Options

Use `cli.js` for full control over parameters:

```bash
node src/javascript/cli.js input.txt output.svg --diagram-type class --layout Sugiyama --edge Bends
```

### Options:
- `--diagram-type` - diagram type: `auto`, `class`, `activity`, `sequence`, `usecase`
- `--layout` - layout type: `Sugiyama`, `Orthogonal`, `Planar`, `Circular`, `Tree`
- `--edge` - edge type: `Bends`, `Orthogonal`, `Polyline`
- `--config` - additional configuration as JSON string

### Examples:

```bash
# Basic usage
node src/javascript/cli.js example_input.txt output.svg

# Activity diagram
node src/javascript/cli.js activity.txt output.svg --diagram-type activity --layout Sugiyama

# With JSON configuration
node src/javascript/cli.js input.txt output.svg --config '{"nodeSpacing": 100}'
```

## Method 2: Simple Generator

Use `generator.js` for simpler invocation:

```bash
node src/javascript/generator.js input.txt output.svg
```

## Method 3: Use as Node.js Module

```javascript
const { generateDiagram, generateFromFile } = require('./src/javascript/generator');

// From file
await generateFromFile('input.txt', 'output.svg', {
  diagramType: 'class',
  layoutType: 'Sugiyama',
  edgeType: 'Bends'
});

// Directly from text
const svg = await generateDiagram('@startuml\nA-->B\n@enduml', {
  diagramType: 'class',
  layoutType: 'Sugiyama'
});

console.log(svg);
```

## Sample Input File

See `example_input.txt` for an example of class diagram definition.
