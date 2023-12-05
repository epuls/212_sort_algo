CS212 Project Repo
The implementation designed by the team allows a user to:

    -sort a series of integers automatically using the most optimal algorithm
    -sort a series of integers by picking one of the sorting algorithms manually
    -run a benchmark generating .csv files containing sort times based on vector size (algorithm type and vector type are specified in the .csv file names for clarity.)

Additional arguments allow the user to specify which “presorting treatment” the vectors will be generated with: whether they are totally random, sorted in reverse, partially sorted, or already sorted.

--------------------------------------------------------------------------------

The application takes in a minimum of 3 but up to five command line arguments: 
filename, recordClockSpeed, sortingMethod, OPTIONAL_1, OPTIONAL_2

<xmp><filename> </xmp> 
-   text file included in the local directory containing a list of integers the user intends to sort, delineated by spaces.

  <xmp><recordClockSpeed> </xmp>
  - can be either 0 or 1, which will record the time it takes to sort the ingested data if “1” is passed in.

<xmp><sortingMethod> </xmp>
- is an integer ranging from 0-5 stating how we would like to sort data.

        0 - Insertion Sort

        1 - Merge Sort

        2 - Quick Sort

        3 - Tree Sort

        4 - ‘baseline’ benchmark:
            runs a benchmark that will select the sorting algorithm with the least rate of change. It will then save that result in the form of a single integer to a 
            “benchmark.txt” in its local directory(this file is loaded on following executions of the application to remove the need for repeated benchmarks.)


          5 - ‘brute force’ benchmark:
              * run a benchmark every time and pick the algorithm with the lowest sort time for the size of the ingested data, and then sort the data using the identified optimal algorithm.

<OPTIONAL_1> 
- can be any of the following: an integer inclusively ranging from 0 to 3, the text “GENDATA”, or the capital letter “F”.

        The integer specifies the type of “presorting treatment” the benchmarked vectors are generated with: 0 uses the default method of randomly populated vectors, 1 uses reverse sorted vectors, 2 uses partially sorted vectors, and 3 uses fully presorted vectors.
        “GENDATA” generates the previously mentioned .csv files containing sort times, which are specifically named based on algorithm used and the “presorting treatment” in which the vectors are generated with.
        “F” is used for <sortingMethod> 4, and forces a benchmark to be run even if a “benchmark.txt” exists, replacing the previously saved benchmark.
<OPTIONAL_2> 
- allows for the user to specify the “presorting treatment” when forcing benchmarks with “F” or recording benchmark data with “GENDATA”.

(note: on first run the application will generate a “settings.txt” file that allows the user to override the initial benchmark vector size max and quantity of generated data)

--------------------------------------------------------------

Sample arguments for the application are as follows:

./input_1.txt 1 4
- Sort input_1.txt using our main “auto-sort” implementation, outputting sort time and the sorted data to the console/terminal. If it is run for the first time, it will run a benchmark as previously stated.

./input_1.txt 1 4 F 1
- Sort input_1.txt using our main “auto-sort” implementation, outputting sort time and the sorted data to the console/terminal. Forces a benchmark and uses reverse sorted vectors to benchmark.

./input_1.txt 0 0
- Sort input_1.txt using Insertion Sort, only outputting the sorted data to the console/terminal

./input_1.txt 1 1 GENDATA 3
- Sort input_1.txt with Merge Sort, recording the results and time to the console/terminal. It will also generate .csv files for each algorithm, running said algorithms up against vectors that are already sorted

--------------------------------------------------------------

Project contains no dependencies.

Compilation instructions:
Load Cmake project and ensure Sorting.cpp, Sorting.h, and main.cpp are added to executable. 
