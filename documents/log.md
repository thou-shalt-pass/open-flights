# Development Log

## 4/1/2022

### Goal of the week

We should finish preprocess all the route and airport data, including adding re-check-in value to each airport.

### Tasks Accomplished

- Leo Luo: finished preprocessing route.csv
- Yanzhen Shen: finished preprocessing airport.csv
- Yirong Chen: finished draft of file structure for algorithms

### Problem Encountered

No problem encountered for this week

### Plan for Next Week

Finish basic structure

## 4/9/2022

### Goal of the week

Modify the proposal to meet all requirements and adjust the project structure accordingly.

### Tasks Accomplished

- Leo Luo, Yanzhen Shen, Yirong Chen: Discussed changes to our proposal, modified our planned data structure and removed airport re-check-in values.

### Problem Encountered

No problem encountered for this week

### Plan for Next Week

Finish implementing PageRank.

## 4/16/2022

### Goal of the week

Finish implementing Pagerank algorithm, check if the result converges as iteration increases

### Tasks Accomplished

- Yirong Chen: set up bijection between IATA code and index of each airport in adjacency matrix; implmeneted PageRank using fixed number of iterations; implemented DFS and strongly connected components
- Leo Luo: stored airports and airlines data into desired structures; implemented Haversine formula to calculate the distance between two airports given latitude and longitude
- Yanzhen Shen: implemented algorithm to find a nullspace within the adjacency matrix

### Problem Encountered

- When we tried to read airports from the csv file, we noticed that the file also included military air base, which do not hold a valid IATA code. We removed those data entries from the csv file.

- We also noticed some airport names include extra commas, we had to read through each character to tranverse the file.

- Our PageRank algorithm is buggy (sum of the "importance score" does not add up to 1; it sums up to 0.55 ish). This is likely caused by the disconnected graphs.

### Plan for Next Week

- Extract the largest set of strongly connected components and run PageRank on that to check if our implementation is correct or not
- Implment Floy-Warshall algorithm to find the shortest path
- Add more test cases to check if our DFS and strongly connected components are running properly

## 4/23/2022

### Goal of the week

Implement test cases for strongly connected components, DFS; implement Floyd-Warshall algorithm;

### Tasks Accomplished

- Yirong Chen: implemented helper function (for testing) and test cases for DFS 
- Leo Luo: implemented test cases for strongly connected components
- Yanzhen Shen: implemented Floyd-Warshall algorithm and its test case

### Problem Encountered

- `ImportanceEigenvector` does not give expected output because of approximation error caused by `double`. We substitude double with `fraction` to solve this.
- However, `fraction` is incredible slow when solving the eigenvector 

### Plan for Next Week

- Finish writing readme on github
- Finish `results.md`
- Answer the leading question to our project (shortest path between given airports and most important airports)

## 5/1/2022

### Goal of the week

Finish writing readme and report

### Tasks Accomplished

- Yirong Chen, Leo Luo, and Yanzhen Shen: finished implementing drivers for test runs; finished writing most part of readme, report, and slides

### Problem Encountered

- The output for running the driver was too large (~800MB), so we have to compress the precomputed into `result.tar.gz` to push onto github. 

### Plan for Next Week

- Record the presentation video

