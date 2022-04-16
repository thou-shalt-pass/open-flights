#include "tests_utilities.h"

#include "type.h"

#include "strongly_connected_components.h"

TEST_CASE("StronglyConnectedComponents(const AdjList& graph)", "[strongly_connected_components]") {
    AdjList graph {
        { 1, 2, 3 },
        { 2, 3 },
        { 0 },
        { 0, 2 }
    };
    StronglyConnectedComponents(graph);
    // TODO
    // REQUIRE( CheckVectorComb() );
}
