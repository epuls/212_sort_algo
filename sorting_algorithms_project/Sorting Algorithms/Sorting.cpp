#include "Sorting.h"
#include "tree_sort.h"

//constructors/destructors
Sorting::Sorting(std::vector<int> sortData, int mode) {
    Data = sortData;

    //throw error if mode argument is out of bounds
    if(mode < 0 | mode > 5){
        std::cerr << "undefined sorting mode";
        std::exit(-1);
    }

    //set sorting type (4 is the auto sort)
    if(mode == 4)
        pickSort(sortData, 1);
    else if (mode == 5)
        pickSort(sortData, 0);
    else
        _sortingType = static_cast<SortingType>(mode); //this casts the input arg to our enum
}

Sorting::~Sorting() {

}

//---------------------------------------------private functions-------------------------------------------------------
std::vector<int> Sorting::makeRandomUnsortedVec(int size) {
    std::vector<int> randomVec = {};
    for(int j = 1; j <= size; j++){
        int rNum = rand() % 1000;
        randomVec.push_back(rNum);
    }
    return randomVec;
}

std::vector<std::vector<int>> Sorting::unsortedVec(int count){
    std::vector<std::vector<int>> outputVec = {};
    for(int i = 1; i <= count; i++){
        std::vector<int> tmp = makeRandomUnsortedVec(i);
        outputVec.push_back(tmp);
    }
    return outputVec;
}

void Sorting::benchmark(int vecSize, int algCount, int mode){
    //use above helper functions to create random arrays, sort, and record times.
    std::vector<std::vector<float>> sortTime; //holds all recorded times
    std::vector<std::vector<int>> deltaIndices = {}; //where each increase in clock timing happens
    std::vector<std::vector<float>> deltaValues = {}; //clocking timing at each increase
    std::vector<float> maxTimes = {};
    std::vector<float> averageTimes = {};
    std::vector<std::vector<float>> ratesOfChange = {};

    //benchmark test itself, runs slowly on large amounts of vectors. Sorting vecSize * 4 total vectors...
    for(int i = 0; i < algCount; i++){
        std::vector<std::vector<int>> benchmarkVecs = unsortedVec(vecSize);
        std::vector<float> tmpTimes;
        std::map<int,float> tmpMap;
        for(int j = 0; j < benchmarkVecs.size(); j++){
            Sorting tmpSortObj(benchmarkVecs[j], i);
            tmpSortObj.Sort(true, false);
            float clockTime = tmpSortObj.ClockOutput;
            tmpTimes.push_back(clockTime);
            tmpMap.insert({j, clockTime});
        }
        sortTime.push_back(tmpTimes);
        benchmarkMaps.push_back(tmpMap);
    }

    if(mode == 0)
        return;


    //analysis -- record points in the saved times that clock timing increases
    for(int i = 0; i < algCount; i++){
        std::vector<int> tmpDeltaIdx = {};
        std::vector<float> tmpDeltaVal = {};
        int tmpIdx = 0;
        for(int j = 0; j < sortTime[i].size(); j++){
            if(sortTime[i][j] > sortTime[i][tmpIdx]){
                tmpDeltaIdx.push_back(j);
                tmpDeltaVal.push_back(sortTime[i][j]);
                tmpIdx = j;
            }
        }
        deltaIndices.push_back(tmpDeltaIdx);
        deltaValues.push_back(tmpDeltaVal);
    }



    //analysis -- where max times and averages are recorded/rates of change
    for(int i = 0; i < algCount; i++){
        float curMax = *std::max_element(sortTime[i].begin(), sortTime[i].end());
        maxTimes.push_back(curMax);
        //std::cout<<"max time: "<<std::to_string(curMax) + "\n";
        std::vector<float> tmpRates;

        float tmpRate;
        float tmpSum = 0;

        for(int j = 0; j < sortTime[i].size(); j++){
            tmpSum += sortTime[i][j];

            if(i != 0 && j != 0 && sortTime[i][j] != 0) //avoid dividing by zero...
                tmpRate = sortTime[i][j] / (float) i;
            else
                tmpRate = 0;

            tmpRates.push_back(tmpRate);
        }
        float tmpAverage = tmpSum / (float) sortTime[i].size();
        averageTimes.push_back(tmpAverage);
        ratesOfChange.push_back(tmpRates);
        //std::cout<<std::to_string(tmpAverage)<<"\n";
    }




    std::vector<std::pair<int,int>> calculatedRanges = {}; //largest ranges of constant sort time
    for(int j = 0; j < 8; j++){
        std::pair<int, int> tmpRange(0,0);
        for(int i = 0; i < algCount; i++){
            if(deltaIndices[i][j])
                if(deltaIndices[i][j] > tmpRange.second){
                    tmpRange.first = i;
                    tmpRange.second = deltaIndices[i][j];
                }
        }
        calculatedRanges.push_back(tmpRange);
    }


    //get algo with min rate of change
    int selIdx = 0;
    int curMin = 100;
    for(int i = 0; i < algCount; i++){
        if(deltaIndices[i].size() < curMin){
            curMin = deltaIndices[i].size();
            selIdx = i;
        }
    }

    _sortingType = static_cast<SortingType>(selIdx);
    std::ofstream saveData;
    saveData.open("benchmark.txt");
    saveData << selIdx;
    saveData.close();


    std::cout<<"Benchmark successful, picked algorithm: "<<GetSortName(selIdx)<< "\n";

}

void Sorting::tryLoad(int mode){
    if(mode == 0)
        benchmark(2000);
    else
        if(std::filesystem::exists("benchmark.txt")){
            std::ifstream saveData;
            saveData.open("benchmark.txt");
            std::string line;
            std::getline(saveData, line);
            int loadedMode = std::stoi(line);
            saveData.close();
            _sortingType = static_cast<SortingType>(loadedMode);
            std::cout<<"Loaded previous benchmark, picked algorithm: "<<GetSortName(loadedMode)<< "\n";
        } else
            benchmark(2000, 4,1);
}


//the auto sort function that picks sorting type by vector size
void Sorting::pickSort(std::vector<int> &data, int method) {

    int size = data.size();
    std::vector<float> times;

    if(method == 0){
        tryLoad();
        //brute force method
        for(int i = 0; i < 4; i++){
            times.push_back(benchmarkMaps[i].find(size)->second);
        }

        int minTimeIdx = 0;
        for(int i = 0; i < 4; i++){
            if(times[i] < times[minTimeIdx]){
                minTimeIdx = i;
            }
        }

        _sortingType = static_cast<SortingType>(minTimeIdx);
        std::cout<<"For size: "<<size<<" most efficient sorting method is: "<< _sortingType<<"\n";
        Sort(false, true);
    } else {
        tryLoad(1);
    }


}

void Sorting::measureTiming(SortingType sortingType, bool print) {
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
    ClockOutput = output;
    //will need to figure out how we want to output our timing values. Will probably need to write to file so we can plot
    if(print)
        std::cout << "Sort time: " << std::fixed << std::setprecision(4) << output << " | vector size: " << Data.size() << std::endl;
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

int Sorting::partition(std::vector<int> &arr, int start, int end) {
    int index = 0, pivotElement = arr[end], pivotIndex;
    int* temp = new int[end - start + 1];
    for (int i = start; i <= end; i++)
    {
        if(arr[i] < pivotElement)
        {
            temp[index] = arr[i];
            index++;
        }
    }

    temp[index] = pivotElement;
    index++;

    for (int i = start; i < end; i++)
    {
        if(arr[i] > pivotElement)
        {
            temp[index] = arr[i];
            index++;
        }
    }

    index = 0;
    for (int i = start; i <= end; i++)
    {
        if(arr[i] == pivotElement)
        {
            pivotIndex = i;
        }
        arr[i] = temp[index];
        index++;
    }
    return pivotIndex; // returning pivotIndex
}

void Sorting::quickSort(std::vector<int> &arr, int start, int end) {
    if(start < end)
    {
        int partitionIndex = partition(arr, start, end); // for getting partition
        quickSort(arr, start, partitionIndex - 1); // sorting left side array
        quickSort(arr, partitionIndex + 1, end); // sorting right side array
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
    quickSort(data, 0, data.size()-1);
}

void Sorting::TreeSort(std::vector<int>& data){
    //need to use class keyword here due to scoping...TreeSort is the name of a public func and a class.
    class TreeSort T;
    T.sort(data);
}

//Main sorting function. Either calls the measureTiming function to sort and record time, or calls the sorting functions directly
void Sorting::Sort(bool measureClock, bool print) {
    if(measureClock)
        measureTiming(_sortingType, print);
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

std::string Sorting::GetSortName(int mode) {
    std::string returnString;
    switch(mode){
        case(0):
            returnString = "Insertion";
            break;
        case(1):
            returnString = "Merge";
            break;
        case(2):
            returnString = "Quick";
            break;
        case(3):
            returnString = "Tree";
            break;
        default:
            std::cerr << "how did you get here";
            std::exit(-1);
            break;
    }
    return returnString;
}
