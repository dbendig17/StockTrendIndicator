#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi.h"

//program takes in one input .txt file for stock data
int main( int argc, char **argv ){
    char filename[25];
    double *arr;
    char *name = malloc(sizeof(char) * 10);
    int size = 0;

    if(argc != 2){
        fprintf(stderr, "usage: %s 'filename.txt'\n", argv[0]);
        exit(-1);
    } else {
        strcpy(filename, argv[1]);
        arr = parseFile(filename, &size, name);
        analyzeTrends(arr, size, name);
        // if(){
        // 
        // }
        free(arr);
        free(name);
    }
    return 0;
}
