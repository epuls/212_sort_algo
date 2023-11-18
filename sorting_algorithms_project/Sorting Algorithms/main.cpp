#include <iostream>
#include "tree_sort.h"

void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {7,67,68,84,94,12,13,82,420,632,932,931};
    TreeSort T;
    T.sort(vec);
    print(vec);
}
