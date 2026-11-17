#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;

void bubbleSort(vector<int>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < a.size() - i; ++j) {
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); swapped = true; }
        }
        if (!swapped) break;
    }
}
void selectionSort(vector<int>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < a.size(); ++j)
            if (a[j] < a[minIndex]) minIndex = j;
        swap(a[i], a[minIndex]);
    }
}
void insertionSort(vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        int key = a[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; --j; }
        a[j + 1] = key;
    }
}
void merge(vector<int>& a, int left, int mid, int right) {
    vector<int> L(a.begin() + left, a.begin() + mid + 1);
    vector<int> R(a.begin() + mid + 1, a.begin() + right + 1);
    size_t i = 0, j = 0; int k = left;
    while (i < L.size() && j < R.size()) a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) a[k++] = L[i++];
    while (j < R.size()) a[k++] = R[j++];
}
void mergeSortRec(vector<int>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRec(a, left, mid); mergeSortRec(a, mid + 1, right); merge(a, left, mid, right);
}
void mergeSort(vector<int>& a) { if (!a.empty()) mergeSortRec(a, 0, static_cast<int>(a.size()) - 1); }

int main() {
    const vector<string> names = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort"};
    const vector<void(*)(vector<int>&)> sorts = {bubbleSort, selectionSort, insertionSort, mergeSort};
    const vector<int> sizes = {5, 10, 50, 100};
    const vector<int> repetitions = {100000, 50000, 5000, 1000};
    const int runs = 5;
    volatile long long checksum = 0;
    cout << "Algorithm,N,Run,Repetitions,AverageTime_us\n";
    for (size_t s = 0; s < sizes.size(); ++s) {
        vector<int> worstCase(sizes[s]);
        iota(worstCase.rbegin(), worstCase.rend(), 1); // N, N-1, ..., 1
        for (size_t alg = 0; alg < sorts.size(); ++alg) {
            for (int run = 1; run <= runs; ++run) {
                vector<vector<int>> testCases(repetitions[s], worstCase); // prepare inputs before timing
                auto start = Clock::now();
                for (auto& data : testCases) {
                    sorts[alg](data);
                    checksum += data[data.size() / 2];
                }
                auto finish = Clock::now();
                double total_us = chrono::duration<double, micro>(finish - start).count();
                cout << names[alg] << ',' << sizes[s] << ',' << run << ',' << repetitions[s] << ','
                     << fixed << setprecision(6) << total_us / repetitions[s] << '\n';
            }
        }
    }
    cerr << "Checksum: " << checksum << '\n';
    return 0;
}
