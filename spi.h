#ifndef _SPI_H
#define _SPI_H
double *parseFile(char *filename, int *size, char *name);
double calculateDailyMA(double price, int numPeriods, double prevMA);
double calculateSMA(double *prices, int numPeriods);
double calculateEMA(double *prices, int numPeriods, double periodSMA);
double *setPriceArray(double *prices, int pricesSize, int arrSize, int multiplier);
double calculateMACD(double *prices, int size);
double calculateSignalLine(double *prices, int size);
int calculateSMACrosses(double *prices, int size);
void analyzeTrends(double *prices, int size, char *name, int flag);
void writeOut(double *prices, int size, char *name, double price, double macd, double prevMACD, double signalLine);
void writeOutSMA(double *prices, int size, FILE *fp);
#endif
