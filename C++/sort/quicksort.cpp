#include<iostream>
#include<vector>
#include<random>
#include<unordered_map>
using namespace std;

template <typename comparable>
int partition(vector<comparable>& arr, const int& left,const int& right) {
	const int pivot = arr[right];
	int pivotIndex = left - 1;

	for (int i = left; i < right; i++) {
		if (arr[i].num <= pivot) {
			pivotIndex++;
			swap(arr[i], arr[pivotIndex]);
		}
	}
	swap(arr[right], arr[++pivotIndex]);

	return pivotIndex;
}

template <typename comparable>
void quicksort(vector<comparable>& arr,const int& left,const int& right) {
	if (left >= right) return;

	int pivotIndex = partition(arr, left, right);

	quicksort(arr, left, pivotIndex - 1);
	quicksort(arr, pivotIndex + 1, right);
}