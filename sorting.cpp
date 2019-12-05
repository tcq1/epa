#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

vector<int> create_list(int size)
{
    vector<int> list(size);
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % size;
    }

    return list;
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

vector<int> bubblesort(vector<int> list)
{
    while (is_sorted(list) != 1)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i] > list[i + 1])
            {
                int tmp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = tmp;
            }
        }
    }

    return list;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int quicksort_divide(vector<int> list, int low, int high)
{
    int pivot = list[high]; // pivot
    int i = (low - 1);      // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (list[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[high]);
    return (i + 1);
}

vector<int> quicksort(vector<int> list, int low, int high)
{
    int index;
    if (low < high)
    {
        index = quicksort_divide(list, low, high);
        quicksort(list, low, index - 1);
        quicksort(list, index + 1, high);
    }
}

vector<int> heapsort(vector<int> list)
{
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

void benchmark(int size)
{
    using namespace chrono;

    vector<int> list = create_list(size);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    bubblesort(list);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    cout << "List size " << size << ": " << time_span.count() << " seconds.\n";
}

int main()
{
    /**
    benchmark(10);
    benchmark(100);
    benchmark(1000);
    benchmark(10000);
    */
    vector<int> list = create_list(5);
    print_list(list);
    quicksort(list, 0, 5);
    print_list(list);

    return 0;
}