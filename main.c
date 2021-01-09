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
    int flag = 0;

    if(argc < 2 || argc > 3){
        fprintf(stderr, "usage: %s 'filename.txt' -f\n", argv[0]);
        exit(-1);
    } else {
        if(argc == 2){
            strcpy(filename, argv[1]);
        } else {
            if(strcmp(argv[1],"-f") == 0){
                flag = 1;
                strcpy(filename, argv[2]);
            } else if (strcmp(argv[2],"-f") == 0) {
                flag = 1;
                strcpy(filename, argv[1]);
            }
        }
        arr = parseFile(filename, &size, name);
        printf("Stock Price Indicator - Dillon B Jan2021\n");
        if(flag){
            analyzeTrends(arr, size, name, 1);
        } else {
            analyzeTrends(arr, size, name, 0);
        }
        free(arr);
        free(name);
    }
    return 0;
}
