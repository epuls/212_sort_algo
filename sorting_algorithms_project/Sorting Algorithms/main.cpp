#include <iostream>
#include "tree_sort.h"

int main() {
    int arr[5] = {23, 18, 73, 21, 98};
    TreeSort T;
    T.sort(arr, 5);
    for(int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
