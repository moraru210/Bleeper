#include <stdio.h>

int main(void){
    FILE* f;

    f = fopen("test.txt", "r");

 

    fclose(f);
    return 0;
}
