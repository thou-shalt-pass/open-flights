#include "tests_utilities.h"

#include "type.h"

#include "importance.h"

TEST_CASE("ImportanceIteration(const AdjList& graph, unsigned interation_half)", "[importance_iteration]") {
    SECTION("strongly connected") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::vector<double> importance = ImportanceIteration(graph, 10);
        CheckVectorDouble(importance, { 0.38, 0.12, 0.29, 0.19 }, 0.01);
    }
    SECTION("nodes with no out-going edges 1") {
        AdjList graph {
            { 2 },
            { 2 },
            { }
        };
        std::vector<double> importance = ImportanceIteration(graph, 10);
        CheckVectorDouble(importance, { 0, 0, 0 }, 0.01);
    }
    SECTION("nodes with no out-going edges 2") {
        AdjList graph {
            { 1 },
            { 0 },
            { }
        };
        std::vector<double> importance = ImportanceIteration(graph, 10);
        CheckVectorDouble(importance, { 0.33, 0.33, 0 }, 0.01);
    }
    SECTION("disconnected") {
        AdjList graph {
            { 1 },
            { 0 },
            { 3, 4 },
            { 2, 4 },
            { 2, 3 }
        };
        std::vector<double> importance_a = ImportanceIteration(graph, 10);
        CheckVectorDouble(importance_a, { 0.2, 0.2, 0.2, 0.2, 0.2 }, 0.01);
    }
}

TEST_CASE("ImportanceEigenvector(const AdjMatrix& graph)", "[importance_eigenvector]") {
    SECTION("strongly connected") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::vector<double> importance = ImportanceEigenvector(graph, 0.01);
        CheckVectorDouble(importance, { 0.38, 0.12, 0.29, 0.19 }, 1e-15);
    }
    // SECTION("nodes with no out-going edges 1") {
    //     AdjList graph {
    //         { 2 },
    //         { 2 },
    //         { }
    //     };
    //     std::vector<double> importance = ImportanceEigenvector(graph);
    //     CheckVectorDouble(importance, { 0, 0, 0 }, 0.01);
    // }
    // SECTION("nodes with no out-going edges 2") {
    //     AdjList graph {
    //         { 1 },
    //         { 0 },
    //         { }
    //     };
    //     std::vector<double> importance = ImportanceEigenvector(graph);
    //     CheckVectorDouble(importance, { 0.33, 0.33, 0 }, 0.01);
    // }
    // SECTION("disconnected") {
    //     AdjList graph {
    //         { 1 },
    //         { 0 },
    //         { 3, 4 },
    //         { 2, 4 },
    //         { 2, 3 }
    //     };
    //     std::vector<double> importance_a = ImportanceEigenvector(graph);
    //     CheckVectorDouble(importance_a, { 0.2, 0.2, 0.2, 0.2, 0.2 }, 0.01);
    // }
}
