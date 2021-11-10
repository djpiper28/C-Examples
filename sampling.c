#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

int doSample(int *n) {
    int num = 0;
    for (int c; c = getchar(), c != EOF && c != '\n';) {
        if (c < '0' || c > '9' || num >= MAX) return -1;
        num *= 10;
        num += c - '0';
    }

    int *a = (int *) malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) a[i] = i;

    for (int i = 0, len = num; i < num/2; i++) {
        int r = rand() % len--;
        n[i] = a[r];
        a[r] = a[num - i - 1];
    }

    free(a);

    return num/2;
}

int main () {
    int n[MAX];
    int num = doSample(n);
    for (int i = 0; i < num; i++) {
        printf("%d ", n[i]);
    }
}
