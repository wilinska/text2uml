const pako = require("pako");

/**
 * Kompresuje dane za pomocą pako i zwraca string base64
 * @param {Object} data - Dane do skompresowania
 * @returns {string} Skompresowane dane w formacie base64
 */
function compressData(data) {
    const compressed = pako.deflate(JSON.stringify(data), { to: "string" });
    return Buffer.from(compressed).toString("base64");
}

/**
 * Dekompresuje dane z formatu base64
 * @param {string} compressedData - Skompresowane dane w formacie base64
 * @returns {Object} Zdekompresowane dane
 */
function decompressData(compressedData) {
    const compressed = Buffer.from(compressedData, "base64");
    return JSON.parse(pako.inflate(compressed, { to: "string" }));
}

module.exports = { compressData, decompressData };
