# Leading Question

Utilizing the OpenFlights dataset gathered from https://openflights.org/data.html, we want to find the shortest air-path between two given airports and the most important airport.

# Dataset Acquisition and Processing

We are using the OpenFlights dataset (https://openflights.org/data.html). 

## Data format

We are using two datasets both stored as CSV files. One contains the information of 14110 distinct airports in 14 columns. We will preprocess the file to extract only the airport ID, latitude, and longitude, and store them into a new CSV file. 
The other CSV file contains 67663 routes between 3321 airports. We will also preprocess this file to filter out only the source airport ID and destination airport ID and store them into a new CSV file.

## Data correction

We will check that all airlines have a valid Source Airport and a destination Airport. We ensure that all airport and airport ID is one to one so there will be no conflict. If not, we filter out that airline. We also make sure that the longitude of the airport is between -180 to 180 and the latitude of the airport between -90 and 90. 

## Data storage

We will store each route as an Edge object, in which the distance is calculated using Haversine formula given the longitude and latitude of the two airports:
```cpp
struct Edge {
	unsigned distance;
};
```

We will store each airport as a Node object, in which ID is the unique 3-letter IATA code for the airport:
```cpp
struct Node{
	std::string city;
	std::string airport_name;
	std::string iata_code;
	double longitude;
	double latitude;
};
```

Let V be the set of nodes (airports), and let E be the set of edges (routes).
We will store the directed graph G = (V, E) both as an adjacency matrix and as an adjacency list. 

For the adjacency matrix, we will use
```cpp
std::vector<std::vector<Edge> > adj_matrix( | V | , std::vector<Edge>( | V | ));
```
For the adjacency list, we will use
```cpp
std::vector<std::list<int> > adj_list( | V | );
```
adj_list is defined as std::vector<std::list<int> >, instead of std::vector<std::vector<Edge> >, since we can access corresponding values in adj_matrix in O(1) .

Since it is a simple graph, we have V + E = O( V^2 ).  
Thus, the total space complexity is O( V^2 + ( V + E ) ) = O( V^2 ) .


# Algorithm

We will implement Floyd-Warshall, PageRank, and DFS.
Note that time complexity does not include preprocessing time; memory complexity does not include input and output memory usage.

## Floyd-Warshall

### Input

An adjacency matrix where entries are the distance between two airports if there exists a route. More formally, the input is a matrix A such that A[i][j] is the distance between node i and j if these two nodes are connected; if (i, j) \notin E, then A[i][j] = \infty. 

### Output

A matrix where entries are shortest distances between two airports. More formally, the output is a matrix B such that B[i][j] is the shortest path between node i and j. 

### Efficiency

- Time: O(V^3)

- Memory: O(V^2)

## PageRank (with fixed number of iterations)

### Input

An adjacency list representing an unweighted directed graph.

### Output

A vector in which each value represents the importance of each airport. More formally, the output is a vector F where F[i] is the number that represents the importance of node i.

### Efficiency

Let k be the number of iterations.

- Time: O( k ( V + E ) )
- Memory: O( V )

## DFS

Abstract DFS library

### Input

unweighted / weighted undirected / directed graph in adjacency list
function object

### Output

Return value: void

### Efficiency

- Time: O(V + E)
- Memory: O(d) where d is the maximum number of nodes on a simple path

# Timeline

- Finish reading and processing the data before April 2nd. 
- Complete PageRank by April 15th.
- Complete Floyd-Warshall by April 23th. 
- Complete DFS by April 29th. 
- Complete test cases by May 4th.
