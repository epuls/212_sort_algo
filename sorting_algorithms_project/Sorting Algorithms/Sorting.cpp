#include "Sorting.h"

//constructors/destructors
Sorting::Sorting(std::vector<int> sortData, int mode) {
    Data = sortData;
    //set Sorting type
    if(mode == 4)
        pickSort(sortData);
    else
        _sortingType = static_cast<SortingType>(mode); //this casts the input arg to our enum
}

Sorting::~Sorting() {

}

//---------------------------------------------private functions-------------------------------------------------------
void Sorting::pickSort(std::vector<int> &data) {
    //arbitrarily setting Sorting type to insertion until this is built
    _sortingType = INSERTION;
}

//modified implementation from lab 02
void Sorting::measureTiming(SortingType sortingType) {
    uint64_t val;

    unsigned long c_start, c_end;

    //wasn't sure if throwing c_start before the switch and c_end after would add a tiny bit of extra time so running it in each case
    switch(sortingType){
        case(INSERTION):
            c_start = std::clock();
            InsertionSort(Data);
            c_end = std::clock();
            break;
        case(MERGE):
            c_start = std::clock();
            MergeSort(Data);
            c_end = std::clock();
            break;
        case(QUICK):
            c_start = std::clock();
            QuickSort(Data);
            c_end = std::clock();
            break;
        case(TREE):
            c_start = std::clock();
            //not yet implemented
            c_end = std::clock();
            break;
    }

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    //will need to figure out how we want to output our timing values
    std::cout << std::fixed << std::setprecision(4) << output << " Output: " << val << std::endl;
}

//---------------------------------------------public functions--------------------------------------------------------
void Sorting::InsertionSort(std::vector<int>& data)
{
    int i, key, j;
    int n = data.size();
    for (i = 1; i < n; i++) {
        key = data[i];
        j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

void Sorting::MergeSort(std::vector<int>& data) {

}

void Sorting::QuickSort(std::vector<int> &data) {

}

//either call the sort that measures timing or call the sorting functions themselves
void Sorting::Sort(bool measureClock) {
    if(measureClock)
        measureTiming(_sortingType);
    else{
        switch(_sortingType){
            case(INSERTION):
                InsertionSort(Data);
                break;
            case(MERGE):
                MergeSort(Data);
                break;
            case(QUICK):
                QuickSort(Data);
                break;
            case(TREE):
                //yes
                break;
        }
    }

}












