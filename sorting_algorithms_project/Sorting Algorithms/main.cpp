
#include <iostream>
#include <fstream>
#include <sstream>

#include "tree_sort.h"
#include "Sorting.h"
#include "Sorting.cpp" //i might be dumb but not sure why i am getting an error without this.



void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

//3 args: filename, clock speed(0 or 1), sort type (0 for insertion, 1 for merge, 2 for quick, 3 for tree
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

    print(inputData);


    //create Sorting object
    Sorting sortObj(inputData, sortType);

    sortObj.Sort(measureClock);
    print(sortObj.Data);


    /*
    std::vector<int> vec = {7,67,68,84,94};
    TreeSort T;
    std::cout << "Unsorted: ";
    T.sort(vec);
    Sorting::InsertionSort(vec);
    print(vec);
    std::cout << std::endl;

    if(vec.size() >= 5){
        T.sort(vec);
        print(vec);
        std::cout << "Sorted with Tree Sort\n";
    } else {
        Sorting::InsertionSort(vec);
        print(vec);
        std::cout << "Sorted with Insertion Sort\n";
    }
     */

}

