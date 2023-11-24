#include "Sorting.h"
#include "tree_sort.h"
#include "tree_sort.cpp"


//constructors/destructors
Sorting::Sorting(std::vector<int> sortData, int mode) {
    Data = sortData;

    //throw error if mode argument is out of bounds
    if(mode < 0 | mode > 4){
        std::cerr << "undefined sorting mode";
        std::exit(-1);
    }

    //set sorting type (4 is the auto sort)
    if(mode == 4)
        pickSort(sortData);
    else
        _sortingType = static_cast<SortingType>(mode); //this casts the input arg to our enum
}

Sorting::~Sorting() = default;

//---------------------------------------------private functions-------------------------------------------------------
//the auto sort function that picks sorting type by vector size
//TODO: flesh out after analysing sort times
void Sorting::pickSort(std::vector<int> &data) {
    //following same logic as before for testing purposes
    int size = data.size();
    if(size <= 5)
        _sortingType = INSERTION;
    else if (size <= 25)
        _sortingType = TREE;
    else
        _sortingType = INSERTION;
}

// TODO modify to write to .csv file here I think -ethen
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
            TreeSort(Data);
            c_end = std::clock();
            break;
    }

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    //will need to figure out how we want to output our timing values. Will probably need to write to file so we can plot
    std::cout << std::fixed << std::setprecision(4) << output << " Output: " << val << std::endl;
}

void Sorting::mergeem(int L, int M, int R, std::vector<int> &array1) {
    //vector<int>
    int a1= M-L+1;
    int a2= R-M;
    //int a=0,b=,c=L;
    std::vector<int> left(a1); //temp array 1
    std::vector<int> right(a2);//temp array 2
    for(int i=0;i<a1;i++){
        left[i]=array1[L+i];
    }for(int j=0;j<a2;j++){
        right[j]=array1[M+1+j];
    }
    int a=0,b=0,c=L;// put temp array back to original array
    for(;a<a1 && b<a2;c++){
        if(left[a]<=right[b]){
            array1[c]=left[a];
            a++;
        }else{
            array1[c]=right[b];
            b++;
        }
    }
    for(;a<a1;a++,c++){// copies remaining ints from left and right
        array1[c]=left[a];
        //c++;
    }for(;b<a2;b++,c++){
        array1[c]=right[b];
    }
}

void Sorting::mergesort(int L, int R, std::vector<int> &array1) {
    if(L<R){
        int M=L+(R-L)/2;
        mergesort(L,M,array1);
        mergesort(M+1,R,array1);
        mergeem(L,M,R,array1);
    }
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
    mergesort(0, data.size()-1, data);
}

void Sorting::QuickSort(std::vector<int> &data) {
//TODO: put quick sort code here
}

void Sorting::TreeSort(std::vector<int>& data){
    //need to use class keyword here due to scoping...TreeSort is the name of a public func and a class.
    class TreeSort T;
    T.sort(data);
}

//Main sorting function. Either calls the measureTiming function to sort and record time, or calls the sorting functions directly
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
                TreeSort(Data);
                break;
        }
    }
}


