// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SearchTree.h"
#include "HashTable.h"
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
	while (ret < nums && arr[ret++] != key);
	return (ret == nums) ? -1 : ret;	//从一开始编号
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

void BST_TEST(){
	cout << "\t\t - - - BST_TEST - - -\n";
	char arr[] = { 'S','E','X','A','R','C','H','M','Z' };
	size_t nums = sizeof(arr) / sizeof(arr[0]);
	BST<char> bst(arr, nums,2);
	cout << "元素:";
	for (size_t i = 0; i < nums; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "BST 根节点:" << bst.get_root()->value << endl;
	cout << "BST 排序序列: ";
	bst.sort();
	cout << endl;
	cout << "BST 查找 'C'字符: " << bst.search('C') << endl;
	cout << "BST 最小值: " << bst.min() << endl;
	cout << "BST 最大值: " << bst.max() << endl;
	cout << "BST Z 向下取整: " << arr[bst.floor('Z')] << endl;
	cout << "BST R 向下取整: " << arr[bst.floor('R')] << endl;
	cout << "BST A 向下取整: " << arr[bst.floor('A')] << endl;
	cout << "BST Z 向上取整: " << arr[bst.ceil('Z')] << endl;
	cout << "BST R 向上取整: " << arr[bst.ceil('R')] << endl;
	cout << "BST A 向上取整: " << arr[bst.ceil('A')] << endl;
	cout << "BST H 的排名: " << bst.rank('H') << endl;
	cout << "BST C 的排名: " << bst.rank('C') << endl;
	cout << "BST Z 的排名: " << bst.rank('Z') << endl;
	cout << "BST 选择排名为3的元素:" << bst.select(3) << endl;
	cout << "BST 选择排名为9的元素:" << bst.select(9) << endl;
	cout << "BST 排名第4的是: " << bst.select(4) << endl;
	cout << "\t\t - - - END_TEST - - -\n\n";
}

void HASH_TEST() {
	cout << "\t - - - HASH_TEST - - - \n";
	char arr[] = { 'S','E','X','A','R','C','H','M','Z' };
	size_t nums = sizeof(arr) / sizeof(arr[0]);
	Hash_Table<char> ht(arr, nums, 16);
	cout << "元素:   ";
	for (size_t i = 0; i < nums; i++) {
		cout << arr[i] << "  ";
	}
	cout << "\n对应的哈希值:";
	for (size_t i = 0; i < nums; i++) {
		cout << ht.M_JSHash(arr[i]) << "  ";
	}
	cout << endl;
	cout << "HT 查找 S 的索引:" << ht.search('S') << endl;
	cout << "HT 查找 Z 的索引:" << ht.search('Z') << endl;
	cout << "HT 查找 M 的索引:" << ht.search('M') << endl;
	cout << "HT 查找 B 的索引:" << ht.search('B') << endl;
	cout << "\t - - - END_TEST - - - \n";
}

int main()
{
	HASH_TEST();
	system("pause");
    return 0;
}
