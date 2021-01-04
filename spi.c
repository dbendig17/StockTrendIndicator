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

//takes in arr of prices for each period in period length
//also takes in the previous num periods SMA, to use as the first
//prevMA in the DailyMA calculation
//returns double array of EMA values for a period
double calculateEMA(double *prices, int numPeriods, double periodSMA) {
    int counter = numPeriods;
    double curMA;
    int i;

    for(i = 0; i < counter; i++) {
        if(i == 0){
            curMA = calculateDailyMA(prices[i], numPeriods, periodSMA);
        } else {
            curMA = calculateDailyMA(prices[i], numPeriods, curMA);
        }
        //printf("%f\n", curMA);
    }

    return curMA;
}

double *setPriceArray(double *prices, int pricesSize, int arrSize, int multiplier){
    int startIdx = pricesSize - (arrSize * multiplier);
    int i, j;
    double *priceArr = malloc(sizeof(double) * arrSize);
    j = 0;
    for(i = startIdx; i < (pricesSize - (arrSize * (multiplier - 1))); i++) {
        priceArr[j] = prices[i];
        //printf("added: %f at %d\n", prices[i], j);
        j++;
    }

    return priceArr;
}

//make MACD calculation function, refer to resources
double calculateMACD(double *prices, int size) {
    double *arr12;
    double *arr26;

    if(size < 52) {
        printf("Cannot calculate MACD, must have 52 periods of data.\n");
        return 0.0;
    } else {
        double sma12, sma26, ema12, ema26;
        //fill arr for 26 period SMA
        arr12 = setPriceArray(prices, size, 12, 2);
        arr26 = setPriceArray(prices, size, 26, 2);
        sma26 = calculateSMA(arr26, 26);
        sma12 = calculateSMA(arr12, 12);
        free(arr12);
        free(arr26);
        // printf("sma12 %f\n", sma12);
        // printf("sma26 %f\n", sma26);
        arr12 = setPriceArray(prices, size, 12, 1);
        arr26 = setPriceArray(prices, size, 26, 1);
        ema12 = calculateEMA(arr12, 12, sma12);
        ema26 = calculateEMA(arr26, 26, sma26);
        //printf("ema12 %f\n", ema12);
        //printf("ema26 %f\n", ema26);
        free(arr12);
        free(arr26);
        return ema12 - ema26;
    }
}

double calculateSignalLine(double *prices, int size){
    int i, j, k;
    double *signalLine = malloc(sizeof(double) * 9);

    j = 0;
    k = 8;
    for(i = 0; i < 9; i++){
        signalLine[j] = calculateMACD(prices, (size - k));
        //printf("%f\n", signalLine[j]);
        j++;
        k--;
    }
    return calculateSMA(signalLine, 9);
}

//calculate signal line function

//make chooseAction function(using information from signal line)

//make display function

//output with text file given as well(keep date and add EMA value?)
