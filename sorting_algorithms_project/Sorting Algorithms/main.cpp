#include <iostream>
#include "tree_sort.h"
void insertionSort(std::vector<int>& data)
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
    insertionSort(vec);
    print(vec);
}
