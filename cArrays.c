#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int somenumbers[5];
    int *ptr = somenumbers; // &somenumbers[0]
    
    int v = 2;
    // Move the pointer along the array
    for(;ptr<&somenumbers[5];ptr++/*inc pointer (compiler does it by the size of each array element)*/) {
        *ptr = v; //Set where ptr is pointing to v
        v *= 2;
    }
    
    for(int i = 0; i<5; i++) {
        printf("%d\n", somenumbers[i]);
    }
    
    return 0;
}
