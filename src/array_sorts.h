#ifndef ARRAY_SORTS_H
#define ARRAY_SORTS_H 

// ---- Various array sorting algorithms ----

void BubbleSort(ViewContext *viewContext);
void ShakerSort(ViewContext *viewContext);
void SelectionSort(ViewContext *viewContext);
void InsertionSort(ViewContext *viewContext);
void ShellSort(ViewContext *viewContext);
void CombSort(ViewContext *viewContext);

void QuickSortInterface(ViewContext *viewContext);
int  partition(ViewContext *viewContext, int low, int high);
void QuickSort(ViewContext *viewContext, int low, int high);

void MergeSortInterface(ViewContext *viewContext);
void Merge(ViewContext *viewContext, int left, int m, int right);
void MergeSort(ViewContext *viewContext, int left, int right);

void Heapify(ViewContext *viewContext, int n, int i);
void HeapSort(ViewContext *viewContext);

#endif
