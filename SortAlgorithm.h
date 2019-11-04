#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <ratio>

using namespace std;

long long int insertCampareTimes;
long long int insertMoveTimes;
long long int mergeCampareTimes;
long long int mergeMoveTimes;
long long int quickCampareTimes;
long long int quickMoveTimes;

namespace SortAlgorithm
{
	//插入排序，算法复杂度是O(n^2)，但是在同样规模下会比选择排序效率高
	template<typename T>
	void insertionSort(T arr[], int n)
	{
		insertCampareTimes = 0;
		insertMoveTimes = 0;
		for (int i = 1; i < n; i++)   //从第二个元素排序即可
		{
			insertCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > 0 && arr[j - 1] > e; j--)
			{
				insertCampareTimes += 2;
				arr[j] = arr[j - 1];   //这是一个不断前推的过程
				insertMoveTimes++;
			}
			arr[j] = e; //使用这种方法的效率会比直接使用swap函数高
			insertMoveTimes++;
		}
	}

	//对arr[l ... r]进行插入排序
	template<typename T>
	void __insertionSortForMerge(T arr[], int l, int r)
	{
		for (int i = l + 1; i <= r; i++)
		{
			mergeCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > l&& arr[j - 1] > e; j--)
			{
				mergeCampareTimes += 2;		//比较过程是两个的交
				arr[j] = arr[j - 1];
				mergeMoveTimes ++;
			}
			arr[j] = e;
			mergeMoveTimes ++;
		}
		return;
	}

	//对arr[l ... r]进行插入排序
	template<typename T>
	void __insertionSortForQuick(T arr[], int l, int r)
	{
		for (int i = l + 1; i <= r; i++)
		{
			quickCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > l && arr[j - 1] > e; j--)
			{
				quickCampareTimes += 2;
				arr[j] = arr[j - 1];
				quickMoveTimes ++;
			}
			arr[j] = e;
			quickMoveTimes ++;
		}
		return;
	}

	//对arr[l...mid]以及arr[mid+1...r]进行归并过程
	template<typename T>
	void __merge(T arr[], int l, int mid, int r)
	{
		T* aux = new T[r - l + 1];
		for (int i = l; i <= r; i++)
			aux[i - l] = arr[i];

		int i = l, j = mid + 1;
		for (int k = l; k <= r; k++)
		{
			mergeCampareTimes ++;		//比较次数+1
			if (i > mid)
			{
				mergeCampareTimes ++;	//腾挪次数+1
				arr[k] = aux[j - l];
				mergeMoveTimes ++;		//腾挪次数+1
				j++;
			}
			else if (j > r)
			{
				mergeCampareTimes += 2;	//比较次数+2,因为if也进行了比较,不成立才到了这里,下面同理
				arr[k] = aux[i - l];
				mergeMoveTimes ++;		//腾挪次数+1
				i++;
			}
			else if (aux[i - l] <= aux[j - l]) //这样不会破坏算法的稳定性
			{
				mergeCampareTimes +=3;	//比较次数+3
				arr[k] = aux[i - l];
				mergeMoveTimes ++;		//腾挪次数+1
				i++;
			}
			else
			{
				mergeCampareTimes += 3;	//比较次数+3
				arr[k] = aux[j - l];
				mergeMoveTimes ++;		//腾挪次数+1
				j++;
			}
		}
		delete[] aux;
	}

	//所有涉及到递归过程以及其他不希望用户直接使用的函数，均以双下划线开头
	//对arr[l ... r]进行合并排序
	template<typename T>
	void __mergeSort(T arr[], int l, int r)
	{
		//避免递归到底浪费大量的堆栈空间和时间，所以当前数组长度小于16时，直接进入插入排序
		if (r - l <= 15)
		{
			__insertionSortForMerge(arr, l, r);
			return;
		}

		int mid = l + (r - l) / 2;  //防止溢出
		__mergeSort(arr, l, mid);
		__mergeSort(arr, mid + 1, r);

		//如果左边待合并数组的最右侧值小于右边最小值，可以直接合并成一个数组，不用进入merge过程
		if (arr[mid] > arr[mid + 1])
		{
			mergeCampareTimes++;
			__merge(arr, l, mid, r);
		}
	}

	//自顶向下的合并排序
	template<typename T>
	void mergeSort(T arr[], int n)
	{
		mergeCampareTimes = 0;
		mergeMoveTimes = 0;
		__mergeSort(arr, 0, n - 1);
	}

	//返回p,使得arr[l...p-1]<arr[p],arr[p+1...r]>arr[p]
	template<typename T>
	int __partition(T arr[], int l, int r)
	{
		swap(arr[l], arr[rand() % (r - l + 1) + l]); //随机交换作为参考值
		quickMoveTimes += 3;	//一个swap过程对应3次腾挪操作
		T e = arr[l];
		int j = l;
		for (int i = l + 1; i <= r; i++)
		{
			quickCampareTimes ++;
			if (arr[i] < e)
			{
				quickCampareTimes ++;
				j++;
				swap(arr[i], arr[j]);
				quickMoveTimes += 3;
			}
		}
		swap(arr[l], arr[j]);
		quickMoveTimes += 3;

		return j;
	}

	//对arr[l ... r]进行快速排序
	template<typename T>
	void __quickSort(T arr[], int l, int r)
	{
		if (r - l <= 15)
		{
			__insertionSortForQuick(arr, l, r);
			return;
		}

		int p = __partition(arr, l, r);

		__quickSort(arr, l, p - 1);
		__quickSort(arr, p + 1, r);
	}

	//快速排序
	template<typename T>
	void quickSort(T arr[], int n)
	{
		quickCampareTimes = 0;
		quickMoveTimes = 0;
		srand(time(NULL));
		__quickSort(arr, 0, n - 1);
	}
}
