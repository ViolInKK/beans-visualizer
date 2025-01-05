#include"content.h"

const char *ARRAY_OVERVIEW_CONTENT = "In computer science, an array is a linear data structure consisting of a collection of elements, of same memory size, arranged sequentially, each element identified by at least one array index or key, and can be accessed via a numeric offset. Arrays at core are of fixed size only, but most of the languages provide dynamic sized arrays.";

const char *BUBBLESORT_OVERVIEW_CONTENT = "Bubble sort, is a simple sorting algorithm that repeatedly steps through the input list element by element, comparing the current element with the one after it, swapping their values if needed. These passes through the list are repeated until no swaps have to be performed during a pass. Bubble sort has time complexity of O(n^2).";

const char *SHAKERSORT_OVERVIEW_CONTENT = "Shaker sort, also called Cocktail Shaker Sort, is an extenstion of the Bubble Sort. Unlike the Bubble Sort, which puts the bigger element to the end of the sublist at each cycle, the Shaker Sort alternates between bringing the bigger element of the unsorted sublist to the end of the ordered part and leading the smaller elements of the sublist at the beginning of the sorted sublist. Shaker sort has time complexity of O(n^2).";

const char *SELECTIONSORT_OVERVIEW_CONTENT = "Selection sort is an iterative and in-place sorting algorithm that divides the data structure in two sublists: the ordered one, and the unordered one. The algorithm loops for all the elements of the data structure and for every cycle picks the smallest element of the unordered sublist and adds it to the sorted sublist, progressivly filling it. Selection sort has time complexity of O(n^2).";

const char *INSERTIONSORT_OVERVIEW_CONTENT = "Insertion sort is a simple algorithm that builds the final sorted array one time at a time. The algorithm divides the data structure in two sublists: a sorted one, and one still to sort. Initially, the sorted sublist is made up of just one element and it gets progressively filled. For every iteration, the algorithm picks an element on the unsorted sublist and inserts it at the right place in the sorted sublist. Insertion sort has time complexity of O(n^2).";

const char *QUICKSORT_OVERVIEW_CONTENT = "Quick sort is a algorithm based on splitting the data structure in smaller partitions and sort them recursively until the data structure is sorted. The division in partitions is done based on an element, called pivot: all the elements bigger than the pivot get placed on the right side of the structure, the smaller ones to the left, creating two partitions. Next, this procedure gets applied recursively to the two partitions and so on. Quick sort has time complexity of O(n * log(n)).";

const char *MERGESORT_OVERVIEW_CONTENT = "Merge sort is a algorithm like quick sort based on splitting the data structure in smaller partitions. The algorithm divides the data structure recursively until the subsequences contain only one element. At this point, the subsequences get merged and ordered sequentially. To do so, the algorithm progressively builds the sorted sublist by adding each time the minimum element of the next two usorted subsequences until there is only one sublist remaining. This will be the sorted data structure. Merge sort has time complexity of O(n * log(n)).";

const char *HEAPSORT_OVERVIEW_CONTENT = "Heap sort is an in-place iterative sorting algorithm based on auxiliary data structures called heap. It's less efficient tha algorithm with the same time complexity and its not suitable for data structures with few elements. The heap is a data structure representable as a binary tree, where each node has a value bigger or equal to its children. Consequently, the root will hold the maximum value. The data structure gets ordered to form the heap initially, and then it gets progressively reordered with an algorithm similar to Selection sort, starting from the bigger elements. Heap sort has time complexity of O(n * log(n)).";

const char *SHELLSORT_OVERVIEW_CONTENT = "Shell sort is one of the oldest sorting algorithms and it's an extension of the Insertion sort. Unlike Insertion sort, Shell sort starts by comparing the elements distant from each other by a certain gap that gets progressively decreased, By starting with the most distant elements, it can optimize performances as it's not limited by just comparing two adjacent elements. Shell sort has time complexity of O(n^1.25) or O(n * log(n)).";

const char *COMBSORT_OVERVIEW_CONTENT = "Comb sort is a algorithm really similar to Bubble sort. It highly improves its performances by removing the 'turtles', that is the small elements placed near the end of the data structure that slows down a lot the performances of Bubble sort. Bubble sort is based on comparing adjaces elements, so with a distance of 1. Comb sort increases this distance using a shrink factor k (usually with a value of 1.3). Initially, the distance has a value of n. For each iteration, a Bubble sort gets executed using the new distance value instead of 1. The distances gets progressively divided by the shirnk factor k. This procedure gets executed until the distance reaches the value of 1. At this point, the algorithm is a regular Bubble Sort, but the majority of the 'turtles' already got removed. Its average time complexity depends, in addition to the number of elements of the data structure, by a value p, representing the number of divisions carried out.";

const char *STACK_OVERVIEW_CONTENT = "In computer science, a stack is an abstract data type that serves as a collection of elements with two main operations: Push, which adds an element to the collection, and Pop, which removes the most recently added element. The order in which an element added to or removed from a stack is described as last in, first out, referred to by the acronym LIFO.";

const char *QUEUE_OVERVIEW_CONTENT = "In computer science, a queue is an abstract data type that serves as a collection of elements with two main operations: Enqueue, which adds element to the rear of the queue, and Dequeue, which removes element from the front. The operations of a queue make it first in, firs out, also referred to by the acronym FIFO.";

const char *LINKED_LIST_OVERVIEW_CONTENT = "In computer science, a linked list is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next. It's a data structure consisting of collection of nodes which together represent a sequence. In it's most basic form, each node contains data, and a reference to next node.";

const char *TREES_OVERVIEW_CONTENT = "In computer science, a tree is a widely used abstract data type that represents a hierarchical tree structure with a set of connected nodes. Each node in the tree can be connected to many children(depending on the type of tree), but must be connected to exactly on parent, except for the root node, which has no parent.";

const char *GRAPHS_OVERVIEW_CONTENT = "In computer science, a graph is an abstract data type that is meant to implement the undirected graph and directed graph concepts. A graph data structure consist of finite(and possible mutable) set of verticies(also called nodes or points), together with a set of unordered pairs of these vertices for an undirected graph or a set of ordered pairs for a directed graph. These pairs are knows as edges(also called links).";
