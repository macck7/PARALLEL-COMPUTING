#include<bits/stdc++.h>
#include<omp.h>
#include<fstream>
using namespace std;
using namespace std::chrono;


int  MATRIX_SIZE; 
int NUM_THREADS;
int k1;
int k_dash1;

#define MAX 1000



double matrix[MAX][MAX];
double matrix_dup[MAX][MAX];
double u[MAX][MAX];
double l[MAX][MAX];
double p[MAX];




int main(int argc, char *argv[])
{
        

	sscanf(argv[1], "%d", &MATRIX_SIZE);   // sscanf() is used to read formatted input from the string
	sscanf(argv[2], "%d", &NUM_THREADS);
	
	auto start_timer = high_resolution_clock::now();
	
        int n= MATRIX_SIZE;
        

	struct drand48_data buffer;
       // intialisation of matrix
        
     
 #pragma omp parallel for num_threads(NUM_THREADS) schedule(static, 4) collapse(2) 
	for(int i=1; i<=n ; i++)
	    {
		for(int j=1; j<=n; j++)
                #pragma omp critical
		   {
			drand48_r( &buffer, &(matrix[i][j]) );
			matrix[i][j] *= 1000;
			matrix_dup[i][j] = matrix[i][j];
		   }
	    }
      	

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
 }



   int k1 = -1;
   int k=1,mx;
   for( k=1 ; k<=n ; k++)
     {
            mx=0;
            #pragma omp single
            {
		
		for(int i=k; i<=n ; i++)
		{
		      
			if(mx< matrix[i][k])
			{
				mx=matrix[i][k];
				k1=i;
			}
		}
	    }
	         if(mx==0)
	         cout<<"singular matrix"<<endl;
	         
                swap(p[k], p[k1]);
             
             
             
             
              #pragma omp parallel for num_threads(NUM_THREADS) schedule(static, 4) 
               for( int i=1; i<=n; i++) 
                 {
                      swap(matrix[k][i], matrix[k1][i]);
                 }
               
                  
             #pragma omp parallel for num_threads(NUM_THREADS) schedule(static, 4) 
               for(int  i=1; i<=k; i++) 
                 {
                      swap(l[k][i], l[k1][i]);
                 }
			
                 u[k][k]=matrix[k][k];
                  
               
             #pragma omp parallel for num_threads(NUM_THREADS) schedule(static, 4)    
	        for(int i=k+1; i<=n ; i++)
	        { 
	            
		    l[i][k]=matrix[i][k]/u[k][k];
		    
		    #pragma omp critical
		    
		    {
		       u[k][i]=matrix[k][i];
	            }
	            
	        }
        
            #pragma omp parallel for num_threads(NUM_THREADS) schedule(static) collapse(2) 
	       for(int i = k+1; i<=n ; i++)
	       {
		     for(int j = k+1; j<=n ; j++)
		       {
	          #pragma omp atomic
		           matrix[i][j] = matrix[i][j] - l[i][k]*u[k][j];
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
    	myfile.open ("ompOutput.txt", ios::app);
    	myfile << n<<","<<duration_time.count()/1000000.0  << endl;
    	myfile.close();

}

