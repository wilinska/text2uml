// src/javascript/dist/wasm/umd/index.js (uproszczony przykład po Rollup)
(function (global, factory) {
    if (typeof define === 'function' && define.amd) {
        // AMD support (np. RequireJS)
        define([], factory);
    } else if (typeof module === 'object' && module.exports) {
        // CommonJS support (Node.js)
        module.exports = factory();
    } else {
        // Browser global (UMD)
        global.Text2UML = factory();
    }
}(typeof self !== 'undefined' ? self : this, function () {
    'use strict';

    // Internal imports (z twoich plików implementation i loader)
    function GeneratorImpl(library) {
        // Implementacja GeneratorImpl (z './implementation/generator')
        return {
            generate: function(input) {
                // Przykładowe wywołanie Embind: library._generateUML(input)
                return library._generateUML(input);  // Zakładając, że Embind eksportuje _generateUML
            }
        };
    }

    function createLoader(Library) {
        // Implementacja createLoader (z './loader') – async inicjalizacja
        return new Promise((resolve, reject) => {
            if (typeof Library !== 'function') {
                reject(new Error('Library is not initialized'));
                return;
            }
            Library({
                onRuntimeInitialized: () => {
                    resolve({ library: Library });  // Przekaż zainicjalizowaną instancję
                },
                onAbort: (error) => reject(new Error('WASM init failed: ' + error))
            });
        });
    }

    // Główna eksportowana funkcja (z index_wasm.js)
    var mainExport = function () {
        // Library jest globalne (z uml-wasm.js)
        return createLoader(Library).then(function (_ref) {
            var library = _ref.library;
            return {
                Generator: GeneratorImpl(library)
            };
        });
    };

    // Zwróć async funkcję jako moduł
    return mainExport;
}));