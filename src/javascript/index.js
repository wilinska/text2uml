// src/javascript/dist/wasm/umd/index.js (simplified example after Rollup)
(function (global, factory) {
    if (typeof define === 'function' && define.amd) {
        // AMD support (e.g., RequireJS)
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

    // Internal imports (from your implementation and loader files)
    function GeneratorImpl(library) {
        // GeneratorImpl implementation (from './implementation/generator')
        return {
            generate: function (input) {
                // Example Embind call: library._generateUML(input)
                return library._generateUML(input);  // Assuming Embind exports _generateUML
            }
        };
    }

    function createLoader(Library) {
        // createLoader implementation (from './loader') – async initialization
        return new Promise((resolve, reject) => {
            if (typeof Library !== 'function') {
                reject(new Error('Library is not initialized'));
                return;
            }
            Library({
                onRuntimeInitialized: () => {
                    resolve({ library: Library });  // Pass initialized instance
                },
                onAbort: (error) => reject(new Error('WASM init failed: ' + error))
            });
        });
    }

    // Main exported function (from index_wasm.js)
    var mainExport = function () {
        // Library is global (from uml-wasm.js)
        return createLoader(Library).then(function (_ref) {
            var library = _ref.library;
            return {
                Generator: GeneratorImpl(library)
            };
        });
    };

    // Return async function as module
    return mainExport;
}));