#include<stdlib.h>
#include<time.h>
#include<stddef.h>

#include"helpers.h"

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void ShuffleArray(int *array, int size){
    if (size > 1){
        srand(time(0));
        for (size_t i = 0; i<size; i++){
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            swap(&array[i], &array[j]);
        }
    }
}

void FillArrayRandom(int *array, int size){
    for (size_t i = 0; i<size; i++){
        array[i] = i;
    }
    ShuffleArray(array, size);
}
