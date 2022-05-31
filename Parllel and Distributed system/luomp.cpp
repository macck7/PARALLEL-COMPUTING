#include<bits/stdc++.h>
#include<omp.h>
#include<fstream>
using namespace std;
using namespace std::chrono;


int MATRIX_SIZE; 
int NUM_THREADS;
int k1;
int k;

#define MAX 3000



double matrix[MAX][MAX];
double matrix_dup[MAX][MAX];
double u[MAX][MAX];
double l[MAX][MAX];
double p[MAX];



int get_maximum_element_index( int c, int r1, int r2)
{
	double max_element=0;
	int index=-1;
	for(int i= r1; i<= r2; i++)
	{
		double temp = abs(matrix[i][c]);
		if(temp > max_element)
		{
			max_element = temp;
			index = i;
		}
	}
	if(max_element == 0)
	{
		cout << "Error - singular matrix. Column "<<c<<" is all zeroes"<<endl;
		return -1;
	}
	return index;
}
int main(int argc, char *argv[])
{
        

	sscanf(argv[1], "%d", &MATRIX_SIZE);   // sscanf() is used to read formatted input from the string
	sscanf(argv[2], "%d", &NUM_THREADS);
	
	auto start_timer = high_resolution_clock::now();
	
        int n= MATRIX_SIZE;
        

	struct drand48_data buffer;
	srand48_r((long int)time(0), &buffer);
       // intialisation of matrix
        
#pragma omp parallel num_threads(NUM_THREADS)
  
  {    
       
    #pragma omp sections
     {
         
     #pragma omp section
	{ 
	// intialisation of permutation
	    for( int i=1 ;i<=n ;i++)
	     {
		p[i]=i;
	     }
	}
	
	 // intialisation of matrix u
     #pragma omp section
       { 
	for( int i=1;i<=n ; i++)
	  {
	        
		for(int j=1; j<=n ; j++)
		{
	
			if(i>j)
			{
				u[i][j]=0;
			}
			else u[i][j]=1;
		}
	  }
	}
	
     #pragma omp section
     {
	for( int i=1;i<=n ; i++)
	{
	
		for(int j=1; j<=n ; j++)
		{
		        if(i<j)
			{
				l[i][j]=0;
			}
			else l[i][j]=1;
		}
		
	}
      }
    }
    
    #pragma omp for schedule(static, 4) collapse(2)
	for(int i=1; i<=n ; i++)
	    {
		for(int j=1; j<=n; j++)
		   {
			drand48_r( &buffer, &(matrix[i][j]) );
			matrix[i][j] *= 1000;
			matrix_dup[i][j] = matrix[i][j];
		   }
	    }
       
 }



  
   for(int k=1 ; k<=n ; k++)
     {
  //          mx=0;
    
/*	    for(int i=k; i<=n ; i++)
		{
		      
			if(mx< matrix[i][k])
			{
				mx=matrix[i][k];
				k1=i;
			}
		}
*/

               int k1 = get_maximum_element_index(k, k, n);
		if(k1 == -1)
		{
			cout << "Singular matrix.\n";
			return 0;
		}	    
	
	  #pragma omp parallel for num_threads(NUM_THREADS) schedule(static, 4)     
               for( int i=1; i<=n; i++) 
                 {
                      swap(matrix[k][i], matrix[k1][i]);
                 }
                 
                 
                swap(p[k], p[k1]);
                u[k][k]=matrix[k][k];
            
            
    #pragma omp parallel num_threads(NUM_THREADS)
         {
		
		#pragma omp for schedule(static, 4) nowait 
               for(int  i=1; i<=k; i++) 
                 {
                      swap(l[k][i], l[k1][i]);
                 }
	      
                 
                 
              #pragma omp for schedule(static, 4) 
	        for(int i=k+1; i<=n ; i++)
	        { 
	            
		    l[i][k]=matrix[i][k]/u[k][k];
		    #pragma omp critical
		    {
		       u[k][i]=matrix[k][i];
	            }
	            
	        }
	        
	      #pragma omp for schedule(static, 4)  
	       for(int i = k+1; i<=n ; i++)
	       {
	             double lm = l[i][k];
		     for(int j = k+1; j<=n ; j++)
		       {
		           matrix[i][j] = matrix[i][j] - lm*u[k][j];
		        }
	       }
	     
        
       }
      
   }	

/*
 
    printf("Original matrix\n");
    
    for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{	
		cout << matrix_dup[i][j] << "\t";
		}
		cout <<"\n";
	}
	cout << endl;
	
	printf("\n");
	printf("\n");
	printf("lower triangular matrix\n");
	
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{	
		cout << l[i][j] << "\t";
		}
		cout <<"\n";
	}
	cout << endl;
	
	printf("\n");
	printf("upper triangular matrix\n");
	
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{	
		cout << u[i][j] << "\t";
		}
		cout <<"\n";
	}
	cout << endl;
	
	
	
	printf("\n");
	printf("permutation matrix\n");
	for(int i=1; i<=n; i++)
	{
	
		cout << p[i] << "\t";
	
	}
	cout << endl;
	
	
	
	printf("\n");

    printf("Multiplication of lower and upper triangular matrix\n");
	
	for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix_dup[i][j] = 0;
 
            for (int k = 1; k <= n; k++) {
                matrix_dup[i][j] += l[i][k] * u[k][j];
            }
 
            cout << matrix_dup[i][j] << "\t";
        }
 
        cout << endl;
    }

	printf("\n");printf("\n");
*/
	
	// getting the end time
	auto end_time = high_resolution_clock::now();
	// get the duration

	auto duration_time = duration_cast<microseconds>(end_time - start_timer);
	cout << "Time taken: " << duration_time.count()/1000000.0 << " seconds" << endl;
	
	ofstream myfile;
    	myfile.open ("LUOmp_Output.txt", ios::app);
    	myfile << n<<","<<duration_time.count()/1000000.0  << endl;
    	myfile.close();

}

