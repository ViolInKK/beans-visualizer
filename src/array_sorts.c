#include<raylib.h>

#include<stdbool.h>
#include<stddef.h>

#include"helpers.h"
#include"rendering.h"

void BubbleSort(ViewContext *viewContext){
    int size = viewContext->arraySize;

    for (int i = 0; i<size - 1; i++){                                       // ______________
        for (int j = 0; j<size - i - 1; j++){                               // |            |
            viewContext->arrayPointer = j;                                  // |  BUBBLE    |
            if (viewContext->array[j] > viewContext->array[j+1]){           // |  SORTING   |
                swap(&viewContext->array[j], &viewContext->array[j+1]);     // |  ALGORITHM |
            }                                                               // |____________|
            VisualizeArraySorting(viewContext);
        }
    }
}

void ShakerSort(ViewContext *viewContext){
    int size = viewContext->arraySize;

    bool swapped = true;                                                    //  _______________
    int start = 0;                                                          //  |             |
    int end = size - 1;                                                     //  |             |
    while (swapped){                                                        //  |             |
        swapped = false;                                                    //  |             |
        for (int i = start; i < end; ++i){                                  //  |             |
            viewContext->arrayPointer = i;                                  //  |             |
            if (viewContext->array[i] > viewContext->array[i + 1]){         //  |             |
                swap(&viewContext->array[i], &viewContext->array[i + 1]);   //  |             |
                swapped = true;                                             //  |             |
                VisualizeArraySorting(viewContext);                         //  |             |
            }                                                               //  |  SHAKER     |
        }                                                                   //  |  SORTING    |
        if (!swapped){                                                      //  |  ALGORITHM  |
            break;                                                          //  |             |
        }                                                                   //  |             |
        swapped = false;                                                    //  |             |
        --end;                                                              //  |             |
        for (int i = end - 1; i >= start; --i){                             //  |             |
            viewContext->arrayPointer = i;                                  //  |             |
            if (viewContext->array[i] > viewContext->array[i + 1]){         //  |             |
                swap(&viewContext->array[i], &viewContext->array[i + 1]);   //  |             |
                swapped = true;                                             //  |             |
                VisualizeArraySorting(viewContext);                         //  |             |
            }                                                               //  |             |
        }                                                                   //  |             |
        ++start;                                                            //  |             |
    }                                                                       //  ---------------
}

void SelectionSort(ViewContext *viewContext){
    int size = viewContext->arraySize;

    int i, j, min_index;
    for (i = 0; i < size-1; i++){                                           //  _______________
        min_index = i;                                                      //  |             | 
        for (j = i+1; j < size; j++){                                       //  |             | 
            if (viewContext->array[j] < viewContext->array[min_index]){     //  |             | 
                min_index = j;                                              //  |  SELECTION  | 
            }                                                               //  |  SORTING    | 
            viewContext->arrayPointer = j;                                  //  |  ALGORITHM  | 
            VisualizeArraySorting(viewContext);                             //  |             | 
        }                                                                   //  |             | 
        swap(&viewContext->array[min_index], &viewContext->array[i]);       //  |             | 
    }                                                                       //  ---------------
}

void InsertionSort(ViewContext *viewContext){
    int size = viewContext->arraySize;

    int i, j, key;                                                          //  _______________
    for (i = 1; i < size; i++){                                             //  |             |
        key = viewContext->array[i];                                        //  |             |
        j = i - 1;                                                          //  |             |
        while (j >= 0 && viewContext->array[j] > key){                      //  |  INSERTION  |
            viewContext->array[j + 1] = viewContext->array[j];              //  |  SORTING    |
            j = j - 1;                                                      //  |  ALGORITHM  |
            viewContext->arrayPointer = j;                                  //  |             |
            VisualizeArraySorting(viewContext);                             //  |             |
        }                                                                   //  |             |
        viewContext->array[j + 1] = key;                                    //  ---------------
    }
}

void ShellSort(ViewContext *viewContext){
    int size = viewContext->arraySize;                                      //  _______________                               
    int i, j, k;                                                            //  |             |
    for (i = size / 2; i > 0; i = i / 2){                                   //  |             |
        for (j = i; j < size; j++){                                         //  |             |
            for (k = j - i; k >= 0; k = k - i){                             //  |             |
                viewContext->arrayPointer = k;                              //  |             |
                if (viewContext->array[k+i] >= viewContext->array[k]){      //  |             |
                    VisualizeArraySorting(viewContext);                     //  |             |
                    break;                                                  //  |  SHELL      |
                }                                                           //  |  SORTING    |
                else{                                                       //  |  ALGORITHM  |
                    VisualizeArraySorting(viewContext);                     //  |             |
                    swap(&viewContext->array[k], &viewContext->array[k+i]); //  |             |
                }                                                           //  |             |
            }                                                               //  |             |
        }                                                                   //  |             |
    }                                                                       //  |             |
}                                                                           //  ---------------

void CombSort(ViewContext *viewContext){
    int size = viewContext->arraySize;                                      //  _______________
    int sm;                                                                 //  |             |
    float shrink = 1.3;                                                     //  |             |
    int gap = size;                                                         //  |             |
    bool sorted = false;                                                    //  |             |
                                                                            //  |             |
    while (!sorted){                                                        //  |             |
        gap /= shrink;                                                      //  |             |
        if (gap <= 1){                                                      //  |             |
            sorted = true;                                                  //  |             |
            gap = 1;                                                        //  |  COMB       |
        }                                                                   //  |  SORTING    |
                                                                            //  |  ALGORITHM  |
        for (int i = 0; i < size - gap; i++){                               //  |             |
            sm = gap + i;                                                   //  |             |
            if (viewContext->array[i] > viewContext->array[sm]){            //  |             |
                viewContext->arrayPointer = i;                              //  |             |
                VisualizeArraySorting(viewContext);                         //  |             |
                swap(&viewContext->array[i], &viewContext->array[sm]);      //  |             |
                VisualizeArraySorting(viewContext);                         //  |             |
                sorted = false;                                             //  ---------------
            }
        }
    }
}

int partition(ViewContext *viewContext, int low, int high){                 //  _______________
    int pivot = viewContext->array[high];                                   //  |             |
    int i = (low - 1);                                                      //  |             |
                                                                            //  |             |
    for (int j = low; j < high; j++){                                       //  |             |
        if (viewContext->array[j] <= pivot){                                //  |             |
            i++;                                                            //  |             |
            swap(&viewContext->array[i], &viewContext->array[j]);           //  |             |
            viewContext->arrayPointer = j;                                  //  |             |
            VisualizeArraySorting(viewContext);                             //  |             |
        }                                                                   //  |             |
    }                                                                       //  |             |
    swap(&viewContext->array[i + 1], &viewContext->array[high]);            //  |  QUICK      |
    VisualizeArraySorting(viewContext);                                     //  |  SORTING    |
    return (i + 1);                                                         //  |  ALGORITHM  |
}                                                                           //  |             |
                                                                            //  |             |
void QuickSort(ViewContext *viewContext, int low, int high){                //  |             |
    if (low < high){                                                        //  |             |
        int pi = partition(viewContext, low, high);                         //  |             |
                                                                            //  |             |
        QuickSort(viewContext, low, pi - 1);                                //  |             |
                                                                            //  |             |
        QuickSort(viewContext, pi + 1, high);                               //  |             |
    }                                                                       //  |             |
}                                                                           //  ---------------

void QuickSortInterface(ViewContext *viewContext){
        QuickSort(viewContext,0, 99);
}

void Merge(ViewContext *viewContext, int left, int m, int right){           //  ______________
    int i,j,k;                                                              //  |            |
    int n1 = m - left + 1;                                                  //  |            |
    int n2 = right - m;                                                     //  |            |
                                                                            //  |            |
    int L[n1], R[n2];                                                       //  |            |
                                                                            //  |            |
    for (i = 0; i < n1; i++){                                               //  |            |
        L[i] = viewContext->array[left + i];                                //  |            |
    }                                                                       //  |            |
    for (j = 0; j < n2; j++){                                               //  |            |
        R[j] = viewContext->array[m + 1 + j];                               //  |            |
    }                                                                       //  |            |
                                                                            //  |            |
    i = 0;                                                                  //  |            |
    j = 0;                                                                  //  |            |
    k = left;                                                               //  |            |
                                                                            //  |            |
    while (i < n1 && j < n2){                                               //  |            |
        if (L[i] <= R[j]){                                                  //  |            |
            viewContext->array[k] = L[i];                                   //  |            |
            i++;                                                            //  |            |
        }                                                                   //  |            |
        else{                                                               //  |            |
            viewContext->array[k] = R[j];                                   //  |            |
            j++;                                                            //  |            |
        }                                                                   //  |            |
        k++;                                                                //  |            |
        viewContext->arrayPointer = k;                                      //  |            |
        VisualizeArraySorting(viewContext);                                 //  |            |
    }                                                                       //  |            |
                                                                            //  |  MERGE     |
    while (i < n1){                                                         //  |  SORTING   |
        viewContext->array[k] = L[i];                                       //  |  ALGORITHM |
        i++;                                                                //  |            |
        k++;                                                                //  |            |
        viewContext->arrayPointer = k;                                      //  |            |
        VisualizeArraySorting(viewContext);                                 //  |            |
    }                                                                       //  |            |
                                                                            //  |            |
    while (j < n2){                                                         //  |            |
        viewContext->array[k] = R[j];                                       //  |            |
        j++;                                                                //  |            |
        k++;                                                                //  |            |
        viewContext->arrayPointer = k;                                      //  |            |
        VisualizeArraySorting(viewContext);                                 //  |            |
    }                                                                       //  |            |
}                                                                           //  |            |
                                                                            //  |            |
void MergeSort(ViewContext *viewContext, int left, int right){              //  |            |
    if (left < right){                                                      //  |            |
        int m = left + (right - left) / 2;                                  //  |            |
                                                                            //  |            |
        MergeSort(viewContext, left, m);                                    //  |            |
        MergeSort(viewContext, m + 1, right);                               //  |            |
        Merge(viewContext, left, m, right);                                 //  |            |
    }                                                                       //  |            |
}                                                                           //  --------------

void MergeSortInterface(ViewContext *viewContext){
    MergeSort(viewContext, 0, 99);
}

void Heapify(ViewContext *viewContext, int n, int i){                           //  ______________
    int largest = i;                                                            //  |            |
    int left = 2 * i + 1;                                                       //  |            |
    int right = 2 * i + 2;                                                      //  |            |
                                                                                //  |            |
    if (left < n && viewContext->array[left] > viewContext->array[largest]){    //  |            |
        largest = left;                                                         //  |            |
    }                                                                           //  |            |
                                                                                //  |            |
    if (right < n && viewContext->array[right] > viewContext->array[largest]){  //  |            |
        largest = right;                                                        //  |            |
    }                                                                           //  |            |
                                                                                //  |            |
    if (largest != i){                                                          //  |            |
        viewContext->arrayPointer = i;                                          //  |            |
        swap(&viewContext->array[i], &viewContext->array[largest]);             //  |  HEAP      |
        VisualizeArraySorting(viewContext);                                     //  |  SORTING   |
        Heapify(viewContext, n, largest);                                       //  |  ALGORITHM |
    }                                                                           //  |            |
}                                                                               //  |            |  
                                                                                //  |            |
void HeapSort(ViewContext *viewContext){                                        //  |            |
    for (int i = viewContext->arraySize / 2 - 1; i >= 0; i--){                  //  |            |
        Heapify(viewContext, viewContext->arraySize, i);                        //  |            |
    }                                                                           //  |            |
    for (int i = viewContext->arraySize - 1; i >= 0; i--){                      //  |            |
        viewContext->arrayPointer = i;                                          //  |            |
        swap(&viewContext->array[0], &viewContext->array[i]);                   //  |            |
        VisualizeArraySorting(viewContext);                                     //  |            |
        Heapify(viewContext, i, 0);                                             //  |            |
    }                                                                           //  |            |
}                                                                               //  --------------
