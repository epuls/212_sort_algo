#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>
//runtime clocking
#include <ctime>
#include <cstdint>
#include <iomanip>

#include "tree_sort.h"



class Sorting {
public:
    Sorting(std::vector<int> sortData, int mode);
    ~Sorting();
    enum SortingType {INSERTION, MERGE, QUICK, TREE};

    std::vector<int> Data;

    //main sort function to handle various options
    void Sort(bool measureClock);

    //static and can be directly called if desired
    static void InsertionSort(std::vector<int>& data);
    static void MergeSort(std::vector<int>& data);
    static void QuickSort(std::vector<int>& data);
    static void TreeSort(std::vector<int>& data);

private:
    void pickSort(std::vector<int>& data); //define how to pick sort, private helper called from AutoSort
    void measureTiming(SortingType sortingType); //call sorts from this func to measure timing
    SortingType _sortingType;
};

#endif //SORTING_H