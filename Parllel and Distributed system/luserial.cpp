#include<bits/stdc++.h>
#include<omp.h>
#include<fstream>
using namespace std;
using namespace std::chrono;


int  MATRIX_SIZE; 


#define MAX 2000

double mat[MAX][MAX];
double mat_dup[MAX][MAX];
double u[MAX][MAX];
double l[MAX][MAX];
double p[MAX];

int main(int argc, char *argv[])
{
        
	int n;
	sscanf(argv[1], "%d", &n);   // sscanf() is used to read formatted input from the string

	
	auto start_timer = high_resolution_clock::now();
	
    	MATRIX_SIZE=n;
        

	
	struct drand48_data buffer;
     // intialisation of matrix
	for(int i=1; i<=n ; i++)
	{
		for(int j=1; j<=n; j++)
		{
			drand48_r( &buffer, &(mat[i][j]) );
			mat[i][j] *= 10000;
			mat_dup[i][j] = mat[i][j];
		}
	}	



	
	 // intialisation of permutation
	for( int i=1 ;i<=n ;i++){
		p[i]=i;
	}
	
	 // intialisation of matrix u

	for( int i=1;i<=n ; i++){
		for(int j=1; j<=n ; j++){
			if(i>j){
				u[i][j]=0;
			}
			else u[i][j]=1;
		}
	}
	
	 // intialisation of matrix l

	for( int i=1;i<=n ; i++){
		for(int j=1; j<=n ; j++){
			if(i<j){
				l[i][j]=0;
			}
			else if(i==j){
				l[i][j]=1;
			}
			else l[i][j]=1;
		}
	}


    int k1 = -1;
	int k=1;
	for( ; k<=n ; k++){
		int mx=0;
		for( int i=k; i<=n ; i++){
			if(mx< mat[i][k]){
				mx=mat[i][k];
				k1=i;
			}
		}
		if(mx==0)
			cout<<"singular matrix"<<endl;


	swap(p[k], p[k1]);
        for(int i=1; i<=n; i++) {
            swap(mat[k][i], mat[k1][i]);
        }
        for(int i=1; i<=k; i++) {
            swap(l[k][i], l[k1][i]);
        }
		
		
		
		u[k][k]=mat[k][k];

		for(int i=k+1; i<=n ; i++){
			l[i][k]=mat[i][k]/u[k][k];
			u[k][i]=mat[k][i];
		}


		for(int i = k+1; i<=n ; i++){
			for(int j = k+1; j<=n ; j++){
				mat[i][j] = mat[i][j] - l[i][k]*u[k][j];
			}
		}
	}
	

/*	
	
	printf("\n");
	printf("Original matrix\n");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)	cout << mat[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	

	printf("\n");
	printf("lower triangular matrix\n");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)	cout << l[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	printf("\n");
	printf("upper triangular matrix\n");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)	cout << u[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	printf("\n");
	printf("permutation matrix\n");
	for(int i=1; i<=n; i++)	cout << p[i] << " ";
	cout << endl;


	printf("\n");

    	printf("Multiplication of lower and upper triangular matrix\n");

	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			double temp = 0;
			for(int k=1; k<=n; k++)
			{
				temp += l[i][k]*u[k][j];
			}
			cout << temp << " ";
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
    	myfile.open ("serialOutput.txt", ios::app);
    	myfile << n<<","<<duration_time.count()/1000000.0  << endl;
    	myfile.close();

}

