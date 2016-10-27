/*
 * main.cpp
 *
 *  Created on: Oct 27, 2016
 *      Author: e1823509
 */

#include <iostream>
#include <algorithm>

using namespace std;

template <class Item>
void printArray(Item input[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << input[i] << " ";
	}
	cout << endl;
}

template <class Item>
void selectionSort(Item input[], int n)
{
	// Expand the sorted part from zero to n-1 (the last element will already be sorted)
	for (int i = 0; i < n-1; ++i)
	{
		// Find the next minimum of the unsorted part
		int min = i;
		for (int j = i+1; j < n; ++j)
		{
			if (input[j] < input[min])
				min = j;
		}
		// Add the minimum to the end of the sorted part
		swap(input[i], input[min]);
	}
}

template <class Item>
void insertionSort(Item input[], int n)
{
	// Iterate from second to the last element to be sorted (first element is already sorted)
	for (int i = 1; i < n; ++i)
	{
		// Get the element to be inserted
		Item tmp = input[i];
		int j; // Index of the insertion position

		// Find the appropriate position to insert the element
		// Shift the elements to right to make place for the insertion
		for (j = i; j > 0 && tmp < input[j-1]; --j)
		{
			input[j] = input[j-1];
		}
		// Actual insertion
		input[j] = tmp;
	}
}

template <class Item>
void shellSort(Item input[], int n)
{
	// Start from gap = n/2, and continue by halving it
	for (int gap = n/2; gap > 0; gap /= 2)
	{
		// Apply insertion sort with increments of the gap size
		// Iterate from second element to the last (first one is already sorted)
		for (int i = 0; i < n; ++i)
		{
			// Get the element to be inserted
			Item tmp = input[i];
			int j;

			// Find the appropriate position to insert the element
			// Shift other elements to right until we find the correct position
			for (j = gap; j > 0 && tmp < input[j-gap]; j -= gap)
			{
				// Shift
				input[j] = input[j-gap];
			}
			// Actual insertion
			input[j] = tmp;
		}
	}
}

template <class Item>
void bubbleSort(Item input[], int n)
{
	bool sorted = false;
	// Move the wall from left to right separating sorted part from the unsorted part
	// Provided that the array is not already sorted
	for (int i = 0; i < n && !sorted; ++i)
	{
		sorted = true;
		// Bubble the minimum from unsorted to the sorted part
		for (int j = n-1; j > i; j--)
		{
			if (input[j] < input[j-1])
			{
				swap(input[j], input[j-1]);
				sorted = false; // Seems not sorted yet
			}
		}
	}
}

template <class Item>
void merge(Item input[], int first, int mid, int last)
{
	// Other cursor variables
	int first1 = first; // First sub-array
	int last1 = mid;
	int first2 = mid + 1; // Second sub-array
	int last2 = last;
	int index; // Cursor for the next empty location in the temporary array
	// Create temporary array large enough to hold all items
	Item *tempArr = new Item[(last1-first1) + (last2 - first2) + 2];

	// Merge
	for (index = 0; (first1 <= last1) && (first2 <= last2);)
	{
		if (input[first1] < input[first2])
			tempArr[index++] = input[first1++];
		else
			tempArr[index++] = input[first2++];
	}

	// Merge the remaining parts (actually it is just a concatenation)
	for (; first1 <= last1;)
		tempArr[index++] = input[first1++];
	for (; first2 <= last2;)
		tempArr[index++] = input[first2++];

	// Write the sorted array on the original one
	for (int i = first, index = 0; i <= last;)
		input[i++] = tempArr[index++];
}

template <class Item>
void mergeSort(Item input[], int first, int last)
{
	if (first < last) // More than one item
	{
		// Bisect the array
		int mid = (last + first) / 2;

		// Merge-sort both arrays separately
		mergeSort(input, first, mid);
		mergeSort(input, mid + 1, last);

		// Merge the sorted arrays together
		merge(input, first, mid, last);
	}
	// else already sorted (there is only one item in the array)
}

int main()
{
	int input[5] = {9, 1, 7, 8, 2};
	int n = sizeof(input) / sizeof(int);

	cout << "Array before sorting:" << endl;
	printArray(input, n);

	//selectionSort(input, n);
	//insertionSort(input, n);
	//shellSort(input, n);
	//bubbleSort(input, n);
	mergeSort(input, 0, 4);

	// Test the merge() method
	/*int inp[6] = {1, 2, 3, 1, 2, 3};
	merge(inp, 0, 2, 5);
	printArray(inp, 6);*/

	cout << "Array after sorting:" << endl;
	printArray(input, n);

	return 0;
}
