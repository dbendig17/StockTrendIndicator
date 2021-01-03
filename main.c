#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi.h"

//program takes in one input .txt file for stock data
int main( int argc, char **argv ){
    char filename[25];
    double *arr;
    int size = 0;
    double *test;
    double arr1[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    test = arr1;
    printf("%f\n", calculateSMA(test, 5));


    //printf("answer = %f\n", calculateDailyMA(100.0, 20, 100.0));
    if(argc != 2){
        fprintf(stderr, "usage: %s 'filename.txt'\n", argv[0]);
        exit(-1);
    } else {
        strcpy(filename, argv[1]);
        arr = parseFile(filename, &size);
        //printf("%f\n", arr[253]);
        printf("%d\n", size);
        free(arr);
    }
    return 0;
}
