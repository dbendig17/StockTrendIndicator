#ifndef _SPI_H
#define _SPI_H
double *parseFile(char *filename, int *size);
double calculateDailyMA(double price, int numPeriods, double prevMA);
double calculateSMA(double *prices, int numPeriods);

#endif
