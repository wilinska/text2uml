# Generowanie diagramów z linii komend

## Metoda 1: CLI z opcjami

Użyj `cli.js` dla pełnej kontroli nad parametrami:

```bash
node src/javascript/cli.js input.txt output.svg --diagram-type class --layout Sugiyama --edge Bends
```

### Opcje:
- `--diagram-type` - typ diagramu: `auto`, `class`, `activity`, `sequence`, `usecase`
- `--layout` - typ layoutu: `Sugiyama`, `Orthogonal`, `Planar`, `Circular`, `Tree`
- `--edge` - typ krawędzi: `Bends`, `Orthogonal`, `Polyline`
- `--config` - dodatkowa konfiguracja jako JSON string

### Przykłady:

```bash
# Podstawowe użycie
node src/javascript/cli.js example_input.txt output.svg

# Diagram aktywności
node src/javascript/cli.js activity.txt output.svg --diagram-type activity --layout Sugiyama

# Z konfiguracją JSON
node src/javascript/cli.js input.txt output.svg --config '{"nodeSpacing": 100}'
```

## Metoda 2: Prosty generator

Użyj `generator.js` dla prostszego wywołania:

```bash
node src/javascript/generator.js input.txt output.svg
```

## Metoda 3: Użycie jako moduł Node.js

```javascript
const { generateDiagram, generateFromFile } = require('./src/javascript/generator');

// Z pliku
await generateFromFile('input.txt', 'output.svg', {
  diagramType: 'class',
  layoutType: 'Sugiyama',
  edgeType: 'Bends'
});

// Bezpośrednio z tekstu
const svg = await generateDiagram('@startuml\nA-->B\n@enduml', {
  diagramType: 'class',
  layoutType: 'Sugiyama'
});

console.log(svg);
```

## Przykładowy plik wejściowy

Zobacz `example_input.txt` dla przykładu definicji diagramu klas.
