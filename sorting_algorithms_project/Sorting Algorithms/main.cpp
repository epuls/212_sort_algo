#include "Sorting.h"

void print(std::vector<int> &vec){
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << '\n';
}

void saveOutput(std::string inputFname, std::vector<int> &vec){
    //remove .txt from extension, add _sorted.txt to output fname
    std::string outFname = inputFname.substr(0, inputFname.size()-4) + "_sorted.txt";
    std::ofstream file(outFname);
    for(int i = 0; i < vec.size(); i++) {
        file << std::to_string(vec[i]) + " ";
    }
    file.close();
    std::cout<<inputFname + " sorted and saved to: " + outFname + "\n";
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

    //Kind of messy, allows user to override default benchmark size for weaker systems
    if(arrayCount != genObj.data_override)
            arrayCount = genObj.data_override;
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

//handles a couple of extra ways to run program. See readme, F and GENDATA
void handleRunArgs(int argc, char *argv[], int &vecType){
    std::string extraArg = argv[4];
    if(argc > 5){
        vecType = std::stoi(argv[5]);
    }
    if(extraArg == "GENDATA"){
        std::vector<int> tmp;
        Sorting genObj(tmp, 0, 0);
        if(genObj.data_override != Sorting::DATA_SIZE)
            std::cout<<"Loaded override settings for generated data size. New value: "<<genObj.data_override<<"\n";

        std::cout<<"Generating data for analysis...\n";
        genData(0, "insertion_sort", vecType, Sorting::DATA_SIZE);
        genData(1, "merge_sort", vecType, Sorting::DATA_SIZE);
        genData(2, "quick_sort", vecType, Sorting::DATA_SIZE);
        genData(3, "tree_sort", vecType, Sorting::DATA_SIZE);

        std::cout<<"Generated benchmark data. Aborting program, run without GENDATA arg to sort.\n";
        std::exit(1);
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

    saveOutput(argv[1], sortObj.Data);
    std::cout<<"Sorted array: ";
    print(sortObj.Data);
}

