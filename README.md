# StockTrendIndicator
This is a finished small portfolio project developed completely in the C language, in a Linux environment using GCC for compiling.

Purpose
The purpose of this project was for me to learn more about the different formulas for analyzing trends in the price of a stock, and also to remain sharp in my C programming skills over the christmas break. Additionally, I wanted to make a program that was both simple or easy to use, and helpful for someone trying to decide if they should think about purchasing a given stock.

Usage
To compile: make main or make all
To run: ./main inputFile.txt (-f)
*-f flag will result in an output textfile being created when the program is run.

Input file format
For the format of the input file, I used a very specific process. I obtained my data using Google Finance, organized with Google Sheets. To create a valid input file, open a new sheets document, and in a column type: "=GOOGLEFINANCE("name(ex AAPL)", "price", "start date(ex 01/01/2020)", "end date(12/01/2020)")". This will produce a list of the stocks prices from the start date to the end date, do not edit this information or add anything else. Simply save the file as a .csv, and then to a .txt. The .txt format of this file is your program input.
