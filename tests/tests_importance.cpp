#include "tests_utilities.h"

#include "type.h"

#include "importance.h"

TEST_CASE("Importance(const AdjList& graph)", "[importance_adj_list]") {
    AdjList graph {
        { 1, 2, 3 },
        { 2, 3 },
        { 0 },
        { 0, 2 }
    };
    std::vector<double> importance = Importance(graph);
    CheckVectorDouble(importance, { 0.38, 0.12, 0.29, 0.19 }, 0.01);
}
