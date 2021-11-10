#include <stdlib.h>
#include <stdio.h>

#define BUFFER_INC_SIZE 10

struct charArr {
    char *buffer;
    int bufferLength, bufferPointer;
};

int initCharArr(struct charArr *arr) {
    arr->buffer = (char *) malloc(sizeof(char) * BUFFER_INC_SIZE);
    arr->bufferLength = BUFFER_INC_SIZE;
    arr->bufferPointer = 0;

    if (arr->buffer == NULL) {
        fprintf(stderr, "Error: Cannot allocate the int array.\n");
    }
    return arr->buffer != NULL;
}

void freeCharArr(struct charArr *arr) {
    if (arr->buffer != NULL) {
        free(arr->buffer);
    } else {
        fprintf(stderr, "Error: Cannot free int array due to null pointer.\n");
    }
}

int add(struct charArr *arr, char c) {
    if (arr->bufferPointer + 1 < arr->bufferLength) {
        arr->buffer[arr->bufferPointer++] = c;
    } else {
        char *newBuffer = realloc(arr->buffer, (sizeof(char) * arr->bufferLength + BUFFER_INC_SIZE));

        // Guard statement for null pointer.
        if (newBuffer == NULL) {
            fprintf(stderr, "Error: Cannot realloc the int array.");
            return 0;
        }

        arr->bufferLength += BUFFER_INC_SIZE;
        arr->buffer = newBuffer;

        add(arr, c);
    }
    return 1;
}

int main(int argc, char **argv) {
    struct charArr array;
    if (!initCharArr(&array)) return -1;

    for (int c; c = getchar(), c != EOF && c!='\n';) {
        if (!add(&array, c)) return -1;
    }
    if (!add(&array, '\0')) return -1;

    printf("%s\n", array.buffer);
    freeCharArr(&array);
    return 0;
}
