#include "tests_utilities.h"

#include "all_pairs_shortest_paths.h" 
#include "type.h"

AdjMatrix EdgeListToAdjMatrix(const std::vector<std::pair<size_t, size_t> >& verticies, const std::vector<unsigned>& weights, size_t n) {
    AdjMatrix mat_distance(n, std::vector<Edge>(n, kNoAirline));
    for(size_t i = 0; i < verticies.size(); i++){
        size_t start = verticies[i].first;
        size_t end = verticies[i].second;
        unsigned distance = weights[i];
        mat_distance[start][end] = distance;
        mat_distance[end][start] = distance;
    }
    return mat_distance;
}

std::pair< std::vector<double>, std::vector<std::vector<size_t> > > AllPath(const APSPResult& result){
   Matrix<size_t> paths;
   std::vector<double> distance;
   for (size_t i = 0; i < result.next.size(); ++i) {
        for (size_t j = i + 1; j < result.next.size(); ++j) {
            distance.push_back( result.distance[i][j]);
            std::vector<size_t> path = PathReconstruction(result.next, i, j);
            paths.push_back(path);
        }
   }
   
   return std::make_pair(distance, paths);
}

TEST_CASE("all_pairs_shortest_paths(const adjMatrix& graph) Small Graph"){
  SECTION("1 Vertex"){
    AdjMatrix adjmatrix = {{5}};
    APSPResult result = AllPairsShortestPaths(adjmatrix);
    REQUIRE(result.distance[0][0] == 0);
    REQUIRE(result.next[0][0] == 0);
  }

  SECTION("3 Vertices Graph"){
    AdjMatrix adjmatrix = {{kNoAirline, 1, 43},
                          {1, kNoAirline, 6},
                          {43, 6, kNoAirline}};

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > all_distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
    std::vector<double> all_expect_distance {1, 7, 6};
    std::vector<std::vector<size_t> > all_expect_paths {{0, 1},
                                                        {0, 1, 2},
                                                        {1, 2}};   

    REQUIRE(all_distance_path.first == all_expect_distance);
    for(size_t i = 0; i < all_expect_paths.size(); i++){
      REQUIRE(all_distance_path.second[i] == all_expect_paths[i]);
    }                  
  }

  SECTION("4 Vertices Graph"){
    AdjMatrix adjmatrix = {{kNoAirline, 2, kNoAirline, kNoAirline, kNoAirline},
                          {2, kNoAirline, 5, kNoAirline, kNoAirline},
                          {kNoAirline, 5, kNoAirline, 7, kNoAirline},
                          {kNoAirline, kNoAirline, 7, kNoAirline, 1},
                          {kNoAirline, kNoAirline, kNoAirline, 1, kNoAirline}};

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > all_distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
    std::vector<double> all_expect_distance {2, 7, 14, 15, 5, 12, 13, 7, 8, 1};
    std::vector<std::vector<size_t> > all_expect_paths {{0, 1},
                                                        {0, 1, 2},
                                                        {0, 1, 2, 3},
                                                        {0, 1, 2, 3, 4},
                                                        {1, 2},
                                                        {1, 2, 3},
                                                        {1, 2, 3, 4},
                                                        {2, 3},
                                                        {2, 3, 4},
                                                        {3, 4}};   

    REQUIRE(all_distance_path.first == all_expect_distance);
    for(size_t i = 0; i < all_expect_paths.size(); i++){
      REQUIRE(all_distance_path.second[i] == all_expect_paths[i]);
    }        
  }

  SECTION("5 Vertices Graph"){
    AdjMatrix adjmatrix = {{kNoAirline,6,8,4,kNoAirline},
                          {6,kNoAirline,1,4,2},
                          {8,1,kNoAirline,9,1},
                          {4,4,9,kNoAirline,kNoAirline},
                          {kNoAirline,2,1,kNoAirline,kNoAirline}};

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
    std::vector<double> expect_distance {6, 7, 4, 8, 1, 4, 2, 5, 1, 6};
    std::vector<std::vector<size_t> > expect_paths { {0, 1},
                                                    {0, 1, 2},
                                                    {0, 3},
                                                    {0, 1, 4},
                                                    {1, 2},
                                                    {1, 3},
                                                    {1, 4},
                                                    {2, 1, 3},
                                                    {2, 4},
                                                    {3, 1, 4} };   

    REQUIRE(distance_path.first == expect_distance);
    for(size_t i = 0; i < expect_paths.size(); i++){
       REQUIRE(distance_path.second[i] == expect_paths[i]);
    }                  
  }
}

TEST_CASE("all_pairs_shortest_paths(const adjMatrix& graph) Normal Graph"){
  SECTION("7 Vertices Graph"){
    std::vector<std::tuple<size_t, size_t, unsigned> > edges;
    std::vector<unsigned> weight {6, 1, 3, 9, 10, 
                                  2, 2, 4, 7, 13};
    std::vector< std::pair<size_t, size_t> > verticies { {0, 1}, {0, 2}, {1, 2}, {1, 4}, {2, 3},
                                                        {3, 4}, {4, 5}, {3, 5}, {5, 6}, {3, 6} };
    AdjMatrix adjmatrix = EdgeListToAdjMatrix(verticies, weight, 7);

    APSPResult result = AllPairsShortestPaths(adjmatrix);

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > all_distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
      
    //Vertex0 to Vertex2
    REQUIRE(result.distance[0][2] == 1);
    REQUIRE(PathReconstruction(result.next,0,2) == std::vector<size_t> {0, 2});

    //Vertex1 to Vertex6
    REQUIRE(result.distance[1][6] == 18);
    REQUIRE(PathReconstruction(result.next,1,6) == std::vector<size_t> {1, 4, 5, 6});

    //Vertex2 to Vertex4
    REQUIRE(result.distance[2][4] == 12);
    REQUIRE(PathReconstruction(result.next,2,4) == std::vector<size_t> {2, 1, 4});

    //Vertex4 to Vertex2
    REQUIRE(result.distance[4][2] == 12);
    REQUIRE(PathReconstruction(result.next,4,2) == std::vector<size_t> {4, 1, 2});

    //Vertex0 to Vertex6
    REQUIRE(result.distance[0][6] == 22);
    REQUIRE(PathReconstruction(result.next,0,6) == std::vector<size_t> {0, 2, 3, 5, 6});
  }

  SECTION("8 Vertices Graph"){
    std::vector<std::tuple<size_t, size_t, unsigned> > edges;
    std::vector<unsigned> weight {3, 7, 1, 2, 3, 
                                  1, 8, 9, 2, 7,
                                  4, 7, 1};
    std::vector< std::pair<size_t, size_t> > verticies {{1, 2}, {2, 8}, {8, 7}, {7, 6}, {6, 5},
                                                        {5, 4}, {4, 3}, {3, 1}, {1, 6}, {4, 8},
                                                        {3, 7}, {2, 5}, {0,1} };

    AdjMatrix adjmatrix = EdgeListToAdjMatrix(verticies, weight, 9);
    APSPResult result = AllPairsShortestPaths(adjmatrix);

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > all_distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
      

    //Vertex2 to Vertex4
    REQUIRE(result.distance[2][4] == 8);
    REQUIRE(PathReconstruction(result.next, 2, 4) == std::vector<size_t> {2, 5, 4});

    //Vertex2 to Vertex3
    REQUIRE(result.distance[2][3] == 11);
    REQUIRE(PathReconstruction(result.next, 2, 3) == std::vector<size_t> {2, 1, 6, 7, 3});

    //Vertex1 to Vertex6
    REQUIRE(result.distance[1][6] == 2);
    REQUIRE(PathReconstruction(result.next,1,6) == std::vector<size_t> {1, 6});

    //Vertex4 to Vertex7
    REQUIRE(result.distance[4][7] == 6);
    REQUIRE(PathReconstruction(result.next,4,7) == std::vector<size_t> {4, 5, 6, 7});

    //Vertex0 to Vertex7
    REQUIRE(result.distance[0][7] == 5);
    REQUIRE(PathReconstruction(result.next,0,7) == std::vector<size_t> {0, 1, 6, 7});
  }
}