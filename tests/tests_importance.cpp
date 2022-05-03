#include "tests_utilities.h"

#include "data.h"
#include "importance.h"
#include "type.h"

TEST_CASE("ImportanceIteration(const AdjList& graph, unsigned iteration_times)", "[importance_it]") {
    SECTION("strongly connected 1") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::vector<double> importance = ImportanceIteration(graph, 1000);
        CheckVectorDoubleWithScalarMultiple(importance, { 2, 2.0 / 3, 1.5, 1 }, 1e-10);
    }

    SECTION("strongly connected 2") {
        AdjList graph {
            { 1, 2 },
            { 2 },
            { 0 },
        };
        std::vector<double> importance = ImportanceIteration(graph, 1000);
        CheckVectorDoubleWithScalarMultiple(importance, { 0.4, 0.2, 0.4 }, 1e-10);
    }

    // SECTION("nodes with no out-going edges 1") {
    //     AdjList graph {
    //         { 2 },
    //         { 2 },
    //         { }
    //     };
    //     std::vector<double> importance = ImportanceIteration(graph, 10);
    //     CheckVectorDouble(importance, { 0, 0, 0 }, 0.01);
    // }

    // SECTION("nodes with no out-going edges 2") {
    //     AdjList graph {
    //         { 1 },
    //         { 0 },
    //         { }
    //     };
    //     std::vector<double> importance = ImportanceIteration(graph, 10);
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
    //     std::vector<double> importance_a = ImportanceIteration(graph, 10);
    //     CheckVectorDouble(importance_a, { 0.2, 0.2, 0.2, 0.2, 0.2 }, 0.01);
    // }
}

TEST_CASE("ImportanceEigenvectorByLU(const AdjList& graph)", "[importance_lu]") {
    SECTION("strongly connected 1") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::vector<double> importance = ImportanceEigenvectorByLU(graph);
        CheckVectorDoubleWithScalarMultiple(importance, { 2, 2.0 / 3, 1.5, 1 }, 1e-10);
    }

    SECTION("strongly connected 2") {
        AdjList graph {
            { 1, 2 },
            { 2 },
            { 0 },
        };
        std::vector<double> importance = ImportanceEigenvectorByLU(graph);
        CheckVectorDoubleWithScalarMultiple(importance, { 0.4, 0.2, 0.4 }, 1e-10);
    }
}

TEST_CASE("ImportanceEigenvectorByGaussian(const AdjList& graph)", "[importance_gaussian]") {
    SECTION("strongly connected 1") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::vector<double> importance = ImportanceEigenvectorByGaussian(graph);
        CheckVectorDoubleWithScalarMultiple(importance, { 2, 2.0 / 3, 1.5, 1 }, 1e-10);
    }

    SECTION("strongly connected 2") {
        AdjList graph {
            { 1, 2 },
            { 2 },
            { 0 },
        };
        std::vector<double> importance = ImportanceEigenvectorByGaussian(graph);
        CheckVectorDoubleWithScalarMultiple(importance, { 0.4, 0.2, 0.4 }, 1e-10);
    }
}

TEST_CASE("mutual test", "[mutual]") {
    SECTION("strongly connected 3") {
        AdjList graph {
            { 1 },
            { 4 },
            { 0, 1, 3, 4 },
            { 2, 4 },
            { 3 },
        };
        std::vector<double> it_result = ImportanceIteration(graph, 1000);
        std::vector<double> lu_result = ImportanceEigenvectorByLU(graph);
        std::vector<double> gaussian_result = ImportanceEigenvectorByGaussian(graph);
        CheckVectorDoubleWithScalarMultiple(lu_result, gaussian_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(lu_result, it_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(gaussian_result, it_result, 1e-10);
    }

    SECTION("strongly connected 4") {
        AdjList graph {
            { 1, 15 },// 0
            { 2, 3 },// 1
            { 6, 5 },// 2
            { 14, 4 },// 3
            { 14 },// 4
            { 6, 9 },// 5
            { 8, 7 },// 6
            { 5, 9, 1 },// 7
            { 7, 0 },// 8
            { 10 },// 9
            { 11 },// 10
            { 12, 8 },// 11
            { 9, 5, 13 },// 12
            { 5, 9, 12, 14 },// 13
            { 0, 15, 13, 5 },// 14
            { 16, 14, 3, 6, 7 },// 15
            { 15, 13 },// 16
        };
        std::vector<double> it_result = ImportanceIteration(graph, 1000);
        std::vector<double> lu_result = ImportanceEigenvectorByLU(graph);
        std::vector<double> gaussian_result = ImportanceEigenvectorByGaussian(graph);
        CheckVectorDoubleWithScalarMultiple(lu_result, gaussian_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(lu_result, it_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(gaussian_result, it_result, 1e-10);
    }
    SECTION("strongly connected 5") {
        AdjList graph {
            { 1, 2, 3, 4, 5 },// 0
            { 2, 7 },// 1
            { 3, 8 },// 2
            { 4, 9 },// 3
            { 5 },// 4
            { 1, 6, 11, 0 },// 5
            { 7 },// 6
            { 8 },// 7
            { 9 },// 8
            { 10, 2 },// 9
            { 11 },// 10
            { 6 },// 11
        };
        std::vector<double> it_result = ImportanceIteration(graph, 1000);
        std::vector<double> lu_result = ImportanceEigenvectorByLU(graph);
        std::vector<double> gaussian_result = ImportanceEigenvectorByGaussian(graph);
        CheckVectorDoubleWithScalarMultiple(lu_result, gaussian_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(lu_result, it_result, 1e-10);
        CheckVectorDoubleWithScalarMultiple(gaussian_result, it_result, 1e-10);
    }
}
