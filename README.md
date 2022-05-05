# CS 225 Final Project: OpenFlights

## Team Members: tluo9-yanzhen4-yirongc3

## Deliverables 

- [Report](https://github-dev.cs.illinois.edu/cs225-sp22/tluo9-yanzhen4-yirongc3/blob/main/results.md)
- [Presentation Video](https://www.youtube.com/watch?v=rm-2JCFS0Fs)
- [Presentation Slides](https://github-dev.cs.illinois.edu/cs225-sp22/tluo9-yanzhen4-yirongc3/blob/main/presentation_slides.pdf)

## Introduction

Our final project uses airports and route dataset from [OpenFlights](https://openflights.org/data.html) to find the shortest air-path between two given airports and the relatively important airports.

We implemented Floyd-Warshall algorithm to find the shortest path between two airports, PageRank algorithm to find important airports.

## File description

### data

contains the the airport and route dataset from [OpenFlights](https://openflights.org/data.html)

- `airport.csv` and `route.csv` are the original source file

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

### Main Drivers

The main entry is divided into two part: algorithm_driver and result_interpreter. 
The reason of that is algorithm_driver will run all algorithms and takes ~82min on EWS 
since it runs all algorithm and major time spent on Floyd-Warshall (~70min). 
We divide the responsibilities into two part: computational and user interaction. 

#### algorithm_driver 

Run strongly connected components algorithm, three algorithms finding importance of airports, and Floyd-Warshall. 
Then store raw data in csv and zip into `result.tar.gz` because raw data is very big (~800MB).

- Compile: `make algorithm_driver`

- Run: `./bin/algorithm_driver <airport-dataset-filename> <airline-dataset-filename>` 

(`<airport-dataset-filename>` and `<airline-dataset-filename>` are optional 
and the default values are `data/airport.csv` and `data/route.csv`)

There are 6072 airports in `data/airport.csv`. 
To short run time (for the purpose of demo), 
we can use `./bin/algorithm_driver data/airport_small.csv` 
where `data/airport_small.csv` only contains first 200 airports in `data/airport.csv`. 

#### result_interpreter 

Read result from algorithm_driver. 
Interact with users. 

- Compile: `make result_interpreter`

- Run: `./bin/result_interpreter <result-zip-filename>`

(`<result-zip-filename>` is optional 
and the default value is `result.tar.gz`)

We can run `./bin/result_interpreter sample_result.tar.gz` 
to interpret the precomputed result from the default dataset (`data/airport.csv` and `data/route.csv`). 

The result_interpreter provides 5 interactive command

- `dfs <origin-iata-code>`: run DFS with the specific origin airport `<origin-iata-code>`
- `scc <iata-code>`: find the index (unique identifier) of the strongly connected component contains airport `<iata-code>`
- `sp <departure-iata-code> <destination-iata-code>`: find the shortest path from the airport `<departure-iata-code>` to the airport `<destination-iata-code>`
- `top <limit-number>`: find the `<limit-number>` most important airports
- `rank <iata-code>`: find importance of the airport `<iata-code>`

### Test Cases (exclude tests_importance_mutual_actual)

- Compile + Run: `sh run_tests.sh`

### Test Case (only tests_importance_mutual_actual)

- Compile: `make tests_importance_mutual_actual`

- Run: `./bin/tests_importance_mutual_actual`

This will take ~12min on EWS.

The reason of excluding this test case from "tests all" is 
this test case takes too long 
since it compares the result of `ImportanceIteration`, `ImportanceEigenvectorByLU` and `ImportanceEigenvectorByGaussian` mutually by inputing the default dataset (`data/airport.csv` and `data/route.csv`).
