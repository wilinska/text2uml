/**
 * Konfiguracja szablonów dla różnych typów layoutów
 */
const configTemplates = {
    Circular: [
        { label: "minDistCircle", id: "minDistCircle", name: "minDistCircle", type: "number", min: 0, step: 1, defaultValue: 100 },
        { label: "minDistLevel", id: "minDistLevel", name: "minDistLevel", type: "number", min: 0, step: 1, defaultValue: 100 },
        { label: "minDistSibling", id: "minDistSibling", name: "minDistSibling", type: "number", min: 0, step: 1, defaultValue: 70 }
    ],
    FMMM: [
        { label: "useHighLevelOptions", id: "useHighLevelOptions", name: "useHighLevelOptions", type: "boolean", defaultValue: true },
        { label: "Unit Edge Length", id: "unitEdgeLength", name: "unitEdgeLength", type: "number", min: 0, step: 1, defaultValue: 75 },
        { label: "Page Ratio", id: "pageRatio", name: "pageRatio", type: "number", min: 0, step: 1, defaultValue: 1 },
        { label: "Fine Tune Scalar", id: "fineTuneScalar", name: "fineTuneScalar", type: "number", min: 0, step: 1, defaultValue: 0.2 },
        { label: "Galaxy Choice", id: "galaxy-choice", name: "galaxyChoice", type: "select", options: ["UniformProb", "NonUniformProbHigherMass", "NonUniformProbLowerMass"], defaultValue: "NonUniformProbLowerMass" },
    ],
    OptimalHierarchy: [
        { label: "Layer Distance", id: "layerDistance", name: "layerDistance", type: "number", min: 0, step: 1, defaultValue: 30 },
        { label: "Node Distance", id: "nodeDistance", name: "nodeDistance", type: "number", min: 0, step: 1, defaultValue: 25 },
        { label: "Weight Balancing", id: "weightBalancing", name: "weightBalancing", type: "number", min: 0, max: 1, step: 0.1, defaultValue: 0.8 }
    ],
    Orthogonal: [],
    Sugiyama: [
        { label: "Distance between layers", id: "layer-distance", name: "layerDistance", type: "number", min: 0, step: 1, defaultValue: 50 },
        { label: "Distance between nodes", id: "node-distance", name: "nodeDistance", type: "number", min: 0, step: 1, defaultValue: 30 },
        { label: "Ranking type", id: "ranking-type", name: "rankingType", type: "select", options: ["OptimalRanking", "LongestPathRanking", "CoffmanGrahamRanking"], defaultValue: "OptimalRanking" },
        { label: "CrossMin algorithm type", id: "cross-type", name: "crossType", type: "select", options: ["MedianHeuristic", "BarycenterHeuristic", "GreedyInsertHeuristic"], defaultValue: "MedianHeuristic" }
    ],
    Tree: [],
};

// Eksport dla Node.js i przeglądarki
if (typeof module !== "undefined" && module.exports) {
    module.exports = { configTemplates };
}
// W przeglądarce configTemplates będzie dostępny jako zmienna globalna
