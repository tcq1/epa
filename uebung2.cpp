#include <iostream>

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

		struct Node *current3;

		while (current1 != NULL && current2 != NULL)
		{
			struct Node *tmp;
			if (current1->key < current2->key)
			{
				tmp = add_node(head1->key, head1->value);
				current1 = current1->next;
				std::cout << "current1 < current2 | " << current1->key << "\n";
			}
			else
			{
				if (current1->key == current2->key)
				{
					tmp = add_node(head1->key, head1->value + head2->value);
					current1 = current1->next;
					std::cout << "current1 == current2 | " << current1->key << "\n";
				}
				else
				{
					tmp = add_node(head2->key, head2->value);
					std::cout << "current1 > current2\n";
				}
				current2 = current2->next;
			}

			if (head3 == NULL)
			{
				head3 = tmp;
				current3 = head3;
			}
			else
			{
				current3->next = tmp;
				current3 = current3->next;
			}
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

struct Node *init_list1()
{
	// key: 1 2 3 4 5
	// val: 2 4 6 8 10

	struct Node *head = add_node(1, 2);
	struct Node *current = head;
	for (int i = 2; i <= 5; i++)
	{
		struct Node *tmp = add_node(i, i * 2);
		current->next = tmp;
		current = current->next;
	}

	return head;
}

struct Node *init_list2()
{
	// key: 1 2 3  4  5
	// val: 3 6 9 12 15

	struct Node *head = add_node(1, 3);
	struct Node *current = head;
	for (int i = 2; i <= 5; i++)
	{
		struct Node *tmp = add_node(i, i * 3);
		current->next = tmp;
		current = current->next;
	}

	return head;
}

int main()
{
	struct Node *head1 = init_list1();
	struct Node *head2 = init_list2();
	std::cout << "List 1: "
			  << "\n";
	show_list(head1);
	std::cout << "List 2: "
			  << "\n";
	show_list(head2);
	std::cout << "List 3: "
			  << "\n";
	show_list(add_lists2(head1, head2));
}
