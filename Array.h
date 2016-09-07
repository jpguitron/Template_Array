/*
Array header file

Luis Enrique Güitrón
Data Structures
24/08/2016
legl_1995@hotmail.com
*/


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#define STEP 100

template <class type>
class Array
{

private:
	type* data;
	int size;
	int binarySearchRecursive(int item, int start, int end);
	void quickSort(int start, int end, int pivot_index);
	void mergeSort(int partitionSize, int* partition);
	void mergePartitions(int * partA,int sizeA ,int* partB, int SizeB, int*partition);
	void swap(int *a, int*b);

public:
	Array(int size);
	~Array();
	void fillOrdered();
	void fillRandom();
	void printRecursive(unsigned n);
	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void mergeSort();
	void quickSort();
	

	//Searching
	int linearSearch(int item);
	int binarySearchIterative(int item);
	int binarySearchRecursive(int item);

	//Helper method
	bool checkOrdered();
};


template <class type>
Array<type>::Array(int size)
{
	srand(time(NULL));
	data = new int[size];
	this->size = size;

}

//______________________________________Filling array________________________________//

template <class type>
void Array<type>::fillOrdered()
{
	data[0] = rand() % STEP + 1;
	for (unsigned i = 1; i < size; i++)
	{
		data[i]=data[i-1]+ rand() % STEP + 1;

	}
}
template <class type>
void Array<type>::fillRandom()
{
	for (unsigned i = 0; i < size; i++)
	{
		int num = rand() % 100;
		data[i] = num;
	}
}
template <class type>
void Array<type>::printRecursive(unsigned n)
{

	if (n < size)
	{
		std::cout << data[n] << ", ";
		printRecursive(n + 1);
	}

	else
	{
		std::cout << std::endl;
	}
}

//________________________________________Searching_______________________________________//
template <class type>
int Array<type>::linearSearch(int item)
{
	for (int i = 0; i < size; i++)
	{
			if (data[i] == item)
				return i;
	}
	return -1;
}
template <class type>
int Array<type>::binarySearchIterative(int item)
{
	int start = 0;
	int end = size - 1;
	int middle;

	while (start <= end)
	{
		middle = (start + end) / 2;

		if (item < data[middle])
			end = middle - 1;

		else if (item > data[middle])
			start = middle + 1;

		else
			return middle;
	}
	return -1;
}
template <class type>
int Array<type>::binarySearchRecursive(int item)
{
	return binarySearchRecursive(item, 0, size - 1);
}
template <class type>
int Array<type>::binarySearchRecursive(int item, int start, int end)
{
	//Base case
	if (start > end)
		return -1;

	int middle = (start + end) / 2;

	if (item < data[middle])
		return	binarySearchRecursive(item, start, middle - 1);

	else if (item > data[middle])
		return binarySearchRecursive(item, middle + 1, end);

	else
		return middle;
	
}

//__________________________________________Sorting_____________________________________//
template <class type>
void Array<type>::swap(int*a, int*b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
template <class type>
void Array<type>::bubbleSort()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (data[j] < data[j - 1])
			{
				swap(&data[j], &data[j - 1]);
			}
		}
	}
}
template <class type>
void Array<type>::selectionSort()
{
	int smallest_index;

	for (int i = 0; i < size; i++)
	{
		smallest_index = i;

		for (int j = i; j < size; j++)
		{
			if (data[j] < data[smallest_index])
				smallest_index=j;
		}
		swap(&data[i], &data[smallest_index]);
	}
}

template <class type>
void Array<type>::insertionSort()
{
	for (int i = 0; i < size-1; i++)
	{
		for (int j = i+1; j > 0; j--)
		{
			if (data[j] < data[j-1])
				swap(&data[j], &data[j-1]);
		}
	}
}
template <class type>
void Array<type>::quickSort()
{
	quickSort(0, size, 0);
}
template <class type>
void Array<type>::quickSort(int start, int end, int pivot_index)
{
	std::cout << std::endl << "the pivot is " <<data[pivot_index] <<std::endl;

	int store_index = pivot_index+1;

	for (int i = start; i < end - 1; i++)
	{
		if (data[i + 1] < data[pivot_index])
		{
			swap(&data[i + 1], &data[store_index]);
			store_index++;
		}
	}
	swap(&data[pivot_index], &data[store_index - 1]);

	//Call the function until it gets fully ordered//
	if (start + 1< end)
	{
	//Check that the pivot changed position in order to make sure to pick a different pivot//
		if (pivot_index == store_index - 1)
		{
			std::cout<<std::endl << "caso1" << std::endl;
			quickSort(start + 1, end, pivot_index + 1);
		}

	//If the pivot changed you have two partitions
		else
		{
			std::cout << std::endl << "caso2" << std::endl;
			end = store_index-1;
			//quickSort(start, end, pivot_index);
			quickSort(start, end, pivot_index);
		}
	}

	//Go to the right partition
	else if(end+1<size)
	{
		std::cout << std::endl << "caso3" << std::endl;
		start = end + 1;
		pivot_index = start;
		end = size;
		quickSort(start, end, pivot_index);
	}
}
template <class type>
void Array<type>::mergeSort()
{
	mergeSort(size,data);
}
template <class type>
void Array<type>::mergeSort(int partitionSize, int* partition)
{
	
	int middle = (int)(partitionSize/2);
	int partition1[middle];
	int partition2[partitionSize - middle];	
	
	
	//Subdivide array into smaller partitions until they are of size 1//
	if(partitionSize>1)
	{
		for(int i = 0; i<middle; i++)
		{
			partition1[i]=partition[i];
		}	
		
		for(int i = middle; i<partitionSize; i++)
		{
			partition2[i-middle] = partition[i];
		}	
		
		mergeSort(middle,partition1);
		mergeSort(partitionSize-middle,partition2);
		
		//Start sorting partitions, it will start with partitions of size 1 and then go with the bigger ones//
		mergePartitions(partition1,middle,partition2,partitionSize-middle,partition);
	}
	
}
template <class type>
void Array<type>::mergePartitions(int * partA ,int sizeA, int* partB, int sizeB, int* partition)
{
	int index_A=0;
	int index_B=0;
	int index_data=0;
	
	//Make sure to keep inside partitions length when sorting them//
	while(index_A<sizeA && index_B<sizeB)
	{
		if(partA[index_A]<partB[index_B])
		{
			partition[index_data]=partA[index_A];
			index_A++;
		}
		
		else
		{
			partition[index_data]=partB[index_B];
			index_B++;
		}
		index_data++;
	}
	
	//Check if any of the partitions remained with data after one of them is done//
	while(index_A<sizeA)
	{
		partition[index_data]=partA[index_A];
		index_A++;
		index_data++;
	}
	
	while(index_B<sizeB)
	{
		partition[index_data]=partB[index_B];
		index_B++;
		index_data++;
	}
}

//_________________________________Helper Methods________________________________//
template <class type>
bool Array<type>::checkOrdered()
{
	for (int i = 0; i < size-1; i++)
	{
		if (data[i] > data[i + 1])
		{
			return false;
		}
	}
	return true;
}
template <class type>
Array<type>::~Array()
{
	delete[]data;
}
