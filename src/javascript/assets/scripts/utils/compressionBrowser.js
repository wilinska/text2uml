/**
 * Moduł kompresji/dekompresji dla przeglądarki (używa pako globalnie)
 */

/**
 * Kompresuje dane za pomocą pako i zwraca string base64
 * @param {Object} data - Dane do skompresowania
 * @returns {string} Skompresowane dane w formacie base64
 */
function compressData(data) {
    const compressed = pako.deflate(JSON.stringify(data));
    return btoa(String.fromCharCode.apply(null, new Uint8Array(compressed)));
}

/**
 * Dekompresuje dane z formatu base64
 * @param {string} compressedData - Skompresowane dane w formacie base64
 * @returns {Object} Zdekompresowane dane
 */
function decompressData(compressedData) {
    const binaryString = atob(compressedData);
    const len = binaryString.length;
    const bytes = new Uint8Array(len);
    for (let i = 0; i < len; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }
    return JSON.parse(pako.inflate(bytes, { to: "string" }));
}

// Export for browser
if (typeof module !== "undefined" && module.exports) {
    module.exports = { compressData, decompressData };
}
