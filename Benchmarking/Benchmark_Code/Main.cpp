// Iterative Merge Sort Adapted from Geeks for Geeks

/**
 *  
 *	 PROGRAM DESCRIPTION:	Program to benchmark the runtime of various algorithms 
 *							on various data structures. 
 *
 *	 DATA STRUCTURES:		LL-Based PQ, STL PQ, Vector Based Min Heap
 *							STL std::make_heap()
 *
 *	 ALGORITHMS:			PQ Sort, STL PQ Sort, Heap Sort, STL Heap Sort
 *							Merge Sort, Bubble Sort, STL Quick Sort
 *
 *	 SPECIFICATIONS:		C++, Windows 10, intel Core i7 10th Gen, 4 Cores
 *							8 Logical Processors, L1 L2 L3 cache
 * 
 **/

#include <algorithm> // stl quick_sort
#include <queue> // stl priority_queue
#include <ctime> // std::time
#include <random> // srand (), rand ()
#include <chrono> // high_resolution clock
#include <iostream> // std::cout 
#include <iomanip>

#include "PriorityQueue.hpp"
#include "HeapPriorityQueue.hpp"

void iterMergeSort(std::vector<int>& sorted, int* L, int* R, int n); // Adapted Merge Sort From GeeksForGeeks
void merge(std::vector<int>& sorted, int* L, int* R, int l, int m, int h);
void bubbleSort(std::vector<int>& sorted);
void swap(int* x, int* y);


int main()
{
	/*
	* -------------------------------------------------------------------------------
	*	Testing Sorting Algorithms
	*  ------------------------------------------------------------------------------
	*/

	int SAMPLES = 10; 	// declare sample size
	std::vector<int> sorted; // vector to store sorted results
	std::srand(static_cast<unsigned int>(std::time(nullptr)));	// current time as seed for random generator

	// print header
	std::cout << "************************************************************************" << std::endl;
	std::cout << "SAMPLE SIZE: " << SAMPLES << std::endl;
	std::cout << std::setw(50) << std::left << "DATA STRUCTURE"
		<< std::setw(20) << std::right << "RUNTIME" << std::endl;
	std::cout << "************************************************************************" << std::endl;


	/*
	* -------------------------------------------------------------------------------
	*		Linked List Based PriorityQueue
	*  ------------------------------------------------------------------------------
	*/
	PriorityQueue<int> pq;
	// insert
	for (int i = 0; i < SAMPLES; i++)
		pq.insert(std::rand() % 1000 + 1);
	// sort
	auto start = std::chrono::high_resolution_clock::now();
	while (!pq.isEmpty()) {
		sorted.push_back(pq.min()); pq.removeMin();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	// print runtime result
	std::cout << std::setw(50) << std::left << "Linked List Based Priority Queue  "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;
	// for (size_t i = 0; i < SAMPLES; i++) { std::cout << i << " " << sorted[i] << std::endl; }

	/*
	* -------------------------------------------------------------------------------
	*		STL Priority Queue (Deque)
	*  ------------------------------------------------------------------------------
	*/
	std::priority_queue<int, std::deque<int>> stlPQ;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	sorted.clear();

	// insert
	for (int i = 0; i < SAMPLES; i++)
		stlPQ.push(std::rand() % 1000 + 1);
	// sort
	start = std::chrono::high_resolution_clock::now();
	while (!stlPQ.empty()) {
		sorted.push_back(stlPQ.top()); stlPQ.pop();
	}
	stop = std::chrono::high_resolution_clock::now();
	//print runtime results
	std::cout << std::setw(50) << std::left << "STL Priority Queue  "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;
	//for (size_t i = 0; i < SAMPLES; i++) { std::cout << i << " " << sorted[i] << std::endl; }


	/*
	* -------------------------------------------------------------------------------
	*		Vector Based Min Heap
	*  ------------------------------------------------------------------------------
	*/

	HeapPriorityQueue<int, Compare<int>> minHeap;
	sorted.clear();

	// insert
	for (int i = 0; i < SAMPLES; i++)
		minHeap.insert(std::rand() % 1000 + 1);
	// sort
	start = std::chrono::high_resolution_clock::now();
	while (!minHeap.empty()) {
		sorted.push_back(minHeap.min());
		minHeap.removeMin();
	}
	stop = std::chrono::high_resolution_clock::now();
	// print runtime results
	std::cout << std::setw(50) << std::left << "Vector Based Min Heap "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;
	//for (size_t i = 0; i < SAMPLES; i++) { std::cout << i << " " << sorted[i] << std::endl; }


	/*
	* -------------------------------------------------------------------------------
	*		std::make_heap()
	*  ------------------------------------------------------------------------------
	*/
	std::vector<int> stlHeap;
	sorted.clear();

	// insert elements in vector
	for (int i = 0; i < SAMPLES; i++)
		stlHeap.push_back(std::rand() % 1000 + 1);
	// convert vector to heap with std::make_heap
	std::make_heap(stlHeap.begin(), stlHeap.end());
	// sort
	start = std::chrono::high_resolution_clock::now();
	while (!stlHeap.empty()) {
		sorted.push_back(stlHeap.front());
		std::pop_heap(stlHeap.begin(), stlHeap.end()); // pop element and place at end of list
		stlHeap.pop_back(); // remove from end of list
	}
	stop = std::chrono::high_resolution_clock::now();

	// print runtime results
	std::cout << std::setw(50) << std::left << "STL std::make_heap "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;
	// print sorted
	// for (size_t i = 0; i < SAMPLES; i++) { std::cout << i << " " << sorted[i] << std::endl; }

/*
* -------------------------------------------------------------------------------
*		Merge Sort on std::vector
*  ------------------------------------------------------------------------------
*/
	int* L = nullptr;
	int* R = nullptr;

	sorted.clear();

	// insert elements in vector
	for (int i = 0; i < SAMPLES; i++)
		sorted.push_back(std::rand() % 1000 + 1);
	// sort
	start = std::chrono::high_resolution_clock::now();
	iterMergeSort(sorted, L, R, SAMPLES);
	stop = std::chrono::high_resolution_clock::now();

	delete[] L;
	delete[] R;

	// print runtime results
	std::cout << std::setw(50) << std::left << "Merge Sort on std::vector<int> "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;

	//print sorted
	//for (int i = 0; i < sorted.size(); i++) {
	//	std::cout << i << " " << sorted[i] << std::endl;
	//}

	/*
	* -------------------------------------------------------------------------------
	*		Bubble Sort on std::vector
	*  ------------------------------------------------------------------------------
	*/
	sorted.clear();

	// insert elements in vector
	for (int i = 0; i < SAMPLES; i++)
		sorted.push_back(std::rand() % 1000 + 1);
	// sort
	start = std::chrono::high_resolution_clock::now();
	bubbleSort(sorted);
	stop = std::chrono::high_resolution_clock::now();

	// print runtime results
	std::cout << std::setw(50) << std::left << "Bubble Sort on std::vector<int> "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;


	// print sorted results
	//std::cout << "bubble sort: " << std::endl;
	//for (auto i : sorted) {
	//	std::cout << i << std::endl;
	// }

	/*
	* -------------------------------------------------------------------------------
	*		STL Quick Sort on std::vector
	*  ------------------------------------------------------------------------------
	*/
	sorted.clear();

	// insert elements in vector
	for (int i = 0; i < SAMPLES; i++)
		sorted.push_back(std::rand() % 1000 + 1);
	// sort
	start = std::chrono::high_resolution_clock::now();
	std::sort(sorted.begin(), sorted.end());
	stop = std::chrono::high_resolution_clock::now();

	// print runtime results
	std::cout << std::setw(50) << std::left << "STL Quick Sort on std::vector<int> "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(2)
		<< std::chrono::duration_cast <std::chrono::microseconds>
		(stop - start).count() / 1000. << " milliseconds\n";
	std::cout << "------------------------------------------------------------------------" << std::endl;


	// print sorted results
	//std::cout << "STL quick_sort : " << std::endl;
	//int sz = sorted.size();
	//for (int i = 0; i < sz; i++) {
	//	std::cout << i << " " << sorted[i] << std::endl;
	//}

	std::cout << "\nPress any key to continue " << std::endl;
	char end_of_tests; std::cin >> end_of_tests;


}


// Utility function to find minimum of two integers
int min(int x, int y) { return (x < y) ? x : y; }


/* Iterative mergesort function to sort arr[0...n-1] */
void iterMergeSort(std::vector<int>& sorted, int* L, int* R, int n)
{
	int curr_size;  // For current size of subarrays to be merged
					// curr_size varies from 1 to n/2
	int left_start; // For picking starting index of left subarray
					// to be merged

	// Merge subarrays in bottom up manner.  First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		// Pick starting point of different subarrays of current size
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			// Find ending point of left subarray. mid+1 is starting
			// point of right
			int mid = min(left_start + curr_size - 1, n - 1);

			int right_end = min(left_start + 2 * curr_size - 1, n - 1);

			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			merge(sorted, L, R, left_start, mid, right_end);
		}
	}
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(std::vector<int>& sorted, int* L, int* R, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	static int x = 0;
	/* create temp arrays */
	if (x++ == 0) {
		L = new int[n1];
		R = new int[n2]; // memory leak, need to delete these somewhere
	}
	else {
		delete [] L;
		delete [] R;
		L = new int[n1];
		R = new int[n2];
	}

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = sorted[l + i];
	for (j = 0; j < n2; j++)
		R[j] = sorted[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			sorted[k] = L[i];
			i++;
		}
		else
		{
			sorted[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		sorted[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		sorted[k] = R[j];
		j++;
		k++;
	}
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(std::vector<int>& sorted) {
	int i, j;
	int n = sorted.size();
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1; j++) {
			if (sorted[j] > sorted[j + 1])
				swap(&sorted[j], &sorted[j + 1]);
		}
	}
}
