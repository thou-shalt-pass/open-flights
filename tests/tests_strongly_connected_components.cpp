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
}
