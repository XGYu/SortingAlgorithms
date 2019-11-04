/***
 * 比较插入排序、合并排序、快速排序三种算法
 * 包括移动次数、比较次数、效率分析(运行时间测试)、稳定性分析
 ***/

#include "SortTestHelper.h"

using namespace SortTestHelper;
using namespace SortAlgorithm;

 

int main() {
	int n;
	n = 1000;
	cout << "Array size is " << n << endl;
	int* arr1 = generateRandomArray(n, 0, n);
	int* arr2 = copyArray(arr1, n);
	int* arr3 = copyArray(arr1, n);
	cout << "The first situation,complately random array:" << endl;
	testSort("InsertionSort", insertionSort, arr1, n);
	testSort("MergeSort", mergeSort, arr2, n);
	testSort("QuickSort", quickSort, arr3, n);
	cout << endl;

	int* arr4 = generateNearlyOrderedArray(n, n / 100);
	int* arr5 = copyArray(arr4, n);
	int* arr6 = copyArray(arr4, n);
	cout << "Second situation,Nearly Ordered array:" << endl;
	testSort("InsertionSort", insertionSort, arr4, n);
	testSort("MergeSort", mergeSort, arr5, n);
	testSort("QuickSort", quickSort, arr6, n);
	
	cout << endl;
	int* arr7 = generateNearlyReverseArray(n, n / 100);
	int* arr8 = copyArray(arr7, n);
	int* arr9 = copyArray(arr7, n);
	cout << "Third situation,Nearly Reverse Ordered array:" << endl;
	testSort("InsertionSort", insertionSort, arr7, n);
	testSort("MergeSort", mergeSort, arr8, n);
	testSort("QuickSort", quickSort, arr9, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;
	delete[] arr8;
	delete[] arr9;
	return 0;
}