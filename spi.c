#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spi.h"

//takes in pointer to file, parses information into arr
//returns arr by reference
double *parseFile(char *filename, int *size) {
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
    *size = counter - 1;

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
            //printf("%f\n", curVal);
        }
    }
    out[index] = -1;

    fclose(fp);
    return out;
}

//takes in todays price, the number of periods for the calculation,
//and yesterdays MA value
//returns todays MA value in double form
double calculateDailyMA(double price, int numPeriods, double prevMA) {
    double k, out;
    k = 2.0 / (numPeriods + 1);
    out = (price * k) + (prevMA * (1.0 - k));
    return out;
}

//used to calculate the simple moving average of a number set
//output value is required for the first
//yesterdays value for an EMA calculation
double calculateSMA(double *prices, int numPeriods) {
    int i;
    double sum = 0.0;
    for (i = 0; i < numPeriods; i++){
        sum = sum + prices[i];
    }
    return sum / numPeriods;
}

//should use calculateEMA to get first previous day MA value
//call calculateDailyMA for each period
// double calculateEMA(double price, int numPeriods, double periodSMA) {
//     double out;
//     int counter = numPeriods;
//     double prevMA;
//
//     return out;
// }

//make MACD calculation function, refer to resources

//make chooseAction function

//make display function
