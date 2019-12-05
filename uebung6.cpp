#include <iostream>
#include <chrono>
#include <vector>

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
    int bound = list.size() - 1;
    
    while (bound > 0)
    {
	int k = 1;
	int j = 0;
        
	do {
		if (list[j] > list[j+1]) {
			swap(&list[j], &list[j+1]);
			k = j;
			//print_list(list);
		}

		j++;
	} while(bound > j);
	bound = k;
    }

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

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    quicksort(list, 0, list.size()-1);
    //bubblesort(list);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    cout << "List size " << size << ": " << time_span.count() << " seconds.\n";
}

int main()
{
    
    benchmark(10);
    benchmark(100);
    benchmark(1000);
    benchmark(10000);
    benchmark(100000);

    vector<int> list = create_list(5);
    print_list(list);
    list = quicksort(list, 0, list.size() - 1);
    print_list(list);
    cout << "List sorted = " << is_sorted(list) << "\n";

    return 0;
}
