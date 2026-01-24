# Testing Instructions

## Method 1: Directly in Browser
1. Open the `browser_version` folder
2. Double-click the `index.html` file
3. The file will open in your default browser

## Method 2: Via Terminal (Simple HTTP Server)
If you encounter CORS issues when opening locally:

```bash
cd /home/luxoft/Desktop/test2uml/browser_version
python3 -m http.server 8080
```

Then open in browser: http://localhost:8080

## Verification

After opening the page you should see:
1. ✅ Interface with two panels (textarea on left, SVG on right)
2. ✅ Sample PlantUML code in textarea
3. ✅ Generated diagram in right panel (automatically on startup)
4. ✅ Toolbars at top with buttons and select menus

## Function Testing

### Test 1: Diagram Generation
- Change something in the textarea text
- Click "Render"
- Diagram should update

### Test 2: Dragging Elements (Class Diagram only)
- Click on the SVG panel (on the right)
- Click on a class rectangle
- It should be highlighted in red
- Drag it with the mouse
- A comment `' @position(x, y)` will appear in the textarea

### Test 3: SVG Save
- Click the 💾 button
- The `diagram.svg` file should download

### Test 4: Configuration
- Select a layout e.g. "Sugiyama"
- Click "Config"
- Change values (e.g. layer distance)
- Click "Apply"
- Diagram will re-render with new settings

### Test 5: Undo/Redo
- Edit text in textarea
- Press Ctrl+Z - should undo changes
- Press Ctrl+Y - should redo changes

## Error Checking

If something doesn't work:
1. Press F12 in the browser
2. Go to the "Console" tab
3. Check messages - they should be:
   - "Text2UML Browser App Starting..."
   - "DOM loaded"
   - "Loading WASM..."
   - "WASM initialized successfully"
   - "Generating initial diagram"
   - "Application ready"

## Possible Issues

### Issue: "WASM module not initialized"
- Make sure files `uml-wasm.js` and `index.js` are in the same folder as `index.html`
- Check if you have internet connection (to download pako from CDN)

### Issue: No diagram
- Open console and check for errors
- Make sure PlantUML code is correct (must start with `@startuml` and end with `@enduml`)

### Issue: CORS error when opening locally
- Use simple HTTP server (method 2 above)
