# Empirical Analysis of Sorting Algorithms (C++)

This project benchmarks Bubble Sort, Selection Sort, Insertion Sort, and Merge Sort using descending input arrays of sizes 5, 10, 50, and 100.

## Requirements
- C++ compiler supporting C++17 (g++ recommended)

## Compile and run
```bash
g++ -O2 -std=c++17 sorting_analysis.cpp -o sorting_analysis
./sorting_analysis > timings.csv
```

The program performs five runs for every algorithm and input size. To make very short operations measurable, it repeats each sort many times and reports the average time per sort in microseconds. Input copies are prepared before the timed section, so the measured interval focuses on sorting.

## Test data
For each N, the test array contains values N, N-1, ..., 1. This is a worst-case arrangement for the standard Bubble Sort and Insertion Sort implementations, and a consistent reverse-sorted test for the other algorithms.

## Files
- `sorting_analysis.cpp` — source code
- `timings.csv` — sample measured run data (five runs per algorithm and size)
- `Sorting_Analysis_Report.pdf` — report with averages, graph, and analysis
- `sorting_times.png` — plotted average execution time

Timing values depend on the computer, compiler, operating system, and background processes. Re-run the program on your own computer for your final measured values.
