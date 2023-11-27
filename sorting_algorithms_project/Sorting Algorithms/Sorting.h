#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

#include <iostream>
#include <vector>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

//runtime clocking
#include <ctime>
#include <cstdint>
#include <iomanip>

#include <algorithm> //used for max_element during benchmark
#include <filesystem> //used for checking if benchmark was completed




class Sorting {
public:
    Sorting(std::vector<int> sortData, int mode);
    ~Sorting();
    enum SortingType {INSERTION, MERGE, QUICK, TREE};
    float ClockOutput;

    std::vector<int> Data;

    //main sort function to handle various options
    void Sort(bool measureClock, bool print);

    //static and can be directly called if desired
    static void InsertionSort(std::vector<int>& data);
    static void MergeSort(std::vector<int>& data);
    static void QuickSort(std::vector<int>& data);
    static void TreeSort(std::vector<int>& data);

    std::string GetSortName(int mode);

private:
    std::vector<std::map<int, float>> benchmarkMaps;

    void pickSort(std::vector<int>& data, int method = 1); //define how to pick sort, private helper called from AutoSort
    void measureTiming(SortingType sortingType, bool print); //call sorts from this func to measure timing
    std::vector<int> makeRandomUnsortedVec(int size);
    std::vector<std::vector<int>> unsortedVec(int count);
    void benchmark(int vecSize, int algCount = 4, int mode = 0);
    void tryLoad(int mode = 0);

    SortingType _sortingType;

    //merge sort helpers
    static void mergeem(int L, int M, int R, std::vector<int>& array1);
    static void mergesort(int L, int R, std::vector<int>& array1);

    //quick sort helpers
    static int partition(std::vector<int>& arr, int start, int end);
    static void quickSort(std::vector<int>& arr, int start, int end);

};

#endif //SORTING_SORTING_H