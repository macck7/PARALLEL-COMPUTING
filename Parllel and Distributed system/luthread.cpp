#include<bits/stdc++.h>
#include<pthread.h>
#include <fstream>
#include<chrono>
#include<time.h>
#include<algorithm>
#include<cmath>
#include<pthread.h>
#include<cstdlib>
#include<cmath>
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)


using namespace std;
using namespace std::chrono;

int  MATRIX_SIZE; 
int MAX_THREAD;
int k1;
int k_dash1;

#define MAX 3000

double matrix[MAX][MAX];
double matrix_dup[MAX][MAX];
double u[MAX][MAX];
double l[MAX][MAX];
double p[MAX];
int step_i = 0;


pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t   barrier;



void* multi(void* arg)
{

	pthread_mutex_lock( &mut );
	int tid = step_i++;
	pthread_mutex_unlock( &mut );


    	int k=k1;int k_dash=k_dash1;
	int ceil_1 = ceil( ( (k*(1.0)) / MAX_THREAD ) );
	int ceil_2 = ceil( ( ((MATRIX_SIZE-k-1)*(1.0)) / MAX_THREAD ) );
	int s1 = tid * ceil_1;
	int e1 = s1 + ceil_1;
	e1 = e1  > (k) ? (k) : e1;
	int s2 = (k+1) + tid * ceil_2;
	int e2 = s2 + ceil_2;
	e2 = e2  > (MATRIX_SIZE) ? (MATRIX_SIZE) : e2;



	for(int i=s1; i<e1; i++)
	{
		swap(l[k][i],l[k_dash][i]);		

	}
	double u_k_k = u[k][k];
	for(int i=s2; i<e2; i++)
	{
		l[i][k] = matrix[i][k]/u_k_k;
		u[k][i] = matrix[k][i];
	}
	



	pthread_barrier_wait(&barrier);
	for(int i=s2; i<e2; i++)
	{
		double operand1 = l[i][k];
		for(int j=k+1; j<MATRIX_SIZE; j++)
			matrix[i][j] -= operand1*u[k][j];
	}

}


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

	int n,t;	
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &t);

	MATRIX_SIZE = n;
	MAX_THREAD = t;

	auto start_timer = high_resolution_clock::now();

	struct drand48_data buffer;
	srand48_r((long int)time(0), &buffer);

	for(int i=0; i<n; i++)
	{
		p[i] = i;
		for(int j=0; j<n; j++)
		{
			drand48_r( &buffer, &(matrix[i][j]) );
			matrix[i][j] *= 1000;
			matrix_dup[i][j] = matrix[i][j];
		}
	}




	pthread_barrier_init(&barrier, NULL, MAX_THREAD);
	pthread_t threads[MAX_THREAD];


		 // intialisation of permutation
	for( int i=0 ;i<n ;i++){
		p[i]=i;
	}
	
	 // intialisation of matrix u

	for( int i=0;i<n ; i++){
		for(int j=0; j<n ; j++){
			if(i>j){
				u[i][j]=0;
			}
			else u[i][j]=1;
		}
	}
	
	 // intialisation of matrix l

	for( int i=0;i<n ; i++){
		for(int j=0; j<n ; j++){
			if(i<j){
				l[i][j]=0;
			}
			else if(i==j){
				l[i][j]=1;
			}
			else l[i][j]=1;
		}
	}




	for(int k=0; k<MATRIX_SIZE; k++)
	{
		int k_dash = get_maximum_element_index(k, k, MATRIX_SIZE-1);
		if(k_dash == -1)
		{
			cout << "Singular matrix.\n";
			return 0;
		}


		swap(p[k], p[k_dash]);
        	for(int i=1; i<=n; i++) {
            	swap(matrix[k][i], matrix[k_dash][i]);
        	}
        	for(int i=1; i<=k; i++) {
            	swap(l[k][i], l[k_dash][i]);
        	}


		u[k][k]=matrix[k][k];   //Diagonal element

		
		//creating threads for parallel computations

        k1=k;k_dash1=k_dash;
		for(int i=0; i<MAX_THREAD; i++){
			int *pi;
			pthread_create(&threads[i], NULL, multi, (void *)(pi));
		}
		//joining threads
		for(int i=0; i<MAX_THREAD; i++){
			pthread_join(threads[i], NULL);

		}

		step_i = 0;
	}



	// printing decompostions 

/*
	for( int i=0 ;i<n ;i++){
		for( int j=0 ;j<n ; j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"\n";
	cout<<"\n";
	for( int i=0 ;i<n ;i++){
		for( int j=0 ;j<n ; j++){
			cout<<l[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"\n";
	cout<<"\n";	
	
	for( int i=0 ;i<n ;i++){
		for( int j=0 ;j<n ; j++){
			cout<<u[i][j]<<" ";
		}
		cout<<endl;
	}  

	cout<<"\n";

	cout<<"\n";	

	for(int i=0 ; i<n ; i++) cout<<p[i]<<"   ";
	cout<<"\n";cout<<"\n";	



	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix_dup[i][j] = 0;
 
            for (int k = 0; k < n; k++) {
                matrix_dup[i][j] += l[i][k] * u[k][j];
            }
 
            cout << matrix_dup[i][j] << "\t";
        }
 
        cout << endl;
    }
*/
	// getting the end time
	auto end_time = high_resolution_clock::now();
	// get the duration
	auto duration_time = duration_cast<microseconds>(end_time - start_timer);
	cout << "Time taken: " << duration_time.count()/1000000.0 << " seconds" << endl;

	
	ofstream myfile;
    	myfile.open ("threadOutput.txt", ios::app);
    	myfile << n<<","<<duration_time.count()/1000000.0  << endl;
    	myfile.close();


}

