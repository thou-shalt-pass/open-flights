# CS 225 Final Project: OpenFlights

## Team Members: tluo9-yanzhen4-yirongc3

## Deliverables 

- [Report]()
- [Presentation Video]()
- [Presentation Slides]()

## Introduction
Our final project uses airports and route dataset from [OpenFlights](https://openflights.org/data.html) to find the shortest air-path between two given airports and the relatively important airports.

We implemented Floyd-Warshall algorithm to find the shortest path between two airports, PageRank algorithm to find important airports.

## File description

### data
contains the the airport and route dataset from [OpenFlights](https://openflights.org/data.html)
- `airport_ori.csv` and `route_ori.csv` are the original source file
- `airport_scc.csv` and `route_scc.csv` are the largest strongly connected component within the source file

### documents
contains `contract.md`, `log.md`, and `proposal.md`

### includes
contains all header files for source files

### src
contains all source files
- `all_pairs_shortest_paths.cpp`: Floyd-Warshall Algorithm
- `data.cpp`: read in and process source data into adjacency matrix and adjacency list
- `importance.cpp`: PageRank algorithm
- `matrix_operation.cpp`: matrix operation support for eigenvector implementation of PageRank
- `strongly_connected_components.cpp`: strongly connected component algorithm

## Running Instruction


