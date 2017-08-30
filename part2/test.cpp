#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int arr[10];
	for (int i = 0; i < 10; ++i)
		arr[i] = i;

	int sum = 0;
	int sumx = 10;

	#pragma omp parallel for default(shared) reduction(+:sum, sumx)
	for (int i = 0; i < 10; ++i){
		sum += arr[i];
		sumx += arr[i];
	}

	cout << sum << endl;
	cout << sumx << endl; 
}

