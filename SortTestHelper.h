#pragma once

#include "SortAlgorithm.h"


namespace SortTestHelper
{
	//随机生成一个[rangeL,rangeR],规模为n的数组
	int* generateRandomArray(int n, int rangeL, int rangeR)
	{
		srand(time(NULL));
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		return arr;
	}

	//生成一个有序整形数组并随机交换swaptimes次
	int* generateNearlyOrderedArray(int n, int swaptimes)
	{
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = i;
		}
		srand(time(NULL));
		for (int i = 0; i < swaptimes;i++)
		{
			int x = rand() % n;
			int y = rand() % n;
			swap(arr[x], arr[y]);
		}
		return arr;
	}

	//生成一个反序整形数组并随即交换swaptimes次
	int* generateNearlyReverseArray(int n, int swaptimes)
	{
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = n - i - 1;
		srand(time(NULL));
		for (int i = 0; i < swaptimes; i++)
		{
			int x = rand() % n;
			int y = rand() % n;
			swap(arr[x], arr[y]);
		}
		return arr;
	}

	//判断一个数组是否是排好序的
	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}

	//复制一个整形数组
	int* copyArray(int arr[], int n)
	{
		int* arrNew = new int[n];
		copy(arr, arr + n, arrNew);
		return arrNew;
	}

	//测试排序算法的执行时间
	template<typename T>
	void testSort(string sortName, void (*sort)(T[], int), T arr[], int n)
	{
		//先计算这个排序过程进行多少时间
		chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
		sort(arr, n);
		chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();

		chrono::duration<double, std::milli> timeSpend = endTime - startTime;
		//然后确保这个排序过程是正确的
		assert(isSorted(arr, n));
		cout << sortName << ":" << endl  << "Running time: "<< timeSpend.count() << "ms.  ";
		if (sortName == "InsertionSort")
		{
			cout << "Moving times: " << insertMoveTimes << ".  " << "Camparing times: " << insertCampareTimes << ".  " << endl;
		}
		else if (sortName == "MergeSort")
		{
			cout << "Moving times: " << mergeMoveTimes << ".  " << "Camparing times: " << mergeCampareTimes << ".  " << endl;
		}
		else if (sortName == "QuickSort")
		{
			cout << "Moving times: " << quickMoveTimes << ".  " << "Camparing times: " << quickCampareTimes << ".  " << endl;
		}

		return;
	}
}
