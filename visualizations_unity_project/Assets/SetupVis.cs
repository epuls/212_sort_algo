using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class SetupVis : MonoBehaviour
{

    public GameObject arrayElementPrefab;
    public GameObject[] elementObjArray;
    public TMP_Text[] elementTextObjs = new TMP_Text[5];
    public int[] arrayToSort = new int[]{1, 2, 5, 4, 3, 1};

    //which algorithm we are currently using
    private ISortingAlgorithm _selectedAlgo;
    
    //Sorting algorithm objs
    private ISortingAlgorithm _insertionSortRef;
    

    private int[] _selectedArray;
    private int _currArrayLength;
    private int _currStep = 0;
    private int _maxStep;
    

    void PopulateElements(ISortingAlgorithm algoToUse, int[] arrayToPopulate)
    {
        //Set Unsorted Array
        algoToUse.UnsortedArray = arrayToPopulate;
        //initialize so we can have the array of the proper length
        _selectedArray = new int[arrayToPopulate.Length];
        //set the current algorithm instance as a reference
        _selectedAlgo = algoToUse;
        
        //Populate text fields
        for (int i = 0; i < arrayToPopulate.Length; i++)
        {
            elementTextObjs[i].text = algoToUse.UnsortedArray[i].ToString();
        }
        
        //Runs algorithm and caches needed data to visualize the sort
        algoToUse.Drive();
        _maxStep = algoToUse.Steps.Count - 1;

    }

    public void StepThroughSort(bool right)
    {
        int currentIndex = _currStep;
        if (right)
        {
            _currStep += 1;
        }
        else
        {
            _currStep -= 1;
        }

        if (_currStep < 0)
        {
            _currStep = 0;
        }

        if (_currStep > _maxStep)
        {
            _currStep = _maxStep;
        }

        Debug.Log("current step index: " + _currStep.ToString());

        
        for (int i = 0; i < arrayToSort.Length; i++)
        {
            _selectedArray[i] = _selectedAlgo.Steps[_currStep][i];
            elementTextObjs[i].text = _selectedAlgo.Steps[_currStep][i].ToString();
        }
        
        
        
    }

    List<int[]> GetSwap(int pStep, int cStep)
    {
        List<int[]> swaps = new List<int[]>();

        int[] prevArray = _selectedAlgo.Steps[pStep];
        int[] selArray = _selectedAlgo.Steps[cStep];

        //just record swaps live this isn't working.
        for (int i = 0; i < prevArray.Length; i++)
        {
            
        }

        return swaps;
    }

    void AnimateSwap()
    {
        //look up some bezier curve stuff to make a smooth animation. 
        //General plan:
            //clone element objs, set to swapped values, deactivate originals
            //animate the clones up or down and move into appropriate spots
            //reactivate originals and deactivate clones
            //this won't mess up the element orders and will just be a visual trick
    }
    
    void Start()
    {
        _insertionSortRef = this.GetComponent<Insertion_Sort>();
        PopulateElements(_insertionSortRef, arrayToSort);
        _currArrayLength = arrayToSort.Length;
    }
    
}
