
#include "Sorting.h"


void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << '\n';
}

//generates .csv file measuring clock speed of sorts on randomly populated arrays
//called at end of main if extra argument GENDATA added to end
void genData(int mode, std::string fname){
    std::ofstream myFile;
    std::string modeStr = std::to_string(mode);
    myFile.open(fname);

    //where you set max array size in data files
    for(int i = 1; i < 5000; i++){
        std::vector<int> sortVecIn = {};
        for(int j = 1; j <= i; j++){
            int rNum = rand() % 1000;
            sortVecIn.push_back(rNum);
        }
        Sorting tmpSortObj(sortVecIn, mode);
        tmpSortObj.Sort(true, false);
        myFile << tmpSortObj.ClockOutput << "\n";
        //print(tmpSortObj.Data);
    }

    myFile.close();
}

//handles a couple of extra ways to run program. F deletes benchmark file and forces another,
// B is an alternate (brute force) auto pick method.
void handleRunArgs(char *argv[]){
    std::string extraArg = argv[4];
    if(extraArg == "GENDATA"){
        //add command line for vector size?
        genData(0, "insertion_sort_data.csv");
        genData(1, "merge_sort_data.csv");
        genData(2, "quick_sort_data.csv");
        genData(3, "tree_sort_data.csv");
    } else if (extraArg == "F"){
        if(std::filesystem::exists("benchmark.txt")){
            std::remove("benchmark.txt");
        }
    }
}



//3 args: filename, measure timing(0 or 1), sort type (0 for insertion, 1 for merge, 2 for quick, 3 for tree, 4 for auto, 5 for auto 2(brute force))
int main(int argc, char *argv[]) {
    if(argc > 4){
        handleRunArgs(argv);
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
    Sorting sortObj(inputData, sortType);

    std::cout<<"Unsorted array: ";
    print(inputData);

    //sort the data. I have the Sort function just taking in a bool but could move this to the constructor, w/e
    sortObj.Sort(measureClock, true);

    std::cout<<"Sorted array: ";
    print(sortObj.Data);


}

