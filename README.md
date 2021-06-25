# openmp_sorting
### Aim: sort a structure by using multiple threads using OPENMP and C++. 
The objective of this experiment is to sort a structure by using multiple threads using OPENMP. We
are using OpenMP with C++. OPENMP isone of the oldest and standard libraries for parallel
processing. It is supported by various programming languages like C, C++, Java and Python. <br/>

We have implemented library sort.h with functions for merge sort, quick sort, radix sort, and heap
sort. In this experiment, we are not using any additional memory and taken minimum
communication with other thraeds which has a great impact on speed and scalability. <br/>
After calling the sort function with reference to data in it, each process calculate the index and
offset of the data element to be kept in repeated manner. As there is an exact similar copy of data for
each process every other process could easily guess the values of other process. <br/>

## Experiment:
### Create executable file using:
g++ -fPIC -c -Wall sort.cpp <br/>
gcc -shared -o libpsort.so sort.o
### Run the file using:
bash test.sh //this will give an idea about speedup and thraed
