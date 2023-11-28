
#include "Sorting.h"


void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << '\n';
}

//generates .csv file measuring clock speed of sorts on randomly populated arrays. Will name the file based on
//the vectors that were created/sorted
void genData(int sortMode, std::string fname, int makeVecMode, int arrayCount){
    std::ofstream myFile;
    std::string fname_verbose = fname;

    switch(makeVecMode) {
        default:
            break;
        case (0):
            fname_verbose += "_random_vec.csv";
            break;
        case (1):
            fname_verbose += "_reverse_sorted_vec.csv";
            break;
        case (2):
            fname_verbose += "_partially_sorted_vec.csv";
            break;
        case (3):
            fname_verbose += "_presorted_vec.csv";
            break;
    }

    myFile.open(fname_verbose);

    std::vector<int> tmpVecTest;
    Sorting genObj(tmpVecTest, 0, 0);
    for(int i = 1; i < arrayCount; i++){
        std::vector<int> sortVecIn = {};
        switch(makeVecMode){
            case (0):
                sortVecIn = genObj.MakeRandomUnsortedVec(i);
                break;
            case (1):
                sortVecIn = genObj.MakeReverseSortedVec(i);
                break;
            case (2):
                sortVecIn = genObj.MakePartiallySortedVec(i);
                break;
            case (3):
                sortVecIn = genObj.MakeSortedVec(i);
                break;
        }
        Sorting tmpSortObj(sortVecIn, sortMode, 0);
        tmpSortObj.Sort(true, false);
        myFile << tmpSortObj.ClockOutput << "\n";
    }

    myFile.close();
}

//handles a couple of extra ways to run program. F deletes benchmark file and forces another,
void handleRunArgs(int argc, char *argv[], int &vecType){
    std::string extraArg = argv[4];
    if(argc > 5){
        vecType = std::stoi(argv[5]);
    }
    if(extraArg == "GENDATA"){
        genData(0, "insertion_sort", vecType, Sorting::DATA_SIZE);
        genData(1, "merge_sort", vecType, Sorting::DATA_SIZE);
        genData(2, "quick_sort", vecType, Sorting::DATA_SIZE);
        genData(3, "tree_sort", vecType, Sorting::DATA_SIZE);
    } else if (extraArg == "F"){
        if(std::filesystem::exists("benchmark.txt")){
            std::remove("benchmark.txt");
        }
    } else {
        vecType = std::stoi(extraArg);
    }

}

//3 args: filename, measure timing(0 or 1), sort type (0 for insertion, 1 for merge, 2 for quick, 3 for tree, 4 for auto, 5 for auto 2(brute force))
int main(int argc, char *argv[]) {
    int autoGenVecType = 0;
    if(argc > 4){
        handleRunArgs(argc, argv, autoGenVecType);
    }

    //base args
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
    Sorting sortObj(inputData, sortType, autoGenVecType);

    std::cout<<"Unsorted array: ";
    print(inputData);

    //sort the data. I have the Sort function just taking in a bool but could move this to the constructor, w/e
    sortObj.Sort(measureClock, true);

    std::cout<<"Sorted array: ";
    print(sortObj.Data);


}

