#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void swap(int *array, int indexA, int indexB) {
  int temp = array[indexA];
  array[indexA] = array[indexB];
  array[indexB] = temp;
}

// Don't call this as the sort as this needs the value of n to init
void insertionSortR(int *array, int n) {
  if (n > 0) {
    insertionSortR(array, n - 1);

    int temp = array[n];
    int j = n - 1;
    for (; j >= 0 && array[j] > temp; j--) {
      array[j + 1] = array[j];
    }

    array[j + 1] = temp;
  }
}

void insertionSort(int *array, int n) { insertionSortR(array, n - 1); }

// Bounded insertion sort for tim sort
void insertionSortRBound(int *array, int min, int max) {
  if (max > min) {
    insertionSortRBound(array, min, max - 1);

    int temp = array[max];
    int j = max - 1;
    for (; j >= min && array[j] > temp; j--) {
      array[j + 1] = array[j];
    }

    array[j + 1] = temp;
  }
}

void insertionSortBound(int *array, int min, int max) {
  insertionSortRBound(array, min, max - 1);
}

void merge(int *array, int min1, int max1, int min2, int max2) {
  int arrayOnePointer = min1;
  int arrayTwoPointer = min2;
  while (arrayOnePointer <= max1 && arrayTwoPointer <= max2) {
    if (array[arrayOnePointer] < array[arrayTwoPointer]) {
      // Swap element in array 1 and 2, inc array 1 pointer
      swap(array, arrayOnePointer, arrayTwoPointer);
      arrayOnePointer++;
    } else {
      // Swap element in array 2 and 1, inc array 2 pointer
      swap(array, arrayOnePointer, arrayTwoPointer);
      arrayTwoPointer++;
    }
  }
}

#define segmentLength 10
void insertionSortSegments(int *array, int size) {
  for (int i = 0; i * segmentLength < size; i += segmentLength + 1) {
    // Assert that i is within the length
    if (i >= size)
      i = size - 1;
    // Insertion sort the segment
    insertionSortBound(array, i, i + segmentLength);
  }
}

void mergeSegments(int *array, int size) {
  int runLength = segmentLength;
  while (runLength < size) {
    // Assert the merge length is a valid
    if (runLength >= size) {
      runLength = size - 1;
    }

    for (int i = 0; i * runLength < size; i += runLength + 1) {
      int chunkLength = runLength / 2;
      merge(array, i, i + chunkLength, i + chunkLength + 1, i + runLength);
    }

    runLength *= 2;
  }
}

void timSort(int *array, int length) {
  insertionSortSegments(array, length);
  mergeSegments(array, length);
}

void quickSortR(int min, int max, int *array) {
  if (min < max) {
    int pointer = min + (max - min) / 2;

    // Iterate over the array
    for (int i = min; i <= max; i++) {
      // Put all numbers less than the pointer before it
      if (array[i] > array[pointer] && i < pointer) {
        int temp = array[i];

        // Move elements from i to pointer - 1 up by 1
        for (int j = i; j < pointer; j++) {
          array[j] = array[j + 1];
        }

        // Put the original element where the pointer used to be
        array[pointer] = temp;
        // The pointer has moved in the array
        pointer--;
        // The element has moved forwards so we are looking at another element
        i--;
        // Put all larger numbers after the pointer
      } else if (array[i] < array[pointer] && i > pointer) {
        int temp = array[i];

        // Move all elements from the pointer + 1 up by 1
        for (int j = i; j > pointer; j--) {
          array[j] = array[j - 1];
        }

        // Put the original element at i at the pointer
        array[pointer] = temp;
        // The pointer has moved
        pointer++;
      }
    }

    quickSortR(min, pointer - 1, array);
    quickSortR(pointer + 1, max, array);
  }
}

void quickSort(int *array, int length) { quickSortR(0, length - 1, array); }

#define logTwo log(2)
void heapify(int *array, int length) {}

void heapSort(int *array, int length) {
  int i = length - 1;
  while (i > 0) {
    // Create a minimum heap
    heapify(array, i);

    // Remove the root
    swap(array, 0, i);
  }
}

void randomiseArrayOrder(int *array, int size) {
  for (int i = 0; i < size; i++) {
    int random = rand() % size;
    int temp = array[i];
    array[i] = array[random];
    array[random] = temp;
  }
}

void printThenRandomise(int *array, int size) {
  printArray(array, size);
  randomiseArrayOrder(array, size);
}

#define size 10
// Test Methods
int main() {
  int *numbers = (int *)malloc(sizeof(int) * size);

  // Intializes random number generator
  time_t t;
  srand((unsigned)time(&t));
  for (int i = 0; i < size; i++)
    numbers[i] = rand() % 100;

  printf("%d is the array size\n", size);
  printArray(numbers, size);

  printf("Insertionsort\n");
  insertionSort(numbers, size);
  printThenRandomise(numbers, size);

  printf("Timsort\n");
  timSort(numbers, size);
  printThenRandomise(numbers, size);

  printf("Quicksort\n");
  quickSort(numbers, size);
  printThenRandomise(numbers, size);

  free(numbers);

  return 0;
}
