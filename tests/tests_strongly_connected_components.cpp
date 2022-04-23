#include "tests_utilities.h"

#include "type.h"

#include "strongly_connected_components.h"

TEST_CASE("StronglyConnectedComponents(const AdjList& graph)", "[strongly_connected_components]") {
    SECTION("single scc") {
        AdjList graph {
            { 1, 2, 3 },
            { 2, 3 },
            { 0 },
            { 0, 2 }
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 2, 3 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("multiple scc") {
        AdjList graph {
            { 1 },// 0
            { 2, 4, 5 },// 1
            { 3, 6 },// 2
            { 2, 7 },// 3
            { 0, 5 },// 4
            { 6 },// 5
            { 5, 7 },// 6
            { 7 },// 7
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 4 }, { 2, 3 }, { 5, 6 }, { 7 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("self-loop") {
        AdjList graph {
            { 0 },// 0
            { 1 },// 1
            { 2 },// 2
            { 3 },// 3
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0 }, { 1 }, { 2 }, { 3 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("disjoint points") {
        AdjList graph {
            {  },// 0
            {  },// 1
            {  },// 2
            {  },// 3
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0 }, { 1 }, { 2 }, { 3 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("large complex scc with single disjoint point") {
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
            {  },// 17
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                                    11, 12, 13, 14, 15, 16 }, { 17 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("spiraling large complex scc") {
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
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("multiple large complex scc") {
        AdjList graph {
            { 8 },// 0
            { 4 },// 1
            { 15, 11 },// 2
            { 12 },// 3
            { 10 },// 4
            { 9, 1 },// 5
            { 14 },// 6
            { 3 },// 7
            { 13, 0, 12, 3, 7 },// 8
            { 10, 1 },// 9
            { 5 },// 10
            { 2, 6 },// 11
            { 0 },// 12
            { 7 },// 13
            { 2 },// 14
            { 11 },// 15
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 8, 13, 7, 3, 12}, { 2, 15, 11, 6, 14 },
                                                 { 5, 9, 1, 4, 10 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("all connected but not strongly connected 1") {
        AdjList graph {
            { 1 },// 0
            { 4, 5 },// 1
            { 3, 6 },// 2
            { 7, 2 },// 3
            { 0, 5 },// 4
            { 6 },// 5
            { 5 },// 6
            { 6, 3 },// 7
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 4 }, { 2, 3, 7 }, { 5, 6 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
    SECTION("all connected but not strongly connected 2") {
        AdjList graph {
            { 5, 1 },// 0
            { 2, 8, 3 },// 1
            { 0 },// 2
            { 7, 4, 2 },// 3
            { 6 },// 4
            { 4 },// 5
            { 5 },// 6
            { 8, 12, 10 },// 7
            { 11 },// 8
            { 7 },// 9
            { 11, 14 },// 10
            { 9, 15 },// 11
            { 13, 14 },// 12
            { 15 },// 13
            { 12 },// 14
            { 14 },// 15
        };
        std::list<std::list<size_t> > result = StronglyConnectedComponents(graph);
        std::list<std::list<size_t> > expect = { { 0, 1, 2, 3 }, { 5, 4, 6 }, { 7, 8, 9, 10, 11 },
                                                {  12, 13, 14, 15 } };
        CheckPartition(result.cbegin(), result.cend(), expect.cbegin(), expect.cend());
    }
}
