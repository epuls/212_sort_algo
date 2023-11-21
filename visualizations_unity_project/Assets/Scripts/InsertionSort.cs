using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class InsertionSort : MonoBehaviour, ISortingAlgorithm
{
    public int[] UnsortedArray { get; set; }
    public int[] SortedArray { get; set; }
    public List<int[]> Steps { get; set; }
    public List<List<int>> Indices { get; set; }
    public List<Vector2> Comparisons { get; set; }
    public int StepCount { get; set; }
    
    //Sorting Algorithm
    public int[] Sort(int[] unsortedArray)
    {
        Steps = new List<int[]> { };
        StepCount = 0;
        
        //create copy of our array
        int[] arr = new int[unsortedArray.Length];
        for (int i = 0; i < arr.Length; i++)
        {
            arr[i] = unsortedArray[i];
        }
        
        //loop through list and sort
        int n = arr.Length;
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            
            
            //Record every value and use a 3D array so you can step between changes for every single step. Nested steps
            Debug.Log("key: " + key.ToString());
            Debug.Log("j: " + j.ToString());
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
                
                Debug.Log("key: " + key.ToString());
                Debug.Log("j: " + j.ToString());
            }
            
            arr[j + 1] = key;
            Debug.Log("key: " + key.ToString());
            Debug.Log("j: " + j.ToString());
            
            RecordStep(arr);
        }
        
        Debug.Log("Step Count: " + StepCount);
        return arr;
    }

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

    public void RecordSwap(int c_key, int val1, int val2)
    {
        //not yet implemented but do it.
    }

    

    public void Drive()
    {
        SortedArray = Sort(UnsortedArray);
    }
    

    void Start()
    {
        
    }
    
}

