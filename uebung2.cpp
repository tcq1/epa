#include <iostream>
#include <chrono>

struct Node
{
	int key;
	double value;
	struct Node *next;
};

struct Node *add_node(int key, double value)
{
	struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
	tmp->key = key;
	tmp->value = value;

	return tmp;
}

int get_length(struct Node *head)
{
	int length = 0;
	struct Node *current = head;

	while (current != NULL)
	{
		length++;
		current = current->next;
	}

	return length;
}

struct Node *init_list(int n)
{
	struct Node *head = add_node(1, 1);
	struct Node *current = head;

	for (int i = 2; i <= n; i++)
	{
		current->next = add_node(i, i);
		current = current->next;
	}

	return head;
}

void show_list(Node *head)
{
	struct Node *current = head;
	while (current != NULL)
	{
		std::cout << "key: " << current->key << " | value: " << current->value << "\n";
		current = current->next;
	}
}

struct Node *add_lists(struct Node *head1, struct Node *head2)
{
	if (get_length(head1) == get_length(head2) && head1 != NULL)
	{
		int key = 1;

		struct Node *current1 = head1;
		struct Node *current2 = head2;

		struct Node *head3 = add_node(1, head1->value + head2->value);
		struct Node *current3 = head3;

		std::cout << "Test1\n";

		while (head1->next != NULL)
		{
			current1 = current1->next;
			current2 = current2->next;
			key++;

			int value = current1->value + current2->value;
			current3->next = add_node(key, value);
			current3 = current3->next;
		}

		std::cout << "Test2\n";

		return head3;
	}

	std::cout << "Lists have different lengths!\n";
	return NULL;
}

struct Node *add_lists2(struct Node *head1, struct Node *head2)
{
	// assumption: list1 and list2 both sorted by key ascending

	// if one of the lists is empty other list is sum of both lists
	if (head1 == NULL)
	{
		return head2;
	}
	else if (head2 == NULL)
	{
		return head1;
	}
	else
	{
		struct Node *head3 = NULL;
		struct Node *current1 = head1;
		struct Node *current2 = head2;

		struct Node *current3, *tmp;

		while (current1 != NULL && current2 != NULL)
		{
			if (current1->key < current2->key)
			{
				tmp = add_node(current1->key, current1->value);
				current1 = current1->next; 
				//std::cout << "tmp key: " << tmp->key << " | value: " << tmp-> value << "\n";
			}
			else
			{
				if (current1->key == current2->key)
				{
					tmp = add_node(current1->key, current1->value + current2->value);
					current1 = current1->next;
					//std::cout << "tmp key: " << tmp->key << " | value: " << tmp-> value << "\n";
				}
				else
				{
					tmp = add_node(current2->key, current2->value);
					//std::cout << "tmp key: " << tmp->key << " | value: " << tmp-> value << "\n";
				}

				current2 = current2->next;
			}

			if (head3 == NULL)
			{
				//std::cout << "Head: ";
				head3 = tmp;
				current3 = head3;
			}
			else
			{
				if (tmp == NULL) break;
				current3->next = tmp;
				current3 = current3->next;
			}

			//std::cout << "current3: key: " << current3->key << " | value: " << current3->value << "\n"; 
		}

		if (get_length(head1) > get_length(head2))
		{
			while (head1->next != NULL)
			{
				current3->next = current1;
				current1 = current1->next;
				current3 = current3->next;
			}
		}
		else if (get_length(head1) < get_length(head2))
		{
			while (head2->next != NULL)
			{
				current3->next = current2;
				current2 = current2->next;
				current3 = current3->next;
			}
		}

		return head3;
	}
}

struct Node *init_list1(int size)
{
	// key: 1 2 3 4 5
	// val: 2 4 6 8 10

	struct Node *head = add_node(1, 2);
	struct Node *current = head;
	for (int i = 2; i <= size; i++)
	{
		struct Node *tmp = add_node(i, i * 2);
		current->next = tmp;
		current = current->next;
	}

	return head;
}

struct Node *init_list2(int size)
{
	// key: 1 2 3  4  5
	// val: 3 6 9 12 15

	struct Node *head = add_node(1, 3);
	struct Node *current = head;
	for (int i = 2; i <= size; i++)
	{
		struct Node *tmp = add_node(i, i * 3);
		current->next = tmp;
		current = current->next;
	}

	return head;
}
/**
std::vector<int> init_vector(int size) {
	std::vector<int> vec(size);
        for (int i = 0; i < size; i++) {
		vec[i] = i;
	}	

	return vec;
}

std::vector<int> add_vectors(std::vector<int> vec1, std::vector<int> vec2) {
	std::vector<int> vec3(std::vector::size(vec1));
	for (int i = 0; i < std::vector::size(vec1); i++) {
		vec3[i] = vec1[i] + vec2[i];
	}

	return vec3;
}*/

void benchmark_list(int size) {
	using namespace std::chrono;

        struct Node *head1 = init_list1(size);
        struct Node *head2 = init_list2(size);
   
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        add_lists2(head1, head2);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        std::cout << "List size " << size << ": " << time_span.count() << " seconds.\n";
}
/**
void benchmark_vector(int size) {
	using namespace std::chrono;

	std::vector<int> vec1 = init_vector(size);
	std::vector<int> vec2 = init_vector(size);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	//add code here

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Vector size " << size << ": " << time_span.count() << " seconds\n";
}*/

int main()
{
	benchmark_list(10);
	benchmark_list(100);
	benchmark_list(1000);
	benchmark_list(10000);
	benchmark_list(100000);
}
