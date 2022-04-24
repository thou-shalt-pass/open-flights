#include "tests_utilities.h"

#include "type.h"

#include <iostream>

#include "all_pairs_shortest_paths.h"

std::vector<size_t> PathReconstruction(const Matrix<size_t>& next, size_t start, size_t end) {
   if(next[start][end] == kNoAirline){
       return std::vector<size_t>();
   }

    std::vector<size_t> path;
    path.push_back(start);
    size_t current = start;
    while(current != end){
        current = next[current][end];
        path.push_back(current);
    }

    return path;
}

void PrintPath(std::vector<size_t> path){ 
  for(size_t i = 0; i < path.size(); i++){
    std::cout << path[i]; 
    if(i != path.size() - 1){
      std::cout << " -> ";
    }
  }
  std::cout << std::endl;
}

std::pair< std::vector<double>, std::vector<std::vector<size_t> > > AllPath(const std::pair<Matrix<unsigned>, Matrix<size_t>>& result){
   
   Matrix<size_t> paths;
   std::vector<double> distance_;
   for(size_t i = 0; i < result.second.size(); i++){
        for(size_t j = i + 1; j < result.second.size(); j++){
            //std::cout << i << " to " << j << " distance " << result.first[i][j] << " : ";
            distance_.push_back( result.first[i][j]);
            std::vector<size_t> path = PathReconstruction(result.second, i, j);
            paths.push_back(path);
        }
   }
   
   return std::pair<std::vector<double>, std::vector<std::vector<size_t> > > (distance_, paths);
}

TEST_CASE("all_pairs_shortest_paths(const adjMatrix& graph)"){
  SECTION("Simple 3 Vertices Graph"){
    AdjMatrix adjmatrix = {{kNoAirline, 1, 43},
                          {1, kNoAirline, 6},
                          {43, 6, kNoAirline}};

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
    std::vector<double> expect_distance {1, 7, 6};
    std::vector<std::vector<size_t> > expect_paths {{0, 1},
                                                    {0, 1, 2},
                                                    {1, 2}};   

    CheckVectorDouble(distance_path.first, expect_distance, 0.1);
    for(size_t i = 0; i < expect_paths.size(); i++){
      CheckVectorSizet(distance_path.second[i],expect_paths[i]);
    }                  
  }

  SECTION("Simple 5 Vertices Graph"){
    AdjMatrix adjmatrix = {{kNoAirline,6,8,4,kNoAirline},
                          {6,kNoAirline,1,4,2},
                          {8,1,kNoAirline,9,1},
                          {4,4,9,kNoAirline,kNoAirline},
                          {kNoAirline,2,1,kNoAirline,kNoAirline}};

    std::pair< std::vector<double>, std::vector<std::vector<size_t> > > distance_path = AllPath(AllPairsShortestPaths(adjmatrix));
    std::vector<double> expect_distance {6, 7, 4, 8, 1, 4, 2, 5, 1, 6};
    std::vector<std::vector<size_t> > expect_paths {{0, 1},
                                                    {0, 1, 2},
                                                    {0, 3},
                                                    {0, 1, 4},
                                                    {1, 2},
                                                    {1, 3},
                                                    {1, 4},
                                                    {2, 1, 3},
                                                    {2, 4},
                                                    {3, 1, 4}};   

    CheckVectorDouble(distance_path.first, expect_distance, 0.1);
    for(size_t i = 0; i < expect_paths.size(); i++){
      CheckVectorSizet(distance_path.second[i],expect_paths[i]);
    }                  
  }
}