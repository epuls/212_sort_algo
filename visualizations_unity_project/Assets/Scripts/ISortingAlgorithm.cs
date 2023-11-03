using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface ISortingAlgorithm
{
    //unsorted array, will need to interact 
    public int[] UnsortedArray { get; set; }
    //sorted array
    public int[] SortedArray { get; set; }
    //Stores the array each time values are swapped.
    public List<int[]> Steps { get;  }
    //Stores the indices as they sweep each step. 
    public List<List<int>> Indices { get;  }
    //Stores each comparison as the indices above sweep for animation.
    public List<Vector2> Comparisons { get; }
    //Used as an index to record steps for the sorting algorithm
    int StepCount { get; set; }
    
    
    
    public int[] Sort()
    {
        int[] tmp = new int[1];
        
        //sorting algos go here. InsertionSort.cs is the base template

        return tmp;
    }

    //records the array after each swap
    public void RecordStep(int[] currArray)
    {
        //Create and store array values
        int[] tmp = new int[currArray.Length];
        for (int k = 0; k < tmp.Length; k++)
        {
            tmp[k] = currArray[k];
        }
                
        Steps.Add(tmp);
        StepCount++;
    }
    

    //called to drive the sort and cache data so we can visualize each step. Will 
    public void Drive()
    {
        
    }
    
    
}
