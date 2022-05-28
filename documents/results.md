# Project Report

## Data Processing

From the preprocessed CSV files, we stored each airport as a node with the city name, the airport name, the IATA code, the longitude, and the latitude. We also stored every route as a weighted edge using distance calculated from Haversine formula using its longitude and latitude. We then constructed an adjacency list and an adjacency matrix to connect nodes with weighted edges to represent the directed graph. For the purpose of fast retrieval, we build a bijection map between index (airport unique identifier) and IATA code by using `std::vector` and `std::unordered_map`. 

## DFS

We implemented the recursive version DFS. The DFS function accepts an adjacency list and many function objects that allow the program to execute customized actions in the specified slots including `before_component`, `start_visit`, and `stop_visit`. It also allows specifying the node visit order within the main loop. One of the examples using this DFS implementation is the strongly connected components algorithm. In the algorithm_driver, given an origin airport, DFS will output the action sequences: start visiting a new component, start visiting an airport, and finish visiting an airport. 

We implemented a test helper function that accepts node visiting order sequence and expected operation (new component, start visit node, stop visit node) sequence. The helper function will run DFS against the expected operation sequence, which allows a high precision testing. Test cases include an example graph, an empty graph, an all self-loop graph, an all disconnected graph, an all connected but not strongly connected graph, and a single strongly connected component graph. 

## Strongly Connected Components

The strongly connected components algorithm relies on our DFS implementation. It calls DFS on the transpose of the graph where we consider the nodes in topological sorting order. Finally, each tree in the depth-first forest is a strongly connected component.

(reference: CLRS 3e p. 617)
```
StronglyConnectedConponents(G)

	call DFS(G) to compute finishing time u.f for each vertex u
	compute G^T
	call DFS(G^T), but in the main loop of DFS, consider the vertices in order of decreasing u.f (as computed in the first DFS)
	output the vertices of each tree in the depth-first forest formed in line 3 as a separate strongly connected component
```

To test the full functionality of the algorithm, we implemented various test cases, including a graph with a single simple strongly connected component, a graph with multiple simple strongly connected components, a graph of self-loops, a graph of disjoint points, a large complex strongly connected component with a single disjoint point, an all connected but not strongly connected graph, and more large complex graphs. 

## PageRank

We implemented the PageRank Algorithm in two different ways to find the importance of each airport.

Our first implementation used a simplified iterative method: we generated a probability vector for all the airports and iterated through the graph for a fixed number of iterations. Each time, we update the importance depending on the outflow and inflow of all airports. As we continue on the iteration, the importance score of each airport approaches a steady state. Therefore, after a fixed number of iterations, the obtained resultant vector reflects the relative importance of each airport, which can be ranked in descending order. 

**More information for our first implementation:**
[Correctness Proof and Complexity Analysis](/importance_it_explanation/importance_it.pdf)

In our second implementation, we generated a probability matrix A, where the (i,j) entry represents the inflow received by the airport of index i  from the airport of index j. Note that Av = v is equivalent to solving for the eigenvectors of A with an eigenvalue of 1. In order to solve this linear system, we obtain a matrix B by subtracting 1 from every entry on the main diagonal (i.e. let B = A - I_n where I_n is the n * n identity matrix). Then we solve for B nullspace. 

There are two approaches to find B nullspace. One is LU decomposition. B can be decomposed into LU, where L is a lower triangular matrix and U is an upper triangular matrix, which help us find the solution to our linear system. The other one is Gaussian Elimination. We can use basic row operations to transfer B into Row Reduced Echelon Form. We then extract the last column, multiplied by -1, and changed the (n,n) entry to 1. This is the nullspace of B and the eigenvector of A, which also represents the importance of all airports. 

In our test cases, we first created small graphs and manually calculated the result. We then compared our manually computed PageRank vector with our output vectors from the above three implementations. We also created larger graphs, running all three implementations and requiring all output to be in the same one-dimensional span (i.e. requiring all three result vectors to be collinear). 

Additionally, we have implemented a test case that runs on the largest strongly connected component of the default dataset using all three implementations and requires all output to be in the same one-dimensional span (i.e. requiring all three result vectors to be collinear). By recording the running time, we found that the iterative approach is the fastest with only 4.3 s, while solving for the eigenvector is significantly slower - LU Decomposition took 3 min 19 s, and Gaussian elimination took 9 min 18 s.

## Floyd-Warshall

To find all pairs shortest paths for airports, we implemented the Floyd-Warshall algorithm. In our implementation, we used a matrix `distance` to store the distance of the shortest paths; the (i,j) entry represents the shortest distance between airport of index i and airport of index j. To keep track of the path, we used another matrix `next` to store them. Its (i,j) entry represents the next airport to go to in the shortest path from i to j. In our algorithm, we iterate through each vertex and update every path using that vertex as the intermediate airport in the path. If there exists a shorter path, we simultaneously update distance[i][j] to be the distance using the intermediate points, and next[i][j] to be the index of the intermediate airport. Therefore, after trying all airports as the intermediate airport, we get the shortest distances in matrix distance. We then implemented our path reconstruction function that utilizes the matrix `next` to generate the exact shortest path from any two given airports. 

In the test cases, we compared the distance and the exact path obtained from running the `AllPairsShortestPaths` and `PathReconstruction` with our manually calculated results.
For matrices of size smaller than or equal to 5, we compared all possible shortest distances and shortest paths. For matrices of size larger than 5, we picked 5 pairs to calculate manually and compare our manual result with the output of the program. 

## Conclusion

With Floyd-Warshall, we are able to find the shortest path for all pairs of airports. The detailed shortest path results can be viewed by running `result_interpretor` with `sp` command.
 
According to our PageRank algorithm, the most important airport is Frankfurt am Main Airport located in Frankfurt, Germany. This aligns with the reality since Frankfurt is approximately located in the middle of Europe, allowing it to efficiently transition flights, and a major site for many global corporate headquarters, including the European Central Bank.
