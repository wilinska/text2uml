# Instrukcje testowania

## Sposób 1: Bezpośrednio w przeglądarce
1. Otwórz folder `browser_version`
2. Dwukrotnie kliknij na plik `index.html`
3. Plik otworzy się w domyślnej przeglądarce

## Sposób 2: Przez terminal (prosty serwer HTTP)
Jeśli wystąpią problemy z CORS przy lokalnym otwieraniu:

```bash
cd /home/luxoft/Desktop/test2uml/browser_version
python3 -m http.server 8080
```

Następnie otwórz w przeglądarce: http://localhost:8080

## Weryfikacja działania

Po otwarciu strony powinieneś zobaczyć:
1. ✅ Interfejs z dwoma panelami (textarea po lewej, SVG po prawej)
2. ✅ Przykładowy kod PlantUML w textarea
3. ✅ Wygenerowany diagram w prawym panelu (automatycznie przy starcie)
4. ✅ Paski narzędzi na górze z przyciskami i selectami

## Testowanie funkcji

### Test 1: Generowanie diagramu
- Zmień coś w tekście w textarea
- Kliknij "Render"
- Diagram powinien się zaktualizować

### Test 2: Przeciąganie elementów (tylko Class Diagram)
- Kliknij na panel SVG (po prawej)
- Kliknij na prostokąt z klasą
- Powinien się zaznaczyć na czerwono
- Przeciągnij go myszką
- W textarea pojawi się komentarz `' @position(x, y)`

### Test 3: Zapis SVG
- Kliknij przycisk 💾
- Plik `diagram.svg` powinien się pobrać

### Test 4: Konfiguracja
- Wybierz layout np. "Sugiyama"
- Kliknij "Config"
- Zmień wartości (np. layer distance)
- Kliknij "Apply"
- Diagram się przerenderuje z nowymi ustawieniami

### Test 5: Undo/Redo
- Edytuj tekst w textarea
- Naciśnij Ctrl+Z - powinno cofnąć zmiany
- Naciśnij Ctrl+Y - powinno przywrócić zmiany

## Sprawdzanie błędów

Jeśli coś nie działa:
1. Naciśnij F12 w przeglądarce
2. Przejdź do zakładki "Console"
3. Sprawdź komunikaty - powinny być:
   - "Text2UML Browser App Starting..."
   - "DOM loaded"
   - "Ładowanie WASM..."
   - "WASM zainicjalizowany pomyślnie"
   - "Generowanie początkowego diagramu"
   - "Aplikacja gotowa"

## Możliwe problemy

### Problem: "WASM module not initialized"
- Upewnij się, że pliki `uml-wasm.js` i `index.js` są w tym samym folderze co `index.html`
- Sprawdź czy masz połączenie z internetem (do pobrania pako z CDN)

### Problem: Brak diagramu
- Otwórz konsolę i sprawdź błędy
- Upewnij się, że kod PlantUML jest poprawny (musi zaczynać się od `@startuml` i kończyć `@enduml`)

### Problem: CORS error przy lokalnym otwieraniu
- Użyj prostego serwera HTTP (sposób 2 powyżej)
