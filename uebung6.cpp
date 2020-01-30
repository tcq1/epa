#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

using namespace std;

vector<int> create_list(int size)
{
    vector<int> list(size);
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % (size+100);
    }

    return list;
}

void print_list(vector<int> list)
{
    cout << "List: ";
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }

    cout << "\n";
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int is_sorted(vector<int> list)
{
    int sorted = 1;
    for (int i = 0; i < list.size() - 1; i++)
    {
        if (list[i] > list[i + 1])
        {
            sorted = 0;
        }
    }

    return sorted;
}

vector<int> selectionsort(vector<int> list) {
    for (int i = 0; i < list.size(); i++) {
	int min = i;
	for (int j = i+1; j < list.size(); j++) {
		if (list[j] < list[min]) {
			min = j;
		}
	}

	swap(&list[i], &list[min]);
    }

    return list;
}

vector<int> bubblesort(vector<int> list)
{
    int comparisons = 0;
    int bound = list.size() - 1;
    
    while (bound > 0)
    {
	int k = 0;
	int j = 0;
        
	do {
		comparisons++;
		if (list[j] > list[j+1]) {
			swap(&list[j], &list[j+1]);
			k = j;
			//print_list(list);
		}

		j++;
	} while(bound > j);
	bound = k;
    }

    cout << "Comparisons: " << comparisons << "\n"; 

    return list;
}

vector<int> odd_even_sort(vector<int> list) {
	int comparisons = 0;
	for (int i = 0; i < list.size(); i++) {
		// odd
		if (i % 2 == 1) {
			comparisons++;
			#pragma omp parallel for shared(list)
			for (int j = 0; j < list.size() - 1; j = j+2) {
				if (list[j] > list[j+1]) {
					swap(list[j], list[j+1]);
				}
			}	
		}
		// even
		else {	
			comparisons++;
			#pragma omp parallel for shared(list) 
			for (int j = 1; j < list.size() - 1; j = j+2) {
				if (list[j] > list[j+1]) {
					swap(list[j], list[j+1]);
				}
			}	
		}
	}

	cout << "Comparisons: " << comparisons << "\n";

	return list;
}

vector<int> quicksort(vector<int> list, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = list[(low+high)/2];
    
    do {
	while (list[i] < pivot) {
		i++;
	}

	while (list[j] > pivot) {
		j--;
	}

	if (i <= j) {
		swap(&list[i], &list[j]);
		i++;
		j--;
	}

    } while (i <= j);

    if (j > low) {
	list = quicksort(list, low, j);
    }

    if (i < high) {
	list = quicksort(list, i, high);
    }

    return list;
}

vector<int> heapsort(vector<int> list)
{
}

void benchmark(int size)
{
    using namespace chrono;

    vector<int> list = create_list(size);
  
    cout << "List size " << size << ":\n";

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    list = odd_even_sort(list);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    if (is_sorted(list)) {
    	cout << size << ": " << time_span.count() << " seconds.\n\n";
    } else {
	cout << "Error: List not sorted correctly!\n";
    }
}

void benchmark2(int size)
{
    using namespace chrono;

    vector<int> list = create_list(size);
  
    cout << "List size " << size << ":\n";

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    list = bubblesort(list);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    if (is_sorted(list)) {
    	cout << size << ": " << time_span.count() << " seconds.\n\n";
    } else {
	cout << "Error: List not sorted correctly!\n";
    }
}

int main()
{
    std::cout << "Benchmark for odd_even_sort parallel: \n";	
    benchmark(10);
    benchmark(100);
    benchmark(1000);
    benchmark(10000);

    std::cout << "\n";

    std::cout << "Benchmark for bubblesort: \n";	
    benchmark2(10);
    benchmark2(100);
    benchmark2(1000);
    benchmark2(10000);

    

    return 0;
}
