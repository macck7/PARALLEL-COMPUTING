# Parallel Programming

This project consists of two LU decomposition implementations that employ Gaussian elimination to factor a dense **N x N** matrix into an upper-triangular and lower-triangular one. Pivoting is the process of finding the biggest magnitude value in a row, column, or both in a matrix and then swapping rows and/or columns in the matrix for the next step in the algorithm. Pivoting is used to eliminate round-off error and increase numerical stability. Row pivoting, a type of pivoting that includes interchanging rows of a trailing submatrix based on the biggest value in the current column, is used in this project. To execute LU decomposition with row pivoting, a permutation matrix P must be computed with PA = LU.The row exchanges are recorded in the permutation matrix.

### Pseudo Code
```
Below is pseudocode for a sequential implementation of LU decomposition with row pivoting.
    inputs: a(n,n)
    outputs: π(n), l(n,n), and u(n,n)

    initialize π as a vector of length n
    initialize u as an n x n matrix with 0s below the diagonal
    initialize l as an n x n matrix with 1s on the diagonal and 0s above the diagonal
    for i = 1 to n
      π[i] = i
    for k = 1 to n
      max = 0
      for i = k to n
        if max < |a(i,k)|
          max = |a(i,k)|
          k' = i
      if max == 0
        error (singular matrix)
      swap π[k] and π[k']
      swap a(k,:) and a(k',:)
      swap l(k,1:k-1) and l(k',1:k-1)
      u(k,k) = a(k,k)
      for i = k+1 to n
        l(i,k) = a(i,k)/u(k,k)
        u(k,i) = a(k,i)
      for i = k+1 to n
        for j = k+1 to n
          a(i,j) = a(i,j) - l(i,k)*u(k,j)
          
    Here, the vector π is a compact representation of a permutation matrix p(n,n), 
    which is very sparse. For the ith row of p, π(i) stores the column index of
    the sole position that contains a 1.
```

## OpenMP
Open Multi-processing (OpenMP) is a technique of parallelizing a section(s) of code in C/C++ languages. OpenMP is also seen as an extension to C/C++ languages by adding the parallelizing features to them.
In general, OpenMP uses a portable, scalable model that gives programmers a simple and flexible interface for developing parallel applications for platforms that ranges from the normal desktop computer to the high-end supercomputers.
In OpenMP, Before running the code, we can initialise the number of threads to be executed using the following command. Here, we set the number of threads to be getting executed to be 8 threads.
export OMP_NUM_THREADS=8


## Posix Thread(p-thread)
C/C++ languages provide the POSIX thread(pthread) standard API(Application program Interface) for all thread related functions. Pthread allows us to create multiple threads for concurrent process flow. It is most effective on multiprocessor or multi-core systems where threads can be implemented on a kernel-level for achieving the speed of execution. Gains can also be found in uni-processor systems by exploiting the latency in IO or other system functions that may halt a process. We must include the pthread.h header file at the beginning of the script to use all the functions of the pthreads library. To execute the c file, we have to use the -pthread or -lpthread in the command line while compiling the file.


## Flow of Control
First of all we have 3 inpedent file which are responsible for serial and parellel processing.
Serial compution is done with the help of seiral.cpp  which it takes whole input matrix and process sequentionlly one by one.
Parllel computation is done with the help oh OpenMP and Pthread. 
After complie all three .cpp codes we have passed different sizes of matrixes to all three file in order to observare the computation time.
Also we have plotted graph to easily compare which type of comuption better for different size.


## Description of code files

luserial.cpp    -       contains c++ code for serial execution for LU decompostion
luomp.cpp       -       contains c++ code for parellel execution using OpenMP library
luthread.cpp    -       contains c++ code for parellel execution using Pthread
Makefile        -       contains program which helps us to compile all above code at once.
LU_Serial_Output.txt -  contains result(time) for executon of different sizes  for serial code.
LUOmp_Output.txt  -     contains result(time) for executon of different size matrices for Parllel excution using OpenMP.
threadOutput.txt  -     contains result(time) for executon of different size matrices for Parllel excution using Pthread.
bar_chart.py  -         Code for reading above three text file and plotting a bar graph.
line_plot.py  -         Code for reading above three text file and plotting a line plot. 
bash.sh      -          Files runs the bash script, which automates the whole process and saves results for plotting graphs for analyises.


## Results
![image](https://raw.githubusercontent.com/macck7/Parllel-and-Distributed-system/main/line_plot.png)
