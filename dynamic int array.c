#include <stdlib.h>
#include <stdio.h>

#define BUFFER_INC_SIZE 1024

struct intArr {
    int *buffer;
    int bufferLength, bufferPointer;
};

int initIntArr(struct intArr *arr) {
    arr->buffer = (int *) malloc(sizeof(int) * BUFFER_INC_SIZE);
    arr->bufferLength = BUFFER_INC_SIZE;
    arr->bufferPointer = 0;
    return arr->buffer != NULL;
}

void freeIntArr(struct intArr *arr) {
    if (arr->buffer != NULL) {
        free(arr->buffer);
    } else {
        fprintf(stderr, "Error: Cannot free int array due to null pointer\n");
    }
}

int add(struct intArr *arr, int num) {
    if (arr->bufferPointer + 1 < arr->bufferLength) {
        arr->buffer[arr->bufferPointer++] = num;
    } else {
        int *newBuffer = realloc(arr->buffer, (sizeof(int) * arr->bufferLength + BUFFER_INC_SIZE));

        // Guard statement for null pointer.
        if (newBuffer == NULL) {
            fprintf(stderr, "Error: Cannot realloc the int array.");
            return 0;
        }

        arr->bufferLength += BUFFER_INC_SIZE;
        arr->buffer = newBuffer;

        add(arr, num);
    }
    return 1;
}

int main(int argc, char **argv) {
    struct intArr array;
    initIntArr(&array);

    for (int c; c = getchar(), c != EOF && c!='\n';) {
        if (c < '0' || c > '9') {
            return -1;
        }

        add(&array, c - '0');
    }

    int num = 0;
    for (int i = 0; i < array.bufferPointer; i++) {
        num *= 10;
        num += array.buffer[i];
    }

    printf("%d\n", num);
    freeIntArr(&array);
    return 0;
}
