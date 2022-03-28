# Leading Question

Utilizing the OpenFlights dataset gathered from https://openflights.org/data.html, we want to find the shortest air-path between two given airports, the most important airport, and the strongly connected component within the airport network based on whether customer needs to re-check-in between flights.

# Dataset Acquisition and Processing

We are using the OpenFlights dataset(https://openflights.org/data.html). 

## Data format

We are using two datasets both stored as CSV files. One contains the information of 14110 distinct airports in 14 columns. We will preprocess the file to extract only the airport ID, latitude, and longitude, and store them into a new CSV file. 
The other CSV file contains 67663 routes between 3321 airports. We will also preprocess this file to filter out only the source airport ID and destination airport ID and store them into a new CSV file.

## Data correction

We will check that all airlines have a valid Source Airport and a destination Airport. We ensure that all airport and airport ID is one to one so there will be no conflict. If not, we filter out that airline. We also make sure that the longitude of the airport is between -180 to 180 and the latitude of the airport between -90 and 90. 

## Data storage

We will store each route structured as an Edge object:
```cpp
struct Edge {
	unsigned long long distance;
	unsigned num_planes;
};
```
we will also construct a two-dimensional vector structured as below
```cpp
std::vector<std::vector<Edge> > adj_matrix_graph(n, std::vector<Edge>(n));
```
The total storage cost is O(n^2) in which n is the number of airports.

## Data modification

We will use a random number generator to assign each airport a bool value to represent whether a customer needs to re-check-in between flights (1 for needs to re-check-in, 0 or no need to re-check-in).

# Algorithm

In order to implement the project successfully, we will take advantage of Floyd-Warshall, PageRank, and strongly connected components (including invoking of DFS) algorithm.
Note that time complexity does not include preprocessing time; memory complexity does not include input and output memory usage.

## Floyd-Warshall

### Input

Adjacency matrix where entries are distance between two airports if there exists a route. More formally, the input is a matrix A such that A[i][j] is the distance between node i and j if these two nodes are connected; if (i, j) \notin E, then A[i][j] = \infty. 

### Output

A matrix where entries are shortest distances between two airports. More formally, the output is a matrix B such that B[i][j] is the shortest path between node i and j. 

### Efficiency

Let n be the number of airports.

- Time: O(n^3)

- Memory: O(n^2)

## PageRank

### Input

Adjacency matrix where entries are number of planes. More formally, the input is a matrix E such that E[i][j] is the number of flights from node i to j. 

### Output

Table includes the importance of each airport. More formally, the output is a vector F where F[i] is the number that represents the importance of node i.

### Efficiency

Let n be the number of airports.

- Time: O(n^3)
- Memory: O(n^2)

## Strongly connected components

### Input

- Unweighted adjacency matrix H such that H[i][j] is a bool value representing whether there exists an route from node i to j.
- Array of bool values representing whether the airports require re-check-in. 

### Output

List contains strongly connected components

### Efficiency

Let n be the number of airports.

- Time: O(n^2)
- Memory: O(n^2)
 
# Timeline

- Finish reading and processing the data before April 2nd. 
- Complete basic structure by April 9th.
- Complete Floyd-Warshall by April 15th. 
- Complete PageRank by April 23rd.
- Complete DFS by April 29th. 
- Complete test cases by May 4th.
