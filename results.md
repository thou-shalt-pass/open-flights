# Project Report
## Data Processing
Files: `data.cpp` and `data.h`
From the preprocessed CSV files, we stored each airport as a node with the city name, the name of the airport, the IATA code, the longitude, and the latitude. We also stored every route as a weighted edge using distance calculated from Haversine formula using the longitude and the latitude. We then constructed an adjacency list and an adjacency matrix to connect notes with weighted edges to represent the directed graph.

## Floyd-Warshall

To find all pairs shortest paths for airports, we implemented the Floyd-Warshall algorithm. In our implementation, we used a matrix `distance` to store the distance of the shortest paths; the (i,j) entry represents the shortest distance between airport of index i and airport of index j. To keep track of the path, we used another matrix `next` to store the shortest paths. Its (i,j) entry represents the next airport to go to in the shortest path from i to j. In our algorithm, we iterate through each vertex and update every path using that vertex as the intermediate airport in the path. If there exists a shorter path, we simultaneously update distance[i][j] to be the distance using the intermediate points, and next[i][j] to be the index of the intermediate airport. Therefore, after trying all airports as the intermediate airport, we get the shortest distances in matrix distance. We then implemented our path reconstruction function that utilizes the matrix `next` to generate the exact path from any two given airports. 

In the test case, we compared the distance and the exact path obtained from running the `AllPairsShortestPaths` and `PathReconstruction` with our manually calculated results.
For matrices of size smaller than or equal to 5, we compare all possible shortest distances and shortest paths. For matrices of size larger than 5, we pick 5 pairs to calculate manually and compare our manual result with our program’s output. 

## DFS

We implemented the recursive version DFS. The DFS function accepts an adjacency list and many function objects that allow the program to execute custom actions in the specified slots including `before_component`, `start_visit`, and `stop_visit`. It also allows specifying the node visit order. One of the examples using this DFS is the strongly connected components algorithm. In the algorithm driver, given an origin airport, DFS will output the action sequences including start visiting a new component, start visiting an airport, and finish visiting an airport. 

We implemented a test helper function that accepts node visiting order sequence and expected operation (new component, start visit node, stop visit node) sequence. The helper function will run DFS against the expected operation sequence. This allows high precision testing. Test cases include an example graph, an empty graph, an all self-loop graph, an all disconnected graph, an all connected but not strongly connected graph, and a single strongly connected component graph. 

## Strongly Connected Components

The strongly connected components algorithm relies on DFS. It first calls DFS and records the order of nodes’ finish visiting time. Then it calls the second DFS on the transpose of the graph in the node visiting order of decreasing nodes’ finish visiting time in the first DFS. Finally, each tree in the depth-first forest is a strongly connected component.

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

Our first implementation used a simplified iterative method:  we generated a probability vector for all the airports and iterated through the graph for a fixed number of iterations. Each time, we update the importance depending on the outflow and inflow of all airports. As we continue on the iteration, the importance score of each airport approaches a steady state. Therefore, after a fixed number of iterations, the resultant vector we obtained reflects the relative importance of each airport, which can be ranked in descending order. 

In our second implementation, we generated a probability matrix A, where the (i,j) entry represents the inflow received by the airport of index i  from the airport of index j.  Given that Av = v, this is equivalent to solving for the eigenvectors of A with an eigenvalue of 1. In order to solve this linear system, we obtain a matrix A* by subtracting 1 from every entry on the main diagonal, then we solve for A* nullspace. 

There are two approaches to find A* nullspace. One is LU decomposition. A can be decomposed into L*U, where L is a lower triangular matrix and U is an upper triangular matrix.[unfinished]. The other one is Gaussian Elimination. We can  use basic row operations to transfer A into Row Reduced Echelon Form. We then extract the last column, multiplied by -1, and changed the (n,n) entry to 1. This is the nullspace of A* and the eigenvector of A, which also represents the importance of all airports. 

In our test cases, we first created small graphs and manually calculated the result. We then compared our manual result with our function output using the above three implementations. We also created larger graphs, running all three implementations and requiring all output to be the same. Additionally, we have implemented a test case that runs the real dataset using all three implementations and requires all output to be the same. 

We also recorded the time taken to run the above three implementation on the largest strongly connected component in the dataset, and found that the iterative approach is the fastest with only 4.3 s, while solving for the eigenvector is significantly slower - LU Decomposition took 3 min 19 s, and Gaussian elimination took 9 min 18 s.

## Conclusion

According to our PageRank algorithm, the most important airport is Frankfurt am Main Airport located in Frankfurt, Germany. This seems to align with the reality since Frankfurt is approximately located in the middle of Europe, allowing it to effectively transition flights, and a major site for many global corporate headquarters, including the European Central Bank.
