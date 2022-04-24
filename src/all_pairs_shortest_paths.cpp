#include "all_pairs_shortest_paths.h"

/*
void Print2DVector(const Matrix<size_t>& vect){
    for(size_t i = 0; i < vect.size(); i++){
        for(size_t j = 0; j < vect.size(); j++){
            std::cout << vect[i][j] << " ";
        }      
        std::cout << std::endl;
    }  
    std::cout <<std::endl;
}

void Print2DVector(const Matrix<unsigned>& vect){
    for(size_t i = 0; i < vect.size(); i++){
        for(size_t j = 0; j < vect.size(); j++){
            std::cout << vect[i][j] << " ";
        }      
        std::cout << std::endl;
    }  
    std::cout <<std::endl;
}
*/

Matrix<size_t> FloydWarshall(Matrix<unsigned>& distance) {
    size_t n = distance.size();
    Matrix<size_t> next(n, std::vector<size_t>(n, std::numeric_limits<size_t>::max()));

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            if(distance[i][j] != kNoAirline){
                next[i][j] = j;
            }
        }
    }

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (distance[i][k] != kNoAirline && distance[k][j] != kNoAirline) {
                    unsigned new_distance = distance[i][k] + distance[k][j];
                    if (new_distance < distance[i][j]){
                        distance[i][j] = new_distance;
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
    return next;
}

std::pair<Matrix<unsigned>, Matrix<size_t> > AllPairsShortestPaths(const AdjMatrix& graph) {
    size_t n = graph.size();
    Matrix<unsigned> distance(n, std::vector<unsigned>(n));
    for(size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; j++) {
            distance[i][j] = graph[i][j].distance;
        }
    }
    Matrix<size_t> next = FloydWarshall(distance);
    //Print2DVector(distance);
    //Print2DVector(next);
    return std::make_pair(std::move(distance), std::move(next));
}