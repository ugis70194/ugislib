#include<iostream>
#include<vector>
#include<random>
using namespace std;

template<typename comparable>
void merge(vector<comparable>& arr, const int& left,const int& mid, const int& right) {
	int leftSideLength = mid - left;
	int rightSideLength = right - mid;

	vector<comparable> leftSide(leftSideLength);
	vector<comparable> rightSide(rightSideLength);

	for (int i = 0; i < leftSideLength; i++) {
		leftSide[i] = arr[left + i];
	}
	for (int i = 0; i < rightSideLength; i++) {
		rightSide[i] = arr[mid + i];
	}

	int i = 0, j = 0, cnt = 0;
	for (int k = left; k < right; k++) {
		if (i >= leftSideLength) {
			arr[k] = rightSide[j];
			j++;
			continue;
		}
		if (j >= rightSideLength) {
			arr[k] = leftSide[i];
			i++;
			continue;
		}
		
		if (leftSide[i] <= rightSide[j]) {
			arr[k] = leftSide[i];
			i++;
		}
		else {
			arr[k] = rightSide[j];
			j++;
		}
	}
}

template<typename comparable>
void mergeSort(vector<comparable>& arr, const int& left, const int& right) {
	if (right - left > 1) {
		const int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid, right);
		merge(arr, left, mid, right);
	}
}
