#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi.h"

//takes in pointer to file, parses information into arr
//returns arr by reference
double *parseFile(char *filename) {
    FILE *fp = NULL;
    double *out = NULL;
    char tempStr[50] = "";
    char date[10] = "";
    char value[15] = "";
    int counter = 0;
    int index = 0;
    double curVal = 0.0;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(-2);
    }

    while(fgets(tempStr, 50, fp) != NULL){
        counter++;
    }
    out = malloc(sizeof(double) * counter);

    fseek(fp, 0, SEEK_SET);
    while(fgets(tempStr, 50, fp) != NULL){
        sscanf(tempStr, "%s %s", date, value);
        if(strcmp(value, "") != 0){
            char delim[] = ",";
            char *valPtr = strtok(value, delim);
            valPtr = strtok(NULL, delim);
            curVal = atof(valPtr);
            out[index] = curVal;
            index++;
        }
    }
    out[index] = -1;
    
    fclose(fp);
    return out;
}
