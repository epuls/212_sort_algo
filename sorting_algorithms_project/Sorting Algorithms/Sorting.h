#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

#include <iostream>
#include <vector>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>
#include <random> //used for randomly populating vectors

//runtime clocking
#include <ctime>
#include <cstdint>
#include <iomanip>

#include <chrono> //used for calculating benchmark runtime

#include <algorithm> //used for max_element during benchmark
#include <filesystem> //used for checking if benchmark was completed

class Sorting {
public:
    Sorting(std::vector<int> sortData, int mode, int benchmarkVecType);
    ~Sorting();
    enum SortingType {INSERTION, MERGE, QUICK, TREE};
    float ClockOutput;

    std::vector<int> Data;

    //main sort function to handle various options
    void Sort(bool measureClock, bool print);

    //core sorting algorithm drivers.
    void InsertionSort(std::vector<int>& data);
    void MergeSort(std::vector<int>& data);
    void QuickSort(std::vector<int>& data);
    void TreeSort(std::vector<int>& data);

    const static int INITIAL_BENCHMARK_MAX = 2000; //how large the autosort benchmark will run to
    const static int DATA_SIZE = 5000; //size of generated data
    int benchmark_override;
    int data_override;

    std::string GetSortName(int mode);

    //made public so we can access from main
    std::vector<int> MakeRandomUnsortedVec(int size);
    std::vector<int> MakeReverseSortedVec(int size);
    std::vector<int> MakePartiallySortedVec(int size);
    std::vector<int> MakeSortedVec(int size);
    std::vector<std::vector<int>> MakeBenchmarkVecs(int count, int mode);

private:
    std::vector<std::map<int, float>> benchmarkMaps;
    int _benchmarkVecCreationMode = 0;

    void pickSort(std::vector<int>& data, int method = 1); //define how to pick sort, private helper called from AutoSort
    void measureTiming(SortingType sortingType, bool print); //call sorts from this func to measure timing

    void benchmark(int vecSize, int autoMode);
    void tryLoadBenchmark();
    std::pair<int, int> tryLoadSettings();

    SortingType _sortingType;

    //merge sort helpers
    static void mergeem(int L, int M, int R, std::vector<int>& array1);
    static void mergesort(int L, int R, std::vector<int>& array1);

    //quick sort helpers
    static int partition(std::vector<int>& arr, int start, int end);
    static void quickSort(std::vector<int>& arr, int start, int end);

};

#endif //SORTING_SORTING_H