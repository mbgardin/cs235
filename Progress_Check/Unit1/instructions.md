# Unit 1 Progress Check


`unemployment.txt` contains information about the unemployment rates for states for approximately the last 50 years. 
Each row contains (in the following order) the name of the state, the year, the month and the unemployment rate. 


Your task is to write a command line utility that allows someone to see what the average unemployment rate is for a given state, and year.
It may be assumed that the tests will always provide 3 arguments and provide valid input for the state, and year.


## Example Usages
To find average unemployment rate for Alabama in 1976 from the data in the small_example.txt
The program would be run in the following way: 
```./unemployment_rate tiny_example.txt Alabama 1976
7.5
```

To specify a different file, the first command-line argument would be changed.  
For example, the following would look at the small-example.txt
```./unemployment_rate small_example.txt Michigan 2000 
3.98333
```

The program should check if the file exists. 
If the file does not exist, the program should print out a statement like the following, and return immediately. 
```./unemployment_rate non-existent-file.txt Wisconsin 2002 
ERROR: could not open file
```

## C++ Reference

You can use the built-in function `stof` to convert string to a `float`:
```c++
float number = stof("3.1415");
```
