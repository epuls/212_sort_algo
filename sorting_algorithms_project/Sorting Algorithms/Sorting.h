#ifndef TREE_SORT_SORTING_H
#define TREE_SORT_SORTING_H
#include <iostream>
#include <vector>
//runtime clocking
#include <ctime>
#include <cstdint>
#include <iomanip>

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

private:
    void pickSort(std::vector<int>& data); //define how to pick sort, private helper called from AutoSort
    void measureTiming(SortingType sortingType); //call sorts from this func to measure timing
     //not yet implemented. do we want to cache the data here and clean up our main?
    SortingType _sortingType;
};


#endif //TREE_SORT_SORTING_H
