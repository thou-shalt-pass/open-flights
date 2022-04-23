#include "tests_utilities.h"

#include "type.h"

#include "dfs.h"

// callback function types
enum OpType { kOpBeforeComponent, kOpBeforeVisit, kOpAfterVisit };

void TestDFS(const AdjList& graph, const std::vector<size_t>& look_next_origin_sequence, 
        const std::vector<std::tuple<OpType, size_t, size_t> >& expected_op_sequence) {
    size_t n = graph.size(), look_next_origin_sequence_ptr = 0, expected_op_sequence_ptr = 0;

    auto look_next_origin = [n, &look_next_origin_sequence, &look_next_origin_sequence_ptr]() {
        if (look_next_origin_sequence_ptr == look_next_origin_sequence.size()) {
            ++look_next_origin_sequence_ptr;
            return n;
        }
        REQUIRE( look_next_origin_sequence_ptr < look_next_origin_sequence.size() );
        return look_next_origin_sequence[look_next_origin_sequence_ptr++];
    };

    auto op_before_component = [&expected_op_sequence, &expected_op_sequence_ptr](size_t origin_idx) {
        REQUIRE( expected_op_sequence_ptr < expected_op_sequence.size() );
        REQUIRE( std::get<0>(expected_op_sequence[expected_op_sequence_ptr]) == kOpBeforeComponent );
        REQUIRE( std::get<1>(expected_op_sequence[expected_op_sequence_ptr]) == origin_idx );
        ++expected_op_sequence_ptr;
        return origin_idx;
    };

    auto op_start_visit = [&expected_op_sequence, &expected_op_sequence_ptr](size_t origin_idx, size_t component_handle) {
        REQUIRE( expected_op_sequence_ptr < expected_op_sequence.size() );
        REQUIRE( std::get<0>(expected_op_sequence[expected_op_sequence_ptr]) == kOpBeforeVisit );
        REQUIRE( std::get<1>(expected_op_sequence[expected_op_sequence_ptr]) == origin_idx );
        REQUIRE( std::get<2>(expected_op_sequence[expected_op_sequence_ptr]) == component_handle );
        ++expected_op_sequence_ptr;
    };

    auto op_after_visit = [&expected_op_sequence, &expected_op_sequence_ptr](size_t origin_idx, size_t component_handle) {
        REQUIRE( expected_op_sequence_ptr < expected_op_sequence.size() );
        REQUIRE( std::get<0>(expected_op_sequence[expected_op_sequence_ptr]) == kOpAfterVisit );
        REQUIRE( std::get<1>(expected_op_sequence[expected_op_sequence_ptr]) == origin_idx );
        REQUIRE( std::get<2>(expected_op_sequence[expected_op_sequence_ptr]) == component_handle );
        ++expected_op_sequence_ptr;
    };

    DFS(graph, look_next_origin, op_before_component, op_start_visit, op_after_visit);

    REQUIRE( expected_op_sequence_ptr == expected_op_sequence.size() );
}

TEST_CASE("DFS 1", "[dfs]") {
    AdjList graph {
        { 1, 3 },
        { 4 },
        { 4, 5 },
        { 1 }, 
        { 3 }, 
        { 5 }
    };
    std::vector<size_t> look_next_origin_sequence { 0, 1, 2, 3, 4, 5 };
    std::vector<std::tuple<OpType, size_t, size_t> > expected_op_sequence { 
        { kOpBeforeComponent, 0, std::numeric_limits<size_t>::max() }, 
        { kOpBeforeVisit, 0, 0 }, 
        { kOpBeforeVisit, 1, 0 }, 
        { kOpBeforeVisit, 4, 0 }, 
        { kOpBeforeVisit, 3, 0 }, 
        { kOpAfterVisit, 3, 0 }, 
        { kOpAfterVisit, 4, 0 }, 
        { kOpAfterVisit, 1, 0 }, 
        { kOpAfterVisit, 0, 0 }, 
        { kOpBeforeComponent, 2, std::numeric_limits<size_t>::max() }, 
        { kOpBeforeVisit, 2, 2 }, 
        { kOpBeforeVisit, 5, 2 }, 
        { kOpAfterVisit, 5, 2 }, 
        { kOpAfterVisit, 2, 2 }, 
    };
    TestDFS(graph, look_next_origin_sequence, expected_op_sequence);
}
