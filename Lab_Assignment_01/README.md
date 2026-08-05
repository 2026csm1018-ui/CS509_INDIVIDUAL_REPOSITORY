# Matrix Multiplication using GEMM

This project implements two approaches for matrix multiplication in C++:

- Simple Matrix Multiplication
- Blocked (Tiled) Matrix Multiplication

The program executes both algorithms on the same set of input matrices, records their execution time, and stores the results in output files.

---

## Files

```
Driver.cpp              -> Driver program
matrix.h                -> Matrix class declaration
matrix.cpp              -> Matrix class implementation

gemm_simple.h           -> Simple GEMM function declaration
gemm_simple.cpp         -> Simple GEMM implementation

gemm_blocking.h         -> Blocked GEMM function declaration
gemm_blocking.cpp       -> Blocked GEMM implementation

Test_Cases/
    INPUT_FILES/        -> Input test cases
    OUTPUT_FILES/       -> Generated output files
```

---

## Input Format

Each input file should follow the format:

```
M K N

Matrix A

Matrix B
```

Example

```
2 3 2

1 2 3
4 5 6

7 8
9 10
11 12
```

where

- Matrix A is of size **M × K**
- Matrix B is of size **K × N**

---

## Output Format

For every input file, an output file is generated.

Example

```
Input File: sample.txt

Algorithm: SIMPLE_ALGO
Execution Time: 146 microseconds
Resultant Matrix:
...

Algorithm: BLOCKING_ALGO
Execution Time: 89 microseconds
Resultant Matrix:
...
```

---

## Compilation

```bash
g++ -std=c++17 Driver.cpp matrix.cpp gemm_simple.cpp gemm_blocking.cpp -o run
```

---

## Execution

```bash
./run
```

The program automatically processes every input file present in

```
Test_Cases/INPUT_FILES
```

and stores the corresponding output in

```
Test_Cases/OUTPUT_FILES
```

---

## Algorithms

### Simple Matrix Multiplication

Uses the conventional triple nested loop approach.

### Blocked Matrix Multiplication

Divides the matrices into fixed-size blocks (32 × 32) to improve cache utilization while performing multiplication.

---

## Time Complexity

| Algorithm | Time Complexity |
|-----------|-----------------|
| Simple GEMM | O(M × K × N) |
| Blocked GEMM | O(M × K × N) |

---

## Benchmark Results

| Test File | Matrix Size | Simple Time (µs) | Blocking Time (µs) |
|-----------|:-----------:|-----------------:|-------------------:|
| test_10_1.txt | 10 × 10 | 16 | 16 |
| test_10_2.txt | 10 × 10 | 15 | 16 |
| test_100_1.txt | 100 × 100 | 14,646 | 14,734 |
| test_100_2.txt | 100 × 100 | 14,342 | 14,544 |
| test_500_1.txt | 500 × 500 | 1,876,129 | 1,877,213 |
| test_500_2.txt | 500 × 500 | 1,781,373 | 1,870,577 |
| test_1000_1.txt | 1000 × 1000 | 14,438,089 | 14,391,788 |
| test_1000_2.txt | 1000 × 1000 | 13,921,194 | 14,392,732 |
| test_2000_1.txt | 2000 × 2000 | 144,791,206 | 117,379,461 |
| test_2000_2.txt | 2000 × 2000 | 147,669,707 | 117,800,542 |

---

## Author

Shahid Alam

M.Tech CSE, IIT Ropar
