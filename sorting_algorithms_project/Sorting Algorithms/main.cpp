#include <iostream>
#include <fstream>
#include <sstream>

#include "tree_sort.h"
#include "Sorting.cpp" //I might be dumb but not sure why I am getting an error without this.

// TODO Add Functions:
//  1. function to create .txt files with varying sizes of randomly populated arrays
//   1a. do we put this as a command line argument to generate new data?
//  2. function to record timings for each sorting function and write to a .csv file for plotting
//   2a. need to add functionality to read multiple input files at a time so we don't have to run the program over and over
//   2b. thinking for 1 and 2 we create an analysis class (analysis.cpp/analysis.h) that handles data creation/timing
//  3. add to merge sort function
//  4. add to quick sort function


void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << '\n';
}

//3 args: filename, measure timing(0 or 1), sort type (0 for insertion, 1 for merge, 2 for quick, 3 for tree, 4 for auto)
int main(int argc, char *argv[]) {
    //args
    std::ifstream ifs(argv[1]); 
    bool measureClock = std::stoi(argv[2]);
    int sortType = std::stoi(argv[3]);

    //data
    std::vector<int> inputData;

    //parsing
    std::string line;
    std::getline(ifs, line);
    std::stringstream ss(line);

    int tmp;
    while(ss >> tmp){
        inputData.push_back(tmp);
    }

    //create Sorting object with read in data and sorting type
    Sorting sortObj(inputData, sortType);

    std::cout<<"Unsorted array: ";
    print(inputData);

    //sort the data. I have the Sort function just taking in a bool but could move this to the constructor, w/e
    sortObj.Sort(measureClock);

    std::cout<<"Sorted array: ";
    print(sortObj.Data);
}

