// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "search.h"
#include <iostream>

using namespace std;

/*
//get array_len

//Method 1:
	template <typename T, size_t N>
	char(&_ArraySizeHelper(T(&array)[N]))[N];

	#define array_len(array) (_ArraySizeHelper(array))

//Method 2:
	template <class T,size_t N>
	size_t array_len(T (&arr)[N]) {
		//arr won't be resolved to be a pointer because of template reference
		return sizeof(arr) / sizeof(arr[0]);
	}
*/

template <class T, size_t N>
size_t array_len(T(&arr)[N]) {
	//arr won't be resolved to be a pointer because of template reference
	return sizeof(arr) / sizeof(arr[0]);
}
int SeqentialSearch(int arr[], int key, int nums) {
	int ret = 0;
	while (ret <= nums && arr[ret++] != key);
	return (ret == nums + 1) ? -1 : ret - 1;
}
int BinarySearch(int arr[], int key, int nums) {
	//sort(arr, arr + nums);
	//Assume that arr is ordered

	/*
		Recursive Edition:
		int BinarySearch(int arr[],int key,int lo,int hi){
			if(hi < lo) return lo;
			int mi = lo + (hi - lo)/2;
			if(key > arr[mi])		BinarySearch(arr,key,mi+1,hi);
			else if(key < arr[mi])	BinarySearch(arr,key,lo,mi-1);
			else					return mid;
		}
	*/
	int lo = 0;
	int hi = nums - 1;
	int mi = 0;
	while (lo <= hi) {
		mi = lo + (hi - lo) / 2;
		if (key < arr[mi])	hi = mi - 1;
		else if (key > arr[mi])	lo = mi + 1;
		else return mi;
	}
	return -1;
}

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int nums = array_len(arr);
	cout << "初始化数组,存放 1~16\n";
	cout << "二分查找 12: " << BinarySearch(arr, 12, nums);
	cout << "顺序查找 12: " << SeqentialSearch(arr, 12, nums);
	system("pause");
    return 0;
}

