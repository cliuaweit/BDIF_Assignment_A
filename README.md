# BDIF_Assignment_A
Given the data in the data file "data.txt", use program "SCRUB" to separate the signal from the noise. Use second program "NORMAL" to analyze the scrubbed output of the "SCRUB" program to explore its properties 
================================================================================================================================

Strategy:
We start from dealing with the small data file first.

1. first problem is how to read the data. The difficult part is to read the time. We need to store the time as some numbers so     that we can sort the time. We need to do so because we will calculate the assest return. The input format of the time is 20140804:10:00:00.574914. So the idea is to separate it as day, hour, minute, second. Store type as long, int, int, float. 

   Now a reasonable way has come out. Write a structure called record, it stores day, hour, minute, second, price and volume. It    also should have an overloading method ">" in order to sort the records in the file.

   Next write a class called matrix in order to store all the records from a SMALL data file. The class can have several methods    such as return, mean etc.
