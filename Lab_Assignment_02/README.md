# CS527 Assignment 2

## Overview

This assignment implements two shortest path algorithms:

-   Bellman-Ford
-   Floyd-Warshall

The input graphs are provided in edge-list format. Before executing the
algorithms, the input graph is converted into Compressed Sparse Row
(CSR) representation.

The driver program allows the user to select Bellman-Ford,
Floyd-Warshall, or both algorithms. It automatically processes all test
cases present in the corresponding input directories and generates
output files in the corresponding output directories.

------------------------------------------------------------------------

## Directory Structure

``` text
Lab_Assignment_02/
│
├── testcases/
│   ├── input/
│   │   ├── bellmanford/
│   │   │   ├── bf_10.txt
│   │   │   ├── bf_100.txt
│   │   │   ├── bf_10000.txt
│   │   │   ├── bf_50000.txt
│   │   │   └── bf_100000.txt
│   │   │
│   │   └── floydwarsal/
│   │       ├── fw_10.txt
│   │       ├── fw_100.txt
│   │       ├── fw_500.txt
│   │       ├── fw_1000.txt
│   │       └── fw_2000.txt
│   │
│   └── outputs/
│       ├── bellmanford/
│       └── floydwarsal/
│
├── driver.cpp
├── graph.cpp
├── graph.h
├── make_csr.cpp
├── make_csr.h
├── run
└── README.md
```

------------------------------------------------------------------------

## Input Format

The input graphs are stored in edge-list format.

The first line contains:

``` text
V E SOURCE
```

where:

-   `V` = number of vertices
-   `E` = number of edges
-   `SOURCE` = source vertex

The next `E` lines contain:

``` text
u v weight
```

where:

-   `u` = source vertex
-   `v` = destination vertex
-   `weight` = weight of the edge

Example:

``` text
5 6 0
0 1 4
0 2 2
1 2 1
1 3 5
2 3 8
3 4 3
```

Vertices are numbered from `0` to `V-1`.

------------------------------------------------------------------------

## Graph Representation

The input graph is provided as an edge list and is converted into CSR
representation before execution.

The conversion is handled by:

``` text
make_csr.cpp
make_csr.h
```

The overall flow is:

``` text
Edge List
    |
    v
make_csr()
    |
    v
CSR Graph
    |
    +----------------------+
    |                      |
    v                      v
Bellman-Ford        Floyd-Warshall
    |                      |
    +----------+-----------+
               |
               v
          Output File
```

------------------------------------------------------------------------

## Algorithms

### 1. Bellman-Ford

Bellman-Ford computes the shortest distance from a given source vertex
to all other vertices.

The test cases contain:

``` text
10
100
10000
50000
100000
```

vertices.

The source vertex used in the provided test cases is `0`.

The implementation also checks whether the graph contains a
negative-weight cycle.

### Complexity

``` text
Time Complexity  : O(VE)
Space Complexity : O(V)
```

------------------------------------------------------------------------

### 2. Floyd-Warshall

Floyd-Warshall computes the shortest distance between every pair of
vertices.

The test cases contain:

``` text
10
100
500
1000
2000
```

vertices.

The implementation also checks whether the graph contains a
negative-weight cycle.

### Complexity

``` text
Time Complexity  : O(V³)
Space Complexity : O(V²)
```

------------------------------------------------------------------------

## Driver Program

The driver provides three options:

``` text
======================================
1. Bellman-Ford
2. Floyd-Warshall
3. Both Algorithms
======================================
Enter your choice :
```

### Option 1 - Bellman-Ford

All files in:

``` text
testcases/input/bellmanford/
```

are processed.

The generated output files are stored in:

``` text
testcases/outputs/bellmanford/
```

### Option 2 - Floyd-Warshall

All files in:

``` text
testcases/input/floydwarsal/
```

are processed.

The generated output files are stored in:

``` text
testcases/outputs/floydwarsal/
```

### Option 3 - Both Algorithms

Both sets of test cases are processed independently.

------------------------------------------------------------------------

## Test Cases

  -----------------------------------------------------------------------
  Algorithm               Test Files              Number of Vertices
  ----------------------- ----------------------- -----------------------
  Bellman-Ford            `bf_10.txt`,            10, 100, 10,000,
                          `bf_100.txt`,           50,000, 100,000
                          `bf_10000.txt`,         
                          `bf_50000.txt`,         
                          `bf_100000.txt`         

  Floyd-Warshall          `fw_10.txt`,            10, 100, 500, 1,000,
                          `fw_100.txt`,           2,000
                          `fw_500.txt`,           
                          `fw_1000.txt`,          
                          `fw_2000.txt`           
  -----------------------------------------------------------------------

------------------------------------------------------------------------

# 11. Results

## 11.1 Bellman-Ford / Floyd-Warshall Results Table

The following table contains the readings obtained from the generated output files.

| Algorithm | Test File | Vertices | Edges | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
|---|---|---:|---:|---:|---|---|---|---:|---|
| Bellman-Ford | `bf_10.txt` | 10 | 40 | 0 | No | Shortest Distances | Shortest distances generated | 29 μs | Recorded |
| Bellman-Ford | `bf_100.txt` | 100 | 400 | 0 | No | Shortest Distances | Shortest distances generated | 265 μs | Recorded |
| Bellman-Ford | `bf_10000.txt` | 10,000 | 40,000 | 0 | No | Shortest Distances | Shortest distances generated | 18,601 μs | Recorded |
| Bellman-Ford | `bf_50000.txt` | 50,000 | 200,000 | 0 | No | Shortest Distances | Shortest distances generated | 21,130 μs | Recorded |
| Bellman-Ford | `bf_100000.txt` | 100,000 | 400,000 | 0 | No | Shortest Distances | Shortest distances generated | 43,115 μs | Recorded |
| Floyd-Warshall | `fw_10.txt` | 10 | 40 | N/A | No | Shortest Distance Matrix | Shortest distance matrix generated | 98 μs | Recorded |
| Floyd-Warshall | `fw_100.txt` | 100 | 400 | N/A | No | Shortest Distance Matrix | Shortest distance matrix generated | 26,601 μs | Recorded |
| Floyd-Warshall | `fw_500.txt` | 500 | 2,000 | N/A | No | Shortest Distance Matrix | Shortest distance matrix generated | 588,503 μs | Recorded |
| Floyd-Warshall | `fw_1000.txt` | 1,000 | 4,000 | N/A | No | Shortest Distance Matrix | Shortest distance matrix generated | 4,607,677 μs | Recorded |
| Floyd-Warshall | `fw_2000.txt` | 2,000 | 8,000 | N/A | No | Shortest Distance Matrix | Shortest distance matrix generated | 36,039,869 μs | Recorded |

All reported test cases have `Negative Weight Cycle: NO`.

### Bellman-Ford Readings

| Test File | Vertices | Edges | Source | Execution Time | Negative Weight Cycle |
|---|---:|---:|---:|---:|---|
| `bf_10.txt` | 10 | 40 | 0 | 29 μs | No |
| `bf_100.txt` | 100 | 400 | 0 | 265 μs | No |
| `bf_10000.txt` | 10,000 | 40,000 | 0 | 18,601 μs | No |
| `bf_50000.txt` | 50,000 | 200,000 | 0 | 21,130 μs | No |
| `bf_100000.txt` | 100,000 | 400,000 | 0 | 43,115 μs | No |

### Floyd-Warshall Readings

| Test File | Vertices | Edges | Execution Time | Negative Weight Cycle |
|---|---:|---:|---:|---|
| `fw_10.txt` | 10 | 40 | 98 μs | No |
| `fw_100.txt` | 100 | 400 | 26,601 μs | No |
| `fw_500.txt` | 500 | 2,000 | 588,503 μs | No |
| `fw_1000.txt` | 1,000 | 4,000 | 4,607,677 μs | No |
| `fw_2000.txt` | 2,000 | 8,000 | 36,039,869 μs | No |

---

## Performance Analysis

### Bellman-Ford

| Vertices | Edges | Time |
|---:|---:|---:|
| 10 | 40 | 29 μs |
| 100 | 400 | 265 μs |
| 10,000 | 40,000 | 18,601 μs |
| 50,000 | 200,000 | 21,130 μs |
| 100,000 | 400,000 | 43,115 μs |

### Floyd-Warshall

| Vertices | Edges | Time |
|---:|---:|---:|
| 10 | 40 | 98 μs |
| 100 | 400 | 26,601 μs |
| 500 | 2,000 | 588,503 μs |
| 1,000 | 4,000 | 4,607,677 μs |
| 2,000 | 8,000 | 36,039,869 μs |

The readings show a much faster increase in execution time for Floyd-Warshall as the number of vertices increases. This is consistent with the cubic time complexity of the algorithm.

# Compilation

Compile the project using:

``` bash
g++ -std=c++17 driver.cpp graph.cpp make_csr.cpp -o driver
```

If additional source files are added to the project, they should also be
included in the compilation command.

------------------------------------------------------------------------

## Running the Program

Run the executable using:

``` bash
./driver
```

The program displays:

``` text
======================================
1. Bellman-Ford
2. Floyd-Warshall
3. Both Algorithms
======================================
Enter your choice :
```

Enter `1` to run Bellman-Ford.

Enter `2` to run Floyd-Warshall.

Enter `3` to run both algorithms.

------------------------------------------------------------------------

## Output Files

For every input file, a corresponding output file is generated.

For example:

``` text
testcases/input/bellmanford/bf_100.txt
```

produces:

``` text
testcases/outputs/bellmanford/bf_100_output.txt
```

Similarly:

``` text
testcases/input/floydwarsal/fw_100.txt
```

produces:

``` text
testcases/outputs/floydwarsal/fw_100_output.txt
```

Each output file contains the input graph information, algorithm name,
execution time, negative-cycle information, and the corresponding
shortest-path output.

------------------------------------------------------------------------

## Notes

-   Input graphs are stored in edge-list format.
-   Input graphs are converted to CSR before execution.
-   Vertices are numbered from `0` to `V-1`.
-   Bellman-Ford uses the source vertex specified in the input file.
-   Floyd-Warshall computes shortest paths between all pairs of
    vertices.
-   No negative-weight cycle was detected in the provided test cases.
-   Execution time is reported in microseconds.
-   The larger Bellman-Ford test cases are sparse.
-   Floyd-Warshall is tested up to 2,000 vertices because of its `O(V³)`
    time and `O(V²)` space requirements.
