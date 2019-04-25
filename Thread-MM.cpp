// CPP Program to multiply two matrix using pthreads 
#include <bits/stdc++.h> 
#include <chrono> 
using namespace std;
using namespace std::chrono; 

// maximum size of matrix 
#define MAX 16

// maximum number of threads 
#define MAX_THREAD 1

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
int step_i = 0; 

void* multi(void* arg) 
{ 
	int core = step_i++; 

	for (int i = core * MAX / MAX_THREAD; i < (core + 1) * MAX / MAX_THREAD; i++) 
		for (int j = 0; j < MAX; j++) 
			for (int k = 0; k < MAX; k++) 
				matC[i][j] += matA[i][k] * matB[k][j]; 
} 


int main() 
{ 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) { 
			matA[i][j] = rand() % 10; 
			matB[i][j] = rand() % 10; 
		} 
	} 
/*
	// Displaying matA 
	cout << endl 
		<< "Matrix A" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			cout << matA[i][j] << " "; 
		cout << endl; 
	} 

	// Displaying matB 
	cout << endl 
		<< "Matrix B" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			cout << matB[i][j] << " ";		 
		cout << endl; 
	} 
*/
	auto start = high_resolution_clock::now();
	
	// declaring four threads 
	pthread_t threads[MAX_THREAD]; 

	// Creating four threads, each evaluating its own part 
	for (int i = 0; i < MAX_THREAD; i++) { 
		int* p; 
		pthread_create(&threads[i], NULL, multi, (void*)(p)); 
	} 

	// joining and waiting for all threads to complete 
	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL);	 
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << endl;

	/*
	// Displaying the result matrix 
	cout << endl 
		<< "Multiplication of A and B" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) 
			cout << matC[i][j] << " ";		 
		cout << endl; 
	} */
	return 0; 
} 
