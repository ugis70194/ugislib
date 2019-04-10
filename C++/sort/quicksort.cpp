#include<iostream>
#include<vector>
#include<random>
using namespace std;

template <typename comparable> 
int partition(int left, int right, vector<comparable>& arr,int j) {
	cout << left << " " << right << endl;
	int pivotIndex = (left + right) / 2;
	const int pivot = arr[pivotIndex];
	swap(arr[right], arr[pivotIndex]);

	cout << j << endl;
	
	pivotIndex = left;
	for (int i = left; i < right; i++) {
		if (arr[i] <= pivot) {
			swap(arr[i], arr[pivotIndex]);
			pivotIndex++;
		}
	}
	swap(arr[right],arr[pivotIndex]);

	return pivotIndex;
}

template <typename comparable>
void quicksort(int left, int right, vector<comparable>& arr,int i) {

	if (left >= right) return;

	int pivotIndex = partition(left, right, arr, i);
	cout << "i " << i << endl;
	i++;
	
	quicksort(left, pivotIndex - 1, arr, i);
	quicksort(pivotIndex + 1, right, arr, i);
}